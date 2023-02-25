#include "ConwaysGameOfLife.h"

ConwaysGameOfLife::ConwaysGameOfLife(const IntMatrix& grid)
    : itsGrid(grid), rows(itsGrid.rows()),cols(itsGrid.cols())
{
    precomputeLookUpNeighborIndices();
}

// precompute the indices of each cell's neighbors in a toroidal grid (wrapping around the edges)
void ConwaysGameOfLife::precomputeLookUpNeighborIndices(){

    const int rows =itsGrid.rows();
    const int cols =itsGrid.cols();

    auto generate_indices = [&](int row, int col, int rows, int cols){
            int row_up = toroidalWrapping(row,-1,rows);
            int col_left = toroidalWrapping(col,-1,cols);
            int row_down = toroidalWrapping(row,1,rows);
            int col_right = toroidalWrapping(col,1,cols);    
            neighborIndicesArray indices = {{
                {row_up, col_left},    // upper-left
                {row_up, col},         // upper
                {row_up, col_right},   // upper-right
                {row, col_left},       // left 
                {row, col_right},      // right
                {row_down, col_left},  // down-left
                {row_down, col},       // down
                {row_down, col_right}  // down-right
            }};
            return std::move(indices);
    };

    itsPrecomputedNeighborIndices.resize(rows);
    for (int row = 0; row < rows; ++row) {  
        itsPrecomputedNeighborIndices[row].resize(cols);
        for (int col = 0; col < cols; ++col) {
            itsPrecomputedNeighborIndices[row][col] = generate_indices(row,col,rows,cols);
        }
    }
    return;
}

// count the number of live neighbors for a given cell
uint8_t ConwaysGameOfLife::countNeighbors(const neighborIndicesArray& _neighborIndices){
    constexpr uint8_t RIGHT_MASK = 0b00000001;
    constexpr uint8_t LEFT_MASK = 0b10000000;
    uint8_t packed = 0;
    
    // pack the states of the neighbor cells into a single integer for efficiency
    for (int i = 0; i < 8; ++i) {
        const int r = _neighborIndices[i][0];
        const int c = _neighborIndices[i][1];
        packed|=(itsGrid(r,c)&RIGHT_MASK)<<i;
    }

    // count the number of live neighbors 
    uint8_t count = 0;
    count += packed & LEFT_MASK?1:0;
    count += (packed<<1) & LEFT_MASK?1:0;
    count += (packed<<2) & LEFT_MASK?1:0;
    count += (packed<<3) & LEFT_MASK?1:0;
    count += packed & RIGHT_MASK?1:0;
    count += (packed>>1) & RIGHT_MASK?1:0;
    count += (packed>>2) & RIGHT_MASK?1:0;
    count += (packed>>3) & RIGHT_MASK?1:0;

    return count;
}

// return the current state of the grid
IntMatrix ConwaysGameOfLife::getUpdatedGrid(){
    return itsGrid;
}

// update the grid to the next generation
void ConwaysGameOfLife::NextGen(){

    IntMatrix _next_grid(rows, cols);
    //#pragma omp parallel for  useful is omp.h is NOT used
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            const auto& _neighbor_indices = itsPrecomputedNeighborIndices[row][col];
            uint8_t numberOfNeighborCellsAlive = countNeighbors(_neighbor_indices); // count number of cells around the current cell 
            if (bool liveCell = itsGrid(row, col) == 1; liveCell){ // check if current cell is alive
                _next_grid(row,col) = numberOfNeighborCellsAlive==2 || numberOfNeighborCellsAlive==3; // next gen cell equals to 1 if number of neighbors 2 or 3 otherwise equals zero.
            }else{
                _next_grid(row,col)=numberOfNeighborCellsAlive==3; // next gen cell set to 1 if number of neighbors equal 3. Otherwise equal zero.
            }
        }
    }
    itsGrid = std::move(_next_grid); // avoid unnecesary copy. faster to swap?
}




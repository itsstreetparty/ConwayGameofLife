#include "ConwaysGameOfLife.h"
#include <algorithm>
#include <future>
//#include <execution>

ConwaysGameOfLife::ConwaysGameOfLife(const IntMatrix& grid)
    : itsGrid(grid), rows(itsGrid.rows()),cols(itsGrid.cols())
{
    precomputeLookUpNeighborIndices();
}

std::array<std::array<int, 2>, 8> ConwaysGameOfLife::generateIndices(int row, int col, int rows, int cols){
    const int row_up = toroidalWrapping(row,-1,rows);
    const int col_left = toroidalWrapping(col,-1,cols);
    const int row_down = toroidalWrapping(row,1,rows);
    const int col_right = toroidalWrapping(col,1,cols); 

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
    return indices;
}

// precompute the indices of each cell's neighbors in a toroidal grid (wrapping around the edges)
void ConwaysGameOfLife::precomputeLookUpNeighborIndices(){

    itsPrecomputedNeighborIndices.resize(rows);
    
    if(rows<=MINIMUM_LEVEL_OF_ROWS){ 
        for (int row = 0; row < rows; ++row) {  
            itsPrecomputedNeighborIndices[row].resize(cols);
            for (int col = 0; col < cols; ++col) {
                itsPrecomputedNeighborIndices[row][col] = generateIndices(row,col,rows,cols);
            }
        }
    }else{
        // right now XCODE, CLANG and STANDARD LIBRARY does not support OpenMP and C++17 Parallel algorithm std::execution::par is not found in #include<execution>
        //std::cout << " parallel calculation" << std::endl;
        std::vector<std::future<void>> futures;
        futures.reserve(num_threads);
        int chunk_rows = rows / num_threads;
        int odd_rows = rows % num_threads;
        for (int t = 0; t < num_threads; ++t) {
            int chunk_start = t * chunk_rows + std::min(t, odd_rows);
            int chunk_end = chunk_start + chunk_rows + (t < odd_rows ? 1 : 0);

            // create a new task for the rows inside chunk_start and chunk_end
            precomputedLookUpTable& _neighbors = itsPrecomputedNeighborIndices;
            futures.push_back(std::async(std::launch::async, [=, &_neighbors](){
                //std::cout<< " thread "<< t<< std::endl;
                for (int row = chunk_start; row < chunk_end; ++row) {
                    // generate_indices
                    _neighbors[row].resize(cols);
                    for (int col = 0; col < cols; ++col) {
                        _neighbors[row][col] = generateIndices(row,col,rows,cols);
                    }
                }
            }));
        }

        for (auto& f : futures) {
            f.get();
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

    // here parallel would be done as above
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




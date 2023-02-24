#ifndef PRECOMPUTATIONLOOKUPTABLE_H
#define PRECOMPUTATIONLOOKUPTABLE_H

#include <iostream>
#include <unordered_map>
#include <array>

#include "Matrix.h"
#include "Utils.h"

using namespace std;

using precomputedNeighborIndices = std::vector<std::vector<std::array<std::array<int, 2>, 8>>>;

template<typename T>
int naiveNeighborCountingLookUpTable(const std::array<std::array<int, 2>, 8>& neighborIndices, const Matrix<T>& currentGrid){

    int sum = 0;
    for (int i = 0; i < 8; ++i) {
        const int r = neighborIndices[i][0];
        const int c = neighborIndices[i][1];
        const auto value = currentGrid(r,c);
        sum += value;
    }
    return sum;
}


/*SAVE MEMORY by using bitwise operation*/  
template<typename T>
uint8_t countNeighbors(const std::array<std::array<int, 2>, 8>& neighborIndices, const Matrix<T>& currentGrid){ // change currentGrid to Matrix<uint_8> 

    
    const uint8_t RIGHT_MASK = 0b00000001;
    const uint8_t LEFT_MASK = 0b10000000;
    uint8_t packed = 0;
    //int sum = 0;
    for (int i = 0; i < 8; ++i) {
        const int r = neighborIndices[i][0];
        const int c = neighborIndices[i][1];
        // pack the states of the neighbor cells into a single integer
        packed|=(currentGrid(r,c)&RIGHT_MASK)<<i;
    }

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


template<typename T>
void precomputeLookUpNeighborIndices(const Matrix<T>& currentGrid, precomputedNeighborIndices& _precomputedNeighborIndices){

    const int rows =currentGrid.rows();
    const int cols =currentGrid.cols();
    _precomputedNeighborIndices.resize(rows);

    for (int row = 0; row < rows; ++row) {
        _precomputedNeighborIndices[row].resize(cols);
        for (int col = 0; col < cols; ++col) {

            int row_up = wrappingtoroidalindice(row,-1,rows);
            int col_left = wrappingtoroidalindice(col,-1,cols);
            int row_down = wrappingtoroidalindice(row,1,rows);
            int col_right = wrappingtoroidalindice(col,1,cols);
            _precomputedNeighborIndices[row][col] = {{
                {row_up, col_left},    // upper-left
                {row_up, col},         // upper
                {row_up, col_right},   // upper-right
                {row, col_left},       // left 
                {row, col_right},      // right
                {row_down, col_left},  // down-left
                {row_down, col},       // down
                {row_down, col_right}  // down-right
            }};
        }
    }
    return;
}


/*** Rules of Life with precomputed Neighbor Indices ***/
template <typename T>
const Matrix<T> rulesOfLifeO1(const Matrix<T>& _actual_grid,const precomputedNeighborIndices& _precomputedNeighborIndices){

    const int rows =_actual_grid.rows();
    const int cols =_actual_grid.cols();
    Matrix<T> _next_grid(_actual_grid.rows(), _actual_grid.cols());

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {

            //For each element, you determine whether it is a live cell or a dead cell based on its value (1 for live, 0 for dead).
            bool liveCell = _actual_grid(row,col)==1;

            //You then count the number of live cells in the 8 neighboring cells around the current element. 
            //These 8 neighboring cells are the ones directly above, below, to the left, to the right, and in the diagonal directions.
            const auto& _neighbor_indices = _precomputedNeighborIndices[row][col];
            int numberOfNeighborCellsAlive = naiveNeighborCountingLookUpTable(_neighbor_indices,_actual_grid);

            /***If the current cell is a live cell and has 2 or 3 live neighbors, it survives to the next generation and its value in the new matrix is set to 1. 
             * If the cell has any other number of live neighbors, it dies and its value in the new matrix is set to 0.***/
            if (liveCell){
                if(numberOfNeighborCellsAlive==2 || numberOfNeighborCellsAlive==3){
                    _next_grid(row,col) = 1;  
                }else{
                    _next_grid(row,col) = 0;    
                }
            /***If the current cell is a dead cell and has exactly 3 live neighbors, it becomes a live cell in the next generation and its value in the new matrix is set to 1. 
             * If the cell has any other number of live neighbors, it remains dead and its value in the new matrix is set to 0..***/
            }else{
                if(numberOfNeighborCellsAlive==3){
                    _next_grid(row,col) = 1;  
                }else{
                    _next_grid(row,col) = 0;       
                }
            }
        }
    }
    return _next_grid;

}



/*** Rules of Life with precomputed Neighbor Indices ***/
template <typename T>
const IntMatrix rulesOfLifeO2(const Matrix<T>& _actual_grid,const precomputedNeighborIndices& _precomputedNeighborIndices){

    const int rows =_actual_grid.rows();
    const int cols =_actual_grid.cols();
    IntMatrix _next_grid(_actual_grid.rows(), _actual_grid.cols());

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {

            //For each element, you determine whether it is a live cell or a dead cell based on its value (1 for live, 0 for dead).
            bool liveCell = _actual_grid(row,col)==1;

            //You then count the number of live cells in the 8 neighboring cells around the current element. 
            //These 8 neighboring cells are the ones directly above, below, to the left, to the right, and in the diagonal directions.
            const auto& _neighbor_indices = _precomputedNeighborIndices[row][col];

            uint8_t numberOfNeighborCellsAlive = countNeighbors(_neighbor_indices,_actual_grid);


            
            /***If the current cell is a live cell and has 2 or 3 live neighbors, it survives to the next generation and its value in the new matrix is set to 1. 
             * If the cell has any other number of live neighbors, it dies and its value in the new matrix is set to 0.***/
            if (liveCell){
                if(numberOfNeighborCellsAlive==2 || numberOfNeighborCellsAlive==3){
                    _next_grid(row,col) = 1;  
                }else{
                    _next_grid(row,col) = 0;    
                }
            /***If the current cell is a dead cell and has exactly 3 live neighbors, it becomes a live cell in the next generation and its value in the new matrix is set to 1. 
             * If the cell has any other number of live neighbors, it remains dead and its value in the new matrix is set to 0..***/
            }else{
                if(numberOfNeighborCellsAlive==3){
                    _next_grid(row,col) = 1;  
                }else{
                    _next_grid(row,col) = 0;       
                }
            }
        }
    }
    return _next_grid;

}



#endif


#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "Matrix.h"

using namespace std;

void my_function1() {
    std::cout << "Hello, world!\n";
}

// wrapping toroidal indices 
int wrappingtoroidalindice(int idx, int idx_offset,int num_ele_){
    return (idx + idx_offset + num_ele_)%num_ele_;
}

const IntMatrix naiveNeighborIndices(int row, int col, int rows, int cols) {
    const IntMatrix m  = {
        {wrappingtoroidalindice(row,-1,rows), wrappingtoroidalindice(col,-1,cols)},     // top-left
        {wrappingtoroidalindice(row,-1,rows), wrappingtoroidalindice(col,0,cols)},      // top
        {wrappingtoroidalindice(row,-1,rows), wrappingtoroidalindice(col,1,cols)},      // top-right
        {wrappingtoroidalindice(row,0,rows), wrappingtoroidalindice(col,-1,cols)},      // left
        {wrappingtoroidalindice(row,0,rows), wrappingtoroidalindice(col,1,cols)},       // right
        {wrappingtoroidalindice(row,1,rows), wrappingtoroidalindice(col,-1,cols)},      // bottom-left
        {wrappingtoroidalindice(row,1,rows), wrappingtoroidalindice(col,0,cols)},       // bottom
        {wrappingtoroidalindice(row,1,rows), wrappingtoroidalindice(col,1,cols)}        // bottom-right
    };
    return m;
}

template<typename T>
int naiveNeighborCounting(const IntMatrix& neighborIndices, const Matrix<T>& m){

    int sum = 0;
    for (int i = 0; i < 8; ++i) {
        const int r = neighborIndices(i,0);
        const int c = neighborIndices(i,1);
        const auto value = m(r,c);
        sum += value;

        // // Print the values of the neighboring elements
        // if (i<=2){
        //     cout << value << "  ,";
        // }else if(i==3){
        //     cout << endl;
        //     cout << value << "  ,";
        // }else if(i==4){
        //     cout << "X" << "    ,"; 
        //     cout << value << "  ,"; 
        //     cout << endl; 
        // }else{
        //     cout << value << "  ,";    
        // }
    }

    return sum;
}

// template <typename T>
// Matrix<T> create_matrix(int n, int m, T init_value) {
//     Matrix<T> matrix(n, m);
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             matrix(i, j) = init_value;
//         }
//     }
//     return matrix;
// }


template <typename T>
const Matrix<T> rulesOfLife(const Matrix<T>& _actual_grid) {

    const int rows =_actual_grid.rows();
    const int cols =_actual_grid.cols();
    Matrix<T> _next_grid(_actual_grid.rows(), _actual_grid.cols());

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {

            //For each element, you determine whether it is a live cell or a dead cell based on its value (1 for live, 0 for dead).
            bool liveCell = _actual_grid(row,col)==1;

            //You then count the number of live cells in the 8 neighboring cells around the current element. 
            //These 8 neighboring cells are the ones directly above, below, to the left, to the right, and in the diagonal directions.
            IntMatrix _neighbor_indices = naiveNeighborIndices(row,col,rows,cols);
            int numberOfNeighborCellsAlive = naiveNeighborCounting(_neighbor_indices,_actual_grid);

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
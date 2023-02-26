#ifndef CONWAYSGAMEOFLIFE_H
#define CONWAYSGAMEOFLIFE_H

#include <vector>
//#include <cstdint>
#include <array>
#include "Matrix.h"

class ConwaysGameOfLife {
public:
    ConwaysGameOfLife(const IntMatrix& grid);
    //ConwaysGameOfLife(std::vector<string>& inputFile);
    void NextGen();
    //IntMatrix calNextGen();
    IntMatrix getUpdatedGrid();


private:
    //int itsGrid;

    using neighborIndicesArray = std::array<std::array<int, 2>, 8>;
    //using precomputedLookUpTable = std::vector<std::vector<std::array<std::array<int, 2>, 8>>>;
    using precomputedLookUpTable = std::vector<std::vector<neighborIndicesArray>>;
    precomputedLookUpTable itsPrecomputedNeighborIndices;
    void precomputeLookUpNeighborIndices();
    uint8_t countNeighbors(const neighborIndicesArray& _neighborIndices);
    std::array<std::array<int, 2>, 8> generateIndices(int row, int col, int rows, int cols);
    inline uint8_t toroidalWrapping(int idx, int idx_offset,int num_ele_){
        return static_cast<uint8_t>((idx + idx_offset + num_ele_)%num_ele_);
    }
    
    IntMatrix itsGrid;
    //IntMatrix nextGenGrid;
    const int rows;
    const int cols;
    int iterations;
    const int num_threads=4; //number of threads this is only to show off 
    const int MINIMUM_LEVEL_OF_ROWS=5; //this should be a higher number 
    /*As a general rule, it is usually only worth using threads for tasks that are computationally expensive and can be parallelized, such as matrix multiplication, image processing, or scientific simulations. For smaller tasks, the overhead of creating and synchronizing threads can actually slow down the computation.
    The number of available threads is also an important consideration. If there are only a few cores available, or if the available cores are already being used for other tasks, adding additional threads may not provide a significant speedup.
    In general, it is best to profile the code and measure the performance with and without threads to determine the optimal number of threads for the given task and hardware. This can help identify any performance bottlenecks and determine if using threads is worthwhile.
    */   
};

#endif // CONWAYS_GAME_OF_LIFE_H

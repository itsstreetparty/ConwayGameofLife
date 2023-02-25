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
    inline uint8_t toroidalWrapping(int idx, int idx_offset,int num_ele_){
        return static_cast<uint8_t>((idx + idx_offset + num_ele_)%num_ele_);
    }
    
    IntMatrix itsGrid;
    //IntMatrix nextGenGrid;
    const int rows;
    const int cols;
    int iterations;
    
};

#endif // CONWAYS_GAME_OF_LIFE_H

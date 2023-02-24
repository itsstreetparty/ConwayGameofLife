#include <iostream>
#include <vector>
#include <string>
#include <cmath>
//#include <immintrin.h> 
#include "Event.h"
#include "Utils.h"
#include "Matrix.h"
#include "PrecomputationLookUpTable.h"


using namespace std;

int main()
{
    // vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    // for (const string& word : msg)
    // {
    //     cout << word << " ";
    // }
    // cout << endl;

    cout << " main " << endl;

    IntMatrix initial_grid = {
       {1,1,1,0},
       {1,1,1,0},
       {0,0,0,0}
    };

    int row = 0;
    int col = 1;
    int rows = initial_grid.rows();
    int cols = initial_grid.cols();
    auto neighborg_indices = naiveNeighborIndices(row,col,rows,cols);

    //cout << naiveNeighborCounting(neighborg_indices, initial_grid) << endl;

   std::vector<std::vector<IntMatrix>> possible;

    cout << initial_grid << endl;

    constexpr int iterations = 3;

    auto changing_grid = initial_grid;
    for (int iter=0; iter<1; ++iter){
        cout << " rulesOfLife " << iter << endl;
        const auto new_grid = rulesOfLife(changing_grid);
         cout << new_grid << endl;
        changing_grid = new_grid;
    }

    precomputedNeighborIndices itsPNI;
    precomputeLookUpNeighborIndices(initial_grid,itsPNI);
    const auto new_grid = rulesOfLifeO1(initial_grid,itsPNI);
    cout << " rulesOfLifeO1 " << endl;
    cout << new_grid << endl;


    const auto new_grid2 = rulesOfLifeO2(initial_grid,itsPNI);
    cout << " rulesOfLifeO2 " << endl;
    cout << new_grid << endl;



    // uint8_t packed = 0b10101010;
    // uint8_t LEFT_MASK = 0b10000000;
    // uint8_t RIGHT_MASK = 0b00000001;

    // uint8_t count = 0;

    // count += packed & LEFT_MASK?1:0;
    // count += (packed<<1) & LEFT_MASK?1:0;
    // count += (packed<<2) & LEFT_MASK?1:0;
    // count += (packed<<3) & LEFT_MASK?1:0;
    // count += packed & RIGHT_MASK?1:0;
    // count += (packed>>1) & RIGHT_MASK?1:0;
    // count += (packed>>2) & RIGHT_MASK?1:0;
    // count += (packed>>3) & RIGHT_MASK?1:0;

    // std::cout << " count "<< count << std::endl;

    return 0;  

}
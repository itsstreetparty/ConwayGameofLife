#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Event.h"
#include "Utils.h"
#include "Matrix.h"

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

    Matrix<int> initial_grid = {
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

    cout << initial_grid << endl;

    constexpr int iterations = 3;

    cout << initial_grid << endl;
    auto changing_grid = initial_grid;
    for (int iter=0; iter<3; ++iter){
        cout << " iteration " << iter << endl;
        const auto new_grid = rulesOfLife(changing_grid);
         cout << new_grid << endl;
        changing_grid = new_grid;
    }

    return 0;

}
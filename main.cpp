#include <iostream>
#include "Matrix.h"
#include "ConwaysGameOfLife.h"

using namespace std;

int main()
{
    IntMatrix initial_grid = {
       {0,0,1,0},
       {0,1,1,0},
       {0,0,0,0}
    };

    // Create a ConwaysGameOfLife object with the input matrix
    ConwaysGameOfLife game(initial_grid);
    cout << " rulesOfLife " << endl;
    cout << game.NextGen() << endl;

    return 0;  

}
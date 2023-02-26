#include <iostream>
#include <filesystem>
#include <vector>

#include "Matrix.h"
#include "ConwaysGameOfLife.h"
#include "Filemanager.h"
#include "CommonUtils.h"

using namespace std;

void some_function(int value) {
  // do something with value
}

int main()
{
    FileManager myFile(getFilePath("input.txt"));
    auto itsLines = myFile.readLines();

    int number_of_iterations = getNumberOfIterations(itsLines); // this removes the last line of ITSLINES
    auto itsInputMatrix = converToMatrix(itsLines);

    // Create a ConwaysGameOfLife object with the input matrix
    ConwaysGameOfLife game(itsInputMatrix);
    for (size_t i=0; i<number_of_iterations;++i){
        game.NextGen();
    }    
    cout << game.getUpdatedGrid() << endl;

    auto vector = converToVectorOfStrings(game.getUpdatedGrid());
    myFile.writeFile("output.txt",vector);

    return 0;  

}
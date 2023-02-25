#include <iostream>
#include <filesystem>
#include <algorithm>

#include "Matrix.h"
#include "ConwaysGameOfLife.h"
#include "Filemanager.h"
#include "CommonUtils.h"

using namespace std;

int main()
{

    // IntMatrix initial_grid = { // to test 
    //    {0,0,1,0},
    //    {0,1,1,0},
    //    {0,0,0,0}
    // };

    std::filesystem::path cwd = std::filesystem::current_path();
    std::filesystem::path filename = "input.txt";
    std::filesystem::path filepath = cwd / filename;
    std::string filepath_str = filepath.string();
    FileManager myFile(filepath_str);
    auto itsLines = myFile.readLines();

    int number_of_iterations = getNumberOfIterations(itsLines);
    auto itsInputMatrix = converToMatrix(itsLines);

    // Create a ConwaysGameOfLife object with the input matrix
    ConwaysGameOfLife game(itsInputMatrix);
    for (size_t i=0; i<number_of_iterations;++i){
        game.NextGen();
    }    
    std::cout << game.getUpdatedGrid() << std::endl;

    auto vector = converToVectorOfStrings(game.getUpdatedGrid());
    myFile.writeFile("output.txt",vector);

    return 0;  

}
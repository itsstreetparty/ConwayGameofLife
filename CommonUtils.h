#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <iostream>
#include <vector>
#include "Matrix.h"


int getNumberOfIterations(std::vector<std::string>& lines) {
    int number_of_iterations = std::stoi(lines.back());
    std::cout << " number of iterations "<< number_of_iterations << std::endl;
    lines.pop_back();
    return number_of_iterations;
}

IntMatrix converToMatrix(std::vector<std::string>& lines){

    std::for_each(lines.begin(),lines.end(),[](auto& value){
        char last_char = value.back();
        if (last_char == ' ' || last_char == '\t' || last_char == '\n' || static_cast<int>(last_char) ==13 ){
            value.pop_back();
        }
    });

    const int _ROWS= lines.size();
    const int _COLS= lines[0].size();

    for (int i = 1; i < lines.size(); ++i) {
        if (lines[i].size() != _COLS) {
            throw std::runtime_error("Input matrix has rows of different lengths");
        }
    }

    IntMatrix matrix(_ROWS,_COLS);
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[0].size(); j++) {
            matrix(i, j) = static_cast<uint8_t>(lines[i][j] - '0');
        }
    }

    return std::move(matrix);

}

std::vector<std::string> converToVectorOfStrings(const IntMatrix& matrix){
    const int _ROWS = matrix.rows();
    const int _COLS = matrix.cols();
    
    std::vector<std::string> vec;
    
    for (int i = 0; i < _ROWS; ++i) {
        std::string str="";
        for (int j = 0; j < _COLS; ++j) {
            //matrix(i, j) = static_cast<uint8_t>(lines[i][j] - '0');
            str += std::to_string(matrix(i,j));
        }
        //std::cout << str << std::endl;
        vec.emplace_back(str);
    }
    return std::move(vec);
}

std::string getFilePath(std::string filename){

    std::filesystem::path cwd = std::filesystem::current_path();
    //std::filesystem::path filename = "input.txt";
    std::filesystem::path filepath = cwd / filename;
    std::string filepath_str = filepath.string();
    return filepath_str;

}


#endif
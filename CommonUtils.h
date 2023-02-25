#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <iostream>
#include <vector>
#include "Matrix.h"

void my_function() {
    std::cout << "Hello, world!\n";
}


int getNumberOfIterations(std::vector<std::string>& lines) {
    int number_of_iterations = std::stoi(lines.back());
    std::cout << " number of iterations "<< number_of_iterations << std::endl;
    lines.pop_back();
    return number_of_iterations;
}


void removeLastCharacter(std::vector<std::string>& lines){
    std::for_each(lines.begin(),lines.end(),[](auto& value){
        char last_char = value.back();
        if (last_char == ' ' || last_char == '\t' || last_char == '\n' || static_cast<int>(last_char) ==13 ){
            value.pop_back();
        }
        for (char c : value) {
            std::cout << "Character: " << c << " (ASCII " << static_cast<int>(c) << ")" << std::endl;
        }
        std::cout << value << " value size " << value.size() <<std::endl;
    });
}

IntMatrix converToMatrix(std::vector<std::string>& lines){

    std::for_each(lines.begin(),lines.end(),[](auto& value){
        char last_char = value.back();
        if (last_char == ' ' || last_char == '\t' || last_char == '\n' || static_cast<int>(last_char) ==13 ){
            value.pop_back();
        }
        // for (char c : value) {
        //     std::cout << "Character: " << c << " (ASCII " << static_cast<int>(c) << ")" << std::endl;
        // }
        // std::cout << value << " value size " << value.size() <<std::endl;
    });

    const int _ROWS= lines.size();
    const int _COLS= lines[0].size();
    IntMatrix matrix(_ROWS,_COLS);
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[0].size(); j++) {
            matrix(i, j) = static_cast<uint8_t>(lines[i][j] - '0');
        }
    }

    return std::move(matrix);

}


#endif
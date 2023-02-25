#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>

class FileManager {
public:
    FileManager(const std::string& filename);
    std::vector<std::string> readLines();
    void writeFile(const std::string& filename,std::vector<std::string> lines);
    bool fileExists();
    bool checkFileSize();
    bool is_text_file();
    bool file_Exists=false;
    bool file_size_correct=false;
    bool isTextFile=false;
    std::vector<std::string> lines;

    friend std::ostream& operator<<(std::ostream& os, const FileManager& obj) {

        for (const auto& element : obj.lines) {
            std::cout << element<< std::endl;
        }

        return os;
    }

private:
    
    //const int m_value = 42;
    std::string m_filename;
    std::ifstream infile;
    const int oneMBinbytes=1048576;
    
};

#endif

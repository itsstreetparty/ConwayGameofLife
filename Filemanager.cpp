#include "Filemanager.h"


FileManager::FileManager(const std::string& filename) : m_filename(filename) {
    if (fileExists()){
        std::cout<< " file exists" << std::endl;
        if (checkFileSize()){
            std::cout<< " file size is correct" << std::endl;
            if (is_text_file()){
                std::cout<< " is a text file "<< std::endl;
            }else{
                std::cout<< " IT IS NOT A TEXT FILE "<< std::endl;
            }
        }else{
            std::cout<< " file is over than 1MB "<< std::endl;
        }
    }else{
        std::cout<< " file does not exist" << std::endl;
    }
}

std::vector<std::string> FileManager::readLines() {

    std::ifstream myfile(m_filename);
    std::string line;
    if(myfile.is_open()){
        while(std::getline(myfile,line)){
            lines.push_back(line);
        }
        myfile.close();
    }else{
        std::cout<< " file is not there "<< std::endl;
    }
    return lines;
}

void FileManager::writeFile(const std::string& filename,std::vector<std::string> lines){

    std::ofstream outfile(filename);
    if(outfile.is_open()){
        std::for_each(lines.begin(), lines.end(), [&outfile](const std::string& line){ outfile << line << std::endl; });
        outfile.close();
        std::cout << "File written successfully." << std::endl;
    } else {
        std::cout << "Failed to open file." << std::endl;
    }
}

bool FileManager::fileExists(){
    file_Exists=std::filesystem::exists(m_filename);
    return file_Exists;
}

bool FileManager::checkFileSize(){
    std::filesystem::path path = std::filesystem::path(m_filename);
    std::uintmax_t filesize = std::filesystem::file_size(path);
    file_size_correct = filesize<=oneMBinbytes?true:false;
    return file_size_correct;
}

bool FileManager::is_text_file(){
    infile.open(m_filename);
    char c;
    while (infile.get(c)) {
        if( c < 0 || c > 127){
            isTextFile=false;
            infile.close();
            return isTextFile;
            }
        }
    isTextFile=true;
    infile.close();
    return isTextFile;
}


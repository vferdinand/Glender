#include "loader.h"

#include<iostream>
#include<string>
#include<fstream>


void load_obj(const std::string& file_path_obj, std::vector<int>& vertices, std::vector<int>& faces){
    std::ifstream file_obj(file_path_obj);

    if(!file_obj.is_open()){
        std::cerr << "Dummkopf Failed to open file:" << file_path_obj << std::endl;
    }
    std::string line;
    while(std::getline(file_obj, line)){
        std::cout << line << std::endl;
    }
    file_obj.close();
}
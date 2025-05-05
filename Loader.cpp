#include "Loader.hpp"

//#include "Vertex.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

//Loader::Loader(const std::string& file_path) : filePath(file_path) {}

Loader::Loader(){}

bool Loader::loadOBJ(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Dummkopf Failed to open file: " << filePath << std::endl;
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;        
        if (prefix == "v") {
            Vertex v;
            iss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        } else if (prefix == "f") {
            unsigned int a, b, c;
            iss >> a >> b >> c;
            triangles.push_back(Triangle({a - 1, b - 1, c - 1}));
        }
    }

    file.close();
    return true;
}

const std::vector<Vertex>& Loader::getVertices() const {
    return vertices;
}

const std::vector<Triangle>& Loader::getTriangles() const {
    return triangles;
}

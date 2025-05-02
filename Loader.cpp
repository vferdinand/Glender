#include "Loader.h"

#include "Vertex.h"

#include <fstream>
#include <sstream>
#include <iostream>

Loader::Loader(const std::string& file_path) : filePath(file_path) {}

bool Loader::load() {
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
            int a, b, c;
            iss >> a >> b >> c;
            // Convert from 1-based to 0-based indexing
            triangles.push_back(a - 1);
            triangles.push_back(b - 1);
            triangles.push_back(c - 1);
        }
    }

    file.close();
    return true;
}

const std::vector<Vertex>& Loader::getVertices() const {
    return vertices;
}

const std::vector<float>& Loader::getTriangles() const {
    return triangles;
}

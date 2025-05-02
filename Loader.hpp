#ifndef LOADER_H
#define LOADER_H

#include "Vertex.hpp"

#include <string>
#include <vector>


class Loader {
private:
	std::string filePath;
	std::vector<Vertex> vertices;  
    std::vector<float> triangles;    


public:
    Loader(const std::string& file_path);

    bool load();

    const std::vector<Vertex>& getVertices() const;
    const std::vector<float>& getTriangles() const;
};

#endif

#ifndef LOADER_H
#define LOADER_H

#include "Vertex.hpp"
#include "Triangle.hpp"

#include <string>
#include <vector>


class Loader {
private:
	//std::string filePath;
	std::vector<Vertex> vertices;  
    std::vector<Triangle> triangles;    


public:
    //Loader(const std::string& file_path);
    Loader();

    bool loadOBJ(const std::string& filePath);

    const std::vector<Vertex>& getVertices() const;
    const std::vector<Triangle>& getTriangles() const;
};

#endif

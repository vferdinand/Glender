#pragma once

#include "Structs.hpp"
#include "Triangle.hpp"

#include <string>
#include <vector>

#include <fstream>
#include <sstream>
#include <iostream>


class Loader {
private:
	std::vector<Vertex> vertices;
    std::vector<Vector3D> verticesNormals;
    std::vector<Triangle> triangles;
    std::vector<RGBA> colors;
    std::vector<std::string> materialNames;

    bool initializeColor(const std::string& filePathMTL);
    bool initializeVerticiesTriangles(const std::string& filePathOBJ);
    int16_t locateMaterial(const std::string& material);

public:
    //Loader(const std::string& file_path);
    Loader();

    bool loadOBJ(const std::string& filePathOBJ, const std::string& filePathMTL = "");

    const std::vector<Vertex>& getVertices() const;
    const std::vector<Triangle>& getTriangles() const;
    const std::vector<RGBA>& getColors() const;
};

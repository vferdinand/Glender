#include <stdio.h>
#include <iostream>
#include <vector>
#include "loader.h"

int main() {
    std::string file_path_obj = "test.obj";
    std::vector<int> vertices;
    std::vector<int> faces;
    load_obj(file_path_obj, vertices, faces);
}
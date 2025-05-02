#ifndef LOADER_H
#define LOADER_H
#include <string>
#include <vector>


class Loader {
public:
    Loader(const std::string& file_path);

    bool load();

    const std::vector<float>& getTriangles() const;
    const std::vector<float>& getVertices() const;
};
void load_obj(const std::string& file_path_obj, std::vector<int>& vertices, std::vector<int>& faces);

#endif

#pragma once

#include "Structs.hpp"

#include <vector>

class Image {
    private:
        std::vector<std::vector<RGBA>> data;
    public:
        Image(size_t rows, size_t cols, RGBA defaultValue = {0.0,0.0,0.0,0.0});
    
        void set(size_t row, size_t col, RGBA value);
        RGBA get(size_t row, size_t col) const;

        // tmp for debugging
        // ersetzt durch save() in future
        void print() const;

        // 
        void save();
};
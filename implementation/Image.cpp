#include "../hpp/Image.hpp"
#include <iostream>

Image::Image(size_t rows, size_t cols, RGBA defaultValue)
    : data(rows, std::vector<RGBA>(cols, defaultValue)) {}

void Image::set(size_t row, size_t col, RGBA value) {
    if (row < data.size() && col < data[row].size()) {
        data[row][col] = value;
    }
}

RGBA Image::get(size_t row, size_t col) const {
    if (row < data.size() && col < data[row].size()) {
        return data[row][col];
    }
    return {0.0, 0.0, 0.0, 1.0};
}

size_t Image::rowCount() const {
    return data.size();
}

size_t Image::colCount() const {
    return data.empty() ? 0 : data[0].size();
}

void Image::print() const {
    for (const auto& row : data) {
        for (RGBA val : row) {
            std::cout << val << ' ';
        }
        std::cout << '\n';
    }
}

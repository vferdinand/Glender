#include "../hpp/Image.hpp"

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
    return {0.0, 0.0, 0.0, 0.0};
}

void Image::print() const {
    for (const auto& row : data) {
        for (RGBA val : row) {
            std::cout << val << ' ';
        }
        std::cout << '\n';
    }
}

void Image::save(const std::string& filename) {
    std::string outName = filename.empty() ? "output.ppm" : filename;

    std::ofstream ofs(outName, std::ios::binary);
    if (!ofs) {
        std::cerr << "Fehler: Konnte Datei nicht öffnen: " << outName << std::endl;
        return;
    }

    size_t height = data.size();
    size_t width  = (height > 0 ? data[0].size() : 0);

    if (width == 0 || height == 0) {
        std::cerr << "Warnung: Bilddaten sind leer, PPM wird trotzdem mit 0×0 abgespeichert." << std::endl;
    }

    ofs << "P6\n"
        << width << " " << height << "\n"
        << "255\n";

    for (const auto& row : data) {
        for (const auto& px : row) {
            uint8_t r_byte = static_cast<uint8_t>(px.r * 255.0f);
            uint8_t g_byte = static_cast<uint8_t>(px.g * 255.0f);
            uint8_t b_byte = static_cast<uint8_t>(px.b * 255.0f);

            ofs.put(static_cast<char>(r_byte));
            ofs.put(static_cast<char>(g_byte));
            ofs.put(static_cast<char>(b_byte));
        }
    }

    ofs.close();
    return;
}
#include "../hpp/Image.hpp"

/*
* Image class implementation
* 
* Diese Klasse repräsentiert ein 2D-Bild mit RGBA-Werten.
* Sie bietet Methoden zum Setzen und Abrufen von Pixelwerten sowie zum Drucken des Bildes.
* Das Bild wird mit einer bestimmten Anzahl von Zeilen und Spalten initialisiert und kann mit einem Standard-RGBA-Wert gefüllt werden.
*/

/**
 * @brief Konstruktor der Image-Klasse.
 * 
 * Initialisiert ein 2D-Bild mit gegebener Anzahl an Zeilen und Spalten.
 * Jeder Pixel wird mit einem Standard-RGBA-Wert gefüllt.
 * 
 * @param rows Anzahl der Zeilen (Höhe des Bildes)
 * @param cols Anzahl der Spalten (Breite des Bildes)
 * @param defaultValue RGBA-Wert, mit dem das Bild initialisiert wird
 */
Image::Image(size_t rows, size_t cols, RGBA defaultValue)
    : data(rows, std::vector<RGBA>(cols, defaultValue)) {}

/**
 * @brief Setzt den RGBA-Wert eines bestimmten Pixels.
 * 
 * @param row Zeilenindex
 * @param col Spaltenindex
 * @param value Neuer RGBA-Wert
 */
void Image::set(size_t row, size_t col, RGBA value) {
    if (row < data.size() && col < data[row].size()) {
        data[row][col] = value;
    }
}

/**
 * @brief Gibt den RGBA-Wert eines bestimmten Pixels zurück.
 * 
 * @param row Zeilenindex
 * @param col Spaltenindex
 * @return RGBA Wert an der angegebenen Position, oder {0,0,0,0}, wenn ungültig
 */
RGBA Image::get(size_t row, size_t col) const {
    if (row < data.size() && col < data[row].size()) {
        return data[row][col];
    }
    return {0.0, 0.0, 0.0, 0.0};
}

/**
 * @brief Gibt das Bild als Text aus (nur zu Debug-Zwecken).
 * 
 * Gibt jeden Pixel als RGBA-Wert auf der Konsole aus.
 */
void Image::print() const {
    for (const auto& row : data) {
        for (RGBA val : row) {
            std::cout << val << ' ';
        }
        std::cout << '\n';
    }
}

/**
 * @brief Speichert das Bild im PPM-Format.
 * 
 * Die Datei wird als "P6" (binäres RGB) gespeichert.
 * Der Alpha-Kanal wird ignoriert. Die RGB-Werte werden jeweils von [0.0, 1.0] in [0, 255] konvertiert.
 * 
 * @param filename Name der Ausgabedatei. Wenn leer, wird "output.ppm" verwendet.
 */
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
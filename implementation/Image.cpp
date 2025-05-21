#include "../hpp/Image.hpp"
#include <iostream>

/*
* Image class implementation
* 
* Diese Klasse repräsentiert ein 2D-Bild mit RGBA-Werten.
* Sie bietet Methoden zum Setzen und Abrufen von Pixelwerten sowie zum Drucken des Bildes.
* Das Bild wird mit einer bestimmten Anzahl von Zeilen und Spalten initialisiert und kann mit einem Standard-RGBA-Wert gefüllt werden.
*/

Image::Image(size_t rows, size_t cols, RGBA defaultValue)
    : data(rows, std::vector<RGBA>(cols, defaultValue)) {}

// Setzt den Wert eines Pixels an der angegebenen Position (row, col) im Bild.
void Image::set(size_t row, size_t col, RGBA value) {
    if (row < data.size() && col < data[row].size()) {
        data[row][col] = value;
    }
}
// Gibt den Wert eines Pixels an der angegebenen Position (row, col) im Bild zurück.
RGBA Image::get(size_t row, size_t col) const {
    if (row < data.size() && col < data[row].size()) {
        return data[row][col];
    }
    return {0.0, 0.0, 0.0, 0.0};
}
// Diese Methode wird später durch eine Methode ersetzt, die das Bild in eine Datei speichert.
// Derzeit wird sie nur für Debugging-Zwecke verwendet.
void Image::print() const {
    for (const auto& row : data) {
        for (RGBA val : row) {
            std::cout << val << ' ';
        }
        std::cout << '\n';
    }
}
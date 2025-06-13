#pragma once

#include "Structs.hpp"

#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

class Image {
    private:
        std::vector<std::vector<RGBA>> data;
    public:

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
        Image(size_t rows, size_t cols, RGBA defaultValue = {0.0,0.0,0.0,0.0});

        /**
         * @brief Setzt den RGBA-Wert eines bestimmten Pixels.
         * 
         * @param row Zeilenindex
         * @param col Spaltenindex
         * @param value Neuer RGBA-Wert
         */
        void set(size_t row, size_t col, RGBA value);

        /**
         * @brief Gibt den RGBA-Wert eines bestimmten Pixels zurück.
         * 
         * @param row Zeilenindex
         * @param col Spaltenindex
         * @return RGBA Wert an der angegebenen Position, oder {0,0,0,0}, wenn ungültig
         */
        RGBA get(size_t row, size_t col) const;


        /**
         * @brief Gibt das Bild als Text aus (nur zu Debug-Zwecken).
         * 
         * Gibt jeden Pixel als RGBA-Wert auf der Konsole aus.
         */
        // tmp for debugging
        // ersetzt durch save() in future
        void print() const;

        /**
         * @brief Speichert das Bild im PPM-Format.
         * 
         * Die Datei wird als "P6" (binäres RGB) gespeichert.
         * Der Alpha-Kanal wird ignoriert. Die RGB-Werte werden jeweils von [0.0, 1.0] in [0, 255] konvertiert.
         * 
         * @param filename Name der Ausgabedatei. Wenn leer, wird "output.ppm" verwendet.
         */
        void save(const std::string& filename = "output.ppm");
};
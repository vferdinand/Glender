#pragma once
#include "Triangle.hpp"
#include "Ray.hpp"
#include "Hitpoint.hpp"
#include "structs/KDPrim.hpp"
#include "structs/KDNode.hpp"
#include <vector>
#include <algorithm>

class KDTree {
private:
    KDNode* root;
    const std::vector<Vertex>* vertices;
    std::vector<Triangle> triangleStorage;

    /**
     * @brief Baut rekursiv den KD-Baum auf.
     *
     * Teilt die übergebenen Primitiven entlang einer Achse basierend auf deren Schwerpunkten.
     *
     * @param prims Die Liste der zu verteilenden KD-Primitiven (Dreiecke mit Referenz zu Vertices).
     * @param depth Die aktuelle Tiefe im Baum (zur Achsenauswahl und Abbruchbedingung).
     * @return Ein Zeiger auf den neu erstellten KDNode.
     */
    KDNode* build(std::vector<KDPrim>& prims, int depth);

    /**
     * @brief Rekursive Methode zur Intersektion eines Strahls mit dem KD-Baum.
     *
     * Wenn der aktuelle Knoten ein Blatt ist, werden alle enthaltenen Dreiecke getestet.
     * Ansonsten wird rekursiv in den linken und rechten Teilbaum gegangen.
     *
     * @param node Zeiger auf den aktuellen Knoten.
     * @param ray Der zu testende Ray.
     * @param hit Referenz auf ein Hitpoint-Objekt, das ggf. aktualisiert wird.
     * @return true, wenn ein Schnittpunkt in diesem Knoten (oder seinen Kindern) gefunden wurde.
     */
    bool intersectNode(const KDNode* node, const Ray& ray, Hitpoint& hit) const;
public:
    /**
     * @brief Destruktor für den KDTree.
     *
     * Gibt den Speicher des Wurzelknotens (und damit rekursiv den gesamten Baum) frei.
     */
    ~KDTree();

    /**
     * @brief Konstruktor für den KDTree.
     *
     * Initialisiert die interne Datenstruktur und beginnt mit dem Aufbau des Baums aus den gegebenen Dreiecken.
     *
     * @param triangles Liste der Dreiecke, die in den KD-Tree aufgenommen werden sollen.
     * @param verts Liste aller Vertices, auf die sich die Dreiecke beziehen.
     */
    KDTree(const std::vector<Triangle>& triangles, const std::vector<Vertex>& vertices);

    /**
     * @brief Testet, ob ein Ray ein beliebiges Dreieck im KDTree trifft.
     *
     * Diese Methode ruft intern die rekursive Intersektion des Baumes auf.
     *
     * @param ray Der Strahl, der getestet wird.
     * @param hit Referenz auf ein Hitpoint-Objekt, das bei Erfolg gefüllt wird.
     * @return true, wenn ein Schnittpunkt gefunden wurde, sonst false.
     */
    bool intersect(const Ray& ray, Hitpoint& hit) const;
};

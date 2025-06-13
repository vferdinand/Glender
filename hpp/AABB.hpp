#pragma once
#include "Structs.hpp"
#include "Ray.hpp"
#include <algorithm>
#include <cmath>
#include <limits>

struct AABB {
    Point3D min;
    Point3D max;

    /**
     * @class AABB
     * @brief Achsenparallele Bounding Box zur räumlichen Partitionierung.
     *
     * Wird verwendet, um Ray-Triangle-Intersektionen durch hierarchische Raumaufteilung effizienter zu machen.
     */

    /**
     * @brief Konstruktor: Erstellt eine leere AABB mit unendlichen Grenzen.
     *
     * Initialisiert das Minimum auf +∞ und das Maximum auf -∞, damit `expand()` diese beim ersten Aufruf korrekt einschränken kann.
     */
    AABB();

    /**
     * @brief Erweitert die Bounding Box so, dass sie alle übergebenen Punkte einschließt.
     *
     * @param indices Eine Liste von Indizes, die auf Vertizes in `vertices` zeigen.
     * @param vertices Die vollständige Liste aller Vertices im Raum.
     */
    void expand(const std::vector<unsigned int>& indices, const std::vector<Vertex>& vertices);
    
    /**
     * @brief Prüft, ob ein Strahl (Ray) die Bounding Box schneidet.
     *
     * Verwendet das sogenannte "Slab-Verfahren", um den Schnitt in allen drei Raumachsen zu testen.
     *
     * @param ray Der Ray, der auf die AABB getestet wird.
     * @return true, wenn der Ray die AABB schneidet, andernfalls false.
     */
    bool intersect(const Ray& ray) const;
};
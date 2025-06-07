#include "../hpp/KDTree.hpp"

/**
 * @brief Konstruktor für den KDTree.
 *
 * Initialisiert die interne Datenstruktur und beginnt mit dem Aufbau des Baums aus den gegebenen Dreiecken.
 *
 * @param triangles Liste der Dreiecke, die in den KD-Tree aufgenommen werden sollen.
 * @param verts Liste aller Vertices, auf die sich die Dreiecke beziehen.
 */
KDTree::KDTree(const std::vector<Triangle>& triangles, const std::vector<Vertex>& verts)
    : vertices(&verts), triangleStorage(triangles) {
    std::vector<KDPrim> prims;
    for (const Triangle& t : triangleStorage)
        prims.push_back({ &t, &verts });
    root = build(prims, 0);
}

/**
 * @brief Destruktor für den KDTree.
 *
 * Gibt den Speicher des Wurzelknotens (und damit rekursiv den gesamten Baum) frei.
 */
KDTree::~KDTree() {
    delete root;
}

/**
 * @brief Destruktor für einen KDNode.
 *
 * Löscht rekursiv alle Kindknoten.
 */
KDNode::~KDNode() {
    delete left;
    delete right;
}

/**
 * @brief Baut rekursiv den KD-Baum auf.
 *
 * Teilt die übergebenen Primitiven entlang einer Achse basierend auf deren Schwerpunkten.
 *
 * @param prims Die Liste der zu verteilenden KD-Primitiven (Dreiecke mit Referenz zu Vertices).
 * @param depth Die aktuelle Tiefe im Baum (zur Achsenauswahl und Abbruchbedingung).
 * @return Ein Zeiger auf den neu erstellten KDNode.
 */
KDNode* KDTree::build(std::vector<KDPrim>& prims, int depth) {
    KDNode* node = new KDNode();

    // Berechne Bounding Box für aktuellen Knoten
    for (const auto& p : prims)
        node->bbox.expand(p.tri->getIndices(), *vertices);

    // Abbruchkriterium: zu wenige Prims oder maximale Tiefe erreicht
    if (prims.size() <= 2 || depth > 20) {
        for (const auto& p : prims)
            node->tris.push_back(p.tri);
        return node;
    }

    // Achse entlang derer gesplittet wird: x=0, y=1, z=2 (zyklisch)
    int axis = depth % 3;

    // Sortiere Prims entlang der Split-Achse nach ihrem Schwerpunkt
    std::sort(prims.begin(), prims.end(), [axis](const KDPrim& a, const KDPrim& b) {
        return a.centroid()[axis] < b.centroid()[axis];
    });

    // Aufteilen der Prims in zwei Hälften
    size_t mid = prims.size() / 2;
    std::vector<KDPrim> left(prims.begin(), prims.begin() + mid);
    std::vector<KDPrim> right(prims.begin() + mid, prims.end());

    // Speichere Split-Informationen im Knoten
    node->axis = axis;
    node->splitPos = prims[mid].centroid()[axis];

     // Rekursiver Aufbau der Kindknoten
    node->left = build(left, depth + 1);
    node->right = build(right, depth + 1);

    return node;
}

/**
 * @brief Testet, ob ein Ray ein beliebiges Dreieck im KDTree trifft.
 *
 * Diese Methode ruft intern die rekursive Intersektion des Baumes auf.
 *
 * @param ray Der Strahl, der getestet wird.
 * @param hit Referenz auf ein Hitpoint-Objekt, das bei Erfolg gefüllt wird.
 * @return true, wenn ein Schnittpunkt gefunden wurde, sonst false.
 */
bool KDTree::intersect(const Ray& ray, Hitpoint& hit) const {
    return intersectNode(root, ray, hit);
}

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
bool KDTree::intersectNode(const KDNode* node, const Ray& ray, Hitpoint& hit) const {
    if (!node->bbox.intersect(ray)) {
        return false;
    }
    
    bool found = false;

    if (node->isLeaf()) {
        // Prüfe alle Dreiecke in einem Blattknoten
        for (const Triangle* tri : node->tris) {
            const auto& idx = tri->getIndices();    
            const Vertex& a = (*vertices)[idx[0]];
            const Vertex& b = (*vertices)[idx[1]];
            const Vertex& c = (*vertices)[idx[2]];
            
            Hitpoint tempHit;
            if (ray.rayTriangleIntersect(ray, a, b, c, tempHit)) {
                if (tempHit.getDistance() < hit.getDistance()) {
                    hit = tempHit;
                    hit.setTriangle(tri);
                    found = true;
                }
            }
        }
        return found;
    }   

    // Rekursiver Aufruf für linke und rechte Kindknoten
    bool leftHit = intersectNode(node->left, ray, hit);
    bool rightHit = intersectNode(node->right, ray, hit);
    return leftHit || rightHit;
}
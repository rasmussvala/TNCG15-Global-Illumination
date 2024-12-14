// C++ Program to Implement KD Tree: https://www.geeksforgeeks.org/kd-trees-in-cpp/
// Modified with glm::vec3 and range search
#include <iostream>
#include <cmath>
#include "../include/glm/glm.hpp"

// Class for KDTree with 3 dimensions
class KDTree
{
private:
    // Node structure representing each point in the KDTree
    struct Node
    {
        // Point in 3 dimensions
        glm::vec3 point;
        // Pointer to left child
        Node *left;
        // Pointer to right child
        Node *right;

        // Constructor to initialize a Node
        Node(const glm::vec3 &pt) : point(pt), left(nullptr), right(nullptr) {}
    };

    Node *root; // Root of the KDTree

    // Recursive function to insert a point into the KDTree
    Node *insertRecursive(Node *node, const glm::vec3 &point, int depth);

    // Recursive function to search for points in the KDTree within a given radius
    std::vector<glm::vec3> searchRecursive(Node *node, const glm::vec3 &point, float radius, int depth);

    // Recursive function to print the KDTree
    void printRecursive(Node *node, int depth) const;

public:
    // Constructor to initialize the KDTree with a null root
    KDTree() : root(nullptr) {}

    // Public function to insert a point into the KDTree
    void insert(const glm::vec3 &point);

    // Public function to search for a point in the KDTree
    std::vector<glm::vec3> search(const glm::vec3 &point, float radius);

    // Public function to print the KDTree
    void print() const;
};

// TODO: Balance tree

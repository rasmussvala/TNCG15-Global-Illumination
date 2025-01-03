// C++ Program to Implement KD Tree: https://www.geeksforgeeks.org/kd-trees-in-cpp/
// Modified with glm::vec3 and range search
#pragma once

#include <iostream>
#include <cmath>
#include "../include/glm/glm.hpp"
#include "../include/Photon.h"

// Class for KDTree with 3 dimensions
class KDTree
{
private:
    // Node structure representing each point in the KDTree
    struct Node
    {
        // Point in 3 dimensions
        Photon photon;
        // Pointer to left child
        Node *left;
        // Pointer to right child
        Node *right;

        // Constructor to initialize a Node
        Node(const Photon &p) : photon(p), left(nullptr), right(nullptr) {}
    };

    Node *root; // Root of the KDTree

    // Recursive function to insert a point into the KDTree
    Node *insertRecursive(std::vector<Photon> &photons, int start, int end, int depth);

    // Recursive function to search for points in the KDTree within a given radius
    std::vector<Photon> searchRecursive(Node *node, const glm::vec3 &point, float radius, int depth);

    // Recursive function to print the KDTree
    void printRecursive(Node *node, int depth) const;

public:
    // Constructor to initialize the KDTree with a null root
    KDTree() : root(nullptr) {}

    // Public function to insert a point into the KDTree
    void insert(const std::vector<Photon> &photons);

    // Public function to search for photons in the KDTree
    std::vector<Photon> search(const glm::vec3 &point, float radius);

    // Public function to print the KDTree
    void print() const;
};

// TODO: Balance tree

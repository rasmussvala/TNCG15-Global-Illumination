// C++ Program to Implement KD Tree: https://www.geeksforgeeks.org/kd-trees-in-cpp/
// Modified to glm::vec3
#include <iostream>
#include <array>
#include <cmath>
#include "../include/glm/glm.hpp"
using namespace std;

// Template class for KDTree with 3 dimensions
size_t K = 3;
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
    Node *insertRecursive(Node *node, const glm::vec3 &point, int depth)
    {
        // Base case: If node is null, create a new node
        if (node == nullptr)
            return new Node(point);

        // Calculate current dimension (cd)
        int cd = depth % K;

        // Compare point with current node and decide to go left or right
        if (point[cd] < node->point[cd])
            node->left = insertRecursive(node->left, point, depth + 1);
        else
            node->right = insertRecursive(node->right, point, depth + 1);

        return node;
    }

    // Recursive function to search for a point in the KDTree
    bool searchRecursive(Node *node, const glm::vec3 &point, float radius, int depth) const
    {
        // Base case: If node is null, the point is not found
        if (node == nullptr)
            return false;

        // If the current node is within range, return true
        if (glm::distance(node->point, point) <= radius)
            return true;

        // Calculate current dimension (cd)
        int cd = depth % K;

        // Compare point with current node and decide to go left or right
        if (point[cd] < node->point[cd])
            return searchRecursive(node->left, point, radius, depth + 1);
        else
            return searchRecursive(node->right, point, radius, depth + 1);
    }

    // Recursive function to print the KDTree
    void printRecursive(Node *node, int depth) const
    {
        // Base case: If node is null, return
        if (node == nullptr)
            return;

        // Print current node with indentation based on depth
        for (int i = 0; i < depth; i++)
            cout << "  ";
        cout << "(";
        for (size_t i = 0; i < K; i++)
        {
            cout << node->point[i];
            if (i < K - 1)
                cout << ", ";
        }
        cout << ")" << endl;

        // Recursively print left and right children
        printRecursive(node->left, depth + 1);
        printRecursive(node->right, depth + 1);
    }

public:
    // Constructor to initialize the KDTree with a null root
    KDTree() : root(nullptr) {}

    // Public function to insert a point into the KDTree
    void insert(const glm::vec3 &point)
    {
        root = insertRecursive(root, point, 0);
    }

    // Public function to search for a point in the KDTree
    bool search(const glm::vec3 &point, float radius) const
    {
        return searchRecursive(root, point, radius, 0);
    }

    // Public function to print the KDTree
    void print() const
    {
        printRecursive(root, 0);
    }
};

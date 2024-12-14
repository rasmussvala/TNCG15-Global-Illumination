// C++ Program to Implement KD Tree: https://www.geeksforgeeks.org/kd-trees-in-cpp/
// Modified with glm::vec3 and range search
#include <iostream>
#include <cmath>
#include "../include/glm/glm.hpp"

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

    // Recursive function to search for points in the KDTree within a given radius
    std::vector<glm::vec3> searchRecursive(Node *node, const glm::vec3 &point, float radius, int depth)
    {
        // Base case: If node is null, return empty vector
        if (node == nullptr)
            return std::vector<glm::vec3>();

        std::vector<glm::vec3> results;

        // Check if current node's point is within the radius
        if (glm::distance(node->point, point) <= radius)
            results.push_back(node->point);

        // Calculate current dimension (cd)
        int cd = depth % K;

        // Decide which subtree to explore first based on the current dimension
        bool goLeft = point[cd] < node->point[cd];
        Node *firstSubtree = goLeft ? node->left : node->right;
        Node *secondSubtree = goLeft ? node->right : node->left;

        // First, recursively search the closer subtree
        std::vector<glm::vec3> firstResults = searchRecursive(firstSubtree, point, radius, depth + 1);
        results.insert(results.end(), firstResults.begin(), firstResults.end());

        // Check if we need to search the other subtree
        // This happens when the splitting plane is closer than the radius
        float planeDist = std::abs(point[cd] - node->point[cd]);
        if (planeDist <= radius)
        {
            std::vector<glm::vec3> secondResults = searchRecursive(secondSubtree, point, radius, depth + 1);
            results.insert(results.end(), secondResults.begin(), secondResults.end());
        }

        return results;
    }
    // Recursive function to print the KDTree
    void printRecursive(Node *node, int depth) const
    {
        // Base case: If node is null, return
        if (node == nullptr)
            return;

        // Print current node with indentation based on depth
        for (int i = 0; i < depth; i++)
            std::cout << "  ";
        std::cout << "(";
        for (size_t i = 0; i < K; i++)
        {
            std::cout << node->point[i];
            if (i < K - 1)
                std::cout << ", ";
        }
        std::cout << ")" << std::endl;

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
    std::vector<glm::vec3> search(const glm::vec3 &point, float radius)
    {
        return searchRecursive(root, point, radius, 0);
    }

    // Public function to print the KDTree
    void print() const
    {
        printRecursive(root, 0);
    }
};

// TODO: Balance tree

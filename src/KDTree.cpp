#include "../include/KDTree.h"

KDTree::Node *KDTree::insertRecursive(Node *node, const glm::vec3 &point, int depth)
{
    // Base case: If node is null, create a new node
    if (node == nullptr)
        return new Node(point);

    // Calculate current dimension (cd)
    int cd = depth % 3;

    // Compare point with current node and decide to go left or right
    if (point[cd] < node->point[cd])
        node->left = insertRecursive(node->left, point, depth + 1);
    else
        node->right = insertRecursive(node->right, point, depth + 1);

    return node;
}

std::vector<glm::vec3> KDTree::searchRecursive(Node *node, const glm::vec3 &point, float radius, int depth)
{
    // Base case: If node is null, return empty vector
    if (node == nullptr)
        return std::vector<glm::vec3>();

    std::vector<glm::vec3> results;

    // Check if current node's point is within the radius
    if (glm::distance(node->point, point) <= radius)
        results.push_back(node->point);

    // Calculate current dimension (cd)
    int cd = depth % 3;

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

void KDTree::printRecursive(Node *node, int depth) const
{
    // Base case: If node is null, return
    if (node == nullptr)
        return;

    // Print current node with indentation based on depth
    for (int i = 0; i < depth; i++)
        std::cout << "  ";
    std::cout << "(";
    for (size_t i = 0; i < 3; i++)
    {
        std::cout << node->point[i];
        if (i < 3 - 1)
            std::cout << ", ";
    }
    std::cout << ")" << std::endl;

    // Recursively print left and right children
    printRecursive(node->left, depth + 1);
    printRecursive(node->right, depth + 1);
}

void KDTree::insert(const glm::vec3 &point)
{
    root = insertRecursive(root, point, 0);
}

std::vector<glm::vec3> KDTree::search(const glm::vec3 &point, float radius)
{
    return searchRecursive(root, point, radius, 0);
}

void KDTree::print() const
{
    printRecursive(root, 0);
}
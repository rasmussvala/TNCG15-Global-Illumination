#include "../include/KDTree.h"

KDTree::Node *KDTree::insertRecursive(std::vector<Photon> &photons, int start, int end, int depth)
{
    if (start > end)
        return nullptr;

    // Calculate current dimension (cd)
    int cd = depth % 3;

    // Sort points by the current dimension
    std::sort(photons.begin() + start, photons.begin() + end + 1, [cd](const Photon &a, const Photon &b)
              { return a.position[cd] < b.position[cd]; });

    // Find the median index
    int mid = start + (end - start) / 2;

    // Create a node with the median point
    Node *node = new Node(photons[mid]);

    // Recursively build the left and right subtrees
    node->left = insertRecursive(photons, start, mid - 1, depth + 1);
    node->right = insertRecursive(photons, mid + 1, end, depth + 1);

    return node;
}

std::vector<Photon> KDTree::searchRecursive(Node *node, const glm::vec3 &point, float radius, int depth)
{
    // Base case: If node is null, return empty vector
    if (node == nullptr)
        return std::vector<Photon>();

    std::vector<Photon> results;

    // Check if current node's point is within the radius
    if (glm::distance(node->photon.position, point) <= radius)
        results.push_back(node->photon);

    // Calculate current dimension (cd)
    int cd = depth % 3;

    // Decide which subtree to explore first based on the current dimension
    bool goLeft = point[cd] < node->photon.position[cd];
    Node *firstSubtree = goLeft ? node->left : node->right;
    Node *secondSubtree = goLeft ? node->right : node->left;

    // First, recursively search the closer subtree
    std::vector<Photon> firstResults = searchRecursive(firstSubtree, point, radius, depth + 1);
    results.insert(results.end(), firstResults.begin(), firstResults.end());

    // Check if we need to search the other subtree
    // This happens when the splitting plane is closer than the radius
    float planeDist = std::abs(point[cd] - node->photon.position[cd]);
    if (planeDist <= radius)
    {
        std::vector<Photon> secondResults = searchRecursive(secondSubtree, point, radius, depth + 1);
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
        std::cout << node->photon.position[i];
        if (i < 3 - 1)
            std::cout << ", ";
    }
    std::cout << ")" << std::endl;

    // Recursively print left and right children
    printRecursive(node->left, depth + 1);
    printRecursive(node->right, depth + 1);
}

void KDTree::insert(const std::vector<Photon> &photons)
{
    std::vector<Photon> photonsCopy = photons;
    root = insertRecursive(photonsCopy, 0, photonsCopy.size() - 1, 0);
}

std::vector<Photon> KDTree::search(const glm::vec3 &point, float radius)
{
    return searchRecursive(root, point, radius, 0);
}

void KDTree::print() const
{
    printRecursive(root, 0);
}
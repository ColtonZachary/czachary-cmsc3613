#include "LazyBinarySearchTree.h"
#include <algorithm>

LazyBinarySearchTree::LazyBinarySearchTree() {
    root = nullptr;
}

LazyBinarySearchTree::~LazyBinarySearchTree() {
    destroy(root);
    root = nullptr;
}

void LazyBinarySearchTree::destroy(TreeNode* n) {
    if (n == nullptr) return;
    destroy(n->left);
    destroy(n->right);
    delete n;
}

TreeNode* LazyBinarySearchTree::search(TreeNode* n, int key) const {
    if (n == nullptr) return nullptr;
    if (key < n->key) return search(n->left, key);
    if (key > n->key) return search(n->right, key);
    return n;
}

bool LazyBinarySearchTree::insertHelper(TreeNode*& n, int key) {
    if (n == nullptr) {
        n = new TreeNode(key);
        return true;
    }

    if (key < n->key) return insertHelper(n->left, key);
    if (key > n->key) return insertHelper(n->right, key);

    if (n->deleted) {
        n->deleted = false; 
        return true;        
    }
    return false;           
}

bool LazyBinarySearchTree::insert(int key) {
    return insertHelper(root, key);
}

bool LazyBinarySearchTree::remove(int key) {
    TreeNode* n = search(root, key);
    if (n == nullptr) return false;
    if (n->deleted) return false;
    n->deleted = true;
    return true;
}

bool LazyBinarySearchTree::contains(int key) const {
    TreeNode* n = search(root, key);
    return (n != nullptr && n->deleted == false);
}

int LazyBinarySearchTree::findMinHelper(TreeNode* n) const {
    if (n == nullptr) return -1;

    int leftMin = findMinHelper(n->left);
    if (leftMin != -1) return leftMin;

    if (!n->deleted) return n->key;

    return findMinHelper(n->right);
}

int LazyBinarySearchTree::findMin() const {
    return findMinHelper(root);
}

int LazyBinarySearchTree::findMaxHelper(TreeNode* n) const {
    if (n == nullptr) return -1;

    int rightMax = findMaxHelper(n->right);
    if (rightMax != -1) return rightMax;

    if (!n->deleted) return n->key;

    return findMaxHelper(n->left);
}

int LazyBinarySearchTree::findMax() const {
    return findMaxHelper(root);
}

int LazyBinarySearchTree::heightHelper(TreeNode* n) const {
    if (n == nullptr) return -1;
    return 1 + std::max(heightHelper(n->left), heightHelper(n->right));
}

int LazyBinarySearchTree::height() const {
    return heightHelper(root);
}

int LazyBinarySearchTree::sizeHelper(TreeNode* n) const {
    if (n == nullptr) return 0;
    return 1 + sizeHelper(n->left) + sizeHelper(n->right);
}

int LazyBinarySearchTree::size() const {
    return sizeHelper(root);
}

void LazyBinarySearchTree::printHelper(TreeNode* n, std::string& out) const {
    if (n == nullptr) return;

    if (!out.empty()) out += " ";

    if (n->deleted) out += "*";
    out += std::to_string(n->key);

    printHelper(n->left, out);
    printHelper(n->right, out);
}

std::string LazyBinarySearchTree::print() const {
    std::string out = "";
    printHelper(root, out);
    return out;
}
#ifndef LAZYBINARYSEARCHTREE_H
#define LAZYBINARYSEARCHTREE_H

#include <string>
#include "TreeNode.h"

class LazyBinarySearchTree {
private:
    TreeNode* root;

    void destroy(TreeNode* n);

    bool insertHelper(TreeNode*& n, int key);
    TreeNode* search(TreeNode* n, int key) const;

    int findMinHelper(TreeNode* n) const;
    int findMaxHelper(TreeNode* n) const;

    int heightHelper(TreeNode* n) const; 
    int sizeHelper(TreeNode* n) const;

    void printHelper(TreeNode* n, std::string& out) const;

public:
    LazyBinarySearchTree();
    ~LazyBinarySearchTree();

    bool insert(int key);
    bool remove(int key);
    bool contains(int key) const;

    int findMin() const;
    int findMax() const;

    int height() const;
    int size() const;

    std::string print() const; 
};

#endif
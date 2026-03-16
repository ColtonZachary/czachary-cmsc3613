#ifndef TREENODE_H
#define TREENODE_H

class TreeNode {
public:
    int key;
    bool deleted;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k) {
        key = k;
        deleted = false;
        left = nullptr;
        right = nullptr;
    }
};

#endif
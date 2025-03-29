#ifndef QUADTREE_H
#define QUADTREE_H

class Quadtree {
public:
    Quadtree(int size);
    void buildTree();
    void compress();
    void reconstruct();
private:
    struct Node { /* Define Node Structure */ };
    Node* root;
};

#endif

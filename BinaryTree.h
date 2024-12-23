#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>


template <typename T>
class BinaryTree
{
protected:
    int _depth;
    std::vector< std::vector<T> > _tree;
public:
    void setDepth(int);
    void setNode(int, int, T);
    T getNode(int, int) const;
    void display();
    BinaryTree();
    ~BinaryTree();
    std::string repeatString(int n);
    std::string lien(int n);
};

#include "BinaryTree.cpp"

#endif



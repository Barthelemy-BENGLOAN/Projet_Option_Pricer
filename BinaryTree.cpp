#include "BinaryTree.h"
#include <stdexcept>
#include <string>
#include<vector>


template <typename T>
void BinaryTree<T>::setDepth(int N) {
    if (N < 0) {
        throw std::invalid_argument("ERROR : Depht " + std::to_string(N) + " value is negative.");
    }
    _depth = N;
    _tree.resize(N + 1);
    for (int i = 0; i <= N; i++) {
        _tree[i].resize(i + 1);
    }
}


template <typename T>
void BinaryTree<T>::setNode(int step, int node, T value) {
    if (step < 0 || step > _depth) {
        throw std::out_of_range("Error : step " + std::to_string(step) + " out of range.");
    }
    if (node < 0 || node >= _tree[step].size()) {
        throw std::out_of_range("Erreur : node " + std::to_string(node) + " out of range.");
    }
    _tree[step][node] = value;
}


template <typename T>
T BinaryTree<T>::getNode(int step, int node) const {
    if (step < 0 || step > _depth) {
        throw std::out_of_range("Error : step " + std::to_string(step) + " out of range.");
    }
    if (node < 0 || node >= _tree[step].size()) {
        throw std::out_of_range("Erreur : node " + std::to_string(node) + " out of range.");
    }
    return _tree[step][node];
}

template <typename T>
BinaryTree<T>::BinaryTree() : _depth(0) {}





template<typename T>
void BinaryTree<T>::display() {
    for (int level = 0; level <= _depth; ++level) {
        for (int index = 0; index <= level; ++index) {
            std::cout << _tree[level][index] << " ";
        }
        std::cout << std::endl;
    }
    for (int level = 0; level <= _depth * 2; ++level) {
        int initial_space = 2 * _depth - level;
        if (level % 2 == 0) {
            std::cout << repeatString(2 * (initial_space)+1);
            for (int i = 0; i <= level / 2; ++i) {
                std::cout << _tree[level / 2][i] << repeatString(6);
            }
            std::cout << std::endl;
        }
        else {
            std::cout << repeatString(2 * initial_space + 1);
            std::cout << lien(level / 2) << std::endl;
        }
    }
};

template <typename T>
std::string BinaryTree<T>::repeatString(int n) {
    std::string space = "";
    for (int i = 0; i < n; i++) {
        space += " ";
    }
    return space;
}


template <typename T>
std::string BinaryTree<T>::lien(int n) {
    std::string retour = "/   \\";
    for (int i = 0; i < n; i++) {
        retour += "   /   \\";
    }
    return retour;
}
template <typename T>
BinaryTree<T>::~BinaryTree() {}

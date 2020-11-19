#ifndef ADS_LABA3_RNDTREE_H
#define ADS_LABA3_RNDTREE_H

#include "Tree.h"
#include <iostream>

using namespace std;

template<class Key = int, class Data = int>
class RNDTree : public Tree<Key, Data> {
private:
    int getCount(typename Tree<Key, Data>::Node *node);

    void fixCount(typename Tree<Key, Data>::Node *node);

    typename Tree<Key, Data>::Node *rotateRight(typename Tree<Key, Data>::Node *node);

    typename Tree<Key, Data>::Node *rotateLeft(typename Tree<Key, Data>::Node *node);

    typename Tree<Key, Data>::Node *join(typename Tree<Key, Data>::Node *node1, typename Tree<Key, Data>::Node *node2);

    typename Tree<Key, Data>::Node *insertRoot(typename Tree<Key, Data>::Node *node, Key key, Data data);

    typename Tree<Key, Data>::Node *addNode(typename Tree<Key, Data>::Node *node, Key key, Data data, bool &flag);

    typename Tree<Key, Data>::Node *removeNode(typename Tree<Key, Data>::Node *node, Key key, bool &flag);

public:

    ~RNDTree() = default;;

    bool addNode(Key key, Data data);

    bool removeNode(Key key);
};

template<class Key, class Data>
int RNDTree<Key, Data>::getCount(typename Tree<Key, Data>::Node *node) {
    if (!node) return 0;
    return node->count;
}

template<class Key, class Data>
void RNDTree<Key, Data>::fixCount(typename Tree<Key, Data>::Node *node) {
    if (node) node->count = getCount(node->right) + getCount(node->left) + 1;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *RNDTree<Key, Data>::rotateRight(typename Tree<Key, Data>::Node *node) {
    if (!node->left) return node;
    typename Tree<Key, Data>::Node *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    tmp->count = node->count;
    fixCount(node);
    fixCount(tmp);
    return tmp;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *RNDTree<Key, Data>::rotateLeft(typename Tree<Key, Data>::Node *node) {
    if (!node->right) return node;
    typename Tree<Key, Data>::Node *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    tmp->count = node->count;
    fixCount(node);
    fixCount(tmp);
    return tmp;
}


template<class Key, class Data>
typename Tree<Key, Data>::Node *
RNDTree<Key, Data>::join(typename Tree<Key, Data>::Node *node1, typename Tree<Key, Data>::Node *node2) {
    if (!node1) return node2;
    if (!node2) return node1;
    if (rand() / RAND_MAX / (node1->count + node2->count + 1) < node1->count) {
        node1->right = join(node1->right, node2);
        fixCount(node1);
        return node1;
    } else {
        node2->left = join(node1, node2->left);
        fixCount(node2);
        return node2;
    }
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *
RNDTree<Key, Data>::insertRoot(typename Tree<Key, Data>::Node *node, Key key, Data data) {
    if (!node) {
        node = new typename Tree<Key, Data>::Node(key, data);
        node->count++;
        return node;
    }
    if (key < node->getKey()) {
        node->left = insertRoot(node->left, key, data);
        return rotateRight(node);
    } else {
        node->right = insertRoot(node->right, key, data);
        return rotateLeft(node);
    }
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *
RNDTree<Key, Data>::addNode(typename Tree<Key, Data>::Node *node, Key key, Data data, bool &flag) {
    Tree<Key, Data>::count_view++;
    if (!Tree<Key, Data>::root) {
        node = new typename Tree<Key, Data>::Node(key, data);
        node->count++;
        Tree<Key, Data>::root = node;
        flag = true;
        return node;
    }
    if (!node) {
        node = new typename Tree<Key, Data>::Node(key, data);
        node->count++;
        flag = true;
        return node;
    }
    if (key == node->getKey()) {
        flag = false;
        Tree<Key, Data>::count_view--;
        return node;
    }
    if (rand() < RAND_MAX / (node->count + 1)) {
        node = insertRoot(node, key, data);
        flag = true;
        return node;
    }
    if (key < node->getKey()) {
        node->left = addNode(node->left, key, data, flag);
    } else {
        node->right = addNode(node->right, key, data, flag);
    }
    if (flag) {
        fixCount(node);
    }
    return node;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *
RNDTree<Key, Data>::removeNode(typename Tree<Key, Data>::Node *node, Key key, bool &flag) {
    Tree<Key, Data>::count_view++;
    if (!node) {
        flag = false;
        Tree<Key, Data>::count_view--;
        return node;
    }
    if (key < node->getKey()) {
        node->left = removeNode(node->left, key, flag);
    } else if (key > node->getKey()) {
        node->right = removeNode(node->right, key, flag);
    } else {
        typename Tree<Key, Data>::Node *tmp = join(node->left, node->right);
        delete node;
        flag = true;
        node = tmp;
    }
    if (flag) {
        fixCount(node);
    }
    return node;
}

template<class Key, class Data>
bool RNDTree<Key, Data>::addNode(Key key, Data data) {
    Tree<Key, Data>::count_view = 0;
    bool flag = false;
    typename Tree<Key, Data>::Node *tmp = nullptr;
    try {
        tmp = Tree<Key, Data>::getNode(Tree<Key, Data>::root, key);
    } catch (exception e) {}
    if (tmp) {
        return flag;
    }
    Tree<Key, Data>::count_view = 0;
    Tree<Key, Data>::root = addNode(Tree<Key, Data>::root, key, data, flag);
    if (flag) Tree<Key, Data>::size++;
    return flag;
}

template<class Key, class Data>
bool RNDTree<Key, Data>::removeNode(Key key) {
    Tree<Key, Data>::count_view = 0;
    bool flag = false;
    Tree<Key, Data>::root = removeNode(Tree<Key, Data>::root, key, flag);
    if (flag) {
        Tree<Key, Data>::size--;
    }
    return flag;
}


#endif //ADS_LABA3_RNDTREE_H

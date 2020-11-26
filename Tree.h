#ifndef ALGORITMLABA2_TREE_TREE_H
#define ALGORITMLABA2_TREE_TREE_H

#include <iostream>
#include <stack>

using namespace std;


template<class Key = int, class Data = int>
class Tree {  // Класс бинарного дерева
protected:
    class Node {
    protected:
        Key key;  // ключ
        Data data;  // данные

    public:
        Node *left;  // указатель на левый узел
        Node *right; // указатель на правый узел
        int count = 0;

        explicit Node(Key key, Data data = Data(), Node *left = nullptr, Node *right = nullptr); // конструктор

        Key getKey(); // геттер

        Data &getData(); // геттер

        void setKey(Key k);  // сеттер

        void setData(Data d); // сеттер

    }; // Класс узла

    int size;  // размер дерева
    int count_view;  // вспомогательная переменная

    virtual Node *addNode(Node *node, Key key, Data data, bool &flag);  // рекурсивная функция для добавления узла

    Node *getNode(Node *node, Key key);  // рекурсивная функция для получения данных узла

    virtual Node *removeNode(Node *node, Key key, bool &flag);  // рекурсивная функция удаления узла

    void clear(Node *node);  // рекурсивная функция очистки дерева

    void out(Node *node, int k);  // рекурсивная функция вывода дерева в консоль

    void printKeys(Node *node);  // рекурсивный обход по дереву

    Node *findMaxNode(Node *node);  // рекурсивный поиск максималльного ключа в дереве

    Node *findMinNode(Node *node);  // рекурсивный поиск минимального ключа в дереве

    Node *getIndexByKey(Node *node, Key key, int &index);  // рекурсивная функция подсчета порядкогово номера узла


public:
    Node *root;

    class Iterator {
    private:
        Tree *tree;
        Node *current;
        stack<Node *> stack;


    public:
        explicit Iterator(Tree<Key, Data> *tree);

        void toBegin();

        void toEnd();

        void checkException(bool flag = true);

        bool hasTree();

        bool hasNext();

        Data &operator*();

        void operator++();

        void operator++(int);

        void operator--();

        void operator--(int);

        bool operator==(Iterator right);

        bool operator!=(Iterator right);

    }; // класс итератора

    class Reverse_Iterator {
    private:
        Tree *tree;
        Node *current;
        stack<Node *> stack;

    public:
        explicit Reverse_Iterator(Tree<Key, Data> *tree);

        void toBegin();

        void toEnd();

        void checkException(bool flag = true);

        bool hasTree();

        bool hasNext();

        Data &operator*();

        void operator++();

        void operator++(int);

        void operator--();

        void operator--(int);

        bool operator==(Reverse_Iterator right);

        bool operator!=(Reverse_Iterator right);
    }; // класс обратного итератора

    Tree();  // конструктор

    Tree(Tree &Right);  // конструктор копирования

    virtual ~Tree();  // деструктор

    int getSize();  // получение количества элементов в дереве

    int getViewNode(); // получение количества просмотренных узлов

    void clear();  // очистка дерева

    bool isEmpty();  // проверка на наличие элементов в дереве

    Data &getData(Key key); // получение данных узла по ключу

    bool setNode(Key key, Data data);  // изменение данных узла по ключу

    virtual bool addNode(Key key, Data data);  // добавление данных по ключу

    virtual bool removeNode(Key key);  // удаление узла по ключу

    void printKeys();  // вывод дерева

    void printTree();  // обход дерева

    int getIndexByKey(Key key);  // подсчет порядкого номера элемента по ключу

    Tree::Iterator begin(); // установка итератора в начало

    Tree::Iterator end();  // установка итератора в конец

    Tree::Reverse_Iterator rbegin(); // установка обратного итератора в начало

    Tree::Reverse_Iterator rend(); // установка обратного итератера в конец

};


template<class Key, class Data>
Tree<Key, Data>::Reverse_Iterator::Reverse_Iterator(Tree<Key, Data> *tree) {
    this->tree = tree;
    this->current = this->tree->root;
}

template<class Key, class Data>
void Tree<Key, Data>::Reverse_Iterator::toBegin() {
    checkException();
    while (current->right != nullptr) {
        stack.push(current);
        current = current->right;
    }
}

template<class Key, class Data>
bool Tree<Key, Data>::Reverse_Iterator::hasTree() {
    return this->tree != nullptr;
}

template<class Key, class Data>
bool Tree<Key, Data>::Reverse_Iterator::hasNext() {
    return this->current != nullptr;
}

template<class Key, class Data>
void Tree<Key, Data>::Reverse_Iterator::checkException(bool flag) {
    if (!hasTree()) {
        throw runtime_error("EXCEPTION!");
    }
    if (!hasNext() && stack.empty()) {
        throw runtime_error("EXCEPTION!");
    }
    if (!hasNext() && flag) {
        throw runtime_error("EXCEPTION!");
    }

}

template<class Key, class Data>
void Tree<Key, Data>::Reverse_Iterator::toEnd() {
    checkException();
    while (current != nullptr) {
        stack.push(current);
        current = current->left;
    }
}

template<class Key, class Data>
Data &Tree<Key, Data>::Reverse_Iterator::operator*() {
    checkException();
    return current->getData();
}

template<class Key, class Data>
void Tree<Key, Data>::Reverse_Iterator::operator++() {
    checkException();
    if (current->left != nullptr) {
        current = current->left;
        while (current->right != nullptr) {
            stack.push(current);
            current = current->right;
        }
    } else {
        if (stack.empty()) {
            throw runtime_error("EXCEPTION");
        }
        current = stack.top();
        stack.pop();
    }
}

template<class Key, class Data>
void Tree<Key, Data>::Reverse_Iterator::operator++(int) {
    checkException();
    if (current->left != nullptr) {
        current = current->left;
        while (current->right != nullptr) {
            stack.push(current);
            current = current->right;
        }
    } else {
        if (stack.empty()) {
            throw runtime_error("EXCEPTION");
        }
        current = stack.top();
        stack.pop();
    }
}

template<class Key, class Data>
void Tree<Key, Data>::Reverse_Iterator::operator--() {
    checkException(false);
    if (!current && !stack.empty()) {
        current = stack.top();
        stack.pop();
        return;
    }
    if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) {
            stack.push(current);
            current = current->left;
        }
    } else {
        if (stack.empty() || current == stack.top()->right) {
            throw runtime_error("EXCEPTION");
        }
        current = stack.top();
        stack.pop();
    }
}

template<class Key, class Data>
void Tree<Key, Data>::Reverse_Iterator::operator--(int) {
    checkException(false);
    if (!current && !stack.empty()) {
        current = stack.top();
        stack.pop();
        return;
    }
    if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) {
            stack.push(current);
            current = current->left;
        }
    } else {
        if (stack.empty() || current == stack.top()->right) {
            throw runtime_error("EXCEPTION");
        }
        current = stack.top();
        stack.pop();
    }
}

template<class Key, class Data>
bool Tree<Key, Data>::Reverse_Iterator::operator==(Tree::Reverse_Iterator right) {
    checkException();
    return this->current == right.current;
}

template<class Key, class Data>
bool Tree<Key, Data>::Reverse_Iterator::operator!=(Tree::Reverse_Iterator right) {
    checkException();
    return this->current != right.current;
}


template<class Key, class Data>
Tree<Key, Data>::Iterator::Iterator(Tree<Key, Data> *tree) {
    this->tree = tree;
    this->current = this->tree->root;
}

template<class Key, class Data>
Data &Tree<Key, Data>::Iterator::operator*() {
    checkException();
    return current->getData();
}

template<class Key, class Data>
void Tree<Key, Data>::Iterator::operator++() {
    checkException();
    if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) {
            stack.push(current);
            current = current->left;
        }
    } else {
        current = stack.top();
        stack.pop();
    }
}

template<class Key, class Data>
void Tree<Key, Data>::Iterator::checkException(bool flag) {
    if (!hasTree()) {
        throw runtime_error("EXCEPTION!");
    }
    if (!hasNext() && stack.empty()) {
        throw runtime_error("EXCEPTION!");
    }
    if (!hasNext() && flag) {
        throw runtime_error("EXCEPTION!");
    }
}

template<class Key, class Data>
bool Tree<Key, Data>::Iterator::hasTree() {
    return this->tree != nullptr;
}

template<class Key, class Data>
bool Tree<Key, Data>::Iterator::hasNext() {
    return this->current != nullptr;
}

template<class Key, class Data>
void Tree<Key, Data>::Iterator::toBegin() {
    checkException();
    while (current->left != nullptr) {
        stack.push(current);
        current = current->left;
    }
}

template<class Key, class Data>
void Tree<Key, Data>::Iterator::toEnd() {
    checkException();
    while (current != nullptr) {
        stack.push(current);
        current = current->right;
    }
}

template<class Key, class Data>
void Tree<Key, Data>::Iterator::operator++(int) {
    checkException();
    if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) {
            stack.push(current);
            current = current->left;
        }
    } else {
        if (stack.empty()) {
            throw runtime_error("EXCEPTION");
        }
        current = stack.top();
        stack.pop();
    }
}

template<class Key, class Data>
void Tree<Key, Data>::Iterator::operator--() {
    checkException(false);
    if (!current && !stack.empty()) {
        current = stack.top();
        stack.pop();
        return;
    }
    if (current->left != nullptr) {
        current = current->left;
        while (current->right != nullptr) {
            stack.push(current);
            current = current->right;
        }
    } else {
        if (stack.empty() || current == stack.top()->left) {
            throw runtime_error("EXCEPTION");
        }
        current = stack.top();
        stack.pop();
    }
}

template<class Key, class Data>
void Tree<Key, Data>::Iterator::operator--(int) {
    checkException(false);
    if (!current && !stack.empty()) {
        current = stack.top();
        stack.pop();
        return;
    }
    if (current->left != nullptr) {
        current = current->left;
        while (current->right != nullptr) {
            stack.push(current);
            current = current->right;
        }
    } else {
        if (stack.empty() || current == stack.top()->left) {
            throw runtime_error("EXCEPTION");
        }
        current = stack.top();
        stack.pop();
    }
}

template<class Key, class Data>
bool Tree<Key, Data>::Iterator::operator==(Tree::Iterator right) {
    checkException();
    return this->current == right.current;
}

template<class Key, class Data>
bool Tree<Key, Data>::Iterator::operator!=(Tree::Iterator right) {
    checkException();
    return this->current != right.current;
}

template<class Key, class Data>
Tree<Key, Data>::Tree() {
    root = nullptr;
    size = 0;
    count_view = 0;
}

template<class Key, class Data>
Tree<Key, Data>::Tree(Tree &Right) {
    root = Right.root;
    size = Right.size;
    count_view = 0;
}

template<class Key, class Data>
Tree<Key, Data>::~Tree() {
    clear();
}

template<class Key, class Data>
int Tree<Key, Data>::getSize() {
    return size;
}

template<class Key, class Data>
bool Tree<Key, Data>::isEmpty() {
    return root == nullptr;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::getNode(Tree::Node *node, Key key) {
    count_view++;
    if (!node) {
        count_view--;
        return nullptr;
    }
    if (node->getKey() > key) {
        node = getNode(node->left, key);

    } else if (node->getKey() < key) {
        node = getNode(node->right, key);
    } else {
        return node;
    }
    return node;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::addNode(Tree::Node *node, Key key, Data data, bool &flag) {
    count_view++;
    if (root == nullptr) {
        Node *tmp = new Node(key, data);
        tmp->count++;
        size++;
        root = tmp;
        return tmp;
    }
    if (node == nullptr) {
        Node *tmp = new Node(key, data);
        tmp->count++;
        size++;
        return tmp;
    } else {
        if (key < node->getKey()) {
            node->left = addNode(node->left, key, data, flag);
            if (flag) node->count++;
            return node;
        } else if (key > node->getKey()) {
            node->right = addNode(node->right, key, data, flag);
            if (flag) node->count++;
            return node;
        } else {
            flag = false;
            count_view--;
            return node;
        }
    }
}

template<class Key, class Data>
void Tree<Key, Data>::clear(Node *node) {
    if (node) {
        if (node->left) clear(node->left);
        if (node->right) clear(node->right);
        delete node;
    }
}

template<class Key, class Data>
void Tree<Key, Data>::clear() {
    if (isEmpty()) return;
    clear(root);
    root = nullptr;
    size = 0;
}

template<class Key, class Data>
void Tree<Key, Data>::out(Tree::Node *node, int k) {
    if (node) {
        out(node->right, k + 1);
        for (int i = 0; i < k; i++) {
            cout << "       ";
        }
        cout << node->getKey() << " (" << node->count << ")" << endl;
        out(node->left, k + 1);
    } else {
        for (int i = 0; i < k; i++) {
            cout << "       ";
        }
        cout << '*' << endl;
    }
}

template<class Key, class Data>
void Tree<Key, Data>::printTree() {
    if (isEmpty()) return;
    out(root, 0);
}

template<class Key, class Data>
bool Tree<Key, Data>::addNode(Key key, Data data) {
    count_view = 0;
    bool flag = true;
    root = addNode(root, key, data, flag);
    if (flag) {
        size++;
    }
    return flag;
}

template<class Key, class Data>
void Tree<Key, Data>::printKeys() {
    if (isEmpty()) return;
    printKeys(root);
}

template<class Key, class Data>
void Tree<Key, Data>::printKeys(Node *node) {
    if (node) {
        cout << node->getKey() << " ";
        if (node->left) printKeys(node->left);
        if (node->right) printKeys(node->right);
    }
}

template<class Key, class Data>
bool Tree<Key, Data>::setNode(Key key, Data data) {
    Node *tmp = getNode(root, key);
    if (tmp) {
        tmp->setData(data);
        return true;
    } else
        return false;
}

template<class Key, class Data>
Data &Tree<Key, Data>::getData(Key key) {
    count_view = 0;
    Node *tmp = getNode(root, key);
    if (tmp) {
        return tmp->getData();
    } else
        throw runtime_error("EXCEPTION!");
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::findMaxNode(Node *node) {
    if (node == nullptr) {
        exit(3);
    }
    if (node->right) {
        count_view++;
        return findMaxNode(node->right);
    }
    return node;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::findMinNode(Tree::Node *node) {
    if (node == nullptr) {
        exit(4);
    }
    if (node->left) {
        return findMinNode(node->left);
    }
    return node;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::removeNode(Tree::Node *node, Key key, bool &flag) {
    count_view++;
    if (node == nullptr) {
        flag = true;
        count_view--;
        return nullptr;
    }
    if (node->getKey() > key) {
        node->left = removeNode(node->left, key, flag);
        if (!flag) {
            node->count--;
        }
        return node;
    } else if (node->getKey() < key) {
        node->right = removeNode(node->right, key, flag);
        if (!flag) {
            node->count--;
        }
        return node;
    } else if (node->getKey() == key) {
        if (node->left && node->right) {
            Node *locMax = findMaxNode(node->left);
            node->setKey(locMax->getKey());
            node->setData(locMax->getData());
            node->count--;
            node->left = removeNode(node->left, locMax->getKey(), flag);
            return node;
        } else if (node->left) {
            Node *tmp = node->left;
            delete node;
            return tmp;
        } else if (node->right) {
            Node *tmp = node->right;
            delete node;
            return tmp;
        } else {
            delete node;
            return nullptr;
        }
    }
}

template<class Key, class Data>
bool Tree<Key, Data>::removeNode(Key key) {
    count_view = 0;
    bool flag = false;
    root = removeNode(root, key, flag);
    if (!flag) {
        size--;
    }
    return !flag;
}

template<class Key, class Data>
int Tree<Key, Data>::getIndexByKey(Key key) {
    count_view = 0;
    int index = 0;
    return getIndexByKey(root, key, index) != nullptr ? index : -1;
}

template<class Key, class Data>
int Tree<Key, Data>::getViewNode() {
    return count_view;
}

template<class Key, class Data>
typename Tree<Key, Data>::Node *Tree<Key, Data>::getIndexByKey(Tree::Node *node, Key key, int &index) {
    if (!node) {
        return nullptr;
    }
    if (node->getKey() == key) {
        if (node->left) {
            node = node->left;
            index += node->count;
        }
        return node;
    } else if (node->getKey() > key) {
        node = getIndexByKey(node->left, key, index);
        return node;
    } else if (node->getKey() < key) {
        if (node->left) {
            Node *tmp;
            tmp = node->left;
            index += tmp->count;
        }
        node = getIndexByKey(node->right, key, index);
        index++;
        return node;
    }
}

template<class Key, class Data>
typename Tree<Key, Data>::Iterator Tree<Key, Data>::begin() {
    Tree<Key, Data>::Iterator iterator(this);
    iterator.toBegin();
    return iterator;
}

template<class Key, class Data>
typename Tree<Key, Data>::Iterator Tree<Key, Data>::end() {
    Tree<Key, Data>::Iterator iterator(this);
    iterator.toEnd();
    return iterator;
}

template<class Key, class Data>
typename Tree<Key, Data>::Reverse_Iterator Tree<Key, Data>::rbegin() {
    Tree<Key, Data>::Reverse_Iterator iterator(this);
    iterator.toEnd();
    return iterator;
}

template<class Key, class Data>
typename Tree<Key, Data>::Reverse_Iterator Tree<Key, Data>::rend() {
    Tree<Key, Data>::Reverse_Iterator iterator(this);
    iterator.toBegin();
    return iterator;
}

template<class Key, class Data>
Tree<Key, Data>::Node::Node(Key key, Data data, Tree::Node *left, Tree::Node *right) {
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
}

template<class Key, class Data>
Key Tree<Key, Data>::Node::getKey() {
    return this->key;
}

template<class Key, class Data>
Data &Tree<Key, Data>::Node::getData() {
    return this->data;
}

template<class Key, class Data>
void Tree<Key, Data>::Node::setKey(Key k) {
    this->key = k;
}

template<class Key, class Data>
void Tree<Key, Data>::Node::setData(Data d) {
    this->data = d;
}

#endif //ALGORITMLABA2_TREE_TREE_H

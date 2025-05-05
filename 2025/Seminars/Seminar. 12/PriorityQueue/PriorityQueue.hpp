#include "Queue.hpp"
#include <iostream>
#include <algorithm>
#pragma once

template<class T, class P = int>

class PriorityQueue 
{
private:

    struct Node 
    {

        P key;
        Queue<T> q;

        int height = 1;
        Node* left = nullptr;
        Node* right = nullptr;
       
        explicit Node(const T& element, const P& priority);
       
    };

    Node* root = nullptr;
    size_t totalSize = 0;   

    int height(Node* node) const;

    int balanceFactor(Node* node) const;

    void updateHeight(Node* node);

    Node* rotateRight(Node* y);

    Node* rotateLeft(Node* x);

    Node* balance(Node* node);

    Node* insert(Node* node, const P& key, const T& element);

    Node* findMax(Node* node) const;

    Node* remove(Node* node, const P& key);

    Node* cloneNode(Node* node);

    void clear(Node* node);

    void free();

    void copyFrom(const PriorityQueue& other);

    void moveTo(PriorityQueue&& other);

public:

    PriorityQueue();

    PriorityQueue(const PriorityQueue& other);

    PriorityQueue(PriorityQueue&& other) noexcept;

    PriorityQueue& operator = (const PriorityQueue& other);

    PriorityQueue& operator = (PriorityQueue&& other) noexcept;

    ~PriorityQueue();

    void push(const T& element, const P& priority);

    void pop();

    const T& top() const;

    bool empty() const;

    size_t size() const;

};

template<class T, class P>

PriorityQueue<T, P>::PriorityQueue(): 
    root(nullptr), totalSize(0) {}

template<class T, class P>

PriorityQueue<T, P>::~PriorityQueue() 
{

    clear(root);

}

template<class T, class P>

PriorityQueue<T, P>::Node::Node(const T& element, const P& priority): 
    key(priority)
{

    q.push(element);

}

template<class T, class P>

int PriorityQueue<T, P>::height(Node* node) const 
{

    return node ? node->height : 0;

}

template<class T, class P>

int PriorityQueue<T, P>::balanceFactor(Node* node) const 
{

    return node ? height(node->left) - height(node->right) : 0;

}

template<class T, class P>

void PriorityQueue<T, P>::updateHeight(Node* node) 
{

    node->height = 1 + std::max(height(node->left), height(node->right));

}

template<class T, class P>

typename PriorityQueue<T, P>::Node* PriorityQueue<T, P>::rotateRight(Node* y) 
{

    Node* x = y->left;
    y->left = x->right;
    x->right = y;

    updateHeight(y);
    updateHeight(x);

    return x;

}

template<class T, class P>

typename PriorityQueue<T, P>::Node* PriorityQueue<T, P>::rotateLeft(Node* x)
{

    Node* y = x->right;
    x->right = y->left;
    y->left = x;

    updateHeight(x);
    updateHeight(y);

    return y;

}

template<class T, class P>

typename PriorityQueue<T, P>::Node* PriorityQueue<T, P>::balance(Node* node)
{

    updateHeight(node);
    int bf = balanceFactor(node);

    if (bf > 1)
    {

        if (balanceFactor(node->left) < 0) node->left = rotateLeft(node->left);
        return rotateRight(node);

    }
    if (bf < -1) 
    {

        if (balanceFactor(node->right) > 0) node->right = rotateRight(node->right);
        return rotateLeft(node);

    }

    return node;

}

template<class T, class P>

typename PriorityQueue<T, P>::Node* PriorityQueue<T, P>::insert(Node* node, const P& key, const T& element)
{

    if (!node)
    {

        totalSize += 1;
        return new Node(element, key);

    }

    if (key < node->key) node->left = insert(node->left, key, element);    
    else if (key > node->key) node->right = insert(node->right, key, element);
    else 
    {

        node->q.push(element);
        totalSize += 1;

        return node;

    }

    return balance(node);

}

template<class T, class P>

typename PriorityQueue<T, P>::Node* PriorityQueue<T, P>::findMax(Node* node) const
{

    while (node->right) node = node->right;
    return node;

}

template<class T, class P>

typename PriorityQueue<T, P>::Node* PriorityQueue<T, P>::remove(Node* node, const P& key)
{

    if (!node) return nullptr;

    if (key < node->key) node->left = remove(node->left, key);
    else if (key > node->key) node->right = remove(node->right, key);
    else 
    {

        if (!node->left || !node->right) 
        {

            Node* temp = node->left ? node->left : node->right;
            delete node;

            return temp;

        }
        else 
        {

            Node* pred = findMax(node->left);
            node->key = pred->key;
            node->q = std::move(pred->q);
            node->left = remove(node->left, pred->key);

        }

    }

    return balance(node);

}

template<class T, class P>

void PriorityQueue<T, P>::clear(Node* node) 
{
    if (!node) return;

    clear(node->left);
    clear(node->right);
    delete node;

}

template<class T, class P>

void PriorityQueue<T, P>::push(const T& element, const P& priority) 
{

    root = insert(root, priority, element);

}

template<class T, class P>

void PriorityQueue<T, P>::pop() 
{

    if (empty()) throw std::runtime_error("pop from empty PriorityQueue");

    Node* maxNode = findMax(root);
    maxNode->q.pop();

    totalSize -= 1;
    if (maxNode->q.empty()) root = remove(root, maxNode->key);

}

template<class T, class P>

const T& PriorityQueue<T, P>::top() const 
{

    if (empty()) throw std::runtime_error("top from empty PriorityQueue");
    return findMax(root)->q.front();

}

template<class T, class P>

bool PriorityQueue<T, P>::empty() const 
{

    return totalSize == 0;

}

template<class T, class P>

size_t PriorityQueue<T, P>::size() const 
{

    return totalSize;

}

template<class T, class P>

typename PriorityQueue<T, P>::Node* PriorityQueue<T, P>::cloneNode(Node* node)
{

    if (!node) return nullptr;

    Node* newNode = new Node(node->q.front(), node->key);
    newNode->q = node->q;        
    newNode->height = node->height;

    newNode->left = cloneNode(node->left);
    newNode->right = cloneNode(node->right);

    return newNode;

}

template<class T, class P>

void PriorityQueue<T, P>::free() 
{

    clear(root);
    root = nullptr;
    totalSize = 0;

}

template<class T, class P>

void PriorityQueue<T, P>::copyFrom(const PriorityQueue& other) 
{

    free();
    root = cloneNode(other.root);
    totalSize = other.totalSize;

}

template<class T, class P>

void PriorityQueue<T, P>::moveTo(PriorityQueue&& other)  
{

    free();

    root = other.root;
    totalSize = other.totalSize;
    other.root = nullptr;
    other.totalSize = 0;

}

template<class T, class P>

PriorityQueue<T, P>::PriorityQueue(const PriorityQueue& other) 
{

    copyFrom(other);

}

template<class T, class P>

PriorityQueue<T, P>::PriorityQueue(PriorityQueue&& other) noexcept 
{

    moveTo(std::move(other));

}

template<class T, class P>

PriorityQueue<T, P>& PriorityQueue<T, P>::operator = (const PriorityQueue& other)
{

    if (this != &other) 
    {

        free();
        copyFrom(other);

    }

    return *this;

}

template<class T, class P>

PriorityQueue<T, P>& PriorityQueue<T, P>::operator = (PriorityQueue&& other) noexcept 
{

    if (this != &other) 
    {

        free();
        moveTo(std::move(other));

    }

    return *this;

}

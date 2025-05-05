#include "Queue.hpp"
#include <iostream>
#include <algorithm>
#pragma once

template<typename T, typename P = int>

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

    void updateHeight(Node* node) ;

    Node* rotateRight(Node* y);

    Node* rotateLeft(Node* x);

    Node* balance(Node* node);

    Node* insert(Node* node, const P& key, const T& element);

    Node* findMax(Node* node) const;

    Node* remove(Node* node, const P& key);

    void clear(Node* node);

public:

    PriorityQueue() = default;

    ~PriorityQueue();

    void push(const T& element, const P& priority);

    T pop();

    const T& top() const;

    bool empty() const;

    size_t size() const;

};

template<typename T, typename P>

PriorityQueue<T, P>::PriorityQueue(): 
    root(nullptr), totalSize(0) {}

template<typename T, typename P>

PriorityQueue<T, P>::~PriorityQueue() 
{

    clear(root);

}

template<typename T, typename P>

PriorityQueue<T, P>::Node::Node(const T& element, const P& priority): 
    key(priority)
{

    q.push(element);

}

template<typename T, typename P>

int PriorityQueue<T, P>::height(Node* node) const 
{

    return node ? node->height : 0;

}

template<typename T, typename P>

int PriorityQueue<T, P>::balanceFactor(Node* node) const 
{

    return node ? height(node->left) - height(node->right) : 0;

}

template<typename T, typename P>

void PriorityQueue<T, P>::updateHeight(Node* node) 
{

    node->height = 1 + std::max(height(node->left), height(node->right));

}

template<typename T, typename P>

typename PriorityQueue<T, P>::Node* PriorityQueue<T, P>::rotateRight(Node* y) 
{

    Node* x = y->left;
    y->left = x->right;
    x->right = y;

    updateHeight(y);
    updateHeight(x);

    return x;

}

template<typename T, typename P>

typename PriorityQueue<T, P>::Node* PriorityQueue<T, P>::rotateLeft(Node* x)
{

    Node* y = x->right;
    x->right = y->left;
    y->left = x;

    updateHeight(x);
    updateHeight(y);

    return y;

}

template<typename T, typename P>

PriorityQueue<T, P>::Node* PriorityQueue<T, P>::balance(Node* node) 
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

template<typename T, typename P>

PriorityQueue<T, P>::Node* PriorityQueue<T, P>::insert(Node* node, const P& key, const T& element) 
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

template<typename T, typename P>

PriorityQueue<T, P>::Node* PriorityQueue<T, P>::findMax(Node* node) const 
{

    while (node->right) node = node->right;
    return node;

}

template<typename T, typename P>

PriorityQueue<T, P>::Node* PriorityQueue<T, P>::remove(Node* node, const P& key) 
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

template<typename T, typename P>

void PriorityQueue<T, P>::clear(Node* node) 
{
    if (!node) return;

    clear(node->left);
    clear(node->right);
    delete node;

}

template<typename T, typename P>

void PriorityQueue<T, P>::push(const T& element, const P& priority) 
{

    root = insert(root, priority, element);

}

template<typename T, typename P>

T PriorityQueue<T, P>::pop() 
{

    if (empty()) throw std::runtime_error("pop from empty PriorityQueue");

    Node* maxNode = findMax(root);
    T value = maxNode->q.front();
    maxNode->q.pop();

    totalSize -= 1;
    if (maxNode->q.empty()) root = remove(root, maxNode->key);
        
    return value;

}

template<typename T, typename P>

const T& PriorityQueue<T, P>::top() const 
{

    if (empty()) throw std::runtime_error("top from empty PriorityQueue");
    return findMax(root)->q.front();

}

template<typename T, typename P>

bool PriorityQueue<T, P>::empty() const 
{

    return totalSize == 0;

}

template<typename T, typename P>

size_t PriorityQueue<T, P>::size() const 
{

    return totalSize;

}

#include <iostream>
#pragma once

template <class T>

class Queue
{
private:

	struct Node
	{
	public:

		T data;
		Node* next = nullptr;
		Node* prev = nullptr;

		explicit Node(const T& data);

		explicit Node(const T& data, Node* next, Node* prev);

	};

	Node* head = nullptr;
	Node* tail = nullptr;
	size_t countOfNodes = 0;

	void free();

	void copyFrom(const Queue& other);

	void moveTo(Queue&& other);

public:

	Queue();

	Queue(const Queue& other);

	Queue(Queue&& other) noexcept;

	Queue& operator = (const Queue& other);

	Queue& operator = (Queue&& other) noexcept;

	~Queue();

	const T& front() const;

	void pop();

	void push(const T& element);

	bool empty() const;

	size_t size() const;

};

template<class T>

Queue<T>::Node::Node(const T& data) :
	data(data), next(nullptr), prev(nullptr) {}

template<class T>

Queue<T>::Node::Node(const T& data, Node* next, Node* prev) :
	data(data), next(next), prev(prev) {}

template <class T>

void Queue<T>::free()
{

	Node* current = head;

	while (current != nullptr)
	{

		Node* nextNode = current->next;
		delete current;
		current = nextNode;

	}

	head = nullptr;
	tail = nullptr;
	countOfNodes = 0;

}

template <class T>

void Queue<T>::copyFrom(const Queue<T>& other)
{

	free();

	Node* prev = nullptr;
	Node* current = other.head;

	head = nullptr;
	tail = nullptr;

	while (current != nullptr)
	{

		Node* newNode = new Node(current->data);
		newNode->prev = prev;
		newNode->next = nullptr;

		if (prev) prev->next = newNode;
		else head = newNode;

		prev = newNode;
		current = current->next;

	}

	tail = prev;
	countOfNodes = other.countOfNodes;

}

template <class T>

void Queue<T>::moveTo(Queue<T>&& other)
{

	this->head = other.head;
	this->tail = other.tail;
	this->countOfNodes = other.countOfNodes;

	other.head = nullptr;
	other.tail = nullptr;
	other.countOfNodes = 0;

}

template <class T>

Queue<T>::Queue()
{

	this->head = nullptr;
	this->tail = nullptr;
	this->countOfNodes = 0;

}

template <class T>

Queue<T>::Queue(const Queue<T>& other)
{

	copyFrom(other);

}

template <class T>

Queue<T>::Queue(Queue&& other) noexcept
{

	moveTo(std::move(other));

}

template <class T>

Queue<T>& Queue<T>::operator = (const Queue<T>& other)
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

template <class T>

Queue<T>& Queue<T>::operator = (Queue<T>&& other) noexcept
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

template <class T>

Queue<T>::~Queue()
{

	free();

}

template <class T>

const T& Queue<T>::front() const
{

	if (empty()) throw std::runtime_error("Queue is empty");
	return head->data;

}

template <class T>

void Queue<T>::pop()
{

	if (empty()) throw std::runtime_error("Queue is empty");

	Node* iter = head;
	head = head->next;

	if (head == nullptr) tail = nullptr;
	else head->prev = nullptr;

	delete iter;
	countOfNodes -= 1;

}

template <class T>

void Queue<T>::push(const T& element)
{

	Node* newNode = new Node(element, nullptr, tail);

	if (tail == nullptr) head = newNode;
	else tail->next = newNode;

	tail = newNode;
	countOfNodes += 1;

}

template <class T>

bool Queue<T>::empty() const
{

	return countOfNodes == 0;

}

template <class T>

size_t Queue<T>::size() const
{

	return countOfNodes;

}

#pragma once

#include "DuoNode.h"
#include "QueueADT.h"

template<class T>
class DuoQueue : public QueueADT<T>
{
private:
	DuoNode<T>* frontPtr;
	DuoNode<T>* backPtr;
public:
	DuoQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	bool dequeueback(T& bckEntry);
	bool peekback(T& bckEntry);
	~DuoQueue();
};

template<class T>
DuoQueue<T>::DuoQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
}

template<class T>
bool DuoQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

template<class T>
bool DuoQueue<T>::enqueue(const T& newEntry)
{
	DuoNode<T>* newNodePtr = new DuoNode<T>(newEntry);
	// Insert the new node
	if (isEmpty())
	{
		//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
		frontPtr->setPrev(nullptr);
	}
	else
	{
		backPtr->setNext(newNodePtr); // The queue was not empty
		newNodePtr->setPrev(backPtr);
	}
	backPtr = newNodePtr; // New node is the last node now
	return true;
}

template<class T>
bool DuoQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	if(frontPtr)
		frontPtr->setPrev(nullptr);
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;
}

template<class T>
bool DuoQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;
}

template<class T>
bool DuoQueue<T>::dequeueback(T& bckEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = backPtr;
	bckEntry = backPtr->getItem();
	backPtr = backPtr->getPrev();
	if (backPtr)
		backPtr->setNext(nullptr);
	// Queue is not empty; remove front
	if (nodeToDeletePtr == frontPtr)	 // Special case: last node in the queue
		frontPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;
}

template<class T>
inline bool DuoQueue<T>::peekback(T& bckEntry)
{
	if (isEmpty())
		return false;

	bckEntry = backPtr->getItem();
	return true;
}

template<class T>
DuoQueue<T>::~DuoQueue()
{
	//Note that the cout statements here is just for learning purpose
	//They should be normally removed from the destructor
	cout << "\nStarting DoubleQueue destructor...";
	cout << "\nFreeing all nodes in the queue...";

	//Free all nodes in the queue
	T temp;
	while (dequeue(temp));

	cout << "\n Is DoubleQueue Empty now?? ==> " << boolalpha << isEmpty();
	cout << "\nEnding DoubleQueue destructor..." << endl;
}

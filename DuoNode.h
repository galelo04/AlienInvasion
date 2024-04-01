#pragma once

#include "Node.h"
template <class T>
class DuoNode : public Node<T>
{
private:
	DuoNode<T>* prev;

public:
	DuoNode();
	DuoNode(const T& r_Item);
	DuoNode(const T& r_Item, DuoNode<T>* nextNodePtr , DuoNode<T>* prevNodePtr);
	void setPrev(DuoNode<T>* nextNodePtr);
	DuoNode<T>* getPrev() const;
};

template<class T>
DuoNode<T>::DuoNode() :prev(nullptr)
{
}

template<class T>
DuoNode<T>::DuoNode(const T& r_Item) :Node<T>(r_Item)
{
}

template<class T>
DuoNode<T>::DuoNode(const T& r_Item, DuoNode<T>* nextNodePtr, DuoNode<T>* prevNodePtr) :Node<T>(r_Item,nextNodePtr) , prev(nullptr)
{
}

template<class T>
void DuoNode<T>::setPrev(DuoNode<T>* nextNodePtr)
{
	prev = nextNodePtr;
}

template<class T>
DuoNode<T>* DuoNode<T>::getPrev() const
{
	return prev;
}

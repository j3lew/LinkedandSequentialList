#include "DoublyLinkedList.hpp"
#include <iostream>
#include <cstddef>
using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
	value = data; 
	prev = NULL;
	next = NULL;
	
}

DoublyLinkedList::DoublyLinkedList()
{
	size_ = 0;
	head_ = NULL;
	tail_ = NULL;
}

DoublyLinkedList::~DoublyLinkedList()
{
	if( size_ != 0 )
	{
		// make a visitor (pointer) that equals the head -> next and using a loop, delete the node before,
		// until the list reaches the end
		Node*visitor = head_ -> next;
		while( visitor != NULL )
		{
			delete( visitor -> prev );
			visitor = visitor -> next;
		}
		// since the loop ends at the tail, it does not delete the tail
		// therefore, this is a special case that is being accounted for
		delete(tail_);
	}
}

bool DoublyLinkedList::empty() const
{
	if( size_ == 0 )
	{
		return true;
	}
	
	else 
	{
		return false;
	}
}

unsigned int DoublyLinkedList::size() const
{
	return size_;
}

void DoublyLinkedList::print() const
{
	Node*visitor = head_;
	while( visitor != NULL )
	{
		cout << visitor -> value << endl;
		visitor = visitor -> next;
	}
}

bool DoublyLinkedList::insert_front(DataType value)
{	
	Node*nNode = new Node(value);
	if( full() )
	{
		return false;
	}
	else if( empty() )
	{
		head_ = nNode;
		tail_ = nNode;
		size_++;
	}
	else
	{
		nNode -> next = head_; 
		head_ -> prev = nNode;
		head_ = nNode;
		head_ -> prev = NULL;
		size_++;
	}
	return true;
}

bool DoublyLinkedList::remove_front()
{
	Node*visitor;
	// list is empty: nothing to remove
	if( empty() )
	{
		return false; 
	}
	// one element in the list
	else if( size_ == 1 )
	{
		delete( head_ );
		tail_ = NULL;
		head_ = NULL;
		size_--;
	}
	// multiple elements in the list	
	else
	{
		visitor = head_;
		head_ = head_ -> next;
		delete ( visitor );
		head_ -> prev = NULL;
		size_--;
	}
	return true;
}

bool DoublyLinkedList::insert_back(DataType value)
{
	Node*nNode = new Node( value );
	// list is empty
	if( full() )
	{
		return false;
	}
	else if( empty() )
	{
		tail_ = nNode;
		head_ = nNode;
		size_++;
	}
	// multiple elements in the list
	else
	{
		tail_ -> next = nNode;
		nNode -> prev = tail_;
		tail_ = nNode;
		tail_ -> next = NULL;
		size_++;
	}
	return true;
}

bool DoublyLinkedList::remove_back()
{
	// list is empty: nothing to remove
	if( empty() )
	{
		return false;
	}
	// one element in the list
	else if( size_ == 1 )
	{
		delete( head_ );
		head_ = NULL;
		tail_ = NULL;
		size_--;
	}
	else
	{
		tail_ = tail_ -> prev;
		delete tail_ -> next;
		tail_ -> next = NULL;
		size_--;
	}
	return true;
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
	Node*nNode;
	nNode = new Node( value );
	if( index > size_ || full() )
	{
		return false;
	}
	else if( index == 0 || empty() )  
	{
		return insert_front( value );
	}
	else if( index == size_ )
	{
		return insert_back( value );
	}
	else
	{
		Node*visitor = getNode( index-1 );
		Node*visitor1 = getNode( index );
		visitor -> next = nNode;
		nNode -> prev = visitor;
		nNode -> next = visitor1;
		visitor1 -> prev = nNode;	
		size_++;	
		return true;
	}
}

bool DoublyLinkedList::remove(unsigned int index)
{
	if( empty() || size_ - 1 < index )
	{
		return false;
	}
	else if( size_ == 1 || index == 0 )
	{
		return remove_front();
	}
	else if( index == size_-1 )
	{
		return remove_back();
	}
	else
	{
		Node*visitor = getNode( index-1 );
		Node*visitorX = getNode( index+1 );
		Node*visitorY = getNode( index );
		visitor -> next = visitorX;
		visitorX -> prev = visitor; 
		delete ( visitorY );
		size_--;
		return true;
	}
}

unsigned int DoublyLinkedList::search(DataType value) const
{
	Node*find = head_;
	int index = 0;
	while( find != NULL )
	{
		if( find -> value == value )
		{
			return index;
		}
		else 
		{
			index++;
			find = find -> next;
		}
	}
	return size_;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
	Node*visitor = getNode( index );
	if( size_ <= index)
	{
		return tail_ -> value;
	}
	else
	{
		return visitor -> value;
	}
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{	
	Node*nNode = new Node( value );
	if( index >= size_ )
	{
		return false;
	}
	else if( index == 0 )
	{
		head_ = head_ -> next;
		delete ( head_ -> prev );
		head_ -> prev = nNode;
		nNode -> next = head_;
		head_ = nNode;
		head_ -> prev = NULL;
	}
	else if( size_-1 == index )
	{
		tail_ = tail_ -> prev;
		delete ( tail_ -> next );
		tail_ -> next = nNode;
		nNode -> prev = tail_;
		tail_ = nNode;
		tail_ -> next = NULL;
	}
	else 
	{
		Node*visitor = getNode( index-1 );
		Node*visitorA = getNode( index+1 );
		Node*visitorB = getNode( index );
		visitor -> next = nNode;
		nNode -> prev = visitor;
		visitorA -> prev = nNode;
		nNode -> next = visitorA;
		delete visitorB;
	}
	return true;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
	Node*visitor = head_;
	if( empty() )
	{
		return NULL;
	}
	int count = 0;
	while( count != index && visitor -> next != NULL )
	{
		visitor = visitor -> next;
		count++; 
	}	
	return visitor;
}
bool DoublyLinkedList::full() const
{
	if( CAPACITY == size_ )
	{
		return true;
	}
	else
	{
		return false;
	}
}

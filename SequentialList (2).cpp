// .cpp files contain code definitions for methods that have been declared
// in the according .hpp file. The skeleton has been set up here for you.
// That is, the methods have been initiated, and your mission, should you 
// choose to accept it (which you should for marks), is to fill in each method
// with the appropriate code.
//
// A note about the "::" syntax: generally, this means "the thing on the right
// belongs to the thing on the left." So, SequentialList::empty() means the method
// empty() belongs to the class SequentialList. This allows empty() to access (and
// potentially change) the member variables in class SequentialList.

#include "SequentialList.hpp"
#include <iostream>
using namespace std;

// This is the constructor.
SequentialList::SequentialList(unsigned int cap)
{
	data_ = new DataType [cap];
	capacity_ = cap;
	size_ = 0;
}


SequentialList::~SequentialList()
{
	delete[] data_;
}

bool SequentialList::empty() const
{
	if (size_ == 0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

unsigned int SequentialList::size() const
{
	return size_;
}

unsigned int SequentialList::capacity() const
{
	return capacity_;
}

bool SequentialList::full() const
{
	if(size_ == capacity_)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SequentialList::print() const
{
	for( int i = 0; i < capacity_; i++ )
	{
		cout << data_[ i ] << endl;
	}
	
}

// NOTE on inserts: do NOT grow the array if we reach capacity. Simply return false.
bool SequentialList::insert_front(DataType val)
{
	// list is full, cannot add more
	if( full() )
	{
		return false;
	}
	// list is empty, first element equals the value
	else if( empty() )
	{
		data_[0] = val; 
		size_++;
	}
	// there are space in the list but not empty
	// move every element to the right of the list to make space 
	else
	{
		int tem_ = size_ - 1;
		while( 0 <= tem_ )
		{
			data_[ tem_ + 1 ] = data_[ tem_ ];
			tem_--;
		}
		data_[ 0 ] = val;
		size_++;
	}
	return true;
}

bool SequentialList::remove_front()
{
	// empty list, nothing to remove
	if( empty() )
	{
		return false;
	}
	// move all the element to the left, starting from index 0
	// make previous element equal to the next one
	else
	{
		int tem_ = 0;
		while( tem_ < size_ - 1 )
		{
			data_[ tem_ ] = data_[ tem_ + 1 ];
			tem_++;
		}
		size_--;
		return true;
	}
}

bool SequentialList::insert_back(DataType val)
{
	// list is full, no space
	if( full() )
	{
		return false;
	}
	else
	{
		data_[ size_ ] = val;
		size_++;
	}
	return true;
}

bool SequentialList::remove_back()
{
	// check if the list is empty (nothing to remove)
	if( empty() ) 
	{
		return false;
	}
	// decrement the size of the list to remove the last element
	else
	{
		size_--;
		return true;
	}
}

bool SequentialList::insert(DataType val, unsigned int index)
{
	if( full() || index > size_)
	{
		return false;
	}
	else
	{
		int i;
		for( i = size_; i > index; i-- )
		{
			data_[ i ] = data_[ i - 1 ];
		}
		data_[ index ] = val;
		size_++;
		return true;
	}
}

bool SequentialList::remove(unsigned int index)
{
	if( empty() || index > size_ - 1 )
	{
		return false;
	}
	else
	{
		for( int i = index + 1; i < size_; i++ )
		{
			data_[i-1] = data_[i];	
		}
		size_--;
		return true;
	}
}

unsigned int SequentialList::search(DataType val) const
{
	// comparing every index in the list with the value given, if the value is found, return the index
	int i;
	for( i = 0; i < size_; i++ )
	{
		if( data_[ i ] == val ) 
		{
			return i;
		}
	}
	return size_;
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
	if( index > size_ - 1 )
	{
		return data_[ size_ - 1 ];
	}
	else
	{
		return data_[ index ];
	}
}

bool SequentialList::replace(unsigned int index, DataType val)
{
	if( index > size_ - 1 )
	{
		return false;
	}
	else 
	{
		data_[ index ] = val;
		return true;
	}
}

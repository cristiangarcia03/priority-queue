#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP
#include <vector>
#include<iostream>
#include "runtimeexcept.hpp"
using namespace std;
class PriorityQueueEmptyException : public RuntimeException 
{
public:
	PriorityQueueEmptyException(const std::string & err) : RuntimeException(err) {}
};




template<typename Object>
class MyPriorityQueue
{
private:
    vector<Object> q;
    int amount;


public:

	// You also need a constructor and a destructor.
	MyPriorityQueue();
	~MyPriorityQueue();

 	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	void insert(const Object & elem);
	// Note:  no non-const version of this one.  This is on purpose because
	// the interior contents should not be able to be modified due to the
	// heap property.  This isn't true of all priority queues but 
	// for this project, we will do this.
	// min and extractMin should throw PriorityQueueEmptyException if the q is empty.
	const Object & min() const;
	void extractMin(); 

};


template<typename Object>
MyPriorityQueue<Object>::MyPriorityQueue()
{
   amount = 0;
}


template<typename Object>
MyPriorityQueue<Object>::~MyPriorityQueue()
{
    // automatically de-allocate
}

template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
	return amount;
}



template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
	if (amount == 0) {
        return true;
    }
    return false;
}



template<typename Object>
void MyPriorityQueue<Object>::insert(const Object & elem) 
{
	q.push_back(elem); 
    amount += 1;
    int index = amount - 1;

    while (index > 0) {

        int parent = (index - 1) / 2;
        if (q[parent] < q[index]) {
            break;
        }

        Object hold = q[index];
        q[index] = q[parent];
        q[parent] = hold;
        index = parent;
    }
}


template<typename Object>
const Object & MyPriorityQueue<Object>::min() const
{
    if (amount == 0){
        throw PriorityQueueEmptyException("min heap is empty") ;
    }
	return q[0];
}


template<typename Object>
void MyPriorityQueue<Object>::extractMin() 
{
    if (amount == 0){
        throw PriorityQueueEmptyException("heap is empty") ;
    }
    
    q[0] = q.back();
    q.pop_back(); 
    amount -= 1;

    int idx = 0;
    int child = 2 * idx + 1; // L 
    Object parent = q[idx]; 

    while (child < amount) {

        Object min_value = parent;
        int min_index = -1; // temp
        for (int i = 0; i < 2 && i + child < amount; i++) {
            if (q[i + child] < min_value) { 
                min_value = q[i + child];
                min_index = i + child;
            }
        }
        if (min_value == parent || min_index == -1) {  
            return;
        }
    
        Object hold = q[idx];
        q[idx] = q[min_index];
        q[min_index] = hold;

        idx = min_index;
        child = 2 * idx + 1;

    }
}


#endif

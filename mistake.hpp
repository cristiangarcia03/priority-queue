#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP

#include "runtimeexcept.hpp"

#include <iostream>

class PriorityQueueEmptyException : public RuntimeException 
{
public:
	PriorityQueueEmptyException(const std::string & err) : RuntimeException(err) {}
};

template<typename Object>
class Node {
    public:
    Object value;
    Node<Object>* left;
    Node<Object>* right;
    Node<Object>* parent;

    Node(){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    Node(Object v) {
        value = v;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

};



template<typename Object>
class MyPriorityQueue
{
private:

    int queue_size;


public:

    Node<Object>* head;
	MyPriorityQueue();
	//~MyPriorityQueue();

 	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	void insert(const Object & elem);


	// Note:  no non-const version of this one.  This is on purpose because
	// the interior contents should not be able to be modified due to the
	// heap property.  This isn't true of all priority queues but 
	// for this project, we will do this.
	// min and extractMin should throw PriorityQueueEmptyException if the queue is empty.
	const Object & min() const; 

	void extractMin(); 

    Node<Object>* insertHelper(Node<Object>* copy, Object v);
    int minHeight(Node<Object>* copy);
    int maxHeight(Node<Object>* copy);

    void printBT1(const std::string& prefix, const Node<Object>* node, bool isLeft);
    void printBT(Node<Object>* node);

    void swap(Node<Object>* parent, Node<Object>* child);

    void remove(Node<Object>* copy);
    void fixerUpper(Node<Object>* copy);

};


template<typename Object>
MyPriorityQueue<Object>::MyPriorityQueue()
{

    queue_size = 0;
    head = new Node<Object>();

}

// template<typename Key, typename Value>
// void LevelBalancedTree<Key,Value>::recursiveDelete(Node<Key, Value>* n) {
// 	if (n != nullptr) {
// 		recursiveDelete(n->left);
// 		recursiveDelete(n->right);
// 		delete n;
// 	}
// }

/*
template<typename Object>
MyPriorityQueue<Object>::~MyPriorityQueue()
{
	// recursiveDelete(head);
} */

template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
	return queue_size;
}

template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
	if (queue_size == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename Object>
const Object & MyPriorityQueue<Object>::min() const
{
	return head->value;
}

template<typename Object>
int MyPriorityQueue<Object>::maxHeight(Node<Object>* copy) {
    Node<Object>* temp = copy;
    int res = 0;
    while (temp != nullptr) {
        temp = temp->left;
        res += 1;
    }
    return res;
}

template<typename Object>
int MyPriorityQueue<Object>::minHeight(Node<Object>* copy) {

    Node<Object>* temp = copy;
    int res = 0;
    while (temp != nullptr) {
        temp = temp->right;
        res += 1;
    }
    return res;
}

template<typename Object>
void MyPriorityQueue<Object>::swap(Node<Object>* parent, Node<Object>* child) {

    child->parent = parent->parent;
    if (parent == this->head) {
        this->head = child;
    } else if (child->parent != nullptr) {
        if (child->parent->left == parent) {
            child->parent->left = child;
        } else {
            child->parent->right = child;
        }
    }
    parent->parent = child;

    if (parent->left == child) { // CHILD IS LEFT CHILD
        if (parent->right != nullptr) {
            parent->right->parent = child;
        }
        Node<Object>* child_Left = child->left;
        Node<Object>* child_Right = child->right;
        child->left = parent;
        child->right = parent->right;
        parent->left = child_Left;
        parent->right = child_Right;
        if (child_Left != nullptr) {
            child_Left->parent = parent;
        }
        if (child_Right != nullptr) {
            child_Right->parent = parent;
        }
        // std::cout << std::endl << "SWAP : " << parent->value << " - " << child->value << std::endl;
        // printBT(head);
    } else {     // CHILD IS RIGHT CHILD
        if (parent->left != nullptr) {
            parent->left->parent = child;
        }
        Node<Object>* child_Left = child->left;
        Node<Object>* child_Right = child->right;
        child->right = parent;
        child->left = parent->left;
        parent->left = child_Left;
        parent->right = child_Right;
        if (child_Left != nullptr) {
            child_Left->parent = parent;
        }
        if (child_Right != nullptr) {
            child_Right->parent = parent;
        }
        // std::cout << std::endl << "SWAP : " << parent->value << " - " << child->value << std::endl;
        // printBT(head);
    }
}


template<typename Object>
Node<Object>* MyPriorityQueue<Object>::insertHelper(Node<Object>* copy, Object v) {

    if (copy->left == nullptr) {
        //std::cout<<"left" << std::endl;
        Node<Object>* new_node = new Node<Object>(v);
        new_node->parent = copy;
        copy->left = new_node;
        //std::cout << copy->value << " under " << v << std::endl;
        return new_node;
    } else if (copy->right == nullptr) {
        //std::cout<<"right" << std::endl;
        Node<Object>* new_node = new Node<Object>(v);
        new_node->parent = copy;
        copy->right = new_node;
        //std::cout << copy->value << " under " << v << std::endl;
        return new_node;
    } else {
        if ((maxHeight(copy->left) == minHeight(copy->left) && maxHeight(copy->left) == minHeight(copy->right)) || (maxHeight(copy->left) != minHeight(copy->left))) {
            //std::cout<<"left " << maxHeight(copy->left) << " " <<  minHeight(copy->left) << " " << minHeight(copy->right) << " " <<copy->value << std::endl;
            return insertHelper(copy->left, v);
        } else {
            //std::cout<<"right" << std::endl;
            return insertHelper(copy->right, v);
        }
    }
    return copy;
}

template<typename Object>
void MyPriorityQueue<Object>::insert(const Object & elem) 
{
    //std::cout<<"CURRENTLY: " << elem << std::endl;
    queue_size += 1;
	if (head->value == false) {
        head->value = elem;
        return;
    }

    Node<Object>* copy = head;
    copy = insertHelper(copy, elem);

    while (copy->parent != nullptr) {
        if (copy->value < copy->parent->value) {
            swap(copy->parent, copy);
        } else {
            break;
        }
    }

    if (queue_size == 15) {
        std::cout<<std::endl<<std::endl;
        printBT(head);
    }
}

template<typename Object>
void MyPriorityQueue<Object>::remove(Node<Object>* copy){
    if (copy->left == nullptr && copy->right == nullptr) {
        if (copy->parent->left == copy) {
            copy->parent->left = nullptr;
        } else {
            copy->parent->right = nullptr;
        }
        //copy->parent = nullptr;
        head->value = copy->value;
        delete copy;
        return;
    }
    if (maxHeight(copy->right) == maxHeight(copy->left)) {
        remove(copy->right);
    } else {
        remove(copy->left);
    }
}

template<typename Object>
void MyPriorityQueue<Object>::swap2pointO(Node<Object>* copy) {

}


template<typename Object>
void MyPriorityQueue<Object>::extractMin() 
{
    if (this->isEmpty() == true) {
        throw PriorityQueueEmptyException("Queue is empty");
    }
    Node<Object>* copy = head;
    remove(copy);

    while (copy->left )

    std::cout << std::endl << std::endl;
    printBT(head);
}










template<typename Object>
void MyPriorityQueue<Object>::printBT1(const std::string& prefix, const Node<Object>* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        //if (node->value != head->value) {
        //    std::cout << node->parent->value << ": " << node->value << std::endl;
        //} else {
        std::cout << node->value << std::endl;
        //}

        // enter the next tree level - left and right branch
        printBT1( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT1( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

template<typename Object>
void MyPriorityQueue<Object>::printBT(Node<Object>* node)
{
    printBT1("", node, false);

}

#endif 

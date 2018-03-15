//
//  LinkedSet.hpp
//  Huffman
//
//  Created by Eric on 2018/3/7.
//  Copyright © 2018 Eric. All rights reserved.
//
#pragma once
#ifndef LinkedSet_hpp
#define LinkedSet_hpp

#include "LinkedQueue.hpp"


template <typename T>
class LinkedSet : public LinkedQueue<T> {

public:
	LinkedSet<T> & push(const T & t);
};

template<typename T>
LinkedSet<T> & LinkedSet<T>::push(const T & t) {
	Node<T> * temp = this->front;
	while (temp) {
		if (t == temp->data)
			return *this;
		temp = temp->link;
	}
	this->LinkedQueue<T>::push(t);
	return *this;
}




#endif /* LinkedSet_hpp */

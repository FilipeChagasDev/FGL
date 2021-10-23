/*
 * list.hpp
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#ifndef BASE_LIST_HPP_
#define BASE_LIST_HPP_

#include <stdint.h>

template <typename T>
struct ListNode
{
	T data;
	ListNode *prev;
	ListNode *next;
};

template <typename T>
class Iterator
{
protected:
	ListNode<T> *node;

public:
	Iterator(ListNode<T> *node); //tested
	T getData(); //tested
	void setData(T data); 
	bool foward(); //tested
	bool back(); //tested
	bool isBegin(); //tested
	bool isEnd();
	bool isNull(); //tested
	ListNode<T> *getNode(); //tested
	virtual ~Iterator();
};

template <typename T>
class List
{
protected:
	ListNode<T> *begin;
	ListNode<T> *end;
	uint32_t counter;

public:
	List();
	void pushBegin(T data); //tested
	void pushEnd(T data);  //tested
	void pushBefore(T data, Iterator<T> iterator); //tested
	void pushAfter(T data, Iterator<T> iterator); //tested
	bool popBegin(); //tested
	bool popEnd(); //tested
	void clear(); //tested
	T getBegin(); //tested
	T getEnd(); //tested
	uint32_t getLen(); //tested
	Iterator<T> getIteratorBegin(); //tested
	Iterator<T> getIteratorEnd(); //tested
	bool removeItemAndGoFoward(Iterator<T> &iterator); //tested
	bool removeItemAndGoBack(Iterator<T> &iterator); //tested

	virtual ~List();
};

//#include "list.cpp"

#endif /* BASE_LIST_HPP_ */

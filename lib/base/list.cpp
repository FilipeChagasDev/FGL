/*
 * list.cpp
 *
 *  Created on: 22 de out de 2021
 *      Author: Filipe Chagas
 */

#if 0

#include "list.hpp"
#include <assert.h>

/*  ------------------------------------
 *	Iterator code
 *	------------------------------------
 */

template <typename T>
Iterator<T>::Iterator(ListNode<T> *node)
{
    this->node = node;
}

template <typename T>
Iterator<T>::~Iterator()
{
    //TODO
}

template <typename T>
T Iterator<T>::getData()
{
    assert(this->node != nullptr);
    return this->node->data;
}

template <typename T>
void Iterator<T>::setData(T data)
{
    assert(this->node != nullptr);
    this->node->data = data;
}

template <typename T>
bool Iterator<T>::foward()
{
    assert(this->node != nullptr);

    this->node = this->node->next;

    return this->node != nullptr;
}

template <typename T>
bool Iterator<T>::back()
{
    assert(this->node != nullptr);

    this->node = this->node->prev;

    return this->node != nullptr;
}

template <typename T>
bool Iterator<T>::isBegin()
{
    assert(this->node != nullptr);
    return this->node->prev == nullptr;
}

template <typename T>
bool Iterator<T>::isEnd()
{
    assert(this->node != nullptr);
    return this->node->next == nullptr;
}

template <typename T>
bool Iterator<T>::isNull()
{
    return this->node == nullptr;
}

template <typename T>
ListNode<T>* Iterator<T>::getNode()
{
    return this->node;
}

/*  ------------------------------------
 *	List code
 *	------------------------------------
 */

template <typename T>
List<T>::List()
{
    this->begin = nullptr;
    this->end = nullptr;
    this->counter = 0;
}

template <typename T>
List<T>::~List()
{
    this->clear();
}

template <typename T>
void List<T>::pushBegin(T data)
{
    ListNode<T> *node = new ListNode<T>;
    node->data = data;
    node->prev = nullptr;
    node->next = nullptr;

    if(this->begin == nullptr) //empty list
    {
        this->begin = node;
        this->end = node;
    }
    else
    {
        ListNode<T> *_begin = this->begin; //Get neighbor
        node->next = _begin; //Connect node to neighbor
        _begin->prev = node; //Connect neighbor to node
        this->begin = node; //Connect header
    }

    this->counter += 1;
}

template <typename T>
void List<T>::pushEnd(T data)
{
    ListNode<T> *node = new ListNode<T>;
    node->data = data;
    node->prev = nullptr;
    node->next = nullptr;

    if(this->end == nullptr) //empty list
    {
        this->begin = node;
        this->end = node;
    }
    else
    {
        ListNode<T> *_end = this->end; //Get neighbor
        node->prev = _end; //Connect node to neighbor
        _end->next = node; //Connect neighbor to node
        this->end = node; //Connect header
    }

    this->counter += 1;
}

template <typename T>
void List<T>::pushBefore(T data, Iterator<T> iterator)
{
    if(iterator.isBegin() == false)
    {
        ListNode<T> *node = new ListNode<T>;
        node->data = data;
        node->prev = nullptr;
        node->next = nullptr;

        //Get neighbors
        ListNode<T> *itn = iterator.getNode();
        ListNode<T> *_prev = itn->prev;

        //Connect node to neighbors
        node->prev = _prev;
        node->next = itn;

        //Connect neighbors to node
        itn->prev = node;
        _prev->next = node;

        this->counter += 1;
    }
    else
    {
        this->pushBegin(data);
    }
}

template <typename T>
void List<T>::pushAfter(T data, Iterator<T> iterator)
{
    if(iterator.isEnd() == false)
    {
        ListNode<T> *node = new ListNode<T>;
        node->data = data;
        node->prev = nullptr;
        node->next = nullptr;

        //Get neighbors
        ListNode<T> *itn = iterator.getNode();
        ListNode<T> *_next = itn->next;

        //Connect node to neighbors
        node->next = _next;
        node->prev = itn;

        //Connect neighbors to node
        itn->next = node;
        _next->prev = node;

        this->counter += 1;
    }
    else
    {
        this->pushEnd(data);
    }
}

template <typename T>
bool List<T>::popBegin()
{
    if(this->begin == nullptr) //Empty list
    {
        return false;
    }
    else if(this->begin == this->end)  //Only one node in list
    {
        delete this->begin;
        this->begin = nullptr;
        this->end = nullptr;
        this->counter -= 1;
        return true;
    }
    else
    {
        ListNode<T> *x = this->begin; //Get node
        this->begin = x->next; //Connect header to neighbor
        this->begin->prev = nullptr; //Set begin point
        delete x; //Delete node
        this->counter -= 1;
        return true;
    }
}

template <typename T>
bool List<T>::popEnd()
{
    if(this->begin == nullptr) //Empty list
    {
        return false;
    }
    else if(this->begin == this->end)  //Only one node in list
    {
        delete this->begin;
        this->begin = nullptr;
        this->end = nullptr;
        this->counter -= 1;
        return true;
    }
    else
    {
        ListNode<T> *x = this->end; //Get node
        this->end = x->prev; //Connect header to neighbor
        this->end->next = nullptr; //Set end point
        delete x; //Delete node
        this->counter -= 1;
        return true;
    }
}

template <typename T>
void List<T>::clear()
{
    while (this->begin != nullptr)
    {
        this->popEnd();
    }
}

template <typename T>
T List<T>::getBegin()
{
    return this->begin->data;
}

template <typename T>
T List<T>::getEnd()
{
    return this->end->data;
}

template <typename T>
uint32_t List<T>::getLen()
{
    return this->counter;
}

template <typename T>
Iterator<T> List<T>::getIteratorBegin()
{
    return Iterator<T>(this->begin);
}

template <typename T>
Iterator<T> List<T>::getIteratorEnd()
{
    return Iterator<T>(this->end);
}

template <typename T>
bool List<T>::removeItemAndGoFoward(Iterator<T> &iterator)
{
    assert(iterator.isNull() == false);

    ListNode<T>* node = iterator.getNode(); //get node
    bool b = iterator.foward();

    //get neighbors
    ListNode<T>* _prev = node->prev;
    ListNode<T>* _next = node->next;

    delete node;

    //connect neighbors and headers
    if(_prev != nullptr) _prev->next = _next;
    else
    {
        this->begin = _next;
        if(this->begin != nullptr) this->begin->prev = nullptr;
    }

    if(_next != nullptr) _next->prev = _prev;
    else
    {
        this->end = _prev;
        if(this->end != nullptr ) this->end->next = nullptr;
    }

    this->counter -= 1;

    return b;
}

template <typename T>
bool List<T>::removeItemAndGoBack(Iterator<T> &iterator)
{
    assert(iterator.isNull() == false);

    ListNode<T>* node = iterator.getNode(); //get node
    bool b = iterator.back();

    //get neighbors
    ListNode<T>* _prev = node->prev;
    ListNode<T>* _next = node->next;

    delete node;

    //connect neighbors and headers
    if(_prev != nullptr) _prev->next = _next;
    else
    {
        this->begin = _next;
        if(this->begin != nullptr) this->begin->prev = nullptr;
    }

    if(_next != nullptr) _next->prev = _prev;
    else
    {
        this->end = _prev;
        if(this->end != nullptr ) this->end->next = nullptr;
    }

    this->counter -= 1;

    return b;
}

template<typename T>
T *List<T>::getArray()
{
    assert(this->counter > 0);

    T *array = new T[this->counter];

    uint32_t i = 0;
    for(ListNode<T> *it = this->begin; it != nullptr; it = it->next)
    {
        array[i] = it->data;
        i += 1;
    }

    return array;
}

#endif

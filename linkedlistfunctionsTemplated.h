#ifndef LINKED_LIST_FUNCTIONS
#define LINKED_LIST_FUNCTIONS
#include <iostream>
#include <iomanip>
#include "assert.h"
#include "../node/node.h"
using namespace std;

// Linked List General Functions:
template <typename T>
void _print_list(node<T> *head);

// recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

// return ptr to key or NULL
template <typename T>
node<T> *_search_list(node<T> *head,
                      T key);

template <typename T>
node<T> *_insert_head(node<T> *&head,
                      T insert_this);

// insert after ptr: insert head if marker null
template <typename T>
node<T> *_insert_after(node<T> *&head,
                       node<T> *after_this,
                       T insert_this);

// insert before ptr: insert head if marker null
template <typename T>
node<T> *_insert_before(node<T> *&head,
                        node<T> *before_this,
                        T insert_this);

// ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *prev_to_this);

// delete, return item
template <typename T>
T _delete_node(node<T> *&head, node<T> *delete_this);

// duplicate the list...
template <typename T>
node<T> *_copy_list(node<T> *head);

// duplicate the list, return pointer to last node in dest...
//      use this function in your queue big three
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

// delete all the nodes
template <typename T>
void _clear_list(node<T> *&head);

//_item at this position
template <typename T>
T &_at(node<T> *head, int pos);

// Functions Definition

// Linked List General Functions:
template <typename T>
void _print_list(node<T> *head)
{
    node<T> *walker = head;
    cout << "Head->";
    while (walker != nullptr)
    {
        cout << *walker;
        walker = walker->_next;
    }
    cout << " ||| " << endl;
}

// recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head)
{
    node<T> *walker = head;
    if (walker == nullptr)
    {
        cout << " ||| ";
    }
    else
    {
        _print_list_backwards(walker->_next);
        cout << "<-[" << walker->_item << "]->";
    }
}

// return ptr to key or NULL
template <typename T>
node<T> *_search_list(node<T> *head,
                      T key)
{
    node<T> *walker = head;
    while (walker != nullptr)
    {
        if (walker->_item == key)
            return walker;
        walker = walker->_next;
    }
    return nullptr;
}

template <typename T>
node<T> *_insert_head(node<T> *&head,
                      T insert_this)
{
    node<T> *temp = new node<T>(insert_this, head);
    if (head != nullptr)
        head->_prev = temp;
    head = temp;
    return head;
}

// insert after ptr: insert head if marker null
template <typename T>
node<T> *_insert_after(node<T> *&head,
                       node<T> *after_this,
                       T insert_this)
{
    if (head == nullptr || after_this == nullptr)
    {
        return _insert_head(head, insert_this);
    }
    // node<T> *walker = head;
    // while (walker != nullptr)
    // {
    //     if (walker == after_this)
    //     {
    //         break;
    //     }
    //     walker = walker->_next;
    // }
    // assert(walker != nullptr && "after_this or (mark) is not in the list");
    node<T> *temp = new node<T>(insert_this, after_this->_next, after_this);
    if (after_this->_next != nullptr)
        after_this->_next->_prev = temp;
    after_this->_next = temp;
    return temp;
}

// insert before ptr: insert head if marker null
template <typename T>
node<T> *_insert_before(node<T> *&head,
                        node<T> *before_this,
                        T insert_this)
{
    if (head == nullptr || before_this == nullptr)
    {
        return _insert_head(head, insert_this);
    }
    return _insert_after(head, before_this->_prev, insert_this);
}

// ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *prev_to_this)
{
    return prev_to_this->_prev;
}

// delete, return item
template <typename T>
T _delete_node(node<T> *&head, node<T> *delete_this)
{
    T item;
    if (head == nullptr || delete_this == nullptr)
    {
        return T();
    }
    if (head == delete_this)
    {
        head = head->_next;
        if (head != nullptr)
            head->_prev = nullptr;
        // delete_this->_prev = nullptr; is this needed ??
    }
    else
    {
        node<T> *temp = delete_this->_prev;
        temp->_next = delete_this->_next;
        node<T> *w = temp->_next;
        if (w != nullptr)
            w->_prev = temp;
        // delete_this->_prev->_next = delete_this->_next;
        // if (delete_this->_next != nullptr)
        //     delete_this->_next->_prev = delete_this->_prev;
    }
    item = delete_this->_item;
    delete delete_this;
    return item;
}

// duplicate the list...
template <typename T>
node<T> *_copy_list(node<T> *head)
{
    if (head == nullptr)
    {
        return head;
    }
    node<T> *result = new node<T>(head->_item);
    node<T> *result_walker = result;
    node<T> *walker = head->_next;
    while (walker != nullptr)
    {
        _insert_after(result, result_walker, walker->_item);
        result_walker = result_walker->_next;
        walker = walker->_next;
    }
    return result;
    // if (head == nullptr)
    //     return head;
    // node<T> *result = nullptr;
    // node<T> *after_node = nullptr;
    // for (node<T> *src_walker = head; src_walker != nullptr; src_walker = src_walker->_next)
    // {
    //     after_node = _insert_after(result, after_node, src_walker->_item);
    // }
    // return result;
}

// duplicate the list, return pointer to last node in dest...
//      use this function in your queue big three
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{
    if (dest != nullptr)
    {
        _clear_list(dest);
    }
    dest = _copy_list(src);
    if (dest == nullptr)
        return nullptr;
    node<T> *temp = dest;
    while (temp != nullptr)
    {
        if (temp->_next == nullptr)
            return temp;
        temp = temp->_next;
    }
    // dest = _copy_list(src);
    return temp;
}

// delete all the nodes
template <typename T>
void _clear_list(node<T> *&head)
{
    while (head != nullptr)
    {
        _delete_node(head, head);
    }
}

//_item at this position
template <typename T>
T &_at(node<T> *head, int pos)
{
    assert(pos >= 0 && "pos >= 0");
    node<T> *walker = head;
    int _pos = 0;
    while (walker != nullptr)
    {
        if (_pos == pos)
        {
            break;
        }
        _pos++;
        walker = walker->_next;
    }
    // assert(walker != nullptr && "pos =< size");
    return walker->_item;
}

#endif
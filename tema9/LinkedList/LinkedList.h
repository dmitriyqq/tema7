//
// Created by dima on 16.03.18.
//

#ifndef INC_7_LINKEDLIST_H
#define INC_7_LINKEDLIST_H

#include <malloc.h>
#include "../BinTree/Tree.h"

struct NamedListNode{
    struct NamedListNode* next;
    struct ListNode* values;
    struct ListNode* last_value;
};

struct ListNode{
    struct ListNode* next;
    struct ListNode* value;
};

struct NamedListNode* createNamedListNode(void* val);

void insertIntoNamedListNode(struct NamedListNode* node, void * val);

void insertNewNamedListNode(struct NamedListNode* node, void * val);

struct ListNode* createListNode(void* val);

void insertAfter(struct ListNode* node, void* val);

void destroyList(struct ListNode* node);

void destroyNamedList(struct NamedListNode* node);

#endif //INC_7_LINKEDLIST_H

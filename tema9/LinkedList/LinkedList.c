//
// Created by dima on 16.03.18.
//

#include "LinkedList.h"

struct NamedListNode* createNamedListNode(void* val){
   struct NamedListNode* node = malloc(sizeof(struct NamedListNode));

    node->next = NULL;
    node->values = createListNode(val);
    node->last_value = node->values;

}

void insertIntoNamedListNode(struct NamedListNode* node, void * val){
    insertAfter(node->last_value, val);
    node->last_value = node->last_value->next;
}

void insertNewNamedListNode(struct NamedListNode* node, void * val){
    struct NamedListNode* old_next = node->next;
    node->next = createNamedListNode(val);
    node->next->next = old_next;
}

struct ListNode* createListNode(void * val){
    struct ListNode* node = malloc(sizeof(struct ListNode));
    node->value = val;
    node->next = NULL;
    return node;
}

void insertAfter(struct ListNode* node, void * val){
    struct ListNode* old_next = node->next;
    node->next = malloc(sizeof(struct ListNode));
    node->next->next = old_next;
    node->next->value = val;
}

void destroyList(struct ListNode* node){
    if(node != NULL){
        destroyList(node->next);
    }
    free(node);
}

void destroyNamedList(struct NamedListNode* node){
    if(node != NULL){
        destroyNamedList(node->next);
        destroyList(node->values);
    }
    free(node);
}
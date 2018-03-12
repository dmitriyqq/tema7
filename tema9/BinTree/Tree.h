//
// Created by dima on 11.03.18.
//

#ifndef INC_7_TREE_H
#define INC_7_TREE_H

struct Node{
    struct Node *left, *right;
    void* value;
    int all;
    int free;
    int height;

};

void traverse(struct Node * v);

void addNode(void *val,struct Node **v);

void destroyTree(struct Node *v);

void prettyPrint(struct Node *v);

void bigLeft(struct Node **v);

void bigRight(struct Node **v);

void smallLeft(struct Node **v);

void smallRight(struct Node **v);


struct Node* createNode(void * val);


#endif //INC_7_TREE_H

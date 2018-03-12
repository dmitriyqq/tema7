//
// Created by dima on 11.03.18.
//


#include <malloc.h>
#include <string.h>
#include "Tree.h"
#include "../Model/Datatypes.h"

int max(int a, int b){
    return (a > b) ? a : b;
}

struct Node* createNode(void * val){

    struct Node* newNode = malloc(sizeof(struct Node));

    newNode->value = val;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;
    newNode->all = 1;

    struct Job* j= val;
    if(j->free)
        newNode->all = 0;
    else
        newNode->all = 1;

    return newNode;
}


void traverse(struct Node *v) {
    if(v != NULL){
        traverse(v->left);
        struct Job* j = v->value;
        printf("Job: %s all: %d free: %d", j->position, v->all, v->free);
        traverse(v->right);
    }
}

int cmp(struct Job *a, struct Job* b){
    int s = strcmp(a->position, b->position);
    if(s == 0)
        return 0;
    else if(s > 0)
        return 1;
    else if(s < 0)
        return -1;
}

void addNode(void *val, struct Node **v) {
    struct Node* vv = *v;

    if(vv == NULL){
        vv = createNode(val);
    }else if(cmp(vv->value, val) > 0){
        addNode(val, &vv->left);
    }else if(cmp(vv->value, val) < 0){
        addNode(val, &vv->right);
    }else{
        vv->all++;
        struct Job* j = val;
        if(!j->free)
            vv->free++;
    }

    // v->height = 1;
    // v->height += (v->left != nullptr) ? v->left->height : -1;
    // v->height += (v->right != nullptr) ? v->right->height : -1;
    /*

    int rh, lh, llh, lrh, rlh, rrh;
    rh = lh = llh = lrh = rlh = rrh = -1;

    if(vv->right != NULL){

        if(vv->right->left != NULL)
            rlh = vv->right->left->height;

        if(vv->right->right != NULL)
            rrh = vv->right->right->height;

        rh = vv->right->height;
    }

    if(vv->left != NULL){

        if(vv->left->left != NULL)
            llh = vv->left->left->height;

        if(vv->left->right != NULL)
            lrh = vv->left->right->height;

        lh = vv->left->height;
    }


    if(rh >= lh+2){
    // Left rotation
        if(rlh <= rrh) {
            smallLeft(v);//small rotation
        }else{
            bigLeft(v);//big rotation
        }
    }else if(lh >= rh+2){
                // Right rotation
        if(lrh <= llh) {
            smallRight(v);//small rotation
        }else{
            bigRight(v);//big rotation
        }
    }

    vv = *v;

    if(vv != NULL){
        int lh, rh;
        if(vv->left == NULL) lh = -1;
        else lh = vv->left->height;

        if(vv->right == NULL) rh = -1;
        else rh = vv->right->height;

        vv->height = max(lh,rh) + 1;
    }
    */
}

void destroyTree(struct Node *v) {

}

void bigLeft(struct Node **a) {
    smallRight(&(*a)->right);
    smallLeft(a);
}

void bigRight(struct Node **a) {
    smallLeft(&(*a)->left);
    smallRight(a);
}

void smallLeft(struct Node **a) {
    struct Node *t = *a;
    a = &(*a)->right;
    t->right = (*a)->left;
    (*a)->left = t;
}

void smallRight(struct Node **a) {
    struct Node *t  = *a;
    a = &(*a)->left;
    t->left = (*a)->right;
    (*a)->right = t;
}

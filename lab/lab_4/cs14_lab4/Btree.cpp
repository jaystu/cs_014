//
//  Btree.cpp
//  cs14_lab4
//
//  Created by John Stuart on 11/9/15.
//  Copyright © 2015 john. All rights reserved.
//

#include "Btree.h"
#include <list>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

template <class T>
struct Node {
    typename list<T>::const_iterator listIt; //list iterator (original position)
    Node *left;
    Node *right;
};
template <class T>
Btree::Btree() {
    root=NULL;
}
Btree::~Btree() {
    destroy_tree();
}
void Btree::insert(typename list<T>::const_iterator value) {
    if(root!=NULL)
        insert(value, root);
    else {
        root=new Node;
        root->listIt=value;
        root->left=NULL;
        root->right=NULL;
    }
}
void Btree::inOrder(typename list<T>::const_iterator &it, list<T> &l) {
    inOrder(it, l, root);
}
void Btree::destroy_tree() {
    destroy_tree(root);
}
void Btree::destroy_tree(Node *leaf) {
    if(leaf!=NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void Btree::insert(typename list<T>::const_iterator value, Node *leaf) {
    if(*value < *leaf->listIt) {
        if(leaf->left!=NULL)
            insert(value, leaf->left);
        else {
            leaf->left=new Node;
            leaf->left->listIt=value;
            leaf->left->left=NULL;    //Sets the left child of the child node to null
            leaf->left->right=NULL;   //Sets the right child of the child node to null
        }
    }
    else if(*value > *leaf->listIt) {
        if(leaf->right!=NULL)
            insert(value, leaf->right);
        else {
            leaf->right=new Node;
            leaf->right->listIt=value;
            leaf->right->left=NULL;  //Sets the left child of the child node to null
            leaf->right->right=NULL; //Sets the right child of the child node to null
        }
    }
    else {
        bool random = rand() < RAND_MAX/2;
        if (random == false) {
            if(leaf->left!=NULL)
                insert(value, leaf->left);
            else {
                leaf->left=new Node;
                leaf->left->listIt=value;
                leaf->left->left=NULL;    //Sets the left child of the child node to null
                leaf->left->right=NULL;   //Sets the right child of the child node to null
            }
        }
        else {
            if(leaf->right!=NULL)
                insert(value, leaf->right);
            else {
                leaf->right=new Node;
                leaf->right->listIt=value;
                leaf->right->left=NULL;  //Sets the left child of the child node to null
                leaf->right->right=NULL; //Sets the right child of the child node to null
            }
        }
    }
}
void Btree::inOrder(typename list<T>::const_iterator &it, list<T> &l, Node* leaf) {
    if (leaf == NULL) {
        return;
    }
    inOrder(it, l, leaf->left);
    cout << *leaf->listIt << " ";
    if (it == leaf->listIt) {
        it++;
    }
    l.insert(it, *leaf->listIt);
    l.erase(leaf->listIt);
    inOrder(it, l, leaf->right);
}

Node *root;

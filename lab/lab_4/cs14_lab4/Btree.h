//
//  Btree.hpp
//  cs14_lab4
//
//  Created by John Stuart on 11/9/15.
//  Copyright © 2015 john. All rights reserved.
//

#ifndef Btree_h
#define Btree_h
#include <iostream>
#include <list>
using namespace std;

template <class T>
class Btree {
public:
    struct Node;
    Btree();
    ~Btree();
    void insert(typename list<T>::const_iterator);
    void inOrder(typename list<T>::const_iterator &, list<T> &);
    void destroy_tree();
    
private:
    void destroy_tree(Node *);
    
    void insert(typename list<T>::const_iterator, Node *);
    void inOrder(typename list<T>::const_iterator &, list<T> &, Node*);
    
    Node *root;
    
};

#endif /* Btree_hpp */

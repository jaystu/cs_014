 //
//  main.cpp
//  cs14_lab4
//
//  Created by John Stuart on 10/27/15.
//  Copyright © 2015 john. All rights reserved.
//

#include <iostream>
#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

template <class T>
class Btree {
public:
    struct Node {
        typename list<T>::const_iterator listIt; //list iterator (original position)
        Node *left;
        Node *right;
    };
    Btree() {
        root=NULL;
    }
    ~Btree() {
        destroy_tree();
    }
    void insert(typename list<T>::const_iterator value) {
        if(root!=NULL)
            insert(value, root);
        else {
            root=new Node;
            root->listIt=value;
            root->left=NULL;
            root->right=NULL;
        }
    }
    void inOrder(typename list<T>::const_iterator &it, list<T> &l) {
        inOrder(it, l, root);
    }
    void destroy_tree() {
        destroy_tree(root);
    }
    
private:
    void destroy_tree(Node *leaf) {
        if(leaf!=NULL) {
            destroy_tree(leaf->left);
            destroy_tree(leaf->right);
            delete leaf;
        }
    }
    
    void insert(typename list<T>::const_iterator value, Node *leaf) {
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
    void inOrder(typename list<T>::const_iterator &it, list<T> &l, Node* leaf) {
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
    
};
class Fraction {
    int gcd(int a, int b) {return b==0 ? a : gcd(b,a%b); }
    int n, d;
public:
    Fraction(int n, int d) : n(n/gcd(n,d)), d(d/gcd(n,d)) {}
    int num() const { return n; }
    int den() const { return d; }
    Fraction& operator*=(const Fraction& rhs) {
        int new_n = n*rhs.n / gcd(n*rhs.n, d*rhs.d);
        d = d*rhs.d / gcd(n*rhs.n, d*rhs.d);
        n = new_n;
        return *this;
    }
};
std::ostream& operator<<(std::ostream& out, const Fraction& f){
    return out << f.num() << '/' << f.den() ;
}
bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return ((lhs.num() * rhs.den()) == (rhs.num() * lhs.den()));
}
bool operator<(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.num() * rhs.den() < rhs.num() * lhs.den());
}
bool operator>(const Fraction& lhs, const Fraction& rhs) {
    return (lhs.num() * rhs.den() > rhs.num() * lhs.den());
}
Fraction operator*(Fraction lhs, const Fraction& rhs)
{
    return lhs *= rhs;
}
/*template <typename T>
list<T> compare(list<T> l) {
    typename list<T>::const_iterator it = l.begin();
    advance(it, 1);
    for (; it != l.end(); it++) {
        if (*it == *(l.begin())) {
            cout << *it << " ";
            l.erase(it);
        }
    }
    cout << endl;
    for (it = l.begin(); it != l.end(); it++) {
        cout << *it << " ";
    }
    return l;
}*/
template <typename T>
list<T> sort (list<T> &l) {
    Btree<T> tree;
    typename list<T>::const_iterator it = l.begin();
    typename list<T>::const_iterator ti = l.begin();
    for (; it != l.end(); it++) {
        tree.insert(it);
    }
    it = l.begin();
    tree.inOrder(it, l);
    cout << endl;
    return l;
}
template <typename T>
void writeList (ofstream &out, list<T> l) {
    typename list<T>::const_iterator it;
    for (it = l.begin(); it != l.end(); it++) {
        out << *it;
        out << " ";
    }
}
int main(int argc, const char * argv[]) {
    
    char type;
    
    list<int> li;
    list<Fraction> lf;
    
    string fileName = argv[1];
    string outputfilename = fileName;
    
    if(fileName.find('.') != string::npos) {
        int index = fileName.find('.');
        outputfilename.erase(index, outputfilename.size() - 1);
    }
    else outputfilename = fileName;
    outputfilename += ".out";
    string line;
    ifstream myfile;
    myfile.open (fileName.c_str());
    ofstream outFile;
    outFile.open (outputfilename.c_str());
    
    while (getline(myfile, line)) {
        
        istringstream(line) >> type;
        
        getline (myfile, line);
        stringstream ss(line);
        int value;
        if (type == 'f') {
            outFile << type << endl;
            while (ss >> value)
            {
                int n = value;
                ss >> value;
                int d = value;
                Fraction fraction(n, d);
                lf.push_back(fraction);
                
                if (ss.peek() == ' ')
                    ss.ignore();
            }
            sort(lf);
            cout << endl << endl << endl;
            writeList(outFile, lf);
            lf.clear();
        }
        else {
            outFile << type << endl;
            while (ss >> value) {
            li.push_back(value);
            
            if (ss.peek() == ' ')
                ss.ignore();
            }
            sort(li);
            writeList(outFile, li);
            li.clear();
        }
        outFile << endl;
    }
    myfile.close();
    outFile.close();
    return 0;
}

// by Ali Ankoud and Kimberly Rodriguez
// 17 August 2022
// BSTree.h

#pragma once
#include "Account.h"

class BSTree
{
    public:
        BSTree();
        ~BSTree();

        bool Insert(Account *);
        // retrieve object, first parameter is the ID of the account
        // second parameter holds pointer to found object, NULL if not found
        bool Retrieve(const int &, Account * &) const;
        // displays the contents of a tree to cout
        void Display() const;

        void Empty();
        bool isEmpty() const;

        void recursivePrint(Node* current) const;
        bool RecursiveInsert(Node* current, Account* insert);
        
    private:
        struct Node
        {
            Account *pAcct;
            Node *right;
            Node *left;
        }; 

        Node *root;
};
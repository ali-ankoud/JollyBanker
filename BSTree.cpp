#include "stdafx.h"
#include "BSTree.h"


BSTree::BSTree()
{
}


BSTree::~BSTree()
{
	Empty();
}

bool BSTree::Insert(Account *insert)
{
	int insertAccountID = insert->getAccountID();
	if (insertAccountID < 1000 || insertAccountID > 9999)
	{
		cerr << "ERROR: Account Number Not Valid" << endl;
		return false;
	}

	if (root == NULL)
	{
		root = new Node;
		root->pAcct = insert;
		root->left = NULL;
		root->right = NULL;
		return true;
	}
	else
	{
		Node *current = root;
		RecursiveInsert(current, insert);
	}
	return false;
}

bool BSTree::Retrieve(const int & accountNumber, Account *& acc) const
{
	Node *current = root;
	bool search = false;

	while (!search) 
	{
		if (current != NULL && accountNumber == current->pAcct->getAccountID())
		{
			search = true;
			acc = current->pAcct;
			return search;
		}
		else if(current != NULL && accountNumber > current->pAcct->getAccountID())
		{
			current = current->right;
		}
		else if (current != NULL && accountNumber < current->pAcct->getAccountID())
		{
			current = current->left;
		}
		else
		{
			search = true;
		}

	}
	cerr << "ERROR: Account Number " << accountNumber  << " Cannot Be Found" << endl;
	return false;
}

void BSTree::Display() const
{
	if (root == NULL)
	{
		cerr << "ERROR: ACCOUNT LIST IS EMPTY" << endl;
	}
	recursivePrint(root);
}

void BSTree::Empty()
{
	delete root;
	root = NULL;
}

bool BSTree::isEmpty() const
{
	if (root->left == NULL && root->right == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BSTree::recursivePrint(Node* current) const
{	
	if (current->right != NULL && current->left != NULL)
	{
		recursivePrint(current->right);
		cout << *(current->pAcct) << endl;
		recursivePrint(current->left);
	}
	else if (current->left != NULL)
	{
		cout << *(current->pAcct) << endl;
		recursivePrint(current->left);
	}
	else if (current->right != NULL)
	{
		cout << *(current->pAcct) << endl;
		recursivePrint(current->right);
	}
	else
	{
		cout << *(current->pAcct) << endl;
	}

}

bool BSTree::RecursiveInsert(Node* current, Account* insert)
{
	if (insert->getAccountID() > current->pAcct->getAccountID())
	{
		if (current->right == NULL)
		{
			Node *insInTree = new Node();
			insInTree->pAcct = insert;
			insInTree->left = NULL;
			insInTree->right = NULL;
			current->right = insInTree;
			return true;
		}
		else
		{
			return RecursiveInsert(current->right, insert);
		}

	}
	else if(insert->getAccountID() < current->pAcct->getAccountID()  )
	{
		if (current->left == NULL)
		{
			Node *insInTree = new Node();
			insInTree->pAcct = insert;
			insInTree->left = NULL;
			insInTree->right = NULL;
			current->left = insInTree;
			return true;
		}
		else
		{
			return RecursiveInsert(current->left, insert);
		}

	}
	else
	{
		cerr << "ERROR: Account " << insert->getAccountID() << " is already open. Transaction refused." << endl;
		return false;
	}
	
}

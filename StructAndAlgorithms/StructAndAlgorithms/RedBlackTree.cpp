#include <iostream>
#include "RedBlackTree.h"

using namespace std;

namespace StructAlgorithm
{
	void SearchTree::inorderTreeWalk(const TreeNode* root)
	{
		if (!root)
		{
			return;
		}

		inorderTreeWalk(root->left);
        
		cout<<root->key<<endl;

		inorderTreeWalk(root->right);
	}

	void SearchTree::preorderTreeWalk(const TreeNode* root)
	{
		if(!root)
		{
			return;
		}

		cout<<root->key<<endl;

		preorderTreeWalk(root->left);
		preorderTreeWalk(root->right);
	}

	void SearchTree::postorderTreeWalk(const TreeNode* root)
	{
		if(!root)
		{
			return;
		}

		postorderTreeWalk(root->left);
		postorderTreeWalk(root->right);

		cout<<root->key<<endl;
	}

	TreeNode* SearchTree::treeSearch(TreeNode* root,const int& key)
	{
		if (!root || root->key == key)
		{
			return root;
		}

		if (key > root->key)
		{
			return treeSearch(root->right,key);
		}
		else
		{
			return treeSearch(root->left,key);
		}

#if 0
		while (root && root->key != key)
		{
			if (key > root->key)
			{
				root = root->right;
			}
			else
			{
				root = root->left;
			}
		}

		return root;
#endif
	}

	TreeNode* SearchTree::treeMinimum( TreeNode* root)
	{
		while(root->left)
		{
			root = root->left;
		}

		return root;
	}
	
	TreeNode* SearchTree::treeMaximum( TreeNode* root)
	{
		while(root->right)
		{
			root = root->right;
		}

		return root;
	}
	
	TreeNode* SearchTree::treeSuccessor( TreeNode* root)
	{
		if (root->right)
		{
			return treeMinimum(root->right);
		}
        
		TreeNode* parent = root->p;
		
		while(parent && root == parent->left)
		{
			root = parent;
			parent = parent->p;
		}

		return root;
	}

	TreeNode* SearchTree::treePresuccessor( TreeNode* root)
	{
		if (root->left)
		{
			return treeMaximum(root->left);
		}

		TreeNode* parent = root->p;
		
		while(parent && root == parent->right)
		{
			root = parent;
			parent = parent->p;
		}

		return parent;
	}

	void SearchTree::treeInsert(TreeNode*& root,TreeNode* node)
	{
		TreeNode* tempNode = root;
        TreeNode* flagNode = 0;

		while(tempNode)
		{
			flagNode = tempNode;

			if (node->key > tempNode->key)
			{
				tempNode = tempNode->right;
			}
			else
			{
				tempNode = tempNode->left;
			}
		}

		node->p = flagNode;

		if (!flagNode)
		{
			root = flagNode;
		}
        else if (node->key > flagNode->key)
        {
			flagNode->right = node;
        }
		else
		{
			flagNode->left = node;
		}
	}

	void SearchTree::transplant(TreeNode*& root,TreeNode* childRootU,TreeNode* childRootV)
	{
		if (!childRootU->p)
		{
			root = childRootV;
		}
		else if (childRootU == childRootU->p->left)
		{
			childRootU->p->left = childRootV;
		}
		else
		{
			childRootU->p->right = childRootV;
		}

		if (childRootV)
		{
			childRootV->p = childRootU->p;
		}
	}
	void SearchTree::treeDelete(TreeNode* root,TreeNode* deleteNode)
	{
		if (0 == deleteNode->left)
		{
			transplant(root,deleteNode,deleteNode->right);
		}
		else if (0 == deleteNode->right)
		{
			transplant(root,deleteNode,deleteNode->left);
		}
		else
		{
			TreeNode* successor = treeSuccessor(deleteNode);

			if (successor == deleteNode->right)
			{
				transplant(root,deleteNode,successor);
			}
			else
			{
				transplant(root,successor,successor->right);
				successor->right = deleteNode->right;
				successor->right->p = successor;
			}

			successor->left = deleteNode->left;
			successor->left->p = successor;
		}
	}

	///////////////////RedBlackTree//////////////////////

	TreeNode* RedBlackTree::nil = 0;

	void RedBlackTree::leftRotate(TreeNode*& root,TreeNode* node)
	{
		TreeNode* y = node->right;
		node->right = y->left;

		if (y->left)
		{
			y->left->p = node;
		}

		y->p = node->p;

		if (y->p = nil)
		{
			root = y;
		}
		else if (node->p->right == node)
		{
			y->p->right = y;
		}
		else
		{
			y->p->left = y;
		}

		y->left = node;
        node->p = y; 
	}

	void RedBlackTree::rightRotate(TreeNode*& root,TreeNode* node)
	{
		TreeNode* x = node->left;
		node->left = x->right;

		if (x->right)
		{
			x->right->p = node;
		}

		x->p = node->p;

		if (x->p == nil)
		{
			root = x;
		}
		else if (node->p->left == node)
		{
			x->p->left = x;
		}
		else
		{
			x->p->right = x;
		}

		x->right = node;
		node->p = x;
	}

	void RedBlackTree::RBTreeInsert(TreeNode*& root,TreeNode* z)
	{
		TreeNode* x = root;
		TreeNode* y = nil;

		while(x != nil)
		{
			y = x;

			if (z->key > x->key)
			{
				x = x->right;
			}
			else
			{
				x = x->left;
			}
		}

		z->p = y;

		if (y == nil)
		{
			root = z;
		}

		if (z->key > y->key)
		{
			y->right = z;
		}
		else
		{
			y->left = z;
		}

		z->left = nil;
		z->right = nil;
		z->colour = RED;

		RBTreeInsertFixup(root,z);
	}
	void RedBlackTree::RBTreeInsertFixup(TreeNode*& root,TreeNode* z)
	{
		while(z->p && z->p->colour == RED)
		{
			if (z->p == z->p->p->left)
			{
				TreeNode* y = z->p->p->right;

				if (RED == y->colour)
				{
					z->p->colour = BLACK;
					y->colour = BLACK;
					z->p->p->colour = RED;
					z = z->p->p;
				}
				else
				{
					if (z == z->p->right)
					{
						z = z->p;
						leftRotate(root,z);
					}
					
					z->p->colour = BLACK;
					z->p->p->colour = RED;

					rightRotate(root,z->p->p);
				}
			}
			else
			{
				TreeNode* y = z->p->p->left;

				if (RED == y->colour)
				{
					z->p->colour = BLACK;
					y->colour = BLACK;
					z->p->p->colour = RED;
					z = z->p->p;
				}
				else
				{
					if (z == z->p->left)
					{
						z = z->p;
						rightRotate(root,z);
					}

					z->p->colour = BLACK;
					z->p->p->colour = RED;

					leftRotate(root,z->p->p);
				}
			}
		}

		root->colour = BLACK;

	}

	void RedBlackTree::RBTransplant(TreeNode*& root,TreeNode* u,TreeNode* v)
	{
		if (u->p == nil)
		{
			root = v;
		}
		else if( u == u->p->left)
		{
			u->p->left = v;
		}
		else
		{
			u->p->right = v;
		}

		u->p = v->p;
	}

	void RedBlackTree::RBTreeDelete(TreeNode*& root,TreeNode* z)
	{
		TreeNode* y = z;

		TreeColour originalColor = y->colour;

		TreeNode* x =nil;

		if (z->left == nil)
		{
			x = z->right;

			RBTransplant(root,z,z->right);
		}
		else if (z->right == nil)
		{
			x = z->left;
			RBTransplant(root,z,z->left);
		}
		else
		{
			y = treeMinimum(z->right);

			originalColor = y->colour;
			x = y->right;

			if (y->p == z)
			{
				x->p = y;
			}
			else
			{
				RBTransplant(root,y,y->right);
				y->right = z->right;
				y->right->p = y;
			}

			RBTransplant(root,z,y);
			y->left = z->left;
			y->left->p = y;
			y->colour = z->colour;
		}

		if (originalColor == BLACK)
		{
			RBDeleteFixup(root,x);
		}
	}

	void RedBlackTree::RBDeleteFixup(TreeNode*& root,TreeNode* x)
	{
		while(x != root && BLACK == x->colour)
		{
			if (x == x->p->left)
			{
				TreeNode* w = x->p->right;

				if (RED == w->colour)
				{
					w->colour = BLACK;
					x->p->colour = RED;
					leftRotate(root,x->p);
					w = x->p->right;
				}

				if (w->left->colour == BLACK && w->right->colour == BLACK)
				{
					w->colour = RED;
					x = x->p;
				}
				else
				{
					if (w->right->colour == BLACK)
					{
						w->left->colour = BLACK;
						w->colour = RED;
						rightRotate(root,w);
						w = x->p->right;
					}

					w->colour = x->p->colour;
					x->p->colour = BLACK;
					w->right->colour =BLACK;
					leftRotate(root,x->p);

					x = root;
				}	
			}
			else
			{
				TreeNode* w = x->p->left;

				if (RED == w->colour)
				{
					w->colour = BLACK;
					x->p->colour = RED;
					leftRotate(root,x->p);
					w = x->p->left;
				}

				if (w->left->colour == BLACK && w->right->colour == BLACK)
				{
					w->colour = RED;
					x = x->p;
				}
				else
				{
					if (w->left->colour == BLACK)
					{
						w->right->colour = BLACK;
						w->colour = RED;
						leftRotate(root,w);
						w = x->p->left;
					}

					w->colour = x->p->colour;
					x->p->colour = BLACK;
					w->left->colour =BLACK;
					rightRotate(root,x->p);

					x = root;
				}	
			}
		}

		x->colour = BLACK;
	}
}



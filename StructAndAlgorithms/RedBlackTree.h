#pragma once

namespace StructAlgorithm
{
	enum TreeColour
	{
		RED,
		BLACK
	};

	struct TreeNode
	{
		TreeNode()
			:p(0)
			,left(0)
			,right(0)
			,key(0)
			,colour(BLACK)
		{

		}

		TreeNode* p;
		TreeNode* left;
		TreeNode* right;
		int key;
		TreeColour colour;
	};

	class SearchTree
	{
	public:
		static void inorderTreeWalk(const TreeNode* root);
		static void preorderTreeWalk(const TreeNode* root);
		static void postorderTreeWalk(const TreeNode* root);
		static TreeNode* treeSearch( TreeNode* root, const int& key);
		static TreeNode* treeMinimum( TreeNode* root);
		static TreeNode* treeMaximum( TreeNode* root);
		static TreeNode* treeSuccessor( TreeNode* root);
		static TreeNode* treePresuccessor( TreeNode* root);
		static void treeInsert(TreeNode*& root,TreeNode* node);
		static void transplant(TreeNode*& root,TreeNode* childRootU,TreeNode* childRootV);
		static void treeDelete(TreeNode* root,TreeNode* deleteNode);
	};

	class RedBlackTree : public SearchTree
	{
	public:
		static void leftRotate(TreeNode*& root,TreeNode* node);
		static void rightRotate(TreeNode*& root,TreeNode* node);
		static void RBTreeInsert(TreeNode*& root,TreeNode* z);
		static void RBTreeInsertFixup(TreeNode*& root,TreeNode* z);
		static void RBTransplant(TreeNode*& root,TreeNode* u,TreeNode* v);
		static void RBTreeDelete(TreeNode*& root,TreeNode* z);
		static void RBDeleteFixup(TreeNode*& root,TreeNode* x);
        
	private:
		static TreeNode* nil;

	};
}
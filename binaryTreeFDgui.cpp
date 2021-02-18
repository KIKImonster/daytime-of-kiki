#define _CRT_SECURE_NO_WARNINGS 1
#include"binaryTree1.h"

BTNode* BinaryTreeCreat(BTDataType* a, int* pi)
{
	if (a[*pi] != '#')
	{
		BTNode* root = (BTNode*)malloc(sizeof(BTNode));
		root->_data = a[*pi];
		++(*pi);
		root->_left = BinaryTreeCreat(a, pi);
		++(*pi);
		root->_right = BinaryTreeCreat(a, pi);
		return root;
	}
	else
		return NULL;
}

//二叉树的销毁
void BinaryTreeDestory(BTNode** root)
{
	BTNode* cur = *root;
	if (cur)
	{
		BinaryTreeDestory(&cur->_left);
		BinaryTreeDestory(&cur->_right);
		free(cur);
		*root = NULL;
	}
}

//二叉树叶子节点个数
int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	if (root->_left == NULL && root->_right == NULL)
		return 1;

	return BinaryTreeLeafSize(root->_left)
		+ BinaryTreeLeafSize(root->_right);
}

//二叉树节点个数
void BinaryTreeSize2(BTNode* root, int* num)
{
	if (root)
	{
		++(*num);
		BinaryTreeSize2(root->_left, num);
		BinaryTreeSize2(root->_right, num);
	}
}

//二叉树第k层节点个数
int BinaryTreeKSize(BTNode* root, int k)
{
	if (root == NULL)
		return 0;
	if (k == 1)
		return 0;
	return BinaryTreeKSize(root->_left, k - 1)
		+ BinaryTreeKSize(root->_right, k - 1);
}

//二叉树查找值为X的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	BTNode* ret;
	if (root == NULL)
		return NULL;
	if (root->_data == x)
		return root;
	ret = BinaryTreeFind(root->_left, x);
	if (ret)
		return ret;

	return BinaryTreeFind(root->_right, x);
}

//二叉树的前序遍历
void BinaryTreePreOrder(BTNode* root);

//二叉树的中序遍历
void BinaryTreeInOrder(BTNode* root);

//二叉树的后序遍历
void BinaryTreePosOrder(BTNode* root);

//二叉树的层序遍历
void BinaryTreeLevelOrder(BTNode* root);

//判断二叉树是否是完全二叉树
void BinaryTreeComplete(BTNode* root);

#ifndef _AVLTREE_H_
#define _AVLTREE_H_
#include <memory>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
class AvlNode
{
public:
	AvlNode(const T& e) :elem(e),height(0) {}
	T elem;
	std::shared_ptr<AvlNode> left;
	std::shared_ptr<AvlNode> right;
	int	height;
};

template <typename T>
class AvlTree
{
public:
	void insertElement(const T& X)
	{
		insert(X, root);
	}
	void preorderTraverse(std::vector<int>& v)
	{
		preorder(root, v);
	}

private:
	void preorder(std::shared_ptr<AvlNode<T>> rt, std::vector<int>& v)
	{
		if (rt)
			v.push_back(rt->elem);
		else
			return;
		preorder(rt->left, v);
		preorder(rt->right, v);
	}
	int height(std::shared_ptr<AvlNode<T>> t)
	{
		if (t)
			return t->height;
		else
			return -1;
	}
	void singleRotateWithLeft(std::shared_ptr<AvlNode<T>>& k2)
	{
		std::shared_ptr<AvlNode<T>> k1 = k2->left;
		std::shared_ptr<AvlNode<T>> orig_k2 = k2;
		orig_k2->left = k1->right;
		k1->right = orig_k2;
		k2 = k1;
		orig_k2->height = std::max(height(orig_k2->left), height(orig_k2->right)) + 1;
		k2->height = std::max(height(k2->left), height(k2->right)) + 1;
	}
	void doubleRotateWithLeft(std::shared_ptr<AvlNode<T>>& k3)
	{
		singleRotateWithRight(k3->left);
		singleRotateWithLeft(k3);
	}
	void singleRotateWithRight(std::shared_ptr<AvlNode<T>>& k2)
	{
		std::shared_ptr<AvlNode<T>> k1 = k2->right;
		std::shared_ptr<AvlNode<T>> orig_k2 = k2;
		orig_k2->right = k1->left;
		k1->left = orig_k2;
		k2 = k1;
		orig_k2->height = std::max(height(orig_k2->left), height(orig_k2->right)) + 1;
		k2->height = std::max(height(k2->left), height(k2->right)) + 1;
	}
	void doubleRotateWithRight(std::shared_ptr<AvlNode<T>>& k3)
	{
		singleRotateWithLeft(k3->right);
		singleRotateWithRight(k3);
	}
	void insert(const T& X, std::shared_ptr<AvlNode<T>>& t)
	{
		if (t == nullptr)
		{
			t = std::make_shared<AvlNode<T>>(AvlNode<T>(X));
		}
		else if (X < t->elem)
		{
			insert(X, t->left);
			if (height(t->left) - height(t->right) == 2)
			{
				if (X < t->left->elem)
					singleRotateWithLeft(t);
				else
					doubleRotateWithLeft(t);
			}
		}
		else if (t->elem < X)
		{
			insert(X, t->right);
			if (height(t->right) - height(t->left) == 2)
			{
				if (t->right->elem < X)
					singleRotateWithRight(t);
				else
					doubleRotateWithRight(t);
			}
		}
		t->height = std::max(height(t->left), height(t->right)) + 1;
	}
	std::shared_ptr<AvlNode<T>> root;
};





#endif
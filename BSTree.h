#pragma once
#include<iostream>
using namespace std;

//节点的结构
template<class K, class V>
struct BSTNode
{
	K _key;
	V _value;

	BSTNode<K, V>* _left;
	BSTNode<K, V>* _right;

	BSTNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class K, class V>
class BSTree
{
	typedef BSTNode<K, V> Node;
public:
	BSTree()
		:_root(NULL)
	{}

	//析构函数
	~BSTree()
	{
		_Destory(_root);
		_root = NULL;
	}
public:
	bool Insert(const K& key, const V& value)
	{
		//树为空
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		//找到数据应该插入的父节点的位置
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		//插入
		cur = new Node(key, value);
		if (key < parent->_key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		return true;
	}

	bool Insert_R(const K& key, const V& value)
	{
		return _Insert_R(_root, key, value);
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return NULL;
	}

	Node* Find_R(const K& key)
	{
		return _Find_R(_root, key);
	}


	bool Remove(const K& key)
	{
		Node * cur = _root;
		Node* parent = NULL;

		//找到需要删除的节点
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				break;
			}
		}

		//删除
		if (cur == NULL)
		{
			return false;
		}

		Node* del = cur;
		//删除节点的左孩子或者右孩子为空
		if (cur->_left == NULL)
		{
			//根节点
			if (cur == _root)
			{
				_root = cur->_right;
			}
			else
			{
				if (cur == parent->_left)
				{
					parent->_left = cur->_right;
				}
				else
				{
					parent->_right = cur->_right;
				}
			}
		}
		else if (cur->_right == NULL)
		{
			//根节点
			if (cur == _root)
			{
				_root = cur->_left;
			}
			else
			{
				if (cur == parent->_left)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_left;
				}
			}
		}
		else
		{
			//左右孩子均不为空
			//找到右子树的最左孩子
			Node* firstLeft = cur->_right;
			while (firstLeft->_left)
			{
				parent = firstLeft;
				firstLeft = firstLeft->_left;
			}

			//替换需要删除的节点
			cur->_key = firstLeft->_key;
			cur->_value = firstLeft->_value;

			del = firstLeft;

			if (firstLeft == parent->_left)
			{
				parent->_left = firstLeft->_right;
			}
			else
			{
				parent->_right = firstLeft->_right;
			}
		}
		delete del;
		return true;
	}

	bool Remove_R(const K& key)
	{
		return _Remove_R(_root, key);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

protected:
	void _InOrder(Node*root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << "-";
		_InOrder(root->_right);
		return;
	}

	bool _Insert_R(Node*& root, const K& key, const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}
		if (root->_key > key)
		{
			_Insert_R(root->_left, key, value);
		}
		else if (root->_key < key)
		{
			_Insert_R(root->_right, key, value);
		}
		else
		{
			return false;
		}
	}

	bool _Remove_R(Node*& root, const K& key)
	{
		if (root == NULL)
		{
			return false;
		}

		if (root->_key > key)
		{
			return _Remove_R(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _Remove_R(root->_right, key);
		}
		else
		{
			Node* del = root;
			//节点的一个孩子为空
			if (root->_left == NULL)
			{
				root = root->_right;
				delete del;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
				delete del;
			}
			else
			{
				//左右孩子为空
				Node* firstLeft = root->_right;
				while (firstLeft->_left)
				{
					firstLeft = firstLeft->_left;
				}

				swap(root->_key, firstLeft->_key);
				swap(root->_value, firstLeft->_value);

				return _Remove_R(root->_right, key);
			}
		}
	}

	Node* _Find_R(Node* root, const K& key)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (root->_key > key)
		{
			return _Find_R(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _Find_R(root->_right, key);
		}
		else
		{
			return root;
		}
	}

	void _Destory(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}
private:
	Node* _root;
};

void TestBSTree()
{
	int a[] = { 0,1,2,3,4,5,6,7,8,9 };
	BSTree<int, int> bt;
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		bt.Insert(a[i], i);
	}
	bt.InOrder();

	/*for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		bt.Remove(a[i]);
		bt.InOrder();
	}*/

	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		BSTNode<int, int>* ret = bt.Find(a[i]);
		if (ret)
		{
			cout << ret->_key << endl;
		}
	}

	BSTNode<int, int>* ret = bt.Find(10);
	if (ret)
	{
		cout << ret->_key << endl;
	}
}

void TestBSTree_R()
{
	int a[] = { 0,1,2,3,4,5,6,7,8,9 };
	BSTree<int, int> bt;
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		bt.Insert_R(a[i], i);
	}
	bt.InOrder();

	/*for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		bt.Remove_R(a[i]);
		bt.InOrder();
	}*/

	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		BSTNode<int, int>* ret = bt.Find_R(a[i]);
		if (ret)
		{
			cout << ret->_key << endl;
		}
	}

	BSTNode<int, int>* ret = bt.Find_R(10);
	if (ret)
	{
		cout << ret->_key << endl;
	}
}
#pragma once

#include <memory>
#include <vector>

using namespace std;

namespace assignment4
{
	template<typename T>
	class TreeNode;

	template<typename T>
	class BinarySearchTree final
	{
	public:
		BinarySearchTree();
		void Insert(unique_ptr<T> data);
		bool Search(const T& data);
		bool Delete(const T& data);
		const weak_ptr<TreeNode<T>> GetRootNode() const;

		static vector<T> TraverseInOrder(const shared_ptr<TreeNode<T>> startNode);

	private:	
		static void traverseInOrderRecursive(const shared_ptr<TreeNode<T>> current, vector<T>& vector);
		void replaceNode(shared_ptr<TreeNode<T>> current, shared_ptr<TreeNode<T>> parent, bool bIsLeft);
		shared_ptr<TreeNode<T>> findMostLeftChild(const shared_ptr<TreeNode<T>> current);
		bool deleteFromNode(shared_ptr<TreeNode<T>> startNode, const T& data);
		shared_ptr<TreeNode<T>> mRoot;	
	};

	template<typename T>
	BinarySearchTree<T>::BinarySearchTree()
		: mRoot(nullptr)
	{
	}

	template<typename T>
	void BinarySearchTree<T>::Insert(unique_ptr<T> data)
	{
		T value = *data;
		shared_ptr<TreeNode<T>> newNodePtr = make_shared<TreeNode<T>>(move(data));

		if (mRoot == nullptr)
		{
			mRoot = newNodePtr;
			return;
		}

		shared_ptr<TreeNode<T>> current = mRoot;
		shared_ptr<TreeNode<T>> parent = mRoot;
		
		while (true)
		{
			if (value <= *current->Data)
			{
				parent = current;
				current = current->Left;
				if (current == nullptr)
				{
					parent->Left = newNodePtr;
					newNodePtr->Parent = parent;
					break;
				}
			}
			else
			{
				parent = current;
				current = current->Right;
				if (current == nullptr)
				{
					parent->Right = newNodePtr;
					newNodePtr->Parent = parent;
					break;
				}
			}
		}
	}
	
	template<typename T>
	const weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		shared_ptr<TreeNode<T>> n = mRoot;
		return n;
	}

	template<typename T>
	bool BinarySearchTree<T>::Search(const T& data)
	{
		shared_ptr<TreeNode<T>> current = mRoot;
		while (current != nullptr)
		{
			if (data == *current->Data)
			{
				return true;
			}
			else if (data < *current->Data)
			{
				current = current->Left;
			}
			else
			{
				current = current->Right;
			}
		}
			
		return false;
	}
	
	template<typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		if (mRoot == nullptr)
		{
			return false;
		}
		return deleteFromNode(mRoot, data);
	}

	template<typename T>
	bool BinarySearchTree<T>::deleteFromNode(shared_ptr<TreeNode<T>> startNode, const T& data)
	{
		shared_ptr<TreeNode<T>> current = startNode;
		shared_ptr<TreeNode<T>> parent = startNode->Parent.lock();
	
		if (data == *current->Data)
		{
			if (parent == nullptr)
			{
				//situation of current == mRoot
				replaceNode(current, current, true);
				return true;
			}
			
			bool bIsLessThanParent = false;
			if (*current->Data < *parent->Data)
			{
				bIsLessThanParent = true;
			}
			replaceNode(current, parent, bIsLessThanParent);
			return true;
		}

		while (true)
		{
			if (data < *current->Data)
			{
				parent = current;
				current = current->Left;
				if (current == nullptr) 
				{
					break;
				}

				if (*current->Data == data)
				{
					replaceNode(current, parent, true);
					return true;
				}
			}
			else 
			{
				parent = current;
				current = current->Right;
				if (current == nullptr)
				{
					break;
				}

				if (*current->Data == data)
				{
					replaceNode(current, parent, false);
					return true;
				}
			}
		}

		return false;
	}

	template<typename T>
	shared_ptr<TreeNode<T>> BinarySearchTree<T>::findMostLeftChild(const shared_ptr<TreeNode<T>> current)
	{
		shared_ptr<TreeNode<T>> ptr = current;
		while (ptr->Left != nullptr)
		{
			ptr = ptr->Left;
		}
		return ptr;
	}

	template<typename T>
	void BinarySearchTree<T>::replaceNode(shared_ptr<TreeNode<T>> current, shared_ptr<TreeNode<T>> parent, bool bIsLeft)
	{
		if (current == parent)
		{
			//situation of (current == mRoot) 
			if (current->Left == nullptr && current->Right == nullptr)
			{
				mRoot = nullptr;
			}
			else if (current->Left != nullptr && current->Right == nullptr)
			{
				mRoot = current->Left;			
			}
			else if (current->Left == nullptr && current->Right != nullptr)
			{	
				mRoot = current->Right;
			}
			else
			{
				shared_ptr<TreeNode<T>> lowestNodeOfRight = findMostLeftChild(current->Right);
				T value = *lowestNodeOfRight->Data;
				*mRoot->Data = value;
				deleteFromNode(current->Right, value);
			}

			return;
		}

		if (current->Left == nullptr && current->Right == nullptr)
		{
			if (bIsLeft == true)
			{
				parent->Left = nullptr;
			}	
			else 
			{
				parent->Right = nullptr;
			}
		}
		else if (current->Left != nullptr && current->Right == nullptr)
		{
			if (bIsLeft == true)
			{
				parent->Left = current->Left;
				current->Left->Parent = parent;
			}
			else
			{
				parent->Right = current->Left;
				current->Left->Parent = parent;
			}
		}
		else if (current->Left == nullptr && current->Right != nullptr)
		{
			if (bIsLeft == true)
			{
				parent->Left = current->Right;
				current->Right->Parent = parent;
			}
			else
			{
				parent->Right = current->Right;
				current->Right->Parent = parent;
			}
		}
		else
		{
			shared_ptr<TreeNode<T>> lowestNodeOfRight = findMostLeftChild(current->Right);
			*current->Data = *lowestNodeOfRight->Data;
			deleteFromNode(current->Right, *current->Data);
		}
	}

	template<typename T>
	vector<T> BinarySearchTree<T>::TraverseInOrder(const shared_ptr<TreeNode<T>> startNode)
	{
		vector<T> v;
		if (startNode == nullptr)
		{
			return v;
		}

		traverseInOrderRecursive(startNode, v);	
		return v;
	}
		
	template<typename T>
	void BinarySearchTree<T>::traverseInOrderRecursive(const shared_ptr<TreeNode<T>> current, vector<T>& v)
	{
		if (current == nullptr)
		{
			return;
		}
	
		traverseInOrderRecursive(current->Left, v);
		v.push_back(*current->Data);
		traverseInOrderRecursive(current->Right, v);		
	}
}

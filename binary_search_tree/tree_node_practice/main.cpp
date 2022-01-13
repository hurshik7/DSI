#include <iostream>
#include <vector>
#include "TreeNode.h"

using namespace std;

template<typename T>
vector<T> TraverseInOrder(const shared_ptr<TreeNode<T>> startNode)
{
	vector<T> v;
	if (startNode == nullptr)
	{
		return v;
	}

	TraverseInOrderRecursive(startNode, v);	
	return v;
}
		
template<typename T>
void TraverseInOrderRecursive(const shared_ptr<TreeNode<T>> current, vector<T>& v)
{
	if (current == nullptr)
	{
		return;
	}
	TraverseInOrderRecursive(current->Left, v);
	v.push_back(*current->Data);
	TraverseInOrderRecursive(current->Right, v);		
}

int main(void)
{
	TreeNode<int> n1(make_unique<int>(1));

	shared_ptr<TreeNode<int>> ptr = make_shared<TreeNode<int>>(make_unique<int>(2));

	shared_ptr<TreeNode<int>> leftChild = make_shared<TreeNode<int>>(make_unique<int>(1));
	ptr->Left = leftChild;
	leftChild->Parent = ptr;	

	shared_ptr<TreeNode<int>> child = make_shared<TreeNode<int>>(make_unique<int>(3));
	ptr->Right = child;
	child->Parent = ptr;
	
	cout << *child->Data << endl;
	cout << *(child->Parent.lock())->Data << endl;

	return 0;
}

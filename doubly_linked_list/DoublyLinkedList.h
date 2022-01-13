#pragma once

#include <memory>
#include <iostream>

using namespace std;

namespace lab10
{
	template<typename T>
	class Node;

	template<typename T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList();
		void Insert(std::unique_ptr<T> data);
		void Insert(std::unique_ptr<T> data, unsigned int index);
		bool Delete(const T& data);
		bool Search(const T& data) const;
		void Print() const;
		
		shared_ptr<Node<T>> operator[](unsigned int index) const;
		unsigned int GetLength() const;
	
	private:
		unsigned int mLength;
		shared_ptr<Node<T>> mHead;
	};

	template<typename T>
	DoublyLinkedList<T>::DoublyLinkedList()
		: mLength(0)
		, mHead(nullptr)
	{
	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data)
	{
		Insert(move(data), mLength);
	}
	
	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data, unsigned int index)
	{
		shared_ptr<Node<T>> newNodePtr = make_shared<Node<T>>(move(data));

		if (mHead == nullptr)
		{
			mHead = newNodePtr;
			mLength++;
			return;
		}

		if (index >= mLength)
		{
			shared_ptr<Node<T>> ptr = mHead;
			while (ptr->Next != nullptr)
			{
				ptr = ptr->Next;
			}
			newNodePtr->Previous = ptr;
			ptr->Next = newNodePtr;
			mLength++;
			return;
		}

		if (index == 0)
		{
			mHead->Previous = newNodePtr;
			newNodePtr->Next = mHead;
			mHead = newNodePtr;
			mLength++;
			return;
		}
		shared_ptr<Node<T>> ptr = this->operator[](index);
		newNodePtr->Next = ptr;
		newNodePtr->Previous = ptr->Previous;
		shared_ptr<Node<T>> prePtr = (ptr->Previous).lock();
		prePtr->Next = newNodePtr;
		ptr->Previous = newNodePtr;
		mLength++;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Delete(const T& data)
	{
		shared_ptr<Node<T>> ptr = mHead;
		while (ptr != nullptr)
		{
			if (*(ptr->Data) == data)
			{
				break;
			}
			ptr = ptr->Next;
		}
		
		if (ptr == nullptr)
		{
			return false;
		}

		mLength--;
		if (ptr == mHead)
		{
			mHead = ptr->Next;
			return true;
		}

		shared_ptr<Node<T>> prevPtr = (ptr->Previous).lock();
		prevPtr->Next = ptr->Next;
		if (ptr->Next != nullptr)
		{
			ptr->Next->Previous = prevPtr;
		}

		return true;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Search(const T& data) const
	{
		shared_ptr<Node<T>> ptr = mHead;
		while (ptr != nullptr)
		{
			if (*(ptr->Data) == data)
			{
				break;
			}
			ptr = ptr->Next;
		}
		
		if (ptr == nullptr)
		{
			return false;
		}
		return true;
	}

	template<typename T>
	void DoublyLinkedList<T>::Print() const
	{
		shared_ptr<Node<T>> ptr = mHead;
		cout << "Doubly linked list : head -> ";
		while (ptr != nullptr)
		{
			cout << *(ptr->Data) << " -> ";
			ptr = ptr->Next;
		}
		cout << "nullptr" << endl;
	}

	template<typename T>
	std::shared_ptr<Node<T>> DoublyLinkedList<T>::operator[](unsigned int index) const
	{
		if (index >= mLength)
		{
			return nullptr;
		}

		shared_ptr<Node<T>> ptr = mHead;
		for (size_t i = 0; i < index; i++)
		{
			ptr = ptr->Next;
		}

		return ptr;
	}

	template<typename T>
	unsigned int DoublyLinkedList<T>::GetLength() const
	{
		return mLength;
	}
}

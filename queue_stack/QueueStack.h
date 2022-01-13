#pragma once
#include <queue>
#include "SmartStack.h"

namespace assignment3
{
	template<typename T>
	class QueueStack
	{
	public:
		QueueStack(unsigned int maxStackSize);
		virtual ~QueueStack();
		QueueStack(QueueStack<T>& other);
		QueueStack<T>& operator=(QueueStack<T>& rhs);

		void Enqueue(T number);
		T Peek();
		T Dequeue();
		T GetMax();
		T GetMin();
		double GetAverage();
		T GetSum();
		unsigned int GetCount();
		unsigned int GetStackCount();

	private:
		unsigned int mMaxStackSize;
		unsigned int mStackCount;
		std::queue<SmartStack<T>*> mQueueStack;
	};

	template<typename T>
	QueueStack<T>::QueueStack(unsigned int maxStackSize)
		: mMaxStackSize(maxStackSize)
		, mStackCount(0)
	{
	}
	
	template<typename T>
	QueueStack<T>::~QueueStack()
	{
		while (mQueueStack.empty() != true)
		{
			delete mQueueStack.front();
			mQueueStack.pop();
		}
	}
	
	template<typename T>
	QueueStack<T>::QueueStack(QueueStack<T>& other)
		: mMaxStackSize(other.mMaxStackSize)
		, mStackCount(other.mStackCount)
	{
		unsigned int otherSize = other.GetStackCount();
		while (otherSize != 0)
		{
			SmartStack<T>* frontStackPtr = other.mQueueStack.front();
			mQueueStack.push(new SmartStack<T>(*frontStackPtr));
			other.mQueueStack.pop();
			other.mQueueStack.push(frontStackPtr);
			otherSize--;
		}
	}
	
	template<typename T>
	QueueStack<T>& QueueStack<T>::operator=(QueueStack<T>& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		while (mQueueStack.empty() != true)
		{
			delete mQueueStack.front();
			mQueueStack.pop();
		}

		mMaxStackSize = rhs.mMaxStackSize;
		mStackCount = rhs.mStackCount;

		unsigned int otherSize = rhs.GetStackCount();
		while (otherSize != 0)
		{
			SmartStack<T>* frontStackPtr = rhs.mQueueStack.front();
			mQueueStack.push(new SmartStack<T>(*frontStackPtr));
			rhs.mQueueStack.pop();
			rhs.mQueueStack.push(frontStackPtr);
			otherSize--;
		}

		return *this;
	}

	template<typename T>
	void QueueStack<T>::Enqueue(T number)
	{
		unsigned int count = GetCount();
		if (count % mMaxStackSize == 0)
		{
			mQueueStack.push(new SmartStack<T>());
			mStackCount++;
		}
		mQueueStack.back()->Push(number);
	}
	
	template<typename T>
	T QueueStack<T>::Peek()
	{
		return mQueueStack.front()->Peek();
	}
	
	template<typename T>
	T QueueStack<T>::Dequeue()
	{
		T ret = mQueueStack.front()->Peek();
		
		mQueueStack.front()->Pop();
		if (mQueueStack.front()->GetCount() == 0)
		{
			delete mQueueStack.front();
			mQueueStack.pop();
			mStackCount--;
		}
		return ret;
	}
	
	template<typename T>
	T QueueStack<T>::GetMax()
	{
		T max = std::numeric_limits<T>::lowest();

		for (size_t i = 0; i < mStackCount; i++)
		{
			SmartStack<T>* frontPtr = mQueueStack.front();
			if (max < frontPtr->GetMax())
			{
				max = frontPtr->GetMax();
			}
			mQueueStack.pop();
			mQueueStack.push(frontPtr);
		}
		return max;
	}
	
	template<typename T>
	T QueueStack<T>::GetMin()
	{
		T min = std::numeric_limits<T>::max();

		for (size_t i = 0; i < mStackCount; i++)
		{
			SmartStack<T>* frontPtr = mQueueStack.front();
			if (min > frontPtr->GetMin())
			{
				min = frontPtr->GetMin();
			}
			mQueueStack.pop();
			mQueueStack.push(frontPtr);
		}
		return min;
	}
	
	template<typename T>
	double QueueStack<T>::GetAverage()
	{
		T sum = GetSum();
		return round(sum / static_cast<double>(GetCount()) * 1000) / 1000;
	}
	
	template<typename T>
	T QueueStack<T>::GetSum()
	{
		T sum = 0;
		for (size_t i = 0; i < mStackCount; i++)
		{
			SmartStack<T>* frontPtr = mQueueStack.front();
			sum += frontPtr->GetSum();
			mQueueStack.pop();
			mQueueStack.push(frontPtr);
		}
		return sum;
	}

	template<typename T>
	unsigned int QueueStack<T>::GetCount()
	{
		unsigned int count = 0;
		for (size_t i = 0; i < mStackCount; i++)
		{
			SmartStack<T>* frontPtr = mQueueStack.front();
			count += frontPtr->GetCount();
			mQueueStack.pop();
			mQueueStack.push(frontPtr);
		}
		return count;
	}

	template<typename T>
	unsigned int QueueStack<T>::GetStackCount()
	{
		return mStackCount;
	}
}
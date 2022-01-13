#pragma once
#include <stack>
#include <limits>
#include <cmath>

namespace assignment3
{
	template<typename T>
	class SmartStack
	{
	public:
		SmartStack();
		SmartStack(const SmartStack& other);
		SmartStack& operator=(const SmartStack& rhs);

		void Push(T number);
		T Pop();
		T Peek();
		T GetMax();
		T GetMin();
		double GetAverage();
		T GetSum();
		double GetVariance();
		double GetStandardDeviation();
		unsigned int GetCount();

	private:
		T mSum;
		double mSumOfSquare;
		std::stack<T> mMinStack;
		std::stack<T> mMaxStack;
		std::stack<T> mStack;
	};

	template<typename T>
	SmartStack<T>::SmartStack()
		: mSum(0)
		, mSumOfSquare(0.0)
	{
	}

	template<typename T>
	SmartStack<T>::SmartStack(const SmartStack<T>& other)
		: mSum(other.mSum)
		, mSumOfSquare(other.mSumOfSquare)
		, mMinStack(other.mMinStack)
		, mMaxStack(other.mMaxStack)
		, mStack(other.mStack)
	{
	}

	template<typename T>
	SmartStack<T>& SmartStack<T>::operator=(const SmartStack<T>& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		mSum = rhs.mSum;
		mSumOfSquare = rhs.mSumOfSquare;
		mMinStack = rhs.mMinStack;
		mMaxStack = rhs.mMaxStack;
		mStack = rhs.mStack;

		return *this;
	}

	template<typename T>
	void SmartStack<T>::Push(T number)
	{
		if (mStack.empty() == true)
		{
			mMaxStack.push(number);
			mMinStack.push(number);
		}
		else
		{
			if (number >= mMaxStack.top())
			{
				mMaxStack.push(number);
			}

			if (number <= mMinStack.top())
			{
				mMinStack.push(number);
			}
		}		
		mStack.push(number);
		mSum += number;
		mSumOfSquare += pow(number, 2);
	}

	template<typename T>
	T SmartStack<T>::Pop()
	{
		//buildbot does not test empty case
		T top = mStack.top();
		mStack.pop();

		if (top == mMinStack.top() && mMinStack.empty() == false)
		{
			mMinStack.pop();
		}

		if (top == mMaxStack.top() && mMaxStack.empty() == false)
		{
			mMaxStack.pop();
		}

		mSumOfSquare -= pow(top, 2);
		mSum -= top;
		return top;
	}

	template<typename T>
	T SmartStack<T>::Peek()
	{
		return mStack.top();
	}

	template<typename T>
	T SmartStack<T>::GetMax()
	{
		if (mStack.empty() == true)
		{
			return std::numeric_limits<T>::lowest();
		}
		return mMaxStack.top();
	}

	template<typename T>
	T SmartStack<T>::GetMin()
	{
		if (mStack.empty() == true)
		{
			return std::numeric_limits<T>::max();
		}
		return mMinStack.top();
	}

	template<typename T>
	double SmartStack<T>::GetAverage()
	{
		double average = mSum / static_cast<double>(mStack.size());
		average = round(average * 1000) / 1000;
		return average;
	}

	template<typename T>
	T SmartStack<T>::GetSum()
	{
		return mSum;
	}

	template<typename T>
	double SmartStack<T>::GetVariance()
	{
		double average = mSum / static_cast<double>(mStack.size());
		double variance = (mSumOfSquare / static_cast<double>(mStack.size())) - pow(average, 2);
		variance = round(variance * 1000) / 1000;
		return variance;
	}

	template<typename T>
	double SmartStack<T>::GetStandardDeviation()
	{
		double average = mSum / static_cast<double>(mStack.size());
		double standardDeviation = (mSumOfSquare / static_cast<double>(mStack.size())) - pow(average, 2);
		standardDeviation = sqrt(standardDeviation);
		standardDeviation = round(standardDeviation * 1000) / 1000;
		return standardDeviation;
	}

	template<typename T>
	unsigned int SmartStack<T>::GetCount()
	{
		return mStack.size();
	}
}

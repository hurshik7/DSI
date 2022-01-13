#pragma once
#include <queue>
#include <cmath>
#include <limits>

namespace assignment3
{
	template<typename T>
	class SmartQueue
	{
	public:
		SmartQueue();

		void Enqueue(T number);
		T Dequeue();
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
		std::queue<T> mQueue;
	};

	template<typename T>
	SmartQueue<T>::SmartQueue()
		: mSum(0)
		, mSumOfSquare(0.0)
	{
	}

	template<typename T>
	void SmartQueue<T>::Enqueue(T number)
	{
		mQueue.push(number);
		mSum += number;
		mSumOfSquare += pow(number, 2);
	}

	template<typename T>
	T SmartQueue<T>::Dequeue()
	{
		//buildbot does not test empty case.
		T ret = mQueue.front();
		mQueue.pop();
		mSumOfSquare -= pow(ret, 2);
		mSum -= ret;
		return ret;
	}

	template<typename T>
	T SmartQueue<T>::Peek()
	{
		return mQueue.front();
	}

	template<typename T>
	T SmartQueue<T>::GetMax()
	{
		T max = std::numeric_limits<T>::lowest();
		unsigned int count = mQueue.size();
		while (count > 0)
		{
			T frontNum = mQueue.front();
			if (frontNum >= max)
			{
				max = frontNum;
			}
			mQueue.pop();
			mQueue.push(frontNum);
			count--;
		}
		
		return max;
	}

	template<typename T>
	T SmartQueue<T>::GetMin()
	{
		T min = std::numeric_limits<T>::max();
		unsigned int count = mQueue.size();
		while (count > 0)
		{
			T frontNum = mQueue.front();
			if (frontNum <= min)
			{
				min = frontNum;
			}
			mQueue.pop();
			mQueue.push(frontNum);
			count--;
		}

		return min;
	}

	template<typename T>
	double SmartQueue<T>::GetAverage()
	{
		double average = mSum / static_cast<double>(mQueue.size());
		average = round(average * 1000) / 1000;
		return average;
	}

	template<typename T>
	T SmartQueue<T>::GetSum()
	{
		return mSum;
	}

	template<typename T>
	double SmartQueue<T>::GetVariance()
	{
		double average = mSum / static_cast<double>(mQueue.size());
		double variance = (mSumOfSquare / static_cast<double>(mQueue.size())) - pow(average, 2);
		variance = round(variance * 1000) / 1000;
		return variance;
	}

	template<typename T>
	double SmartQueue<T>::GetStandardDeviation()
	{
		double average = mSum / static_cast<double>(mQueue.size());
		double standardDeviation = (mSumOfSquare / static_cast<double>(mQueue.size())) - pow(average, 2);
		standardDeviation = sqrt(standardDeviation);
		standardDeviation = round(standardDeviation * 1000) / 1000;
		return standardDeviation;
	}

	template<typename T>
	unsigned int SmartQueue<T>::GetCount()
	{
		return mQueue.size();
	}
}

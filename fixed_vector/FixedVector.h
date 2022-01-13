#pragma once

namespace lab8
{
	template<typename T, size_t N>
	class FixedVector
	{
	public:
		FixedVector();
		virtual ~FixedVector();
		FixedVector(const FixedVector<T, N>& other);
		FixedVector<T, N>& operator=(const FixedVector<T, N>& rhs);

		bool Add(const T& t);
		bool Remove(const T& t);
		const T& Get(unsigned int index) const;
		T& operator[](unsigned int index);
		int GetIndex(const T& t) const;
		size_t GetSize() const;
		size_t GetCapacity() const;

	private:
		T mArr[N];
		size_t mCount;
	};

	template<typename T, size_t N>
	FixedVector<T, N>::FixedVector()
		: mCount(0)
	{
	}

	template<typename T, size_t N>
	FixedVector<T, N>::~FixedVector()
	{
	}

	template<typename T, size_t N>
	FixedVector<T, N>::FixedVector(const FixedVector<T, N>& other)
	{
		mCount = other.mCount;
		for (size_t i = 0; i < N; i++)
		{
			mArr[i] = other.mArr[i];
		}
	}

	template<typename T, size_t N>
	FixedVector<T, N>& FixedVector<T, N>::operator=(const FixedVector<T, N>& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		mCount = rhs.mCount;
		for (size_t i = 0; i < N; i++)
		{
			mArr[i] = rhs.mArr[i];
		}

		return *this;
	}

	template<typename T, size_t N>
	bool FixedVector<T, N>::Add(const T& t)
	{
		if (mCount == N)
		{
			return false;
		}
		mArr[mCount] = t;
		mCount++;
		return true;
	}

	template<typename T, size_t N>
	bool FixedVector<T, N>::Remove(const T& t)
	{
		int index = -1;
		for (size_t i = 0; i < mCount; i++)
		{
			if (mArr[i] == t)
			{
				index = i;
				break;
			}
		}

		if (index == -1)
		{
			return false;
		}

		for (size_t i = static_cast<size_t>(index); i < mCount - 1; i++)
		{
			mArr[i] = mArr[i + 1];
		}
		mCount--;
		return true;
	}

	template<typename T, size_t N>
	const T& FixedVector<T, N>::Get(unsigned int index) const
	{
		//index is always within range
		return mArr[index];
	}

	template<typename T, size_t N>
	T& FixedVector<T, N>::operator[](unsigned int index)
	{
		//index is always within range
		return mArr[index];
	}

	template<typename T, size_t N>
	int FixedVector<T, N>::GetIndex(const T& t) const
	{
		int index = -1;
		for (size_t i = 0; i < mCount; i++)
		{
			if (mArr[i] == t)
			{
				index = static_cast<int>(i);
				break;
			}
		}
		return index;
	}

	template<typename T, size_t N>
	size_t FixedVector<T, N>::GetSize() const
	{
		return mCount;
	}

	template<typename T, size_t N>
	size_t FixedVector<T, N>::GetCapacity() const
	{
		return N;
	}
}
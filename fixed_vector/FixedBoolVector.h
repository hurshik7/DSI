#pragma once

namespace lab8
{
	template<size_t N>
	class FixedVector<bool, N>
	{
	public:
		FixedVector();
		FixedVector(const FixedVector<bool, N>& bOther);
		FixedVector<bool, N>& operator=(const FixedVector<bool, N>& bRhs);

		bool Add(bool bT);
		bool Remove(bool bT);
		bool Get(unsigned int index) const;
		bool operator[](unsigned int index);
		int GetIndex(bool bT) const;
		size_t GetSize() const;
		size_t GetCapacity() const;

	private:
		unsigned int mData[N / 32 + 1];
		size_t mCount;
	};

	template<size_t N>
	FixedVector<bool, N>::FixedVector()
		: mCount(0)
	{
		for (size_t i = 0; i < N / 32 + 1; i++)
		{
			mData[i] = 0;
		}
	}

	template<size_t N>
	FixedVector<bool, N>::FixedVector(const FixedVector<bool, N>& bOther)
	{
		mCount = bOther.mCount;
		for (size_t i = 0; i < N / 32 + 1; i++)
		{
			mData[i] = bOther.mData[i];
		}
	}

	template<size_t N>
	FixedVector<bool, N>& FixedVector<bool, N>::operator=(const FixedVector<bool, N>& bRhs)
	{
		if (this == &bRhs)
		{
			return *this;
		}

		mCount = bRhs.mCount;
		for (size_t i = 0; i < N / 32 + 1; i++)
		{
			mData[i] = bRhs.mData[i];
		}

		return *this;
	}

	template<size_t N>
	bool FixedVector<bool, N>::Add(bool bT)
	{
		if (mCount == N)
		{
			return false;
		}
		
		if (bT == true)
		{
			mData[mCount / 32] |= (1 << (mCount % 32));
		}
		mCount++;
		return true;
	}

	template<size_t N>
	bool FixedVector<bool, N>::Remove(bool bT)
	{
		int index = -1;
		for (size_t i = 0; i < mCount; i++)
		{
			if (Get(i) == bT)
			{
				index = static_cast<int>(i);
				break;
			}
		}

		if (index == -1)
		{
			return false;
		}
	
		for (int i = index + 1; i < static_cast<int>(mCount); i++)
		{
			int prev = i - 1;
			int curr = i;

			if (mData[curr / 32] & (1 << (curr % 32)))
			{
				mData[prev / 32] |= (1 << (prev % 32));
			}
			else
			{
				unsigned int allOnes = 0xFFFFFFFF;
				allOnes ^= (1 << (prev % 32));
				mData[prev / 32] &= allOnes;
			}
		}
		
		mCount--;
		return true;
	}

	template<size_t N>
	bool FixedVector<bool, N>::Get(unsigned int index) const
	{
		//index is always within range
		return (mData[index / 32] & (1 << (index % 32))) != 0;
	}

	template<size_t N>
	bool FixedVector<bool, N>::operator[](unsigned int index)
	{
		//index is always within range
		return Get(index);
	}

	template<size_t N>
	int FixedVector<bool, N>::GetIndex(bool bT) const
	{
		int index = -1;
		for (size_t i = 0; i < mCount; i++)
		{
			if (Get(i) == bT)
			{
				index = static_cast<int>(i);
				break;
			}
		}
		return index;
	}

	template<size_t N>
	size_t FixedVector<bool, N>::GetSize() const
	{
		return mCount;
	}

	template<size_t N>
	size_t FixedVector<bool, N>::GetCapacity() const
	{
		return N;
	}
}
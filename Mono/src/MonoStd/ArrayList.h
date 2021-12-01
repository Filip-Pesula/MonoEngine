#pragma once
#include <cstdint>
#include <cstring>
template<typename T>
class ArrayList
{
	T* heepArray;
	uint32_t mSize;
	uint32_t mHeepSize;
	uint32_t mIncrement;
	void resize()
	{
		T* newHeepArray;
		newHeepArray = new T[mHeepSize + mIncrement];
		std::memcpy(newHeepArray, heepArray,sizeof(T)*mHeepSize);
		delete[] heepArray;
		heepArray = newHeepArray;
		delete[] newHeepArray;
		mHeepSize += mIncrement;
	}
public:
	ArrayList()
	{
		mIncrement = 1;
		mSize = 0;
		mHeepSize = 1;
		heepArray = new T[mIncrement];
	}
	ArrayList(uint32_t increment)
	{
		mIncrement = increment;
		mSize = 0;
		mHeepSize = increment;
		heepArray = new T[mIncrement];
	}
	void add(T obj)
	{
		if (mSize == mHeepSize)
		{
			resize();
		}
		heepArray[mSize] = obj;
		mSize++;
	}
	T get(uint32_t index)
	{
		return heepArray[index];
	}
	~ArrayList()
	{
		delete[] heepArray;
	}
};
template<typename K>
class RefArrayList
{
	ArrayList<K> list;
	ArrayList<ArrayList<K>> listRef;
};
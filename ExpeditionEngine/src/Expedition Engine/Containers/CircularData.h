#ifndef CIRCULAR_DATA
#define CIRCULAR_DATA

#include <assert.h>

class CircularData
{
public:
	CircularData() = delete;
	CircularData(const int& sizeOfArray)
	{
		mask = sizeOfArray - 1u;
		size = sizeOfArray;
	}
	CircularData(const CircularData&) = delete;
	CircularData& operator= (const CircularData&) = delete;
	~CircularData() = default;

	int operator++()
	{
		++index;

		index = index & mask;

		return index;
	}

	bool operator==(const CircularData& other)
	{
		assert(size == other.size);
		return (index == other.index);
	}

	bool operator!=(const CircularData& other)
	{
		assert(size == other.size);
		return (index != other.index);
	}

	const int& GetIndex() const
	{
		return index;
	}

private:
	unsigned int mask;
	int index = 0;
	int size = 0;
};

#endif // !CIRCULAR_DATA

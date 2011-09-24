#ifndef _VECTORLIST_H
#define _VECTORLIST_H
#include <string.h>

#define VECLST_INDEXERROR	0xffffffff

template <class _Ty>

class VectorList
{
	typedef VectorList<_Ty> _Myt;
public:
	VectorList()
	{
		item = NULL;
		valid = NULL;
		init(0);
	}
	VectorList(unsigned long count)
	{
		item = NULL;
		valid = NULL;
		init(count);
	}
	~VectorList()
	{
		clear();
	}

	void clear()
	{
		if (item)
		{
			delete[] item;
			item = NULL;
		}
		if (valid)
		{
			delete[] valid;
			valid = NULL;
		}
		index = 0;
	}
	void clear_item()
	{
		init(capacity);
	}
	void init(unsigned long count)
	{
		clear();
		capacity = count;
		if (capacity > 0)
		{
			item = new _Ty[capacity];
			valid = new bool[capacity];
		}
		if (valid)
		{
			memset(valid, 0, sizeof(bool) * capacity);
		}
		ibegin = 0;
		iend = 0;
		size = 0;
		zero = 0;
		index = 0;
		pushedindex = 0;
//		clear_item();
	}


	_Ty * push()
	{
		if (!isInRange())
		{
			return NULL;
		}
		pop();
		if (!size)
		{
			size++;
		}
		valid[index] = true;
		return &item[index];
	}
	_Ty * push(const _Ty &_item)
	{
		if (!isInRange())
		{
			return NULL;
		}
		memcpy(push(), &_item, sizeof(_Ty));
		return &item[index];
	}

	_Ty * push_back()
	{
		pushIndex();
		toEnd();
		if (size)
		{
			toNext();
		}
		iend = index;
		if (size && ibegin == iend)
		{
			ibegin = toNext();
			toEnd();
			pop();
		}
		else
		{
			size++;
		}
		valid[index] = true;
		return &item[index];
	}
	_Ty * push_back(const _Ty & _item)
	{
		memcpy(push_back(), &_item, sizeof(_Ty));
		return &item[iend];
	}
	_Ty * push_front()
	{
		pushIndex();
		toBegin();
		if (size)
		{
			toPrev();
		}
		ibegin = index;
		if (size && ibegin == iend)
		{
			iend = toPrev();
			pop();
		}
		else
		{
			size++;
		}
		valid[index] = true;
		return &item[index];
	}
	_Ty * push_front(const _Ty & _item)
	{
		memcpy(push_front(), &_item, sizeof(_Ty));
		return &item[ibegin];
	}
	unsigned long pop()
	{
		if (!size || !valid[index])
		{
			return index;
		}

		unsigned long _index = index;
		valid[index] = false;
		item[index].~_Ty();
		if (index == ibegin)
		{
			size--;
			if (size)
			{
				ibegin = toNext();
				while (!valid[index])
				{
					size--;
					if (!size)
					{
						break;
					}
					ibegin = toNext();
				}
			}
		}
		else if (index == iend)
		{
			size--;
			if (size)
			{
				iend = toPrev();
				while (!valid[index])
				{
					size--;
					if (!size)
					{
						break;
					}
					iend = toPrev();
				}
			}
		}
		index = _index;
		return index;
	}
	unsigned long pop(unsigned long _index)
	{
		unsigned long _tindex = index;
		if (toIndex(_index) == VECLST_INDEXERROR)
		{
			return VECLST_INDEXERROR;
		}
		pop();
		index = _tindex;
		return _index;
	}
	unsigned long pop_back()
	{
		return pop(iend);
	}
	unsigned long pop_front()
	{
		return pop(ibegin);
	}
	unsigned long toBegin()
	{
		index = ibegin;
		return index;
	}
	unsigned long toEnd()
	{
		index = iend;
		return index;
	}
	unsigned long toNext()
	{
		if (index < capacity - 1)
		{
			index++;
		}
		else
		{
			index = zero;
		}
		return index;
	}
	unsigned long toNext(bool sizeonly)
	{
		if (sizeonly)
		{
			unsigned long _zero = zero;
			unsigned long _capacity = capacity;
			zero = ibegin;
			capacity = iend + 1;
			toNext();
			if (!isInRange())
			{
				index = zero;
			}
			zero = _zero;
			capacity = _capacity;
			return index;
		}
		return toNext();
	}
	unsigned long toPrev()
	{
		if (index > zero)
		{
			index--;
		}
		else
		{
			index = capacity - 1;
		}
		return index;
	}
	unsigned long toPrev(bool sizeonly)
	{
		if (sizeonly)
		{
			unsigned long _zero = zero;
			unsigned long _capacity = capacity;
			zero = ibegin;
			capacity = iend + 1;
			toPrev();
			if (!isInRange())
			{
				index = capacity - 1;
			}
			zero = _zero;
			capacity = _capacity;
			return index;
		}
		return toPrev();
	}
	unsigned long toIndex(unsigned long _index)
	{
		if (_index >= capacity)
		{
			return VECLST_INDEXERROR;
		}
		index = _index;
		return index;
	}
	_Ty * begin()
	{
		return &item[ibegin];
	}
	_Ty * end()
	{
		return &item[iend];
	}
	_Ty * next()
	{
		toNext();
		return &item[index];
	}
	_Ty * prev()
	{
		toPrev();
		return &item[index];
	}
	bool isBegin()
	{
		if (index == ibegin)
		{
			return true;
		}
		return false;
	}
	bool isEnd()
	{
		if (index == iend)
		{
			return true;
		}
		return false;
	}
	bool isValid()
	{
		return valid[index];
	}
	bool isInRange()
	{
		if (!size)
		{
			return false;
		}
		if (index > capacity)
		{
			return false;
		}

		if (index == ibegin || index == iend)
		{
			return true;
		}
		if ((ibegin < iend) && (index > ibegin && index < iend))
		{
			return true;
		}
		if ((ibegin > iend) && (index > ibegin || index < iend))
		{
			return true;
		}
		return false;
	}
	unsigned long getIndex()
	{
		return index;
	}
	unsigned long getBeginIndex()
	{
		return ibegin;
	}
	unsigned long getEndIndex()
	{
		return iend;
	}
	unsigned long getSize()
	{
		return size;
	}
	unsigned long getCapacity()
	{
		return capacity;
	}
private:
	void pushIndex()
	{
		pushedindex = index;
	}
public:
	void popIndex()
	{
		index = pushedindex;
	}

	_Ty & operator*() const
	{
		return item[index];
	}
	_Ty & operator[](unsigned long _index) const
	{
		if (_index < capacity)
		{
			return item[_index];
		}
		else
		{
			return item[capacity - 1];
		}
	}

public:
	_Ty * item;
	bool * valid;
	unsigned long index;
	unsigned long pushedindex;
	unsigned long ibegin;
	unsigned long zero;
	unsigned long iend;
	unsigned long size;
	unsigned long capacity;
};

#endif
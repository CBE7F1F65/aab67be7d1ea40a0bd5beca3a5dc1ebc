#ifndef _VECTORLIST_H
#define _VECTORLIST_H

#include <string.h>
#ifdef __WIN32
#include <windows.h>
#else
#ifndef DWORD
typedef unsigned long	DWORD;
#endif
#ifndef NULL
#define NULL	(0)
#endif
#ifndef ZeroMemory
#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
#endif
#endif

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
	VectorList(DWORD count)
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
	void init(DWORD count)
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
			ZeroMemory(valid, sizeof(bool) * capacity);
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
	DWORD pop()
	{
		if (!size || !valid[index])
		{
			return index;
		}

		DWORD _index = index;
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
	DWORD pop(DWORD _index)
	{
		DWORD _tindex = index;
		if (toIndex(_index) == VECLST_INDEXERROR)
		{
			return VECLST_INDEXERROR;
		}
		pop();
		index = _tindex;
		return _index;
	}
	DWORD pop_back()
	{
		return pop(iend);
	}
	DWORD pop_front()
	{
		return pop(ibegin);
	}
	DWORD toBegin()
	{
		index = ibegin;
		return index;
	}
	DWORD toEnd()
	{
		index = iend;
		return index;
	}
	DWORD toNext()
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
	DWORD toNext(bool sizeonly)
	{
		if (sizeonly)
		{
			DWORD _zero = zero;
			DWORD _capacity = capacity;
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
	DWORD toPrev()
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
	DWORD toPrev(bool sizeonly)
	{
		if (sizeonly)
		{
			DWORD _zero = zero;
			DWORD _capacity = capacity;
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
	DWORD toIndex(DWORD _index)
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
	DWORD getIndex()
	{
		return index;
	}
	DWORD getBeginIndex()
	{
		return ibegin;
	}
	DWORD getEndIndex()
	{
		return iend;
	}
	DWORD getSize()
	{
		return size;
	}
	DWORD getCapacity()
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
	_Ty & operator[](DWORD _index) const
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
	DWORD index;
	DWORD pushedindex;
	DWORD ibegin;
	DWORD zero;
	DWORD iend;
	DWORD size;
	DWORD capacity;
};

#endif
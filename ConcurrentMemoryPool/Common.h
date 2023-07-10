#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <assert.h>

using std::cout;
using std::endl;

void*& NextObj(void* obj)
{
	return *(void**)obj;
}
// �����зֺõ�С����������
class FreeList
{
public:
	void Push(void* obj)
	{
		assert(obj);
		// ͷ�����������
		NextObj(obj) = _freeList;
		_freeList = obj;
	}
	void* Pop()
	{
		assert(_freeList);
		void* obj = _freeList;
		_freeList = NextObj(_freeList);
	}
private:
	void* _freeList;
};
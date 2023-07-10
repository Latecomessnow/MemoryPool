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
// 管理切分好的小块自由链表
class FreeList
{
public:
	void Push(void* obj)
	{
		assert(obj);
		// 头插进自由链表
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
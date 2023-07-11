#pragma once

#include "Common.h"

class ThreadCache
{
public:
	void* Allocate(size_t size);
	void Deallocate(void* ptr, size_t size);
	// 从中心缓存获取对象
	void* FetchFromCentralCache(size_t index, size_t size);
private:
	// 线程缓存是一个具有256个桶的数组，每一个桶里面存的都是自由链表
	FreeList _freeLists[NFREELIST];
};

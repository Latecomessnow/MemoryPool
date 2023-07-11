#define _CRT_SECURE_NO_WARNINGS 1

#include "ThreadCache.h"

void* ThreadCache::Allocate(size_t size)
{
	assert(size > 0);
	assert(size <= MAX_BYTES);
	// 按照申请内存空间的字节数去对齐到相应位置的ThreadCache的桶位置
	size_t alignSize = SizeClass::RoundUp(size);
	size_t index = SizeClass::Index(alignSize);
	if (!_freeLists[index].Empty())
		return _freeLists[index].Pop();
	else
		return FetchFromCentralCache(index, alignSize);
}

// 从中心缓存获取对象
void* ThreadCache::FetchFromCentralCache(size_t index, size_t size)
{
	// ... 
	return nullptr;
}

void ThreadCache::Deallocate(void* ptr, size_t size)
{
	assert(ptr);
	assert(size <= MAX_BYTES);
	size_t index = SizeClass::Index(size);
	// 头插进ThreadCache对应位置的桶的自由链表中
	_freeLists[index].Push(ptr);
}
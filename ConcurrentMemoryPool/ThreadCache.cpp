#define _CRT_SECURE_NO_WARNINGS 1

#include "ThreadCache.h"

void* ThreadCache::Allocate(size_t size)
{
	assert(size > 0);
	assert(size <= MAX_BYTES);
	// ���������ڴ�ռ���ֽ���ȥ���뵽��Ӧλ�õ�ThreadCache��Ͱλ��
	size_t alignSize = SizeClass::RoundUp(size);
	size_t index = SizeClass::Index(alignSize);
	if (!_freeLists[index].Empty())
		return _freeLists[index].Pop();
	else
		return FetchFromCentralCache(index, alignSize);
}

// �����Ļ����ȡ����
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
	// ͷ���ThreadCache��Ӧλ�õ�Ͱ������������
	_freeLists[index].Push(ptr);
}
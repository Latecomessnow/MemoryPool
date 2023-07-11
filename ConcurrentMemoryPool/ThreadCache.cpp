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
		return _freeLists->Pop();
	else
		return FetchFromCentralCache(index, alignSize);
}

// �����Ļ����ȡ����
void* FetchFromCentralCache(size_t index, size_t size)
{

}

void ThreadCache::Deallocate(void* ptr, size_t size)
{

}
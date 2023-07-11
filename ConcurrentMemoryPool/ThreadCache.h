#pragma once

#include "Common.h"

class ThreadCache
{
public:
	void* Allocate(size_t size);
	void Deallocate(void* ptr, size_t size);
	// �����Ļ����ȡ����
	void* FetchFromCentralCache(size_t index, size_t size);
private:
	// �̻߳�����һ������256��Ͱ�����飬ÿһ��Ͱ�����Ķ�����������
	FreeList _freeLists[NFREELIST];
};

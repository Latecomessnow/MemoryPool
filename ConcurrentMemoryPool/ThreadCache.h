#pragma once

#include "Common.h"

class ThreadCache
{
public:
	void* Allocate(size_t size);
	void Deallocate(void* ptr, size_t size);
private:
	// �̻߳�����һ������256��Ͱ�����飬ÿһ��Ͱ�����Ķ�����������
	FreeList _freeLists[256];
};

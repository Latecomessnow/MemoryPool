#pragma once

#include "Common.h"
#include "ThreadCache.h"

static void* ConcurrentAlloc(size_t size)
{
	// 通过线程局部缓存，每个线程无锁的获取自己的ThreadCache对象
	if (pTLSThreadCache == nullptr)
		pTLSThreadCache = new ThreadCache;
	cout << std::this_thread::get_id() << "[线程ID]"  << " : " << pTLSThreadCache << "[TLS变量指针]" << endl;
	return pTLSThreadCache->Allocate(size);
}

static void ConcurrentFree(void* ptr, size_t size)
{
	// 线程释放内存时，一定是已经申请过了自己的TLS变量
	assert(pTLSThreadCache);
	assert(ptr);
	pTLSThreadCache->Deallocate(ptr, size); // 后面再改，释放内存时不需要指定该内存空间的大小
}

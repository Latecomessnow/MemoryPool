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

// TLS thread local storage
// 线程局部存储，可以实现每个线程都有自己的ThreadCache对象，然后中心缓存、页缓存这些就共享的
static _declspec(thread) ThreadCache* pTLSThreadCache = nullptr;

// 注
// 如果TLS变量不加static修饰的话，因为ThreadCache.h会在多个.cpp文件中展开，就会形成多个TLS变量
// 导致编译后多个变量名相同编译失败，所以此处用static修饰，外部链接属性变为内部链接属性
// TLS变量只在当前文件中展开
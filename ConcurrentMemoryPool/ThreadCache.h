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

// TLS thread local storage
// �ֲ߳̾��洢������ʵ��ÿ���̶߳����Լ���ThreadCache����Ȼ�����Ļ��桢ҳ������Щ�͹����
static _declspec(thread) ThreadCache* pTLSThreadCache = nullptr;

// ע
// ���TLS��������static���εĻ�����ΪThreadCache.h���ڶ��.cpp�ļ���չ�����ͻ��γɶ��TLS����
// ���±��������������ͬ����ʧ�ܣ����Դ˴���static���Σ��ⲿ�������Ա�Ϊ�ڲ���������
// TLS����ֻ�ڵ�ǰ�ļ���չ��
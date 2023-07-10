#pragma once

#include <iostream>
#include <vector>
#include <time.h>

using std::cout;
using std::endl;

//// 1. 定长内存池
//template<size_t N> // 每次申请空间都是N个字节的空间
//class ObjectPool
//{
//private:
//
//};

// 2. 定长内存池
template<class T> // 每次申请空间都是一个T对象的空间
class ObjectPool
{
public:
	T* New()
	{
		T* obj = nullptr;
		// 优先使用还回来的内存块对象
		if (_freeList)
		{
			void* next = *((void**)_freeList);
			obj = (T*)_freeList;
			_freeList = next;
		}
		else
		{
			//if (_memory == nullptr)
			if (_remainBytes < sizeof(T)) // 剩余空间不够开辟一个T对象，将剩下的内存碎片丢弃，重新开辟大块内存
			{
				_remainBytes = 128 * 1024;
				_memory = (char*)malloc(_remainBytes);
				if (_memory == nullptr)
					throw std::bad_alloc();
			}
			obj = (T*)_memory;
			// 防止申请的空间不够存一个指针的大小
			size_t objSize = sizeof(T) < sizeof(void*) ? sizeof(void*) : sizeof(T);
			_memory += objSize;
			_remainBytes -= objSize;
		}
		// 定位new，显示调用T的构造函数初始化
		new(obj)T;
		return obj;
	}
	void Delete(T* obj)
	{
		// 显示调用析构函数清理对象
		obj->~T();

		// 头插
		*(void**)obj = _freeList;
		_freeList = obj;
		//if (_freeList == nullptr)
		//{
		//	_freeList = obj;
		//	*(void**)_freeList = nullptr;
		//}
		//else
		//{
		//	*(void**)obj = _freeList;
		//	_freeList = obj;
		//}
	}
private:
	//void* _memory;   // 指向定长内存池向系统申请的大块内存空间的起始地址
	char* _memory = nullptr;   // 指向定长内存池向系统申请的大块内存空间的起始地址
	size_t _remainBytes = 0;   // 内存池中大块内存的剩余字节数
	void* _freeList = nullptr; // 指向回收内存空间的自由链表头指针
};


/*****************************************测试******************************************/
struct TreeNode
{
	int _val;
	TreeNode* _left;
	TreeNode* _right;

	TreeNode()
		:_val(0)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

void TestObjectPool()
{
	// 申请释放的轮次
	const size_t Rounds = 5;

	// 每轮申请释放多少次
	const size_t N = 100000;

	std::vector<TreeNode*> v1;
	v1.reserve(N);

	size_t begin1 = clock();
	for (size_t j = 0; j < Rounds; ++j)
	{
		for (int i = 0; i < N; ++i)
		{
			v1.push_back(new TreeNode);
		}
		for (int i = 0; i < N; ++i)
		{
			delete v1[i];
		}
		v1.clear();
	}

	size_t end1 = clock();

	std::vector<TreeNode*> v2;
	v2.reserve(N);

	ObjectPool<TreeNode> TNPool;
	size_t begin2 = clock();
	for (size_t j = 0; j < Rounds; ++j)
	{
		for (int i = 0; i < N; ++i)
		{
			v2.push_back(TNPool.New());
		}
		for (int i = 0; i < N; ++i)
		{
			TNPool.Delete(v2[i]);
		}
		v2.clear();
	}
	size_t end2 = clock();

	cout << "new cost time:" << end1 - begin1 << endl;
	cout << "object pool cost time:" << end2 - begin2 << endl;
}
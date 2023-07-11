#define _CRT_SECURE_NO_WARNINGS 1

#include "ObjectPool.h"
#include "CurrentAlloc.h"

void Alloc1()
{
	for (size_t i = 0; i < 5; i++)
	{
		void* ptr = ConcurrentAlloc(6);
	}
}
void Alloc2()
{
	for (size_t i = 0; i < 5; i++)
	{
		void* ptr = ConcurrentAlloc(7);
	}
}
void TestTLS()
{
	std::thread t1(Alloc1);
	std::thread t2(Alloc2);

	t1.join();
	t2.join();
}

int main()
{
	TestTLS();
	//TestObjectPool();
	return 0;
}
/*
	循环顺序队列：实现顺序队列空间更有效的使用(rear%MAXSIZE/top%MAXSIZE: 实现循环（ 0->MAXSIZE-1 ）)

		1. 队尾标识到队列尾时，转为向头部入队
		2. 空队列：（rear == top）
		   满队列：牺牲队列的一个存储位置，当队尾到队头只有一个位置时认为队列满
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>

#define MAXSIZE 5

typedef char elemType;
typedef struct cycleQueue
{
	elemType data[MAXSIZE];
	int top;// 队头标识（可出队元素位置）,因为循环因素并不是真实数据数组的下标（top%MAXSIZE才是）
	int rear;// 队尾标识（可入队元素位置）	
}cycleQueue;

void initCycQueue(cycleQueue* cycQ)
{
	cycQ->top = 0;
	cycQ->rear = 0;
}

void enqueue(cycleQueue* cycQ, elemType e)
{
	// 入队是要操作队尾标识rear（1.(rear + 1)为了空出一个存储位置 ; 2. %MAXSIZE（取余）：0->MAXSIZE-1 循环 ）
	if ((cycQ->rear + 1)%MAXSIZE == cycQ->top)
	{
		printf("队列已满！！\n");
		return;
	}
	cycQ->data[cycQ->rear%MAXSIZE] = e;
	cycQ->rear++;
	printf("数据入队成功：%c\n", e);
}

void dequeue(cycleQueue* cycQ)
{
	// 出队操作对头标识top（当队头top与队尾rear标识再度重合时，队列为空）
	if (cycQ->top%MAXSIZE == cycQ->rear)
	{
		printf("队列已空！！\n");
		return;
	}
	//出队元素
	elemType e = cycQ->data[cycQ->top%MAXSIZE];
	cycQ->top++;
	printf("出队元素为：%c\n", e);
}

int main()
{
	cycleQueue *cycQ = (cycleQueue*)malloc(sizeof(cycleQueue));
	initCycQueue(cycQ);
	elemType e = 'a';
	for (int i = 0; i < 5; ++i)
	{
		enqueue(cycQ, e);
		e = e + 1;
	}
	
	dequeue(cycQ);	
	enqueue(cycQ, 'f');
	return 1;
}
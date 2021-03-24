/***************************************************************************
*	    		数据结构：逻辑结构 + 物理结构（存储结构）
*
* 1.逻辑结构：
*	- 线性结构：线性表（“一对一”)（List, queue, stack..）
*	- 非线性结构：集合（"互斥"），树（"一对多"），图（“多对多”）..
*
* 2.物理结构（存储结构）：顺序存储，链式存储
*
* ------------------ 一. 线性表：顺序队列（顺序表模拟实现的队列结构） ---------------
* （3）- 栈与队列：不允许随意位置的插入和删除操作
*		・队列（stack）：Fast In First Out(FIFO-先进先出)
*			-> 只允许在一侧进行“插入"（enQueue：入队），
*			-> 另一侧进行"删除"（deQueue：出队）”
*			操作：（ 队头:top; 队尾:rear ）
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>

#define MAXSIZE 4

typedef char elemType;
typedef struct Queue
{
	elemType data[MAXSIZE];
	int top;//队头标识（可出队元素位置）
	int rear;//队尾标识（可插入元素位置）
}Queue;

Queue* initQueue(Queue* queue)
{
	queue->top = 0;
	queue->rear = 0;
	return queue;
}

Queue* enQueue(Queue* queue, elemType e)
{
	if (queue->rear == MAXSIZE)
	{
		printf("队列已满，无法入队！！\n");
		return queue;
	}
	queue->data[queue->rear++] = e;
	printf("入队元素：%c\n", e);
	return queue;
}

Queue* deQueue(Queue* queue)
{
	if (queue->top == queue->rear)
	{
		printf("空队列！！\n");
	}else{
		
		elemType e = queue->data[queue->top];
		printf("出队元素：%c\n", e);
		queue->top++;
	}
	return queue;
}

int main()
{
	// 结构体指针的初始化（内存分配）
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue = initQueue(queue);
	queue = enQueue(queue, 'a');
	queue = enQueue(queue, 'b');
	queue = enQueue(queue, 'c');
	queue = enQueue(queue, 'd');
	queue = enQueue(queue, 'e');
	for (int i = 0; i < 6; ++i)
	{
		queue = deQueue(queue);
	}
	
	return 0;
}

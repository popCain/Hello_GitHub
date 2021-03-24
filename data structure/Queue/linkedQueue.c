/*
	所有链式：都要将要插入的数据包裹在节点Node中(即需要创建初始化一个节点Node：包括数据域和指针域)

	链式队列：使用链表实现的队列存储结构
		-- 链式队列（入队：尾插法， 出队：头节点top移动）
		-- 对比：链式栈（入栈：使用了链表的头插法， 头指针作为栈顶，出栈或入栈）
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>

typedef int elemType;
// 链式存储必备节点结构体
typedef struct Node
{
	elemType data;
	struct Node* next;

}Node;

// 队列结构体（队头，队尾节点标识定义）
typedef struct linkedQueue
{
	Node* rear; // 队尾节点标识（队尾指针-新节点可在其后入队）
	Node* top; // 队头节点标识（队头的指针）
}linkedQueue;

// 队列初始化（头尾都为空）
void initLinkedQueue(linkedQueue* LQ)
{
	LQ->rear = NULL;
	LQ->top = NULL;
}

// 入队不会产生溢出的问题(先尾后插入节点，然后向后移动队尾标识)
void enQueue(linkedQueue* LQ, elemType e)
{
	// 数据包裹在节点Node中，尾插（节点先分配内存然后初始化）
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = e;
	temp->next = NULL;

	// 是否为空队列
	if (LQ->rear == NULL)
	{
		LQ->rear = temp;
		LQ->top = temp;
		printf("入队成功：%c\n", e);
	}else{
		// 新节点入队（尾插）
		LQ->rear->next = temp;
		// 尾节点标识后移
		LQ->rear = temp;
		printf("入队成功：%c\n", e);
	}
}

// 出队有可能溢出
elemType deQueue(linkedQueue* LQ)
{
	// 判断是否空栈
	if (LQ->top == NULL)
	{
		printf("空队列！！\n");
		exit(1);
	}

	// 取出头节点（队头）
	Node* temp = LQ->top;

	// 取出队头数据元素
	elemType e = temp->data;
	printf("元素出队成功：%c\n", e);

	// 队头指针后移
	LQ->top = temp->next;

	// 是否删除了最后的队列元素
	if (LQ->top == NULL)
	{
		LQ->rear = NULL;
	}
	free(temp);
	return e;
}

int main()
{
	linkedQueue* LQ;
	LQ = (linkedQueue*)malloc(sizeof(linkedQueue));
	initLinkedQueue(LQ);
	elemType e = 'a';
	for (int i = 0; i < 10; ++i)
	{
		enQueue(LQ, e);
		e = e + 1;
	}
	for (int i = 0; i < 8; ++i)
	{
		e = deQueue(LQ);
	}
	enQueue(LQ, '#');
	e = deQueue(LQ);
	e = deQueue(LQ);
	e = deQueue(LQ);
	e = deQueue(LQ);
	return 1;
}
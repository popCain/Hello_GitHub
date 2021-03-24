/***************************************************************************
*	    		数据结构：逻辑结构 + 物理结构（存储结构）
*
* 1.逻辑结构：
*	- 线性结构：线性表（“一对一”)（List, queue, stack..）
*	- 非线性结构：集合（"互斥"），树（"一对多"），图（“多对多”）..
*
* 2.物理结构（存储结构）：顺序存储，链式存储
*
* ------------------------------- 一. 线性表：链栈栈（链表的头插法，且在头节点删除） ----------------------------------
*  栈顶指针top就是链栈（或者说链表的头节点指针headNode->next）
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>
//#include <time.h>

typedef char elemType;

//链式存储必备（链表的节点结构体）
typedef struct Node
{
	elemType data;
	struct Node* next;
}Node;
// 栈结构体
typedef struct linkedStack
{
	// 指向栈顶元素
	Node* top;
}linkedStack;


// 初始化
void initLinkedStack(linkedStack* LS)
{
	// 栈顶标识对象指向空（表示空栈）
	LS->top = NULL;
}

// 清空栈
void clearStack(linkedStack* LS)
{
	Node* cur = NULL;
	while(LS->top != NULL)
	{
		cur = LS->top;
		LS->top = cur->next;
		free(cur);
	}
}

// 头插法(入栈) push
void push(linkedStack* LS, elemType e)
{
	//创建节点Node
	Node* tempNode = (Node*)malloc(sizeof(Node));
	tempNode->data = e;
	tempNode->next = LS->top;
	LS->top = tempNode;
	printf("入栈成功：%c\n", e);
}

// 类似从头遍历，但每次出栈一个元素（出栈） pop
elemType pop(linkedStack* LS)
{
	if (LS->top == NULL)
	{
		printf("空栈！！\n");
		exit(1);
	}
	elemType e;
	Node* tempNode = LS->top;
	e = tempNode->data;
	printf("出栈元素为：%c\n", e);
	LS->top = tempNode->next;
	free(tempNode);
	return e;
}

int main()
{
	linkedStack* LS;
	LS = (linkedStack*)malloc(sizeof(linkedStack));
	initLinkedStack(LS);
	push(LS, 'a');
	push(LS, 'b');
	push(LS, 'c');
	push(LS, 'd');
	push(LS, 'e');

	elemType e;
	for (int i = 0; i < 6; ++i)
	{
		 e = pop(LS);
	}

	return 0;
}
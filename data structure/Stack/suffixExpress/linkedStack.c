#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>
#include "linkedStack.h"

// 初始化
linkedStack initLinkedStack(linkedStack LS)
{
	
	LS->next = NULL;
	LS->data = 'H';
	return LS;
}

// 头插法(入栈) push
linkedStack push(linkedStack LS, elemType e)
{
	//创建节点Node
	Node* tempNode = (Node*)malloc(sizeof(Node));
	tempNode->data = e;
	tempNode->next = LS->next;
	LS->next = tempNode;
	//printf("入栈成功：%c\n", e);
	return LS;
}

// pop的参数e有问题
// 类似从头遍历，但每次出栈一个元素（出栈） pop
elemType pop(linkedStack LS)
{
	if (LS->next == NULL)
	{
		printf("空栈！！\n");
		return NULL;
	}
	Node* tempNode = LS->next;
	elemType e = tempNode->data;
	//printf("出栈元素为：%c\n", e);
	LS->next = tempNode->next;
	free(tempNode);
	return e;
}

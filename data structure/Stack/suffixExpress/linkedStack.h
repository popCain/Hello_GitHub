#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

typedef char elemType;

typedef struct Node
{
	elemType data;
	struct Node* next;
}Node;
typedef struct Node* linkedStack;

// 初始化
linkedStack initLinkedStack(linkedStack LS);
// 头插法(入栈) push
linkedStack push(linkedStack LS, elemType e);
// 类似从头遍历，但每次出栈一个元素（出栈） pop
elemType pop(linkedStack LS);
#endif
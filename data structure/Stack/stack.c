/***************************************************************************
*	    		数据结构：逻辑结构 + 物理结构（存储结构）
*
* 1.逻辑结构：
*	- 线性结构：线性表（“一对一”)（List, queue, stack..）
*	- 非线性结构：集合（"互斥"），树（"一对多"），图（“多对多”）..
*
* 2.物理结构（存储结构）：顺序存储，链式存储
*
* ------------------------------- 一. 线性表：顺序栈（主要是栈顶top指针的变动） ----------------------------------
* （3）- 栈与队列：不允许随意位置的插入和删除操作
*		・栈（stack）：Last In First Out(LIFO-后进先出)
*			-> 只允许在同一侧进行“插入（push：入栈）和删除（pop：出栈）”操作（栈顶top）
*			-> 另一侧不能操作（栈底bottom）
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>

#define MAXSIZE 20
#define ERROR 0
#define OK 1

typedef int elemType;
typedef struct Stack
{
	elemType *data;//数据数组
	int top;//栈顶指针
}sqStack;

sqStack initSQStack(sqStack sqs);//分配内存，初始化top为‘-1’表示空栈
sqStack push(sqStack sqs, elemType e);//入栈（top++）
sqStack pop(sqStack sqs);//出栈（top--）

int main(){
	sqStack sqs;

	sqs = initSQStack(sqs);

	for (int i = 0; i < MAXSIZE-1; ++i)
	{
		sqs = push(sqs, i);
	}
	printf("sqs.top:%d\n", sqs.top);
	for (int i = 0; i < MAXSIZE-1; ++i)
	{
		sqs = pop(sqs);
	}
	return OK;
}

// 初始化栈结构
sqStack initSQStack(sqStack sqs)
{
	sqs.data = (elemType*)malloc(sizeof(elemType)*MAXSIZE);
	sqs.top = -1;
	return sqs;
}

// 进栈（push）
sqStack push(sqStack sqs, elemType e)
{
	if (sqs.top == MAXSIZE-1)
	{
		printf("满栈！！\n");
		return sqs;
	}
	sqs.top = sqs.top + 1;
	sqs.data[sqs.top] = e;
	//printf("%d\n", sqs.top);
	printf("入栈元素：%d\n", e);
	return sqs; 
}

// 出栈
sqStack pop(sqStack sqs)
{
	if (sqs.top == -1)
	{
		printf("空栈！！\n");
		return sqs;
	}
	elemType e;
	e = sqs.data[sqs.top];
	printf("出栈元素：%d\n", e);
	sqs.top--;
	return sqs;
}




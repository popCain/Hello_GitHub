/***************************************************************************
*	    		数据结构：逻辑结构 + 物理结构（存储结构）
*
* 1.逻辑结构：
*	- 线性结构：线性表（“一对一”)（List, queue, stack..）
*	- 非线性结构：集合（"互斥"），树（"一对多"），图（“多对多”）..
*
* 2.物理结构（存储结构）：顺序存储，链式存储
*
* ------------------------------- 一. 线性表 ----------------------------------
* （2）- 静态链表：（定长数组（存node：data+cur游标））实现
*		集顺序表和链表的优点：既能快速读取访问元素，又能快速增删数据（但存储size提前确定了）
*					-- 可插入位置的更新及相应游标的变换，前位指针依然重要
*	L[0]:游标指向可插入数据位置 L[1]:数据链表表头，不存数据（是数据链表的入口）
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>
#define MAXSIZE 20

typedef struct Node
{
	char data; //存储字符
	int cur; //游标（指针相当）
}Node;
typedef struct Node* staticLinkList;

void createReserveList(staticLinkList L);// 创建备用表
int initList(staticLinkList L);// 创建表并返回数据表头（数据链表入口，不存数据）
int canInsertPosition(staticLinkList L);// 返回可插入数据位置，更新L[0]
void traversal(staticLinkList L, int head);// 遍历
void delData(staticLinkList L, int head, char a);//删除符合元素（遍历找到前向位的指针）
int insertData(staticLinkList L, int head, int N, char a);//插入（遍历找到前向位的指针）

int main()
{
	staticLinkList L;
	//-- 全局变量：为此数组型链表申请存储空间(要全局进行分配空间)
	L = (staticLinkList)malloc(sizeof(Node)*MAXSIZE);
	// 获取数据链表表头（并创建数据链表）
	int head = initList(L);
	traversal(L, head);
	delData(L, head, 'f');
	traversal(L, head);
	insertData(L, head, 7, '+');
	traversal(L, head);
	return 0;
}

//-- 初始化静态链表
int initList(staticLinkList L)
{
	//-- 创建备用静态链表（加上游标cur，备用链表的表头指向可插入数据位置L[0]）
	createReserveList(L);
	printf("创建备用链表如下：\n");
	traversal(L, 0);

	//--获取第一个插入位置L[1]（即数据链表的表头）
	int head = canInsertPosition(L);
	//数据表头不要插入数据，防止被删除
	//L[head].data = 'a';

	//数据链表指针域
	int temp;
	for (int i = 0; i < 10; ++i)
	{
		temp = canInsertPosition(L);
		L[temp].data = 'a' + i;
	}
	//数据链表最后一个值游标指向0
	L[temp].cur = 0;
	printf("创建静态链表成功:\n");
	//traversal(L, head);
	return head;
}

// 返回可插值位置；并将index0指向（当前可插值位置指向的位置）
int canInsertPosition(staticLinkList L)
{
	int index = L[0].cur;
	//若链表未满（L[0]始终指向可插值的位置）
	if (L[0].cur != 0)
	{
		// L[0]指向下一个可插值的位置
		L[0].cur = L[index].cur;
	}else{
		printf("已没有空间添加节点！！\n");
		exit(1);
	}
	printf("可插入节点：%d\n", index);
	return index;
}

//-- 创建一个原始的备用数组型静态链表（游标0->1->2->3->4..->MAXSIZE-1:类链表的指针域）
void createReserveList(staticLinkList L)
{
	for (int i = 0; i < MAXSIZE-1; ++i)
	{
		L[i].cur = i+1;
	}
	//链表最后一个节点，游标指向0（表示结束）
	L[MAXSIZE-1].cur = 0;
}

//-- 遍历静态链表
void traversal(staticLinkList L, int head)
{

	int temp = head;// 遍历指针(数据链表表头head开始)

	// 直到指针为0，表示存储数据结束位
	while(L[temp].cur)
	{
		printf("array[%d]-- 数据域：%c, 下一数据储存位置：%d\n",temp, L[temp].data, L[temp].cur);
		temp = L[temp].cur;
	}
	//输出数据链表最后一个节点的数据（cur游标肯定是指向0的）
	printf("array[%d]-- 数据域：%c, 下一数据储存位置：%d\n",temp, L[temp].data, L[temp].cur);
}

//--删除数据链表中某特定元素
void delData(staticLinkList L, int head, char a)
{
	// 表头
	int temp = head;
	//要删除的数据链表节点下标
	int delIndex;

	//遍历寻找表中等于a的节点下标
	while(L[temp].data != a)
	{
		temp = L[temp].cur;
		if (temp == 0)
		{
			printf("数据链表无此数据！！\n");
			return;
		}
	}
	// 找到了要删除数据下标
	delIndex = temp;

	//连接元数据链表中del的前后节点(先寻找它的前一个节点)
	int befor1Del = head;
	while(L[befor1Del].cur != delIndex)
	{
		befor1Del = L[befor1Del].cur;
	}
	//连接要删除节点的前后节点
	L[befor1Del].cur = L[delIndex].cur;

	//更新可插入index，原index降级，删除的del——index升级
	L[delIndex].cur = L[0].cur;
	L[0].cur = delIndex;
	printf("删除元素成功：@%d\n", delIndex);
	printf("删除元素后数据链表：\n");
}

//--向链表中特定位置N之前插入一个元素(将新元素插入L[0]指向的可插入位置，然后更改游标指向)
int insertData(staticLinkList L, int head, int N, char a)
{
	if (N < 2 || N > MAXSIZE)
	{
		printf("插入位置错误！！\n");
		return 0;
	}
	int temp = head;
	for (int i = 1; i < N; ++i)
	{
		//选定N前一位置的下标index--temp = L[N-1].cur
		temp = L[temp].cur;
	}

	/******************N-1，新插值（L[0]），N********************/
	// 可插入数居的位置
	int insertIndex = canInsertPosition(L);
	//新插值位置指向N位置（即N-1位置的下标）
	L[insertIndex].data = a;
	//插入位置的后位指向N位置下标
	L[insertIndex].cur = L[temp].cur;

	//插入位置的前位指向N-1位置下标
	L[temp].cur = insertIndex;
	
	printf("插值后的数据链表：@%d\n", N);
	return 1;
}


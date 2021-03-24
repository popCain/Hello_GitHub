/***************************************************************************
*	    		数据结构(データ構造こうぞう)：逻辑结构 + 物理结构（存储结构）
*
* 1.逻辑结构（論理構造　ロジック）：
*	- 线性结构：线性表・線形構造（“一对一”)（List, queue, stack..）
*	- 非线性结构：集合・セット（"互斥"），树・木構造（"一对多"），图・グラフ構造（“多对多”）..
*
* 2.物理结构（存储结构・保存方式）：顺序存储（連続するメモリ），链式存储（リンク・連結）
*
* 3.基本操作：遍历（めぐり）+访问（增删查改）
*
* 4.遍历方式：for/while迭代；递归
* ------------------------------- 一. 线性表 ----------------------------------
* （1）- 顺序表（配列）：主要注意插入，删除操作：需要移位 ¥¥¥¥¥¥-- 最主要是“移位操作”
******************************************************************************/

#include <stdio.h>
#include <stdlib.h> 
#include <sys/malloc.h>  //包含了malloc函数

#define MAXSIZE 20	// 连续存储空间初始分配量
#define OK 1
#define ERROR 0
typedef int ElemType; // 表中数据项类型（这里是int）
typedef int Status;
// 定义结构体--线性表
typedef struct
{
	ElemType *data; // 定义数组来存储数据元素（声明）
	// ElemType *elem; //分配线性表存储空间的基地址（开始地址）
	// length = sizeof(data)/sizeof(data[0])
	int listSize;
	int length; // 线性表长度（实际存储数据长度）
}sqList;

Status initList(sqList *L);//分配内存
Status getElem(sqList L, int i, ElemType *e);//随意直接取
Status insertElem(sqList *L, int i, ElemType e);//从最后位向前各向后移一位，到插入位置后一位止
int deleteElem(sqList *L, int i);// 从删除位后开始，各向前移一位
Status traversalList(sqList L);

int main()
{
	sqList *L;
	// 初始化
	initList(L);
	for (int i = 0; i < 10; i++)
	{
		// 插入
		insertElem(L, i, i);
	}
	// 遍历
	traversalList(*L);
	printf("%d\n", L->length);
	// 删除
	ElemType e;
	printf("%s\n", "请输入要删除顺序表的位置：");
	int index;
	scanf("%d", &index);
	if (index < 0 || index > L->length-1)
	{
		printf("%s\n", "outOfRange请重新输入：");
		scanf("%d", &index);
	}
	e = deleteElem(L, index);
	printf("%s", "删除掉元素：");
	printf("%d\n", e);
	return 1;
}

/******************************* -初始化线性表- ************************/
Status initList(sqList *L)
{
	//L->elem = (ElemType *)malloc(MAXSIZE*sizeof(ElemType));
	//固定长度的连续存储空间（指针数组）
	L->data = (ElemType *)malloc(MAXSIZE*sizeof(ElemType));
	//L->data[MAXSIZE] = {0,0,0,0,0,0,0,0,0,0};
	L->listSize = MAXSIZE;
	L->length = 0;
	return OK;
}

/******************************* -获取线性表中第i个元素- ************************/
// i >= 0(与数组同步)
typedef int Status;
// '.'：直接引用
Status getElem(sqList L, int i, ElemType *e)
{
	if(L.length == 0 || i < 0 || i > L.length-1)
		return ERROR;
	*e = L.data[i];
	return OK;
}

/******************************* -在线性表第i个元素位置前插入元素（数组下标同步）- ************************/
// '->':指针
Status insertElem(sqList *L, int i, ElemType e)
{
	// 数组已满
	if (L->length == MAXSIZE)
	{
		return ERROR;
	}
	// 插入位置错误（越界）
	if (i < 0 || i > L->length)
	{
		return ERROR;
	}
	// 插入位置后各元素向后移位（非最后元素后插值）
	if (i <= L->length-1)
	{
		for (int k = L->length-1; k >= i ; k--)
		{
			L->data[k+1] = L->data[k];
		}
	}
	// 插入元素
	L->data[i] = e;
	// 长度加1
	L->length++;
	return OK;
}

/******************************* -删除线性表的第i个元素- ************************/
// i >= 1(数组下标从0开始)
int deleteElem(sqList *L, int i)
{
	if (L->length == 0)
	{
		return ERROR;
	}
	if (i < 0 || i > L->length -1)
	{
		return ERROR;
	}
	ElemType e;
	e = L->data[i];
	printf("%d\n", e);
	//非删除最后一个元素
	if (i < L->length-1)
	{
		for (int k = i+1; k < L->length; k++)
		{
			L->data[k-1] = L->data[k];
		}
	L->length--;
	}
	return e;
}

/******************************* -遍历线性表的元素- ************************/
Status traversalList(sqList L)
{
	if (L.length == 0)
	{
		printf("%s\n", "线性表为空！");
		return OK;
	}
	printf("%s\n","线性表元素遍历：");
	for (int i = 0; i < L.length; i++)
	{
		printf("%d\t", L.data[i]);
	}
	printf("\n");
	return OK;
}
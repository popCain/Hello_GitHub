/***************************************************************************
*	    		数据结构：逻辑结构 + 物理结构（存储结构）
*
* 1.逻辑结构：
*	- 线性结构：线性表（“一对一”)（List, queue, stack..）
*	- 非线性结构：集合（"互斥"），树（"一对多"），图（“多对多”）..
*
* 2.物理结构（存储结构）：顺序存储，链式存储
*
* ------------------------------- 一. 线性表：单链表（头节点，前位指针域最重要） ----------------------------------
* （2）- 链表（連結リスト）：*单链表，静态链表，循环链表，双向链表。 -- ¥¥¥最主要是“遍历”操作
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef int elemType;

// レコード
typedef struct Node
{
	elemType data;
	// 里面必须用 struct Node来表示此结构体
	struct Node* next;
	
}Node;//外面可以直接用Node来表示此结构体
typedef struct Node* linkList;

linkList initLinkList(linkList L);//分配内存；初始化头节点（L=head）
linkList createLinkListHead(linkList L, int N);//头插法（新插入节点总在头节点后面）
linkList createLinkListTail(linkList L, int N);//尾插法（要先遍历找到尾部，再开始插值）
elemType getElem(linkList L, int i);//遍历查找
void insertLinkList(linkList L, elemType e, int position);//遍历找到位置前一位指针地址
void traversalLinkList(linkList head);//遍历
void delLinkList(linkList L, int position);//遍历找到删除位前一节点指针域

int main()
{
	linkList L;
	L = initLinkList(L);
	//L = (Node *)malloc(sizeof(Node));
	L = createLinkListHead(L, 10);
	L = createLinkListTail(L,10);
	printf("%s\n","遍历结果：");
	traversalLinkList(L);
	elemType e;
	e = getElem(L, 2);
	printf("%s %d\n","获得数据项：", e);

	insertLinkList(L, 1000, 5);
	printf("%s\n","插入后遍历结果：");
	traversalLinkList(L);

	delLinkList(L, 5);
	printf("%s\n","删除后遍历结果：");
	traversalLinkList(L);

	return 1;
}

/******************************* -初始化链表- ************************/
linkList initLinkList(linkList L)
{
	L = (linkList)malloc(sizeof(Node));
	if (L == NULL)
	{
		printf("%s\n","申请空间失败");
	}
	L -> data = 0;
	L -> next = NULL;
	return L;
}

/******************************* -创建链表（头插法）- ************************/
linkList createLinkListHead(linkList L, int N)
{
	//int x;
	srand(time(0));
	Node *p;
	for (int i = 0; i < N; ++i)
	{
		//scanf("%d", &x);
		//创建一个新的Node节点
		p = (Node*)malloc(sizeof(Node));
		p->data = rand()%100 + 1;
		p->next = L->next;
		L->next = p;
	}
	return L;
}

/******************************* -创建链表（尾插法）- ***********************/
linkList createLinkListTail(linkList L, int N)
{
	srand(time(0));
	Node* p;
	for (int i = 0; i < N; ++i)
	{
		p = (Node*)malloc(sizeof(Node));
		p->data = rand()%100 + 1;
		Node* head = L;
		//从头遍历寻找尾部
		while(head->next != NULL)
		{
			head = head->next;
		}
		head->next = p;
		p->next = NULL;
	}
	return L;
}
/******************************* -链表遍历- ************************/
void traversalLinkList(linkList head)
{

	Node *p = head->next;
	// while迭代
	while(p!=NULL)
	{
		printf("%d\t", p->data);
		p=p->next;	
	}
	printf("\n");	
}

/******************************* -链表获取某位置数据- ************************/
//iは０から
elemType getElem(linkList L, int i)
{
	Node* p = L->next;
	
	for (int j = 0; j < i; j++)
	{
		if (p != NULL)
		{
			p = p->next;
		}else{
			printf("%s\n", "无此数据！！");
		return ERROR;
		}
		
	}
	elemType e;
	e = p->data;
	printf("%s\n", "找到了数据：");
	printf("%d\n", e);
	return e;
}

/******************************* -链表某位置增加数据(找到插入位置前的节点重要)- ************************/
void insertLinkList(linkList L, elemType e, int position)
{
	// 创建装数据e的节点p
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = NULL;
	//寻找位置position插入
	Node* temp = L;
	for (int i = 0; i < position; ++i)
	{
		if (temp != NULL)
		{
			temp = temp->next;
		}
		else{
			printf("%s\n","插入位置错误！！");
		}
	}
	p->next = temp->next;
	temp->next = p;
	printf("%s\n", "插入成功！！");
}

/******************************* -链表某位置删除数据(找到删除位置前的节点重要)- ************************/
void delLinkList(linkList L, int position)
{
	Node* temp = L;
	for (int i = 0; i < position; ++i)
	{
		if(temp != NULL)
		{
			temp = temp->next;
		}else{
			printf("%s\n", "删除位置错误！！");
			return;
		}
		
	}
	Node* delNode = temp->next;
	temp->next = delNode->next;
	free(delNode);
	printf("%s\n", "删除成功！！");
}
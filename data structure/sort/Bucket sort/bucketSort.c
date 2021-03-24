/*
	 桶排序： 分配过程 + 回收过程(链表实现)
	
	1. 分配：将数组内的元素按照一定的规则分配到一定数量的桶中
	2. 各自排序：将各个桶中的数字分别进行排序
	3. 回收过程

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define DEFAULT_BUCKET_SIZE 10 //每个桶可放元素个数

// 链表用来储存每个桶内的元素
typedef int elemType;
typedef struct Node
{
	elemType data;
	struct Node* next;
}Node;


// 待排数组中各元素应该放到哪个桶中
int getBucketIndex(int value)
{
	return value/DEFAULT_BUCKET_SIZE;
}

// 遍历链表（不要动表中任何，包括头指针）
void printBucket(Node* list)
{
	
	Node *p = list->next;
	while(p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	
}

void traveral(int a[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

// 插入排序（排桶内元素）
Node* insertSort(Node* list){
	Node* p = list->next;
	//int* arr = (int*)malloc(sizeof(int));
	int arr[20];
	int count = 0;
	while(p)
	{
		arr[count++] = p->data;
		//printf("%d\n", p->data);
		p = p->next;
		
	}
	//traveral(arr, count);

	// 插入排序
	if (count>0)
	{
		int tmp, j;
		for (int i = 1; i < count; ++i)
		{
			tmp = arr[i];
			j=i-1;
			while(j >= 0 && arr[j] > tmp)
			{
				arr[j+1] = arr[j];
				j--;
			}
			arr[j+1] = tmp;
		}
	
		//traveral(arr, count);
	}
	
	Node* tmp_node = list->next;
	int k = 0;
	while(tmp_node)
	{
		tmp_node->data = arr[k++];
		tmp_node = tmp_node->next;
	}

	return list;
}


// 桶排序（数组+链表）
void bucketSort(int a[], int n)
{
	// 这些都是用来优化，选择合适的桶数
	int min, max;
	min = a[0];
	max = a[0];

	for (int i = 0; i < n; ++i)
	{
		if (a[i] < min)
		{
			min = a[i];
		}else if (a[i] > max)
		{
			max = a[i];
		}
	}
	// 23-9 = 14 14/5 = 2 [0, 5],[6, 10],[11, 15],[16, 20],[21, 25]...
	//int bucketNum = (max - min)/DEFAULT_BUCKET_SIZE + 1;

	int bucketNum = 10;
	Node** buckets;// 相当于二维链表

	// 申请了十个桶
	buckets = (Node**)malloc(sizeof(Node*)*bucketNum);
	// 空桶初始化
	
	for (int i = 0; i < bucketNum; ++i)
	{
		buckets[i] = (Node*)malloc(sizeof(Node));
		if (buckets[i] == NULL)
		{
			printf("申情空间失败！！\n");
			return;
		}
		buckets[i]->next = NULL;
	}
	

	// 分配过程：将待排数组的元素依次入桶
	for (int i = 0; i < n; ++i)
	{
		// 确定元素应该放进哪个桶
		int position = getBucketIndex(a[i]);
		//printf("%d\n", position);
		// 声明一个链表节点存放元素
		Node* current = (Node*)malloc(sizeof(Node));
		// 头插法
		current->data = a[i];
		//printf("%d\n", current->data);

		//printf("buckets:%d\n", buckets[position]->data);
		current->next = buckets[position]->next;
		buckets[position]->next = current;
	}

	// 输出分配给各个桶后的结果
	printf("待排元素入桶：\n");
	for (int i = 0; i < bucketNum; ++i)
	{
		printf("桶%d -> ",i);
		// 链表遍历桶中的元素
		printBucket(buckets[i]);
		printf("\n");
	}
	printf("\n");

	// 各自排序
	printf("入桶元素桶内排序：\n");
	for (int i = 0; i < bucketNum; ++i)
	{
		// 各自排序
		if (buckets[i]->next)//桶内有数据的，需要排序
		{
			// 各桶已各自排序
			buckets[i] = insertSort(buckets[i]);
			printf("桶%d -> ",i);
			// 链表遍历桶中的元素
			printBucket(buckets[i]);
			printf("\n");
		}	
	}

	// 回收过程
	int j=0;
	for (int i = 0; i < bucketNum; ++i)
	{
		// 取出桶中元素放回原数组
		Node* p = buckets[i]->next;
		while(p)
		{
			a[j++] = p->data;
			p = p->next; 
		}
	}

}





int main()
{
	int a[20] = {2, 1, 32, 4, 56, 10, 31, 15, 11, 7, 8, 30, 14, 12, 13, 41, 45, 16, 20, 6};
	int n = sizeof(a)/sizeof(a[0]);
	printf("排序之前：\n");
	traveral(a, n);
	printf("\n");

	bucketSort(a, n);
	printf("\n");
	printf("排序之后：\n");
	traveral(a, n);
	printf("\n");
	return 0;
}
/*
	・堆：优先队列（ヒープは優先度付きキューとも呼ばれる）

	   1. 完全二叉树（完全二分木）
	   2. - 大根堆（各父节点均大于左右子节点）
	   	  - 小根堆（各父节点均小于左右子节点）

	・存储：因为是完全二叉树，所以一般使用顺序表存储（数组）

	・创建：主要是调整堆的过程（从最后一个分支节点开始一直到根节点结束）[len/2-1]取整，即为最后的分支节点

	・时间复杂度：
		- 创建堆：O(n);
		- 插入：O(log(n));
		- 删除堆顶：O(log(n));
		- 堆排序：O(log(n!)) = O(nlog(n));
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>
#include <math.h>

#define MAXSIZE 100

typedef int elemType;
typedef struct heap
{
	elemType data[MAXSIZE];
	// 堆的size（数组实际存储的元素数）
	int len;
}Heap;

// 堆初始化
void initHeap(Heap* h)
{
	h->len = 0;
}

// 堆遍历
void traveral(Heap* h)
{
	elemType e;
	for (int i = 0; i <= h->len - 1; ++i)
	{
		e = h->data[i];
		printf("%d ", e);
	}
	printf("\n");
}

// 按树形遍历输出
void traveralAsTree(Heap* h)
{
	int treeHight = floor(log(h->len + 1)/log(2));
	printf("treeHight: %d\n", treeHight);
}

// k分支节点为根开始，向下调整堆-从start节点开始到end节点调整结束（向下调整则需要父与双子比较）
void adjustHeap(Heap* h, int start, int end)
{
	// 父节点
	int i = start;
	// 左子节点
	int j = 2*i + 1;
	// 将此父节点向下和他的左右子比较（若父最小则跳出此次循环，若父大则需要向下对左右子树调整到底）
	elemType fater = h->data[i];
	// 不要溢出（即是否还属于此树）
	while(j < end)
	{
		// 保证有右子（若无直接向下）-- 小根堆（根为最小值），取较小子
		if (j < end-1 && h->data[j] > h->data[j+1])
		{
			// 取较小
			j++;
		}
		// 父节点与较小的子节点比较（如果比左右子都小则跳出此次父节点的调整循环）
		if (fater <= h->data[j])
		{
			// 因为子树已为堆型（若父小于两子则无需再向下比较）
			break;
		}
		// 父节点大（将较小的子节点赋值给父节点）-- 元父节点的值还保存在father变量中
		h->data[i] = h->data[j];
		// 因为父节点大，所以破坏了子树的堆形，需要继续向下比较调整-- 以小子为父，继续向下调整堆
		i = j;
		j = 2*i + 1;
	}
	// 直到break或叶节点结束（将元父节点值赋给此叶节点）
	h->data[i] = fater;
}

// 创建堆
void createHeap(Heap* h)
{
	int i;
	elemType e;
	scanf("%d", &e);
	while(e != -1)
	{
		h->data[h->len] = e;
		h->len++;
		scanf("%d", &e);
	}
	printf("输入的原完全二叉树为：\n");
	traveral(h);

	int size = h->len;
	// 外循环for--从最后一个非叶节点开始[len/2 - 1]，“向下调整”，依次读取非叶节点到根节点结束
	for (int i = h->len/2 - 1; i >= 0; i--)
	{
		// 对每个非叶节点向下调整，以保证子树为堆型（父则要与双子比较）
		adjustHeap(h, i, size);
	}
}


// 插入堆（1.尾插 2.向上调整堆，只与其父比较大小，至根节点或比父大时结束循环）
void pushHeap(Heap* h, elemType e)
{
	// 将要插入元素，放在堆的最后叶位置
	h->data[h->len++] = e;
	// 新插入的子节点
	int child = h->len - 1;
	// 其父节点
	int father = floor((child-1)/2);
	// 与其父节点比较（子小则与父交换）
	while(h->data[child] < h->data[father] && child > 0)
	{
		// 交换父子节点的值
		elemType temp;
		temp = h->data[child];
		h->data[child] = h->data[father];
		h->data[father] = temp;

		// 继续向上调整堆
		child = father;
		father = floor((child-1)/2);
	}// 直到子节点比父节点大或已比较至根节点结束

}

// 删除堆顶元素
int deleteTopHeap(Heap* h)
{
	// 取出堆顶最小值
	elemType top = h->data[0];
	// 将堆尾元素移动到堆顶
	h->data[0] = h->data[h->len-1];
	// 堆长度减1
	h->len--;
	// 根节点向下调整堆(以保证子枝全为堆)
	adjustHeap(h, 0, h->len);
	return top;
}

// 堆排序--借用其他存储空间:O(log(n!))（不断删除堆顶元素的操作,原堆长不断减小）
int* heapSort(Heap* h, int size)
{
	// 保存由堆顶元素组成，有序数组(C语言不提倡局部变量的地址作为返回值，容易丢失出错)
	// 可以声明为静态变量，确保推出函数时，变量不会消失
	static int* sortedHeap = (int*)malloc(size*sizeof(int)); 

	//elemType sortedHeap[h->len];

	for (int i = 0; i < size; ++i)
	{
		sortedHeap[i] = deleteTopHeap(h);
		printf("%d ", sortedHeap[i]);
	}
	printf("\n");
	return sortedHeap;
}

// 堆排序--不借用其他存储空间:O(n*log(n))（取堆顶的原理一样，原堆长不变，将堆顶元素与堆尾元素互换）
void heapSort_2(Heap* h, int size)
{
	size = size - 1;
	while(size > 0)
	{
		// 取出堆顶最小值与堆尾交换
		int top = h->data[0];
		h->data[0] = h->data[size];
		h->data[size] = top;
		// 向下调整（从根开始到size结束）
		adjustHeap(h, 0, size);
		size--;	
	}	
}


int main()
{
	Heap* h = (Heap*)malloc(sizeof(Heap));
	initHeap(h);
	createHeap(h);

	printf("二叉堆为：\n");
	traveral(h);
	traveralAsTree(h);

	printf("插入元素后的堆：\n");
	pushHeap(h, 1);
	traveral(h);

	printf("删除堆顶元素后：\n");
	elemType top = deleteTopHeap(h);
	printf("堆顶元素：%d\n", top);
	traveral(h);
	
	// 无需额外存储空间
	elemType size = h1->len;
	printf("排序后2: \n");
	heapSort_2(h1, size);
	traveral(h1);

	// 保存由堆顶元素组成，有序数组(原堆消失)
	int* a = (int*)malloc(size*sizeof(int));
	printf("排序后：\n");
	a = heapSort(h, size);
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", a[i]);
	}
	return 1;
}
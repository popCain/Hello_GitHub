/*
	基本排序算法：

		1. 选择排序（選択ソート）

		2. 插入排序（挿入ソート）

		3.　冒泡排序（バブルソート）	

*/

#include <stdio.h>
#include <stdlib.h>

// 冒泡排序（逐一向后比较，每次冒泡排好一个数），所以外循环：需要n-1次冒泡排完
void bubbleSort(int a[], int n)
{
	int tmp;
	// n-1次冒泡
	for (int i = 0; i < n-1; ++i)
	{
		// 1次冒泡，将一个大值往后放
		for (int j = 0; j < n-1-i; ++j)
		{
			if (a[j] > a[j+1])
			{
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
}

// 选择排序（外循环：需要n-1次选择操作）
void selectSort(int a[], int n)
{
	int min_index, min_temp;
	//数组范围[0, n-1],故操作[0, n-2]即可完成排序
	for (int i = 0; i < n-1; ++i)	// n个数，需要n-1次选择，选择最小值放0位置，依次。。
	{
		//每次都将a[i]当作基准，寻找包括a[i]在内其后最小值的下标
		min_index = i;
		// 前i都是已排好的位置
		for (int j = i + 1; j < n; j++)
		{
			// 选出最小值下标j
			if (a[j] < a[min_index])
			{
				min_index = j;
			}
		}

		// 最小值与a[i]交换
		if (min_index != i)
		{
			min_temp = a[i];
			a[i] = a[min_index];
			a[min_index] = min_temp;
		}
	}
}

// 插入排序（移动操作）--从第二个数开始到第n个数结束，依次插入到前面已排好队列的适当位置（想插入必然需要依次向后移动一位）
void insertSort(int a[], int n)
{
	int j, tmp;
	// 这里i代表从第二个数（下标为1）开始，分别与其前面已排元素比较，插入合适位置
	for (int i = 1; i < n; ++i)
	{
		// 取出第i个要插入的数
		tmp = a[i];
		// 与其前面元素比较
		j = i - 1;
		while(j >= 0 && tmp < a[j])
		{
			// 元素后移，方便插入
			a[j+1] = a[j];
			j--;
		}
		// while循环结束，tmp>a[j], 所以需要再j的后一位插入
		a[j+1] = tmp;
	}
}

// 遍历
void traveral(int a[], int n)
{

	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}


int main()
{
	int a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	printf("排序前：\n");
	traveral(a, 10);
	selectSort(a, 10);
	printf("排序后：\n");
	traveral(a, 10);


	int b[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	printf("排序前：\n");
	traveral(b, 10);
	bubbleSort(b, 10);
	printf("排序后：\n");
	traveral(b, 10);

	int c[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	printf("排序前：\n");
	traveral(c, 10);
	insertSort(c, 10);
	printf("排序后：\n");
	traveral(c, 10);
	return 0;
}
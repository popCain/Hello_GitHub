/*
			-- 普通插入排序：对已经较为有序的序列效率较高（所以用shellSort先将序列变为较为有序的序列）

			-- 希尔排序：改进版插入排序
				*（缩小增量排序）间隔增量减小，到1完成排序（一定要在最后缩小到1,到1变为插入排序）

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>

// 一般希尔排序
void shellSort1(int a[], int n)
{
	int gap = n/2;
	int tmp;
	// 直到最后一次（增量为1，即普通插入操作）
	while(gap >= 1)
	{
		// 前[0, gap-1]就相当于原插入排序的0；
		for (int i = gap, j = 0; i < n; ++i)
		{
			// 待插入数据
			tmp = a[i];
			j = i - gap;
			// 内循环（向前比较,）
			while(j>=0 && a[j] > tmp)
			{
				// 移动数据，空出j位置插入
				a[j + gap] = a[j];
				// 每间隔gap取出一个前面的数（插入对象）
				j = j - gap;
			}
			// 插入（对比普通插入操作理解）
			a[j + gap] = tmp;		
		}
		// 缩小增量
		gap = gap/2;
	}
}

// 优化希尔排序： 1.增量序列优化 2.每趟插入排序的优化（内循环中总将较大的元素右移）
void shellSort(int a[], int n)
{
	int gap = 1; // 增量
	int tmp;
	// 增量序列优化(得到小于n的最大整数)
	while(gap < n/3)
	{
		gap = gap*3 + 1;
	}
	// 递减到1结束（最后一次变普通插入）
	while(gap >= 1)
	{
		for (int i = gap, j = 0; i < n; ++i)
		{
			// 待插入数据
			tmp = a[i];
			
			j = i - gap;
			while(j>=0 && tmp < a[j])
			{
				a[j + gap] = a[j];
				j = j - gap;
			}
			a[j+gap] = tmp;
		}

		// 增量递减
		gap = gap/3;
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

int main()
{
	int a[20] = {2, 3, 10, 9, 12, 11, 4, 5, 7, 8, 13, 14, 15, 16, 20, 1, 6, 18, 5, 7};
	int n = sizeof(a)/sizeof(a[0]);
	printf("排序前：\n");
	traveral(a, n);

	printf("排序后：\n");
	shellSort(a, n);
	traveral(a, n);
	return 0;
}
/*
				特殊桶排序（非比较排序） - 计数排序
	


*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>
# include <string.h>
void countSort(int a[], int n)
{
	int min, max;
	min = a[0];
	max = a[0];

	// 计算数据的分散空间
	for (int i = 1; i < n; ++i)
	{
		// 找出待排数组的最大值和最小值
		if (a[i] < min)
		{
			min = a[i];
		}else if (a[i] > max)
		{
			max = a[i];
		}
	}
	// 所需额外的空间（数组长度）
	int range = max - min + 1;
	int* tmp = (int*)malloc(sizeof(int)*range);
	if (tmp == NULL)
	{
		printf("内存分配失败！！\n");
		return;
	}
	// 初始化内存
	memset(tmp, 0, range);

	// 分配过程 -- 计数（待排数组的数据出现次数，相对应额外数组下标位置值加1）
	for (int i = 0; i < n; ++i)
	{
		tmp[a[i] - min]++; //计数（待排数组元素与额外数组下标对应）
	}

	// 回收过程 -- 根据额外数组存放的计数和下标，将排好序的数放回原数组
	for (int i = 0, j=0; i < range; ++i)
	{
		while(tmp[i]--)
		{
			a[j++] = i + min;
		}
	}

	free(tmp);

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
	int a[20] = {5, 7, 10, 19, 3, 15, 11, 20, 34, 27, 12, 16, 13, 18, 2, 4, 32, 26, 22, 7};
	// 数组的长度
	int n = sizeof(a)/sizeof(a[0]);

	printf("排序前：\n");
	traveral(a, n);

	// 计数排序
	countSort(a, n);
	printf("排序后：\n");
	traveral(a, n);
	return 0;
}
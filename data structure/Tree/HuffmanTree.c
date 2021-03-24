/*

	*度：父节点下子节点的个数
	哈夫曼树：最优二叉树(只有度为0或2的节点，没有度为1的节点)

		*普通二叉树：

			1. 节点数-N, 度为0的节点数-N0，度为1的节点数-N1, 度为2的节点数-N2

					N = N0 + N1 + N2 

			2. 分枝数- B = 2N2 + N1（度为2的节点有两个分支，度为1的节点有一个分支） 

					N = B + 1（分支数+根节点）

			N0 + N1 + N2 = 2N2 + N1 + 1 => N0 = N2 + 1

	哈夫曼树（无度为1节点）：N = N0 + N2 = N0 + (N0 - 1) = 2*N0 - 1

	*【注】：（发信序列：'abcdefg...'）作为带权叶节点，建哈夫曼树（以进行哈夫曼编码）

		- 序列长度（叶节点数：N0） => 哈夫曼树所需节点数：N = 2*N0 - 1

	*例：N0 = 10, N = 2*N0-1 = 19(0~18:数组下标)。   value: a~j( weight: 1~10 )
		*注：编码-下标（权重）：（权重一样的元素，先读到的放左子 --> 唯一じゃなくても、唯一にする）
			《*》- 根节点不包括在编码内

											     18(55)
											   /        \
											  /          \
									   0-16(22)        17(33)-1
										/  \             /      \
									   /    \           /        \
								  0-9(10)   13(12)   0-14(15)    15(18)-1
											 / \         / \       /  \
								            /   \       /   \     /    \
								       0-5(6)  11(6)   6(7) 7(8) 8(9)   12(9)-1
												 / \                    /   \
								                /   \                  /     \
								            0-2(3)  10(3)           3(4)    4(5)-1
													/  \
								                   /    \
								               0-0(1)   1(2)

	+¥+ - Attention: 根节点一定是在哈夫曼树数组的最后一位：（下标2n-2的位置）；因为要依次将两较小子的父节点指向“n+i”,到2n-2结束。

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>

#define LEAF_NUM 10
#define TREE_NODE_NUM 2*LEAF_NUM - 1

// 哈夫曼树节点结构
typedef char elemType;
typedef struct Node
{
	elemType value;
	int weight;
	int parent;
	int LChild;
	int RChild;
}HMTNode;
typedef HMTNode* HMTree;

// 哈夫曼编码结构体
typedef struct huffman_code
{
	// 保存的编码
	int bit[LEAF_NUM];
	int len;//实际编码长度 
}huffman_code;

// 字符串编码后存储结构体
typedef struct strCoding
{
	int encoding[200];
	int len;
}strCoding;

// 初始化树，分配存储空间
HMTree initHuffmanTree(HMTree hmt)
{
	hmt = (HMTree)malloc(TREE_NODE_NUM*sizeof(HMTNode));
	return hmt;
}

/* 
	建哈夫曼树（定长数组<2N-1>）：

		1. 前N个位置放叶节点，后面N-1个位置放分支节点
	*循环♻️（n-1次完成）
		2. 挑选权值最小及次小值叶节点，组成小二叉树，其父指向(n+i)位置（其权值为两子之和，加入比较）
		3. 下一循环要比较（0～n+i），包括新的父节点权重也要加入比较（比较过的叶节点会有父节点，无需再次比较）

*/
void createHuffmanTree(HMTree hmt, int* w)
{
	// 前‘0～LEAF_NUM-1’为叶节点存放位置（叶节点初始化）
	for (int i = 0; i < LEAF_NUM; ++i)
	{
		hmt[i].weight = w[i];
		hmt[i].parent = -1;
		hmt[i].LChild = -1;
		hmt[i].RChild = -1;
		hmt[i].value = 'a' + i;
	}

	// ‘LEAF_NUM～TREE_NODE_NUM-1’存放非叶节点（非叶节点初始化）
	for (int i = LEAF_NUM; i < TREE_NODE_NUM; ++i)
	{
		hmt[i].weight = 0;
		hmt[i].parent = -1;
		hmt[i].LChild = -1;
		hmt[i].RChild = -1;
	}

	int min1, min2, s1, s2;
	// 循环构建哈夫曼树(挑选0～LEAF_NUM中叶节点中较小的两个权值：经LEAF_NUM - 1次结束)
	for (int i = 0; i < LEAF_NUM - 1; i++)
	{
		//s1为最小值下标， S2为次小值下标
		s1=s2=0;
		min1 = 100;
		min2 = 100;
		// 找数组中最小和次小值
		// 找出所有节点中权值最小且无父节点的两个节点（将之合并为一棵二叉树）
		for (int j = 0; j < LEAF_NUM+i; j++)
		{
			// min1存最小值，min2存次小值（但比min1大的值不一定比min2大）
			// 判断节点是否有父节点，可判断节点是否已被取出过（避免重复）
			if (hmt[j].parent == -1 && hmt[j].weight < min1)
			{
				// 将较大的值赋给min2
				min2 = min1;
				s2 = s1;
				min1 = hmt[j].weight;
				s1 = j;
			// 判断此比min1大的值是否小于次小值min2
			}else if (hmt[j].parent == -1 && hmt[j].weight < min2)
			{
				min2 = hmt[j].weight;
				s2 = j;
			}
		}// 一次查询完毕

		// 其和存放到（n+i）位置（前n存放了叶子节点）
		hmt[s1].parent = LEAF_NUM + i;
		hmt[s2].parent = LEAF_NUM + i;
		hmt[LEAF_NUM+i].weight = hmt[s1].weight + hmt[s2].weight;
		hmt[LEAF_NUM+i].LChild = s1;
		hmt[LEAF_NUM+i].RChild = s2;
	}
	printf("哈夫曼树如下：\n");
}

void traveral(HMTree hmt)
{
	for (int i = 0; i < TREE_NODE_NUM; ++i)
	{
		printf("节点-%d-<%c>的权值为：%d, 其父为：%d, 左子为：%d, 右子为：%d\n",i, hmt[i].value, hmt[i].weight, hmt[i].parent, hmt[i].LChild, hmt[i].RChild);
	}
}

// 为编码结构体数组分配内存空间（手动分配的堆内存）
huffman_code* initHuffmanCodeStruct(huffman_code* hmc)
{
	// 存放哈夫曼编码结构体的数组
	hmc = (huffman_code*)malloc(LEAF_NUM*sizeof(huffman_code));
	/*
	for (int i = 0; i < LEAF_NUM; ++i)
	{
		for (int j = 0; j < LEAF_NUM; ++j)
		{
			hmc[i].bit[j] = 0;
		}
		hmc[i].len = 0;
	}
	*/
	return hmc;
}

// 哈夫曼编码（密码本）：主要是从叶节点开始向上寻找父节点到根节点为止 ---> 由叶到根（叶下标与编码数组下标对应）
void huffmanCoding(HMTree hmt, huffman_code* hmc)
{	
	int huffmanCode[10] = {0};
	// 从叶节点往上寻找其父，至根节点止（哈夫曼树的前n叶节点位置）
	for (int i = 0; i < LEAF_NUM; ++i)
	{
		// 找叶的父节点
		int temp_Parent = hmt[i].parent;
		int j = 0;
		// 向根方向迭代的下标
		int cur = i;

		// 是否到根节点
		while(temp_Parent != -1)
		{
			// 是左子编码为0， 是右子编码为1
			if (hmt[temp_Parent].LChild == cur)
			{
				huffmanCode[j++] = 0;
			}else{
				huffmanCode[j++] = 1;
			}
			// 继续向上寻找
			cur = temp_Parent;// 当前子
			temp_Parent = hmt[cur].parent;// curの父
		}//至根节点结束（编码不包括根节点）
		//huffmanCode[j] = 0;//根节点编码为0（x）

		// 编码数组（密码本下标）与哈夫曼树中叶节点下标位置一致
		hmc[i].len = j;
		printf("%d哈夫曼编码逆序与正序分别为：\n", i);
		// 因为从叶节点开始的编码，所以逆序输出为正确编码
		for (int k = 0; k < j; k++)
		{
			hmc[i].bit[j-k-1] = huffmanCode[k];
			printf("%d ", huffmanCode[k]);
		}
		printf("\n");

		// 编码正序
		for (int k = 0; k < hmc[i].len; k++)
		{
			printf("%d ", hmc[i].bit[k]);
		}
		printf("\n");
	}//for（各节点结束）
}

/* 
	给定字符串进行编码：《 字符 --> 对应叶节点下标 --> 对应编码数组下标,得此字符编码bit[] 》♻️
		1. 循环读取字符串中字符，到‘\n’字符串结束
		2. 由哈夫曼树数组（对比前n位叶节点的值），找到对应字符的下标
		3. 此下标对应，编码结构体（密码本）中的下标，得此字符编码
*/
void encoding(HMTree hmt, huffman_code* hmc, char* str, strCoding* strC)
{
	strC->len = 0;

	int i = 0;
	// 是否到字符串结尾
	while(str[i]!='\0'){
		// 输入字符是否在（a～j）；因为只对这些字符做了编码（密码本）
		if (str[i] >= 'a' && str[i] <= 'j')
		{
			// 从哈夫曼树里找到相应的字符下标
			for (int j = 0; j < LEAF_NUM; ++j)
			{
				// 若找到相应字符
				if (str[i] == hmt[j].value)
				{
					// 此下标对应字符编码在hmc[j].bit[]中
					for (int k = 0; k < hmc[j].len; ++k)
					{
						strC->encoding[strC->len++] = hmc[j].bit[k];
					}
					// 每个字符只有一个对应，所有找到即跳出此次循环，进入下一次
					break;	 
				}
			}// 找对应字符

			// 下一字符
			i++;
		}else{
			printf("输入字符串有误！！\n");
			return;
		}
	}
}

// 遍历字符串编码结果
void traveral_encode(strCoding* strC)
{
	printf("字符串编码结果为：\n");
	for (int i = 0; i < strC->len; ++i)
	{
		printf("%d ", strC->encoding[i]);
	}
	printf("\n");
}

/* 
	字符串01序列的解码：由根（哈夫曼树数组最后一位：2n-2）到叶（获取叶节点的值）
		1. 读取编码序列（0: 根的左子，1: 根的右子），
		2. 从根节点往下直到叶节点（无左右子），取出此叶节点的值即为解码字符)
*/
void bit2StrDecode(HMTree hmt, strCoding* strC, char* str_output)
{
	// 字符串编码后的01序列
	int len = 0;
	int root = TREE_NODE_NUM - 1;// 哈夫曼树数组最后一位：2n-2为根的下标

	// 遍历字符串编码的数组
	for (int i = 0; i < strC->len; ++i)
	{
		if (strC->encoding[i] == 0)
		{
			root = hmt[root].LChild;
		}else{
			root = hmt[root].RChild;
		}
		// 是否到达叶节点(叶节点无左右子，即均为-1)
		if (hmt[root].LChild == -1)
		{
			// 此叶节点的值即为解码字符
			str_output[len++] = hmt[root].value;

			// 一段01序列结束--继续从根节点（进入下一段字符01序列）
			root = TREE_NODE_NUM - 1;
		}	
	}// 遍历字符的01编码序列结束

	// 字符串数组结束符号
	str_output[len] = '\0';

}

int main()
{

	printf("请输入%d个叶节点的权值：\n", LEAF_NUM);
	// 手动叶节点权重
	int wgt[LEAF_NUM];
	for (int i = 0; i < LEAF_NUM; ++i)
	{
		int leafWeight;
		scanf("%d", &leafWeight);
		wgt[i] = leafWeight;
	}

	HMTree hmt;
	//hmt = initHuffmanTree(hmt);
	hmt = (HMTree)malloc(TREE_NODE_NUM*sizeof(HMTNode));
	createHuffmanTree(hmt, wgt);
	traveral(hmt);

	// 哈夫曼编码数组（全局变量）
	huffman_code hmc[LEAF_NUM];
	//hmc = initHuffmanCodeStruct(hmc);
	huffmanCoding(hmt, hmc);

	// 各字符所对应的编码结果（密码本）
	for (int i = 0; i < LEAF_NUM; ++i)
	{
		printf("字符%c的编码为：", hmt[i].value);
		for (int j = 0; j < hmc[i].len; ++j)
		{
			printf("%d ", hmc[i].bit[j]);
		}
		printf("\n");
	}

	// 读取需要编码的字符串
	char str_input[20];
	printf("请输入要编码字符串（20字以内）：\n");
	scanf("%s", str_input);

	// 储存编码结果
	strCoding* strC = (strCoding*)malloc(sizeof(strCoding));

	// 将读取的字符串编码，编码结果储存在线性表strC中
	encoding(hmt, hmc, str_input, strC);
	// 遍历编码结果
	traveral_encode(strC);

	// 将编码结果进行解码（01序列到字符串）
	char str_output[20];
	bit2StrDecode(hmt, strC, str_output);
	printf("解码结果为：%s\n", str_output);

	// 手动分配的内存释放
	free(strC);
	free(hmt);
	return 0;
}
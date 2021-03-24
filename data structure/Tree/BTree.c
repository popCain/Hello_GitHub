/*

  二叉树：普通二叉树（链式存储）； 完全二叉树（顺序存储）

					a
				  /   \
				 b     c
			    / \   / 
			   d   e f

	- 前序遍历：a b d e c f  （根 -> 左 -> 右）
	- 中序遍历：d b e a f c  （左 -> 根 -> 右）
	- 后序遍历：d e b f c a  （左 -> 右 -> 根）
	- 层次遍历：a b c d e f   (按层次依次取出：队列数据结构遍历)

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>

#define MAXSIZE 30
typedef char elemType;

// 二叉树节点结构
typedef struct BTNode
{
	elemType data;
	struct BTNode *lChild, *rChild;
}BTNode;
typedef BTNode* BTree;

// 队列结构（顺序队列）
typedef struct Queue
{
	// 存储二叉树节点
	BTNode* data[MAXSIZE];
	int top, rear; 
	
}Queue;

// 初始化队列
Queue* initQueue(Queue* queue)
{
	queue->top = -1;
	queue->rear = -1;
	return queue;
}

// 入队
Queue* enQueue(Queue* queue, BTNode* btn)
{
	if (queue->rear == MAXSIZE - 1)
	{
		printf("队列已满！！\n");
		exit(1);
	}
	// 下标先加1，再赋值（队尾元素后面位置入队）
	//queue->rear = queue->rear + 1;
	queue->data[++queue->rear] = btn;
	return queue;
}

// 出队
BTNode* deQueue(Queue* queue)
{
	if (queue->top == queue->rear)
	{
		printf("队列已空！！\n");
		exit(1);
	}
	// 因为此top不是指向队头元素（而是队头元素的前一位，所以要先加一再取出）
	BTNode* btn = queue->data[++queue->top];
	return btn;
}

// 初始化二叉树
BTree initBTree(BTree BT)
{
	BT = (BTree)malloc(sizeof(BTNode));
	BT->data = 'a';
	BT->lChild = NULL;
	BT->rChild = NULL;
	return BT;
}

// 创建二叉树
BTree createBTree(BTree BT)
{
	BTNode* tempNode1 = (BTNode*)malloc(sizeof(BTNode));
	tempNode1->data = 'b';
	BT->lChild = tempNode1;

	BTNode* tempNode2 = (BTNode*)malloc(sizeof(BTNode));
	tempNode2->data = 'c';
	BT->rChild = tempNode2;

	BTNode* tempNode3 = (BTNode*)malloc(sizeof(BTNode));
	tempNode3->data = 'd';
	tempNode3->lChild = NULL;
	tempNode3->rChild = NULL;
	BT->lChild->lChild = tempNode3;

	BTNode* tempNode4 = (BTNode*)malloc(sizeof(BTNode));
	tempNode4->data = 'e';
	tempNode4->lChild = NULL;
	tempNode4->rChild = NULL;
	BT->lChild->rChild = tempNode4;

	BTNode* tempNode5 = (BTNode*)malloc(sizeof(BTNode));
	tempNode5->data = 'f';
	tempNode5->lChild = NULL;
	tempNode5->rChild = NULL;
	BT->rChild->lChild = tempNode5;

	return BT;
}

//  前序遍历：根 -> 左 -> 右
void preOrderTraveral(BTree BT)
{
	if (BT == NULL)
	{
		//printf("二叉树遍历结束！！\n");
		return;
	}

	printf("%c ", BT->data);
	preOrderTraveral(BT->lChild);
	preOrderTraveral(BT->rChild);
}

// 中序遍历：左 -> 根 -> 右
void inOrderTraveral(BTree BT)
{
	if (BT == NULL)
	{
		return;
	}
	inOrderTraveral(BT->lChild);
	printf("%c ", BT->data);
	inOrderTraveral(BT->rChild);
}

// 后序遍历：左 -> 右 -> 根
void postOrderTraveral(BTree BT)
{
	if (BT == NULL)
	{
		return;
	}
	postOrderTraveral(BT->lChild);
	postOrderTraveral(BT->rChild);
	printf("%c ", BT->data);
}

// 层次遍历: 将树的根节点依次入队，《根节点出队（左右子依次入队）：循环♻️》
void levelTraveral(BTree BT)
{
	if (BT == NULL)
	{
		return;
	}
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue = initQueue(queue);
	// 根节点入队
	queue = enQueue(queue, BT);

	BTNode* tempNode;
	while(queue->top < queue->rear)
	{
		// 根节点出队（依次出队）
		tempNode = deQueue(queue);
		printf("%c ", tempNode->data);

		// 节点的左右子依次入队
		if (tempNode->lChild != NULL)
		{
			queue = enQueue(queue, tempNode->lChild);
		}
		if (tempNode->rChild != NULL)
		{
			queue = enQueue(queue, tempNode->rChild);
		}
	}	
}


int main()
{
	BTree BT;
	BT = initBTree(BT);
	BT = createBTree(BT);

	// 前向遍历：根 -> 左 -> 右
	printf("前序遍历：");
	preOrderTraveral(BT);
	printf("\n");
	// 中序遍历
	printf("中序遍历：");
	inOrderTraveral(BT);
	printf("\n");

	// 后序遍历
	printf("后序遍历：");
	postOrderTraveral(BT);
	printf("\n");

	// 层次遍历（按树的层进行遍历）
	printf("层次遍历：");
	levelTraveral(BT);
	printf("\n");
	return 0;
}

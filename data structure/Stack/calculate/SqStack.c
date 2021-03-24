#include <stdio.h>
#include <stdlib.h>

#include "SqStack.h"

/* 创建栈 */
sqstack *sqstack_create()
{
    sqstack *L;

    L = (sqstack *)malloc(sizeof(*L));

    L->top = -1;

    return L;
}

/* 入栈 */
int sqstack_push(sqstack *L,int x)
{
    //如果入栈超出栈空间
    if (L->top == MAXSIZE - 1)
    {
    return -1;
    }
    //压栈
    L->data[++L->top] = x;
    return 0;
}

/* 出栈 */
int sqstack_pop(sqstack *L,int *x)
{
    //如果出栈超出栈空间
    if (L->top == -1)
    {
    return -1;
    }
    //利用传出参数传出栈顶元素
    *x = L->data[L->top--];
    return 0;
}

/* 获得栈顶值 */
int sqstack_top(sqstack *L,int *x)
{
    if (L->top == -1)
    {
    return -1;
    }

    *x = L->data[L->top];
    return 0;
}
/* 判断栈是否为空 */
int sqstack_is_empty(sqstack *L)
{
    return (L->top == -1);
}

/* 打印输出栈中元素 */
void sqstack_display(sqstack *L)
{
    int i;
    if (L->top == -1)
    {
    return ;
    }

    for (i = 0 ; i <= L->top; i++)
    {
    printf("%d ",L->data[i]);
    }
    printf("\n");
}
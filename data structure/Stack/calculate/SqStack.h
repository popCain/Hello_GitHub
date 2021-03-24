// 避免多文件引用此头文件时的声明冲突
#ifndef SQSTACK_H
#define SQSTACK_H

#define MAXSIZE 32
typedef struct SqStack
{
	int data[MAXSIZE];
	int top;
}sqstack;

sqstack *sqstack_create();  //创建栈
int sqstack_push(sqstack *, int ); //入栈
int sqstack_pop(sqstack *, int *); //出栈
int sqstack_top(sqstack *, int *); //查看栈顶值
int sqstack_is_empty(sqstack *); //判断栈是否为控
void sqstack_display(sqstack *); //显示栈内容，调试用的


#endif
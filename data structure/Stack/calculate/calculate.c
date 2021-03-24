#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<ctype.h>

#define INITSIZE  20
#define INCREMENT 10
#define MAXBUFFER 10
#define LEN   sizeof(Elemtype)

/*栈的动态分配顺序存储结构*/
//存储的数据为浮点型
typedef double Elemtype;
typedef struct{
	Elemtype *base;
	Elemtype *top;
	int StackSize; 
}SqStack;

void InitStack(SqStack *S)
{
	S->base=(Elemtype*)malloc(LEN*INITSIZE);
	assert(S->base != NULL);
	S->top=S->base;
	S->StackSize=INITSIZE;
}

void PushStack(SqStack *S,Elemtype e)
{
	if(S->top - S->base >= S->StackSize)
	{
		S->base=(Elemtype*)realloc(S->base,(S->StackSize+INCREMENT)*LEN);
		assert(S->base !=NULL);
		S->top=S->base+S->StackSize;
		S->StackSize+=INCREMENT;
	}
	*S->top =e;
	 S->top++;
}

void PopStack(SqStack *S,Elemtype *e)
{
	*e=*--S->top;
}

void CalFunction(SqStack *S,char str[])
{
	Elemtype number,e,d;
	char arr[MAXBUFFER];
	int i=0,j=0;
	
	InitStack(S);
	
	while(str[i]!='\0')
	{
		while(isdigit(str[i])||str[i]=='.')  //过滤数字（包括小数）
		{
			// 先赋值操作，再进行++操作(等价):arr[j++]=str[i++]
			// 存储多位数或小数
			arr[j]=str[i];
			j++;
			i++;
			// 字符串结尾标识
			arr[j]='\0';
			
			if( j >= MAXBUFFER )
			{
				printf("输入单个数据过大！\n");
				return;//结束函数
			}
			// 以空格作为数字分隔
			if(str[i]==' ')
			{
				number=atof(arr);    //利用atof函数将数字字符转化为double型数据
				PushStack(S,number); //将转换的数进行压栈
				j=0;
				break;//跳出此内部循环体（对外层循环结构无影响）
			}
		}
		
		switch(str[i])
		{
			//先出的数放右边（右对齐）
			case '+':
				PopStack(S,&e);
				PopStack(S,&d);
				PushStack(S,d+e);
				break;
			case '-':
				PopStack(S,&e);
				PopStack(S,&d);
				PushStack(S,d-e);
				break;
			case '*':
				PopStack(S,&e);
				PopStack(S,&d);
				PushStack(S,d*e);
				break;
			case '/':
				PopStack(S,&e);
				PopStack(S,&d);
				if(e == 0)
				{
					printf("输入出错，分母为零！\n");
					return ;
				}
				PushStack(S,d/e);
				break;
		}
		i++; 	
	}//while结束（到达字符串结尾）
	
	PopStack(S,&e);
	printf("计算结果为：%lf",e);	
}

int main()
{
	char str[100];
	SqStack S;
	printf("请按逆波兰表达式输入数据,字符之间用空格隔开:");
	gets(str);

	CalFunction(&S,str);
	return 0;
}


// 检测用例 5 - (6 + 7) * 8 + 9 / 4

// 输入：5 8 6 7 + * - 9 4 / + # 

// 输出： - 96.750000

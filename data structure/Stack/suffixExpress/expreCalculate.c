/*
	输入的中缀表达式为: 9+(3-1)*3+10/2
	(逆波兰)后缀表达式： 9 3 1 -3 *+10 2 /+

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>
#include <ctype.h>
#include <assert.h>

#define INITSIZE  20
#define INCREMENT 10
#define MAXBUFFER 10

//-- 存储的数据为浮点型（计算后缀表达式）
typedef double Elemtype;
typedef struct{
	Elemtype *base;
	Elemtype *top;
	int StackSize; 
}SqStack;
#define LEN   sizeof(Elemtype)
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
	printf("计算结果为：%f\n",e);	
}

//-- 后缀表达式用栈
typedef char elemType;
typedef struct Node
{
	elemType data;
	struct Node* next;
}Node;
typedef struct Node* linkedStack;

// 初始化
linkedStack initLinkedStack(linkedStack LS)
{
	
	LS->next = NULL;
	LS->data = 'H';
	return LS;
}

// 头插法(入栈) push
linkedStack push(linkedStack LS, elemType e)
{
	//创建节点Node
	Node* tempNode = (Node*)malloc(sizeof(Node));
	tempNode->data = e;
	tempNode->next = LS->next;
	LS->next = tempNode;
	//printf("入栈成功：%c\n", e);
	return LS;
}

// pop的参数e有问题

// 类似从头遍历，但每次出栈一个元素（出栈） pop
elemType pop(linkedStack LS)
{
	if (LS->next == NULL)
	{
		printf("空栈！！\n");
		return NULL;
	}
	Node* tempNode = LS->next;
	elemType e = tempNode->data;
	//printf("出栈元素为：%c\n", e);
	LS->next = tempNode->next;
	free(tempNode);
	return e;
}

elemType* infix2suffix(linkedStack LS, elemType* str)
{
	elemType* suffix_expression = (elemType*)malloc(sizeof(elemType)*40);
	//char suffix_expression[30];
	int i = 0;
	int j = 0;
	elemType e;
	// '\0'为字符串结束标志（所以C中，字符串所占内存字节：需要字节数+1（‘\0’））
	while(str[i] != '\0')
	{
		// 如果是数字直接输出--多位数的情况（直到下一位是运算符时输出空格作为多位数的间隔）
		while(isdigit(str[i]) || str[i]=='.')
		{
			printf("%c", str[i]);
			
			//  后缀表达式字符串
			suffix_expression[j++] = str[i];
			i++;
			// 当下一个字符不是数字时，输出空格
			if(!isdigit(str[i]) && str[i]!='.')
			{
				printf(" ");
				// 空格分隔多位数与其他字符
				suffix_expression[j++] = ' ';

			}
		}
		// 加减法优先级最低，如果空栈直接进栈
		// 否则将栈中存储的运算符全部出栈，
		if (str[i]=='+' || str[i]=='-')
		{
			//printf("%c\n", str[i]);
			// 栈不空时
			if (LS->next)
			{

				// 将栈内符号全部出栈（直至遇到左括号‘（’）
				do{

					e = pop(LS);
					if (e == '(')
					{
						LS = push(LS, e);
					}
					else{
						printf("%c", e);
						suffix_expression[j++] = e;
						suffix_expression[j++] = ' ';
						//j++;
					}
				}while(LS->next && e != '(');
				// 将‘+’或'-'号入栈
				LS = push(LS, str[i]);
			}else{
				// 将‘+’或‘-’号入栈
				LS = push(LS, str[i]);
			}
		// 乘，除，左括号优先级高；直接入栈
		}else if (str[i]=='*' || str[i]=='/' || str[i]=='(')
		{
			LS = push(LS, str[i]);

		// 当遇到右括号时，将栈中运算符弹出，直至匹配到左括号（左括号弹出不打印，右括号也不入栈）
		}else if (str[i] == ')')
		{
			e = pop(LS);
			while(e != '(')
			{
				printf("%c", e);
				suffix_expression[j++] = e;
				suffix_expression[j++] = ' ';
				//j++;
				e = pop(LS);
			}

		}else if (str[i] == '\0')
		{
			break;

		}else{
			printf("输入格式错误！！\n");
			return NULL;
		}
		
		i++;
	}// while结束

	// 最后将栈中剩余的运算符弹栈，打印
	while(LS->next)
	{
		e = pop(LS);
		printf("%c", e);
		suffix_expression[j++] = e;
		suffix_expression[j++] = ' ';
		//j++;
	}
	suffix_expression[j] = '\0';
	printf("\n");
	return suffix_expression;
}

int main()
{
	//初始化栈
	linkedStack LS;
	LS = (Node*)malloc(sizeof(Node));
	LS = initLinkedStack(LS);

	elemType str[30];
	//str = (elemType*)malloc(sizeof(elemType));
	gets(str);
	printf("输入的表达式为: %s\n", str);

	elemType* suffix_expression = infix2suffix(LS, str);
	printf("转化为后缀表达式后: %s\n", suffix_expression);

	// 计算结果
	SqStack S;
	CalFunction(&S, suffix_expression);
	return 0;
}
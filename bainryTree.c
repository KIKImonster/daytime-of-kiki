nclude <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h> 
#include <math.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

#define MAX_TREE_SIZE 100
#define MAX_QUEUE_SIZE 5
#define Nil ' ' 

typedef char TElemtype;    //将树的结点类型设置为字符型 
typedef TElemtype SqBiTree[MAX_TREE_SIZE];    //定义顺序存储二叉树的结构数组 

typedef struct{
	int level;    //树的层号 
	int order;    //一层中的序号(从左向右) 
}position;

/*-------二叉树的函数定义-------*/

/*初始化树*/
int InitBiTree(SqBiTree T)
{
	int i;
	for (i = 0; i<MAX_TREE_SIZE; i++)
	{
		T[i] = Nil;    //将初值设为空格 
	}

	T[MAX_TREE_SIZE] = '\0';    //给数组尾部加上结标致 
	return OK;
}

/*创建树*/
int CreateBiTree(SqBiTree T)
{
	int i = 0;
	int l = 0;
	char s[MAX_TREE_SIZE];
	printf("请按顺序输入结点的值,空格表示空结点,结点数<=%d\n", MAX_TREE_SIZE);
	gets(s);
	l = strlen(s);
	for (; i<l; i++)
	{
		T[i] = s[i];
		if (i != 0 && T[(i + 1) / 2 - 1] == Nil&&T[i] != Nil)
		{
			printf("出现无双亲且不是根的结点.\n");
			return ERROR;
		}
	}
	for (; i<MAX_TREE_SIZE; i++)
	{
		T[i] = Nil;
	}
	return OK;
}

#define ClearBiTree InitBiTree    //在顺序存储结构中,ClearBiTree和InitBiTree完全一样 

/*判断树是否为空*/
int BiTreeEmpty(SqBiTree T)
{
	if (T[0] == Nil)
	{
		printf("树为空.\n");
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int main( )
{
	position p;
	SqBiTree T;
	SqBiTree S;
	TElemtype elem;
	InitBiTree(T);
	BiTreeEmpty(T);
	CreateBiTree(T);
	puts(T);
	return 0;
}
typedef struct BiTreeNode
{
    char data;
    struct BiTreeNode *left;
    struct BiTreeNode *right;
}BiTreeNode,*BiTree;
 
/**二叉树的建立--按照先序方式建立--插入**/
void CreateBiTree(BiTree *T)
{
    char val;
    scanf("%c",&val);
 
    if(val == '#')
        *T = NULL;  //null表示为空枝
 
    else
    {
        *T = (BiTree)malloc(sizeof(BiTreeNode));
        (*T)->data = val;
        CreateBiTree(&(*T)->left);
        CreateBiTree(&(*T)->right);
    }
}
 
 
/**先序遍历  根左右**/
void PreOrderTravel(BiTree T)
{
    if(T==NULL)
        return;
    printf("%c ",T->data);
    PreOrderTravel(T->left);
    PreOrderTravel(T->right);
}
 
/**中序遍历 左根右**/
void InOrderTravel(BiTree T)
{
    if(T==NULL)
        return;
    InOrderTravel(T->left);
    printf("%c ",T->data);
    InOrderTravel(T->right);
}
 



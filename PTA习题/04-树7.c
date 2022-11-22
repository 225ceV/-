#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* ����������ɲ���ʵ�֣�ϸ�ڲ��� */
void InorderTraversal( BinTree BT );  /* ����������ɲ���ʵ�֣�ϸ�ڲ��� */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );


int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0; 
}

// ���� 
BinTree Insert( BinTree BST, ElementType X ){
	if(!BST){  // ���Ϊ�գ������½�� 
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = NULL;
		BST->Right = NULL;
	}else{
		if(X < BST->Data)
			BST->Left = Insert(BST->Left,X);
		else if(BST->Data < X)
			BST->Right = Insert(BST->Right,X);
	}
	return BST; 
}

// ɾ��
BinTree Delete( BinTree BST, ElementType X ){
	BinTree tmp;
	if(!BST){
		printf("Not Found\n");
		return BST;
	}else{
		if(X < BST->Data)
			BST->Left = Delete(BST->Left,X);
		else if(BST->Data < X)
			BST->Right = Delete(BST->Right,X);
		else{  // �ҵ�Ҫɾ����� 
			if(BST->Left && BST->Right){  // ����ý�������Ҷ��� 
				tmp = FindMin(BST->Right);
				BST->Data = tmp->Data;
				BST->Right = Delete(BST->Right,tmp->Data);
			}else{
				tmp = BST;
				if(BST->Left && !BST->Right)
					BST = BST->Left;
				else if(!BST->Left && BST->Right)
					BST = BST->Right;
				else
					BST = NULL;
				free(tmp);
			}
		}
	}
	return BST;
} 

/* 你的代码将被嵌在这里 */
Position FindMin( BinTree BST )
{
    // if(!BST->Left) return BST;
    // return FindMin(BST->Left);
    while(!BST->Left){
        BST=BST->Left;
    }
    return BST;
}
Position FindMax( BinTree BST )
{
    // if(!BST->Right) return BST;
    // return FindMax(BST->Right);
    while (!BST->Right)
    {
        BST=BST->Right;
    }
    return BST;
    
}

BinTree Insert( BinTree BST, ElementType X )
{
    if(!BST){
        Position new= (BinTree)malloc(sizeof(struct TNode));
        new->Data=X;
        return new;
    }
    if(X<BST->Data) BST->Left=Insert(BST->Left, X);
    else BST->Right=Insert(BST->Right, X);
    return BST;
}

Position Find( BinTree BST, ElementType X )
{
    // if(!BST) return NULL;
    // if(BST->Data==X) return BST;
    // if(BST->Data>X) return Find(BST->Left, X);
    // if(BST->Data<X) return Find(BST->Right, X);
    while (!BST)
    {
        if(BST->Data==X) return BST;
        else if(BST->Data>X) BST=BST->Left;
        else if(X>BST->Data) BST=BST->Right;
    }
    return NULL;
}

BinTree Delete( BinTree BST, ElementType X )
{
    if(!BST){
        printf("%s\n", "Not Found");
        return BST;
    } 
    if(X<BST->Data) BST->Left=Delete(BST->Left, X);   //!
    else if(X>BST->Data) BST->Right=Delete(BST->Right, X); //!
    //找到了
    else{
        if(BST->Left&&BST->Right){
            Position up=FindMin(BST->Right);
            BST->Data=up->Data;
            BST->Right=Delete(BST->Right, BST->Data);                //!

        }else{
            Position old=BST;
            BST=BST->Left?BST->Left:BST->Right;        //! 为了删除点的父节点信息
            free(old);
        }
    }
    return BST;
}
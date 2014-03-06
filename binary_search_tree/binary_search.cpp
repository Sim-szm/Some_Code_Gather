#include <cstdlib>
#include <cassert.h>
#include "binary_search.h"
#define M 10
/*f初始值为NULL，p记录最后访问过的节点*/
bool search_BST(BiTree T,int key,BiTree f, BiTree *p){
	if(!T){
		*p=f;
		return false;
	}
	else if(key==T->data){
		*p=T;
		return true;
	}
	else if(key<T->data){
		return search_BST(T->lchild,key,f,p);
	}
	else {
		return search_BST(T->rchild,key,f,p);
	}
}

bool insert_BST(BiTree *T,int key){
	BiTree p,s;
	if(!search_BST(T,key,NULL,&p)){   //p记录最后一个访问的结点
		s=(BiTree*)malloc(sizeof(BiTNode));
		s->data=key;
		s->lchild=s->rchild=NULL;
		if(!p){
			*T=s;
		}
		else if(key<p->data){
			p->lchild=s;
		}
		else if(key>p->data){
			p->rchild=s;
		}
		return true;
	}
	else
		return false;
}

static inline void __creat(){
	int i;
	int array[M]={23,54,34,43,12,77,45,14,66,35};
	BiTree p=NULL;
	for(i=0;i<M;i++){
		insert_BST(&p,array[i]);
	}
}

bool delete_BST(BiTree *T,int key){
	assert(T!=NULL);
	if(key==(*T)->data){
		return Delete_Node(T);
	}
	else if(key<(*T)->data){
		return delete_BST((*T)->lchild,key);
	}
	else if(key>(*T)->data){
		return delete_BST((*T)->rchild,key);
	}
}

bool Delete_Node(BiTree *p){
	BiTree q,s;
	if((*p)->rchild==NULL){
		q=*p;
		*p=(*p)->lchild;  //right tree is NULL
		free(q);
	}
	else if((*p)->lchild==NULL){
		q=*p;
		*p=(*p)->rchild;   //left tree is NULL
		free(q);
	}
	else{
		/*....*/   
	}
}
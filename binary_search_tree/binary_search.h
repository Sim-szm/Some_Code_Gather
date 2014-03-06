#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

typedef struct BiNode {
	int data ;
	struct BiNode *lchild ,*rchild;
}BiTNode,*BiTree;

bool search_BST(BiTree T,int key,BiTree f, BiTree *p);
bool insert_BST(BiTree *T,int key);
static inline void __creat();
bool delete_BST(BiTree *T,int key);
bool Delete_Node(BiTree *p);
#endif
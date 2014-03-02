/* =====================================================================================
 * 
 *       Filename:  red-black_tree.c
 *        Version:  1.0
 *        Created:  2013年05月28日 17时25分01秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, 
 *        Company:  Class 1107 of Computer Science and Technology
 * 
 *=====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define red 0
#define black 1

typedef struct Node{
	int color;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
}node;
node *grandnode(node *n){
	return n->parent->parent;
}
node *uncle(node *n){
	if(n->parent==grandnode(n)->left){
		return grandnode(n)->right;
	}else{
		return grandnode(n)->left;
	}
}
void rotate_left(node *n){
	node *new=n->right,*g=n->parent;
	g->left=new;
	n->parent=new;
	n->right=new->left;
	if(new->left != NULL){
		new->left->parent=n;
	}
	new->parent=g;
	new->left=n;
}
void rotate_right(node *n){
	node *new=n->left,*g=n->parent;
	g->right=new;
	n->parent=new;
	n->left=new->right;
	if(new->right != NULL){
		new->right->parent=n;
	}
	new->parent=g;
	new->right=n;
}
/*
 *  descly for those function here !
 */
void insert_case2(node *);
void insert_case3(node *);
void insert_case4(node *);
void insert_case5(node *);

void insert_case1(node *n){i
	if(n->parent==NULL){
		n->color=black;
	}else{
		insert_case2(n);
	}
}
void insert_case2(node *n){
	if((n->parent->color)==black){
		return ;
	}else{
		insert_case3(n);
	}
}
void insert_case3(node *n){
	if(uncle(n)!=NULL && (uncle(n)->color)==red){
		n->parent->color=black;
		uncle(n)->color=black;
		grandnode(n)->color=red;
		insert_case1(grandnode(n));

	}else{
		insert_case4(n);
	}
}
void insert_case4(node *n){
	if(n==n->parent->right && n->parent==grandnode(n)->left){
		rotate_left(n->parent);
		n=n->left;
	}else if(n==n->parent->left && n->parent==grandnode(n)->right){
		rotate_right(n->parent);
		n=n->right;
	}
	insert_case5(n);
}
void insert_case5(node *n){
	n->parent->color=black;
	grandnode(n)->color=red;
	if(n==n->parent->left && n->parent==grandnode(n)->left){
		rotate_right(grandnode(n));
	}else{
		rotate_left(grandnode(n));
	}
}
void print_tree(node *n){
	if(n==NULL){
		return ;
	}else{
		printf("color is : %2d ",n->color);
		print_tree(n->left);
		print_tree(n->right);
	}
}
int main(int argc, char *argv[])
{
	node *head=(node *)malloc(sizeof(node));
	head->color=black;
	head->left=NULL;
	head->parent=NULL;
	head->right=NULL;
	node *doc=(node *)malloc(sizeof(node));
	doc->color=black;
	doc->left=NULL;
	doc->parent=NULL;
	doc->right=NULL;
	node *pos=(node *)malloc(sizeof(node));
	pos->color=black;
	pos->left=NULL;
	pos->parent=NULL;
	pos->right=NULL;
	insert_case1(head);
	insert_case1(doc);
	insert_case1(pos);
	return 0;
}


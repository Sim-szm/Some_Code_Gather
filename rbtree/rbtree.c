/*
 * =====================================================================================
 *
 *       Filename:  rbtree.c
 *        Version:  1.0
 *        Created:  2014年03月10日 20时09分24秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "rbtree.h"

#define NIL(rbtree) \
	(&((rbtree)->null))

void rbtree_init(rbtree_t *rbtree){
	if(NULL!=rbtree){
		rbtree_black(NIL(rbtree));
		rbtree->root=NIL(rbtree);
		rbtree->tree_size=0;
	}
}

void rbtree_insert_node(rbtree_t *rbtree ,rbtree_node_t *node){
	rbtree_node_t *p,*q;
	if((NULL==rbtree) || (NULL==node) || (node==NIL(rbtree))){
		errno=EINVAL;
		return;
	}
	if(rbtree->root==NIL(rbtree)){
		rbtree->root=node;
		node->parent=NIL(rbtree);
	}
	else{
		p=rbtree->root;
		while(p!=NIL(rbtree)){
			q=p;
			if(node->key < p->key){
				p=p->left;
			}
			else {
				p=p->right;
			}
		}
		node->parent=q;
		if(node->key < q->key){
			q->left=node;
		}
		else{
			q->right=node;
		}
	}
	node->left=NIL(rbtree);
	node->right=NIL(rbtree);
	rbtree_red(node);
	rbtree_insert_adjust(rbtree,node);
	rbtree->tree_size++;
}

void rbtree_delete_node(rbtree_t *rbtree ,rbtree_node_t *node){
	int black_value;
	rbtree_node_t *temp,*sub;
	if((NULL==rbtree)||(NULL==node)||(node==NIL(rbtree))){
		errno=EINVAL;
		return;
	}
	if(node->left==NIL(rbtree)){
		temp=node;
		sub=node->right;
	}
	else{
		temp=subrbtree_find_min_node(node->right,NIL(rbtree));
		if(temp->left!=NIL(rbtree)){
			sub=temp->left;
		}
		else{
			sub=temp->right;
		}
	}
	if(temp==rbtree->root){
		rbtree->root=sub;
		rbtree_black(sub);
		clear_rbtree_node(temp);
		return;
	}
	black_value=rbtree_test_isblack(temp);
	if(temp->parent==node){
		sub->parent=temp;
	}
	else{
		sub->parent=temp->parent;
	}
	if(temp==temp->parent->left){
		temp->parent->left=sub;
	}
	else{
		temp->parent->right=sub;
	}
	if(temp!=node){
		temp->parent=node->parent;
		if(node==rbtree->root){
			rbtree->root=temp;
		}
		else{
			if(node->parent->left==node){
				node->parent->left=temp;
			}
			else{
				node->parent->right=temp;
			}
		}
		temp->right=node->right;
		temp->left=node->left;
		if(temp->left!=NIL(rbtree)){
			temp->left->parent=temp;
		}
		if(temp->right!=NIL(rbtree)){
			temp->right->parent=temp;
		}
		temp->color=node->color;
	}
	clear_rbtree_node(node);
	if(black_value){
		rbtree_delete_adjust(rbtree,sub);
	}
}

rbtree_node_t* rbtree_search(rbtree_t *rbtree,int key){

}

rbtree_node_t* rbtree_lookup(rbtree_t *rbtree,int key){

}

rbtree_node_t* subrbtree_find_min_node(rbtree_t *rbtree,rbtree_node_t *sentinel){

}

rbtree_node_t* subrbtree_find_max_node(rbtree_t *rbtree,rbtree_node_t *sentinel){

}

void rbtree_mid_travel(rbtree_t *rbtree,void* (*operator)(rbtree_node_t *,void *),void *node_data){

}

static inline void rbtree_insert_adjust(rbtree_t *rbtree,rbtree_node_t *node){

}

static inline void rbtree_delete_adjust(rbtree_t *rbtree,rbtree_node_t *node){

}

static inline void rbtree_adjust_rotate_left(rbtree_t *rbtree,rbtree_node_t *node){

}

static inline void rbtree_adjust_rotate_right(rbtree_t *rbtree,rbtree_node_t *node){

}

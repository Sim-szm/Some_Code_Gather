/*
 * =====================================================================================
 *
 *       Filename:  rbtree.h
 *        Version:  1.0
 *        Created:  2014年03月10日 18时34分16秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef RBTREE_H
#define RBTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;
#define rbtree_black(rbnode)        ((rbnode)->color=1)
#define rbtree_red(rbnode)          ((rbnode)->color=0)
#define rbtree_test_isblack(rbnode) ((rbnode)->color=1)
#define rbtree_test_isred(rbnode)   ((rbnode)->color=0)

typedef struct rbtree_node{
	int color;
	void *node_data;
	int key;
	rbtree_node *parent;
	rbtree_node *left;
	rbtree_node *right;
}rbtree_node_t;

typedef struct rbtree{
	int tree_size;
	rbtree_node_t *root;
	rbtree_node_t null;
}rbtree_t;

typedef struct rbtree_check{
	int height;
	int depth;
	int fini_flag;
	rbtree_node_t *null;
}rbtree_check_t;

#define clear_rbtree_node(node) do{ 	\
	node->parent=NULL; 	\
	node->left=NULL;  	\
	node->right=NULL; 	\
}while(0)  

#define rbtree_is_empty(rbtree) \
	((rbtree)->root==&(rbtree)->null)

#define rbtree_max(rbtree) \
	subrbtree_find_max_node((rbtree)->root,&(rbtree)->null)

#define rbtree_min(rbtree) \
	subrbtree_find_min_node((rbtree)->root,&(rbtree)->null)

void rbtree_init(rbtree_t *rbtree);

void rbtree_insert_ndoe(rbtree_t *rbtree,rbtree_node_t *node);

void rbtree_delete_node(rbtree_t *rbtree,rbtree_node_t *node);

rbtree_node_t* rbtree_search(rbtree_t *rbtree,int key);

rbtree_node_t* rbtree_lookup(rbtree_t *rbtree,int key);

rbtree_node_t* subrbtree_find_min_node(rbtree_node_t *rbtree,rbtree_node_t *sentinel);

rbtree_node_t* subrbtree_find_max_node(rbtree_node_t *rbtree,rbtree_node_t *sentinel);

void rbtree_mid_travel(rbtree_t *rbtree,void* (*operator)(rbtree_node_t *,void *),void *node_data);

static inline void rbtree_insert_adjust(rbtree_t *rbtree,rbtree_node_t *node);

static inline void rbtree_delete_adjust(rbtree_t *rbtree,rbtree_node_t *node);

static inline void rbtree_adjust_rotate_left(rbtree_t *rbtree,rbtree_node_t *node);

static inline void rbtree_adjust_rotate_right(rbtree_t *rbtree,rbtree_node_t *node);

#endif 

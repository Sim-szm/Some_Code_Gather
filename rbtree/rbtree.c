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

void rbtree_init(rbtree_t *rbtree){
	
}

void rbtree_insert_node(rbtree_t *rbtree ,rbtree_node_t *node){

}

void rbtree_delete_node(rbtree_t *rbtree ,rbtree_node_t *node){

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

/*
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Library General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc.
#
# See the COPYING file for license information.
#
#Copyright (c) 2014 sim szm <xianszm007@gmail.com>
*/
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
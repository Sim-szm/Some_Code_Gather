#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256 
//*********************************************
typedef struct node {
	char data;
	struct node *left,*right;
}node;
node *tree_root;
typedef struct queuenode {
	node *val;
	int priority;
	struct queuenode *next;
}queuenode;
typedef struct{
  int size;
  struct queuenode *first;
}queue;
typedef struct hlnode{
	char data;
	char *code;
	struct hlnode *next;
}hlnode;
typedef struct {
	hlnode *first;
	hlnode *last;
}hlchain;
//**********************************************
void init_priority_queue(queue **Queue){
	(*Queue)=(queue *)malloc(sizeof(queue));
	(*Queue)->first=NULL;
	(*Queue)->size=0;
}
void update_queue(queue **Queue,node *val,int priority){
	queuenode *aux,*pos;
     if((*Queue)->size==MAX){
		printf("queue is full !");
		return ;
     }
     aux=(queuenode *)malloc(sizeof(queuenode));
	 aux->priority=priority;
	 aux->val=val;
	if((*Queue)->size==0||(*Queue)->first==NULL){
		aux->next=NULL;
		(*Queue)->first=aux;
		(*Queue)->size++;
	}
	else{
        if(priority <= (*Queue)->first->priority){
            aux->next=(*Queue)->first;
            (*Queue)->first=aux;
            (*Queue)->size++;
        }
        else{
		  pos=(*Queue)->first;
		  while(NULL!=pos->next){
			 if(priority <= pos->next->priority){
				aux->next=pos->next;
				pos->next=aux;
                (*Queue)->size++;
                return ;
             }
			pos=pos->next;
          }
          if(NULL==pos->next){
              aux->next=NULL;
              pos->next=aux;
              (*Queue)->size++;
              return ;
          }
        }
	}
}
node * get_queuenode(queue **Queue){
    node *value;
    if((*Queue)->size > 0){
        value=(*Queue)->first->val;
        (*Queue)->first=(*Queue)->first->next;
        (*Queue)->size--;
    }
    return value;
}
void traver_tree(node *treenode,hlchain **chain,int k,char *code_recond){
    hlnode *aux;
    if(treenode->left==NULL && treenode->right==NULL){
        code_recond[k]='\0';
        aux=(hlnode *)malloc(sizeof(hlnode));
        aux->code=(char *)malloc(sizeof(char)*strlen(code_recond));
        strcpy(aux->code,code_recond);
        aux->data=treenode->data;
        aux->next=NULL;
        if((*chain)->first==NULL){
            (*chain)->first=aux;
            (*chain)->last=aux;
        }else{
            (*chain)->last->next=aux;
            (*chain)->last=aux;
        }
    }
    if(treenode->left!=NULL){
        code_recond[k]='0';
        traver_tree(treenode->left,chain,k+1,code_recond);
    }
    if(treenode->right!=NULL){
        code_recond[k]='1';
        traver_tree(treenode->right,chain,k+1,code_recond);
    }
}
hlchain * chain_value(node *tree_root){
    char code_recond[MAX];
    int k=0;
    hlchain *chain=(hlchain *)malloc(sizeof(hlchain));
    chain->first=NULL;
    chain->last=NULL;
    traver_tree(tree_root,&chain,k,code_recond);
    return chain;
}
node * create_tree(char *inputstring){
    int i;
    int priority=0;
    queue *pri_queue;
    node *newnode,*left,*right;
	int *probably=(int *)malloc(sizeof( int )*MAX );
    for(i=0;i<MAX;i++){
        probably[i]=0;
    }
    for(i=0;inputstring[i]!='\0';i++){
        probably[(unsigned char)inputstring[i]]++;
        //printf("\n*************\n%d \n****************\n",proba[(unsigned char)inputstring[i]]);
    }
    init_priority_queue(&pri_queue);
    for(i=0;i<MAX;i++){
        if(probably[i]!=0){
            node *aux=(node*)malloc(sizeof(node));
            aux->left=NULL;
            aux->right=NULL;
            aux->data=(char)i;
            update_queue(&pri_queue,aux,probably[i]);
        }
    }
    free(probably);
    while(pri_queue->size!=1){
        priority=pri_queue->first->priority;
        priority+=pri_queue->first->next->priority;
        left=get_queuenode(&pri_queue);
        right=get_queuenode(&pri_queue); 
        newnode =(node *)malloc(sizeof(node));
        newnode->left=left;
        newnode->right=right;

        update_queue(&pri_queue,newnode,priority);
    }
    tree_root=(node *)malloc(sizeof(node));
    tree_root=get_queuenode(&pri_queue);
    return tree_root;
}
void encode(char *encode_string,hlchain *chain){
    int i;
    hlnode *p;
    for(i=0; encode_string[i]!='\0'; i++){
		p = chain->first;
		while(p->data != encode_string[i])
			p = p->next;
		printf("\n*******\nthe < '%c' > encode binary string is %s ",p->data,p->code);
	}
    printf("\n");
}
void decode(node *tree_root ,char *decode_string){
    node *p=tree_root;
    int i;
	printf("decoding as string : ");
    for(i=0;decode_string[i]!='\0';i++){
        if(p->left==NULL && p->right==NULL){
            printf("%c",p->data);
            p=tree_root;
        }
        if(decode_string[i]=='0'){
            p=p->left;
        }
        if(decode_string[i]=='1'){
            p=p->right;
        }
        if(decode_string[i]!='0' && decode_string[i]!='1'){
            printf("encode error ! can not identify \n");
            return ;
        }
    }
    if(p->left==NULL &&p->right==NULL){
        printf("%c",p->data);
        p=tree_root;
    }
    printf("\n");

}
int main(void){
    char inputstring[MAX];
    char decoding[MAX];
	int flag=1;
    node *codetree;
    hlchain *chain;
    printf("input the string to encoding : ");
	fflush( stdin );
    gets(inputstring );
    codetree=create_tree(inputstring);
    chain=chain_value(codetree);
    encode(inputstring,chain);
	puts("\n****************************");
	while(flag){
	  printf("input the number string to decoding : ");
	  fflush(stdin);
	  gets(decoding);
      decode(codetree,decoding);
	  printf("\nchoose the flag's value continue ( '1' ) or not ( '0' ) ?= : ");
	  scanf("%d",&flag);
	}
	return 0;
}

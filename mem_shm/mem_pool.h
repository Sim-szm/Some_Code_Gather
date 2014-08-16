/*
 * =====================================================================================
 *
 *       Filename:  mem_pool.h
 *        Version:  1.0
 *        Created:  2014年08月11日 16时29分57秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
class MemPool{
public:
	MemPool(): m_pHeader(NULL),m_pData(NULL){
	}

	~MemPool(){
	}
	
	typedef struct allocBlock{
		unsigned int flag;
		unsigned int next;
	}AllocBlock_t;

	typedef struct memHeader{
		unsigned int maxSize;   // maxsize could be alloc
		unsigned int allocSize; // size of already alloced
		unsigned int nodeSize;  // node size
		unsigned int blockSize; // alloc block size
		unsigned int freeList;  // free list 
	}MemHeader;
	
	inline unsigned int Ref(void* p){
		return ((char *)p-(char *)m_pHeader);
	}

	inline void* Deref(unsigned int pos){
		return ((char *)m_pHeader + pos);
	}
	
	const MemHeader* getMemheader() const{
	    return m_pHeader;
	}

	const char* get_errMsg() const {
	    return m_errMsg;
	}

	int init(int key,unsigned int maxSize,\
				unsigned int nodeSize,\
				bool exist){
		exist = false;
		int shmid = shmget(key,maxSize,IPC_CREAT \
					| IPC_EXCL | 0644);
		if(shmid < 0){
			if(errno != EEXIST){
				snprintf(m_errMsg,sizeof(m_errMsg),\
						"MemPool init shmget error,\
						key=%d,size=%d,errno=%d,errMsg=%s",
						key,size,errno,strerror(errno));
				return -1;
			}
			exist = true;
			shmid = shmget(key,maxSize,0644);
			if(shmid < 0){
				snprintf(m_errMsg,sizeof(m_errMsg),\
						"MemPool init shmget alreadyzone error,
						key=%d,size=%d,errno=%d,errMsg=%s",
						key,size,errno,strerror(errno));
				return -1;
			}
		}
		void* pShm = shmat(shmid,NULL,0);
		if(!pShm){
			snprintf(m_errMsg,sizeof(m_errMsg),\
					"MemPool init shmat attach error,\
					key=%d,size=%d,errno=%d,errMsg=%s",
					key,size,errno,strerror(errno));
			return -1;
		}
		m_pHeader = (MemHeader *)pShm;
		if (exist){
			m_pData = (char *)m_pHeader + sizeof(MemHeader);
		}else{
			m_pHeader->maxSize = maxSize;
			m_pHeader->allocSize = sizeof(MemHeader);
			m_pHeader->nodeSize = nodeSize;
			m_pHeader->maxSize = maxSize;
			m_pHeader->blockSize = (nodeSize + sizeof(int) + 3) & ~3;
			m_pHeader->freeList = 0;
			m_pData = (char *)m_pHeader + sizeof(MemHeader);
		}
		return 0;
	}
	
	AllocBlock_t* getfreeBlock(){
		AllocBlock_t *p = NULL;
		if(m_pHeader->freeList == 0){
			p =NULL;
		}else{
			p = (AllocBlock_t *)Deref(m_pHeader->freeList);
			m_pHeader->freeList = p->next;
			p->flag = 1;
		}
		return p;
	}

	void* Alloc(bool zero = true){
		AllocBlock_t *p = getfreeBlock();
		if(NULL == p){
		    //free is NULL , alloc from mem
			if(m_pHeader->allocSize + m_pHeader->blockSize <=\
				    m_pHeader->maxSize){
				p = (AllocBlock_t *)Deref(m_pHeader->allocSize);
				m_pHeader->allocSize += m_pHeader->blockSize;
			}
		}else if(p){
			if(zero)
			  memset(p,0,sizeof(m_pHeader->blockSize));
			p->flag = 1;
			return ((char *)p + (int)sizeof(int));
		}else{
			return NULL;
		}
	}
	
	void linkfreeBlock(AllocBlock_t *p){
	    p->flag = 0;
	    p->next = m_pHeader->freeList;
	    m_pHeader->freeList = Ref(p);
	}

	int Free(void *p){
		AllocBlock_t *pBlock = (AllocBlock_t *)((char *)p - sizeof(int));
		int n = (char *)pBlock - (char *)m_pData;
		if(n <0 || (unsigned int)n + sizeof(MemHeader) >= m_pHeader->allocSize\
			    || n % m_pHeader->blockSize){
			snprintf(m_errMsg,sizeof(m_errMsg),\
					"MemPool Free pointer error,\
				header=%p,maxSize=%u,allocSize=%u,blockSize=%u",
				m_pHeader,m_pHeader->maxSize,m_pHeader->allocSize,\
				m_pHeader->blockSize);
			return -1;
			
		}
		if(pBlock->flag != 1){
		    return -1;
		}
		linkfreeBlock(pBlock);
		return 0;
	}

protected:
	char* m_errMsg[256];
	MemHeader* m_pHeader;
	void*  m_pData;
};

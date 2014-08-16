/*
 * =====================================================================================
 *
 *       Filename:  shm_map.h
 *        Version:  1.0
 *        Created:  2014年08月12日 18时22分37秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef SHM_MAP_H
#define SHM_MAP_H

#include <map>
#include "mem_pool.h"
template <typename keytype, typename nodetype>
class ShmemkeyMap:public MemPool{
protected:
    typedef std::map<keytype,nodetype*> nodemap;
    nodemap m_NodeMap;
    typename nodemap::iterator m_Iter;
public:
    ShmemkeyMap(){
    	m_NodeMap.clear();
	m_Iter = m_NodeMap.end();
    }

    virtual ~ShmemkeyMap(){
    }

    virtual int Recover(){
    	AllocBlock_t *pBlock = (AllocBlock_t *)m_pData;
        while((unsigned long)pBlock - (unsigned long)m_pHeader <\
                    m_pHeader->allocSize)	{
            if(pBlock->flag == 1){
                keytype *pKey = (keytype *)((char *)pBlock + sizeof(int));
                nodetype *pNode = (nodetype *)((char *)pBlock + sizeof(int)\
                            +sizeof(keytype));
                m_NodeMap.insert(typename nodemap::value_type(*pKey,pNode));
            }else if(pBlock->flag !=0){
                return -1;
            }
            pBlock = (AllocBlock_t *)((char *)pBlock + m_pHeader->blockSize);
        }
        return 0;
    }
    int AddNode(const Keytype &key, nodetype * &pNode){
        if ((m_Iter = m_NodeMap.find(key)) == m_NodeMap.end()){
            void * pAlloc = NULL;
            if ((pAlloc = Alloc()) != NULL){
                *(keytype *)pAlloc = key;
                pNode = (nodetype *)((char *)pAlloc + sizeof(keytype));

                std::pair<typename NodeMap::iterator, bool> result;
                result = m_NodeMap.insert(typename NodeMap::value_type(key, pNode));
                if (!result.second){
                    pNode = NULL;
                    Free(pAlloc);
                    return -1;
                }

                return 0;
            }else{
                return -1;
            }
        }else{
            pNode = m_Iter->second;
            return 1;
        }
    }

    void DelNode(const keytype & key){
        if ((m_Iter = m_NodeMap.find(key)) != m_NodeMap.end()){
            void * pAlloc = (char *)(m_Iter->second) - sizeof(keytype);
            m_NodeMap.erase(m_Iter);
            Free(pAlloc);
        }
    }

    nodetype * GetNode(const keytype & key){
        if ((m_Iter = m_NodeMap.find(key)) != m_NodeMap.end()){
            return m_Iter->second;
        }else{
            return NULL;
        }
    }

};
#endif

/**
* @file myeTokenList.h
* @brief ；链表
* @author yuming.cheng <yuming.cheng@ape-tech.com>
* @version 1-0
* @date 2014-05-14
*/

#ifndef _MYETOKENLIST_H_
#define _MYETOKENLIST_H_

#include "myeCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _myeToken
{
    int offet;
    
    
}myeToken;


typedef struct _myeTokenList
{   
    int num_token;
    myeToken* head;

}myeTokenList;



myeTokenList* myeTokenList_new();

int myeTokenList_add_token(myeToken* p_token);




#ifdef __cplusplus
}
#endif

#endif

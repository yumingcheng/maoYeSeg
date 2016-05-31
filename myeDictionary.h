/**
* @file myeDictionary.h
* @brief 辞典,词汇查寻程序
* @author yuming.cheng <yuming.cheng@ape-tech.com>
* @version 1-0
* @date 2014-05-14
*/


#ifndef _MYE_DICTIONARY_H_
#define _MYE_DICTIONARY_H_

#include "myeCommon.h"


#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _myeDictionary
{
   GHashTable* g_word_fre_dic; 
   GHashTable* g_ngram_fre_dic;
        
}myeDictionary;

myeDictionary* myeDictionary_init();
int myeDictionary_query(myeDictionary* me,const char* p_query,int* frequence);
int myeDictionary_n_query(myeDictionary* me,const char* p_query,int query_size,int* frequence);

int myeDictionary_query_ngram(myeDictionary* me,const char* p_query,int* frequence);
int myeDictionary_n_query_ngram(myeDictionary* me,const char* p_query,int query_size,int* frequence);

int myeDictionary_reload(myeDictionary* me,const char* p_dic_path);

int myeDictionary_load(myeDictionary* me,const char* p_dic_path);
int myeDictionary_load_ngram(myeDictionary* me,const char* p_dic_path);

int myeDictionary_free(myeDictionary* me);





#ifdef __cplusplus
}
#endif

#endif

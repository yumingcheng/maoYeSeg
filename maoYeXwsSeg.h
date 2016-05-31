/**
* @file maoYeXwsSeg.h
* @brief mmSeg4j算法分词
* @author yuming.cheng <yuming.cheng@ape-tech.com>
* @version 1-0
* @date 2014-05-14
*/


#ifndef _MAOYE_XWS_SEG_H_
#define _MAOYE_XWS_SEG_H_

#include "maoYeSeg.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _maoYeXwsSeg maoYeXwsSeg;

maoYeXwsSeg* maoYeXwsSeg_new(const char* dic_path);

void maoYeXwsSeg_delete(maoYeSeg* s_me);

int maoYeXwsSeg_string_tokenize(maoYeSeg* s_me,const char* lpzwInput,void* ppToken);

int maoYeXwsSeg_list_tokenize(maoYeSeg* s_me,const char* lpzwInput,void* ppToken);

int maoYeXwsSeg_setopt(maoYeSeg* s_me,int TYPE,void* p_date);




#ifdef __cplusplus
}
#endif

#endif

/**
* @file maoYeMMSeg.h
* @brief mmSeg4j算法分词
* @author yuming.cheng <yuming.cheng@ape-tech.com>
* @version 1-0
* @date 2014-05-14
*/


#ifndef _MAOYE_MM_SEG_H_
#define _MAOYE_MM_SEG_H_

#include "maoYeSeg.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _maoYeMMSeg maoYeMMSeg;


maoYeMMSeg* maoYeMMSeg_new(const char* dic_path);

void maoYeMMSeg_delete(maoYeSeg* me);

int maoYeMMSeg_string_tokenize(maoYeSeg* me,const char* lpzwInput,void* ppToken);

int maoYeMMSeg_list_tokenize(maoYeSeg* me,const char* lpzwInput,void* ppToken);

int maoYeMMSeg_setopt(maoYeSeg* me,int TYPE,void* p_date);






#ifdef __cplusplus
}
#endif

#endif

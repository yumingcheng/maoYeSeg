/**
* @file maoYeSeg.h
* @brief 分词主结构
* @author yuming.cheng <yuming.cheng@ape-tech.com>
* @version 1-0
* @date 2014-05-14
*/

#ifndef _MAOYE_SEG_H_
#define _MAOYE_SEG_H_


#include "myeCommon.h"
#include "myeStringUtil.h"
#include "myeSegEngine.h"
#include "myeDictionary.h"
#include "myeTokenList.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define ALG_MM4JSEG 0x00000001
#define ALG_XWSNGRAM 0x00000010

typedef struct _maoYeSeg maoYeSeg;



typedef struct _maoYeSegClass
{
    char m_name[56]; 
    //构造函数
    maoYeSeg* (* Constructor)(int cflag);
    //析构函数
    void (* Destructor)(maoYeSeg* me);
       
    //分词主程序 
    int (* string_tokenize)(maoYeSeg* me,const char* lpzwInput,void* ppToken);
    
    //分词主程序
    int (* list_tokenize)(maoYeSeg* me,const char* lpzwInput,void* ppToken);

    int (*setopt)(maoYeSeg* me,int TYPE,void* pdate);

    int i;
    int n;
    int j;

}maoYeSegClass;



maoYeSeg* maoYeSeg_new(int cflag);

void maoYeSeg_delete(maoYeSeg* me);

int maoYeSeg_string_tokenize(maoYeSeg* me,const char* lpzwInput,void* ppToken);

int maoYeSeg_list_tokenize(maoYeSeg* me,const char* lpzwInput,void* ppToken);

int maoYeSeg_setopt(maoYeSeg* me,int TYPE,void* p_date);



#ifdef __cplusplus
}
#endif

#endif



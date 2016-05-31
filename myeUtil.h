/**
 * @file maoYeUtil.h
 * @brief utf8字符串判断处理
 * @author yuming.cheng <yuming.cheng@ape-tech.com>
 * @version 1-0
 * @date 2014-05-09
 */

#ifndef _MAOYE_UTIL_H_
#define _MAOYE_UTIL_H_

#include "myeCommon.h"
#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct _myeList
    {
        void* data;
        struct _myeList* next;
        struct _myeList* prior;
        int maxTop;

    }myeList;

    typedef int (*myeCompareFunc)(const void* a, const void* b,const void* arg);

    myeList* mye_list_insert_compare(myeList* list,void* data,myeCompareFunc mye_compare,void* compare_arg);

    myeList* mye_list_insert(myeList* list,void* data);

    void mye_list_free(myeList* list);

    void* mye_list_find_top(myeList* list);




#ifdef __cplusplus
}
#endif

#endif

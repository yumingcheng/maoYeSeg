/**
* @file myeStringUtil.h
* @brief 分词字符串处理
* @author yuming.cheng <yuming.cheng@ape-tech.com>
* @version 1-0
* @date 2014-05-14
*/


#ifndef _MAOYE_STRING_UTIL_H_
#define _MAOYE_STRING_UTIL_H_

#include "myeCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

//unicode2/utf16 根据编码查看在65535个编码字符中的位置
#define UCS_ENCODE_TO_INDEX(h) ((0xFF & h[0]) << 8) | (0xFF & h[1]) 
//unicode2/utf16 根据在65535个编码中的位置，获取编码字符
#define UCS_INDEC_TO_ENCODE(i, h) (h[0] = (i/256), h[1] = (i%256), h)

int myeutil_get_first_atom_len(const char* buf,int* type);


//FE FF　　　　　UTF-16/UCS-2, little endian
//FF FE　　　　　UTF-16/UCS-2, big endian
int myeutil_utf8_to_unicode(char* dest,int* size_d,const char* src,int bom); 
int myeutilm_utf8_to_unicode(char* dest,int* size_d,const char* src,int size_n,int bom); 

int myeutilm_unicode_to_utf8(char* dest,const char* src,int size_n,int bom); 

int myeutil_full_to_half_angle(char** dest,const char* src);
int myeutilm_full_to_half_angle(char** dest,const char* src,int size_n);


#ifdef __cplusplus
}
#endif


#endif

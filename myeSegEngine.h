/**
* @file myeSegEngine.h
* @brief 分词核心部分,n-最短距离
* @author yuming.cheng <yuming.cheng@ape-tech.com>
* @version 1-0
* @date 2014-05-09
*/

#ifndef _MAOYE_SEGENGINE_H_
#define _MAOYE_SEGENGINE_H_

#include "myeDictionary.h"
#include "myeTokenList.h"
#include "myeUtil.h"

typedef struct _mmsegAnalyse mmsegAnalyse;
typedef struct _xwsAnalyse xwsAnalyse;
typedef struct _wordItem wordItem;

typedef struct _myeAtomsNode
{
    int offset;
    int max_path;
    int num_atoms;
    char* atoms_string;     
    wordItem* p_word_item;
    
    //一个myeArray内单元前后 
    struct _myeAtomsNode* next; 
    struct _myeAtomsNode* prior; 

    //跨myeArray指针前后
    struct _myeAtomsNode* far_next;
    struct _myeAtomsNode* far_prior;

    //mmsegAnalyse* analyse_array;
    void* analyse_array;
    int num_array_used;
    
}myeAtomsNode;

struct _mmsegAnalyse
{
    int flag_use; //1已经使用 零可以使用
    int from_index; //指向位置index
    int seg_ranking;//当前结果排名

    //跨myeArray指针前后
    myeAtomsNode* far_next;
    myeAtomsNode* far_prior;

    //所以在myeAtomsNode
    myeAtomsNode* location;

    int seg_step; //节点个数

    int atoms_length; //最大匹配长度
    double average_length;//平均词长
    double variance_length;//词长标准差
    double morphemic_freedom;//单字词自由语素度

    //一个myeArray内单元前后 
    struct _mmsegAnalyse* next; 
    struct _mmsegAnalyse* prior; 

};

struct _xwsAnalyse
{
    //所以在myeAtomsNode
    myeAtomsNode* location;
    int flag_use; //1已经使用 零可以使用

    double nowLength;//路径长度

    //跨myeArray指针前后
    myeAtomsNode* far_next;
    myeAtomsNode* far_prior;

    //一个myeArray内单元前后 
    struct _xwsAnalyse* next; 
    struct _xwsAnalyse* prior; 

};

/* --------------------------------------------------------------------------*/
/**
* @brief _myeNode 结构体.存放word_node_array 词组
*/
/* --------------------------------------------------------------------------*/
typedef struct _myeArray
{
    //最多指向个数
    int max_path;
    
    //节点词组个数
    int num_node;

    //最长array内部字符串原子单元atom个数
    int max_atoms_in_array;

    //标记数据类型
    int mye_array_type;

    myeAtomsNode*  mye_node_head;
    myeAtomsNode*  mye_node_end;

}myeArray;

typedef struct _myeSegEngine
{
    int max_array_list_length; //数组最长
    int max_array_list_used;//使用长度
    myeDictionary* mye_dic;
    myeArray* mye_array_list; 
    
}myeSegEngine;

struct _wordItem
{
    char* p_str;            //字符串指针
    int str_size;           //字符串长度
    int num_atoms;          //原子词个数
    int add_index;          //添加的index位置
    int atoms_string_type;  //头尾等特殊标记
    int atoms_string_fre;   //词频
    int atoms_string_handle;//词性
};

myeSegEngine* myeSegEngine_init(int max_array_list_length , myeDictionary* mye_dic);

int myeSegEngine_add(myeSegEngine* me,const char* p_str,int str_size,int num_atoms,int add_index,int atoms_string_type);

int myeSegEngine_add_full(myeSegEngine* me,wordItem* p_word_item);

int myeSegEngine_memset(myeSegEngine* me);

int myeSegEngine_free(myeSegEngine* me);

/*********** MMSeg4j 算法函数  *****************/

int myeSegEngine_mmseg4j_calculate(myeSegEngine* me);

int myeSegEngine_get_mmseg_result(myeSegEngine* me,myeTokenList* p_token_list);


/*********** Xws 算法函数  *****************/

int myeSegEngine_xws_calculate(myeSegEngine* me);

int myeSegEngine_get_nshort_paths(myeSegEngine* me,int index);

int myeSegEngine_get_xws_result(myeSegEngine* me,myeTokenList* p_token_list);


#endif













#include "myeSegEngine.h"


myeSegEngine* myeSegEngine_init(int max_array_list_length,myeDictionary* mye_dic)
{
    myeSegEngine* me = (myeSegEngine*)calloc(1,sizeof(myeSegEngine));
    me->mye_array_list = (myeArray*)calloc(2000,sizeof(myeArray));    
    me->max_array_list_length = 2000;
    me->mye_dic = mye_dic;
    return me;    
}


int myeSegEngine_add(myeSegEngine* me,const char* p_str,int str_size,int num_atoms,int add_index,int atoms_string_type)
{   
    if(add_index > 2000)
        return -1;

    myeArray* mye_array_list = me->mye_array_list;
    myeAtomsNode* p_temp_node = NULL;
    myeAtomsNode* p_end_node = NULL;
    myeAtomsNode* p_head_node = NULL;

    mye_array_list[add_index].mye_array_type = atoms_string_type;
    p_head_node = mye_array_list[add_index].mye_node_head;


    p_temp_node = (myeAtomsNode*)calloc(1,sizeof(myeAtomsNode));                   
    p_temp_node->atoms_string = (char*)calloc(1,str_size+1);
    strncpy(p_temp_node->atoms_string,p_str,str_size);
    p_temp_node->offset = add_index;
    printf("%s/%d/%d\n",p_temp_node->atoms_string,add_index,str_size);
    if(add_index == 0)
    {
        p_temp_node->max_path = 1;
        mye_array_list[add_index].max_path = 1;
    }
    else
        p_temp_node->max_path = mye_array_list[add_index].max_path;
    p_temp_node->num_atoms = num_atoms;

    if(p_head_node == NULL)
    {
        mye_array_list[add_index].mye_node_head = p_temp_node;
        p_temp_node->next = p_temp_node;
        p_temp_node->prior = p_temp_node;
    }
    else 
    {
        p_temp_node -> next = p_head_node->prior->next;
        p_head_node->prior->next = p_temp_node;
        p_temp_node -> prior = p_head_node->prior;
        p_head_node->prior = p_temp_node;
    }

    mye_array_list[add_index+num_atoms].max_path += 1;
    mye_array_list[add_index].num_node += 1;
    if(me->max_array_list_used < add_index)
        me->max_array_list_used = add_index;
    if(mye_array_list[add_index].max_atoms_in_array < num_atoms)
        mye_array_list[add_index].max_atoms_in_array = num_atoms;
    return 0;
}

int myeSegEngine_add_full(myeSegEngine* me,wordItem* p_word_item)
{

    int add_index = p_word_item->add_index;
    int num_atoms = p_word_item->num_atoms;
    int atoms_string_type = p_word_item->atoms_string_type;
    int str_size = p_word_item->str_size;
    if(add_index > 2000)
        return -1;

    myeArray* mye_array_list = me->mye_array_list;
    myeAtomsNode* p_temp_node = NULL;
    myeAtomsNode* p_end_node = NULL;
    myeAtomsNode* p_head_node = NULL;

    mye_array_list[add_index].mye_array_type = atoms_string_type;
    p_head_node = mye_array_list[add_index].mye_node_head;


    p_temp_node = (myeAtomsNode*)calloc(1,sizeof(myeAtomsNode));                   
    p_temp_node->atoms_string = (char*)calloc(1,str_size+1);
    strncpy(p_temp_node->atoms_string,p_word_item->p_str,p_word_item->str_size);
    p_temp_node->offset = add_index;
    p_temp_node -> p_word_item = (wordItem*)calloc(1,sizeof(wordItem));
    memcpy(p_temp_node->p_word_item,p_word_item,sizeof(wordItem));
    printf("add{%s/%d/%d/%d}\n",p_temp_node->atoms_string,add_index,p_word_item->str_size,p_temp_node->p_word_item->atoms_string_fre);
    if(add_index == 0)
    {
        p_temp_node->max_path = 1;
        mye_array_list[add_index].max_path = 1;
    }
    else
    {
        p_temp_node->max_path = mye_array_list[add_index].max_path;
    }
    
    p_temp_node->num_atoms = num_atoms;
    if(p_head_node == NULL)
    {
        mye_array_list[add_index].mye_node_head = p_temp_node;
        p_temp_node->next = p_temp_node;
        p_temp_node->prior = p_temp_node;
    }
    else 
    {
        p_temp_node -> next = p_head_node->prior->next;
        p_head_node->prior->next = p_temp_node;
        p_temp_node -> prior = p_head_node->prior;
        p_head_node->prior = p_temp_node;
    }

    mye_array_list[add_index+num_atoms].max_path += 1;
    mye_array_list[add_index].num_node += 1;
    if(me->max_array_list_used < add_index)
        me->max_array_list_used = add_index;
    if(mye_array_list[add_index].max_atoms_in_array < num_atoms)
        mye_array_list[add_index].max_atoms_in_array = num_atoms;
    return 0;
}

int myeSegEngine_memset(myeArray* mye_array_list,int start_index,int end_index,int (*memset_fun)(void*,int))
{
//    int i = 0; 
//    myeAtomsNode* p_cur_node = NULL;
//    for(i = start_index; i < end_index; i++) 
//    {
//        p_cur_node = NULL;
//        do
//        {
//            p_cur_node = mye_array_list[i].mye_node_head;
//            if(p_cur_node == NULL)
//            {
//                break;
//            }
//            else
//            {
//                p_cur_node->far_next = NULL;
//                p_cur_node->far_prior = NULL;
//                p_cur_node->num_array_used= 0;
//                memset_fun(p_cur_node->analyse_array,p_cur_node->max_path);
//                p_cur_node->analyse_array = NULL;    
//                p_cur_node = p_cur_node->prior;
//            }
//
//        }while(p_cur_node != mye_array_list[i].mye_node_head);
//    }
    return 0;
}


int myeSegEngine_free(myeSegEngine* me)
{
    free(me->mye_array_list);
    free(me);
    return 0;
}

/*********** MMSeg4j 算法函数  *****************/


static int mmseg_get_result(myeAtomsNode** p_atoms_node,myeList* list);
static int order_by_mmseg4j(const void* p1,const void* p2,const void* mye_dic);
static double mmseg_morphemic_freedom_calculate(mmsegAnalyse* analyse_array,int len_array,myeDictionary* mye_dic);
static mmsegAnalyse* mmseg_insert_analyse_myeatomsnode(myeAtomsNode* p_cur_node,myeAtomsNode* p_prior_node,int seg_step,int atoms_length,double average_length,double variance_length,int flag_cover);
static int mmseg_node_free(int index,myeArray* mye_array_list);


static int mmseg_get_result(myeAtomsNode** p_atoms_node,myeList* list)
{
    mmsegAnalyse* m_analyse = (mmsegAnalyse*)mye_list_find_top(list);
    if(m_analyse == NULL)
    {
        return -1;
    }
    else
    {
        if(m_analyse -> seg_step == 1)
        {
            *p_atoms_node = m_analyse->location;
            return 0;
        }
        else if(m_analyse -> seg_step == 2)
        {
            *p_atoms_node = m_analyse->far_prior;
            return 0;
        }
        else if(m_analyse-> seg_step == 3)
        {
            *p_atoms_node = (m_analyse->far_prior)->far_prior;
            return 0;
        }

    }
    return 0;
}

static int order_by_mmseg4j(const void* p1,const void* p2,const void* mye_dic)
{
    //    printf("%s() \n",__func__);
    if(((mmsegAnalyse*)p1) ->atoms_length > ((mmsegAnalyse*)p2) -> atoms_length)  //atoms_length 
    {
        return 1;
    }
    else if(((mmsegAnalyse*)p1)->atoms_length < ((mmsegAnalyse*)p2)-> atoms_length)
    {
        return -1;
    }
    else 
    {
        if(((mmsegAnalyse*)p1) ->seg_step > ((mmsegAnalyse*)p2) -> seg_step)  //average_length
        {
            return -1;
        }
        else if(((mmsegAnalyse*)p1) ->seg_step < ((mmsegAnalyse*)p2) -> seg_step)
        {
            return 1;
        }
        else 
        {
            if(((mmsegAnalyse*)p1) ->variance_length  - ((mmsegAnalyse*)p2) -> variance_length > 1e-10)  //variance_length
            {
                return -1;
            }
            else if(((mmsegAnalyse*)p1) ->variance_length - ((mmsegAnalyse*)p2) -> variance_length < -1e-10)
            {
                return 1;
            }
            else 
            {
                double p1_freedom =  mmseg_morphemic_freedom_calculate(((mmsegAnalyse*)p1),((mmsegAnalyse*)p1)->seg_step,(myeDictionary*)mye_dic);
                double p2_freedom =  mmseg_morphemic_freedom_calculate(((mmsegAnalyse*)p2),((mmsegAnalyse*)p2)->seg_step,(myeDictionary*)mye_dic);
                printf("morphemic_freedom [%lf][%lf]\n",p1_freedom,p2_freedom);

                if( p1_freedom - p2_freedom > 1e-10 )  //morphemic_freedom
                {
                    return 1;
                }
                else if( p1_freedom - p2_freedom < -1e-10)
                {
                    return -1;
                }
                else 
                {
                    return 0;
                }
                return 0;
            }
            return 0;
        }
        return 0;
    }

    return 0;
}

static mmsegAnalyse* mmseg_insert_analyse_myeatomsnode(myeAtomsNode* p_cur_node,myeAtomsNode* p_prior_node,int seg_step,int atoms_length,double average_length,double variance_length,int flag_cover)
{
    //    printf("%d/%d/%s\n",p_cur_node->max_path,p_cur_node->num_array_used,p_cur_node->atoms_string);
    if(p_cur_node->analyse_array == NULL && p_cur_node->max_path > 0)
    {
        p_cur_node->analyse_array = (mmsegAnalyse*)calloc(p_cur_node->max_path,sizeof(mmsegAnalyse));
        ((mmsegAnalyse*)(p_cur_node->analyse_array))[0].far_prior = p_prior_node;
        ((mmsegAnalyse*)(p_cur_node->analyse_array))[0].location = p_cur_node;
        ((mmsegAnalyse*)(p_cur_node->analyse_array))[0].flag_use = 1;
        ((mmsegAnalyse*)(p_cur_node->analyse_array))[0].seg_step = seg_step;
        ((mmsegAnalyse*)(p_cur_node->analyse_array))[0].average_length = average_length;
        ((mmsegAnalyse*)(p_cur_node->analyse_array))[0].variance_length = variance_length;
        ((mmsegAnalyse*)(p_cur_node->analyse_array))[0].atoms_length = atoms_length;
        p_cur_node->num_array_used += 1;
        return &(((mmsegAnalyse*)(p_cur_node->analyse_array))[0]);

    }
    else
    {
        int i = 0;
        for(i = 0; i < p_cur_node->max_path; i++)
        {   
            //           printf("查寻覆盖 %d\n",i);
            if(((mmsegAnalyse*)(p_cur_node->analyse_array))[i].far_prior == p_prior_node || flag_cover == 1)
            {
                //                printf("重复覆盖 flag_cover = %d\n",flag_cover);
                ((mmsegAnalyse*)(p_cur_node->analyse_array))[i].far_prior = p_prior_node;
                ((mmsegAnalyse*)(p_cur_node->analyse_array))[i].location = p_cur_node;
                ((mmsegAnalyse*)(p_cur_node->analyse_array))[i].flag_use = 1;
                ((mmsegAnalyse*)(p_cur_node->analyse_array))[i].seg_step = seg_step;
                ((mmsegAnalyse*)(p_cur_node->analyse_array))[i].average_length = average_length;
                ((mmsegAnalyse*)(p_cur_node->analyse_array))[i].variance_length = variance_length;
                ((mmsegAnalyse*)(p_cur_node->analyse_array))[i].atoms_length = atoms_length;
                return &(((mmsegAnalyse*)(p_cur_node->analyse_array))[i]);
            }
        }
        if(p_cur_node->num_array_used < p_cur_node->max_path)
        {
            //                printf("还有空余\n");
//            (mmsegAnalyse)((p_cur_node->analyse_array)[p_cur_node->num_array_used]).far_prior = p_prior_node;

            ((mmsegAnalyse*)(p_cur_node->analyse_array))[p_cur_node->num_array_used].far_prior = p_prior_node;
            ((mmsegAnalyse*)(p_cur_node->analyse_array))[p_cur_node->num_array_used].location = p_cur_node;
            ((mmsegAnalyse*)(p_cur_node->analyse_array))[p_cur_node->num_array_used].flag_use = 1;
            ((mmsegAnalyse*)(p_cur_node->analyse_array))[p_cur_node->num_array_used].seg_step = seg_step;
            ((mmsegAnalyse*)(p_cur_node->analyse_array))[p_cur_node->num_array_used].average_length = average_length;
            ((mmsegAnalyse*)(p_cur_node->analyse_array))[p_cur_node->num_array_used].variance_length = variance_length;
            ((mmsegAnalyse*)(p_cur_node->analyse_array))[p_cur_node->num_array_used].atoms_length = atoms_length;
            int id = p_cur_node->num_array_used;
            p_cur_node->num_array_used += 1;
            return &(((mmsegAnalyse*)(p_cur_node->analyse_array))[id]);
        }
    }
    return NULL;
}

static double mmseg_morphemic_freedom_calculate(mmsegAnalyse* analyse_array,int len_array,myeDictionary* mye_dic)
{   
    int i = 0 ;
    double morphemic_freedom = 0.0;
    morphemic_freedom = 0.0;
    if(analyse_array -> seg_step >= 1)
    {
        if(analyse_array -> location -> num_atoms == 1)
        {   
            int temp_fre = 0; 
            //            printf("%s() [%d] [%s] \n",__func__,1,analyse_array->location->atoms_string);
            if(myeDictionary_query(mye_dic,analyse_array->location->atoms_string,&temp_fre))
            {
                //                printf("[%d] \n",temp_fre);
                morphemic_freedom += log(temp_fre);
            }
        }
    }

    if(analyse_array -> seg_step >=2)
    {   
        if(analyse_array ->far_prior->num_atoms == 1)
        {   
            int temp_fre = 0; 
            //            printf("%s() [%d] [%s] \n",__func__,2,analyse_array->far_prior->atoms_string);
            if(myeDictionary_query(mye_dic,analyse_array->far_prior->atoms_string,&temp_fre))
            {
                //                printf("[%d] \n",temp_fre);
                morphemic_freedom += log(temp_fre);
            }
        }
    }

    if(analyse_array -> seg_step >= 3)
    {
        if(analyse_array -> far_prior->far_prior->num_atoms == 1)
        {
            int temp_fre = 0; 
            //            printf("%s() [%d] [%s] \n",__func__,3,analyse_array->far_prior->far_prior->atoms_string);
            if(myeDictionary_query(mye_dic,analyse_array->far_prior->far_prior->atoms_string,&temp_fre))
            {
                //                printf("[%d] \n",temp_fre);
                morphemic_freedom += log(temp_fre);
            }
        }

    }
    //    printf("\n");
    return morphemic_freedom;
}

static int mmseg_node_free(int index,myeArray* mye_array_list)
{
    myeAtomsNode* p_head_node = NULL;
    myeAtomsNode* p_end_node = NULL;
    myeAtomsNode* p_temp_node = NULL;
    p_head_node = mye_array_list[index].mye_node_head;

    p_end_node = p_head_node;

    int i = 0 ;
    do
    {
        p_temp_node = p_end_node;
//        printf("[%s]\n",p_temp_node->atoms_string);
        p_end_node = p_end_node->prior;
        if(p_temp_node->analyse_array)
        {
            free((mmsegAnalyse*)(p_temp_node->analyse_array));
        }
        if(p_temp_node->atoms_string)
        {
            free(p_temp_node->atoms_string);
        }
        if(p_temp_node)
        {
            free(p_temp_node);
        }
        i++;
    }while(p_end_node != p_head_node);
    //    printf("%s() %d/%d/%d/%d\n",__func__,mye_array_list[index].max_path,i,index,mye_array_list[index].num_node);
    return 0;
}


int myeSegEngine_mmseg4j_calculate(myeSegEngine* me)
{
    int cur_index = 0; 
    int cur_length = 0;

    myeAtomsNode* p_first_node = NULL;
    myeAtomsNode* p_second_node = NULL;
    myeAtomsNode* p_third_node = NULL;
    myeAtomsNode* p_end_node = NULL;

    mmsegAnalyse* m_analyse = NULL;

    myeArray* mye_array_list = me->mye_array_list;

    do
    {
        //step 1 最大长度
        int max_length = 0;
        int max_index = 0;
        myeList* mye_list = NULL;
        p_first_node = mye_array_list[cur_index].mye_node_head;
        if(mye_array_list[cur_index].mye_array_type == 4)
        {
            break;
        }
        do
        {
            printf("first (%s)\n",p_first_node->atoms_string);
            cur_length = p_first_node->num_atoms;
            int temp_next_index = cur_index + cur_length;
            myeAtomsNode* temp_first_node =  mye_array_list[temp_next_index].mye_node_head;
            if(mye_array_list[temp_next_index].mye_array_type == 4) //判断p_first_node是否就是最后一个词
            {
                max_length  = cur_length;
                max_index = cur_index;
                double average_length = cur_length*1.0;
                double variance_length = 0.0;
                //添件到本node的mmsegAnalyse
                m_analyse = mmseg_insert_analyse_myeatomsnode(p_first_node,p_first_node,1,cur_length,average_length,variance_length,1);
                mye_list = mye_list_insert_compare(mye_list,m_analyse,order_by_mmseg4j,me->mye_dic);
                printf("结果 %d/%d/%lf\n",m_analyse->atoms_length,m_analyse->seg_step,m_analyse->variance_length); 
                //                printf("%s/%d[%d] -",p_first_node->atoms_string,1,max_index);
                break;
            }   
            p_second_node = mye_array_list[temp_next_index].mye_node_head;
            do
            {
                p_second_node -> far_prior = p_first_node;
                printf("second (%s)\n",p_second_node->atoms_string);
                cur_length = p_first_node->num_atoms + p_second_node->num_atoms; 
                int temp_next_next_index = cur_index + cur_length;              
                myeAtomsNode* temp_second_node =  mye_array_list[temp_next_next_index].mye_node_head;

                max_length  = cur_length;
                max_index = temp_next_index;
                double average_length = cur_length/2.0;
                double variance_length = sqrt((pow(average_length-p_second_node->num_atoms,2)+pow(average_length-p_first_node->num_atoms,2)))/2;
                m_analyse = mmseg_insert_analyse_myeatomsnode(p_second_node,p_first_node,2,cur_length,average_length,variance_length,0);

                if((mye_array_list[temp_next_next_index].mye_array_type) == 4)//判断p_second_node是否就是最后一个词
                {
                    mye_list = mye_list_insert_compare(mye_list,m_analyse,order_by_mmseg4j,me->mye_dic);
                    printf("结果 %d/%d/%lf\n",m_analyse->atoms_length,m_analyse->seg_step,m_analyse->variance_length); 
                    //                    printf("%s/%d[%d] - ",p_second_node->atoms_string,2,max_index);
                    //                    continue;
                    //                    break;
                }
                else
                {
                    p_third_node = mye_array_list[temp_next_next_index].mye_node_head->prior;
                    printf("third (%s)\n",p_third_node->atoms_string);
                    //第三步了
                    cur_length = p_first_node->num_atoms + p_second_node->num_atoms + mye_array_list[temp_next_next_index].max_atoms_in_array;  
                    int temp_next_next_next_index = cur_index + cur_length;
                    myeAtomsNode* temp_third_node = mye_array_list[temp_next_next_next_index].mye_node_head; 

                    max_length = cur_length; 
                    max_index = temp_next_next_index;
                    double average_length = cur_length/3.0;
                    double variance_length = sqrt((pow(average_length-p_third_node->num_atoms,2)+pow(average_length-p_second_node->num_atoms,2)+pow(average_length-p_first_node->num_atoms,2)))/3;
                    m_analyse = mmseg_insert_analyse_myeatomsnode(p_third_node,p_second_node,3,cur_length,average_length,variance_length,0);

                    printf("结果 %d/%d/%lf\n",m_analyse->atoms_length,m_analyse->seg_step,m_analyse->variance_length); 
                    mye_list = mye_list_insert_compare(mye_list,m_analyse,order_by_mmseg4j,me->mye_dic);
                    //                    printf("%s/%d[%d]\n",p_third_node->atoms_string,3,max_index);
                }
                p_second_node = p_second_node->prior;
            }while(p_second_node != mye_array_list[temp_next_index].mye_node_head);            
            //           printf("\n");
            p_first_node = p_first_node -> prior;
        }while(p_first_node != mye_array_list[cur_index].mye_node_head);

        //p_end_node = mye_array_list[max_index].mye_node_head->prior;
        myeAtomsNode* node_result = NULL;
        mmseg_get_result(&node_result,mye_list);

        printf("end [%s][%d][%d][%d]\n",node_result->atoms_string,node_result->num_atoms,node_result->offset,cur_index);
        int add_index = node_result->num_atoms;
        int i = 0 ;
        for(i = 0 ;i < add_index ;i++)
            mmseg_node_free(cur_index+i,mye_array_list);
        cur_index += add_index;
        mye_list_free(mye_list);
        printf("==========end==================\n");

    }while(cur_index < me->max_array_list_used);
    mmseg_node_free(me->max_array_list_used,mye_array_list);

    return 0;
}


int myeSegEngine_get_mmseg_result(myeSegEngine* me,myeTokenList* p_token_list)
{
    return 0;
}


/*********** Xws 算法函数  *****************/
static int xws_analyse_sort(myeAtomsNode* p_cur_node);
static double xws_path_length_calculate(myeAtomsNode* p_cur_node,myeAtomsNode* p_prior_node,myeDictionary* mye_dic);
static xwsAnalyse* xws_insert_analyse_myeatomsnode(myeAtomsNode* p_cur_node,myeAtomsNode* p_prior_node,double path_length);

static int xws_analyse_sort(myeAtomsNode* p_cur_node)
{
    int i = 0 ; 
    int j = 0 ;
    xwsAnalyse* tempXws = (xwsAnalyse*)calloc(1,sizeof(xwsAnalyse));
    for(i = 0 ; i < p_cur_node->max_path - 1; i++)
    {
        for(j = 0; j < p_cur_node->max_path - i - 1; j++)
        {
            if(((xwsAnalyse*)(p_cur_node->analyse_array))[j].nowLength > ((xwsAnalyse*)(p_cur_node->analyse_array))[j+1].nowLength)
            {
                memcpy(tempXws,((xwsAnalyse*)(p_cur_node->analyse_array))+j,sizeof(xwsAnalyse));
                memcpy(((xwsAnalyse*)(p_cur_node->analyse_array))+j,((xwsAnalyse*)(p_cur_node->analyse_array))+j+1,sizeof(xwsAnalyse));
                memcpy(((xwsAnalyse*)(p_cur_node->analyse_array))+j+1,tempXws,sizeof(xwsAnalyse));
            }
        }
    }
    return 0;
}

//计算距离,这一次插入的距离
static xwsAnalyse* xws_insert_analyse_myeatomsnode(myeAtomsNode* p_cur_node,myeAtomsNode* p_prior_node,double path_length)
{    
    double prior_length =0;
    xws_analyse_sort(p_prior_node);
    if(p_prior_node->analyse_array != NULL)        
    {
        prior_length = ((xwsAnalyse*)(p_prior_node->analyse_array))[0].nowLength;
    }
        


    if(p_cur_node->analyse_array == NULL && p_cur_node->max_path > 0)
    {
        p_cur_node->analyse_array = (mmsegAnalyse*)calloc(p_cur_node->max_path,sizeof(xwsAnalyse));
        ((xwsAnalyse*)(p_cur_node->analyse_array))[0].far_prior = p_prior_node;
        ((xwsAnalyse*)(p_cur_node->analyse_array))[0].location = p_cur_node;
        ((xwsAnalyse*)(p_cur_node->analyse_array))[0].flag_use = 1;
        ((xwsAnalyse*)(p_cur_node->analyse_array))[0].nowLength = prior_length + path_length;
        p_cur_node->num_array_used += 1;
        printf("[cur = %s][%lf][pri=%s][%lf][%lf]\n",p_cur_node->atoms_string,path_length,p_prior_node->atoms_string,prior_length,prior_length + path_length);
        return (xwsAnalyse*)(&(((mmsegAnalyse*)(p_cur_node->analyse_array))[0]));
    }   
    else
    {
        ((xwsAnalyse*)(p_cur_node->analyse_array))[p_cur_node->num_array_used].far_prior = p_prior_node;
        ((xwsAnalyse*)(p_cur_node->analyse_array))[p_cur_node->num_array_used].location = p_cur_node;
        ((xwsAnalyse*)(p_cur_node->analyse_array))[p_cur_node->num_array_used].flag_use = 1;
        ((xwsAnalyse*)(p_cur_node->analyse_array))[p_cur_node->num_array_used].nowLength = prior_length + path_length;    
        p_cur_node->num_array_used += 1;
        printf("[cur = %s][%lf][pri=%s][%lf][%lf]\n",p_cur_node->atoms_string,path_length,p_prior_node->atoms_string,prior_length,prior_length + path_length);
        return (xwsAnalyse*)(&(((mmsegAnalyse*)(p_cur_node->analyse_array))[p_cur_node->num_array_used]));
    }
    return NULL;
}

static double xws_path_length_calculate(myeAtomsNode* p_cur_node,myeAtomsNode* p_prior_node,myeDictionary* mye_dic)
{
    char temp_string[200] = {0};
    int bi_frequence = 0;
    int sig_frequence = 0;
    strcpy(temp_string,p_prior_node -> atoms_string); 
    strcat(temp_string,"@"); 
    strcat(temp_string,p_cur_node -> atoms_string); 
    myeDictionary_query_ngram(mye_dic,temp_string,&bi_frequence);    
    sig_frequence = p_prior_node->p_word_item->atoms_string_fre;
    if(bi_frequence == 0)
    {   
        bi_frequence = 1;
    }
    if(sig_frequence == 0)
    {
        sig_frequence = 1;
    }
    printf("[%s][%d][%d][%lf]\n",temp_string,bi_frequence,sig_frequence,log(sig_frequence * 1.0 / bi_frequence));
    return log(sig_frequence * 1.0 / bi_frequence);
}

int myeSegEngine_xws_calculate(myeSegEngine* me)
{
    myeAtomsNode* p_first_node = NULL;
    myeAtomsNode* p_second_node = NULL;
    myeAtomsNode* temp_first_node = NULL;
    myeAtomsNode* temp_second_node = NULL;

    xwsAnalyse* m_analyse = NULL;
    myeArray* mye_array_list = me->mye_array_list;
    int cur_index = 0; 
    int cur_length = 0;

    while(cur_index <=  me->max_array_list_used)
    {
            temp_first_node = mye_array_list[cur_index].mye_node_head;
            if(mye_array_list[cur_index].mye_array_type == 4)
            {
                xws_analyse_sort(temp_first_node);
                break;
            }            
            do
            {
                printf("first (%s)\n",temp_first_node->atoms_string);
                cur_length = temp_first_node->num_atoms;
                int temp_second_index = cur_index + cur_length;
                temp_second_node = mye_array_list[temp_second_index].mye_node_head;
                do
                {
                    double path_length = xws_path_length_calculate(temp_second_node,temp_first_node,me->mye_dic); 
                    xws_insert_analyse_myeatomsnode(temp_second_node,temp_first_node,path_length);
                    temp_second_node = temp_second_node->prior;   

                }while(temp_second_node != mye_array_list[temp_second_index].mye_node_head);

                temp_first_node = temp_first_node -> prior;
            }while(temp_first_node != mye_array_list[cur_index].mye_node_head);
            cur_index++;
    }
    myeSegEngine_get_nshort_paths(me,me->max_array_list_used);
}

int myeSegEngine_get_nshort_paths(myeSegEngine* me,int index)
{
    myeArray* mye_array_list = me->mye_array_list;
    myeAtomsNode* endAtom =  mye_array_list[index].mye_node_head;
    printf("%s\n",endAtom->atoms_string);
    myeAtomsNode* p_prior_node = ((xwsAnalyse*)(endAtom->analyse_array))[0].far_prior;        
    while(p_prior_node != NULL)
    {
            if(p_prior_node -> analyse_array != NULL)
                printf("%s\n",p_prior_node->atoms_string);
            else 
                break;

            p_prior_node = ((xwsAnalyse*)(p_prior_node->analyse_array))[0].far_prior;
    }
    printf("\n");

    return 0;
}

int myeSegEngine_get_xws_result(myeSegEngine* me,myeTokenList* p_token_list)
{

    return 0;
}

#include "maoYeMMSeg.h"


struct _maoYeMMSeg
{
    maoYeSegClass* isa;
    myeSegEngine* mye_engine;
    myeDictionary* mye_dic;
};

static maoYeSegClass maoYeMMSegClass =
{
    "maoYeMMSegClass",
    NULL,
    maoYeMMSeg_delete,
    maoYeMMSeg_string_tokenize,
    maoYeMMSeg_list_tokenize,
    maoYeMMSeg_setopt,
    0,
    0,
    0
};



maoYeMMSeg* maoYeMMSeg_new(const char* p_dic_path)
{
    maoYeMMSeg* me = (maoYeMMSeg*)calloc(1,sizeof(maoYeMMSeg));    
    me->isa = &(maoYeMMSegClass);
    printf("(%p)(%p)(%s)\n",me->isa,&(maoYeMMSegClass),maoYeMMSegClass.m_name);
    me->mye_dic = myeDictionary_init();    
    myeDictionary_load(me->mye_dic,"./webdict_with_freq.txt");
    me->mye_engine = myeSegEngine_init(10,me->mye_dic);
    return me;
}

void maoYeMMSeg_delete(maoYeSeg* s_me)
{
    maoYeMMSeg* me = (maoYeMMSeg*)s_me;
    myeDictionary_free(me->mye_dic);
    myeSegEngine_free(me->mye_engine);
    free(me);
}

int maoYeMMSeg_string_tokenize(maoYeSeg* s_me,const char* lpzwInput,void* ppToken)
{
    maoYeMMSeg* me = (maoYeMMSeg*)s_me;
    int n_out_len = 0 ;
    int n_out_type = 0 ; 
    int n_out_pos = 0;
    int count_atom = 0;
    int row_index = 0;
    char* p = NULL;
    myeutil_full_to_half_angle(&p,lpzwInput);
    while (n_out_len = myeutil_get_first_atom_len((const char*)(p + n_out_pos), &n_out_type), n_out_len > 0)
    {
        printf("n_out_type %d\n",n_out_type);
        count_atom = 0;
        if(n_out_type == 3)
        {
                count_atom++;
                myeSegEngine_add(me->mye_engine,p+n_out_pos,n_out_len,count_atom,row_index,3);
        }
        else
        {
                count_atom++;
                myeSegEngine_add(me->mye_engine,p+n_out_pos,n_out_len,count_atom,row_index,1);
                row_index++;
                n_out_pos += n_out_len;
                continue;
        }
        int n_in_len = 0;
        int n_in_type = 0;
        int n_in_pos  = n_out_pos+n_out_len;
       
        while(n_in_len= myeutil_get_first_atom_len((const char*)(p + n_in_pos), &n_in_type), n_in_len > 0)
        {
            printf("n_in_type %d\n",n_in_type);
            if(n_in_type == 3 && count_atom++ <= 5)
            {   
                if(myeDictionary_n_query(me->mye_dic,p+n_out_pos,n_in_pos-n_out_pos+n_in_len,NULL))
                    myeSegEngine_add(me->mye_engine,p+n_out_pos,n_in_pos-n_out_pos+n_in_len,count_atom,row_index,3);
            }
            else if(n_in_type == 1 && count_atom++ <= 5)
            {
                if(myeDictionary_n_query(me->mye_dic,p+n_out_pos,n_in_pos-n_out_pos+n_in_len,NULL))
                 myeSegEngine_add(me->mye_engine,p+n_out_pos,n_in_pos-n_out_pos+n_in_len,count_atom,row_index,3);
                 break;
            }
            n_in_pos += n_in_len;
        }
        row_index++;
        n_out_pos += n_out_len;
    }
    myeSegEngine_add(me->mye_engine,"#end",4,1,row_index,4);

    myeTokenList* p_token_list = NULL;
    myeSegEngine_mmseg4j_calculate(me->mye_engine);
    free(p); 
    return 0;
}

int maoYeMMSeg_list_tokenize(maoYeSeg* s_me,const char* lpzwInput,void* ppToken)
{
    maoYeMMSeg* me = (maoYeMMSeg*)s_me;
    return 0;
}

int maoYeMMSeg_setopt(maoYeSeg* me,int TYPE,void* p_date)
{
    return 0;
}




#include "maoYeXwsSeg.h"


struct _maoYeXwsSeg
{
    maoYeSegClass* isa;
    myeSegEngine* mye_engine;
    myeDictionary* mye_dic;
    
};

static maoYeSegClass maoYeXwsSegClass =
{
    "maoYeXwsSegClass",
    NULL,
    maoYeXwsSeg_delete,
    maoYeXwsSeg_string_tokenize,
    maoYeXwsSeg_list_tokenize,
    maoYeXwsSeg_setopt,
    0,
    0,
    0
};



maoYeXwsSeg* maoYeXwsSeg_new(const char* dic_path)
{
    maoYeXwsSeg* me = (maoYeXwsSeg*)calloc(1,sizeof(maoYeXwsSeg));
    me->isa = &(maoYeXwsSegClass);
    me->mye_dic = myeDictionary_init();
    myeDictionary_load(me->mye_dic,"./core.dic");
//    myeDictionary_load(me->mye_dic,"webdict_with_freq.txt");
    myeDictionary_load_ngram(me->mye_dic,"./bigramdict.dic");
    me->mye_engine = myeSegEngine_init(10,me->mye_dic);
    return me; 
}

void maoYeXwsSeg_delete(maoYeSeg* s_me)
{
    maoYeXwsSeg* me = (maoYeXwsSeg*)s_me;
    myeDictionary_free(me->mye_dic);
    myeSegEngine_free(me->mye_engine);
    free(me);

}

int maoYeXwsSeg_string_tokenize(maoYeSeg* s_me,const char* lpzwInput,void* ppToken)
{
    maoYeXwsSeg* me = (maoYeXwsSeg*)s_me;
    int n_out_len = 0 ;
    int n_out_type = 0 ; 
    int n_out_pos = 0;
    int count_atom = 0;
    int row_index = 0;
    int frequence = 0;
    char* p = NULL;
    myeutil_full_to_half_angle(&p,lpzwInput);

    wordItem* p_item = (wordItem*)calloc(1,sizeof(wordItem));
    myeDictionary_query(me->mye_dic,"始##始",&frequence);
    p_item->p_str = "始##始";
    p_item->str_size = 8;
    p_item->num_atoms = 1;
    p_item->add_index = row_index;
    p_item->atoms_string_type = 7;
    p_item->atoms_string_fre = frequence;
    myeSegEngine_add_full(me->mye_engine,p_item);
    memset(p_item,0,sizeof(wordItem));
    row_index++;
    while (n_out_len = myeutil_get_first_atom_len((char*)(p + n_out_pos), &n_out_type), n_out_len > 0)
    {
        count_atom = 0;
        printf("%s\n",(const char*)(p + n_out_pos));
        wordItem* p_out_item = (wordItem*)calloc(1,sizeof(wordItem));
        if(n_out_type == 3 )
        {
                count_atom++;
                frequence = 0;
                myeDictionary_n_query(me->mye_dic,p+n_out_pos,n_out_len,&frequence);
                p_item->p_str = p+n_out_pos;
                p_item->str_size = n_out_len;
                p_item->num_atoms = count_atom;
                p_item->add_index = row_index;
                p_item->atoms_string_type = 3;
                p_item->atoms_string_fre = frequence;
                p_item->atoms_string_handle = 0;
                myeSegEngine_add_full(me->mye_engine,p_item);
                memset(p_item,0,sizeof(wordItem));
        }
        else
        {
                count_atom++;
                p_out_item->p_str = p+n_out_pos;
                p_out_item->str_size = n_out_len;
                p_out_item->num_atoms = count_atom;
                p_out_item->add_index = row_index;
                p_out_item->atoms_string_type = 1;
                p_out_item->atoms_string_fre = frequence;
                p_out_item->atoms_string_handle = 0;
                myeSegEngine_add_full(me->mye_engine,p_out_item);
                memset(p_item,0,sizeof(wordItem));
                row_index++;
                n_out_pos += n_out_len;
                continue;
        }
        int n_in_len = 0;
        int n_in_type = 0;
        int n_in_pos  = n_out_pos+n_out_len;
       
        while(n_in_len= myeutil_get_first_atom_len((char*)(p + n_in_pos), &n_in_type), n_in_len > 0)
        {
//            printf("n_in_type %d\n",n_in_type);
            wordItem* p_in_item = (wordItem*)calloc(1,sizeof(wordItem));
            if(n_in_type == 3 && count_atom++ <= 5)
            {   
                frequence = 0;
                if(myeDictionary_n_query(me->mye_dic,p+n_out_pos,n_in_pos-n_out_pos+n_in_len,&frequence))
                {
                    p_item->p_str = p+n_out_pos;
                    p_item->str_size = n_in_pos-n_out_pos+n_in_len;
                    p_item->num_atoms = count_atom;
                    p_item->add_index = row_index;
                    p_item->atoms_string_type = 3;
                    p_item->atoms_string_fre = frequence;
                    p_item->atoms_string_handle = 0;
                    myeSegEngine_add_full(me->mye_engine,p_item);
                    memset(p_item,0,sizeof(wordItem));
                }
            }
            else if(n_in_type == 1 && count_atom++ <= 5)
            {
//                 myeSegEngine_add(me->mye_engine,p+n_out_pos,n_in_pos-n_out_pos+n_in_len,count_atom,row_index,3);
                 break;
            }
            n_in_pos += n_in_len;
        }
        row_index++;
        n_out_pos += n_out_len;
    }
    p_item->p_str = "末##末";
    p_item->str_size = 8;
    p_item->num_atoms = 1;
    p_item->add_index = row_index;
    p_item->atoms_string_type = 4;
    p_item->atoms_string_fre = 0;
    myeSegEngine_add_full(me->mye_engine,p_item);

    myeTokenList* p_token_list = NULL;
    myeSegEngine_xws_calculate(me->mye_engine);
    free(p);
    return 0;
//    p(abcd) = p(a)p(b|a)p(c|b)p(d|c)
    
}

int maoYeXwsSeg_list_tokenize(maoYeSeg* s_me,const char* lpzwInput,void* ppToken)
{
    maoYeXwsSeg* me = (maoYeXwsSeg*)s_me;

}

int maoYeXwsSeg_setopt(maoYeSeg* s_me,int TYPE,void* p_date)
{

}



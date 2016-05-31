#include "myeDictionary.h"

static void key_destroy_func(gpointer key)
{
    g_free(key);
}
static void value_destroy_func(gpointer value)
{
    
}

static void read_file_data(GHashTable* g_table,const char* p_dic_path)
{
    FILE *fin = fopen(p_dic_path, "rb");
    if(fin == NULL)
    {
        printf("File [%s] [error] 打开失败\n",p_dic_path);
        exit(0);
    }
    char* saveptr1 = NULL;
    char* p_str = NULL;
    char* p_token = NULL; 
    char read_buf[1024] = {0};

    int m = 0;
    while((fgets(read_buf,1024,fin))!=NULL)
    {       
        m++;
        int i = strlen(read_buf);       
        int j = 0; 
        char* p_token_frist = NULL;
        int i_token_second = 0;

        if(read_buf[i-1]=='\n') //因为最后一行没有回车符
        {       
            read_buf[i-1] = 0;
        }       
        for (j = 1, p_str = read_buf; ; j++, p_str = NULL)
        {       
            p_token = strtok_r(p_str,"\t ", &saveptr1);
            if (p_token == NULL)
                break;
            if(j == 1)
            {       
                p_token_frist = (char*)calloc(1,strlen(p_token)+1);
                strcpy(p_token_frist,p_token);
                i_token_second = 1;

            }
            else if(j == 2)
            {
                i_token_second = atoi(p_token);
            }
        }
        if(m < 20)
            printf("(%s)[%d]\n",p_token_frist,i_token_second);
        g_hash_table_insert(g_table,p_token_frist,(void*)i_token_second);
    }
    fclose(fin);

}

int myeDictionary_reload(myeDictionary* me,const char* p_dic_path)
{
    return 0;
    
}

myeDictionary* myeDictionary_init()
{
    myeDictionary* me = (myeDictionary*)calloc(1,sizeof(myeDictionary));
    me->g_word_fre_dic = g_hash_table_new_full(g_str_hash,g_int_equal,key_destroy_func,value_destroy_func);
    me->g_ngram_fre_dic = g_hash_table_new_full(g_str_hash,g_int_equal,key_destroy_func,value_destroy_func);
    return me;
}

int myeDictionary_query(myeDictionary* me,const char* p_query,int* frequence)
{
    int word_fre = 0;
    int gboolean = 0;
    gboolean = g_hash_table_lookup_extended(me->g_word_fre_dic,p_query,NULL,(void**)&word_fre);
    if(frequence != NULL)
        *frequence = word_fre;
    return gboolean;

}

int myeDictionary_n_query(myeDictionary* me,const char* p_query,int query_size,int* frequence)
{
    char* temp_query = NULL;
    temp_query = (char*)calloc(1,query_size+1);
    strncpy(temp_query,p_query,query_size);
    int word_fre = 0;
    int gboolean = 0;
    gboolean = g_hash_table_lookup_extended(me->g_word_fre_dic,temp_query,NULL,(void**)&word_fre);
    if(frequence != NULL)
        *frequence = word_fre;
    free(temp_query);
    return gboolean;
}

int myeDictionary_query_ngram(myeDictionary* me,const char* p_query,int* frequence)
{
    int word_fre = 0;
    int gboolean = 0;
    gboolean = g_hash_table_lookup_extended(me->g_ngram_fre_dic,p_query,NULL,(void**)&word_fre);
    if(frequence != NULL)
        *frequence = word_fre;
    return 0;
}

int myeDictionary_n_query_ngram(myeDictionary* me,const char* p_query,int query_size,int* frequence)
{
    char* temp_query = NULL;
    temp_query = (char*)calloc(1,query_size+1);
    strncpy(temp_query,p_query,query_size);
    int word_fre = 0;
    int gboolean = 0;
    gboolean = g_hash_table_lookup_extended(me->g_ngram_fre_dic,temp_query,NULL,(void**)&word_fre);
    if(frequence != NULL)
        *frequence = word_fre;
    free(temp_query);
    return gboolean;
}

int myeDictionary_load(myeDictionary* me,const char* p_dic_path)
{
    read_file_data(me->g_word_fre_dic,p_dic_path);
}

int myeDictionary_reload_ngram(myeDictionary* me,const char* p_dic_path)
{
    return 0;
}

int myeDictionary_load_ngram(myeDictionary* me,const char* p_dic_path)
{
    read_file_data(me->g_ngram_fre_dic,p_dic_path);
    return 0;
}

int myeDictionary_free(myeDictionary* me)
{
    if(me->g_word_fre_dic)        
        g_hash_table_destroy(me->g_word_fre_dic);
    if(me->g_ngram_fre_dic)        
        g_hash_table_destroy(me->g_ngram_fre_dic);
    free(me);
    return 0;
}



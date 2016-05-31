#include "myeUtil.h"
myeList* mye_list_insert(myeList* list,void* data)
{
    if(list == NULL)
    {
        list = (myeList*)calloc(1,sizeof(myeList));
        list->data = data;
        return list;
    }
    else 
    {
        myeList* temp_list =  (myeList*)calloc(1,sizeof(myeList));
        temp_list->next = list->next;
        list -> next = temp_list;
    }
    
    return list;
}

myeList* mye_list_insert_compare(myeList* list,void* data,myeCompareFunc mye_compare,void* compare_arg)
{
    if(list == NULL)
    {
        list = (myeList*)calloc(1,sizeof(myeList));
        list->data = data;
        return list;
    }
    else
    {
        if(mye_compare == NULL)
        {
            //添加到头部
            myeList* temp_list =  (myeList*)calloc(1,sizeof(myeList));
            temp_list->next = list->next;
            list -> next = temp_list;
            return list;
        }
        else
        {   
            myeList* top_list = list;
            if(mye_compare(data,top_list->data,compare_arg) > 0)
            {
                myeList* temp = NULL;
                while(top_list)
                {
                    temp = top_list;
                    top_list = top_list->next;
                    free(temp);
                    temp = NULL;
                }
                temp = (myeList*)calloc(1,sizeof(myeList));
                temp->data = data;
                return temp;
            }
            else if(mye_compare(data,top_list->data,compare_arg) < 0)
            {
                return list;
            }
            else 
            {
                //添加到头部
                myeList* temp_list =  (myeList*)calloc(1,sizeof(myeList));
                temp_list->next = list->next;
                list -> next = temp_list;
                return list;
            }
        }
    }
}

void* mye_list_find_top(myeList* list)
{
        return list->data;
}

void mye_list_free(myeList* list)
{
    myeList* temp = NULL;
    while(list)
    {
        temp = list;
        list = list->next;
        free(temp);
        temp = NULL;
    }
    list = NULL;
}


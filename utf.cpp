#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
#define UTF16_EncodingtoOrder(h) ((0xFF & h[0]) << 8) | (0xFF & h[1])                                                                                    
#define UTF16_OrdertoEncoding(i, h) (h[0] = (i/256), h[1] = (i%256), h)

typedef struct _dict
{
    int n_fre;
    int n_word_len;
    int n_handle;
    char word[200];

}dict;

typedef struct _dictable
{
    int count;
    dict*   p_dict_list;    

}dictable;

string UTF16toUTF8(const char* str, int len, bool bom)
{
	string out = "";
	int i = 0;
	char high_byte = 0;
	char low_byte = 0;
	
	for(i = 0; i < len; i += 2)
	{
		/* Big-Endian for the byte order mark. */
		if((str[i] == (char)0xFE) && (str[i + 1] == (char)0xFF))
		{
			bom = true;
			continue;
		}
		/* Little-Endian for the byte order mark. */
		else if((str[i] == (char)0xFF) && (str[i + 1] == (char)0xFE))
		{
			bom = false;
			continue;
		}
		/* Big-Endian for the byte order mark. */
		if(bom)
		{
			high_byte = str[i];
			low_byte = str[i + 1];
		}
		/* Little-Endian for the byte order mark. */
		else
		{
			high_byte = str[i + 1];
			low_byte = str[i];
		}
		/* One encoded. ASCII charactor. */
		if(!(high_byte & 0xFF) && !(low_byte & 0x80))
		{
			out.push_back(low_byte);
		}
		/* Two encoded. */
		else if(!(high_byte & 0xF8))
		{
			out.push_back(0xC0 | ((high_byte << 2) & 0x1C) | ((low_byte >> 6) & 0x03));
			out.push_back(0x80 | ((low_byte >> 0) & 0x3F));
		}
		/* Three encoded. */
		else
		{
			out.push_back(0xE0 | ((high_byte >> 4) & 0x0F));
			out.push_back(0x80 | ((high_byte << 2) & 0x3C) | ((low_byte >> 6) & 0x03));
			out.push_back(0x80 | ((low_byte >> 0) & 0x3F));
		}
	}
	return out;
}

string UTF8toUTF16(const char* str, int len, bool bom)
{
	string out = "";
	int i = 0;
	char high_byte = 0;
	char low_byte = 0;
	
	for(i = 0; i < len; )
	{
		/* One encoded. ASCII charactor. */
		if(!(str[i] & 0x80))
		{
			high_byte = 0x00;
			low_byte = str[i];
			i++;
		}
		/* Two encoded. */
		else if(!(str[i] & 0xE0 ^ 0xC0) && 
				!(str[i + 1] & 0xC0 ^ 0x80))
		{
			high_byte = (str[i] & 0x1C) >> 2;
			low_byte = ((str[i] & 0x03) << 6) | (str[i + 1] & 0x3F);
			i += 2;
		}
		/* Three encoded. */
		else if(!(str[i] & 0xF0 ^ 0xE0) && 
				!(str[i + 1] & 0xC0 ^ 0x80) && 
				!(str[i + 2] & 0xC0 ^ 0x80))
		{
			high_byte = ((str[i] & 0x0F) << 4) | ((str[i + 1] & 0x3C) >> 2);
			low_byte = ((str[i + 1] & 0x03) << 6) | (str[i + 2] & 0x3F);
			i += 3;
		}
		/* Four encoded. */
		else if(!(str[i] & 0xF8 ^ 0xF0) && 
				!(str[i + 1] & 0xC0 ^ 0x80) && 
				!(str[i + 2] & 0xC0 ^ 0x80) && 
				!(str[i + 3] & 0xC0 ^ 0x80))
		{
			// Modify in 2011-06-22 as some character like that "𤭢" can not recognized.
			// cout << __FILE__ << ": " << __LINE__ << ": Cann't convert four byte for UTF-16!\n";
			// exit(-1);
			high_byte = ((str[i + 1] & 0x0F) << 4) | ((str[i + 2] & 0x3C) >> 2);
			low_byte = ((str[i + 2] & 0x03) << 6) | (str[i + 3] & 0x3F);
			i += 4;
		}
		/* Error encoded. */
		else
		{
			cout << __FILE__ << ": " << __LINE__ << ": Cann't find more byte in UTF-8!\n";
			out.push_back(0);
			out.push_back(0);
			return out;
			// exit(-1);
		}
		
		/* Push back the results with Big-Endian. */
		if(bom)
		{
			out.push_back(high_byte);
			out.push_back(low_byte);
		}
		/* Push back the results with Little-Endian. */
		else
		{
			out.push_back(low_byte);
			out.push_back(high_byte);
		}
	}
	return out;
}

int main(int argc,char* argv[])
{
        char utf16_1[10] = {0};
    int index = 0;
    index = UTF16_EncodingtoOrder(UTF8toUTF16("个",3,true));
    printf("index = [%d]/n",index);
    string str = UTF16toUTF8(UTF16_OrdertoEncoding(20010,utf16_1), 2, true);
    printf("index 1 = [%d][%s]/n",index,str.data());

/*    int i = 0;
    int j = 0 ;
    int buffer[3] = {0};
    

    FILE* fp = NULL;
    if((fp = fopen(argv[1],"r")) == NULL)
    {
        return -1;
    }

    FILE* fw = NULL;
    if((fw = fopen(argv[2],"w")) == NULL)
    {
        return -1;
    }
    
    

    dictable* p_table_list = (dictable*)calloc(65536,sizeof(dictable));

    for(i = 0 ; i < 65536; i++ )
    {
        fread(&(p_table_list[i].count),sizeof(int),1,fp);
        if(p_table_list[i].count <= 0)
        {   
            continue;
        }
        printf("count=%d/%d\n",p_table_list[i].count,i);
//        printf("%d\n",(p_table_list[i].count));
        p_table_list[i].p_dict_list = (dict*)malloc(p_table_list[i].count*sizeof(dict));
       


        assert(p_table_list[i].p_dict_list != NULL);
        char buf[300] = {0};
        char utf16_1[10] = {0};
        for(j = 0 ; j <  p_table_list[i].count;j++)
        {
            memset(buf,0,sizeof(buf));
            fread(buffer, sizeof(int), 3, fp);
            p_table_list[i].p_dict_list[j].n_fre = buffer[0] ;
            p_table_list[i].p_dict_list[j].n_word_len = buffer[1] ;
            p_table_list[i].p_dict_list[j].n_handle = buffer[2] ;
            if(buffer[1] > 0 )
            {   
                fread(p_table_list[i].p_dict_list[j].word,sizeof(char),buffer[1],fp);
            }
//            printf("\t\tn_fre=%d\n",p_table_list[i].p_dict_list[j].n_fre);
//            printf("\t\tn_word_len=%d\n",p_table_list[i].p_dict_list[j].n_word_len);
//            printf("\t\tn_handle=%d\n",p_table_list[i].p_dict_list[j].n_handle);
//            printf("\t\tword=[%s]\n",p_table_list[i].p_dict_list[j].word);
            strcpy(buf,UTF16toUTF8(UTF16_OrdertoEncoding(i,utf16_1), 2, true).c_str());
//            printf("buf=[%s%s]\n",buf,p_table_list[i].p_dict_list[j].word);
            strcat(buf,p_table_list[i].p_dict_list[j].word);
           
            fwrite(buf,strlen(buf),1,fw);
            fwrite(" ",strlen(" "),1,fw);
            char i_buf[20] = {0};
            sprintf(i_buf,"%d\n",p_table_list[i].p_dict_list[j].n_fre);
            fwrite(i_buf,strlen(i_buf),1,fw);
            
        }
    }
    fclose(fp);
*/
    return 0;
}













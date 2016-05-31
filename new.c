#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maoYeStrProcess.h"

int myeutil_get_first_atom_len(const char* str, int* type)
{
	*type = 0;
	if (NULL == str || '\0' == str[0])
	{
		return 0;
	}
	// One encoded. ASCII charactor.
	if (!(str[0] & 0x80))
	{
		int offset = 1;
		if((str[0] >= 0x30 && str[0] <= 0x39)
				|| (str[0] >= 0x40 && str[0] <= 0x5A)
				|| (str[0] >= 0x61 && str[0] <= 0x7A)
				|| (str[0] == 0x2d) || (str[0] == 0x2e))
		{
			while (str[offset] && !(str[offset] & 0x80)
					&& ((str[offset] >= 0x30 && str[offset] <= 0x39)
					|| (str[offset] >= 0x40 && str[offset] <= 0x5A)
					|| (str[offset] >= 0x61 && str[offset] <= 0x7A)
					|| (str[offset] == 0x2d) || (str[offset] == 0x2e)))
			{
				offset++;
			}
		}
		*type = 1;
		return offset;
	}
	// Two encoded.
	else if (!((str[0] & 0xE0) ^ 0xC0) && !((str[1] & 0xC0) ^ 0x80))
	{
		*type = 2;
		return 2;
	}
	// Three encoded.
	else if (!((str[0] & 0xF0) ^ 0xE0) && !((str[1] & 0xC0) ^ 0x80)
			&& !((str[2] & 0xC0) ^ 0x80))
	{
		*type = 3;
		return 3;
	}
	// Four encoded.
	else if (!((str[0] & 0xF8) ^ 0xF0) && !((str[1] & 0xC0) ^ 0x80)
			&& !((str[2] & 0xC0) ^ 0x80) && !((str[3] & 0xC0) ^ 0x80))
	{
		*type = 4;
		return 4;
	}
	// Error encoded.
	else
	{
		*type = -1;
		return -1;
	}
}

int main(int argc,char* argv[])
{
    int n_out_len = 0 ;
    int n_out_type = 0 ; 
    int n_out_pos = 0;
    int count_atom = 0;

    maoYeStrProcess* me = (maoYeStrProcess*)calloc(1,sizeof(maoYeStrProcess));

    maoYeAtoms* p_temp_atoms = NULL;
    char* p = "中国人民万岁你好阿";
    while (n_out_len = myeutil_get_first_atom_len((const char*)(p + n_out_pos), &n_out_type), n_out_len > 0)
    {
        count_atom = 0;
        if(n_out_type == 3 )
        {
                (me->maoye_sentence).maoye_atoms_list = (maoYeAtoms*)calloc(1,sizeof(maoYeAtoms));
                (me->maoye_sentence).maoye_atoms_list->p_atom = (char*)calloc(1,n_out_len+1);
                (me->maoye_sentence).maoye_atoms_list->atoms_num = 1;
                strncpy((me->maoye_sentence).maoye_atoms_list->p_atom,p+n_out_pos,n_out_len);                               
                printf("B: [%s][%d]\t\n",(me->maoye_sentence).maoye_atoms_list->p_atom,(me->maoye_sentence).maoye_atoms_list->atoms_num);
                count_atom++;
        }

        int n_in_len = 0;
        int n_in_type = 0;
        int n_in_pos  = n_out_pos+n_out_len;
       
        while(n_in_len= myeutil_get_first_atom_len((const char*)(p + n_in_pos), &n_in_type), n_in_len > 0)
        {
            if(n_in_type == 3 && count_atom++ <= 5)
            {   
                p_temp_atoms = (maoYeAtoms*)calloc(1,sizeof(maoYeAtoms));
                p_temp_atoms->atoms_num = count_atom;
                p_temp_atoms->p_atom =  (char*)calloc(1,n_in_pos-n_out_pos+n_in_len + 1);
                strncpy(p_temp_atoms->p_atom,p + n_out_pos,n_in_pos-n_out_pos+n_in_len);                               
                printf("l: [%s][%d]\t\n",p_temp_atoms->p_atom,p_temp_atoms->atoms_num);
            }
            n_in_pos += n_in_len;
        }
        n_out_pos += n_out_len;
    }
    return 0;
}

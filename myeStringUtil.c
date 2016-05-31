#include "myeStringUtil.h"


int myeutil_get_first_atom_len(const char* buf,int* type)
{
    *type = 0;
    if (NULL == buf || '\0' == buf[0])
    {
        return 0;
    }
    // One encoded. ASCII charactor.
    if (!(buf[0] & 0x80))
    {
        int offset = 1;
        if((buf[0] >= 0x30 && buf[0] <= 0x39)
                || (buf[0] >= 0x40 && buf[0] <= 0x5A)
                || (buf[0] >= 0x61 && buf[0] <= 0x7A)
                || (buf[0] == 0x2d) || (buf[0] == 0x2e))
        {
            while (buf[offset] && !(buf[offset] & 0x80)
                    && ((buf[offset] >= 0x30 && buf[offset] <= 0x39)
                        || (buf[offset] >= 0x40 && buf[offset] <= 0x5A)
                        || (buf[offset] >= 0x61 && buf[offset] <= 0x7A)
                        || (buf[offset] == 0x2d) || (buf[offset] == 0x2e)))
            {
                offset++;
            }
        }
        *type = 1;
        return offset;
    }
    // Two encoded.
    else if (!((buf[0] & 0xE0) ^ 0xC0) && !((buf[1] & 0xC0) ^ 0x80))
    {
        *type = 2;
        return 2;
    }
    // Three encoded. 11100110 10110001 10001001/ 6C49 =    unicode 0100 1110 0010 1101 = 中(4e2d) 转 utf8 e4 b8 ad  11100100 10111000 10101101
    /*
       0000 - 007F 0xxxxxxx 
       0080 - 07FF 110xxxxx
       10xxxxxx  0800 - FFFF

       1110xxxx 10xxxxxx 10xxxxxx  

    */
    
    else if (!((buf[0] & 0xF0) ^ 0xE0) && !((buf[1] & 0xC0) ^ 0x80)
            && !((buf[2] & 0xC0) ^ 0x80))
    {
        *type = 3;
        return 3;
    }
    // Four encoded.
    else if (!((buf[0] & 0xF8) ^ 0xF0) && !((buf[1] & 0xC0) ^ 0x80)
            && !((buf[2] & 0xC0) ^ 0x80) && !((buf[3] & 0xC0) ^ 0x80))
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


int myeutil_utf8_to_unicode(char* dest,int* size_d,const char* src,int bom)
{
    return myeutilm_utf8_to_unicode( dest,size_d,src,-1,bom);
}

int myeutilm_utf8_to_unicode(char* dest,int* size_d,const char* src,int size_n,int bom)
{
    int flag = 0;
    if(size_n < 0)
        flag  = 1;
    int end_index = 0;
	char high_byte = 0;
	char low_byte = 0;

	int i = 0;    
    *size_d = 0;
    while(src[i] != '\0')
    {
		/* One encoded. ASCII charactor. */
		if(!(src[i] & 0x80))
		{
            if( flag != 1 && i + 1 > size_n )
                break;
			high_byte = 0x00;
			low_byte = src[i];
			i++;
		}
		/* Two encoded. */
		else if(!((src[i] & 0xE0) ^ 0xC0) && !((src[i+1] & 0xC0) ^ 0x80))
		{
            if(flag != 1 && i + 2 > size_n)
                break;
			high_byte = (src[i] & 0x1C) >> 2;
			low_byte = ((src[i] & 0x03) << 6) | (src[i + 1] & 0x3F);
			i += 2;
		}
		/* Three encoded. */
		else if(!((src[i] & 0xF0) ^ 0xE0) && !((src[i+1] & 0xC0) ^ 0x80) && !((src[i+2] & 0xC0) ^ 0x80))
		{
            if(flag != 1 && i + 3 > size_n)
                break;
            printf("123123\n");
			high_byte = ((src[i] & 0x0F) << 4) | ((src[i + 1] & 0x3C) >> 2);
			low_byte = ((src[i + 1] & 0x03) << 6) | (src[i + 2] & 0x3F);
			i += 3;
		}
		/* Four encoded. */
		else if(!((src[i] & 0xF8) ^ 0xF0) && !((src[i+1] & 0xC0) ^ 0x80) && !((src[i+2] & 0xC0) ^ 0x80) && !((src[i+3] & 0xC0) ^ 0x80))
		{
			// Modify in 2011-06-22 as some character like that "𤭢" can not recognized.
            if(flag != 1 && i + 4 > size_n)
                break;
			high_byte = ((src[i + 1] & 0x0F) << 4) | ((src[i + 2] & 0x3C) >> 2);
			low_byte = ((src[i + 2] & 0x03) << 6) | (src[i + 3] & 0x3F);
			i += 4;
		}
		/* Error encoded. */
		else
		{
            dest[end_index++] = 0;
            dest[end_index++] = 0;
            return -1;
		}
		
		/* Push back the results with Big-Endian. */
		if(bom)
		{
            dest[end_index++] = high_byte;
            dest[end_index++] = low_byte;
		}
		/* Push back the results with Little-Endian. */
		else
		{
            dest[end_index++] = low_byte;
            dest[end_index++] = high_byte;
		}
        *size_d += 2;
	}
    return 0;
}


int myeutilm_unicode_to_utf8(char* dest,const char* src,int size_n,int bom)
{
    int flag = 0;
    if(size_n < 0)
        flag  = 1;
    int end_index = 0;
	char high_byte = 0;
	char low_byte = 0;
    int i = 0;
    while(i < size_n)
    {
        if(flag != 1 && i + 2 > size_n)
            break;
		/* Big-Endian for the byte order mark. utf16 用来判断大端还是小段的前两个字节*/
		if((src[i] == (char)0xFE) && (src[i + 1] == (char)0xFF))
		{
			bom = 1;
            i += 2;
			continue;
		}
		/* Little-Endian for the byte order mark. */
		else if((src[i] == (char)0xFF) && (src[i + 1] == (char)0xFE))
		{
			bom = 0;
            i += 2;
			continue;
		}
		/* Big-Endian for the byte order mark. */
		if(bom)
		{
			high_byte = src[i];
			low_byte = src[i + 1];
		}
		/* Little-Endian for the byte order mark. */
		else
		{
			high_byte = src[i + 1];
			low_byte = src[i];
		}
		/* One encoded. ASCII charactor. */
		if(!(high_byte & 0xFF) && !(low_byte & 0x80))
		{
            dest[end_index++] = low_byte;
		}
		/* Two encoded. */
		else if(!(high_byte & 0xF8))
		{
            dest[end_index++] = (0xC0 | ((high_byte << 2) & 0x1C) | ((low_byte >> 6) & 0x03));
            dest[end_index++] = (0x80 | ((low_byte >> 0) & 0x3F));
		}
		/* Three encoded. */
		else
		{
            dest[end_index++] = (0xE0 | ((high_byte >> 4) & 0x0F));
            dest[end_index++] =(0x80 | ((high_byte << 2) & 0x3C) | ((low_byte >> 6) & 0x03));
            dest[end_index++] =(0x80 | ((low_byte >> 0) & 0x3F));
		}
        i += 2;
	}
	return 0;
}

int myeutil_full_to_half_angle(char** dest,const char* src)
{
    return myeutilm_full_to_half_angle(dest,src,-1);
}

int myeutilm_full_to_half_angle(char** dest,const char* src,int size_n)
{
    printf("[%d]\n",strlen(src));
    int len = 0;
    int flag = 0;
    char* temp_unicode =  NULL;
    if(size_n < 0)
    {
        flag  = 1;
        *dest = (char*)calloc(1,strlen(src)+1);
        temp_unicode  = (char*)calloc(1,strlen(src)*2+1);
    }
    else
    {
        *dest = (char*)calloc(1,size_n+1);
        temp_unicode  = (char*)calloc(1,size_n*2+1);
    }

    int end_index = 0;
    int temp_unicode_len = 0;
	char high_byte = 0;
	char low_byte = 0;

	int i = 0;    
    while(src[i] != '\0')
    {
		/* One encoded. ASCII charactor. */
		if(!(src[i] & 0x80))
		{
            if( flag != 1 && i + 1 > size_n )
                break;
			high_byte = 0x00;
			low_byte = src[i];
			i++;
		}
		/* Two encoded. */
		else if(!((src[i] & 0xE0) ^ 0xC0) && !((src[i+1] & 0xC0) ^ 0x80))
		{
            if(flag != 1 && i + 2 > size_n)
                break;
			high_byte = (src[i] & 0x1C) >> 2;
			low_byte = ((src[i] & 0x03) << 6) | (src[i + 1] & 0x3F);
			i += 2;
		}
		/* Three encoded. */
		else if(!((src[i] & 0xF0) ^ 0xE0) && !((src[i+1] & 0xC0) ^ 0x80) && !((src[i+2] & 0xC0) ^ 0x80))
		{
            if(flag != 1 && i + 3 > size_n)
                break;
            printf("123123\n");
			high_byte = ((src[i] & 0x0F) << 4) | ((src[i + 1] & 0x3C) >> 2);
			low_byte = ((src[i + 1] & 0x03) << 6) | (src[i + 2] & 0x3F);
			i += 3;
		}
		/* Four encoded. */
		else if(!((src[i] & 0xF8) ^ 0xF0) && !((src[i+1] & 0xC0) ^ 0x80) && !((src[i+2] & 0xC0) ^ 0x80) && !((src[i+3] & 0xC0) ^ 0x80))
		{
			// Modify in 2011-06-22 as some character like that "𤭢" can not recognized.
            if(flag != 1 && i + 4 > size_n)
                break;
			high_byte = ((src[i + 1] & 0x0F) << 4) | ((src[i + 2] & 0x3C) >> 2);
			low_byte = ((src[i + 2] & 0x03) << 6) | (src[i + 3] & 0x3F);
			i += 4;
		}
		/* Error encoded. */
		else
		{
            temp_unicode[end_index++] = 0;
            temp_unicode[end_index++] = 0;
            return -1;
		}
		
		/* Push back the results with Big-Endian. */
//        1111 1111 

        if(high_byte == (char)0xFF)
        {
            low_byte = low_byte + 0x20 ;
            high_byte = 0x00;
        }
        temp_unicode[end_index++] = high_byte;
        temp_unicode[end_index++] = low_byte;
        temp_unicode_len += 2;
	}

    myeutilm_unicode_to_utf8(*dest,temp_unicode,temp_unicode_len,1);
    free(temp_unicode);
    return 0;
}
    










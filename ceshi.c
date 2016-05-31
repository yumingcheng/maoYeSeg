#include "myeStringUtil.h"


int main(int argc,char* argv[])
{

    char dest_1[1000] = {0};
    char dest_2[1000] = {0};
    int len = 0;
    myeutil_utf8_to_unicode(dest_1,&len,argv[1],1);
    myeutilm_unicode_to_utf8(dest_2,dest_1,len,1);
    printf("[%s]\n",dest_2);

    char* dest = NULL;
    myeutil_full_to_half_angle(&dest,argv[1]);
    printf("dest = [%s]\n",dest);
    free(dest);


    return 0;
}

#include "maoYeSeg.h"

int main(int argc,char* argv[])
{
    maoYeSeg* me =  maoYeSeg_new(ALG_XWSNGRAM);
    maoYeSeg_string_tokenize(me,argv[1],NULL);
    maoYeSeg_delete(me);
    return 0; 
}

#include "maoYeSeg.h"
#include "maoYeMMSeg.h"
#include "maoYeXwsSeg.h"

struct _maoYeSeg
{
    maoYeSegClass* isa;
};

maoYeSeg* maoYeSeg_new(int cflag)
{
    maoYeSeg* me = NULL;
    if(cflag == 0x00000001)
    {
        me = (maoYeSeg*)maoYeMMSeg_new(NULL);
    }
    else if(cflag == 0x00000010)
    {
        me = (maoYeSeg*)maoYeXwsSeg_new(NULL);
    }
    return me;
}

void maoYeSeg_delete(maoYeSeg* me)
{
    me->isa->Destructor(me);
}

int maoYeSeg_string_tokenize(maoYeSeg* me,const char* lpzwInput,void* ppToken)
{
    me->isa->string_tokenize(me,lpzwInput,ppToken);
}

int maoYeSeg_list_tokenize(maoYeSeg* me,const char* lpzwInput,void* ppToken)
{
    me->isa->list_tokenize(me,lpzwInput,ppToken);
}

int maoYeSeg_setopt(maoYeSeg* me,int TYPE,void* p_date)
{
    me->isa->setopt(me,TYPE,p_date);
}

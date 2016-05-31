cc  =  g++
lib = -fPIC  -lm -g -Wall `pkg-config --libs --cflags glib-2.0`
clib = -fPIC -g -Wall -lm

main=maoYeMMSeg.o  maoYeSeg.o  maoYeXwsSeg.o myeDictionary.o  myeSegEngine.o  myeStringUtil.o  myeTokenList.o   myeUtil.o main.o

all:maoYe
maoYe:$(main)
	$(cc) -o maoYe $(main) $(lib) 

$(main):%.o:%.c
	$(cc) -c $< -o $@  $(lib)


.PHONY: clean
clean:
	-rm *.o 
	-rm	maoYe 




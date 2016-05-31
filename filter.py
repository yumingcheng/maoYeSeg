#!/usr/bin/env python
#-*-coding:utf-8-*








worddic = {}
#fp = open('coreDict_Unicode.txt')
#fp = open('BigramDict_Unicode.txt')
fp = open('core.dic')


for line in fp:
    vword = line.split();
    if vword[1] not in worddic:
        worddic[vword[1]] = int(vword[2])
    elif int(vword[2]) > worddic[vword[1]]:
        worddic[vword[1]] += int(vword[2])

for key,value in worddic.items():
    print key,value


        










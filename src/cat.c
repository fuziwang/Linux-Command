#include <stdlib.h>
#include <stdio.h>
#include "cat.h"

int fileCopy(FILE *src,FILE *dest){
	int c;
	while((c=getc(src))!=EOF)
		putc(c,dest);
	return c;
}

int main(int argc,char *argv[]){
	if(argc == 1){
		fileCopy(stdin,stdout);// 如果没有参数，就从键盘获取输入并显示在屏幕
	} else {
		char *input;
		FILE *inf;
		int count = 0;
        while(--argc>0){
			input = argv[argc];
            if((inf=fopen(input,"r"))==NULL){
				printf("\ncan't open %s\n",input);
                continue;
            } 
            count++;
            fileCopy(inf,stdout);
			return 0;
            fclose(inf);
        }
       	getchar();
       	return 0;
	}
}

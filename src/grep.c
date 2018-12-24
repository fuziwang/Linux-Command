#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "grep.h"
 
int main(int argc,char *argv[])
{
    char buffer[MAX_BUFFER];
    FILE *fp;
    int key_sum = 0,res_sum = 0;
    char *buf_ptr = NULL;
    char const *key_ptr = NULL;

    if(argc< 3){
       	printf("lackcommand\n");
       	exit(EXIT_FAILURE);
    }
    if(strlen(FILE_PTR)== 0) {
        printf("filename error\n");
        exit(EXIT_FAILURE);
    }

    fp= fopen(FILE_PTR,"r");
    if(!fp){
        printf("openfile error\n");
        exit(EXIT_FAILURE);
    }
    key_sum= strlen(KEY_PTR);
    printf("find:\n");
    while(fgets(buffer,sizeof(buffer),fp)!= 0){
        buf_ptr= buffer;
        key_ptr= KEY_PTR;
        while(*buf_ptr!= '\0'){
            if((*buf_ptr== '\0')|(*key_ptr == '\0'))
                break;
            if(*buf_ptr== *key_ptr){
                key_ptr++;
                if(*key_ptr== '\0'){
                printf("%s",buffer);
                res_sum++;
            	}
        	}
        	else key_ptr = KEY_PTR;
        	buf_ptr++;
        }
    }
    fclose(fp);
    printf("progress %d is found %d\n",getpid(),res_sum);
    exit(EXIT_SUCCESS);       
}

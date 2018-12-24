#include <stdio.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <time.h> 
#include "stat.h"

void mode_to_letter(int mode,char *str) 
{ 

    str[0]='-';

    if(S_ISDIR(mode)) str[0]='d';
    if(S_ISCHR(mode)) str[0]='c';
    if(S_ISBLK(mode)) str[0]='b';

    if(mode & S_IRUSR) str[1]='r';
    else str[1]='-'; 
    if(mode & S_IWUSR) str[2]='w'; 
    else str[2]='-'; 
    if(mode & S_IXUSR) str[3]='x'; 
    else str[3]='-'; 

    if(mode & S_IRGRP) str[4]='r';
    else str[4]='-'; 
    if(mode & S_IWGRP) str[5]='w'; 
    else str[5]='-'; 
    if(mode & S_IXGRP) str[6]='x'; 
    else str[6]='-'; 

    if(mode & S_IROTH) str[7]='r';
    else str[7]='-'; 
    if(mode & S_IWOTH) str[8]='w'; 
    else str[8]='-'; 
    if(mode & S_IXOTH) str[9]='x'; 
    else str[9]='-'; 

    str[10]='\0'; 
} 
int main(int argc,char *argv[]) 
{ 
    int i, ret; 
    char data[20]; 
    struct stat buf;         
    if(argc < 2) { 
        printf("stat: missing operand\n"); 
        printf("Try 'stat --help' for more information.\n"); 
        exit(-1); 
    } 

    for(i = 1;i < argc; ++i) { 
        ret = stat(argv[i], &buf); 
        if(-1 == ret) { 
            perror("stat"); 
        } else { 
            printf("File: %s\n", argv[i]); 
            printf("Size: %lld              Blocks: %lld          IO Block: %ld   ", (long long) buf.st_size, (long long) buf.st_blocks, (long) buf.st_blksize);         switch (buf.st_mode & S_IFMT) { 
                case S_IFBLK:  printf("block device\n");            break; 
                case S_IFCHR:  printf("character device\n");        break; 
                case S_IFDIR:  printf("directory\n");               break; 
                case S_IFIFO:  printf("FIFO/pipe\n");               break; 
                case S_IFLNK:  printf("symlink\n");                 break; 
                case S_IFREG:  printf("regular file\n");            break; 
                case S_IFSOCK: printf("socket\n");                  break; 
                default:       printf("unknown?\n");                break; 
            }
            printf("Device: fd01h/64769d    Inode: %ld      Links: %ld\n", (long) buf.st_ino, (long) buf.st_nlink);           
            mode_to_letter(buf.st_mode, data);         
            printf("Access: (7204/%s)  Uid: ( %ld/ frewen)   Gid: ( %ld/ frewen)\n", data, (long) buf.st_uid, (long) buf.st_gid);
            printf("Access: %s", ctime(&buf.st_atime)); 
            printf("Modify: %s", ctime(&buf.st_mtime)); 
            printf("Change: %s", ctime(&buf.st_ctime)); 
            printf(" Birth: -\n"); 
        } 
         
    } 
    return 0; 
}

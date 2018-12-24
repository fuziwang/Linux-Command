#ifndef FIND_H

//递归搜寻目录
void listDir(char* path);
//通配符匹配
int isMatch(const char *s, const char *p);
//10的i次方
//因为math.h调用了几次都失败, 就自己写了
int p10(int i);

#endif
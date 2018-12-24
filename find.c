#include<stdio.h>
#include<dirent.h>
#include<regex.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "find.h"

//���ѡ�����, 0����ûָ��, 1����ָ����
//�ֱ���-name, -prune, -ctime, -mtime, -print
int state[5] = {0, 0, 0, 0, 0};
//���-nameָ��������
char name[512];
//���-pruneָ��������
char pname[512];
//���-ctimeָ���Ĳ���, ��-8
char ctim[32];
//���-mtimeָ���Ĳ���, ��-8
char mtim[32];


int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("��������\n");
		exit(1);
	}
	
	//���Ҫ��ѯ��Ŀ¼
	char* path = argv[1];
	//��������
	for(int i = 0; i <= argc-1; ++i)
	{
		if(strcmp(argv[i], "-name")==0)
		{
			//���ָ����-name��û�����ļ���
			if(i>=argc-1)
			{
				printf("��ָ����ѯ�ļ���\n");
				exit(1);
			}
			//�������name����ȫ�ֱ�����
			strcpy(name, argv[i+1]);
			//״ֵ̬��1
			state[0] = 1;
		}
		else if(strcmp(argv[i], "-prune")==0)
		{
			//���ָ����-prune��û����Ŀ¼��
			if(i>=argc-1)
			{
				printf("��ָ����ѯ�ļ���\n");
				exit(1);
			}
			//�ų�Ŀ¼����ͨ���ƥ�����ų�, Ԥ����ͷβ����ͨ���*
			//����di1, �Ὣdir1, dir2���ų�
			strcpy(pname, "*");
			strcat(pname, argv[i+1]);
			strcat(pname, "*");
			state[1] = 1;
		}
		else if(strcmp(argv[i], "-ctime")==0)
		{
			//���ָ����-ctime��û����ʱ��
			if(i>=argc-1)
			{
				printf("��ָ����ѯʱ��\n");
				exit(1);
			}
			strcpy(ctim, argv[i+1]);
			state[2] = 1;
		}
		else if(strcmp(argv[i], "-mtime")==0)
		{
			//���ָ����-mtime��û����ʱ��
			if(i>=argc-1)
			{
				printf("��ָ����ѯʱ��\n");
				exit(1);
			}
			strcpy(mtim, argv[i+1]);
			state[3] = 1;
		}
		else if(strcmp(argv[i], "-print")==0)
		{
			state[4] = 1;
		}
	}
	
	//������ɶʱ�����.��..Ŀ¼, ֱ���趨ָ��-name, -ctime, -mtimeʱ�������.��..
	if(state[0]!=1 && state[2]!=1 && state[3]!=1) printf(".\n..\n");
	listDir(path);
}

void listDir(char* path)
{
	DIR* dir;
	struct dirent* mydirent;
	//�����Ŀ¼��ȫ��, ���ڵݹ�
	char childPath[512];

	if((dir = opendir(path)) != NULL)
	{
		while((mydirent = readdir(dir)) != NULL)
		{
			//��Ÿ��ļ���ȫ·����
			char fullName[1024];
			sprintf(fullName, "%s/%s", path, mydirent->d_name);

			//���ջ�������
			int flag = 1;

			//�����.��.. ���ý����������
			if(strcmp(mydirent->d_name, ".") == 0 || strcmp(mydirent->d_name, "..") == 0) continue;
			//���ָ����-prune��ƥ���ļ���, ��flag==0
			//isMatchΪͨ���ƥ��
			if(state[1]==1 && isMatch(fullName, pname)) flag = 0;
			//���ָ����-name �� ���ļ�������ָ��������, flag==0
			if(flag && state[0]==1 && !isMatch(mydirent->d_name, name)) flag = 0;
			//-ctime
			if(flag && state[2]==1)
			{
				//��ѯ�ļ���ϸ��Ϣ
				struct stat buf;
				stat(fullName, &buf);

				//�����ǰʱ��-�ļ�ctimeʱ��, �����ֵ
				time_t t;
				time(&t);
				//һ��86400��, ������
				int diff = (t - buf.st_ctim.tv_sec)/86400;

				//ctim[]������-12�����ַ���, ��һ����ȡ�������12�ַ�����ת��Ϊint����num��
				int num = 0;
				int i = 0;
				while(ctim[i]!='\0') ++i;
				for(int j = 1; ctim[j]!='\0'; ++j, --i) num+=(ctim[j]-48)*p10(i-2);

				//�����-���ֵһ������Ҫ���, flag==0
				if(ctim[0]=='-')
				{
					if(diff>num) flag = 0;
				}
				//�����+���ֵһ��С��Ҫ���, flag==0
				else if(ctim[0]=='+')
				{
					if(diff<=num)
					{
						flag = 0;
					}
				}
			}
			//mtime
			if(flag && state[3]==1)
			{
				struct stat buf;
				stat(fullName, &buf);

				time_t t;
				time(&t);
				int diff = (t - buf.st_atim.tv_sec)/86400;

				int num = 0;
				int i = 0;
				while(mtim[i]!='\0') ++i;
				for(int j = 1; mtim[j]!='\0'; ++j, --i) num+=(mtim[j]-48)*p10(i-2);

				if(mtim[0]=='-')
				{
					if(diff>num) flag = 0;
				}
				else if(mtim[0]=='+')
				{
					if(diff<=num)
					{
						flag = 0;
					}
				}
			}
			//�������ͨ���ջ���, �����ȫ·����
			if(flag) printf("%s\n", fullName);
			//����Ǹ���Ŀ¼
			if(mydirent->d_type & DT_DIR)
			{
				//�õ���Ŀ¼ȫ���ݹ�����������
				sprintf(childPath, "%s/%s", path, mydirent->d_name);
				listDir(childPath);
			}
		}
		closedir(dir);
	}
}

//ͨ���ƥ�亯��
int isMatch(const char *s, const char *p)
{
    if (s == NULL && p == NULL)
        return 1;
    int m = strlen(s);
    int n = strlen(p);
    if (m == 0 && n == 0)
        return 1;
    int si = 0, pi = 0;
    int xidx = -1, mtch = -1;
    while (si < m)
    {
        if (pi < n && (*(p + pi) == '*'))
        {
            xidx = pi++;
            mtch = si; // si��Ӧxidx��λ��
        }
        else if (pi < n && (*(s + si) == *(p + pi) || *(p + pi) == '?'))
        {
            ++si;
            ++pi;
        }
        else if (xidx > -1)
        { // ��һ�� '*' ��λ��
            pi = xidx + 1;
            si = ++mtch;
        }
        else
        {
            return 0;
        }
    }
    while (pi < n && (*(p + pi) == '*'))
        ++pi;
    return (pi == n);
}

int p10(int i)
{
    if(i == 0) return 1;
    if(i == 1) return 10;
    return 10*p10(i-1);
}

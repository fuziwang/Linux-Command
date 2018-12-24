#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include "chown.h"
 
int main(int argc, char **argv)
{
	char owner[128] = {'\0'}, group[128] = {'\0'};
	int i, o, g;
	struct passwd *pw_own, *pw_gro; //struct passwd 结构用于获得用户信息，如用户名，uid，gid...等 
	DIR *dp;
 
	i = o = g = 0;
	if (argc != 3){
		fprintf(stderr, "usage: %s owner:group path\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	while (argv[1][i] != ':'){
		owner[o] = argv[1][i];
		++i;
		++o;
	}
	owner[o] = '\0';
	++i;
	while (argv[1][i] != '\0'){
		group[g] = argv[1][i];
		++i;
		++g;
	}
	group[g] = '\0';

	if ((pw_own = getpwnam(owner)) == NULL || (pw_gro = getpwnam(group)) == NULL){ 
		printf("error: invalid user '%s'\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	if ((dp = opendir(argv[2])) == NULL){
		if ((i = open(argv[2], O_RDONLY)) != -1)
			close(i);
		else{
			printf("error: cannot access '%s': %m\n", argv[2]);
			exit(EXIT_FAILURE);
		}
	}

	if ((i = open(argv[2], O_RDONLY)) == -1){
		if ((dp = opendir(argv[2])) != NULL)
			closedir(dp);
		else{
			printf("error: cannot access '%s': %m\n", argv[2]);
			exit(EXIT_FAILURE);
		}
	}

	if (chown(argv[2], pw_own->pw_uid, pw_gro->pw_uid) < 0)
		perror("error");
		
	exit(EXIT_SUCCESS);
}
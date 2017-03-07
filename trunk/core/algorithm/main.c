/*********************************************************
 * Author			: crazy_mad
 * Last modified	: 2017-03-06 12:33
 * Filename			: main.c
 * Description		: 
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	pid_t pid = fork();
	if (pid == 0) {
		//execl("./algorithm", "algorithm", "mai.c");
		execl("/usr/bin/algorithm", "algorithm", "/home/crazymad/github/hustoj/trunk/core/algorithm/test.c", (char*)NULL);
	} else if (pid > 0){
		int ret;
		wait(&ret);
	  	printf("%d\n", WEXITSTATUS(ret));	
	} else {
		perror("fork error");
		exit(1);
	}

	return 0;
}

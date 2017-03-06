#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	for (int i = 1; i < 10; i++) {//test
		/*hello world!*/printf("hello world!\n");
	}
	FILE *fp;
	char buf[256] = { 0 };
	fp = fopen("main.c", "r");
	while (fgets(buf, 256, fp)) {
		printf("%s\n", buf);
	}
	while (fgets(buf, 256, fp)) {
		printf("%s\n", buf);
	}
	fclose(fp);

	return 0;
}

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
	execl("./algorithm", "algorithm", "main.c");

	return 0;
}

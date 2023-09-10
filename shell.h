#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define BUF_SIZE 1024
#define BUF_FLUSH (-1)
#define PROMPT "$ "

extern char **environ;

/************* FUNCTIONS *************/

/* write functions */
int _putchar(char c);
int _puts(char *str);

#endif

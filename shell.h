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

/************* STRUCTURES ************/
struct session_info
{
	unsigned int status;
	unsigned long iter_num;
};
typedef struct session_info s_info;

/************* FUNCTIONS *************/

/* write functions */
int _putchar(char c);
int _puts(char *str);

/* string functions */
char *_strdup(const char *str);
size_t _strlen(const char *str);

/* number functions */
unsigned int digits_counter(unsigned long num);
char *convertUnsignedNum(unsigned long num);
int _atoi(char *s);

/* errors functions */
int command_validity_checker(s_info s_i, char *cmd, int print_error);

/* memory functions */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif

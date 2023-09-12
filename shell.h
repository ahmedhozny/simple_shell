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
int _strcmp(char *s1, char *s2);
char **getArgs(const char *str, const char *delim);

/* number functions */
unsigned int digits_counter(unsigned long num);
char *convertUnsignedNum(unsigned long num);
int _atoi(char *s);
int _isPositiveNumber(char *str);

/* errors functions */
int command_validity_checker(s_info s_i, char *cmd, int print_error);
int exitcode_validity_checker(s_info s_i, char *exit_code, int print_error);

/* memory functions */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void bigFree(char **ptr, int size);

/* execute functions */
int _execute(s_info *s_i, char *arg0, char **argv);

/* system functions */
void exit_sh(s_info s_i, char **argv);
void exit_with_status(s_info s_i, char *code);
void _EOF(s_info s_info, ssize_t line_size);

#endif

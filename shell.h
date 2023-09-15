#ifndef SHELL
#define SHELL

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define BUF_FLUSH (-1)
#define ERROR_FLUSH (-2)
#define PROMPT "$ "

extern char **environ;

/************* STRUCTURES ************/

/**
 * struct node - node of singly linked
 * @d_ptr: pointer to the data
 * @next: points to the next node
 *
 * Description: structure of a singly linked list node
 */
typedef struct node
{
	void *d_ptr;
	struct node *next;
} node;

/**
 * struct list - creates singly linked list
 * @data_type: data type of the given data
 * @head: points to the head node
 *
 * Description: structure of a singly linked list node
 */
typedef struct list
{
	char data_type;
	struct node *head;
} list;

/**
 * struct session_info - struct for session_info
 * @status: current status code
 * @iter_num: current iteration number
 * @cur_line: current line of input
 * @cur_cmd: current command array
 * @env_keys: list of environment keys
 * @env_vals: list of environment values
 *
 * Description: struct to store all needed information
 * about the current session
 */
typedef struct session_info
{
	unsigned int status;
	unsigned long iter_num;
	char *cur_line;
	char **cur_cmd;
	list *env_keys;
	list *env_vals;
} s_info;

/**
 * struct builtin - struct for built-in cmd
 * @str: string to cmd
 * @func: pointer to the proper function
 *
 * Description: struct to choose
 * the appropriate function to execute built-in commands
 */
typedef struct builtin
{
	char *str;
	int (*func)(s_info *s_i, char **args);
} builtin;

/************* FUNCTIONS *************/

/* write functions */
int _putchar(char c);
int _puts(char *str);

/* string functions */
char *_strdup(const char *str);
size_t _strlen(const char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *s1, char *s2, char between);
char **strtow(char *str, char delim);
char **split(char *str, char delim);
char **getArgs(const char *str, const char *delim);

/* number functions */
unsigned int digits_counter(unsigned long num);
char *convertUnsignedNum(unsigned long num);
int _atoi(char *s);
int _isPositiveNumber(char *str);

/* errors functions */
int command_validity_error(s_info *s_i, char *cmd, int print_error);
int exitcode_validity_checker(s_info *s_i, char *exit_code, int print_error);

/* memory functions */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void bigFree(char **ptr, int size);
void cleanup(s_info *s_i);

/* execute functions */
int _execute(s_info *s_i, char *arg0, char **argv);

/* system functions */
void exit_sh(s_info *s_i, char **argv);
void exit_with_status(s_info *s_i, char *exit_code);
void _EOF(s_info *s_i);

/* handelers functions */
char *break_cmd(char *cmd);
char *search_PATH(s_info *s_i, char *cmd);
int exec_builtin(s_info *s_i, char **args, char *cmd);

/* lists functions */
list *create_list(char type);
node *append_node(list *list, void *data);
node *insert_node(list *list, int index, void *data);
void free_list(list *list, int keep_pointers);
size_t print_list(const list *h);
int get_index(list *list, char *key);
node *get_node(list *list, unsigned int index);
int delete_node(list *list, unsigned int index, int keep_pointers);
int list_size(list *list);
node *amend_node(list *list, unsigned int index, void *data);

/* environment functions */
int init_environment(s_info *s_i);
char **environment_to_array(s_info *s_i);
void print_env(s_info *s_i);
node *_getenv(s_info *s_i, char *key);
int _setenv(s_info *s_i);
int _unsetenv(s_info *s_i);

/* SHELL functions */
int shell(s_info *s_i);

#endif

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
 * @env_keys: list of environment keys
 * @env_vals: list of environment values
 *
 * Description: struct to store all needed information
 * about the current session
 */
struct session_info
{
	unsigned int status;
	unsigned long iter_num;
	list *env_keys;
	list *env_vals;
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
char *_strcat(char *s1, char *s2, char between);
char **strtow(char *str, char delim);
char **getArgs(const char *str, const char *delim);

/* number functions */
unsigned int digits_counter(unsigned long num);
char *convertUnsignedNum(unsigned long num);
int _atoi(char *s);
int _isPositiveNumber(char *str);

/* errors functions */
int command_validity_checker(s_info *s_i, char *cmd, int print_error);
int exitcode_validity_checker(s_info *s_i, char *exit_code, int print_error);

/* memory functions */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void bigFree(char **ptr, int size);

/* execute functions */
int _execute(s_info *s_i, char *arg0, char **argv);

/* system functions */
void exit_sh(s_info *s_i, char **argv);
void exit_with_status(s_info *s_i, char *code);
void _EOF(s_info *s_i, ssize_t line_size);

/* handelers functions */
char *search_PATH(s_info *s_i, char *cmd);

/* lists functions */
list *create_list(char type);
node *append_node(list *list, void *data);
node *insert_node(list *list, int index, void *data);
void free_list(list *list, int keep_pointers);
size_t print_list(const list *h);
node *get_node(list *list, unsigned int index);
int delete_node(list *list, unsigned int index);
int list_size(list *list);
node *amend_node(list *list, unsigned int index, void *data);

/* environment functions */
int init_environment(s_info *s_i);
char **environment_to_array(s_info *s_i);
node *_getenv(s_info *s_i, char *key);
int _setenv(s_info *s_i, char *key, char *val);

#endif

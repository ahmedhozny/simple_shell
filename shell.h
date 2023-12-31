#ifndef SHELL
#define SHELL

#include <errno.h>
#include <fcntl.h>
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

#define CMD_SEP (-1)
#define CMD_AND (-2)
#define CMD_OR (-3)

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
 * @fd: number of file descriptor
 * @inst_prefix: prefix of our instance
 * @prev_dir: previous directory
 * @cur_line: current line of input
 * @cur_cmd: current command array
 * @cmd_list: commands list
 * @ops_list: operators list
 * @env_keys: list of environment keys
 * @env_vals: list of environment values
 * @als_keys: list of all stored aliases
 * @als_vals: list of aliases values
 *
 * Description: struct to store all needed information
 * about the current session
 */
typedef struct session_info
{
	unsigned int status;
	unsigned long iter_num;
	int fd;
	char *inst_prefix;
	char *prev_dir;
	char *cur_line;
	char **cur_cmd;
	char **cmd_list;
	int *ops_list;
	list *env_keys;
	list *env_vals;
	list *als_keys;
	list *als_vals;
} s_info;

/************* FUNCTIONS *************/

/* write functions */
int _putchar(char c);
int _puts(char *str);

/* string functions */
char *_strdup(const char *str);
size_t _strlen(const char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *s1, char *s2, char between);
int isValidName(char ch);

/* splitting functions */
char **strtow(char *str, char delim);
char **split(char *str, char delim);
int break_chain(s_info *s_i);

/* number functions */
unsigned int digits_counter(unsigned long num);
char *convertUnsignedNum(unsigned long num);
int _atoi(char *s);
int _isPositiveNumber(char *str);

/* errors functions */
int command_validity_error(s_info *s_i, char *cmd, int prints);
int exitcode_validity_checker(s_info *s_i, char *exit_code, int prints);
int cd_validity_checker(s_info *s_i, char *dir, int prints);
int bad_chain_error(s_info *s_i, int op, int prints);
void print_error(s_info *s_i, char *err_message, char *err_reason);
int file_permission_error(s_info *s_i, int prints);
int file_error(s_info *s_i, char *file_name);

/* memory functions */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void bigFree(char **ptr, int size);
void cleanup(s_info *s_i);

/* execute functions */
int _execute(s_info *s_i);
int pre_execute(s_info *s_i);

/* exit functions */
void exit_sh(s_info *s_i);
void exit_with_status(s_info *s_i);
void _EOF(s_info *s_i);

/* handlers functions */
int check_chain(const char *str);
void handle_input(s_info *s_i);
int handle_op(s_info *s_i, int op);
void handle_comments(s_info *s_i);
char *search_PATH(s_info *s_i);

/* built-in handlers functions */
int exec_builtin(s_info *s_i);
int cd(s_info *s_i);
int change_dir(s_info *s_i, char *pwd);

/* variable replacement functions */
int variable_rep(s_info *s_i);

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
int _setenv(s_info *s_i, char *key, char *value);
int _unsetenv(s_info *s_i);

/* alias functions */
int init_aliases(s_info *s_i);
void alias_handler(s_info *s_i);
void print_alias(s_info *s_i, char *name);
char *get_alias(s_info *s_i, char *name);
void set_alias(s_info *s_i, char *name, char *value);

/* line reader functions */
ssize_t readline(char **ptr, size_t *n, int fd);
int read_char(char *c, int fd);

/* SHELL functions */
int shell(s_info *s_i);
s_info *session_getter_setter(s_info *s_i);

#endif

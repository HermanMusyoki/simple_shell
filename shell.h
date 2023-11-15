#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for reading  or writing buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for chaining commands*/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for changeNUM() to convert numbers */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list struct
 * @num: parameter for the number of  categories
 * @str: pointer to a string
 * @next: points to the next node in the linked list
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - stores the pseudo-arguements that are passed to the
 * function, enabling uniform prototype for function pointer struct
 * @alias: the alias node
 * @arg: a string formed from getline storing arguements
 * @histcount: the history line number count of the program
 * @argv:an array of strings passed from arguments
 * @path: the path for current command
 * @readfd: the fd from which to read line input
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @argc: the argument count passed to the function
 * @line_count: parameter for error line count
 * @err_num: code for the error count for exits
 * @linecount_flag: if on count this line of input
 * @fname: the name for the file of the program
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @env: linked list local copy of environment
 * @environ: a  copy of environ from LL env that is in custom
 * @history: the history node
 * @env_changed: checks if the environ has changed
 * @status: the return status of the last exececuted command
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path; /* pointer to the path */
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /*  double pointer to cmd ; chain buffer, to manage memory */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - a struct that contains a builtin string
 * and related function
 * @type: the builtin command flag
 * @func: pointer to the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/***** firstList.c *****/
size_t listLength(const list_t *h);
char **strList(list_t *head);
size_t outputList(const list_t *h);
list_t *nodeBeginsChar(list_t *node, char *prefix, char c);
ssize_t retrieveNode(list_t *head, list_t *node);

/***** FuncErrors.c *****/
void cyso_puts(char *str);
int cyso_putchar(char c);
int put_FD(char c, int fd);
int puts_FD(char *str, int fd);

/***** functionComponent.c *****/
int displayHistory(info_t *info);
int removeAlias(info_t *info, char *str);
int addAlias(info_t *info, char *str);
int outputAlias(list_t *node);
int cyso_alias(info_t *info);

/***** getShellEnv.c *****/
char **getShellEnv(info_t *info);
int removeEnv(info_t *info, char *var);
int addEnv(info_t *info, char *var, char *value);

/***** memRealloc.c *****/
char *addMemory(char *str, char b, unsigned int n);
void freeStrings(char **dptr);
void *memoryRealloc(void *ptr, unsigned int old_size, unsigned int new_size);

/***** shHistory.c *****/
char *retrieveHistoryFile(info_t *info);
int createHistory(info_t *info);
int checkHistory(info_t *info);
int createHistoryList(info_t *info, char *buf, int linecount);
int listHistory(info_t *info);

/***** stringFunc.c *****/
char *stringCpy(char *dest, char *src);
char *stringDup(const char *str);
void _puts(char *str);
int _putchar(char c);

/***** stringToInteger *****/
int active_sh(info_t *info);
int check_delimiter(char c, char *delimiter);
int checkAlpha(int c);
int stringToInteger(char *str);

/***** terminates.c *****/
char *stringnCpy(char *dest, char *src, int n);
char *stringnCat(char *dest, char *src, int n);
char *stringChr(char *str, char chars);

/***** varsFunc.c *****/
int cyso_isChain(info_t *info, char *buf, size_t *p);
void readChain(info_t *info, char *buf, size_t *p, size_t st, size_t len);
int changeAlias(info_t *info);
int changeVars(info_t *info);
int changeString(char **old, char *new);

/*****builtinFunctions.c****/
int cyso_Cd(info_t *info);
int cyso_exit(info_t *info);
int cyso_Aid(info_t *info);

/*****errorFunctions1.c****/
int cyso_Erratoi(char *s);
void outputError(info_t *info, char *estr);
int outputD(int input, int fd);
char *changeNum(long int num, int base, int flags);
void deleteComments(char *buf);

/*****getInformationFunc.c****/
void deleteInfo(info_t *info);
void setInfo(info_t *info, char **av);
void freeInfo(info_t *info, int all);

/******listsFunc.c*****/
list_t *putNode(list_t **head, const char *str, int num);
list_t *putNodeEnd(list_t **head, const char *str, int num);
size_t outputListstr(const list_t *h);
int removeNodeatIndex(list_t **head, unsigned int index);
void freeList(list_t **head_ptr);

/*****stringComponents.c*****/
int stringLen(char *s);
int stringCmp(char *s1, char *s2);
char *beginWith(const char *haystack, const char *needle);
char *stringCat(char *dest, char *src);

/****environFunction.c*****/
int cyso_env(info_t *info);
char *getEnv(info_t *info, const char *name);
int cyso_addEnv(info_t *info);
int cyso_removeEnv(info_t *info);
int fillEnv_list(info_t *info);

/*****funcMem.c*****/
int cysoFree(void **ptr);

/****getLineFunc.c******/
ssize_t inputBuffer(info_t *info, char **buf, size_t *len);
ssize_t getInput(info_t *info);
ssize_t readBuffer(info_t *info, char *buf, size_t *i);
int get_Line(info_t *info, char **ptr, size_t *length);
void sigint_handler(__attribute__((unused))int sig_num);

/*****parserFunc.c*****/
int checkCommand(info_t *info, char *path);
char *duplicateChars(char *pathstr, int start, int stop);
char *locatePath(info_t *info, char *pathstr, char *cmd);

/***shLoop.c*****/
int cyso_hsh(info_t *info, char **av);
int locateBuiltin(info_t *info);
void locateCommand(info_t *info);
void forkCommand(info_t *info);

/*****tokenfunc.c******/
char **stringTow(char *str, char *d);
char **stringTow2(char *str, char d);

#endif /* _SHELL_H_ */

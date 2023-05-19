#ifndef _CHWA_H_
#define _CHWA_H_


#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct string_list - singly linked list
 * @numbr: The number list
 * @string: pointer to string
 * @next: pointer to next
 */
typedef struct string_list
{
	int numbr;
	char *string;
	struct string_list *next;
} pass_list;

/**
 * struct cmd_execute - structure with commands to execute
 * @arg: arguments
 * @argv: array of arguments
 * @path: path
 * @arg_count: arg count
 * @cnt_line: line count
 * @error_numb: code to exit error
 * @count_flag: line count of input
 * @finame: filename
 * @env: pointer to a struct
 * @history: pointer to a struct
 * @alias: pointer to a struct
 * @environ: environment
 * @chnge_envir: environment change
 * @exec_status: exec_status to be executed
 * @cmand_buff: buffer
 * @cmand_buff_tp: ty_pes of buffer
 * @rd_filedes: read file descriptor
 * @count_history: history count
 */
typedef struct cmd_execute
{
	char *arg;
	char **argv;
	char *path;
	int arg_count;
	unsigned int cnt_line;
	int error_numb;
	int count_flag;
	char *finame;
	pass_list *env;
	pass_list *history;
	pass_list *alias;
	char **environ;
	int chnge_envir;
	int exec_status;
	char **cmand_buff;
	int cmand_buff_tp;
	int rd_filedes;
	int count_history;
} exec_info;

#define _init_ \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct built_in - contains a built_in string and related function
 *@ty_pes: the built_in command flag
 *@fnctn: the function
 */
typedef struct built_in
{
	char *ty_pes;
	int (*fnctn)(exec_info *);
} built_in_table;

void errPrt(exec_info *, char *);
int decPtr(int, int);

int fill_env_list(exec_info *);
int shenv(exec_info *);
int shsetenv(exec_info *);
char *shgetenv(exec_info *, const char *);
int shunsetenv(exec_info *);

int ali2str(exec_info *, char *);
int aliasPtr(pass_list *);
int setAlias(exec_info *, char *);
int shalias(exec_info *);
int shhistory(exec_info *);

int chainTester(exec_info *, char *, size_t *);
void chainer(exec_info *, char *, size_t *, size_t, size_t);

int err2int(char *);
char *numConverter(long int, int, int);
void delComments(char *);

char **gEnviron(exec_info *);
int sEnviron(exec_info *, char *, char *);
int uSetEnv(exec_info *info, char *var);

int isExec(exec_info *, char *);
char *charDuplicate(char *, int, int);
char *pathLoc(exec_info *, char *, char *);

int write2histFile(exec_info *info);
int refreshHistList(exec_info *info);
int readHistFile(exec_info *info);
char *getHistFile(exec_info *info);
int genHistList(exec_info *info, char *buf, int linecount);

void finf(exec_info *, int);
void clinf(exec_info *);
void setinf(exec_info *, char **);

int ptrFree(void **);

ssize_t getIndex(pass_list *, pass_list *);
char **list2string(pass_list *);
size_t listLength(const pass_list *);
pass_list *prefixSearch(pass_list *, char *, char);
size_t lstPrt(const pass_list *);

int IntaractiveStatus(exec_info *);
int alphaChecker(int);
int dChecks(char, char *);
int s2i(char *);

char *catStr(char *, char *, int);
char *cpystr(char *, char *, int);
char *chrLoc(char *, char);

size_t strListPrt(const pass_list *);
void listFree(pass_list **);

pass_list *nodeAdd(pass_list **, const char *, int);
int delNode(pass_list **, unsigned int);
pass_list *nodeAppend(pass_list **, const char *, int);

ssize_t readBuffer(exec_info *, char *, size_t *);
int lineGet(exec_info *, char **, size_t *);
void signalInterruptH(int);
ssize_t gInput(exec_info *);

void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

int shExit(exec_info *);
int shcd(exec_info *);
int shhelp(exec_info *);

int shputchar(char);
int _putchar(char);

int shputfd(char c, int fd);
int shputsfd(char *string, int fd);
void shputs(char *);
void _puts(char *);

int exec_builtin(exec_info *);
void _spawncmd(exec_info *);
void search_cmd(exec_info *);
int shell_loop(exec_info *, char **);

int str_compare(char *, char *);
int str_length(char *);
char *str_starts_with(const char *, const char *);
char *str_concat(char *, char *);

char *duplicate_str(const char *);
char *copy_string(char *, char *);

char **str2wrd(char *, char *);

char **str2wrd2(char *, char);

int aliSub(exec_info *);
int varSub(exec_info *);
int stringSub(char **, char *);

#endif

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
/**
 * struct builtin - builtin strings
 * @type: builtin flah
 * @func: function
*/

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

typedef struct passinfo
{
char *arg;
char **argv;
char *path;
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
char **cmd_buf;
int cmd_buf_type;
int readfd;
int histcount;
} info_t;

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
void handle_file_open_error(char **argv);
void populate_and_read_history(info_t *info, char **argv);
char *getCurrentdirectory(char *buffer, size_t size);
int validateAndConvert(char *argument);
int exitShell(info_t *info);
void _eputs(char *str);
void _eputchar(char c);
void _puts(const char *str);
void printError(info_t *info, const char *message);
int handleNoArgument(info_t *info, char *buffer);
int handleDashargument(info_t *info, char *currentDir, char *buffer);
void handleChdirResult(info_t *info, int chdirResult, char *currentDir, char *buffer);
int handleChangeDirArgument(info_t *info);
void printList(list_t *list);
int deleteNodeAtIndex(list_t **head, unsigned int index);
unsigned int getNodeIndex(list_t *list, int (*compare)(list_t *, char *, int), char *prefix);
list_t *nodeStartsWith(list_t *list, char *prefix, int n);
list_t *addNodeEnd(list_t **head, char *str, int n);
void _putchar(char c);
int displayHistory(info_t *info);
int _putsfd(char *str, int fd);
int _putfd(char c, int fd);
int aliasCompare(char *str, char *prefix, char *unused);
int displayEnvironment(info_t *info);
char *_getEnv(info_t *info, const char *name);
int _setEnvR(info_t *info);
int unsetEnvR(info_t *info);
int populateEnv_list(info_t *info);
int printAlias(list_t *node);

#endif

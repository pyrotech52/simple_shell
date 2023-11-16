#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <stddef.h>
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
}list_t;

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
char ** cmd_buf;
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
#endif

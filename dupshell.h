#ifndef DUPSHELL_H
#define DUPSHELL_H

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

extern char **environ;

/* used to define custom getline()*/
#define ENABLE_GETLINE 0
#define ENABLE_STRTOK 0

#define HISTORY_FILE_NAME ".my_shell_history"
#define MAX_HISTORY_ENTRIES 4096

/* used to convert numbers */
#define LOWERCASE_ENABLED 1
#define UNSIGNED_ENABLED  2

/* used to merge several commands */
#define NORM  0
#define OR    1
#define AND   2
#define CHAIN 3

/* used to read&writing buffers */
#define R_BUF_SZ 1024
#define W_BUF_SZ 1024
#define FLASH_INDICATOR -1

/**
 *struct argbundle - holds pseudo-arguments for a function
 *@argstr: user input fetched by getline
 *@argvstr: string array obtained from user input
 *@path: path of current argument string
 *@argc_no: number of arguments
 *@line_tt: number of errors
 *@error_no: exit()s error code
 *@counter_line: the number of lines in each output
 *@filename: filename of current program
 *@envcpy: singly linked list local environ copy
 *@environcpy: edited environ copy
 *@hist: node in singly linked list
 *@aka: alternate name of node
 *@altered_env: denote environ change
 *@status: info about the last exec'd command
 *@buf_cmd: pointer address to buf_cmd, it is used when chaining commands
 *@buf_operation: variable to specify command opperation ||, &&, ;
 *@rdfiledes: file descriptor from which line input is read
 *@numhist: keeps track of the history line number count
 */
typedef struct argbundle
{
	char *argstr;
	char **argvstr;
	char *path;
	int argc_no;
	unsigned int line_tt;
	int error_no;
	int counter_line;
	char *filename;
	list_t *envcpy;
	list_t *hist;
	list_t *aka;
	char **environcpy;
	int altered_env;
	int status;

	char **buf_cmd;
	int buf_operation;
	int rdfiledes;
	int numhist;
} system;

#define SYSTEMINFO \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct lststr - singly linked list
 * @no: the number field
 * @string: a string
 * @next_node: points to the next node
 */

typedef struct lststr
{
	int no;
	char *string;
	struct lststr *next_node;
} lst_t;

/**
 * struct built - contains a builtin string and related function
 * @cmd: the builtin command flag
 * @handler: the function
 */
typedef struct built
{
	char *cmd;
	int (*handler)(system *);
} built_t;

/*used in the file (strget.c) */
ssize_t getSysInput(system *);
int custGetLine(system *, char **, size_t *);
void handleSigint(int);

/* used in the file (strparse.c)*/
int cmd_exist(system *, char *);
char *dup_str(char *, int, int);
char *cmd_path(system *, char *, char *);

/* used in the file (strtoken.c) */
char **tkzStr(char *, char *);
char **tkzStr2(char *, char);

/* used in the file (strexec.c) */
int strexec(system *, char **);
int search_builtin(system *);
void search_cmd(system *);
void child_fork(system *);

/* used in the file (loopexec.c) */
int loopexec(char **);

/* used in the file (strenv.c) */
char **strenv(system *);
int rmsetenv(system *, char *);
int setenvset(system *, char *, char *);

/* used in the file (strenviron.c) */
char *retrivenv(system *, const char *);
int managenv(system *);
int modsetenv(system *);
int unsetenvrm(system *);
int intenvar(system *);

/* used in the file (strinfo.c) */
void resetinfo(system *);
void settinginfo(system *, char **);
void memfrinfo(system *, int);

/* used in the file (strerr.c) */
void output(char *);
int putoutchar(char);
int writechar(char c, int file_desc);
int writestr(char *str, int file_desc);

/* used in the file (strerr1.c) */
int atoiErr(char *);
void outputErr(system *, char *);
int print_int(int, int);
char *stringify_no(long int, int, int);
void strip_comment(char *);

/* used in the file (nodemod.c) */
lst_t *putnode_start(lst_t **, const char *, int);
lst_t *putnode_end(lst_t **, const char *, int);
size_t printstrlst(const lst_t *);
int rmnodeindex(lst_t **, unsigned int);
void memfree(lst_t **);

/* used in the file (nodemod1.c) */
size_t szlst(const lst_t *);
char **lsttostr(lst_t *);
size_t putlst(const lst_t *);
lst_t *specprefix(lst_t *, char *, char);
ssize_t retrindex(lst_t *, lst_t *);

/* used in the file (str.c) */
int str_len(char *);
int str_cmp(char *, char *);
char *str_start(const char *, const char *);
char *str_cat(char *, char *);

/* used in the file (str1.c) */
char *str_cpy(char *, char *);
char *str_dup(const char *);
void _puts(char *);
int _putchar(char);

/* used in the file (prdfndcmd.c) */
int exitbin(system *);
int cdbin(system *);
int helpbin(system *);

/* used in the file (prdfndcmd1.c) */
int histdisp(system *);
int createaka(system *);

/* used in the file (manmemory.c)*/
char *filblock(char *, char, unsigned int);
void freemem(char **);
void *reallocmem(void *, unsigned int, unsigned int);

/* used in the file (freemem.c) */
int clearmem(void **);

/* used in the file(stratoi.c) */
int modsys(system *);
int delimchar(char, char *);
int alphachar(int);
int strtint(char *);

/* used in the (strvar.c) */
int check_opp(system *, char *, size_t *);
void chainproc(system *, char *, size_t *, size_t, size_t);
int akasub(system *);
int varsub(system *);
int strsub(char **, char *);

/* used in the (manhistory.c)*/
char *rethistfile(system *systeminfo);
int wrthist(system *systeminfo);
int rdhist(system *systeminfo);
int conhistlst(system *systeminfo, char *buf, int counter_line);
int renohist(system *systeminfo);

/* used in the (term.c) */
char *str_n_cpy(char *, char *, int);
char *str_n_cat(char *, char *, int);
char *str_chr(char *, char);

#endif

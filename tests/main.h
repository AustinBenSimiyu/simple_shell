#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/**
 * struct list - l,list
 * @var: vars
 * @next: next code
 */
typedef struct list
{
	char *var;
	struct list *next;

} list_t;

int exec_cmd(char **token, list_t *ev, int num, char **cmmd);
char *space_null(char str);
void concat(int i);
int prompt(char **envr);
int _atoi(char *str);
int builtin_exit(char **str, list_t *ev, int num, char **cmmd);
char *_strcat(char *des, char *str);
int _set_env(list_t **ev, char *num, char *d);
void _home(list_t *ev, char *curr);
int exec_cd(list_t *ev, char *curr, char *dir, char *str, int num);
int _cd(char **str, list_t *ev, int num);
void *_realloc(void *ptr, unsigned int old_size, unsigned int n_size);
size_t _getline(char **line);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *des, char *str);
char *_strdup(char *str);
int _strlen(char *str, int posn, char delm);
int token_str(char *str, char delm);
char *ignore_d(char *str, char delm);
char **_strtok(char *str, char *del);
char *_wh(char *str, list_t *ev);
int _size(char *str, char delm);
int **_token(char *str, char *delm);
list_t *env_lst(char **ev);
int builtin_env(char **str, list_t *ev);
void _free(char **arr);
char *_dup(char *str, int bts);
char *env_find(char *nm, list_t *ev);
int num_length(int num);
char intstr(int num);
size_t _printf(list_t *list);
list_t *append_node(list_t **head, char *data);
int get_idx(list_t **head, int index);
void free_list(list_t * lists);
char *ignore_chars(char *str);
void non_interactive(list_t *env);
void no_dir_change(char *str, int num, list_t *ev);
void num_wrng(char *str, int num, list_t *ev);
void not_found(char *str, int num, list_t *ev);
int get_envr(list_t *ev, char *name);
int _unsetenv(list_t **ev, char **str);
int _setenv(list_t **ev, char **str);
int _exe(char **cmmd, list_t *ev, int num);
void _cont(int i, char *cmmd, list_t *ev)

#endif

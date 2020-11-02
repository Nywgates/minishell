/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 08:34:39 by qgimenez          #+#    #+#             */
/*   Updated: 2020/11/02 10:10:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <assert.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct	s_lst
{
	void			*maillon;
	struct s_lst	*next;
	int				pipe;
}				t_lst;

typedef	struct	s_var
{
	char	**argument;
	int		first;
	int		status;
	int		fdleft[2];
	int		fdright[2];
	int		*fd_out;
	int		*fd_in;
	int		pos;
	int		pos_in;
	int		error;
	char	**env;
	pid_t	pid;
}				t_var;

typedef struct	s_fils
{
	pid_t			pid;
	struct s_fils	*next;
}				t_fils;

int				g_sigbool;
int				g_stt;
int				g_storestt;
int				g_gpid;
char			**g_env;
char			**g_cmd;
char			**g_arg;
t_var			g_fd;
t_fils			*g_fiston;
t_lst			*g_lst;
char			*g_save;
char			*g_nsm;
int				g_err;

int				err_pipe(t_lst *lst, char **my_path);
char			*get_path(char *home, char *argument);
char			*get_current(char *home);
int				print_cd(t_lst *lst);
void			sigint(int i);
void			signothing(int i);
int				print_echo(t_lst *lst, t_var fd);
t_var			fdp(char **argument);
int				count_pipe(char **argument);
int				get_fd(char **argument, t_var *fd);
int				chev_left(char **argument, int i, t_var *fd);
int				chev_right(char **arg, int i, t_var *fd, int n);
char			**get_env(char *name, char **env);
void			ft_env(char **arg, char **env);
int				print_env(int fd, char ***environ);
int				print_unset(t_lst *lst, char ***env);
int				print_export(t_lst *lst, int fd, char ***env);
char			*get_name(char *str);
void			dollar_inte(char **arg, int i, int n);
void			dollar_dieze(char **arg, int i, int n);
void			dollar_zero(char **arg, int i, int n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
void			ft_swap(char **s1, char **s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin_free(char *s1, char *s2, int num);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_strncmp(char *s1, const char *s2, size_t n);
int				get_next_line(int fd, char **line);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlen(const char *str);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strchr(const char *s, int c);
char			**ft_set_split(char *s, char *set, char *keep);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
void			need_line(char *keep, char **s, char ***k);
void			*freebuffs(char **buff);
void			*ft_calloc_bis(size_t count, size_t size);
char			*get_current(char *home);
int				ft_exit(t_lst *lst, char *my_path, char **flags);
char			**tronk(char **arg, int start, int end);
int				ft_check_in(char *str, char c);
int				ft_error(char *str, int ret);
void			free_dbl_ptr(char **ptr);
t_lst			*ft_lstnew(void *content);
void			ft_lstadd_back(t_lst **alst, t_lst *toto);
void			ft_lstclear(t_lst **lst);
char			**capture_the_flag(t_lst *lst, char *my_path);
char			*env_path(t_lst *lst);
void			ft_pidadd_back(t_fils **at_fils, t_fils *toto);
t_fils			*ft_pidnew(pid_t pid);
void			ft_pidclear(t_fils **tata);
int				exec_bin_pipe(t_lst *lst, t_var fd, char ***env);
int				print_path(int fd);
char			*ft_itoa(int n);
int				ft_alphabet(char **env, int len, int fd);
int				get_size(char **tab);
int				ft_atoi(const char *str);
char			**mem_no_flag(void);
char			**ft_split_mini(char const *s, char c);
int				count_size_mini(char const *s, char c);
int				find_arg(char *arg, char **environ);
char			*get_arg(char *argument);
int				ft_alphabet(char **env, int len, int fd);
int				check_arg(char *argument);
void			mouv_maillon(t_lst **lst, t_var *var, char *path, char **flag);
void			init_var_exec(t_var *var, char ***env);
int				check_built_in(char *str);
void			ft_wait_pid(t_fils *fiston, char *name);
int				comp_len(char *str, size_t l, t_lst *lst);
int				built_in(t_lst *lst, t_var var, char *my_path, char **flags);
void			exec_fils(t_lst *lst, char *my_path, char **flags, t_var var);
int				check_pipe(char **argument);
char			*check_quote(t_lst *lst);
void			ft_quote1(t_lst *lst, char *aux);
void			*del_quote_lst(t_lst *lst);
void			filter(char *commande, char ***env);
void			help_quote(t_lst *lst, char *mem, char **str);
char			*boobool(char *line, char mem, int *titi);
int				help_chev_r(int j, char **aux, t_var *fd, int n);
void			ft_quote(t_lst *lst, char *aux, char mem, char *str);
void			doodool(char **res, char **aux, char *mem, int *i);
char			*doodool2(char **res, char **aux);
void			dedel2(char **res, char **aux, int *i);
int				c(char c, char *tab);
void			bs_dbquote2(int *i, char *mem, char *aux, int *n);
int				chev_r_after_quote(char **argument, int i, t_var *fd, int n);
int				rt_read(int ret, char **buf);
int				check_chev(char **argument);
int				error_token(char *line);
int				skip_quote(char *line, int *i);
int				check_blank(char *line, int b);
void			ft_env_tri(char **arg, int i, int n, char **env);
void			ft_env_bis(char **arg, int i, int *n, char **env);
void			ft_env2(char **arg, int i, int n, char **env);
int				free_env(char **env, char *line);
void			ft_exit2(int i);
void			ft_exit3(int i, char **flags, char *my_path, int bl);
int				g_save_ret(char *save);
void			filter_bis(t_lst *lst, t_var fd, char **argument, char ***env);
void			free_filter(char **argument, t_var fd, t_lst *lst);
int				filter2(t_var fd, char **argument, t_lst *lst, char ***env);
void			replace_pipe(char **flag);
int				check_error_main(char *line);
int				filter_comp(char *str, size_t len, char *argument);
int				inception_return(void);
int				need_line_chev(char **arg, int i);
int				check_new_line(char **arg, int i);
int				check_pipe_main(char *line);
int				skip(char *line, int *i);
char			*del_quote(char *str);
void			exit_trois_un(int i, char **flags, char *my_path, int bl);
void			chev_r_line(char **arg, int *i, t_var *fd, int n);
int				ft_env_help(char **arg, int *i, int *n);
void			ft_env_helpbis(char **arg, int i, int *n, char **env);

#endif

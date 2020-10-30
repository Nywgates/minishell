/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:24:44 by user42            #+#    #+#             */
/*   Updated: 2020/10/30 16:45:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_built_in(char *str)
{
	if (!ft_strncmp(str, "echo", 4) && ft_strlen(str) == 4)
		return (1);
	else if (!ft_strncmp(str, "pwd", 3) && ft_strlen(str) == 3)
		return (1);
	else if (!ft_strncmp(str, "env", 3) && ft_strlen(str) == 3)
		return (1);
	else if (!ft_strncmp(str, "export", 6) && ft_strlen(str) == 6)
		return (1);
	else if (!ft_strncmp(str, "exit", 4) && ft_strlen(str) == 4)
		return (1);
	else if (!ft_strncmp(str, "cd", 2) && ft_strlen(str) == 2)
		return (1);
	else if (!ft_strncmp(str, "unset", 5) && ft_strlen(str) == 5)
		return (1);
	else
		return (0);
}

void	ft_wait_pid(t_fils *fiston, char *name)
{
	int		status;
	t_fils	*tmp;

	tmp = fiston;
	while (fiston)
	{
		waitpid(fiston->pid, &status, 0);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(fiston->pid, &status, 0);
		if (WIFEXITED(status) && !check_built_in(name))
		{
			if (!g_err)
				g_stt = WEXITSTATUS(status);
		}
		fiston = fiston->next;
	}
	fiston = tmp;
}

int		comp_len(char *str, size_t l, t_lst *lst)
{
	return (!ft_strncmp(lst->maillon, str, l)
		&& ft_strlen(lst->maillon) == l);
}

int		built_in(t_lst *lst, t_var var, char *my_path, char **flags)
{
	if (!ft_strncmp(lst->maillon, "echo", 4) && ft_strlen(lst->maillon) == 4)
	{
		print_echo(lst, var);
		if (var.fd_out[var.pos] != 1)
			close(var.fd_out[var.pos]);
		return (1);
	}
	else if (comp_len("unset", 5, lst))
		return (1);
	else if (comp_len("pwd", 3, lst))
		return (print_path(var.fd_out[var.pos]));
	else if (comp_len("env", 3, lst))
		return (print_env(var.fd_out[var.pos], &var.env));
	else if (comp_len("export", 6, lst))
		return (print_export(lst, var.fd_out[var.pos], &var.env));
	else if (comp_len("exit", 4, lst))
		return (ft_exit(lst, my_path, flags));
	else if (comp_len("cd", 2, lst))
		return (print_cd(lst));
	else
		return (0);
}

void	exec_fils(t_lst *lst, char *my_path, char **flags, t_var var)
{
	if (lst->pipe)
	{
		dup2(var.fdright[1], 1);
		close(var.fdright[0]);
		close(var.fdright[1]);
	}
	if (var.first > 1)
	{
		dup2(var.fdleft[0], 0);
		close(var.fdleft[0]);
		close(var.fdleft[1]);
	}
	if (!check_built_in(lst->maillon) && var.fd_out[var.pos] != 1)
		dup2(var.fd_out[var.pos], 1);
	if (g_err)
		exit_trois_un(0, flags, my_path, 1);
	if (built_in(lst, var, my_path, flags))
		return ;
	else if (my_path && execve(my_path, flags, var.env) == -1)
	{
		perror("execve\n");
		exit_trois_un(0, flags, my_path, 0);
	}
}

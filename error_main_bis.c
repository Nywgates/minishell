/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_main_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 09:51:14 by user42            #+#    #+#             */
/*   Updated: 2020/10/20 09:52:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error_token(char *line)
{
	write(1, "bash: syntax error near unexpected token ';'\n", 46);
	g_stt = 2;
	write(1, "minishell>", 11);
	free(line);
	return (0);
}

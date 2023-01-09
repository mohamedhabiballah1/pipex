/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:24:43 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/01/09 14:59:38 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

char	*ft_path(char **env)
{
	while (env)
	{
		if (ft_strncmp("PATH=", *env, 5) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

char	*ft_access(char **paths, char **cmd)
{
	char	*str;
	char	*str1;
	int		i;

	i = 0;
	while (paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		str1 = ft_strjoin(str, *cmd);
		free(str);
		if (access(str1, F_OK) == 0)
			return (str1);
		free(str1);
		i++;
	}
	return (NULL);
}

void	ft_child(t_list p, char *cmd, char **env)
{
	dup2(p.end[0], 0);
	close(p.end[1]);
	p.childcmd = ft_split(cmd, ' ');
	p.child_path = ft_access(p.paths, p.childcmd);
	if (!p.child_path)
	{
		ft_freestr(p.childcmd);
		ft_freestr(p.paths);
		write(2, "command not found", 17);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (execve(p.child_path, p.childcmd, env) < 0)
		{
			free(p.child_path);
			ft_freestr(p.childcmd);
			write(2, "Exec error", 10);
			exit(EXIT_FAILURE);
		}
		free(p.child_path);
		ft_freestr(p.childcmd);
	}
}

void	ft_parent(t_list p, char *cmd, char **env)
{
	dup2(p.end[1], 1);
	close(p.end[0]);
	p.parentcmd = ft_split(cmd, ' ');
	p.parent_path = ft_access(p.paths, p.parentcmd);
	if (!p.parent_path)
	{
		ft_freestr(p.parentcmd);
		ft_freestr(p.paths);
		write(2, "command not found", 17);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (execve(p.parent_path, p.parentcmd, env) < 0)
		{
			free(p.parent_path);
			ft_freestr(p.parentcmd);
			write(2, "Exec error", 10);
			exit(EXIT_FAILURE);
		}
		free(p.parent_path);
		ft_freestr(p.parentcmd);
	}
}

void	ft_freestr(char **str)
{
	int	j;

	j = 0;
	while (str[j] != NULL)
		free(str[j++]);
	free(str);
}

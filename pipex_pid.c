/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:24:43 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/01/11 13:52:51 by mhabib-a         ###   ########.fr       */
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

void	ft_child2(t_list p, char *cmd, char **env)
{
	dup2(p.end[0], 0);
	close(p.end[1]);
	p.child2cmd = ft_split(cmd, ' ');
	p.child2_path = ft_access(p.paths, p.child2cmd);
	if (!p.child2_path)
	{
		ft_freestr(p.child2cmd);
		ft_freestr(p.paths);
		write(2, "command not found", 17);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (execve(p.child2_path, p.child2cmd, env) < 0)
		{
			free(p.child2_path);
			ft_freestr(p.child2cmd);
			write(2, "Exec error", 10);
			exit(EXIT_FAILURE);
		}
		free(p.child2_path);
		ft_freestr(p.child2cmd);
		exit(EXIT_SUCCESS);
	}
}

void	ft_child1(t_list p, char *cmd, char **env)
{
	dup2(p.end[1], 1);
	close(p.end[0]);
	p.child1cmd = ft_split(cmd, ' ');
	p.child1_path = ft_access(p.paths, p.child1cmd);
	if (!p.child1_path)
	{
		ft_freestr(p.child1cmd);
		ft_freestr(p.paths);
		write(2, "command not found", 17);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (execve(p.child1_path, p.child1cmd, env) < 0)
		{
			free(p.child1_path);
			ft_freestr(p.child1cmd);
			write(2, "Exec error", 10);
			exit(EXIT_FAILURE);
		}
		free(p.child1_path);
		ft_freestr(p.child1cmd);
		exit(EXIT_SUCCESS);
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

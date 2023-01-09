/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:33:08 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/01/09 15:05:03 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	ft_pipex(t_list point, char **argv, char **env)
{
	if (pipe(point.end) < 0)
	{
		write(2, "pipe error", 11);
		exit(EXIT_FAILURE);
	}
	point.pid = fork();
	if (point.pid < 0)
	{
		write(2, "Procces PID less than 0", 23);
		perror("Procces Error");
		exit(EXIT_FAILURE);
	}
	else if (point.pid > 0)
		ft_parent(point, argv[2], env);
	else if (point.pid == 0)
		ft_child(point, argv[3], env);
	waitpid(point.pid, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_list	point;

	if (argc == 5)
	{
		point.fd_in = open(argv[1], O_RDONLY);
		point.fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
		if (point.fd_in < 0 || point.fd_out < 0)
		{
			write(2, "FD Error", 9);
			exit(EXIT_FAILURE);
		}
		dup2(point.fd_in, 0);
		dup2(point.fd_out, 1);
		point.first_path = ft_path(env);
		point.paths = ft_split(point.first_path, ':');
		ft_pipex(point, argv, env);
		ft_freestr(point.paths);
	}
	else
	{
		write(2, "Invalid number of argument", 26);
		exit(EXIT_FAILURE);
	}
	return (0);
}

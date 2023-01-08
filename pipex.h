/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:35:34 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/01/08 16:31:39 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<string.h>
# include<sys/wait.h>
# include<sys/types.h>
# include<fcntl.h>

typedef struct pipex
{
	char	*first_path;
	char	**paths;
	char	**parentcmd;
	char	**childcmd;
	char	*parent_path;
	char	*child_path;
	int		fd_out;
	int		fd_in;
	int		end[2];
	int		j;
	pid_t	pid;
	pid_t	pid1;
}	t_list;

char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_access(char **paths, char **cmd);
void	ft_child(t_list p, char *cmd, char **env);
void	ft_parent(t_list p, char *cmd, char **env);
char	*ft_path(char **env);
void	ft_freestr(char **str);

#endif

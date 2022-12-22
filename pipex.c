/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:33:08 by mhabib-a          #+#    #+#             */
/*   Updated: 2022/12/21 17:50:54 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

char    *ft_path(char **env)
{
    while(env)
    {
        if(ft_strncmp("PATH=", *env, 5) == 0)
            return(*env+5);
        env++;
    }
    return(NULL);
}

char    *ft_access(char **paths, char **cmd)
{
    char    *str, *str1;
    int i = 0;

    while(paths[i])
    {
        str = ft_strjoin(paths[i], "/");
        str1 = ft_strjoin(str, cmd[0]);
        free(str);
        if (access(str1, F_OK) == 0)
            return(str1);
        free(str1);
        i++;
    }
    return (NULL);
}

int main(int argc, char **argv, char **env)
{
    char *first_path, **paths, **cmdargs, *sec_path;
    int fd_in, fd_out;
    
    fd_in = open(argv[1], O_RDONLY);
    fd_out = open(argv[3], O_CREAT | O_RDWR | O_TRUNC, 0664);
    dup2(fd_in, 0);
    dup2(fd_out, 1);
    first_path = ft_path(env);
    paths = ft_split(first_path, ':');
    cmdargs = ft_split(argv[2], ' ');
    sec_path = ft_access(paths, cmdargs);
    execve(sec_path, cmdargs, env);
}
    /*int fd_in;
    int fd_out;
    char *first_path;
    char **paths;
    char **cmdargs;
    char *sec_path;
    
    fd_in = open(argv[1], O_RDONLY);
    fd_out = open(argv[3], O_CREAT | O_RDWR | O_TRUNC, 0664);
    dup2(fd_in, 0);
    dup2(fd_out, 1);
    first_path = ft_path(env);
    paths = ft_split(first_path, ':');
    cmdargs = ft_split(argv[2], ' ');
    sec_path = ft_access(paths, cmdargs);
    execve(sec_path, cmdargs, env); */
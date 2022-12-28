/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:33:08 by mhabib-a          #+#    #+#             */
/*   Updated: 2022/12/28 11:16:57 by mhabib-a         ###   ########.fr       */
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
        str1 = ft_strjoin(str, *cmd);
        free(str);
        if (access(str1, F_OK) == 0)
            return(str1);
        free(str1);
        i++;
    }
    write(2, "No such file or directory", 26);
    return (NULL);
}

void    ft_child(t_list p, char *cmd, char **env)
{
    dup2(p.end[1], 1);
    close(p.end[0]);
    p.childcmd = ft_split(cmd, ' ');
    p.child_path = ft_access(p.paths, p.childcmd);
    execve(p.child_path, p.childcmd, env);
}

void    ft_parent(t_list p, char *cmd, char **env)
{
    dup2(p.end[0], 0);
    close(p.end[1]);
    p.parentcmd = ft_split(cmd, ' ');
    p.parent_path = ft_access(p.paths, p.parentcmd);
    execve(p.child_path, p.childcmd, env);
}

void    ft_pipex(char **argv, char **env)
{
    t_list point;
     
    point.fd_in = open(argv[1], O_CREAT | O_RDWR);
    point.fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC , 0664);
    if (point.fd_in < 0 || point.fd_out < 0)
        write(2, "FD Error", 9);
    dup2(point.fd_in, 0);
    dup2(point.fd_out, 1);
    point.first_path = ft_path(env);
    point.paths = ft_split(point.first_path, ':');
    pipe(point.end);
    point.pid = fork();
    if (point.pid < 0)
        perror("Error");
    else if (point.pid > 0)
        ft_parent(point, argv[3], env);   
    else if (point.pid == 0)
        ft_child(point, argv[2], env);
    waitpid(point.pid, NULL ,0);
}

int main(int argc, char **argv, char **env)
{
    
    if (argc == 5 )
        ft_pipex(argv, env);
    else
        write(2, "Invalid number of argument", 27);
}


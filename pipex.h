/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:35:34 by mhabib-a          #+#    #+#             */
/*   Updated: 2022/12/27 11:49:10 by mhabib-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

#define PIPEX_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>

typedef struct pipex
{
    char *first_path; //
    char **paths; // 
    char **parentcmd;
    char **childcmd; //
    char *parent_path;
    char *child_path; //
    int fd_out; //
    int fd_in; // 
    int end[2]; //
    pid_t pid; //
    pid_t pid1; //
}               t_list;

typedef struct bonus
{
    int fd_in;
    int fd_out;
    char *path;
    char **paths;
    char **cmds;
    int nmbcmds;
    int nmbpipes;
    char *command;
    int end[1];
    pid_t   pid;
}       t_bonus;

char	**ft_split(char const *s, char c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char    *ft_access(char **paths, char **cmd);
#endif
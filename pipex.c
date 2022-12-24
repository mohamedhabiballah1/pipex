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
void    ft_child(t_list p, char *cmd, char **env)
{
    dup2(p.end[1], 1);
    close(p.end[0]);
    p.cmdargs = ft_split(cmd, ' ');
    p.sec_path = ft_access(p.paths, p.cmdargs);
    execve(p.sec_path, p.cmdargs, env);
}

void    ft_parent(t_list p, char *cmd, char **env)
{
    dup2(p.end[0], 0);
    close(p.end[1]);

    p.cmdargs = ft_split(cmd, ' ');
    p.sec_path = ft_access(p.paths, p.cmdargs);
    execve(p.sec_path, p.cmdargs, env);
}
int main(int argc, char **argv, char **env)
{
    t_list  point;
    
    point.fd_in = open(argv[1], O_CREAT | O_RDWR);
    point.fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC , 0664);
    dup2(point.fd_in, 0);
    dup2(point.fd_out, 1);
    pipe(point.end);
    point.pid = fork();

    point.first_path = ft_path(env);
    point.paths = ft_split(point.first_path, ':');

    if (point.pid < 0)
        perror("Error");
    else if (point.pid > 0)
        ft_parent(point, argv[2], env);
    else if (point.pid == 0)
        ft_child(point, argv[3], env);
    
    waitpid(point.pid, NULL, 0);
}
    /*point.fd_in = open(argv[1], O_RDONLY);
    point.fd_out = open(argv[3], O_CREAT | O_RDWR | O_TRUNC, 0664);
    dup2(point.fd_in, 0);
    dup2(point.fd_out, 1);
    point.first_path = ft_path(env);
    point.paths = ft_split(point.first_path, ':');
    point.cmdargs = ft_split(argv[2], ' ');
    point.sec_path = ft_access(point.paths, point.cmdargs);
    execve(point.sec_path, point.cmdargs, env);
    __________________________________________________________________
    int fd_in;
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
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
    //write(2, "No such file or directory", 26);
    return (NULL);
}

int     ft_cmds(char **av)
{
    int i = 0;
    while(av[i] != NULL)
        i++;
    i -= 3;
    return(i);
}

int     ft_pipes(int i)
{
    i *= 2;
    return(i);
}

void    ft_exec(t_bonus p, char *av, char **env)
{
    p.cmds = ft_split(av, ' ');
    p.command = ft_access(p.paths, p.cmds);
    execve(p.command, p.cmds, env);
}

void    ft_dup(int in, int out)
{
    dup2(in, 0);
    dup2(out, 1);
}

void    ft_pipex(int ac, char **av, char **env)
{
    t_bonus p;
    p.path = ft_path(env);
    p.paths = ft_split(p.path, ':');
    p.nmbcmds = ft_cmds(av);
    p.nmbpipes = ft_pipes(p.nmbcmds);
    int i = 2;
    int end[p.nmbcmds * 2];
    pipe(end);
    int j = 0;
    while (av[i] >= av[ac - 3])
    {
        p.pid = fork();
        if (p.pid >= 0)
        {
            if(j != 0){
                if(dup2(end[(j-1) * 2], 0) < 0)
                    perror(" dup2");
                if (av[i + 1] != av[ac - 3])
                {
                    if(dup2(end[j * 2 + 1], 1) < 0){
                        perror("dup2");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            ft_exec(p, av[i], env);
        }
        i++;
    }
    for(i = 0; i < 2 * p.nmbcmds; i++){
        close(end[i]);
    }
}

int main(int ac, char **av, char **env)
{
    t_bonus p;

    p.fd_in = open(av[1], O_RDWR);
    p.fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0664);

    dup2(p.fd_in, 0);
    dup2(p.fd_out, 1);
    ft_pipex(ac, av, env);
}
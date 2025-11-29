<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:52:05 by aawad             #+#    #+#             */
/*   Updated: 2025/11/24 14:18:58 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*get_env_value(const char *name, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = strlen(name);
	while (envp[i])
	{
		if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

static char	*build_full_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

static void	exec_child_process(t_cmd *cmd, char ***envp)
{
	char	*path;

	if (handle_redirections(cmd->redirections) < 0)
		exit(1);
	path = find_path(cmd->args[0], *envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	execve(path, cmd->args, *envp);
	perror("execve");
	free(path);
	exit(126);
=======
// pipe == 0 -> child process
// pipe<0 ->  error process
// pipe > 0 -> parent process

// t_cmd->args = {"ls", "-l", NULL};
// t_cmd->redirections = NULL;
// t_cmd->next = NULL;

#include "minishell.h"


void free_split(char **split)
{
    int i = 0;

    if (!split)
        return;

    while (split[i])
    {
        free(split[i]); 
        i++;
    }
    free(split);
}


char *get_env_value(const char *name, char **envp)
{
    int i = 0;
    size_t len = strlen(name);

    while (envp[i])
    {

        if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
        {
        
            return strdup(envp[i] + len + 1);
        }
        i++;
    }
    return NULL; 
}
char *find_path(char *cmd, char **envp)
{
    int i = 0;


    if (ft_strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return ft_strdup(cmd); 
        return NULL;
    }
    char *path_env = get_env_value("PATH", envp);
    if (!path_env)
        return NULL;

    char **paths = ft_split(path_env, ':');
    if (!paths)
        return NULL;

    while (paths[i])
    {
        char *tmp = ft_strjoin(paths[i], "/");
        char *full_path = ft_strjoin(tmp, cmd);
        free(tmp);

        if (access(full_path, X_OK) == 0)
        {
            free_split(paths); 
            return full_path;  
        }
        free(full_path);
        i++;
    }

    free_split(paths);
    return NULL; // not found
}

void execute_single_command(t_cmd *cmd, char ***envp)
{


if (built_in(cmd->args[0]))
{
    // Save original stdin/stdout
    int *saved_fds = save_std_fds();
    if (!saved_fds)
        return; // handle error

    // Apply redirections temporarily
    if (handle_redirections(cmd->redirections) == 0)
        execute_builtin(cmd, envp); // run the builtin

    restore_std_fds(saved_fds);

    return; 
}

  
    pid_t pid = fork();

    if (pid == 0)
    {
        if (handle_redirections(cmd->redirections) < 0)
            exit(1);

        char *path = find_path(cmd->args[0], envp);
        if (!path)
        {
            printf("minishell: %s: command not found\n", cmd->args[0]);
            exit(127);
        }

        execve(path, cmd->args, envp);
        perror("execve");
        free(path);
        exit(1);
    }
    else if (pid > 0)
    {/*
 * Save original stdin and stdout
 * Used when executing built-ins with redirections in parent process
 * Returns: array of 2 file descriptors [stdin_backup, stdout_backup]
 */
        int status;
        waitpid(pid, &status, 0);
    }
    else
    {
        perror("fork"); 
    }
>>>>>>> eee43455382b4f5868def40d6323bf9575792024
}

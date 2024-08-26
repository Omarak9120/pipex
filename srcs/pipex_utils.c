/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:18:22 by oabdelka          #+#    #+#             */
/*   Updated: 2024/08/26 19:08:20 by oabdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void free_split(char **strs)
{
    int i = 0;

    while (strs[i])
    {
        free(strs[i]);
        i++;
    }
    free(strs);
}
/* Function that will look for the path line inside the environment, will
 split and test each command path and then return the right one. */
/*if (ft_strchr(cmd, '/'))
		return (cmd);*/
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
        if (access(path, F_OK) == 0)
            return (free_split(paths), path);
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

/* A simple error displaying function. */
void	error(void)
{
	printf("Error Occured!\n");
	exit(EXIT_FAILURE);
}

/* Function that take the command and send it to find_path
 before executing it. */
void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		printf("error\n");
		return ;
	}
	 if (!*cmd)
		return (printf("error"),free(cmd));
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
	free_split(cmd);
}

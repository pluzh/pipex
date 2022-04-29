/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmichel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:56:20 by lmichel           #+#    #+#             */
/*   Updated: 2021/12/08 13:56:22 by lmichel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_access(char *name, int is_input)
{
	if (is_input && access(name, R_OK))
	{
		write(1, "pipex: permission denied: ", 26);
		write(1, name, ft_strlen(name));
		write(1, "\n", 1);
		return (0);
	}
	else if (!is_input && access(name, W_OK))
	{
		write(1, "pipex: permission denied: ", 26);
		write(1, name, ft_strlen(name));
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}

int	check_file(char *name, int is_input)
{
	int	fd;

	if (is_input)
	{
		fd = open(name, O_RDONLY);
		if (access(name, F_OK))
		{
			write(1, "pipex: no such file or directory: ", 34);
			write(1, name, ft_strlen(name));
			write(1, "\n", 1);
			return (-1);
		}
		if (!check_access(name, 1))
			return (-1);
	}
	else
	{
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (!check_access(name, 0))
			return (-1);
	}
	return (fd);
}

void	execute(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	path = get_path(args[0], envp);
	execve(path, args, envp);
	write(2, "pipex: command not found: ", 26);
	write(2, path, ft_strlen(path));
	write(2, "\n", 1);
}

void	ft_start(char **argv, char **envp)
{
	int		end[2];
	pid_t	proc;

	pipe(end);
	proc = fork();
	if (proc < 0)
		return (perror("Fork: "));
	if (!proc)
	{
		dup2(end[1], STDOUT_FILENO);
		close(end[0]);
		execute(argv[2], envp);
		exit(1);
	}
	else
	{
		waitpid(-1, 0, 0);
		dup2(end[0], STDIN_FILENO);
		close(end[1]);
		execute(argv[3], envp);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;

	if (argc != 5)
	{
		write(1, "pipex: there should be 4 arguments\n", 35);
		return (1);
	}
	fd1 = check_file(argv[1], 1);
	fd2 = check_file(argv[4], 0);
	if (fd1 == -1 || fd2 == -1)
		exit(1);
	dup2(fd1, 0);
	dup2(fd2, 1);
	ft_start(argv, envp);
	close(fd1);
	close(fd2);
}

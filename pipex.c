/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:05:24 by ajeannin          #+#    #+#             */
/*   Updated: 2023/04/21 18:54:17 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex"

static int	init_struct(t_pipex *pipex, int ac, char **av)
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile < 0)
		return (msg(ERR_INFILE));
	pipex->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->outfile < 0)
		return (msg(ERR_OUTFILE));
	if (pipe(pipex->pipe) < 0)
		return (msg(ERR_PIPE));
	pipex->paths = find_path(env);
	pipex->cmd_paths = ft_split(pipex->paths, ':');
	return 0;
}

int	main(int ac, char **av, char **env)
{
	t_pipex pipex;

	if (ac != 5)
		return (msg(ERR_INPUT));
/*	
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile < 0)
		msg(ERR_INFILE);
	pipex.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.outfile < 0)
		msg(ERR_OUFILE);
	if (pipe(pipex.pipe) < 0)
		msg(ERR_PIPE);
	pipex.paths = find_path(env);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
*/
	init_struct(pipex, ac, av);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, av, env);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, av, env);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_parent(&pipex);
	return (0);
}

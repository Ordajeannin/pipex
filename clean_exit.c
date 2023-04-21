/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:18:00 by ajeannin          #+#    #+#             */
/*   Updated: 2023/04/21 19:13:04 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex"

void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = -1;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->cmd_paths[++i])
		free(pipex->cmd_paths[i]);
	free(pipex->cmd_paths);
}

void	free_children(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (pipex->cmd_args[++i])
		free(pipex->cmd_args[i]);
	free(pipex->cmd_args);
	free(pipex->cmd);
}

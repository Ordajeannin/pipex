/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_work.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:26:43 by ajeannin          #+#    #+#             */
/*   Updated: 2023/04/21 18:57:42 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex"

/*
 * 1.
 * Fait en sorte que l'input de la premiere commande soit l'infile
 * -> entree standart = infile
 * Fait en sorte que l'output de cette meme commande soit l'input de la 2nd
 * -> output = sortie du pipe
 * Ferme l'entree du pipe, par principe
 * -> close pipe[0]
 *
 * 2.
 * Verifie si la commande a des arguments
 * Extrait le path vers cette commande dans l'environnement donne
 * Si celui ci existe, alors execution de la commande,
 * Sinon, free et message d'erreur
*/
void	first_child(t_pipex pipex, char **av, char **env)
{
//	dup2(pipex.pipe[1], 1);
//	close(pipex.pipe[0]);
	dup2(pipex.infile, 0);
	dup2(pipex.pipe[1], 1);
	close(pipex.pipe[0]);
	pipex.cmd_args = ft_split(av[2], ' ');
	pipex.cmd = extract_cmd_path(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_children(&pipex);
		msg(ERR_CMD);
	}
	execve(pipex.cmd, pipex.cmd_args, env);
}

/*
 * 1. ~ Idem
 * Fait en sorte que l'input de la deuxieme commande soit l'output de la 1er
 * -> entree standart = pipe[0]
 * Fait en sorte que l'output de cette meme commande soit ecrit sur l'outfile
 * -> output = outfile
 * Ferme la sortie du pipe, par principe
 * -> close pipe[1]
 *
 *  2. Similaire en tout point, si ce n'est av[3] et non av[2]
*/
void	second_child(t_pipex pipex, char **av, char **env)
{
	dup2(pipex.pipe[0], 0);
//	close(pipex.pipe[1]);
	dup2(pipex.outfile, 1);
	close(pipex.pipe[1]);
	pipex.cmd_args = ft_split(av[3], ' ');
	pipex.cmd = extract_cmd_path(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		free_children(&pipex);
		msg(ERR_CMD);
	}
	execve(pipex.cmd, pipex.cmd_args, env);
}

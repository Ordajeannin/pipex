/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:45:32 by ajeannin          #+#    #+#             */
/*   Updated: 2023/04/21 19:13:39 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "to few/to much args"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	int		pipe[2];
	char	*paths;
	char	*cmd;
	char	**cmd_paths;
	char	**cmd_args;
}	t_pipex;


void	close_pipes(t_pipex *pipex);
char	*extract_cmd_path(char **paths, char *cmd);
char	*find_path(char **env);
void	first_child(t_pipex pipex, char **av, char **env);
void	free_children(t_pipex *pipex);
void	free_parent(t_pipex *pipex);
int		msg(char *msg);
void	second_child(t_pipex pipex, char **av, char **env);

#endif

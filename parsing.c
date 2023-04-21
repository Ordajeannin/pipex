/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:02:41 by ajeannin          #+#    #+#             */
/*   Updated: 2023/04/21 17:24:31 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Recherche si la commande est accessible a partir des paths fournis.
 * Temp va permettre de tester chaque path individuellement.
 * Au premier concluant, la fct renvoie le path complet.
 * si aucun path n'est concluant, renvoie NULL
*/
char	*extract_cmd_path(char **paths, char *cmd)
{
	char	*temp;
	char	*command;

	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

/*
 * Recherche de la variable d'environnement "PATH"... en comparant
 * les quatres premiers caracteres de chaque chaine avec "PATH".
 * Si la variable "PATH" est trouvee, renvoie un pointeur vers la sous-chaine
 * de *env apres les 5 premiers caracteres : "PATH=".
*/
char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

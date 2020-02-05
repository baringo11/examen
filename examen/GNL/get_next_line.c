/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:32:49 by jbaringo          #+#    #+#             */
/*   Updated: 2020/01/28 14:39:43 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		next_line(char **text, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*text)[i] != '\n' && (*text)[i] != '\0')
		i++;
	if ((*text)[i] == '\n')
	{
		*line = ft_substr(*text, 0, i);
		tmp = ft_strdup(&(*text)[i + 1]);
		free(*text);
		*text = tmp;
	}
	else
	{
		*line = ft_strdup(*text);
		free(*text);
		*text = NULL;
		return (0);
	}
	return (1);
}

int		check(int t_read, char **text, char **line)
{
	if (t_read < 0)
		return (-1);
	else if (t_read == 0 && text == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (next_line(text, line));
}

int		get_next_line(char **line)
{
	int				t_read;
	char			buff[3];
	static char		*text;
	char			*tmp;

	while ((t_read = read(0, buff, 2)) > 0)
	{
		buff[t_read] = '\0';
		if (text == NULL)
			text = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(text, buff);
			free(text);
			text = tmp;
		}
		if (ft_strchr(text, '\n'))
			break ;
	}
	return (check(t_read, &text, line));
}
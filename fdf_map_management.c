/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:51:31 by iwaslet           #+#    #+#             */
/*   Updated: 2024/01/26 12:38:34 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**manage_map(char *map, t_vars *vars)
{
	int		fd;
	char	*coord;
	char	*temp;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		mlx_error(0, vars);
	temp = ft_calloc(1, 1);
	coord = get_next_line(fd);
	while (coord)
	{
		if (coord[0] && coord[0] == '\n')
		{
			ft_free_two(temp, coord);
			mlx_error(0, vars);
		}
		temp = ft_strjoin_gnl(temp, coord);
		free(coord);
		coord = get_next_line(fd);
	}
	return(ft_fill_tab(temp, ft_create_infotab(temp)));
}

int	ft_count_lines(char *text)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (text[i])
	{
		if (text[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

t_point	**ft_fill_tab(char *lngstr, t_point **pointinfo)
{
	int		i;
	int		j;
	char	**tab;
	char	**tmp;

	i = 0;
	tab = ft_split(lngstr, '\n');
	free(lngstr);
	while (tab[i])
	{
		tmp = ft_split(tab[i], ' ');
		pointinfo[i] = malloc(sizeof(t_point) * (ft_count_columns(tmp) + 1));
		j = -1;
		while (tmp[++j])
		{
			pointinfo[i][j].value = ft_atoi(tmp[j]);
			pointinfo[i][j].rgb = "0xFFFFFF";
			if (ft_strchr(tmp[j], ','))
				pointinfo[i][j].rgb = ft_strdup(ft_strchr(tmp[j], ','));
		}
		free (tmp);
		i++;
	}
	return (pointinfo);
}

int	ft_count_columns(char **line)
{
	int		j;
	char	**temp;

	j = 0;
	temp = line;
	while (temp[j])
		j++;
	return (j);
}

t_point	**ft_create_infotab(char *longstr)
{
	t_point	**pointinfo;
	int		count;
	
	count = ft_count_lines(longstr);
	pointinfo = malloc(sizeof(t_point *) * (count + 1));

	return(pointinfo);
}

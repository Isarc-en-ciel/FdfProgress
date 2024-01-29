/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_src.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:48:00 by iwaslet           #+#    #+#             */
/*   Updated: 2024/01/26 12:21:47 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_vars	vars;
	t_data	img;
	int		fd;

	fd = 0;
	if (ac != 2)
		exit(1);
	manage_map(av[1], &vars);
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		return (mlx_error(0, &vars));
	vars.win = mlx_new_window(vars.mlx, 1080, 1080, "FDF");
	// void	*mlx_new_image(void *mlx_ptr,int width,int height); /* meme taille que la fenetre */
	// char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
	// 		   int *size_line, int *endian);
	img.img = mlx_new_image(vars.mlx,1080,1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	int i = -1;
	
	while (++i < 1080)
	{
		*(unsigned int*)img.addr = 0xFF0000;
		img.addr += (i * (img.bits_per_pixel / 8)); 
	}

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//pour dessiner: data.adresse du premier pixel + coordonnees pour chaque point
	 if (vars.win == NULL)
	 	return (mlx_error(1, &vars));
	mlx_key_hook(vars.win, &key_hook, &vars);
	mlx_hook(vars.win, CROSS, 0, &close_window, &vars);
	mlx_loop_hook(vars.mlx, &so_long, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

int so_long(t_vars *vars)
{
	(void) vars;

	return (1);
}

int	mlx_error(int type, t_vars *vars)
{
	if (type == 1)
		free(vars->win);
	return (1);
}

void	ft_free_two(char *s1, char *s2)
{
	if (s1)
		free (s1);
	if (s2)
		free (s2);
}

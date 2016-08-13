/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomeirin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 12:59:24 by jomeirin          #+#    #+#             */
/*   Updated: 2016/07/15 13:40:35 by jomeirin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
#define RTV1_H
//#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_color
{
	float		red;
	float		green;
	float		blue;
}				t_color;

typedef struct	s_materials
{
	t_color		defuse;
	float		reflection;
}				t_material;

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef struct	s_ray
{
	t_vec		origin;
	t_vec		dir;
}				t_ray;

typedef struct	s_plain
{
	t_vec		pos;
	t_vec		norm;
}				t_plain;
/*
typedef struct	s_cylinder
{
}				t_cyl;
*/
/*
typedef struct	s_cone
{
}				t_cone;
*/
typedef struct	s_lightness
{
	t_vec		light;
	t_color		intensity;
}				t_light;

typedef	struct	s_sphere
{
	t_vec		position; t_sphere s;s.position.x = atoi(strncpy(line[a], 
	float		radius;
	int			material;
}				t_sphere;

void	save_xpm(char *f_name, unsigned char *image, int width, int height);

#endif

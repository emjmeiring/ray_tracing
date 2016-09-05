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

#ifndef RT_H
#define RT_H
#include <mlx.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "get_scene.h"
#define WIDTH  640
#define HEIGHT 480
#define INF 1e8
#define M_DEPTH 5

typedef struct	s_color
{
	float		r;
	float		g;
	float		b;
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
	t_vec		position;
	float		radius;
	int			material;
}				t_sphere;

typedef struct	s_counters
{
	int			i;
	int			j;
	int			k;
	float		inv_w;
	float		inv_h;
	float		f_v;
	float		aspect_r;
	float		angle;
	float		x_dir;
	float		y_dir;
	t_color		pixel;
}				t_index;

void		set_up_num(t_index *num);
int			intersect_sphere(t_ray *r, t_object *s, float *t0, float *t1);
void		save_xpm(char *f_name, unsigned char *image, int width, int height);
float		dot_product(t_vec a, t_vec b);
t_vec		vec_subtract(t_vec a, t_vec b);
t_vec		scale_vec(float scalar, t_vec v);
t_vec		add_vec(t_vec a, t_vec b);
t_vec		cross_prod(t_vec a, t_vec b);

#endif

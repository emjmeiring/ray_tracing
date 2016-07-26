/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomeirin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 12:59:24 by jomeirin          #+#    #+#             */
/*   Updated: 2016/07/15 13:40:35 by jomeirin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
#define RTV1_H
#include <mlx.h>
#include <math.h>
#include <unistd.h>

typedef struct	color
{
	float		red;
	float		green;
	float		blue;
}				color;

typedef struct	materials
{
	color		defuse;
	float		reflection;
}				material;

typedef struct	vector
{
	float		x;
	float		y;
	float		z;
}				vec;

typedef struct	lightness
{
	vec			light;
	color		intensity;
}				light;

typedef struct	ray
{
	vec			origin;
	vec			dir;
}				ray;

typedef	struct	sphere
{
	vec			position;
	float		radius;
	int			material;
}				sphere;

void	save_xpm(char *f_name, unsigned char *image, int width, int height);

#endif

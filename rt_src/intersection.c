/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomeirin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 12:58:33 by jomeirin          #+#    #+#             */
/*   Updated: 2016/07/15 12:58:36 by jomeirin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../includes/get_scene.h"
#include <stdio.h>

int		intersect_sphere(t_ray *r, t_object *s, float *t0, float *t1)
{
	t_vec	l;
	t_vec	position;
	float	tca;
	float	thc;
	float	d2;
	
	//printf("t0: %f\nt1: %f\n", *t0, *t1);
	position = (t_vec){s->position_x, s->position_y, s->position_z};
	//printf("pos = #%f#%f#%f#\n", s->position_x, s->position_y, s->position_z);
	l = vec_subtract(position, r->origin);
	//printf("l = #%f#%f#%f#\n", l.x, l.y, l.z);
	tca = dot_product(l, r->dir);
	if (tca < 0)
	{
			//write(1, "ass!", 4);
		return (0);
	}
	d2 = dot_product(l, l) - tca * tca;
	if (d2 > s->radius_x2)
		return (0);
	thc = sqrt(s->radius_x2 - d2);
	//printf("l: %f %f %f\ndir: %f %f %f\ntca = %f\n %d\n", l.x, l.y, l.z, r->dir.x, r->dir.y, r->dir.z, tca, ++i);
	//printf("thc: %f\n", thc);
	*t0 = tca - thc;
	*t1  = tca + thc;
	//printf("fanal t0:%f\nfinal t1: %f\n", *t0, *t1);
		//write(1, "kla,", 4);
	return (1);
}
/*
int		intersect_sphere(t_ray *r, t_sphere *s, float *closest)
{
	float	A;
	float	B;
	float	C;
	float	discr;
	float	t0;
	float	t1;
	t_vec	distance;

	A = dot_product(&r->dir, &r->dir);
	distance = vec_subtract(&r->origin, &s->position);
	B = 2 * dot_product(&r->dir, &distance);
	C = dot_product(&distance, &distance) - (s->radius * s->radius);
	discr = (B * B) - (4 * A * C);
	
	if (discr < 0)
		return (0);
	else
	{
		t0 = (-B + sqrt(discr)) * 0.5;
		t1 = (-B - sqrt(discr)) * 0.5;
		if (t0 > t1)
			t0 = t1;
		if ((t0 > 0.001f) && (t0 < *closest))
		{
				//write(1, "hey", 3);
			*closest = t0;
			return (1);
		}
		else return (0);
	}
}*/
/*
int		intersecting_plain(t_ray *r, t_sphere *s, float *closest)
{

 }*/

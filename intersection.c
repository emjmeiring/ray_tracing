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

#include "rtv1.h"
#include <stdio.h>

float	dot_product(vec *a, vec *b)
{
	float result;

	result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	return (result);
}

vec	vec_subtract(vec *a, vec *b)
{
	vec result;

	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;
	return (result);
}

vec		scale_vec(float scalar, vec *v)
{
	vec result;

	result.x = v->x * scalar;
	result.y = v->y * scalar;
	result.z = v->z * scalar;
	return (result);
}

vec		add_vec(vec *a, vec *b)
{
	vec result;
	
	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	return (result);
}
int		intersect_sphere(ray *r, sphere *s, float *closest)
{
	float	A;
	float	B;
	float	C;
	float	discr;
	float	t0;
	float	t1;
	vec		distance;

	A = dot_product(&r->dir, &r->dir);
	distance = vec_subtract(&r->origin, &s->position);
	B = 2 * dot_product(&r->dir, &distance);
	C = dot_product(&distance, &distance) - (s->radius * s->radius);
	discr = (B * B) - (4 * A * C);
	
	if (discr < 0)
		return (0);
	else
	{
		t0 = (-B + sqrt(discr)) / 2;
		t1 = (-B - sqrt(discr)) / 2;
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
}

#define WIDTH  800
#define HEIGHT 600

int main(void){
	
	sphere s;
	ray r;
		//material met;
	
	int i,j;
	unsigned char img[WIDTH * HEIGHT * 3];
	int hit;
	float t;

	
	s.position.x = 200;
	s.position.y = 200;
	s.position.z = 100;
	s.radius = 100;
	
	r.dir.x = 0;
	r.dir.y = 0;
	r.dir.z = 1;
	r.origin.z = 0;
	
	
	
	for(i=0;i<HEIGHT;i++){
		r.origin.y = i;
		for(j=0;j<WIDTH;j++){
			r.origin.x = j;
			t = 2000.00f;
			hit = intersect_sphere(&r, &s, &t);
			if(hit)
			{
				img[(j + i*WIDTH)*3 + 0] = 255;
				img[(j + i*WIDTH)*3 + 1] = 10;
				img[(j + i*WIDTH)*3 + 2] = 250;
			}else
			{
				img[(j + i*WIDTH)*3 + 0] = 0;
				img[(j + i*WIDTH)*3 + 1] = 0;
				img[(j + i*WIDTH)*3 + 2] = 0;
			}
		}
			//printf("\n");
	}
	save_xpm("scene1.xpm", img, WIDTH, HEIGHT);
	return (0);
}
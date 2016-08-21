#include "../includes/rt.h"

float		dot_product(t_vec *a, t_vec *b)
{
	float result;

	result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	return (result);
}

t_vec		vec_subtract(t_vec *a, t_vec *b)
{
	t_vec result;

	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;
		//printf("1#%f#%f#%f#\n", result.x, result.y, result.z);
	return (result);
}

t_vec		scale_vec(float scalar, t_vec *v)
{
	t_vec result;

	result.x = v->x * scalar;
	result.y = v->y * scalar;
	result.z = v->z * scalar;
	return (result);
}

t_vec		add_vec(t_vec *a, t_vec *b)
{
	t_vec result;

	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	return (result);
}

void		set_up_num(t_index *num)
{
	num->i = 0;
	num->j = 0;
	num->k = 0;
	num->inv_w = (1.0f/WIDTH);
	num->inv_h = (1.0f/HEIGHT);
	num->f_v = 30;
	num->aspect_r = ((float)WIDTH/HEIGHT);
	num->angle = tanf(M_PI * 0.5f * num->f_v / 180.f);
	num->x_dir = 0;
	num->y_dir = 0;
}
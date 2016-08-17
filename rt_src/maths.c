#include "../includes/rt.h"

float	dot_product(t_vec *a, t_vec *b)
{
	float result;

	result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	return (result);
}

t_vec	vec_subtract(t_vec *a, t_vec *b)
{
	t_vec result;

	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;
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


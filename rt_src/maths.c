#include "../includes/rt.h"

float		dot_product(t_vec a, t_vec b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vec		vec_subtract(t_vec a, t_vec b)
{
	return (t_vec){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec		scale_vec(float scalar, t_vec v)
{
	return (t_vec){v.x * scalar, v.y * scalar, v.z * scalar};
}

t_vec		add_vec(t_vec a, t_vec b)
{
	return (t_vec){a.x + b.x, a.y + b.y, a.z + b.z};
}
#include "../includes/rt.h"

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

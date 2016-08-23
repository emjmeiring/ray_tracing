/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smashele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 15:34:37 by smashele          #+#    #+#             */
/*   Updated: 2016/08/21 11:51:36 by smashele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_scene.h"
#include <stdio.h>

void		pony_freedom(t_object *first)
{
	t_object	*pony;
	t_object	*unicorn;
	
	while (first->next)
	{
		pony = first;
		while (pony->next)
		{
			unicorn = pony;
			pony = pony->next;
		}
		free(pony);
		unicorn->next = NULL;
	}
	free(first);
}

int			error_handle(const char *s)
{
	int		a;
	int		this;
	int		that;
	
	this = 0;
	that = 0;
	a = -1;
	while (s[++a])
	{
		s[a] == 58 ? this++ : 0;
		s[a] == 59 ? that++ : 0;
	}
	if (s[--a] != 59 || this == 0 || that == 0)
		return (1);
	return (this - that);
}

int			save_pony(const char *s, int a, t_object *pony)
{
	while (s[a])
	{
		if (f_cmp(s, "object", a) == 0)
			return (0);
		f_cmp(s, "red", a) == 0 ? pony->red = f_atof(s, a) : 0;
		f_cmp(s, "green", a) == 0 ? pony->green = f_atof(s, a) : 0;
		f_cmp(s, "blue", a) == 0 ? pony->blue = f_atof(s, a) : 0;
		f_cmp(s, "reflection", a) == 0 ? pony->reflection = f_atof(s, a) : 0;
		f_cmp(s, "trans", a) == 0 ? pony->trans = f_atof(s, a) : 0;
		f_cmp(s, "position_x", a) == 0 ? pony->position_x = f_atof(s, a) : 0;
		f_cmp(s, "position_y", a) == 0 ? pony->position_y = f_atof(s, a) : 0;
		f_cmp(s, "position_z", a) == 0 ? pony->position_z = f_atof(s, a) : 0;
		f_cmp(s, "radius", a) == 0 ? pony->radius = f_atof(s, a) : 0;
		f_cmp(s, "radius", a) == 0 ? pony->radius_x2 = R1 * R1 : 0;
		f_cmp(s, "length_x", a) == 0 ? pony->length_x = f_atof(s, a) : 0;
		f_cmp(s, "length_y", a) == 0 ? pony->length_y = f_atof(s, a) : 0;
		f_cmp(s, "length_z", a) == 0 ? pony->length_z = f_atof(s, a) : 0;
		while (s[a] && s[a] != 59)
			a++;
		s[a] == 59 ? a++ : 0;
	}
	return (1);
}

t_object	*store_data(char *line, t_object *pony)
{
	int			a;
	int			b;
	t_object	*temp;
	
	a = -1;
	b = 0;
	if (error_handle(line) != 0)
		return (pony);
	temp = pony;
	while (line[++a])
	{
		if (f_cmp(line, "object", a) == 0)
		{
			b > 0 ? pony->next = fresh_pony() : 0;
			b > 0 ? pony = pony->next : 0;
			pony->name = unicorn_name(line, a);
			while (line[a] != 59)
				a++;
			save_pony(line, a, pony);
			b++;
		}
		while (line[a] != 59)
			a++;
	}
	return (temp);
}

t_object	*get_scene(char *name)
{
	int			a;
	int			fd;
	char		korea;
	char		*japan;
	t_object	*pony;
	
	a = 52;
	fd = open(name, O_RDONLY);
	japan = (char*)malloc(51);
	pony = fresh_pony();
	while (a > 0)
		japan[--a] = 0;
	while (read(fd, &korea, 1) > 0)
	{
		korea > 64 && korea < 91 ? korea += 32 : 0;
		korea > 32 && korea < 127 ? japan[a++] = korea : 0;
		korea > 32 && a % 50 == 0 ? japan = clone(&japan, a, 51) : 0;
	}
	pony = store_data(japan, pony);
	free(japan);
	return (pony);
}

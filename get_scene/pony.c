/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pony.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smashele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 15:43:16 by smashele          #+#    #+#             */
/*   Updated: 2016/08/21 12:21:16 by smashele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_scene.h"

t_object	*fresh_pony(void)
{
	t_object	*pony;
	
	pony = (t_object*)malloc(sizeof(t_object));
	pony->name = NULL;
	pony->red = 0;
	pony->green = 0;
	pony->blue = 0;
	pony->reflection = 0;
	pony->position_x = 0;
	pony->position_y = 0;
	pony->position_z = 0;
	pony->radius = 0;
	pony->radius_x2 = 0;
	pony->length_x = 0;
	pony->length_y = 0;
	pony->length_z = 0;
	pony->next = NULL;
	return (pony);
}

char		*clone(char **s, int count, int size)
{
	int		a;
	char	*new;
	
	a = size;
	new = (char*)malloc(count + size);
	while (--a >= 0)
		new[a] = 0;
	while (++a < count)
		new[a] = s[0][a];
	free(*s);
	return (new);
}

int			f_cmp(const char *s1, const char *s2, int a)
{
	int		b;
	int		c;
	int		d;
	
	b = 0;
	c = 0;
	d = 0;
	while (s1[a + c] && s1[a + c] != 58)
		c++;
	while (s2[d])
		d++;
	if (c == 0 || d == 0)
		return (1);
	c += a;
	while (s1[a] == s2[b] && a < c && b < d)
	{
		a++;
		b++;
	}
	c = a == c && b == d ? s1[--a] - s2[--b] : 1;
	return (c);
}

float		f_atof(const char *s, int a)
{
	float	res;
	float	dec;
	float	neg;
	int		b;
	
	res = 0;
	b = 0;
	dec = 1;
	while (s[a] && s[a] != 58)
		a++;
	s[a] == 58 ? a++ : 0;
	while (s[a] && s[a] != 45 && s[a] < 48 && s[a] > 57)
		a++;
	neg = s[a] == 45 && s[a + 1] > 47 && s[a + 1] < 58 ? -1 : 1;
	s[a] == 43 || s[a] == 45 ? a++ : 0;
	while (s[a] && s[a] > 47 && s[a] < 58)
		res = res * 10 + (s[a++] - 48);
	if (s[a] == 46)
		while (s[++a] && s[a] > 47 && s[a] < 58 && b++ < 6)
			res = res + (s[a] - 48) / (dec *= 10);
	return (res * neg);
}

char		*unicorn_name(char *s, int a)
{
	int		b;
	int		c;
	char	*mew;
	
	b = 0;
	while (s[a] && s[a] != 58)
		a++;
	if (s[a++])
	{
		c = -1;
		while (s[a + b] && s[a + b] != 59)
			b++;
		mew = (char*)malloc(sizeof(char) * (b + 1));
		while (c++ < b)
			mew[c] = 0;
		c = -1;
		while (++c < b)
			mew[c] = s[a + c];
		b > 0 && s[a] > 96 && s[a] < 123 ? mew[0] -= 32 : 0;
		return (mew);
	}
	return (NULL);
}

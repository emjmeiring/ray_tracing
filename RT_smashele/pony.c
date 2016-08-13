#include "RT.h"
#include <stdio.h>

t_object	*fresh_pony()
{
	t_object	*pony;
	char		*x;

	x = (char*)malloc(5);
	x = "none\0";
	pony = (t_object*)malloc(sizeof(t_object));
	pony->NAME = x;
	pony->RED = 0;
	pony->GREEN = 0;
	pony->BLUE = 0;
	pony->REF = 0;
	pony->POS_X = 0;
	pony->POS_Y = 0;
	pony->POS_Z = 0;
	pony->RAD = 0;
	pony->LEN_X = 0;
	pony->LEN_Y = 0;
	pony->LEN_Z = 0;
	pony->next = NULL;
	return (pony);
}

char	*clone(char **s, int count, int size)
{
	int	a;
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

int	f_cmp(const char *s1, const char *s2, int a)
{
	int	b;
	int	c;
	int	d;

	b = 0;
	c = 0;
	d = 0;
	while (s1[a + c] && s1[a + c] != ':')
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
	if (a == c && b == d)
		return (s1[--a] - s2[--b]);
	else
		return (1);
}

float	f_atof(const char *s, int a)
{
	float	res;
	float	dec;
	int	neg;
	int	b;

	res = 0;
	b = 0;
	dec = 1;
	while (s[a] && s[a] != D1)
		a++;
	s[a] == D1 ? a++ : 0;
	while (s[a] && s[a] != 45 && s[a] < 48 && s[a] > 57)
		a++;
	neg = s[a] == 45 && s[a + 1] > 47 && s[a + 1] < 58 ? -1 : 1;
	s[a] == 43 || s[a] == 45 ? a++ : 0;
	while (s[a] && s[a] > 47 && s[a] < 59)
		res = res * 10 + (s[a++] - 48);
	if (s[a] == '.')
		while (s[++a] && s[a] > 47 && s[a] < 58 && b++ < 6)
			res = res + (s[a] - 48) / (dec *= 10);
	return (res * neg);
}

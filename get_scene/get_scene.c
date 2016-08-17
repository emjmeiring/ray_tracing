#include "../includes/get_scene.h"

int	error_handle(const char *s)
{
	int	a;
	int	this;
	int	that;

	this = 0;
	that = 0;
	a = -1;
	while (s[++a])
	{
		s[a] == D1 ? this++ : 0;
		s[a] == D2 ? that++ : 0;
	}
	if (s[--a] != D2 || this == 0 || that == 0)
		return (1);
	return (this - that);
}

void	save_pony(const char *s, int a, t_object *pony)
{
	while (s[a])
	{
		if (f_cmp(s, "object", a) == 0)
			return;
		f_cmp(s, "red", a) == 0? pony->RED = f_atof(s, a) : 0;
		f_cmp(s, "green", a) == 0? pony->GREEN = f_atof(s, a) : 0;
		f_cmp(s, "blue", a) == 0? pony->BLUE = f_atof(s, a) : 0;
		f_cmp(s, "reflection", a) == 0? pony->REF = f_atof(s, a) : 0;
		f_cmp(s, "position_x", a) == 0? pony->POS_X = f_atof(s, a) : 0;
		f_cmp(s, "position_y", a) == 0? pony->POS_Y = f_atof(s, a) : 0;
		f_cmp(s, "position_z", a) == 0? pony->POS_Z = f_atof(s, a) : 0;
		f_cmp(s, "radius", a) == 0? pony->RAD = f_atof(s, a) : 0;
		f_cmp(s, "length_x", a) == 0? pony->LEN_X = f_atof(s, a) : 0;
		f_cmp(s, "length_y", a) == 0? pony->LEN_Y = f_atof(s, a) : 0;
		f_cmp(s, "length_z", a) == 0? pony->LEN_Z = f_atof(s, a) : 0;
		while (s[a] && s[a] != ';')
			a++;
		s[a] == ';' ? a++ : 0;
	}
}

int	store_data(char *line, t_object *pony)
{
	int		a;
	int		b;

	a = -1;
	b = 0;
	if (error_handle(line) != 0)
		return (0);
	while (line[++a])
	{
		if (f_cmp(line, "object", a) == 0)
		{
			b > 0 ? pony->next = fresh_pony() : 0;
			b > 0 ? pony = pony->next : 0;
			pony->NAME = unicorn_name(line, a);
			while (line[a] != ';')
				a++;
			save_pony(line, a, pony);
			b++;
		}
		while (line[a] != ';')
			a++;
	}
	return (1);
}

t_object	*get_scene(char *name)
{
	int		a;
	int		fd;
	char		korea;
	char		*japan;
	t_object	*pony;
	t_object	*temp;

	a = 51;
	fd = open(name, O_RDONLY);
	japan = (char*)malloc(51);
	pony = fresh_pony();
	temp = pony;
	while (a > 0)
		japan[--a] = 0;
	while (fd != -1 && read(fd, &korea, 1) > 0)
	{
		korea > 64 && korea < 91 ? korea += 32 : 0;
		korea > 32 ? japan[a++] = korea : 0;
		korea > 32 && a % 50 == 0 ? japan = clone(&japan, a, 51) : 0;
	}
	store_data(japan, pony);
	return (temp);
}

#include "RT.h"
#include <stdio.h>

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

int	store_data(const char *line, t_object *pony)
{
	int		a;
	int		b;

	a = -1;
	b = 0;
	while (line[++a])
	{
		if (f_cmp(line, "object", a) == 0)
		{
			b > 0 ? pony->next = fresh_pony() : 0;
			b > 0 ? pony = pony->next : 0;
			while (line[a] != ';')
				a++;
			save_pony(line, a, pony);
			b++;
		}
		while (line[a] != ';')
			a++;
	}
	return (0);
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

int	main(int argc, char **argv)
{
	int		a;
	t_object	*pony;

	a = 0;
	while (argv[++a])
	{
		pony = get_scene(argv[1]);
		while (pony)
		{
			printf("%s - name:		%s\n", argv[1], pony->NAME);
			printf("%s - red:		%f\n" , argv[1], pony->RED);
			printf("%s - green:		%f\n" , argv[1], pony->GREEN);
			printf("%s - blue:		%f\n" , argv[1], pony->BLUE);
			printf("%s - reflection:	%f\n" , argv[1], pony->REF);
			printf("%s - position_x:	%f\n" , argv[1], pony->POS_X);
			printf("%s - position_y:	%f\n" , argv[1], pony->POS_Y);
			printf("%s - position_z:	%f\n" , argv[1], pony->POS_Z);
			printf("%s - radius:		%f\n" , argv[1], pony->RAD);
			printf("%s - length_x:	%f\n" , argv[1], pony->LEN_X);
			printf("%s - length_y:	%f\n" , argv[1], pony->LEN_Y);
			printf("%s - length_z:	%f\n\n" , argv[1], pony->LEN_Z);
			pony = pony->next;
		}
	}
	return (2000);
}

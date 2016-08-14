#include "RT.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		a;
	t_object	*pony;

	a = 0;
	while (argv[++a])
	{
		pony = get_scene(argv[a]);
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

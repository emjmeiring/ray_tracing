#include "includes/rt.h"
#include "includes/get_scene.h"

float	length2(t_vec *r)
{
	float x;

	x = r->x * r->x + r->y * r->y + r->z * r->z;
	return (x);
}

t_vec	normalize(t_vec *r)
{
	float	len;
	float	bla;
	t_vec	dir;

	bla = dot_product(*r,*r);
	if (bla > 0)
	{
		len = 1.0f / sqrt(bla);
		//printf("1x=%f==\n", r->dir.x);
			//printf("1y=%f==\n", r->dir.y);
			//printf("1z=%f==\n", r->dir.z);
			//printf("1len		%f\n", sqrt(length2(r)));
		dir = scale_vec(len, *r);
		//printf("2x=%f==\n", dir.x);
		//printf("2y=%f==\n", dir.y);
		//printf("2z=%f==\n", dir.z);
		//printf("2len		%f\n", sqrt(length2(r)));
	}
	return (dir);
}

float		mix(float a, float b, float mix)
{
	return (b * mix + a * (1 - mix));
}

float		max(float i, float j)
{
	if (i >= j)
		return (i);
	else return (j);
}
float		min(float i, float j)
{
	if (i <= j)
		return (i);
	else return (j);
}

t_vec		trace(t_ray *r, t_object *objects, int depth)
{
	t_vec		pixel;
	t_vec		surf_color;
	t_object	*sphere;
	t_object	*pony;
	t_vec		p_hit;
	t_vec		n_hit;
	t_vec		refl_color;
	t_vec		refr_color;
	t_ray		refl;
	t_ray		refr;
		//t_vec		neg;
	float		bias;
	float		tclosest;
	float		t0;
	float		t1;
	float		facing_ratio;
	float		fresnel;
	float		ior;
	float		eta;
	float		cosi;
	float		k;
	int			inside;
		//static int i =0;
	sphere = NULL;
	pony =	objects;
	t0 = INF;
	t1 = INF;
	tclosest = INF;
	bias = 1e-4;
	inside = 0;
	facing_ratio = 0;
	ior = 1.1;
	eta = 0;
	cosi = 0;
	k = 0;
	surf_color = (t_vec){0,0,0};
	
//neg = (t_vec){-1, -1, -1};
	while (pony)
	{
			//printf("%s : ", pony->name);
//printf("^^%f^%f^^\n", t[0], t[1]);//printf("pos = #%f#%f#%f#\n", pony->position_x, pony->position_y, pony->position_z);
		if (intersect_sphere(r, pony, &t0, &t1))
		{
//i++;//printf("hit");//printf("name: %s\n", pony->name);//printf("**%p**\n", sphere);
			t0 < 0 ? t0 = t1 : 0;
			if (t0 < tclosest)
			{
				tclosest = t0;
				sphere = pony;
				//surf_color = (t_vec){sphere->red, sphere->green, sphere->blue};
//printf("**%p**\n", sphere);
			}
		}
		
//printf("2^^%f^%f^^\n", t[0], t[1]);//printf("name:		%s\n", pony->name);
//printf("**%p**\n", sphere);
		pony = pony->next;
	}
//printf(" :%d: ", i);
	if(!sphere)
		return (t_vec){2,2,2};
	p_hit = add_vec(r->origin, scale_vec(tclosest, r->dir));
	n_hit = vec_subtract(p_hit, (t_vec){sphere->position_x, sphere->position_y, sphere->position_z});
	n_hit = normalize(&n_hit);
	if (dot_product(r->dir, n_hit) > 0)
	{
		n_hit = scale_vec(-1.f, n_hit);
		inside = 1;
			//printf("p_hit:(%f,%f,%f)\n n_hit:(%f,%f,%f)\nin: %d\nn_hit Len: %f\n", p_hit.x, p_hit.y, p_hit.z, n_hit.x, n_hit.y, n_hit.z, inside, sqrt(dot_product(n_hit,n_hit)));
	}
	if ((sphere->trans > 0 || sphere->reflection > 0) && depth < M_DEPTH)
	{
		facing_ratio = -1 * dot_product(r->dir, n_hit);
		fresnel = mix(pow(1 - facing_ratio, 3), 1, 0.1);
		refl.dir = vec_subtract(r->dir, scale_vec(2*dot_product(r->dir, n_hit), n_hit));
		refl.dir = normalize(&refl.dir);
		refl.origin = add_vec(p_hit, scale_vec(bias, n_hit));
		refl_color = trace(&refl, objects, depth + 1);
		if (sphere->trans)
		{
			if(inside)
				eta = ior;
			else eta = 1.0f / ior;
			cosi = -1.0f * dot_product(n_hit, r->dir);
			k = 1.0f - eta * eta * (1.0f - cosi * cosi);
			refr.dir = add_vec(scale_vec(eta, r->dir), scale_vec(eta * cosi - sqrt(k), n_hit));
			refr.dir = normalize(&refr.dir);
			refr.origin = vec_subtract(p_hit, scale_vec(bias, n_hit));
			refr_color = trace(&refr, objects, depth + 1.0f);
		}
		surf_color = add_vec(scale_vec(fresnel, (t_vec)refl_color), scale_vec((1.0f - fresnel) *  sphere->trans,(t_vec)refr_color));
		surf_color = cross_prod(surf_color, (t_vec){sphere->position_x, sphere->position_y, sphere->position_z});
	}
	else
	{
		pony = objects;
		t_vec sphere_color;
		t_vec transmission;
		t_ray light_ray;
		t_object *light;
		t0 = INF;
		t1 = INF;
		//light = (t_vec){0,0,0};
		float x = 0;
		while (pony)
		{
			if (strcmp(pony->name, "Light") == 0)
			{
				sphere_color = (t_vec){sphere->red, sphere->green, sphere->blue};
				transmission = (t_vec){1,1,1};
				light_ray.dir = vec_subtract((t_vec){pony->position_x, pony->position_y, pony->position_z}, p_hit);
				light_ray.dir = normalize(&light_ray.dir);
				//printf("%f",sqrt(length2(&light_ray.dir)));
				t_object *unicorn = objects;
				light = pony;
				while (unicorn)
				{
					if (strcmp(unicorn->name, "Light") !=  0)
					{
						light_ray.origin = add_vec(p_hit, scale_vec(bias, n_hit));
						if(intersect_sphere(&light_ray, unicorn, &t0, &t1))
						{
							transmission = (t_vec){0,0,0};
							light = pony;
							unicorn = NULL;
						}
					}
					if (unicorn)
						unicorn = unicorn->next;
				}
				t_vec a = cross_prod(sphere_color, transmission);
				x = dot_product(n_hit,light_ray.dir);
				x = max(0, x);
				/*if (x < 0)
					x = 0;*/
					//printf("light_emis: %f, %f, %f\n",light.emis_r, light.emis_g, light.emis_b);
				t_vec b = scale_vec(x, (t_vec){light->emis_r, light->emis_g, light->emis_b});
				surf_color = add_vec(surf_color, cross_prod(a, b));
			}
			pony = pony->next;
		}
/*		printf("surf_color: %f, %f, %f\n",surf_color.x, surf_color.y, surf_color.z);
if (surf_color.y >= 0.8){
printf("sphere_color: %f, %f, %f\n",sphere_color.x, sphere_color.y, sphere_color.z);
printf("transmission: %f, %f, %f\n",transmission.x, transmission.y, transmission.z);
printf("x = %f\n", x);
printf("light_emis: %f, %f, %f\n",light.emis_r, light.emis_g, light.emis_b);
}*/
	}
//printf(" :%d: ", i);
	return (add_vec(surf_color, (t_vec){sphere->emis_r, sphere->emis_g, sphere->emis_b}));
}

//remove this pony if getsnene works
t_object	*my_pony(char *s, t_vec c, float refl, float trans, t_vec pos, float r, t_vec e)
{
	t_object	*pony;
	static int i=0;
	pony = (t_object*)malloc(sizeof(t_object));
	pony->name = s;
	pony->red = c.x;
	pony->green = c.y;
	pony->blue = c.z;
	pony->reflection = refl;
	pony->trans = trans;
	pony->position_x = pos.x;
	pony->position_y = pos.y;
	pony->position_z = pos.z;
	pony->radius = r;
	pony->radius_x2 = r * r;
	pony->length_x = 0;
	pony->length_y = 0;
	pony->length_z = 0;
	pony->emis_r = e.x;
	pony->emis_g = e.y;
	pony->emis_b = e.z;
	pony->next = NULL;
	return (pony);
}

void le_main(t_object *objects)
{
	t_object		*pony;
	t_ray			r;
	t_index			num;
	unsigned char	img[WIDTH * HEIGHT * 3];
	t_vec			pixel;

	r.origin.x = 0;
	r.origin.y = 0;
	r.origin.z = 0;
	set_up_num(&num);
	objects = my_pony("Sphere", (t_vec){0.2, 0.2, 0.2}, 0.0, 0.0, (t_vec){0.0, -10004, -20}, 10000, (t_vec){0,0,0});
	objects->next = my_pony("Sphere", (t_vec){1.0, 0.32, 0.36}, 1.0, 0.0, (t_vec){0.0, 0.0, -20}, 4, (t_vec){0,0,0});
	objects->next->next = my_pony("Sphere", (t_vec){0.9, 0.76, 0.46}, 0.0, 1.0, (t_vec){5.0, -1.0, -15}, 2, (t_vec){0,0,0});
	objects->next->next->next = my_pony("Sphere", (t_vec){0.65, 0.77, 0.97}, 0.0, 0.0, (t_vec){5.0, 0.0, -25}, 3, (t_vec){0,0,0});
	objects->next->next->next->next = my_pony("Sphere", (t_vec){0.9, 0.1, 0.9}, 0.0, 0.0, (t_vec){-5.5, 5.0, -15}, 3, (t_vec){0,0,0});
	objects->next->next->next->next->next = my_pony("Light", (t_vec){0.0, 0.0, 0.0}, 0.0, 0.0, (t_vec){0.0, 20.0, -30}, 3, (t_vec){3,3,3});
	while (num.i < HEIGHT)
	{
		num.j = 0;
		
		while (num.j < WIDTH)
		{
			num.y_dir = (1 - 2 * ((num.i + 0.5f) * num.inv_h)) * num.angle;
			num.x_dir = (2 * ((num.j + 0.5f) * num.inv_w) - 1) * num.angle * 							num.aspect_r;
			r.dir.x = num.x_dir;
			r.dir.y = num.y_dir;
			r.dir.z = -1.f;
			
			/*printf("1x=%f==\n", r.dir.x);
			printf("1y=%f==\n", r.dir.y);
			printf("1z=%f==\n", r.dir.z);
			printf("1len		%f\n", sqrt(length2(&r)));
			*/
			r.dir = normalize(&r.dir);
			//printf("1len		%f\n", sqrt(dot_product(r.dir,r.dir)));
			pixel = trace(&r, objects, 0);
			img[(num.j + num.i * WIDTH) * 3 + 0] = min(1, pixel.x) * 255;
			img[(num.j + num.i*WIDTH)*3 + 1] = min(1, pixel.y) * 255;
			img[(num.j + num.i*WIDTH)*3 + 2] = min(1, pixel.z) * 255;
			/*
			printf("x=%f==\n", r.dir.x);
			printf("y=%f==\n", r.dir.y);
			printf("z=%f==\n", r.dir.z);
			printf("len		%f\n", sqrt(length2(&r)));
			//printf("**%f**\n", r.dir.x);*/
			num.j++;
		}
		num.i++;
	}	
	/*
	pony = objects;
	for(i=0;i<HEIGHT;i++){
		r.origin.y = i;
		for(j=0;j<WIDTH;j++){
			r.origin.x = j;
			while (pony)
			{
				t = 2000.00f;
				s.position.x = pony->position_x;
					//printf("**%f**", s.position.x);
				s.position.y = pony->position_y;
				s.position.z = pony->position_z;
				s.radius = pony->radius;
					//printf("**%f**", s.radius);
				hit = intersect_sphere(&r, &s, &t);
					//printf("-%d-", hit);
				if(hit)
				{
					img[(j + i*WIDTH)*3 + 0] = 255;
					img[(j + i*WIDTH)*3 + 1] = 190;
					img[(j + i*WIDTH)*3 + 2] = 0;
				}else
				{
					img[(j + i*WIDTH)*3 + 0] = 219;
					img[(j + i*WIDTH)*3 + 1] = 20;
					img[(j + i*WIDTH)*3 + 2] = 147;
				}
				pony = pony->next;
			}
			pony = objects;
		}
	}*/
	save_xpm("scene1.ppm", img, WIDTH, HEIGHT);
	pony_freedom(objects);
}

int	main(int argc, char **argv)
{
	int		a;
	t_object	*pony;
	t_object	*objects;
	/*
	if (argc != 2)
		return (0);
	while (*++argv)
	{
		objects = get_scene(*argv);
		pony = objects;
		while (pony)
		{
			printf("%s - name:		%s\n", *argv, pony->name);
			printf("%s - red:		%f\n", *argv, pony->red);
			printf("%s - green:		%f\n", *argv, pony->green);
			printf("%s - blue:		%f\n", *argv, pony->blue);
			printf("%s - reflection:	%f\n", *argv, pony->reflection);
			printf("%s - transparency:	%f\n", *argv, pony->trans);
			printf("%s - position_x:	%f\n", *argv, pony->position_x);
			printf("%s - position_y:	%f\n", *argv, pony->position_y);
			printf("%s - position_z:	%f\n", *argv, pony->position_z);
			printf("%s - radius:		%f\n", *argv, pony->radius);
			printf("%s - radius_x2:	%f\n", *argv, pony->radius_x2);
			printf("%s - length_x:	%f\n", *argv, pony->length_x);
			printf("%s - length_y:	%f\n", *argv, pony->length_y);
			printf("%s - length_z:	%f\n\n", *argv, pony->length_z);
			pony = pony->next;
		}
	}*/
	le_main(objects);
	//pony_freedom(objects);
	return (2000);
}


/*
printf("**%d**\n", num.i);
	printf("**%d**\n", num.j);
	printf("**%d**\n", num.k);
	printf("**%f**\n", num.inv_width);
	printf("**%f**\n", num.inv_height);
	printf("**%f**\n", num.f_v);
	printf("**%f**\n", num.aspect_r);
	printf("**%f**\n", num.angle);*/

#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
        vec3 color;

	color = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);

	if(recursion_depth >= world.recursion_depth_limit) //ends recurstion
	{
		color = color*(1 - reflectivity);
		return color;
	}
	vec3 direct = ray.direction;
	Ray myray(intersection_point, direct - 2*dot(direct,normal)*normal);

	return (1 - reflectivity) * color + reflectivity * world.Cast_Ray(myray, ++recursion_depth); // continues recursion
}

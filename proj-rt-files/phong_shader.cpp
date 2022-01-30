#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    //find ambient
    vec3 amb = world.ambient_color * world.ambient_intensity * color_ambient;
    vec3 dif;
    vec3 spec;
    //find Diffuse

    for(unsigned i = 0; i<world.lights.size(); i++){
	vec3 light = (world.lights[i]->position - intersection_point);
       
	Ray light_dist (intersection_point, light);

	vec3 first_hit = light_dist.Point(world.Closest_Intersection(light_dist).dist) - intersection_point;

	if(!world.enable_shadows || (!world.Closest_Intersection(light_dist).object || first_hit.magnitude() > light.magnitude())){

		vec3 reflection_vec = (2 * dot(light, normal) * normal - light).normalized();

		dif = dif +  (color_diffuse * world.lights[i]->Emitted_Light(light) * std::max(dot(normal, light.normalized()), 0.0));

		spec = spec + (color_specular * world.lights[i]->Emitted_Light(light) * std::pow(std::max(dot(reflection_vec, -(ray.direction)), 0.0),specular_power)); 
	}
       

}
    color = amb + dif + spec;   
    return color;
}

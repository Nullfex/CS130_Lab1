#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    vec3 x = (ray.endpoint - center);
    Hit intersect = {0,0,0};
    double a = (dot(x,x) - (radius*radius));
    double b = dot((ray.direction + ray.direction), x);
    double discriminant = ((b*b) - (4*a));

    if(discriminant > 0){
    
    double root_pos = ((-b + sqrt(discriminant)) / 2);
    double root_neg = ((-b - sqrt(discriminant)) / 2);
    
    if((root_pos > 0)&& (root_neg > 0)){
           intersect.object = this;
           intersect.dist = root_neg;
           intersect.part = part;
       }
    }
    
    return intersect;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}

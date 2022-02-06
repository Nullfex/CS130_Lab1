#include "mesh.h"
#include <fstream>
#include <string>
#include <limits>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{

//    TODO
//    return {};
	double min_t = std::numeric_limits<double>::max();
	double dist = 0;
    	Hit result;
	result.object = NULL;

   	if(part < 0) 
	{
		for(int i = 0; i < triangles.size(); i++) {
            
		if(dist < min_t) 
		{
                	if(Intersect_Triangle(ray, i, dist)) 
			{
                		result = {this, dist, i};
				min_t = dist;
                	}
            	}
        	}
    	}
    	else if(Intersect_Triangle(ray, part, dist))
	{
            result = {this, dist, part};
    	}
    return result;

}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const
{
//    TODO;
   	assert(part>=0);

	ivec3 mytri = triangles[part];
	vec3 a = vertices[mytri[0]];
	vec3 b = vertices[mytri[1]];
	vec3 c = vertices[mytri[2]];

	vec3 ac = c - a;
	vec3 ab = b - c;

    return cross(ab,ac).normalized(); 

}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
bool Mesh::Intersect_Triangle(const Ray& ray, int tri, double& dist) const
{
//    TODO;
	vec3 x, y, z, direct;
	ivec3 point;
	double a, b, g;
	
	point = triangles[tri];
	x = vertices[point[1]] - vertices[point[0]];
	y = vertices[point[2]] - vertices[point[0]];
	z = ray.endpoint - vertices[triangles[tri][0]];
	direct = ray.direction;

	if(dot(direct,this->Normal(direct,tri)) == 0){
		return false;
	}

	b = dot(cross(direct,y), z) / dot(cross(direct,y), x);
	g = dot(cross(direct,x), z) / dot(cross(direct,x), y);
	a = 1 - b - g;

	dist = -dot(cross(x,y), z) / dot(cross(x,y), direct);
	
	 return !((a < -weight_tol || b < -weight_tol || g < -weight_tol) || dist < small_t);
	 
}

// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box b;
    TODO;
    return b;
}

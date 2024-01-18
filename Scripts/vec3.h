#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 
{
  public:
    float e[3];

    vec3() : e{0,0,0} {}
    vec3(float e0, float e1, float e2) : e{e0, e1, e2} {}

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    float operator[](int i) const { return e[i]; }
    float& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3 &v) 
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(float t) 
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(float t) 
    {
        return *this *= 1/t;
    }

    float length() const 
    {
        return sqrt(length_squared());
    }

    float length_squared() const // dot product of a vector and itself
    {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    bool near_zero() const 
    {
        // Return true if the vector is close to zero in all dimensions. 
        auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

    static vec3 random() 
    {
        return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max) 
    {
        return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

// purpose of inline- instead of the compiler pushing the instruction pointer to the beginnign of the function to 
//call it, instead the compiler replaces the function call in the code with the actual body of the 
//function elminating the overhead of a function call like passing parameter and jumping to a
// different location in code
// Vector Utility Functions
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) 
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) 
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) 
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) 
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(float t, const vec3 &v) 
{
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, float t) 
{
    return t * v;
}

inline vec3 operator/(vec3 v, float t) 
{
    return (1/t) * v;
}

inline float dot(const vec3 &u, const vec3 &v) 
{
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) 
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) 
{
    return v / v.length();
}

// find a random vector in a unit sphere
inline vec3 random_in_unit_sphere() 
{
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() < 1)// checks if in unit sphere
            return p;
    }
}

// find a random vector in a unit sphere and normalize it
inline vec3 random_unit_vector() 
{
    return unit_vector(random_in_unit_sphere());
}

// converts a unit vector on the hemisphere to be in the same hemisphere as the normal
inline vec3 random_on_hemisphere(const vec3& normal) 
{
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere/direction as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

// takes in a vector and normal vector and returns the reflected vector over the normal vector axis
vec3 reflect(const vec3& v, const vec3& n) 
{
    return v - 2*dot(v,n)*n;
}

// takes a vector and normal vector and returns a reftracted vector
// eta and eta prime are the reftractive indices of the medium the ray is in and the medium the ray 
// refracts into
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) 
{
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

inline vec3 random_in_unit_disk() 
{
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}
#endif
#version 330 core
out vec4 FragColor;

uniform vec2 iResolution;
uniform float iTime;
vec2 fragCoord = gl_FragCoord.xy;

vec2 sphere_center = vec2(0.5, 0.5);
float sphere_radius = 0.2;

struct Sphere
{
    vec3 center;
    float radius;
    vec3 color;
    float sigma_a;
    vec3 scatter;
};

bool intersect_sphere(vec3 ray_origin, vec3 ray_direction, Sphere sphere, out float t0, out float t1)
{
    vec3 L = sphere.center - ray_origin;
    float tca = dot(L, ray_direction);
    float d2 = dot(L, L) - tca * tca;
    if (d2 > sphere.radius * sphere.radius) return false;
    float thc = sqrt(sphere.radius * sphere.radius - d2);
    t0 = tca - thc;
    t1 = tca + thc;
    return true;
}

vec3 trace_scene(vec3 ray_origin, vec3 ray_direction, Sphere sphere)
{
    float t0, t1;
    vec3 background_color = vec3(0.572, 0.772, 0.921);
    vec3 sphere_color = vec3(1.0, 0.0, 0.0);
    if (intersect_sphere(ray_origin, ray_direction, sphere, t0, t1))
    {
        vec3 p1 = ray_origin + ray_direction * t0;
        vec3 p2 = ray_origin + ray_direction * t1;
        float dist = length(p1-p2);
        float tranmission = exp(-dist * sphere.sigma_a);
        return background_color * tranmission + sphere.scatter * (1.0 - tranmission);
    }
    else
    {
        return background_color;
    }
}

void main()
{
    vec2 real_fragCoord = vec2(gl_FragCoord.x / iResolution.x, gl_FragCoord.y / iResolution.y);


    Sphere sphere;
    sphere.center = vec3(0.5, 0.5, 0.0);
    sphere.radius = 0.5;
    sphere.color = vec3(1.0, 0.0, 0.0);
    sphere.sigma_a = 0.1;
    sphere.scatter = vec3(0.8, 0.1, 0.5);

    vec3 res = trace_scene(vec3(0.0, 0.0, 5.0), vec3(0.0, 0.0, -1.0), sphere);
    FragColor = vec4(res, 1.0);
}
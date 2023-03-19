#version 330 core
out vec4 FragColor;

uniform vec2 iResolution;
uniform float iTime;
vec2 fragCoord = gl_FragCoord.xy;

struct Sphere
{
    vec3 center;
    float radius;
    vec3 color;
};

struct Ray
{
    vec3 origin;
    vec3 dir;
};

bool intersect(Ray ray, Sphere sphere, out float t0, out float t1)
{
    vec3 L = sphere.center - ray.origin;
    float tca = dot(L, ray.dir);
    float d2 = dot(L, L) - tca * tca;
    float r2 = sphere.radius * sphere.radius;
    if (d2 > r2) return false;
    float thc = sqrt(r2 - d2);
    t0 = tca - thc;
    t1 = tca + thc;
    return true;
}

vec3 background_color = vec3(0.572, 0.772, 0.921);

vec2 sphere_center = vec2(0.5, 0.5);
float sphere_radius = 0.2;

float sigma_a = 0.1;
vec3 scatter = vec3(0.8, 0.1, 0.5);

void main()
{
    vec2 p = (fragCoord.xy * 2.0 - iResolution.xy) / min(iResolution.x, iResolution.y);
    vec3 view_pos = vec3(0, 0, 0);

    Ray ray;
    ray.origin = view_pos;
    ray.dir = normalize(vec3(p, -0.2));

    Sphere sphere;
    sphere.center = vec3(0, 0, -5);
    sphere.radius = 5;

    float t0, t1;
    if (intersect(ray, sphere, t0, t1))
    {
        vec3 p1 = ray.origin + ray.dir * t0;
        vec3 p2 = ray.origin + ray.dir * t1;
        float dist = length(p1-p2);
        float tranmission = exp(-dist * sigma_a);
        FragColor = vec4(background_color * tranmission + scatter * (1.0 - tranmission), 1.0);
    }
    else
    {
        FragColor = vec4(background_color, 1.0);
    }
}
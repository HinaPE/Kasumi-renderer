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

struct Light
{
    vec3 pos;
    vec3 color;
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

// uniform field
vec3 background_color = vec3(0.572, 0.772, 0.921);
vec2 sphere_center = vec2(0.5, 0.5);
uniform float sphere_radius;
uniform float sigma_a;
vec3 scatter = vec3(0.8, 0.1, 0.5);
// uniform field

void main()
{
    vec2 p = (fragCoord.xy * 2.0 - iResolution.xy) / min(iResolution.x, iResolution.y);
    vec3 view_pos = vec3(0, 0, 0);

    Ray ray;
    ray.origin = view_pos;
    ray.dir = normalize(vec3(p, -0.2));

    Sphere sphere;
    sphere.center = vec3(0, 0, -10);
    sphere.radius = sphere_radius;

    Light light;
    light.pos = vec3(0, 5, -5);
    light.color = vec3(1.3, 0.3, 0.9);


    float t0, t1;
    if (intersect(ray, sphere, t0, t1))
    {
        float step_size = 0.2;
        int ns = int((t1 - t0) / step_size);
        step_size = (t1 - t0) / float(ns);

        float transparency = 1.0;
        vec3 res = vec3(0.0);

        for (int i = 0; i < ns; i++)
        {
            float t = t1 - float(i + 0.5) * step_size;
            vec3 sample_pos = ray.origin + ray.dir * t;

            // compute sample transparency using Beer's law
            float sample_transparency = exp(-step_size * sigma_a);
            transparency *= sample_transparency;

            float t3, t4; // t3 is negative, we don't need it
            Ray ray2;
            ray2.origin = sample_pos;
            ray2.dir = normalize(light.pos - sample_pos);
            intersect(ray2, sphere, t3, t4);
            float light_atenuation = exp(-t4 * sigma_a);
            res += light.color * light_atenuation * step_size;

            res *= sample_transparency;
        }

        FragColor = vec4(background_color * transparency + res, 1.0);

//        vec3 p1 = ray.origin + ray.dir * t0;
//        vec3 p2 = ray.origin + ray.dir * t1;
//        float dist = length(p1-p2);
//        float tranmission = exp(-dist * sigma_a);
//        FragColor = vec4(background_color * tranmission + scatter * (1.0 - tranmission), 1.0);
    }
    else
    {
        FragColor = vec4(background_color, 1.0);
    }
}
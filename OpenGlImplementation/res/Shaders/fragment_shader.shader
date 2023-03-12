#version 330 core
#define MAX_STEPS 100
#define MAX_DIST 100.0
#define SURFACE_DIST 0.01

layout(location = 0) out vec4 color; 


in vec2 v_texCoord;

uniform sampler2D u_Texture;
uniform vec2 u_resolution;
uniform float u_time;
uniform float u_zoom;
uniform float u_pan;

float m_mat_id=0;

float smin(float val1, float val2,float amount)
{
	float dist = clamp(0.5 + (val2 - val1)/ amount, 0., 1.);

	return mix(val2, val1, dist)-amount * dist * (1.0 - dist)/2;

}

float DistToSphere(vec3 sphere_origin,vec3 ray,float radius)
{
	float disttosphere = length(ray - sphere_origin) - radius;
	if (disttosphere < SURFACE_DIST)
	{
		m_mat_id = 0;
	}
	return disttosphere;
}

float Getdist(vec3 ray)
{
	vec3 sphere_o = vec3(0, 2, 6);
	//vec3 sphere_distort = sphere_o * 2.;
	float r = 1;
	float ret;
	//vec3 test = vec3(mod(ray.x, 0.5)*2., mod(ray.y,0.5), mod(ray.z, 0.5));
	//vec2 test2 = ray.xy * mat2(cos(time), sin(time), -sin(time), cos(time));
	vec3 ray_rot = ray;
	//ray_rot.xz *= mat2(cos(u_time*4), sin(u_time*4), -sin(u_time*4), cos(u_time*4));

	ray_rot.x *= 2;
	ray_rot.y *= 2;
	
	float dist = DistToSphere(sphere_o,ray_rot,r);
	float dist2 = DistToSphere(sphere_o.xyz,ray_rot+vec3(sin(u_time),2+cos(u_time),0), r);
	m_mat_id = dist2 - dist;
	ret = smin(dist,dist2,1);
	return ret;
}



vec3 SurfNormal(vec3 SurfPoint)
{
	float dist = Getdist(SurfPoint);
	
	vec2 e = vec2(0.03, 0.);
	
	vec3 N = dist - vec3(Getdist(SurfPoint - e.xyy), Getdist(SurfPoint - e.yxy), Getdist(SurfPoint - e.yyx));
	
	return normalize(N);

}




float RayMarch(vec3 ray_origin,vec3 ray_direction)
{
	float dist = 0.;
	for (int i = 0; i < MAX_STEPS; i++)
	{
		vec3 Point = ray_origin + (ray_direction * dist);
		float surf_dist = Getdist(Point);
		dist += surf_dist;
		if (dist > MAX_DIST || surf_dist < SURFACE_DIST)break;
	}
	return dist;
}

float AddLighting(vec3 SurfPoint, vec3 light_pos)
{
	
	vec3 light_vec = normalize(light_pos - SurfPoint);
	vec3 n = SurfNormal(SurfPoint);
	float lighting = dot(light_vec, n);

	//float c = RayMarch(SurfPoint + (n* SURFACE_DIST*2), light_vec);
	//float a = length(SurfPoint - light_pos);
	//if (c < a)
	//{
	//	lighting *= 0.1;
	//}
	return lighting;
}


void main()
{

	//color = texcolor;
	float time = u_time;
	vec3 camera_pos = vec3(0.7+u_pan, 1., 0.+u_zoom);
	//camera_pos.yz *= mat2(cos(time), sin(time), -sin(time), cos(time));
	vec3 light_pos = camera_pos;
	vec2 resolution = u_resolution;
	vec2 test = vec2(gl_FragCoord.x, gl_FragCoord.y);
	vec2 uv;
	test = (test-(0.5*resolution)) / resolution.y;

	//vec3 col = 0.5 + 0.5 * cos(u_time + test.xyx + vec3(0, 2, 4));
	//test.x = test.x * cos(time) - test.y * sin(time);
	//test.x = test.x * sin(time) + test.y * cos(time);

	vec3 ray_dir = normalize(vec3(test, 1.0));
	//ray_dir.xz *= mat2(cos(time), sin(time), -sin(time), cos(time));
	float col = RayMarch(camera_pos, ray_dir);
	float light = 0.;
	vec3 obj_color = vec3(1., 1., 1.);
	uv = gl_FragCoord.yx / resolution.xy;
	
	
	if (col < MAX_DIST)
	{
		vec3 surf_point = camera_pos + ray_dir * col;

		light = AddLighting(surf_point,light_pos);
		//vec3 diff = GetMatId(surf_point);
		if (m_mat_id > 0)
		{
			obj_color = vec3(1., 0., 0.) * clamp(m_mat_id, 0., 1.) + clamp(1 - m_mat_id, 0., 1.) * obj_color;
		}
	
	}

	//color = texture(u_Texture, v_texCoord);
	color = vec4((obj_color)*light,1.0);
	if (col < MAX_DIST)
	{
		color = texture(u_Texture, uv);
	}

}
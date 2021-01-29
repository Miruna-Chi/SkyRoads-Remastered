#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec3 tex_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float elapsed_time;

// UFO on drugs
uniform int UFOaffliction;
uniform int isUFO;
uniform float rand_drugs;
uniform vec3 rgb;
uniform int renderCameraTarget;

// TODO: output values to fragment shader
out vec3 frag_color;
out vec3 frag_pos;
out vec3 frag_normal;
out vec3 frag_tex_coord;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	// TODO: send output to fragment shader
	if (isUFO == 1 && UFOaffliction == 1) {
		frag_color = vec3 (max(sin(rand(v_position.xy)), rgb.x), 
						   max(sin(rand(v_position.xz)), rgb.y),
						   max(sin(rand(v_position.yz)), rgb.z));
		frag_pos = v_position + (rand(v_position.xy + rand_drugs)) * v_normal;
		frag_normal = v_normal;
		frag_tex_coord = tex_coord;

		if (renderCameraTarget == 1)
			gl_Position = Projection * View * Model * vec4(frag_pos, 1.0);
		else gl_Position = Model * vec4(frag_pos, 1.0);
	}
	else {
		frag_color = vec3(sin(rand(v_position.xy)), cos(rand(v_position.yz)),
							cos(rand(v_position.xz)));
		frag_normal = v_normal;	
		frag_tex_coord = tex_coord;
		gl_Position = Model * vec4(v_position, 1.0);
	}
	
}

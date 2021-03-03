#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int isEarth;
uniform float elapsed_time;

in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	vec4 color = texture2D(texture_1, texcoord);

	if (color.a < 0.5f)
		discard;

	vec4 color2 = texture2D(texture_2, texcoord);
	color.rgb = mix(color.rgb, color2.rgb, 0.5f); 
	// ultimul parametru reprezinta factorul de interpolare intre cele 2 culori, avand valoare intre 0 si 1
	if (isEarth == 1) {
		color = texture2D(texture_1, vec2(texcoord.x + elapsed_time / 5, texcoord.y));
	}

	out_color = color;




}
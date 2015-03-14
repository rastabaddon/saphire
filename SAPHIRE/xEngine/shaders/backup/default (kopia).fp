#version 330

out vec3 color;

in vec2 UV;
uniform sampler2D texture0;

void main(void)
{
	//color = vec4(1,0,0,1);
	color = texture( texture0, UV  ).xyz ;
}

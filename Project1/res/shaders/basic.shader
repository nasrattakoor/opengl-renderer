#shader vertex
#version 460 core

layout(location = 0) in vec4 pos;
//layout(location = 1) in vec2 texCoord;

// "v" for "varying" - look it up
//out vec2 v_TexCoord;

uniform mat4 u_MVP;
out vec4 vertexPos;

void main()
{
	gl_Position = u_MVP * pos;
	vertexPos = pos;
	//v_TexCoord = texCoord;
}

#shader fragment
#version 460 core

//in vec2 v_TexCoord;

out vec4 color;

uniform vec4 u_Color;
//uniform sampler2D u_Texture;

in vec4 vertexPos;

void main()
{
	//vec4 texColor = texture(u_Texture, v_TexCoord);
	//color = u_Color;
	//color = texColor;
	color = vec4(vertexPos.xyz, 1.0f);
}
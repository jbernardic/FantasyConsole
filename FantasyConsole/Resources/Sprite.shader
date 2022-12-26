#shader vertex
#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_IsBitmap;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;
out float v_IsBitmap;

uniform mat4 model;
uniform mat4 projection;

void main() {
	gl_Position = projection * model * vec4(a_Position, 0.0, 1.0);
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_IsBitmap = a_IsBitmap;
}


#shader fragment
#version 330 core

layout (location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;
in float v_IsBitmap;

uniform sampler2D textures[2];

void main() {
	int index = int(v_TexIndex);
	vec4 tex = texture(textures[index], v_TexCoord);
	if(v_IsBitmap > 0.5) tex = vec4(tex.r, tex.g, tex.b, tex.r);
	o_Color = tex;
}
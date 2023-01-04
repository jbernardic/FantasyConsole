#shader vertex
#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 model;
uniform mat4 projection;

void main() {
	gl_Position = projection * model * vec4(a_Position, 0.0, 1.0);
	v_TexCoord = a_TexCoord;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoord;

uniform int hasTexture;
uniform vec4 color;
uniform sampler2D Texture;

void main() {
	if (hasTexture == 1) {
		o_Color = texture(Texture, v_TexCoord);
	}
	else {
		o_Color = vec4(color);
	}

}
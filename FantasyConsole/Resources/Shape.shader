#shader vertex
#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 aTexCoords;

out vec2 _texcoord;

uniform mat4 model;
uniform mat4 projection;

void main() {
	gl_Position = projection * model * vec4(pos, 0.0, 1.0);
	_texcoord = aTexCoords;
}


#shader fragment
#version 330 core

out vec4 color;

in vec2 _texcoord;

uniform int tex;
uniform vec4 _color;
uniform sampler2D _texture;

void main() {
	color = _color;

	if (tex == 1) {
		color = texture(_texture, _texcoord);
	}

}
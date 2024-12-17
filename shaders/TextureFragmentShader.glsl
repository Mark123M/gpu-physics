#version 330 core

//uniform vec4 myColor;
in vec3 myColor;
in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D myTexture;
uniform sampler2D myTexture2;

void main() {
	//FragColor = vec4(myColor, 1.0);
	//FragColor = texture(myTexture, texCoord) * vec4(myColor, 1.0);
	FragColor = mix(texture(myTexture, texCoord), texture(myTexture2, vec2(-texCoord.x, texCoord.y)), 0.2) * vec4(myColor, 1.0);
}
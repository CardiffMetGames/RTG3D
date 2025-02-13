#version 410

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout (location=0) in vec3 vertexPos;
layout (location=2) in vec3 vertexTexCoord;
layout (location=3) in vec3 vertexNormal;
layout (location=4) in vec3 vertexColour;

out SimplePacket {

  vec3 colour;

} outputVertex;


void main(void) {

	outputVertex.colour = vertexColour;

	vec4 worldCoord = modelMatrix * vec4(vertexPos, 1.0);

	gl_Position = projMatrix * viewMatrix * worldCoord;
}

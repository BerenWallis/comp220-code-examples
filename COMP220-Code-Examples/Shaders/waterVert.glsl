#version 330 core
#define PI 3.14159265358979323846
#define screenWidth 1080

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColours;
layout(location=2) in vec2 vertexTextureCoord;
layout(location=3) in vec3 vertexNormals;

//Uniforms 
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;
uniform vec3 waves;
uniform float time;

//Outputs
out vec4 vertexColoursOut;
out vec2 vertexTextureCoordOut;
out vec3 vertexNormalsOut;
out vec3 viewDirection;
out float waveHeight;

void main(){

	mat4 mvpMatrix=projectionMatrix*viewMatrix*(modelMatrix);
	vec3 n = vec3(vertexPosition.x,cos(vertexPosition.y*time)*sin(time),vertexPosition.z);
	vec4 worldPosition=modelMatrix*vec4(n,1.0f);
	
	vec4 mvpPosition=mvpMatrix*vec4(n,1.0f);
	waveHeight = vertexPosition.y;
	vertexColoursOut=vertexColours;
	vertexTextureCoordOut=vertexTextureCoord;
	vertexNormalsOut=normalize(modelMatrix*vec4(vertexNormals,0.0f)).xyz;
	viewDirection=normalize(cameraPosition-worldPosition.xyz);
	//int t = int(time) % 5;
	gl_Position=mvpPosition;

}
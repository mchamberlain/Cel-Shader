varying vec3 normal;
varying vec3 position;
	
void main()
{
	gl_FrontColor = gl_Color;
	normal = gl_NormalMatrix * gl_Normal;
	position = gl_ModelViewMatrix * gl_Vertex;
	
	gl_Position = ftransform();
} 
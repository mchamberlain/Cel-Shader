varying vec3 normal;
varying vec3 position;

void main()
{
	vec3 nn = normalize(normal);
  vec3 light_pos = gl_LightSource[0].position;
  vec3 light_dir = normalize(position - light_pos);
  vec3 eye_dir = normalize(-position);
  vec3 reflect_dir = normalize(reflect(light_dir, nn));
	
  float spec = max(dot(reflect_dir, eye_dir), 0.0);
	float diffuse = max(dot(-light_dir, nn), 0.0);

  float intensity = 0.6 * diffuse + 0.4 * spec;

 	if (intensity > 0.9) {
 		intensity = 1.1;
 	}
 	else if (intensity > 0.5) {
 		intensity = 0.7;
 	}
 	else {
 		intensity = 0.5;
  }

	gl_FragColor = gl_Color * intensity;
} 
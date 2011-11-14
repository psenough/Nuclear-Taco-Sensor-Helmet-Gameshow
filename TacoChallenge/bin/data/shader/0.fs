uniform sampler2D T, N;
uniform float a, time;
varying vec2 t;

void main() {
	float q = dot(t, vec2(sin(a), cos(a)));
	float a = atan(t.y, t.x);
	float d = length(t);
	gl_FragColor = texture2D(T, vec2(texture2D(N, vec2(a * 0.01, 0.01*time)).x, 0.0));
	
	//gl_FragColor = vec4(0.0,1.0,0.0,0.0); 
}
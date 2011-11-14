uniform sampler2D N;
varying vec2 t;


void main() {
	gl_FragColor = texture2D(N, t);
	
	//gl_FragColor = vec4(0.0,1.0,0.0,0.0); 
}
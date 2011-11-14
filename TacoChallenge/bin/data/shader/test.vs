
varying vec2 t;

void main() {
	gl_Position = gl_Vertex;
	t = gl_Vertex.xy * 0.5 + 0.5;
}
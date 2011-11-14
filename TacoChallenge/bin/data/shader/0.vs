
varying vec2 t;
uniform vec2 s;
void main() {
	gl_Position = gl_Vertex;
	t = gl_Vertex.xy * s;
}
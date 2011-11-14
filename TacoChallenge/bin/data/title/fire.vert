varying vec2 t;

uniform vec2 s;

void main()
{
   gl_Position = gl_Vertex * vec4(s, 1.0, 1.0);
   t = gl_Vertex.xy * 0.5 + 0.5;
}
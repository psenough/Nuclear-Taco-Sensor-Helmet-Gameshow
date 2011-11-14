varying vec2 t;

uniform sampler2D T;

void main()
{
   gl_FragColor = texture2D(T, t);
   gl_FragColor.rgb *= gl_FragColor.a;
}
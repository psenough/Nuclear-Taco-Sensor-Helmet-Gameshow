varying vec2 t;
uniform float time;

uniform sampler2D M, N, G;

void main()
{
   vec4 c = (texture2D(N, gl_FragCoord.xy / vec2(256.0) + vec2(0.0, -0.5*time)) + texture2D(N, gl_FragCoord.xy / vec2(512.0) + vec2(0.0, 0.25*time)));
   
   gl_FragColor = texture2D(G, vec2((abs(c - 1.0)).r, 0.0)) * texture2D(M, t).r;
   gl_FragColor.rgb *= gl_FragColor.a;
}
#ifdef GL_ES
precision mediump float;
#endif

in vec4 v_color;
in vec2 v_texture;

uniform sampler2D u_texture;

void main() {
  vec4 col = texture2D(u_texture, v_texture);
  gl_FragColor = mix(v_color, col, .5);
}

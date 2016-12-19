#ifdef GL_ES
precision mediump float;
#endif

in vec2 v_texture;

uniform sampler2D u_texture;
uniform vec4 u_color;

void main(void) {
  gl_FragColor = vec4(1, 1, 1, texture2D(u_texture, v_texture).r) * u_color;
}

#ifdef GL_ES
precision mediump float;
#endif

attribute vec4 a_chardata;

uniform mat4 u_view;
uniform mat4 u_projection;

varying vec2 v_texture;

void main() {
  v_texture = a_chardata.zw;

  gl_Position = u_projection * u_view * vec4(a_chardata.xy, 0, 1);
}

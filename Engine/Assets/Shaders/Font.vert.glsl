#ifdef GL_ES
precision mediump float;
#endif

in vec4 a_chardata;
out vec2 v_texture;

void main() {
  v_texture = a_chardata.zw;

  gl_Position = vec4(a_chardata.xy, 0, 1);
}

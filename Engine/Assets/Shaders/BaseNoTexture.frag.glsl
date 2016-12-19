#ifdef GL_ES
precision mediump float;
#endif

in vec4 v_color;

void main() {
  gl_FragColor = v_color;
}

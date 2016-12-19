#ifdef GL_ES
precision mediump float;
#endif

in vec3 a_position;

void main() {
  gl_Position = vec4(a_position, 1.0);
}

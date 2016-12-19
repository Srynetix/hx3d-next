#ifdef GL_ES
precision mediump float;
#endif

in vec3 a_position;
in vec4 a_color;
in vec2 a_texture;

out vec4 v_color;
out vec2 v_texture;

void main() {
  v_color = a_color;
  v_texture = a_texture;

  gl_Position = vec4(a_position, 1.0);
}

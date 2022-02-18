#version 330 core


layout(location = 0) in vec4 position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform vec4 color;

out vec4 out_color;

void main(){
out_color = color;
gl_Position = u_projection * u_view  * u_model * vec4(position.xy, 1, 1);
}
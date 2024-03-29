#version 330 core


layout(location = 0) in vec4 position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 texCoords;
out vec4 world_position;

void main(){
    texCoords = position.zw;
    world_position = u_model * vec4(position.xy, 1, 1);
    gl_Position = u_projection * u_view  * u_model * vec4(position.xy, 1, 1);
}
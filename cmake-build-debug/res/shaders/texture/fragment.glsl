#version 330 core

in vec2 texCoords;

uniform sampler2D u_Tex;

out vec4 FragColor;

in vec4 world_position;

uniform int light_size;

uniform float lights[128];


vec4 getLight(vec2 position, vec4 frag_color){
    float d = distance(position, world_position.xy) / 160;
    if (d < 1)
    return frag_color;

    float f = (pow(d, 2) + 0.01);

    return vec4((frag_color.rgb) / f, frag_color.a) ;
}

void main()
{
    vec4 frag_color = texture(u_Tex, texCoords);

    if (frag_color.a < 1.0)
    discard;

    vec4 color = frag_color / 6;

    for (int i = 0; i < light_size; i += 2){
        color += getLight(vec2(lights[i], lights[i + 1]), frag_color);
    }

    FragColor = color;
}
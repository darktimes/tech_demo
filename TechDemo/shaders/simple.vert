#version 450 core
layout(location = 0) in vec3 position;

out VS_OUT {
    vec4 color;
} vs_out;

//layout (location = 3) uniform mat4 model;
//layout (location = 4) uniform mat4 view;
//layout (location = 5) uniform mat4 projection;

void main(void) {
//    gl_Position = projection * view * model * vec4(position, 1.0f);
    gl_Position = vec4(position, 1.0f);
    vs_out.color = vec4(position, 1.0f) * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}
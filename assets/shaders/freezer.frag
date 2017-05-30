#version 150

uniform sampler2D tex0; // NEW IMAGE
uniform sampler2D tex1; // SELECTOR
uniform sampler2D tex2; // OLD IMAGE

layout (std140) uniform;
uniform freezer {
 float amount;
 uniform float black;
 uniform float white;
};


in vec2         vertTexCoord0;
out vec4		oColor;

void main()
{
    vec2 n_fragCoord = vertTexCoord0;
    float t = 1.0-amount;
    oColor = vec4(mix(texture(tex0, n_fragCoord).rgb, texture(tex2, n_fragCoord).rgb, (1.0 - t * t * t) * smoothstep(black, white, texture(tex1, n_fragCoord).rgb)), 1);
}
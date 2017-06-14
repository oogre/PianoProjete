
#version 330 core
#include "PhotoshopMathFP.glsl"

uniform sampler2D tex0;

in vec2         vertTexCoord0;
out vec4		oColor;

layout (std140) uniform;
uniform coloradjustement {
    float bri;
    float sat;
    float con;
    float red;
    float green;
    float blue;
};


void main()
{
    float b = bri, s = sat, c = con;
    if(b>0)
        b = 10 * (b * b * b);
    if(s>0)
        s = 10 * (s * s * s);

    b += 1;
    s += 1;
    c += 1;
    
    
    vec3 fader = step(vec3(red, green, blue), vec3(0)) * vec3(red, green, blue);
    vec3 nega =  step(vec3(0), vec3(red, green, blue)) * vec3(red, green, blue);
    vec3 color = ContrastSaturationBrightness(texture(tex0, vertTexCoord0).rgb, b, s, c);
    oColor = vec4( abs(color - nega) + (color * fader), 1.0 );
    
    
    

}


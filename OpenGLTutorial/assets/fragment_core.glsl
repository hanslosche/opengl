#version 330 core
out vec4 FragColor;

//uniform vec4 ourColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixVal;
void main(){
   // FragColor = vec4(ourColor, 1.0f);
   // FragColor = vec4(ourColor, 1.0f) * texture(texture1, TexCoord);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixVal);
} 
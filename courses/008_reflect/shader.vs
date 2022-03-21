#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 FragPos;
out vec3 Normal;

void main()
{
   
   
   
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   FragPos = vec3((model * vec4(aPos, 1.0)).x,(model * vec4(aPos, 1.0)).y,(model * vec4(aPos, 1.0)).z);//Error if calculate first, show nothing   
   Normal = mat3(transpose(inverse(model)))*aNormal;
   TexCoords = aTexCoords;
   //gl_Position = projection * view * model * vec4(aPos,1.0f);
   
   // texCoord = vec2(aTex.x, 1.0-aTex.y);
}
#pragma once
#include "shaderManager.h"
#include <glm/ext/vector_float3.hpp>

class BlinnPhongShader : public ShaderManager
{
public:
    std::string getVertexShader() const override
    {
        return
            "#version 400\n"
            "layout(location=0) in vec3 vp;" //vertex position
            "layout(location=1) in vec3 vn;"	//vertex normal
            "uniform mat4 model;" //model matrix
            "uniform mat4 view;" //pohled
            "uniform mat4 projection;"
            "out vec3 worldPos;"
            "out vec3 worldNorm;" //output to fragment shader
            "void main () {"
            "   worldPos = vec3(model * vec4(vp, 1.0));"
            "   worldNorm = mat3(transpose(inverse(model))) * vn;"
            "	gl_Position = projection * view * model * vec4(vp, 1.0);"
            "}";
    }
    std::string getFragmentShader() const override
    {
        return
            "#version 400\n"
            "in vec3 worldPos;"
            "in vec3 worldNorm;"
            "out vec4 fragColor;"
            "uniform vec3 lightPosition;"
            "uniform vec3 lightColor;"
            "uniform float lightIntensity;"
            "uniform vec3 viewPos;"  // Pøidáno pro viewDir
            "const float constantAtt = 1.0;"
            "const float linearAtt = 0.01;"
            "const float quadraticAtt = 0.001;"
            "void main() {"
            "   float distance = length(lightPosition - worldPos);"
            "   float attenuation = 1.0 / (constantAtt + linearAtt * distance + quadraticAtt * distance * distance);"
            "   vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);"
            "   vec3 norm = normalize(worldNorm);"
            "   vec3 lightDir = normalize(lightPosition - worldPos);"
            "   float diff = max(dot(norm, lightDir), 0.0);"
            "   vec4 diffuse = diff * vec4(lightColor * lightIntensity, 1.0);"
            "   vec3 viewDir = normalize(viewPos - worldPos);"
            "   vec3 halfwayDir = normalize(lightDir + viewDir);"
            "   float spec = pow(max(dot(norm, halfwayDir), 0.0), 32);"
            "   vec4 specular = vec4(spec * lightColor * lightIntensity, 1.0);"
            "   diffuse *= attenuation;"
            "   specular *= attenuation;"
            "   vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);"
            "   fragColor = ambient + (diffuse * objectColor) + specular;"
            "}";
    }

    void setupUniforms(ShaderProgram& shaderProgram) const override
    {
        // Uniformy se nastaví pøes observer pattern z kamery a svìtla
    }
};
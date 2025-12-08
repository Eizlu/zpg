#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "stb/stb_image.h"
#include "model.h"
#include <GL/glew.h>
#include <iostream>
#include "shaderProgram.h"

void Model::applyMaterialToShader(ShaderProgram* shader) const
{
    if (!shader) return;
    shader->use();

    const MaterialData& m = materials[0];

    shader->setUniform("material.Ka", m.Ka);
    shader->setUniform("material.Kd", m.Kd);
    shader->setUniform("material.Ks", m.Ks);
    shader->setUniform("material.Ns", m.Ns);

    shader->setUniform("hasTexture", m.hasTexture);

    if (m.hasTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m.diffuseTexID);
        shader->setUniform("diffuseMap", 0);
    }
}

void Model::setTexture(GLuint textureID)
{
    if (materials.empty()) return;
    {
		materials.push_back(MaterialData());
    }

	materials[0].diffuseTexID = textureID;
    materials[0].hasTexture = true;
}

GLuint loadTextureFromFile(const std::string& path) {
    int w, h, n;
    stbi_set_flip_vertically_on_load(true); // èasto potøeba
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &n, 4);
    if (!data) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return 0;
    }

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // optional wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(data);
    return tex;
}


Model::Model() : VBO(0), VAO(0), vertexCount(0), useExternalData(false), externalVertices(nullptr), externalVertexCount(0)
{
}

Model::Model(const float* vertices, GLsizei Count, bool hasTexture) : VBO(0), VAO(0), vertexCount(0), useExternalData(true), externalVertices(vertices), externalVertexCount(Count)
{
    materials.clear();
    MaterialData def;
    def.Ka = glm::vec3(0.2f, 0.2f, 0.2f);
    def.Kd = glm::vec3(0.8f, 0.8f, 0.8f);
    def.Ks = glm::vec3(0.1f, 0.1f, 0.1f);
    def.Ns = 32.0f;
    def.hasTexture = hasTexture;
    materials.push_back(def);

	const int stride = hasTexture ? 8 : 6;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, externalVertexCount * sizeof(float), externalVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    if (hasTexture)
    {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    else 
        glDisableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    vertexCount = externalVertexCount / 6; // Assuming each vertex has 6 components (3 for position, 3 for color)
}

Model::Model(const char* name)
{

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    std::string inputfile = std::string("models/") + name;
    // vypoèti base dir (napø. "models/shrek/")
    std::string::size_type pos = inputfile.find_last_of("/\\");
    std::string base_dir = (pos == std::string::npos) ? std::string("") : inputfile.substr(0, pos + 1);

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str(), base_dir.c_str());

    if (!warn.empty()) std::cout << "Warn: " << warn << std::endl;
    if (!err.empty()) std::cerr << "Err: " << err << std::endl;
    if (!ret) throw std::runtime_error("Failed to load OBJ file!");

    std::vector<float> vertices;

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            // Position
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            // Normals (if exist)
            if (index.normal_index >= 0) {
                vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 2]);
            }
            else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }

            //  UV coordinates (if exist)
            if (index.texcoord_index >= 0) {
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            }
            else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }
        }
    }

    this->materials.clear();
    for (const auto& m : materials) {
        Model::MaterialData mm;
        mm.Ka = glm::vec3(m.ambient[0], m.ambient[1], m.ambient[2]);
        mm.Kd = glm::vec3(m.diffuse[0], m.diffuse[1], m.diffuse[2]);
        mm.Ks = glm::vec3(m.specular[0], m.specular[1], m.specular[2]);
        mm.Ns = m.shininess > 0.0f ? m.shininess : 32.0f;

        if (!m.diffuse_texname.empty()) {
            mm.diffuseTexName = base_dir + m.diffuse_texname;
            mm.diffuseTexID = loadTextureFromFile(mm.diffuseTexName);
            mm.hasTexture = true;
            std::cout << "Loaded texture: " << mm.diffuseTexName << std::endl;
        }

        this->materials.push_back(mm);
    }


    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    vertexCount = (int)vertices.size() / 8;


    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1); //enable vertex attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2); //enable vertex attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

Model::~Model()
{
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}

void Model::draw() const
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}


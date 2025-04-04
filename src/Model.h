#pragma once

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
public:
    vector<Texture> textures_loaded;	
    vector<Mesh>    meshes;
    string directory;
    bool gammaCorrection;

    Model(string const& filepath, glm::vec3 pos, glm::vec3 scale = glm::vec3(1,1,1), bool gamma = false);
    void Draw(Shader& shader);

private:
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    void loadModel(string const& path);

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
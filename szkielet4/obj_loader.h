//
// Created by Piotr on 02.09.2015.
//

#ifndef BEKA_OBJ_LOADER_H
#define BEKA_OBJ_LOADER_H

#include "glm/glm.hpp"
#include <vector>

bool loadObject(
        const char *path,
        std::vector<glm::vec3> &out_vertices,
        std::vector<glm::vec2> &out_uvs,
        std::vector<glm::vec3> &out_normals
);

#endif //BEKA_OBJ_LOADER_H

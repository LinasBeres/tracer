#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "tinyxml2.h"

#include "vector.h"
#include "sphere.h"
#include "mesh.h"


class Scene
{
    public:
        Scene();
        Scene(const std::string& scenePath);

        int loadSceneFile(const std::string& scenePath);
        void loadSpheres();
        void loadMeshes();
        void loadMaterials();
        void loadCamera();
        void loadConfiguration();
        void cleanScene();
        void cleanSpheresList();
        void cleanMeshesList();
        void cleanMaterialsList();
        void printSpheresData();

        const std::vector<Sphere>& getSpheresList();
        const std::vector<Mesh>& getMeshesList();

    private:
        tinyxml2::XMLDocument sceneFile;

        std::vector<Sphere> spheresList;
        std::vector<Mesh> meshesList;
};

#endif // SCENEPARSER_H

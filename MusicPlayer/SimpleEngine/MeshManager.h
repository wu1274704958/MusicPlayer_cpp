#pragma once

#include "MeshVAO.h"
#include <iostream>
#include <map>
class MeshManager {
public:
	static std::map<std::string, MeshVAO> _MVS;
	static void addMesh(float *d,int len,const char *name);
	static const MeshVAO& getVAO(const char *name);
private:
	MeshManager();
};

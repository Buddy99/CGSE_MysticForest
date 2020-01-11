#ifndef MODEL_H
#define MODEL_H

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class Model
{
public:
	Model();
	Model(string lod1, string lod2, string lod3);
	ofxAssimpModelLoader currentModel;
	ofxAssimpModelLoader lods[3];
	void switchLOD(ofCamera& cam);
	int currentLod;
};

#endif // MODEL_H

#include "Model.h"

Model::Model()
{
}

Model::Model(string lod1, string lod2, string lod3)
{
	lods[0].loadModel(lod1);
	lods[1].loadModel(lod2);
	lods[2].loadModel(lod3);
	currentModel = lods[2];
	currentLod = 1;
}

void Model::switchLOD(ofCamera& cam) {
	float currentDistance = currentModel.getPosition().distance(cam.getPosition());
	int newLod;
	if (currentDistance > 1000)
	{
		newLod = 3;
	}
	else if (currentDistance > 500)
	{
		newLod = 2;
	}
	else
	{
		newLod = 1;
	}
	if (newLod != currentLod)
	{
		ofPoint pos = currentModel.getPosition();
		switch (newLod) {
		case 1:
			currentModel = lods[0];
			break;
		case 2:
			currentModel = lods[1];
			break;
		case 3:
			currentModel = lods[2];
			break;
		default:
			break;
		}
		currentLod = newLod;
		currentModel.setRotation(0, 180, 1, 0, 0);
		currentModel.setScale(0.2, 0.2, 0.2);
		currentModel.setPosition(pos.x, pos.y, pos.z);
		currentModel.drawFaces();
	}
}
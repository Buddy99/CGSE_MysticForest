#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "Model.h"
#include "GLFW/glfw3.h"

#define kMoveInc 250
#define kRotInc 5
#define numOfClouds 40

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void setupTree(Model& model, float x, float y, float z);
	void bubbleSort(ofPlanePrimitive* cubeSide, ofColor* color, int counter);
	float clamp(float n, float min, float max);

	ofSpherePrimitive earth;
	ofPlanePrimitive ground;
	ofBoxPrimitive ornamentCube;
	ofPlanePrimitive clouds[numOfClouds];

	ofLight cornerLights[6];
	ofTexture earthTex;
	ofTexture grassTex;
	ofTexture ornamentTex;
	ofTexture mipmapTex;
	ofTexture cloudTex;

	ofxAssimpModelLoader sword1;
	ofxAssimpModelLoader sword2;
	ofxAssimpModelLoader pillar;
	ofxAssimpModelLoader dove;
	Model tree[19];
	int size;

	ofCamera cam;
	ofVec3f cameraPosition;
	ofVec3f cameraRotation;
	ofVec2f mousePosition;

	ofTrueTypeFont	chosenSide;
	string side;
	ofRectangle bounds;

	ofPlanePrimitive chaosCube[6];
	ofPlanePrimitive orderCube[6];
	ofColor transparentChaosColor[6];
	ofColor transparentOrderColor[6];

	bool keys[255];
	float lastFrame;

	int clashCounter = 0;
	bool countdown = true;
};

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFullscreen(true);
	ofSetBackgroundColor(100, 160, 200);
	ofDisableAlphaBlending();
	ofEnableDepthTest();
	ofSetVerticalSync(true);
	ofSetTimeModeFixedRate();

	// Hide Cursor
	ofHideCursor();

	// Lights
	for (auto light : cornerLights)
	{
		light.enable();
	}
	cornerLights[0].setPosition(ofVec3f(5000, 550, 5000));
	cornerLights[1].setPosition(ofVec3f(-5000, 550, -5000));
	cornerLights[2].setPosition(ofVec3f(5000, 550, -5000));
	cornerLights[3].setPosition(ofVec3f(-5000, 550, 5000));
	cornerLights[4].setPosition(ofVec3f(5000, 550, 0));
	cornerLights[5].setPosition(ofVec3f(-5000, 550, 0));

	// Textures (+ Mipmapping for some Textures)
	ofDisableArbTex();
	ofLoadImage(earthTex, "earth.png");
	ofLoadImage(grassTex, "grass.png");
	grassTex.generateMipmap();
	grassTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	grassTex.setTextureWrap(GL_REPEAT, GL_REPEAT);
	ofLoadImage(ornamentTex, "ornament.png");
	ofLoadImage(mipmapTex, "ornament.png");
	mipmapTex.generateMipmap();
	mipmapTex.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	ofLoadImage(cloudTex, "cloud.png");

	// Setup camera initial position
	cam.setPosition(-2, 20, 100);

	// Setup Text
	ofTrueTypeFont::setGlobalDpi(72);
	chosenSide.load("verdana.ttf", 30, true, true);
	chosenSide.setLineHeight(34.0f);
	chosenSide.setLetterSpacing(1.035);

	// Setup ground
	ground.mapTexCoords(0, 0, 50, 50);
	ground.tiltDeg(-90);
	ground.setScale(10, 20, 30);

	// Setup Cloud Billboards
	// Order
	int cloudPosZ = -500;
	for (int i = 0; i < numOfClouds/4; i++) {
		clouds[i] = ofPlanePrimitive();
		int size = std::rand() % 1000;
		clouds[i].setWidth(50);
		clouds[i].setHeight(50);
		clouds[i].setPosition(800, 400, cloudPosZ);
		clouds[i].lookAt(cam);
		cloudPosZ += 200;
	}
	cloudPosZ = -600;
	for (int i = numOfClouds/4; i < numOfClouds/2; i++) {
		clouds[i] = ofPlanePrimitive();
		int size = std::rand() % 1000;
		clouds[i].setWidth(50);
		clouds[i].setHeight(50);
		clouds[i].setPosition(800, 550, cloudPosZ);
		clouds[i].lookAt(cam);
		cloudPosZ += 200;
	}
	// Chaos
	cloudPosZ = -500;
	for (int i = numOfClouds/2; i < numOfClouds - numOfClouds/4; i++) {
		clouds[i] = ofPlanePrimitive();
		int size = std::rand() % 1000;
		clouds[i].setWidth(50);
		clouds[i].setHeight(50);
		clouds[i].setPosition(-800 + std::rand() % 50, 400 + std::rand() % 150, cloudPosZ + std::rand() % 50);
		clouds[i].lookAt(cam);
		cloudPosZ += 200;
	}
	cloudPosZ = -600;
	for (int i = numOfClouds - numOfClouds/4; i < numOfClouds; i++) {
		clouds[i] = ofPlanePrimitive();
		int size = std::rand() % 1000;
		clouds[i].setWidth(50);
		clouds[i].setHeight(50);
		clouds[i].setPosition(-800 + std::rand() % 50, 650 + std::rand() % 150, cloudPosZ + std::rand() % 50);
		clouds[i].lookAt(cam);
		cloudPosZ += 200;
	}

	// Setup transparent cubes
	// Chaos Side
	// lower
	chaosCube[0].setPosition(-40, 10, -100);
	chaosCube[0].set(10, 10);
	chaosCube[0].tiltDeg(-90);
	transparentChaosColor[0] = ofColor(0, 0, 255, 100);
	// right
	chaosCube[1].setPosition(-45, 15, -100);
	chaosCube[1].set(10, 10);
	chaosCube[1].tiltDeg(-90);
	chaosCube[1].panDeg(-90);
	transparentChaosColor[1]= ofColor(0, 255, 0, 100);
	// top
	chaosCube[2].setPosition(-40, 20, -100);
	chaosCube[2].set(10, 10);
	chaosCube[2].tiltDeg(90);
	transparentChaosColor[2] = ofColor(0, 0, 255, 100);
	// left
	chaosCube[3].setPosition(-35, 15, -100);
	chaosCube[3].set(10, 10);
	chaosCube[3].tiltDeg(-90);
	chaosCube[3].panDeg(90);
	transparentChaosColor[3] = ofColor(0, 255, 0, 100);
	// back
	chaosCube[4].setPosition(-40, 15, -105);
	chaosCube[4].set(10, 10);
	transparentChaosColor[4] = ofColor(255, 0, 0, 100);
	// front
	chaosCube[5].setPosition(-40, 15, -95);
	chaosCube[5].set(10, 10);
	transparentChaosColor[5] = ofColor(255, 0, 0, 100);

	// Order Side
	// lower
	orderCube[0].setPosition(40, 10, -100);
	orderCube[0].set(10, 10);
	orderCube[0].tiltDeg(-90);
	transparentOrderColor[0] = ofColor(100, 100);
	// right
	orderCube[1].setPosition(45, 15, -100);
	orderCube[1].set(10, 10);
	orderCube[1].tiltDeg(-90);
	orderCube[1].panDeg(-90);
	transparentOrderColor[1] = ofColor(0, 100);
	// top
	orderCube[2].setPosition(40, 20, -100);
	orderCube[2].set(10, 10);
	orderCube[2].tiltDeg(90);
	transparentOrderColor[2]= ofColor(100, 100);
	// left
	orderCube[3].setPosition(35, 15, -100);
	orderCube[3].set(10, 10);
	orderCube[3].tiltDeg(-90);
	orderCube[3].panDeg(90);
	transparentOrderColor[3] = ofColor(0, 100);
	// back
	orderCube[4].setPosition(40, 15, -105);
	orderCube[4].set(10, 10);
	transparentOrderColor[4] = ofColor(255, 100);
	// front
	orderCube[5].setPosition(40, 15, -95);
	orderCube[5].set(10, 10);
	transparentOrderColor[5]= ofColor(255, 100);

	// Setup models
	// Neutral
	setupTree(tree[0], -100, 0, -200);
	setupTree(tree[1], 0, 0, -300);
	setupTree(tree[2], 100, 0, -400);
	// Chaos Side
	setupTree(tree[3], -315, 0, 80);
	setupTree(tree[4], -180, 0, 50);
	setupTree(tree[5], -250, 0, 200);
	setupTree(tree[6], -330, 0, 0);
	setupTree(tree[7], -215, 0, 320);
	setupTree(tree[8], -470, 0, 300);
	setupTree(tree[9], -440, 0, 240);
	setupTree(tree[10], -390, 0, 110);
	// Order Side
	setupTree(tree[11], 400, 0, 100);
	setupTree(tree[12], 300, 0, 150);
	setupTree(tree[13], 400, 0, 200);
	setupTree(tree[14], 300, 0, 250);
	setupTree(tree[15], 400, 0, 0);
	setupTree(tree[16], 300, 0, 50);
	setupTree(tree[17], 400, 0, -100);
	setupTree(tree[18], 300, 0, -50);

	sword1.loadModel("Sword.obj");
	sword1.setRotation(0, 180, 1, 0, 0);
	sword1.setScale(0.05, 0.05, 0.05);
	sword1.setPosition(-50, 10, -45);

	sword2.loadModel("Sword.obj");
	sword2.setRotation(0, 180, 1, 0, 7);
	sword2.setScale(0.05, 0.05, 0.05);
	sword2.setPosition(-50, 10, -50);

	pillar.loadModel("Säule.obj");
	pillar.setPosition(0, 0, -40);
	pillar.setRotation(0, 180, 1, 0, 0);
	pillar.setScale(0.025, 0.025, 0.025);

	dove.loadModel("Dove.obj");
	dove.setPosition(25, 10, -20);
	dove.setRotation(0, 180, 1, 0, 3);
	dove.setScale(0.025, 0.025, 0.025);

	mousePosition = { 0,0 };
	cameraRotation = { 0,0,1 };
}

//--------------------------------------------------------------
void ofApp::setupTree(Model& model, float x, float y, float z)
{
	model.lods[0].loadModel("Tree_LOD_One.obj");
	model.lods[1].loadModel("Tree_LOD_Two.obj");
	model.lods[2].loadModel("Tree_LOD_Three.obj");
	model.currentModel = model.lods[0];
	model.currentLod = 1;
	model.currentModel.setRotation(0, 180, 1, 0, 0);
	model.currentModel.setScale(0.2, 0.2, 0.2);
	model.currentModel.setPosition(x, y, z);
}

//--------------------------------------------------------------
void ofApp::update() {
	earth.panDeg(1);

	// Controls
	cameraPosition = cam.getPosition();
	lastFrame = ofGetLastFrameTime();
	if (keys[static_cast<int>('w')]) {
		cameraPosition.z -= kMoveInc * cosf(ofDegToRad(cameraRotation.x)) * lastFrame;
		cameraPosition.x -= kMoveInc * sinf(ofDegToRad(cameraRotation.x)) * lastFrame;
	}
	if (keys[static_cast<int>('s')]) {
		cameraPosition.z += kMoveInc * cosf(ofDegToRad(cameraRotation.x)) * lastFrame;
		cameraPosition.x += kMoveInc * sinf(ofDegToRad(cameraRotation.x)) * lastFrame;
	}
	if (keys[static_cast<int>('a')]) {
		cameraPosition.z += kMoveInc * sinf(ofDegToRad(cameraRotation.x)) * lastFrame;
		cameraPosition.x -= kMoveInc * cosf(ofDegToRad(cameraRotation.x)) * lastFrame;
	}
	if (keys[static_cast<int>('d')]) {
		cameraPosition.z -= kMoveInc * sinf(ofDegToRad(cameraRotation.x)) * lastFrame;
		cameraPosition.x += kMoveInc * cosf(ofDegToRad(cameraRotation.x)) * lastFrame;
	}
	cam.setPosition(cameraPosition);

	// LOD Switching
	size = sizeof(tree) / sizeof(tree[0]);
	for (int i = 0; i < size; i++) {
		tree[i].switchLOD(cam);
	}

	// Billboards
	for (auto i = 0; i < numOfClouds; i++) {
		clouds[i].lookAt(cam);
	}

	// Transparency sorting
	int chaos = sizeof(chaosCube) / sizeof(chaosCube[0]);
	int order = sizeof(orderCube) / sizeof(orderCube[0]);
	bubbleSort(chaosCube, transparentChaosColor, chaos);
	bubbleSort(orderCube, transparentOrderColor, order);

	if (clashCounter == 40)
	{
		countdown = true;
	}
	else if (clashCounter == 0)
	{
		countdown = false;
	}
	if (countdown)
	{
		sword1.setPosition(sword1.getPosition().x, sword1.getPosition().y, sword1.getPosition().z - 0.5);
		sword2.setPosition(sword2.getPosition().x, sword2.getPosition().y, sword2.getPosition().z + 0.5);
		dove.setPosition(dove.getPosition().x, dove.getPosition().y + 0.05, dove.getPosition().z);
		clashCounter--;
	}
	else
	{
		sword1.setPosition(sword1.getPosition().x, sword1.getPosition().y, sword1.getPosition().z + 0.5);
		sword2.setPosition(sword2.getPosition().x, sword2.getPosition().y, sword2.getPosition().z - 0.5);
		dove.setPosition(dove.getPosition().x, dove.getPosition().y - 0.05, dove.getPosition().z);
		clashCounter++;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	cam.begin();

	// Axis Helper
	//ofDrawAxis(100);

	ofSetColor(255, 255, 255);

	// Trees
	for (int i = 0; i < size; i++)
	{
		tree[i].currentModel.drawFaces();
	}

	// Pillar
	pillar.drawFaces();

	// Dove
	dove.drawFaces();

	// Swords
	sword1.drawFaces();
	sword2.drawFaces();

	// Earth
	earth.setPosition(0, 30, -40);
	earth.setScale(0.4, 0.4, 0.4);
	earthTex.bind();
	earth.draw();
	earthTex.unbind();

	// OrnamentCube without Mipmapping
	ornamentCube.setScale(0.3, 0.3, 0.3);
	ornamentCube.setPosition(-100, 15, -100);
	ornamentTex.bind();
	ornamentCube.draw();
	ornamentTex.unbind();

	// OrnamentCube with Mipmapping
	ornamentCube.setScale(0.3, 0.3, 0.3);
	ornamentCube.setPosition(100, 15, -100);
	mipmapTex.bind();
	ornamentCube.draw();
	mipmapTex.unbind();

	// Ground
	grassTex.bind();
	ground.draw();
	grassTex.unbind();

	ofEnableAlphaBlending();

	// Clouds
	cloudTex.bind();
	for (auto cloud : clouds) {
		cloud.draw();
	}
	cloudTex.unbind();

	// Transparent cubes

	for (int i = 0; i < 6; i++) {
		ofSetColor(transparentChaosColor[i]);
		chaosCube[i].draw();
	}
	for (int i = 0; i < 6; i++) {
		ofSetColor(transparentOrderColor[i]);
		orderCube[i].draw();
	}
	ofDisableAlphaBlending();
	ofClearAlpha();

	cam.end();

	// Chosen Side (Chaos or Order)
	if (cam.getPosition().x <= 0)
	{
		side = " C H A O S ";
	}
	else
	{
		side = " O R D E R ";
	}
	ofSetColor(225);

	ofPushMatrix();
	bounds = chosenSide.getStringBoundingBox(side, 0, 0);

	ofTranslate(250 + bounds.width / 2, 24 + bounds.height / 2, 0);
	ofScale(2 + sin(ofGetElapsedTimef()), 2 + sin(ofGetElapsedTimef()), 1.0);

	chosenSide.drawString(side, -bounds.width / 2, bounds.height / 2);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::bubbleSort(ofPlanePrimitive* cubeSide, ofColor* color, int counter) {
	int i, j;
	for (i = 0; i < counter - 1; i++) {
		for (j = 0; j < counter - i - 1; j++) {
			ofVec3f cPos1 = cubeSide[j].getPosition();
			ofVec3f cPos2 = cubeSide[j + 1].getPosition();
			if (cPos1.squareDistance(cam.getPosition()) < cPos2.squareDistance(cam.getPosition())) {
				std::swap(cubeSide[j], cubeSide[j + 1]);
				std::swap(color[j], color[j + 1]);
			}
		}
	}
}

//--------------------------------------------------------------
float ofApp::clamp(float n, float min, float max) {
	return (n < min) ? min : (max < n) ? max : n;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	keys[key] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	keys[key] = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	float middleY = ofGetHeight() / 2;
	float middleX = ofGetWidth() / 2;
	cam.setOrientation({ 0,0,0 });
	cameraRotation.y += fmod((middleY - y) / 10, 360);
	cameraRotation.x += fmod((middleX - x) / 10, 360);
	cameraRotation.y = clamp(cameraRotation.y, -60, 89);
	cam.panDeg(cameraRotation.x);
	cam.tiltDeg(cameraRotation.y);
	glfwSetCursorPos(((ofAppGLFWWindow*)ofGetWindowPtr())->getGLFWWindow(), middleX, middleY);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 450, true, true, true);
	this->span = 20;

	ofFbo fbo;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	string word = "Aa";
	this->font.drawString(word, this->font.stringWidth(word) * -0.5, this->font.stringHeight(word) * 0.5);

	fbo.end();

	ofPixels pixels;
	fbo.readToPixels(pixels);

	for (int x = 0; x < fbo.getWidth(); x += this->span) {

		for (int y = 0; y < fbo.getHeight(); y += this->span) {

			if (pixels.getColor(x, y) != ofColor(0, 0)) {

				this->locations.push_back(glm::vec2(x - ofGetWidth() * 0.5, ofGetHeight() - y - ofGetHeight() * 0.5));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	for (auto& location : this->locations) {

		for (int z = this->span * -2; z <= this->span * 2; z += this->span) {

			float noise_value = ofNoise(location.x * 0.0045, location.y * 0.0045, z * 0.05, ofGetFrameNum() * 0.02);

			if (noise_value > 0.5) {

				ofFill();
				ofSetColor(39);
				ofDrawBox(glm::vec3(location, z), this->span - 1);

				ofNoFill();
				ofSetColor(239);
				ofDrawBox(glm::vec3(location, z), this->span);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
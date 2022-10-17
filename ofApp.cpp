#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetColor(255);

	this->font_size = 40;
	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	this->font.load(font_settings);

	this->words = {

		"A", "B", "C", "D", "E",
		"F", "G", "H", "I", "J",
		"K", "L", "M", "N", "O",
		"P", "Q", "R", "S", "T",
		"U", "V", "W", "X", "Y", "Z",
	};

	for (int x = this->font_size * -12; x <= this->font_size * 12; x += this->font_size * 0.8) {

		for (int y = this->font_size * -12; y <= this->font_size * 12; y += this->font_size * 1.2) {

			this->location_list.push_back(glm::vec2(x, y));
			this->index_list.push_back(0.f);
			this->param_list.push_back(true);
		}
	}


}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	for (auto& param : this->param_list) {

		param = false;
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		auto y = ((int)((this->location_list[i].x + 1000) * 10 + ofGetFrameNum() * 10) % 1200) - 600;

		if (this->location_list[i].y > y - 60 && this->location_list[i].y < y + 60) {

			this->index_list[i] += ofRandom(1, 5);

			this->index_list[i] = (int)this->index_list[i] % this->words.size();
			this->param_list[i] = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofTranslate(this->font_size * 0.5, this->font_size * 0.5);
	ofRotate(330);

	for (int i = 0; i < this->location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->location_list[i]);

		if (this->param_list[i]) {

			ofRotateY(ofMap(ofNoise(this->location_list[i].y * 0.005, ofGetFrameNum() * 0.03), 0, 1, -3600, 3600));
		}

		this->font.drawString(this->words[this->index_list[i]], this->font_size * -0.25, this->font_size * -0.5);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
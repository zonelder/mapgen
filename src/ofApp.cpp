#include "ofApp.h"
#include "map/Map.h"

//@brief setup map
double t;
int step = 0;
syrenmap::Map globalMap(24);



void ofApp::setup() {

	//@brief generate our map
	globalMap.generate();
	globalMap.updateColoring();

}


//--------------------------------------------------------------
void ofApp::update(){
	double T = clock();
	if ((T - step) > 10000)
	{
		step += 10000;
		auto state = (int)(globalMap.getRenderStatus());
		auto next_state = (state + 1) % (int)(syrenmap::renderStatus::MAX);
		globalMap.setRenderstatus(syrenmap::renderStatus(next_state));
	}
	t = T;
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255, 255, 255);
	globalMap.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

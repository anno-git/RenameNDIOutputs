#pragma once

#include "ofMain.h"
#include "ofxNDI.h"
#include "ofxNDIRouter.h"
#include "ofxImGui.h"

class ofApp : public ofBaseApp{

public:
    std::vector<ofxNDIRouter> routers;
    std::vector<string> selected_sources;
    std::vector<string> routers_names;
    std::vector<ofxNDI::Source> sources;
    ofxImGui::Gui gui;

    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;
    
    void updateListSources();

    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
		
};

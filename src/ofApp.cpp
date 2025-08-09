#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    updateListSources();
    loadSettings();
    ofSetWindowTitle("Rename NDI Outputs");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.begin();
    ImGui::Begin("router");
    if(ImGui::Button("save"))
    {
        saveSettings();
    }
    ImGui::SameLine();
    if(ImGui::Button("load"))
    {
        loadSettings();
    }
    ImGui::Separator();
    if(ImGui::Button("update source list"))
    {
        updateListSources();
    }
    if(ImGui::Button("add router"))
    {
        routers.push_back(ofxNDIRouter());
        selected_sources.push_back("");
        routers_names.push_back("");
    }
    int eraseIndex = -1;
    
    for(auto i = 0; i < routers.size(); i++)
    {
        ImGui::Separator();
        char buf[100];
        std::snprintf(buf, sizeof(buf), "%s", routers_names[i].c_str());

        bool pushedColor = (buf[0] == '\0');
        
        string labels = "select source for router[" + ofToString(i + 1) + "]";
        if(ImGui::BeginCombo(labels.c_str(), selected_sources[i].c_str()))
        {
            for (int n = 0; n < sources.size(); n++)
            {
                bool is_selected = (selected_sources[i] == sources[n].p_ndi_name);
                if (ImGui::Selectable(sources[n].p_ndi_name.c_str(), is_selected))
                {
                    if(selected_sources[i] != sources[n].p_ndi_name)
                    {
                        selected_sources[i] = sources[n].p_ndi_name;
                        if(buf[0] != '\0')
                        {
                            routers[i].setup(routers_names[i]);
                            routers[i].setRoute(sources[n]);
                        }
                    }
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
                }
            }
            ImGui::EndCombo();
        }
        
        if (pushedColor) {
            ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(255, 0, 0, 255));
            // 必要ならホバー/アクティブも同様に push して、あとで同数 pop する
            // ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(255, 0, 0, 255));
            // ImGui::PushStyleColor(ImGuiCol_FrameBgActive,  IM_COL32(255, 0, 0, 255));
        }
        labels = "Output name of router[" + ofToString(i + 1) + "]";
        // 入力
        bool changed = ImGui::InputText(labels.c_str(), buf, sizeof(buf));

        // push したら必ず pop（buf の現在値ではなく pushedColor で判断）
        if (pushedColor) {
            ImGui::PopStyleColor(1);
            // ホバー/アクティブも push したなら PopStyleColor(3) に合わせる
        }

        if (changed) {
            routers_names[i] = buf;   // 入力中は随時更新
        }

        // フォーカスが外れた瞬間で確定
        if (ImGui::IsItemDeactivatedAfterEdit()) {
            if (buf[0] != '\0') {
                for(auto& source: sources)
                {
                    if(source.p_ndi_name == selected_sources[i])
                    {
                        routers[i].setup(routers_names[i]);
                        routers[i].setRoute(source);
                        break;
                    }
                }
            }
        }

        
        labels = "erase router[" + ofToString(i + 1) + "]";
        if(ImGui::Button(labels.c_str()))
        {
            eraseIndex = i;
        }
    }
    if (eraseIndex != -1) {
        routers.erase(routers.begin() + eraseIndex);
        routers_names.erase(routers_names.begin() + eraseIndex);
        selected_sources.erase(selected_sources.begin() + eraseIndex);
    }
    
    ImGui::End();
    gui.end();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::updateListSources()
{
    sources = ofxNDI::listSources();
}

//--------------------------------------------------------------
void ofApp::saveSettings()
{
    ofJson json;
    for(int i = 0; i < routers.size(); i++)
    {
        json["routers"][i]["name"] = routers_names[i];
        json["routers"][i]["source"] = selected_sources[i];
    }
    ofSaveJson("settings.json", json);
}

//--------------------------------------------------------------
void ofApp::loadSettings()
{
    ofFile file("settings.json");
    if(file.exists())
    {
        ofJson json;
        json << file;
        if(json.find("routers") != json.end())
        {
            updateListSources();
            routers.clear();
            routers_names.clear();
            selected_sources.clear();
            for(int i = 0; i < json["routers"].size(); i++)
            {
                string name = json["routers"][i]["name"];
                string source = json["routers"][i]["source"];
                if(name.size() > 0)
                {
                    bool found = false;
                    for(auto& s: sources)
                    {
                        if(s.p_ndi_name == source)
                        {
                            routers.push_back(ofxNDIRouter());
                            routers_names.push_back(name);
                            selected_sources.push_back(source);
                            routers.back().setup(name);
                            routers.back().setRoute(s);
                            found = true;
                            break;
                        }
                    }
                    if(!found)
                    {
                        ofLogWarning("RenameNDIOutputs") << "source:" << source << " not found.";
                    }
                }
            }
        }
    }
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
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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

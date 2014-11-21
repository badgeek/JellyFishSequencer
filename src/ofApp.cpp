#include "ofApp.h"

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofBackground(0);
   // seqtest.set(300, 50, 100, 100);
    jelly_cnt = 0;
    camWidth = 640;
    camHeight = 480;

    vidGrabber.setGrabber(ofPtr<ofxPS3EyeGrabber>(new ofxPS3EyeGrabber()));
    vidGrabber.initGrabber(640, 480);

    videoTexture.allocate(camWidth,camHeight, GL_RGBA);

    videoSource.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    //videoCrop.allocate(camWidth,camHeight, GL_RGB);

    ofSetVerticalSync(true);

    // ----
    timer_current = 0;
    timer_interval = 250;

    sender.setup(HOST, PORT);

}





//--------------------------------------------------------------
void ofApp::update(){

    ofBackground(0,0,0);

    //this->blendImage(0,0,100,100, videoCrop);

    vidGrabber.update();
    if (vidGrabber.isFrameNew())
    {
        videoSource.setFromPixels(vidGrabber.getPixelsRef());
    }

    float timer_now = ofGetElapsedTimeMillis();

    if((timer_now - timer_current) > 100   )
    {
        timer_current = timer_now;

        ofxOscMessage m;
        m.setAddress("/jelly/magnitude");

        for (int x = 0; x < jellySequencer.size(); x++)
        {
            //jellySequencer.at(x).
            m.addFloatArg(jellySequencer.at(x)->differenceVideo);
            //m.addIntArg(jellySequencer.at(x)->differenceVideo);
       }

        sender.sendMessage(m);


    }

    for (int x = 0; x < jellySequencer.size(); x++)
    {
        if(jellySequencer.at(x)->deleteMe)
        {
            delete jellySequencer.at(x);
            jellySequencer.erase(jellySequencer.begin()+x);
        }
        //jellySequencer.at(x)->x -= 10;
   }

}

//--------------------------------------------------------------
void ofApp::draw(){

  //  videoCrop.draw(0,0);
//    ofSetHexColor(0xffffff);
    float ratio =  videoSource.getWidth()/videoSource.getHeight();

   videoSource.draw(0,0,ofGetWidth(),ofGetWidth()/ratio);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') ofToggleFullscreen();

    if (key == 'o') {

        ofxOscMessage m;
        m.setAddress("/jelly/magnitude");
        m.addIntArg(666);
        sender.sendMessage(m);
    }

    if (key == 'm')
    {
        for (int x = 0; x < jellySequencer.size(); x++)
        {
            jellySequencer.at(x)->grabFrame();
            //m.addIntArg(jellySequencer.at(x)->differenceVideo);
       }
    }

    printf("key: %i\n", key);
/*key: 356
key: 357
key: 359
key: 358
*/
    //kiri
    if (key == 356)
    {
        for (int x = 0; x < jellySequencer.size(); x++)
        {
            jellySequencer.at(x)->x -= 10;
       }

    }
    //atas
    if (key == 357)
    {
        for (int x = 0; x < jellySequencer.size(); x++)
        {
            jellySequencer.at(x)->y -= 10;
       }

    }
    //bawah
    if (key == 359)
    {
        for (int x = 0; x < jellySequencer.size(); x++)
        {
            jellySequencer.at(x)->y += 10;
       }

    }
    //kanan
    if (key == 358)
    {
        for (int x = 0; x < jellySequencer.size(); x++)
        {
            jellySequencer.at(x)->x += 10;
       }

    }


    if (key == 'z')
    {
        for (int x = 0; x < jellySequencer.size(); x++)
        {
                delete jellySequencer.at(x);
                jellySequencer.erase(jellySequencer.begin()+x);
            //jellySequencer.at(x)->x -= 10;
       }

        jelly_cnt = 0;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'a')
    {
        float ratio =  videoSource.getWidth()/videoSource.getHeight();
        jelly_cnt++;
        jellySequence * seq = new jellySequence();
        seq->sourceVideo = &videoSource;
        seq->set(mouseX-50, mouseY-50, 100, 100);
        seq->jelly_id = jelly_cnt;
        seq->videoQuadW = ofGetWidth();
        seq->videoQuadH = ofGetWidth()/ratio;
        seq->setup();

            //jellySequencer.push_back(300, 50, 100, 200);
       jellySequencer.push_back(seq);
    }
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

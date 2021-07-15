#ifndef _VideoCtrlTest_VideoCtrlTest_h
#define _VideoCtrlTest_VideoCtrlTest_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#include <VideoCtrl/VideoCtrl.h>

class VideoSliderCtrl : public SliderCtrl {
    bool mousedown { false };
    void LeftDown(Point p, dword keyflags) override { mousedown = true;  SliderCtrl::LeftDown(p, keyflags); }
    void LeftUp(Point p, dword keyflags)   override { NewPositionSelected(GetData()); mousedown = false; SliderCtrl::LeftUp(p, keyflags);   }
public:
    bool IsMouseDown() { return mousedown; }
    
    Event<Value> NewPositionSelected;
};

#define LAYOUTFILE <VideoCtrlTest/VideoCtrlTest.lay>
#include <CtrlCore/lay.h>

class VideoCtrlTest : public WithVideoCtrlTestLayout<TopWindow> {
public:
    VideoCtrlTest();
    void VideoPositionChanged(uint64 pos);
    void Run();
    void Run(String file);
};

#endif

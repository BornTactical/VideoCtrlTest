#include "VideoCtrlTest.h"

void VideoCtrlTest::Run() {
    Open();
    while(IsOpen()) {
        ProcessEvents();
        
        if(videoCtrl.IsOpen()) {
            videoCtrl.Render();
        }
        
        Sleep(1);
    }
}

void VideoCtrlTest::Run(String file) {
    videoCtrl.Open(file);
    
    Run();
}

void VideoCtrlTest::VideoPositionChanged(uint64 pos) {
    if(!slider.IsMouseDown()) {
        slider <<= (int64)pos;
    }
}

VideoCtrlTest::VideoCtrlTest() {
    CtrlLayout(*this, "VideoCtrl test");
    Sizeable();
    
    openBtn.WhenPush = [&] {
        FileSel selector;
        if(selector.ExecuteOpen("Load video")) {
            String file = selector.Get();
            videoCtrl.Open(file);
            uint64 first = videoCtrl.FirstTS();
            uint64 duration = videoCtrl.Duration();
            
            slider.MinMax(videoCtrl.FirstTS(), videoCtrl.Duration());
            volumeSlider.MinMax(0.0, 1.0);
        }
    };
    
    pauseBtn.WhenPush = [&] {
        videoCtrl.Pause();
    };
    
    playBtn.WhenPush = [&] {
        videoCtrl.Play();
    };
    
    rewindBtn.WhenPush = [&] {
        videoCtrl.Rewind();
    };
    
    slider.NewPositionSelected         = [&](int pos)    { videoCtrl.Seek(pos); };
    volumeSlider.WhenAction            = [&]()           { videoCtrl.Volume(volumeSlider.GetData()); };
    videoCtrl.WhenVideoPositionChanged = [&](uint64 pos) { VideoPositionChanged(pos); };
}

GUI_APP_MAIN {
    const Vector<String>& cmdline = CommandLine();
    for(int i = 0; i < cmdline.GetCount(); i++) {
    }
    
    if(cmdline.GetCount() == 1) {
        VideoCtrlTest().Run(cmdline[0]);
    }
    else {
        VideoCtrlTest().Run();
    }
}

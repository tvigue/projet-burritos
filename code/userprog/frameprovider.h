#ifdef CHANGED
#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

class FrameProvider
{

public:
    FrameProvider ();	
    ~FrameProvider ();
    int GetEmptyFrame();
    void ReleaseFrame(int which);
    bool TestFrame(int which);
    void MarkFrame(int which);
    int NumAvailFrame();
private :
    int numFrames;
    unsigned int * map;

};
#endif
#endif //CHANGED

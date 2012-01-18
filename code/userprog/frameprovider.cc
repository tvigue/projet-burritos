#include "frameprovider.h"
#include "system.h"

FrameProvider::FrameProvider(){

	numFrames=NumPhysPages;
	map = new unsigned int[numFrames];
    for (int i = 0; i < numFrames; i++)
	ReleaseFrame (i);

}

FrameProvider::~FrameProvider(){

	delete [] map;

}

bool FrameProvider::TestFrame (int which)
{
    ASSERT (which >= 0 && which < numFrames);
    if (map[which]==1)
	return TRUE;
    else
	return FALSE;
}

void FrameProvider::MarkFrame (int which)
{
    ASSERT (which >= 0 && which < numFrames);
    map[which]=1;
}


int FrameProvider::GetEmptyFrame(){
	    
	for (int i = 0; i < numFrames; i++){
	if (!TestFrame (i))
	  {
	      MarkFrame(i);
	      return i;
	  }
	 }
    return -1;

}

void FrameProvider::ReleaseFrame(int which){

	ASSERT (which >= 0 && which < numFrames);
    map[which]=0;
}

int FrameProvider::NumAvailFrame(){

    int count = 0;

    for (int i = 0; i < numFrames; i++)
	if (!TestFrame (i))
	    count++;
    return count;

}

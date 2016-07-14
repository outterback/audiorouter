/*
  ==============================================================================

    GUI_Thread.h
    Created: 12 Jul 2016 3:22:46pm
    Author:  dzadza

  ==============================================================================
*/

#ifndef GUI_THREAD_H_INCLUDED
#define GUI_THREAD_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class GUIThread : public Thread
{
public:
	GUIThread();
	void run() override;
};



#endif  // GUI_THREAD_H_INCLUDED

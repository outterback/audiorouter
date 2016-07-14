/*
  ==============================================================================

    GUI_Thread.cpp
    Created: 12 Jul 2016 3:22:46pm
    Author:  dzadza

  ==============================================================================
*/

#include "GUI_Thread.h"
#include <chrono>

void GUIThread::run(int ms, AudioProcessor& p)
{
	std::chrono::milliseconds dur(16);

	while (true)
	{
		
		double as = p.getTimeInPeriod();
		textLabel.setText(std::to_string(as), NotificationType::sendNotification);
	}

}

GUIThread::GUIThread()
{
}

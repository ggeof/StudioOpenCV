
#include "interface/MainView.h"

int main(int argc, char **argv)
{
    // On charge gtk
    XInitThreads();
	gtk_init(&argc, &argv);

	cv::setUseOptimized(true); // On indique qu'on veut optimizer OpenCV

    // Lecture des arguments
	int argcView = 1;
	bool helpShow = false;
	while(argcView != argc)
	{
		argcView++;
	}

    MainView window();
    window.run();

	return 1;
}

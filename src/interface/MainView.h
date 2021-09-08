#ifndef __MAINVIEW_H__  
#define __MAINVIEW_H__

#include <gtk/gtk.h>
#include <map>

class MainView
{
    public:
        MainView(/* args */);

        ~MainView();

        void run();

    protected:

        void load();

        bool update();

    private:
        enum GtkElement {

        };

        std::map<GtkElement, GtkWidget*> widgets;
};

#endif // __MAINVIEW_H__
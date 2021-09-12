#ifndef __MAINVIEW_H__  
#define __MAINVIEW_H__

#include <gtk/gtk.h>
#include <map>

#include "../core/Functions/FunctionOpenCV.h"

class MainView
{
    public:
        MainView(/* args */);

        ~MainView();

        void run();

    protected:

        void load();

        static gboolean update();

        std::shared_ptr<FunctionOpenCV> functionOpencv;

        static void compilAndRunFunction(GtkWidget *widget, MainView *mainView);

    private:
        enum GtkElement {
            Window,
            imageShowed,
            entryCode,
            returnCompilation
        };

        std::map<GtkElement, GtkWidget*> widgets;
};

#endif // __MAINVIEW_H__
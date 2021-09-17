#ifndef __MAINVIEW_H__  
#define __MAINVIEW_H__

#include <gtk/gtk.h>
#include <map>

#include "../core/Functions/ExecuteFunction.h"
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


        static gboolean keyPressed(GtkWidget* widget, GdkEvent* event, MainView* wdw);

        static void compilFunction(GtkWidget *widget, MainView *mainView);

        static void runFunction(GtkWidget *widget, MainView *mainView);

        static void compilAndRunFunction(GtkWidget *widget, MainView *mainView);

        void updateFunction();

    private:
        enum GtkElement {
            Window,
            comboBoxChoseImage,
            imageShowed,
            entryCode,
            returnCompilation,

            listImage
        };

        std::map<GtkElement, GtkWidget*> widgets;

        ExecuteFunction execFunction;
};

#endif // __MAINVIEW_H__
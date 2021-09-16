#include "MainView.h"
#include "../core/Functions/ExecuteFunction.h"

#include <thread>


#define EXECUTE_FUNCTION_IN_THREAD(function, ...){\
        std::thread t(function, __VA_ARGS__);\
        t.detach(); }

#define EXECUTE_CALL_IN_THREAD(function,  TypePointer)\
    +[](GtkWidget* widget, TypePointer* ptr){\
        EXECUTE_FUNCTION_IN_THREAD(function, widget, ptr)\
    }

MainView::MainView(/* args */) :
    functionOpencv(std::make_shared<FunctionOpenCV>("functionOpencv")), execFunction(functionOpencv)
{

    this->load();

    
    g_idle_add ((GSourceFunc) update, this);
    g_signal_connect(G_OBJECT(this->widgets[GtkElement::Window]), "key-press-event", G_CALLBACK(this->keyPressed), this);
}

void MainView::load() 
{
    // Chargement fichier glade qui contient l'interface
    GtkBuilder * builder = gtk_builder_new();
    
    GError *err = NULL;
    gtk_builder_add_from_file (builder, (std::string(PATH_PROJET)+"/ressources/interface/StudioOpenCV.glade").c_str(), &err);
    
    this->widgets[GtkElement::Window] = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow")); 
    
    this->widgets[GtkElement::returnCompilation] = GTK_WIDGET(gtk_builder_get_object(builder, "returnCompilation")); 
    this->widgets[GtkElement::entryCode] = GTK_WIDGET(gtk_builder_get_object(builder, "entryCode")); 
    this->widgets[GtkElement::imageShowed] = GTK_WIDGET(gtk_builder_get_object(builder, "imageShowed")); 

    
    GtkWidget * btn = GTK_WIDGET(gtk_builder_get_object(builder, "btnCompilExecuter")); 
    g_signal_connect(G_OBJECT(btn), "clicked", G_CALLBACK(compilAndRunFunction), this);


    // action button menu
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "menuFunctionCompil")), "activate", G_CALLBACK(EXECUTE_CALL_IN_THREAD(compilFunction, MainView)), this);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "menuFunctionRun")), "activate", G_CALLBACK(EXECUTE_CALL_IN_THREAD(runFunction, MainView)), this);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "menuFunctioncompilAndRun")), "activate", G_CALLBACK(EXECUTE_CALL_IN_THREAD(compilAndRunFunction, MainView)), this);

}

MainView::~MainView() 
{
    
}

void MainView::run() 
{
    gtk_widget_show_all(this->widgets[GtkElement::Window]);
    gtk_main();
}

gboolean MainView::update() 
{
    

    return true;
}

gboolean MainView::keyPressed(GtkWidget* widget, GdkEvent* event, MainView* wdw) 
{
    if(event->key.keyval == GDK_KEY_F5)
        EXECUTE_FUNCTION_IN_THREAD(MainView::compilAndRunFunction, widget, wdw)
    else
        return false;

    // a key recognized is pressed
    return true;
    
}

void MainView::compilFunction(GtkWidget *widget, MainView *mainView) 
{
    gtk_label_set_label(GTK_LABEL(mainView->widgets[GtkElement::returnCompilation]), "");
    mainView->updateFunction();
    
    std::string rtn = mainView->execFunction.compile() + "\n--- END COMPILATION\n\n";
    gtk_label_set_label(GTK_LABEL(mainView->widgets[GtkElement::returnCompilation]), rtn.c_str());
}

void MainView::runFunction(GtkWidget *widget, MainView *mainView) 
{
    gtk_label_set_label(GTK_LABEL(mainView->widgets[GtkElement::returnCompilation]), "");
    std::string rtn = mainView->execFunction.execute() + "\n--- END EXECUTION\n";
    gtk_label_set_label(GTK_LABEL(mainView->widgets[GtkElement::returnCompilation]), rtn.c_str());
    
}

void MainView::compilAndRunFunction(GtkWidget *widget, MainView *mainView) 
{
    mainView->compilFunction(widget, mainView);
    std::string rtn =  std::string(gtk_label_get_label(GTK_LABEL(mainView->widgets[GtkElement::returnCompilation]))) + "\n" +
            mainView->execFunction.execute() + "\n--- END EXECUTION\n";
    gtk_label_set_label(GTK_LABEL(mainView->widgets[GtkElement::returnCompilation]), rtn.c_str());
}

void MainView::updateFunction() 
{
    auto buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(this->widgets[GtkElement::entryCode]));
    GtkTextIter start,
                end;

    gtk_text_buffer_get_end_iter(buf, &end);
    gtk_text_buffer_get_start_iter(buf, &start);

    this->functionOpencv->setCode(std::string(gtk_text_buffer_get_text(buf, &start, &end, false)));
    
}

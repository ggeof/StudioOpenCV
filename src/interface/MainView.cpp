#include "MainView.h"
#include "../core/Functions/ExecuteFunction.h"

MainView::MainView(/* args */) 
{
    this->functionOpencv = new FunctionOpenCV("functionOpencv");

    this->load();

    
    g_idle_add ((GSourceFunc) update, this);
}

void MainView::load() 
{
    // Chargement fichier glade qui contient l'interface
    GtkBuilder * builder = gtk_builder_new();
    
    GError *err = NULL;
    gtk_builder_add_from_file (builder, "ressources/Interface/InterfaceCALIPER.glade", &err);
    if (err != NULL)
        *user << err->message;

    
    this->widgets[GtkElement::Window] = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow")); 

    
    this->widgets[GtkElement::returnCompilation] = GTK_WIDGET(gtk_builder_get_object(builder, "returnCompilation")); 
    this->widgets[GtkElement::entryCode] = GTK_WIDGET(gtk_builder_get_object(builder, "entryCode")); 
    this->widgets[GtkElement::imageShowed] = GTK_WIDGET(gtk_builder_get_object(builder, "imageShowed")); 

    
    GtkWidget * btn = GTK_WIDGET(gtk_builder_get_object(builder, "btnCompilExecuter")); 
    g_signal_connect(G_OBJECT(this->wdw), "clicked", G_CALLBACK(compilAndRunFunction), this);
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
    
}

void MainView::compilAndRunFunction(GtkWidget *widget, MainView *mainView) 
{
    mainView->updateFunction();
    ExecuteFunction exec(mainView->functionOpencv);
    std::string rtn = exec.compile() + "\n--- END COMPILATION\n";
    gtk_label_set_label(GTK_LABEL(mainView->widgets[GtkElement::returnCompilation]), rtn.c_str());
    rtn = exec.execute() + "\n--- END EXECUTION\n";
    gtk_label_set_label(GTK_LABEL(mainView->widgets[GtkElement::returnCompilation]), rtn.c_str());
}

void MainView::updateFunction() 
{
    this->functionOpencv->setCode(gtk_text_buffer_get_text(gtk_text_view_get_buffer(this->widgets[GtkElement::entryCode])));
}

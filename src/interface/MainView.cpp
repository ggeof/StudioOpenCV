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
    this->widgets[GtkElement::comboBoxChoseImage] = GTK_WIDGET(gtk_builder_get_object(builder, "cbAffichageImage")); 

    
    GtkWidget * btn = GTK_WIDGET(gtk_builder_get_object(builder, "btnCompilExecuter")); 
    g_signal_connect(G_OBJECT(btn), "clicked", G_CALLBACK(compilAndRunFunction), this);

    // Action List Image
    this->widgets[GtkElement::listImage] = GTK_WIDGET(gtk_builder_get_object(builder, "listImage")); 
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "btnAddImg")), "clicked", G_CALLBACK(
        +[](GtkWidget* widget, GtkListBox* list){
            GtkWidget* entry = gtk_entry_new();
            
            gtk_widget_set_margin_left(entry, 10);
            gtk_widget_set_margin_right(entry, 10);
            gtk_widget_set_margin_top(entry, 10);
            gtk_widget_set_margin_bottom(entry, 10);

            GtkWidget* row = gtk_list_box_row_new();
            gtk_container_add(GTK_CONTAINER(row), entry);
            gtk_container_add(GTK_CONTAINER(list), row);
            gtk_widget_show_all(row);
        }), GTK_LIST_BOX(this->widgets[GtkElement::listImage]));
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "btnDeleteImg")), "clicked", G_CALLBACK(
        +[](GtkWidget* widget, GtkListBox* list){
            GtkWidget* entry = gtk_entry_new();
            auto a = gtk_list_box_get_selected_row(list);
            if(a != NULL)
                gtk_container_remove(GTK_CONTAINER(list), GTK_WIDGET(a));
        }), GTK_LIST_BOX(this->widgets[GtkElement::listImage]));


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

    // Update du code
    auto buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(this->widgets[GtkElement::entryCode]));
    GtkTextIter start,
                end;

    gtk_text_buffer_get_end_iter(buf, &end);
    gtk_text_buffer_get_start_iter(buf, &start);

    this->functionOpencv->setCode(std::string(gtk_text_buffer_get_text(buf, &start, &end, false)));

    // Update matrice intermédiaire
    std::map<std::string, cv::Mat> imgs, imgsPrec = this->functionOpencv->getImages();

    GList* l = gtk_container_get_children(GTK_CONTAINER(this->widgets[GtkElement::listImage]));    
    GList* element = g_list_first(l);
    while (element) {
        std::string name(gtk_entry_get_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN((GtkWidget*)element->data)))));
        if(name != "")
        {
            if(imgsPrec.find(name) != imgsPrec.end())
                imgs[name] = imgsPrec[name];
            else
                imgs[name] = cv::Mat();
        }

        element = g_list_next(element);
    }

    this->functionOpencv->setImages(imgs);
}


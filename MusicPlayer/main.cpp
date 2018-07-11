#include <iostream>
#include <bass.h>
#include <string>
#include "GetFileName.h"
#include "MMPlayer.h"


int main(int argc,char **argv)
{
	{
		MMPlayer player(argc, argv);
		player.main_loop();
	}
	system("pause");

    /*BASS_Init(-1, 44100, 0, NULL, NULL);

    HSTREAM chan = BASS_StreamCreateFile(FALSE, "test.mp3", 0, 0, BASS_SAMPLE_FLOAT);
    if (chan == 0)
    {
        int errorCode = BASS_ErrorGetCode();
        printf("errorCode = %d    \n", errorCode);
        return 1;
    }
    printf("%d\n", chan);

    BASS_ChannelPlay(chan, FALSE);

    while(BASS_ChannelIsActive(chan))
    {
        sleep(1);
    }*/
    return 0;

}

/*

#include <gtk/gtk.h>
static void activate (GtkApplication *app , gpointer data);
static void print_hello (GtkApplication *app , gpointer data);

int gtk_test(int argc,char **argv)
{
    GtkApplication *app;
    int app_status;

    app = gtk_application_new("org.rain.gtk",G_APPLICATION_FLAGS_NONE);

    std::cout << app << std::endl;

    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);

    app_status = g_application_run(G_APPLICATION(app) , argc , argv);      //运行app
    g_object_unref(app);                                                  //销毁app


    return app_status;
}

static void activate (GtkApplication *app , gpointer data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;

    window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window) , "Application");
    gtk_window_set_default_size(GTK_WINDOW(window) , 200 , 200);


    button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add (GTK_CONTAINER (window), button_box);

    button = gtk_button_new_with_label ("Hello World");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_container_add (GTK_CONTAINER (button_box), button);

    gtk_widget_show_all(window);
}

static void print_hello (GtkApplication *app , gpointer data)
{
    g_print("hello\n");
}
*/

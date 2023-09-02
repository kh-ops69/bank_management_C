#include <gtk4/4.12.1/include/gtk-4.0/gtk/gtk.h>
#include <gtk4/4.12.1/include/gtk-4.0/gtk/gtkaboutdialog.h>
#include <gtk4/4.12.1/include/gtk-4.0/gtk/css/gtkcss.h>

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
    GtkWidget *window;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
    gtk_widget_show (window);
}

int main (int    argc,
      char **argv)
{
    GtkApplication *app;
    int status;
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}

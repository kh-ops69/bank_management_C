#include <gtk/gtk.h>

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
    g_print ("Hello World\n");
}

static void
print_input (GtkWidget *widget,
             gpointer   data)
{
    g_print (data);
}

static void on_show_text_from_buffer(GtkWidget *p_button, gpointer user_data) {
    gtk_button_set_label(GTK_BUTTON(p_button), "Clicked!");
    g_print("%s\n", (char *)user_data); // I wanna print out what it's been typed in here
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;

    /* create a new window, and set its title */
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");

    /* Here we construct the container that is going pack our buttons */
    grid = gtk_grid_new ();

    /* Pack the container in the window */
    gtk_window_set_child (GTK_WINDOW (window), grid);

    button = gtk_button_new_with_label ("LOGIN: ");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

    /* Place the first button in the grid cell (0, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

    button = gtk_button_new_with_label ("SIGN UP: ");
    g_signal_connect (button, "clicked", G_CALLBACK (on_show_text_from_buffer), NULL);

    /* Place the second button in the grid cell (1, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
    gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

    button = gtk_button_new_with_label ("QUIT");
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);

    /* Place the Quit button in the grid cell (0, 1), and make it
     * span 2 columns.
     */
    gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);


//    GtkWidget *p_grid = gtk_grid_new();
//    GtkWidget *p_button = gtk_button_new_with_label("Click me");

    gtk_grid_set_column_spacing(GTK_GRID(grid), 16);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 16);

    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    GtkEntryBuffer *p_buffer_1 = gtk_entry_buffer_new(NULL, -1);

    GtkWidget *p_entry_1 = gtk_entry_new_with_buffer(p_buffer_1);
    GtkWidget *p_entry_2 = gtk_entry_new_with_buffer(p_buffer_1);

    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(p_entry_1), 4, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(p_entry_2), 5, 1, 3, 1);
//    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(p_button), 0, 2, 3, 1);

    char *p_text_in_entry = g_strdup(gtk_entry_buffer_get_text(p_buffer_1));

    gtk_editable_get_text(GTK_EDITABLE(p_entry_1));
    g_print(p_entry_1);

    g_signal_connect(button, "clicked", G_CALLBACK(on_show_text_from_buffer),
                    p_text_in_entry);

    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_widget_show (window);

}

int
main (int    argc,
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

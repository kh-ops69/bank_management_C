#include <gtk/gtk.h>

GtkWidget *login_window = NULL;

// ... (other code)

static void login_page(GtkApplication *loginPage, gpointer usr_data) {
    // Create a new GtkApplicationWindow for the login form
    login_window = gtk_application_window_new(loginPage);
    gtk_window_set_title(GTK_WINDOW(login_window), "Login");

    // Create the login form and add it to the login_window
//    GtkWidget *login_form = create_login_form(); // Implement create_login_form() to create the login form widgets
//    gtk_window_set_child(GTK_WINDOW(login_window), login_form);

    // Show the login window
    gtk_widget_show(login_window);
}

static void print_hello(GtkWidget *p_button, gpointer user_data){
    g_print("HELLO WORLD\n");
}

// Define a callback function for the "clicked" event of the button
static void on_show_text_from_buffer(GtkWidget *p_button, gpointer user_data) {
    // Cast the user_data to a string
    char *p_text_in_entry = (char *)user_data;

    // Get the text from the GtkEntryBuffer associated with the GtkEntry
    const char *entry_text = gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(p_text_in_entry));

    // Print the text
    g_print("%s\n", entry_text);

    // Change the button label
    gtk_button_set_label(GTK_BUTTON(p_button), "Clicked!");
}

//static void login_page(GtkApplication *loginPage, gpointer usr_data) {
//    GtkWidget *gwindow;
//    GtkWidget *grid;
//    GtkWidget *button;
//    GtkWidget *p_entry_1;
//    GtkWidget *p_entry_2;
//
//    gwindow = gtk_application_window_new(loginPage);
//    gtk_window_set_title(GTK_WINDOW(gwindow), "Window");
//
//    grid = gtk_grid_new();
//    gtk_window_set_child(GTK_WINDOW(gwindow), grid);
//
//    gtk_grid_set_column_spacing(GTK_GRID(grid), 16);
//    gtk_grid_set_row_spacing(GTK_GRID(grid), 16);
//
//    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
//    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
//
//    GtkEntryBuffer *p_buffer_1 = gtk_entry_buffer_new(NULL, -1);
//    p_entry_1 = gtk_entry_new_with_buffer(p_buffer_1);
//    p_entry_2 = gtk_entry_new_with_buffer(p_buffer_1);
//
//    gtk_grid_attach(GTK_GRID(grid), p_entry_1, 0, 0, 3, 1);
//    gtk_grid_attach(GTK_GRID(grid), p_entry_2, 0, 1, 3, 1);
//
//    button = gtk_button_new_with_label("Submit");
//    g_signal_connect(button, "clicked", G_CALLBACK(on_show_text_from_buffer), p_buffer_1);
//
//    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 3, 1);
//
//    gtk_widget_show(gwindow);
//}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    button = gtk_button_new_with_label("LOGIN: ");
    g_signal_connect(button, "clicked", G_CALLBACK(login_page), NULL);

    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    button = gtk_button_new_with_label("ADMIN ACCESS: ");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

    button = gtk_button_new_with_label("QUIT");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);

    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

    // Show the main window
    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    GtkApplication *app, *directapp;
    int status, status2;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}





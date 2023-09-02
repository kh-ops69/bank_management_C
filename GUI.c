#include <gtk/gtk.h>

static void print_hello(GtkWidget *p_button, gpointer user_data) {
    g_print("HELLO WORLD\n");
}

static void on_show_text_from_buffer(GtkWidget *p_button, gpointer user_data) {
    GtkEntry *entry = GTK_ENTRY(user_data);
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
    const char *entry_text = gtk_entry_buffer_get_text(buffer);
    g_print("Text entered: %s\n", entry_text);
}

static void open_login_page(GtkButton *button, gpointer user_data) {
    GtkApplication *app = GTK_APPLICATION(user_data);

    // Create a new login window
    GtkWidget *login_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(login_window), "Login Page");

    // Create a grid for the login form
    GtkWidget *login_form = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(login_window), login_form);

    // Create an entry widget
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter your username");
    gtk_grid_attach(GTK_GRID(login_form), entry, 0, 0, 1, 1);

    // Create a button to submit
    GtkWidget *submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_show_text_from_buffer), entry);
    gtk_grid_attach(GTK_GRID(login_form), submit_button, 0, 1, 1, 1);

    // Show all widgets
    gtk_widget_show(login_window);
}

static void open_admin_access_page(GtkButton *button, gpointer user_data){
    GtkApplication *app = GTK_APPLICATION(user_data);
    GtkWidget *admin_access_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(admin_access_window), "ADMIN ACCESS ONLY");

    // Create a grid for the login form
    GtkWidget *admin_form = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(admin_access_window), admin_form);

    // Create an entry widget
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter your username");
    gtk_grid_attach(GTK_GRID(admin_form), entry, 0, 0, 1, 1);

    GtkWidget *entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Enter your password");
    gtk_grid_attach(GTK_GRID(admin_form), entry2, 1, 0, 1, 1);

    // Create a button to submit
    GtkWidget *submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_show_text_from_buffer), entry);
    gtk_grid_attach(GTK_GRID(admin_form), submit_button, 0, 1, 1, 1);

    // Show all widgets
    gtk_widget_show(admin_access_window);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *login_button;
    GtkWidget *admin_button;
    GtkWidget *quit_button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Main Window");

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    login_button = gtk_button_new_with_label("Login");
    g_signal_connect(login_button, "clicked", G_CALLBACK(open_login_page), app);
    gtk_grid_attach(GTK_GRID(grid), login_button, 0, 0, 1, 1);

    admin_button = gtk_button_new_with_label("Admin Access");
    g_signal_connect(admin_button, "clicked", G_CALLBACK(open_admin_access_page), app);
    gtk_grid_attach(GTK_GRID(grid), admin_button, 1, 0, 1, 1);

    quit_button = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped(quit_button, "clicked", G_CALLBACK(gtk_window_destroy), window);
    gtk_grid_attach(GTK_GRID(grid), quit_button, 0, 1, 2, 1);

    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

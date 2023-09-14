#include <gtk/gtk.h>
#include "library.c"
#include "passwordOps.c"

static void print_hello(GtkWidget *p_button, gpointer user_data) {
    g_print("HELLO WORLD\n");
}

const gchar *on_show_text_from_buffer(GtkWidget *p_button, gpointer user_data) {
    GtkEntry *entry = GTK_ENTRY(user_data);
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
    const char *entry_text = gtk_entry_buffer_get_text(buffer);
    g_print("Text entered: %s\n", entry_text);
    return entry_text;
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
    const gchar *login_username = gtk_entry_buffer_get_text(entry);

    GtkWidget *passw_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(passw_entry), "Enter your password: ");
    gtk_grid_attach(GTK_GRID(login_form), passw_entry, 1, 0, 1, 1);

    // Create a button to submit
    GtkWidget *submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_show_text_from_buffer), entry);
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_show_text_from_buffer), passw_entry);
    gtk_grid_attach(GTK_GRID(login_form), submit_button, 0, 1, 1, 1);

    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *res;
    int rc = sqlite3_open("test.db", &db);

    char *sql2 = "SELECT * FROM BANK_CUST WHERE account_bal = @acc_bal";


    rc = sqlite3_prepare_v2(db, sql2, -1, &res, 0);

    if (rc == SQLITE_OK) {

        int idx = sqlite3_bind_parameter_index(res, "@id");
        int value = 3;
        sqlite3_bind_int(res, idx, value);

    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW) {

        printf("%s: ", sqlite3_column_text(res, 0));
        printf("%s\n", sqlite3_column_text(res, 1));
        printf("%s\n", sqlite3_column_text(res, 2));

    }

    sqlite3_finalize(res);

    sqlite3_close(db);


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

    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *res;

    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "DROP TABLE IF EXISTS BANK_CUST;"
                "CREATE TABLE BANK_CUST(Id INT, Name TEXT, account_bal INT, passw_hash TEXT);"
               "INSERT INTO BANK_CUST VALUES(1, 'Krishna', 52642, 'Dusj#&!18');"
               "INSERT INTO BANK_CUST VALUES(2, 'Ram', 'YTGQU28h1');"
                "INSERT INTO BANK_CUST VALUES(3, 'Jagat', 'HDuahg@&12');"
                "INSERT INTO BANK_CUST VALUES(4, 'Harsha', '');"
                "INSERT INTO BANK_CUST VALUES(5, 'Taha', 350000);"
                "INSERT INTO BANK_CUST VALUES(6, 'Dhanush', 21000);"
                "INSERT INTO BANK_CUST VALUES(7, 'Vignesh', 41400);"
                "INSERT INTO BANK_CUST VALUES(8, 'Azeez', 21600);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    int last_id = sqlite3_last_insert_rowid(db);
    printf("The last Id of the inserted row is %d\n", last_id);

    char *sql1 = "SELECT * FROM Cars";
    rc = sqlite3_exec(db, sql1, callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    char *sql2 = "SELECT * FROM Cars WHERE Id = @id";

    rc = sqlite3_prepare_v2(db, sql2, -1, &res, 0);

    if (rc == SQLITE_OK) {

        int idx = sqlite3_bind_parameter_index(res, "@id");
        int value = 3;
        sqlite3_bind_int(res, idx, value);

    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW) {

        printf("%s: ", sqlite3_column_text(res, 0));
        printf("%s\n", sqlite3_column_text(res, 1));
        printf("%s\n", sqlite3_column_text(res, 2));

    }

    sqlite3_finalize(res);

    sqlite3_close(db);

    char some = '3';
    int a= some;
    int check_res;
    // declare and initialize string
    char str[] = "Geeks3.";

    // print string
    printf("%s\n", str);

    int length = 0;
    length = strlen(str);

    // displaying the length of string
    printf("Length of string str is %d\n", length);

    check_res = check(str, length);
    char* hashed_password = returnPasswordHash(str, length);
    printf("hashed password is: %s\n", hashed_password);
    printf("the return value is: %d\n", check_res);
    printf("ascii: %d", a);

    return status;
}

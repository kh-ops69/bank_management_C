#include <gtk/gtk.h>
#include "library.c"
#include "passwordOps.c"

typedef struct {
    GtkEntry *username_entry;
    GtkEntry *password_entry;
} LoginData;

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

static void on_submit_login(GtkButton *button, gpointer user_data) {

    LoginData *login_data = (LoginData *)user_data;

    GtkEntry *entry = login_data->username_entry;
    GtkEntry *passw_entry = login_data->password_entry;

    const gchar *login_username = gtk_editable_get_text(entry);
    const gchar *login_password = gtk_editable_get_text(passw_entry);

    int length = 0;
    length = strlen(login_password);

    // displaying the length of string
    printf("Length of string str is %d\n", length);

    int check_res = check(login_password, length);
    char* hashed_password = returnPasswordHash(login_password, length);
    printf("hashed password is: %s\n", hashed_password);
    printf("the return value is: %d\n", check_res);

    // TODO: Implement the database query using login_username
    sqlite3 *db;
    sqlite3_stmt *res;
    int rc = sqlite3_open("accounts.db", &db);

    char *sql2 = "SELECT * FROM BANK_CUST WHERE Name = ?";
    rc = sqlite3_prepare_v2(db, sql2, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res,1, login_username, -1,SQLITE_STATIC);

    }else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    int step = sqlite3_step(res);

    if (step == SQLITE_ROW) {

        printf("%s: ", sqlite3_column_text(res, 0));
        printf("%s\n", sqlite3_column_text(res, 1));
        printf("%s\n", sqlite3_column_text(res, 2));
        printf("%s\n", sqlite3_column_text(res, 3));
        char *reverse_hash = reversePasswordHash(sqlite3_column_text(res, 3), strlen(sqlite3_column_text(res, 3)));
        printf("reverse hash password is: %s\n", reverse_hash);

    }
    else{
        printf("no such user exists in the database: \n");
    }

    sqlite3_finalize(res);

    sqlite3_close(db);

    // For testing, you can print the username
    g_print("Username entered: %s\n", login_username);
}

static void return_error_message(GtkButton *button, gpointer user_data){
    GtkApplication *app = GTK_APPLICATION(user_data);
    GtkWidget *error_window = gtk_application_window_new(app);
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
//    GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);

    GtkWidget *passw_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(passw_entry), "Enter your password: ");
    gtk_grid_attach(GTK_GRID(login_form), passw_entry, 1, 0, 1, 1);

    LoginData *login_data = g_malloc(sizeof(LoginData));
    login_data->username_entry = GTK_ENTRY(entry);
    login_data->password_entry = GTK_ENTRY(passw_entry);

    // Create a button to submit
    GtkWidget *submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_show_text_from_buffer), entry);
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_show_text_from_buffer), passw_entry);
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_login), login_data);
    gtk_grid_attach(GTK_GRID(login_form), submit_button, 0, 1, 1, 1);

//    g_free(login_data);

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

    int rc = sqlite3_open("accounts.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

// TODO: creating an sql query for creation of new database with bank customer details: needs
// TODO: to be executed only once
//    char *sql = "DROP TABLE IF EXISTS BANK_CUST;"
//                "CREATE TABLE BANK_CUST(Id INT, Name TEXT, account_bal INT, passw_hash TEXT);"
//               "INSERT INTO BANK_CUST VALUES(1, 'Krishna', 52642, 'Dusj#&!18');"
//               "INSERT INTO BANK_CUST VALUES(2, 'Ram', 2729, 'YTGQU28h1');"
//                "INSERT INTO BANK_CUST VALUES(3, 'Jagat', 87279,'HDuahg@&12');"
//                "INSERT INTO BANK_CUST VALUES(4, 'Harsha',928280,'Juwn2@!nd');"
//                "INSERT INTO BANK_CUST VALUES(5, 'Taha', 350000, 'ndcj@*9S');"
//                "INSERT INTO BANK_CUST VALUES(6, 'Dhanush', 21000, 'sudbh12DJ');"
//                "INSERT INTO BANK_CUST VALUES(7, 'Vignesh', 41400, 'dch@#8nD');"
//                "INSERT INTO BANK_CUST VALUES(8, 'Azeez', 21600, 'HDjjh2@');";
//
//    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
//
//    if (rc != SQLITE_OK ) {
//
//        fprintf(stderr, "SQL error: %s\n", err_msg);
//
//        sqlite3_free(err_msg);
//        sqlite3_close(db);
//
//        return 1;
//    }
//   sqlite3_close(db);

    return status;
}

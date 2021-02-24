#include <gtk/gtk.h>

static void
print_clipboard(GtkWidget *widget,
                gpointer data) {
    // print text/plain
    GtkClipboard *clip = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    gchar *text = gtk_clipboard_wait_for_text(clip);
    printf("Clipboard text was:\n%s\n", text);

    // print rich text
    GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
    gsize *length = NULL;
    GdkAtom *format = NULL;
    gboolean available = gtk_clipboard_wait_is_rich_text_available(clip, buffer);
    printf("Clipboard rich text available: %s\n", available ? "true" : "false");
    guint8 *rst = gtk_clipboard_wait_for_rich_text(clip, buffer, format, length);
    printf("Clipboard rich text was:\n%s", rst);

    if (buffer == NULL)
        return;

    g_free(buffer);
    g_object_unref(format);
    g_free(length);
}

static void
activate(GtkApplication *app,
         gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Window");
    gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);

    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER (window), button_box);

    button = gtk_button_new_with_label("Fetch Clipboard");
    g_signal_connect (button, "clicked", G_CALLBACK(print_clipboard), NULL);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER (button_box), button);

    gtk_widget_show_all(window);
}

int
main(int argc,
     char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    return status;
}




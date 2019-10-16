/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief Cross platform message box invokation function.
 *
 * @copyright CaptainsLog is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include "captnmessage.h"
#include <assert.h>
#include <string.h>
#include <gtk/gtk.h>

int captain_message(int level, int buttons, const char *message)
{
    assert(gtk_init_check(NULL, NULL));

    GtkMessageType message_type;
    switch (level) {
        default:
        case CAPTMSG_INFO:
            message_type = GTK_MESSAGE_INFO;
            break;
        case CAPTMSG_WARNING:
            message_type = GTK_MESSAGE_WARNING;
            break;
        case CAPTMSG_ERROR:
            message_type = GTK_MESSAGE_ERROR;
            break;
    }

    GtkButtonsType buttons_type;
    switch (buttons) {
        default:
        case CAPTMSG_OK:
            buttons_type = GTK_BUTTONS_OK;
            break;
        case CAPTMSG_OK_CANCEL:
            buttons_type = GTK_BUTTONS_OK_CANCEL;
            break;
        case CAPTMSG_YES_NO:
            buttons_type = GTK_BUTTONS_YES_NO;
            break;
        case CAPTMSG_ABRT_RET_IGN:
            buttons_type = GTK_BUTTONS_NONE; /* We need to set our own for this one. */
            break;
    }

    GtkWidget *dialog = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, message_type, buttons_type, "%s", message);

    if (buttons == CAPTMSG_ABRT_RET_IGN) {
        gtk_dialog_add_button(GTK_DIALOG(dialog), "_Abort", GTK_RESPONSE_CANCEL);
        gtk_dialog_add_button(GTK_DIALOG(dialog), "_Retry", GTK_RESPONSE_OK);
        gtk_dialog_add_button(GTK_DIALOG(dialog), "_Ignore", GTK_RESPONSE_REJECT);
    }

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    while (gtk_events_pending()) {
        gtk_main_iteration();
    }

    switch (result) {
        case GTK_RESPONSE_OK:
        case GTK_RESPONSE_YES:
            return CAPTMSG_YES;
        case GTK_RESPONSE_REJECT:
            return CAPTMSG_IGN;
        default:
            return CAPTMSG_NO;
    }
}

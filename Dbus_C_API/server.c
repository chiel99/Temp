#include <stdio.h>
#include <unistd.h>
#include <dbus/dbus.h>
#include "common.h"

void reply_method_call(DBusMessage* msg, DBusConnection* conn)
{
    //DBusMessage* reply;
    DBusMessageIter args;
    char* param = "";

    /* Get the args in message */
    if (!dbus_message_iter_init(msg, &args))
        LOGE("Message has no argument\n");
    else if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args))
        LOGE("Argument is not a String\n");
    else
        dbus_message_iter_get_basic(&args, &param);

    LOGE("Get method call: %s\n", param);

    //reply = dbus_message_new_method_return(msg);
    
}

void listen(DBusConnection* conn)
{
    DBusMessage* msg;
    //DBusMessage* reply;

    while (1) {
        dbus_connection_read_write(conn, 0);
        msg = dbus_connection_pop_message(conn);
        if (msg == NULL) {
            sleep(1);
            continue;
        }

        if (dbus_message_is_method_call(msg, TEST_METHOD_TYPE, TEST_METHOD))
            reply_method_call(msg, conn);

        dbus_message_unref(msg);
    }
}

int main(int argc, char** args)
{
    DBusError err;
    DBusConnection* conn;
    int ret;

    /* Init the dbus_error */
    dbus_error_init(&err);

    /* Connect to the bus */
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err)) {
        LOGE("Connection error: %s\n", err.message);
        dbus_error_free(&err);
    }
    if (conn == NULL) {
        return -1;
    }

    /* Request a name on the bus */
    ret = dbus_bus_request_name(conn, TEST_DBUS_SERVER_NAME,
            DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
    if (dbus_error_is_set(&err)) {
        LOGE("Name error: %s\n", err.message);
        dbus_error_free(&err);
    }
    if (ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
        return -1;
    }

    /* Looping */
    listen(conn);

    /* Close the dbus connection */
    dbus_connection_close(conn);
    return 0;
}

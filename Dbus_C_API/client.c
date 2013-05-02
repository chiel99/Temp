#include <stdio.h>
#include <dbus/dbus.h>

#include "common.h"

int main(int argc, char** args)
{
    DBusMessage* msg;
    DBusMessageIter dmargs;
    DBusPendingCall *pending;
    DBusError err;
    DBusConnection* conn;
    int ret;
    char* param = "Hello";

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
    ret = dbus_bus_request_name(conn, TEST_DBUS_CLIENT_NAME,
            DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
    if (dbus_error_is_set(&err)) {
        LOGE("Name error: %s\n", err.message);
        dbus_error_free(&err);
    }
    if (ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
        return -1;
    }

    /* call server */
    msg = dbus_message_new_method_call(TEST_DBUS_SERVER_NAME,
            TEST_DBUS_SERVER_OBJ,
            TEST_METHOD_TYPE,
            TEST_METHOD);

    if (msg == NULL) {
        LOGE("Message null\n");
        return -1;
    }

    dbus_message_iter_init_append(msg, &dmargs);
    if (!dbus_message_iter_append_basic(&dmargs, DBUS_TYPE_STRING, &param)) {
        LOGE("OOM\n");
        return -1;
    }

    if (!dbus_connection_send_with_reply(conn, msg, &pending, -1)) {
        LOGE("OOM\n");
        return -1;
    }
    if (pending == NULL) {
        LOGE("Pending call null\n");
        return -1;
    }

    dbus_connection_flush(conn);
    LOGE("Message sent\n");

    dbus_message_unref(msg);

    /* Close the dbus connection */
    dbus_connection_close(conn);
    return 0;
}

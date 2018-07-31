#include <gmodule.h>
#include <stdio.h>

typedef void (* FuncProto)(const char *sub_message);

int
main(int argc, char **argv)
{
    FuncProto plugin_f;
    GModule *module;
    if (argc != 2) {
        puts("ERROR with parameters");
        return -1;
    }

    module = g_module_open(argv[1], G_MODULE_BIND_LAZY);
    if (!module) {
        puts("ERROR opening module");
        return 1;
    }

    if (!g_module_symbol (module, "say_hello", (gpointer *)&plugin_f)) {
        puts("ERROR loading symbol");
        g_module_close(module);
        return -1;
    }

    if (plugin_f == NULL) {
        puts("ERROR symbol painting to NULL");
        g_module_close(module);
        return -1;
    }

    plugin_f("plugin text");
    g_module_close(module);
    return 0;
}

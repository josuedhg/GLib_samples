#include "character.h"
void
player_death(GObject *player, gpointer user_data)
{
    gchar *name = my_character_get_name(MY_CHARACTER(player));
    g_print ("%s is death\n", name);
    *(gboolean*)user_data = TRUE;
    g_free(name);
}

int
main (int argc, char **args)
{
    gboolean isdeath = FALSE;
    Character *p[] = {my_character_new ("Player1"), my_character_new ("Player2")};
    g_signal_connect (p[0], "dead", G_CALLBACK (player_death), &isdeath);
    g_signal_connect (p[1], "dead", G_CALLBACK (player_death), &isdeath);
    while (!isdeath) {
        g_print("fight\n");
        my_character_atack(p[0], p[1]);
        my_character_heal(p[0]);
        if (isdeath)
            continue;
        my_character_atack(p[1], p[0]);
        my_character_heal(p[0]);
    }
    g_object_unref (p[0]);
    g_object_unref (p[1]);
}


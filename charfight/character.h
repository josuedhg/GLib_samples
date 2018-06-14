#ifndef __MY_CHARACTER_H__
#define __MY_CHARACTER_H__

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define MY_TYPE_CHARACTER my_character_get_type()

G_DECLARE_FINAL_TYPE (Character, my_character, MY, CHARACTER, GObject);

struct _Character {
    GObject parent;
    gchar *name;
    gint hp;
    gint mana;
};

Character * my_character_new (gchar *name);

void my_character_atack(Character *self, Character *enemy);

void my_character_heal(Character *self);

gchar *my_character_get_name(Character *self);

G_END_DECLS

#endif

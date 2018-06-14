#include "character.h"

enum
{
    NAME = 1,
    HP,
    MANA,
    N_PROPERTIES
};

enum
{
    DIED,
    N_SIGNALS
};

G_DEFINE_TYPE (Character, my_character, G_TYPE_OBJECT);

static void
my_character_set_property (GObject      *object,
                           guint         property_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
    Character *self = MY_CHARACTER (object);

    switch (property_id) {
        case NAME:
            g_free(self->name);
            self->name = g_value_dup_string(value);
            break;
        case HP:
            self->hp = g_value_get_int (value);
            break;
        case MANA:
            self->mana = g_value_get_int (value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
    }
}

static void
my_character_get_property (GObject    *object,
                           guint       property_id,
                           GValue     *value,
                           GParamSpec *pspec)
{
    Character *self = MY_CHARACTER (object);

    switch (property_id) {
        case NAME:
            g_value_set_string(value, self->name);
            break;
        case HP:
            g_value_set_int (value, self->hp);
            break;
        case MANA:
            g_value_set_int (value, self->mana);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
    }
}

static void
my_character_init (Character *self)
{
}

static void
my_character_class_init (CharacterClass *klass)
{
    GObjectClass *g_object_class = G_OBJECT_CLASS (klass);
    GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

    g_object_class->set_property = my_character_set_property;
    g_object_class->get_property = my_character_get_property;
    
    obj_properties[NAME] = g_param_spec_string ("name",
                                             "Name",
                                             "Character Name",
                                             NULL,
                                             G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);

    obj_properties[HP] = g_param_spec_int ("hp",
                                           "Hp",
                                           "Character Hit Points",
                                           0,
                                           200,
                                           200,
                                           G_PARAM_READWRITE);

    obj_properties[MANA] = g_param_spec_int ("mana",
                                             "Mana",
                                             "Character Mana Points",
                                             0,
                                             200,
                                             200,
                                             G_PARAM_READWRITE);

    g_object_class_install_properties (g_object_class,
                                      N_PROPERTIES,
                                      obj_properties);

    g_signal_new(
        "dead",                                /* signal_name */
        MY_TYPE_CHARACTER,                     /* itype */
        G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED, /* signal_flags */
        0,                                     /* class_offset */
        NULL,                                  /* accumulator */
        NULL,                                  /* accu_data */
        g_cclosure_marshal_VOID__VOID,         /* c_marshaller */
        G_TYPE_NONE,                           /* return_type */
        0);
}

Character *
my_character_new (gchar *name)
{
    return MY_CHARACTER(g_object_new (MY_TYPE_CHARACTER, "name", name, "hp", 200, "mana", 200, NULL));
}

void
my_character_atack (Character *self, Character *enemy)
{
    gint32 damage = g_random_int_range (0, 30);
    g_print ("%s make %d points of damage to %s\n", self->name, damage, enemy->name);
    if (enemy->hp - damage <= 0) {
        g_object_set (enemy, "hp", 0, NULL);
        g_signal_emit_by_name (enemy, "dead");
    } else {
        g_object_set (enemy, "hp", enemy->hp - damage, NULL);
    }
    g_print ("%s has %d hitpoints, %s has %d hitpoints\n", self->name, self->hp, enemy->name, enemy->hp);
}

void
my_character_heal (Character *self)
{
    if (self->mana > 20) {
        gint32 heal = g_random_int_range (0, 10);
        g_print ("%s heals %d hitpoints to himself\n", self->name, heal);
        if (self->hp + heal >= 200) {
            g_object_set (self, "hp", 200, NULL);
        } else {
            g_object_set (self, "hp", self->hp + heal, NULL);
        }
        g_object_set (self, "mana", self->mana - 20, NULL);
    }
}

gchar *my_character_get_name(Character *self)
{
    return g_strdup(self->name);
}

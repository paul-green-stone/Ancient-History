#include "../../include/Widgets/menu.h"
#include "../../include/Widgets/_widget.h"
#include "../../include/Widgets/widget.h"
#include "../../include/io.h"

#define MAX_WIDGETS_IN_THE_MENU 6

/* ================================================================ */

typedef struct menu {

    SDL_Renderer* context;

    /* Number of widgets in the menu */
    size_t num_widgets;

    /* A widget that has focus */
    struct widget_class* widgets[MAX_WIDGETS_IN_THE_MENU];
    int active_widget;
    int free_widget_slot;

    /* Color of a widget in a menu */
    SDL_Color widget_color;
    SDL_Color active_widget_color;

    /* Space between two consecutive widgets */
    int padding;

    Alignment alignment;
} Menu;

/* ================================================================ */


Menu* Menu_new(SDL_Renderer* context) {

    Menu* new_menu = NULL;

    if ((new_menu = calloc(1, sizeof(struct menu))) == NULL) {
        return NULL;
    }

    new_menu->context = context;
    new_menu->active_widget = -1;

    return new_menu;
}

/* ================================ */

int Menu_destroy(Menu** menu) {

    if ((menu == NULL) || (*menu == NULL)) {
        return -1;
    }

    for (int i = 0; i < MAX_WIDGETS_IN_THE_MENU; i++) {
        
        Widget_destroy((*menu)->widgets[i]);
    }
    
    free(*menu);

    return 0;
}

/* ================================ */

int Menu_pack(Menu* menu, void* _widget) {
    
    if (_widget == NULL) {
        return -1;
    }
    
    if (menu->num_widgets == MAX_WIDGETS_IN_THE_MENU) {
        return -2;
    }
    
    menu->widgets[menu->free_widget_slot++] = _widget;
    menu->num_widgets++;
    
    return 0;
}

/* ================================ */

int Menu_draw(const Menu* menu) {

    int status = 0;


    for (int i = 0; i < MAX_WIDGETS_IN_THE_MENU; i++) {
        
        if (menu->widgets[i] == NULL) {
            continue ;
        }

        if (menu->active_widget == i) {
            Text_setColor(Widget_getText(menu->widgets[i]), (SDL_Color*) &menu->active_widget_color);
        }
        else {
            Text_setColor(Widget_getText(menu->widgets[i]), (SDL_Color*) &menu->widget_color);
        }

        status += Widget_draw(menu->widgets[i], menu->context);
    }

    return status;
}

/* ================================ */

void Menu_update(Menu* menu) {
    
    if (menu->num_widgets <= 0) {
        return ;
    }

    if (Input_isKey_just_pressed(SDL_SCANCODE_UP)) {
        
        if ((menu->active_widget == -1) || (menu->active_widget == 0)) {
            menu->active_widget = menu->num_widgets - 1;
        }
        else {
            menu->active_widget -= 1;
        }
    }

    if (Input_isKey_just_pressed(SDL_SCANCODE_DOWN)) {

        if ((menu->active_widget == -1) || (menu->active_widget == menu->num_widgets - 1)) {
            menu->active_widget = 0;
        }
        else {
            menu->active_widget += 1;
        }
    }
}

/* ================================ */

void Menu_setActive_color(Menu* menu, SDL_Color* color) {
    menu->active_widget_color = *color;
}

/* ================================ */

void Menu_set_color(Menu* menu, SDL_Color* color) {
    menu->widget_color = *color;
}

/* ================================ */

size_t Menu_size(const Menu* menu) {
    return menu->num_widgets;
}

/* ================================================================ */

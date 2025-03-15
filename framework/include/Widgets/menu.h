#ifndef _SPARK_MENU_INTERFACE_H
#define _SPARK_MENU_INTERFACE_H

#include "widget.h"
#include "Button.h"

/* ================================================================ */

typedef struct menu Menu;

typedef enum {CENTERED} Alignment;

/* ================================================================ */

/**
 * Create a new menu for a specified rendering context.
 * 
 * @param context the menu will be associated with this renderer
 * 
 * @return Returns the `Menu*` or NULL on failure.
 */
Menu* Menu_new(SDL_Renderer* context);

/**
 * The function destroys a menu and reclaims the memory it occupies.
 * 
 * @param menu menu that needs to be destroyed
 * 
 * @return Returns 0 on success or -1 on failure.
 */
int Menu_destroy(Menu** menu);

/**
 * 
 */
void Menu_setMargin(Menu* menu, int margin);

/**
 * The function adds a widget to the menu.
 * 
 * @param menu menu into which the widget is to be added
 * @param widget widget to be added
 * 
 * @return Returns 0 on success or -1 on failure.
 */
int Menu_pack(Menu* menu, void* widget);

/**
 * The function draws a menu on the screen.
 * 
 * @param menu menu that needs to be drawn
 * 
 * @return Returns 0 on success or -1 on failure.
 */
int Menu_draw(const Menu* menu);

/**
 * The function updates the menu according to the user input. 
 * By default, it uses `UP` and `DOWN` arrow keys.
 * 
 * @param menu menu to update
 * 
 * @return None.
 */
void Menu_update(Menu* menu);

/**
 * 
 */
void Menu_setActive_color(Menu* menu, SDL_Color* color);

/**
 * 
 */
void Menu_set_color(Menu* menu, SDL_Color* color);

/**
 * 
 */
void Menu_logF(const Menu* menu);

/**
 * 
 */
void Menu_logB(const Menu* menu);

/**
 *
 */
size_t Menu_size(const Menu* menu);

/* ================================================================ */

#endif /* _SPARK_MENU_INTERFACE_H */

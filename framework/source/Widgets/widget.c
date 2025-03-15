#include "../../include/Widgets/_widget.h"
#include "../../include/Widgets/widget.h"
#include "../../include/Math/Vector2D.h"

/* ================================================================ */

void* Widget_create(const void* _widget_class, ...) {

    const struct widget_class* widget_class = _widget_class;
    void* widget = NULL;

    if ((widget = calloc(1, widget_class->size)) == NULL) {
        return NULL;
    }

    *(const struct widget_class**) widget = widget_class;

    if (widget_class->ctor != NULL) {

        va_list ap;

        va_start(ap, _widget_class);
        widget = widget_class->ctor(widget, &ap);
        va_end(ap);
    }

    return widget;
}

/* ================================ */

void Widget_destroy(void* widget) {

    const struct widget_class** widget_class_p = widget;

    if ((widget != NULL) && (*widget_class_p != NULL) && ((*widget_class_p)->dtor != NULL)) {
        
        widget = (*widget_class_p)->dtor(widget);
        
        free(widget);
    }
}

/* ================================ */

void Widget_log(const void* widget, FILE* stream) {

    const struct widget_class* const* widget_class_p = widget;

    if ((widget != NULL) && (*widget_class_p != NULL) && ((*widget_class_p)->dtor != NULL)) {

        fprintf(stream, "%-16s: %s\n", "Widget Type", (*widget_class_p)->name);

        (*widget_class_p)->log(widget, stream);
    }
}

/* ================================ */

int Widget_draw(const void* widget, SDL_Renderer* context) {

    const struct widget_class* const* widget_class_p = widget;

    if ((widget != NULL) && (*widget_class_p != NULL) && ((*widget_class_p)->draw != NULL)) {

        return (*widget_class_p)->draw(widget, context);
    }

    /* Let's suppose -12 indicates that the widget doesn't impelement a method */
    return -12;
}

/* ================================ */

const char* Widget_getLable(const void* widget) {

    const struct widget_class* const* widget_class_p = widget;

    if ((widget != NULL) && (*widget_class_p != NULL) && ((*widget_class_p)->get_label != NULL)) {

        return (*widget_class_p)->get_label(widget);
    }

    return "-12";
}

/* ================================ */

Text* Widget_getText(const void* widget) {

    const struct widget_class* const* widget_class_p = widget;

    if ((widget != NULL) && (*widget_class_p != NULL) && ((*widget_class_p)->get_text != NULL)) {

        return (*widget_class_p)->get_text(widget);
    }

    return NULL;
}

/* ================================ */

Vector2D* Widget_getPosition(const void* widget) {

    const struct widget_class* const* widget_class_p = widget;

    if ((widget != NULL) && (*widget_class_p != NULL) && ((*widget_class_p)->get_position != NULL)) {

        return (*widget_class_p)->get_position(widget);
    }

    return NULL;
}

/* ================================================================ */

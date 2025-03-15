#include "../../include/Widgets/widget.h"
#include "../../include/Widgets/_widget.h"
#include "../../include/text.h"
#include "../../include/Math/Vector2D.h"

/* ================================================================ */

struct button {

    const void* widget_type;

    Text* label;
    Vector2D position;
};

/* ================================ */

static void* Button_ctor(void* _self, va_list* app) {

    struct button* self = _self;

    /* ================================================ */
    /* ====== Extracting arguments from the list ====== */
    /* ================================================ */

    SDL_Renderer* context = va_arg(*app, SDL_Renderer*);
    TTF_Font* font = va_arg(*app, TTF_Font*);
    SDL_Color* color = va_arg(*app, SDL_Color*);
    const char* str = va_arg(*app, const char*);
    Vector2D* position = va_arg(*app, Vector2D*);

    if ((self->label = Text_new(context, font, color, str)) == NULL) {
        return NULL;
    }

    self->position = *position;

    return self;
}

/* ================================ */

static void* Button_dtor(void* _self) {

    struct button* self = _self;

    Text_destroy(&self->label);

    return self;
}

/* ================================ */

static const char* Button_getLabel(const void* _self) {

    const struct button* self = _self;

    return self->label->content;
}

/* ================================ */

static Text* Button_getText(const void* _self) {

    const struct button* self = _self;

    return self->label;
}

/* ================================ */

static void Button_log(const void* _self, FILE* stream) {

    const struct button* self = _self;

    fprintf(stream, "%-16s: %p\n", "&Label", Button_getText(_self));
    fprintf(stream, "%-16s: %s\n", "Label", Button_getLabel(_self));
    fprintf(stream, "%-16s: [%d, %d, %d, %d]\n", "Lable Color", self->label->color.r, self->label->color.g, self->label->color.b, self->label->color.a);
    fprintf(stream, "%-16s: %d\n", "Width", self->label->width);
    fprintf(stream, "%-16s: %d\n", "Height", self->label->height);
    fprintf(stream, "%-16s: [%.0f, %.0f]\n", "Position", self->position.x, self->position.y);
}

/* ================================ */

static int Button_draw(const void* _self, SDL_Renderer* context) {

    const struct button* self = _self;

    return Text_draw(self->label, &(SDL_Rect) {(int) self->position.x, (int) self->position.y, self->label->width, self->label->height});
}

/* ================================ */

static Vector2D* Button_getPosition(const void* _self) {

    const struct button* self = _self;

    return (Vector2D*) &self->position;
}

/* ================================ */

static const struct widget_class _Button = {

	.size = sizeof(struct button),
	.ctor = Button_ctor,
    .dtor = Button_dtor,
    .log = Button_log,
    .draw = Button_draw,
    .get_label = Button_getLabel,
    .get_text = Button_getText,
    .get_position = Button_getPosition,

    .name = "Button",
};

const void* Button = &_Button;

/* ================================================================ */

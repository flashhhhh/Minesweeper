enum ButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT,
    BUTTON_SPRITE_MOUSE_LEFT_DOWN,
    BUTTON_SPRITE_MOUSE_RIGHT_DOWN,
    BUTTON_SPRITE_MOUSE_LEFT_UP,
};

class BUTTON {
    private:
        SDL_Point cursorPosition;
        ButtonSprite currentSprite;
    
    public:
        BUTTON();
        void setPosition(int x, int y);
        void handleEvent(SDL_Event* event);
        pair<ButtonSprite, SDL_Point> processClick();
};

// control mouse's cursor
BUTTON button;

BUTTON::BUTTON() {
    cursorPosition.x = -1;
    cursorPosition.y = -1;
    currentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void BUTTON::setPosition(int x, int y) {
    cursorPosition.x = x;
    cursorPosition.y = y;
}

void BUTTON::handleEvent(SDL_Event* event) {
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        setPosition(x, y);
        if (event->button.button == SDL_BUTTON_LEFT) currentSprite = BUTTON_SPRITE_MOUSE_LEFT_DOWN;
        else if (event->button.button == SDL_BUTTON_RIGHT) currentSprite = BUTTON_SPRITE_MOUSE_RIGHT_DOWN;
    }
    else if (event->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        setPosition(x, y);
        if (event->button.button == SDL_BUTTON_LEFT) currentSprite = BUTTON_SPRITE_MOUSE_LEFT_UP;
    }
}

pair<ButtonSprite, SDL_Point> BUTTON::processClick() {
    pair<ButtonSprite, SDL_Point> result;

    result.first = currentSprite;
    result.second = cursorPosition;

    if (result.first != BUTTON_SPRITE_MOUSE_OUT) {
        cursorPosition.x = -1;
        cursorPosition.y = -1;
        currentSprite = BUTTON_SPRITE_MOUSE_OUT;
    }

    return result;
}
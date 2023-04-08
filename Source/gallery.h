class Gallery {
    public:
        Gallery();
        ~Gallery();
        bool loadImage(string path);
        bool loadFromRenderedText(string textureText, SDL_Color color);
        void free();
        void render(int x, int y, int w, int h);
    
    private:
        SDL_Texture* texture;
};

Gallery gallery;

Gallery::Gallery() {
    texture = NULL;
}

Gallery::~Gallery() {
    free();
}

// load image to gallery's texture
bool Gallery::loadImage(string path) {
    free();
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL) {
        cout << "Unable to load image " << path.c_str() << "! SDL_Image Error: " << IMG_GetError() <<'\n';
        return 0;
    }

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if (texture == NULL) {
        cout << "Unable to create texture from " << path.c_str() <<"! SDL Error: " << SDL_GetError() <<'\n';
        return 0;
    }

    SDL_FreeSurface(loadedSurface);
    return 1;
}

// load string text to gallery's texture
bool Gallery::loadFromRenderedText(string textureText, SDL_Color textColor) {
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (textSurface == NULL) {
        cout << "Unable to render text surface! SDL_TTF Error: " << TTF_GetError() <<'\n';
        return 0;
    }

    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (texture == NULL) {
        cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() <<'\n';
        return 0;
    }

    SDL_FreeSurface(textSurface);
    return 1;
}

// release gallery's texture
void Gallery::free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

// render gallery's texture
void Gallery::render(int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
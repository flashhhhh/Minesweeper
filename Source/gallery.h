enum textureName {
    FREE, number1, number2, number3, number4, number5, number6, number7, number8, 
    LIGHT_FLAG, DARK_FLAG, LIGHT_BOMB, DARK_BOMB,
    EASY_BACKGROUND, MEDIUM_BACKGROUND, HARD_BACKGROUND, START_GAME_BACKGROUND,
    EASY_MUTE_BACKGROUND, MEDIUM_MUTE_BACKGROUND, HARD_MUTE_BACKGROUND,
    LIGHT_MODE_CELL, DARK_MODE_CELL, LIGHT_ZERO_CELL, DARK_ZERO_CELL,
};

class Gallery {
    public:
        Gallery();
        ~Gallery();
        void loadImage(string path);
        void loadText(string textureText, SDL_Color color);
        void updateTextureList(textureName name, string path);
        void free();
        void render(textureName name, int x, int y, int w, int h);
        void render(textureName name, SDL_Rect *rect);
    
    private:
        int numTextures;
        vector<SDL_Texture*> texture;
};

Gallery gallery;

Gallery::Gallery() {
    numTextures = 30;

    texture.resize(numTextures);
    for (int i = 0; i < numTextures; ++i) texture[i] = NULL;
}

Gallery::~Gallery() {
    free();
}

// load image to gallery's texture
void Gallery::loadImage(string path) {
    free();

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL) cout << "Unable to load image " << path.c_str() << "! SDL_Image Error: " << IMG_GetError() <<'\n';

    //SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
    texture[FREE] = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if (texture[FREE] == NULL) cout << "Unable to create texture from " << path.c_str() <<"! SDL Error: " << SDL_GetError() <<'\n';

    SDL_FreeSurface(loadedSurface);
}

// load string text to gallery's texture
void Gallery::loadText(string textureText, SDL_Color textColor) {
    free();

    SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, textureText.c_str(), textColor);
    texture[FREE] = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);
}

void Gallery::updateTextureList(textureName name, string path) {
    if (texture[name] != NULL) {
        SDL_DestroyTexture(texture[name]);
        texture[name] = NULL;
    }

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    texture[name] = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    SDL_FreeSurface(loadedSurface);
}

// release gallery's texture
void Gallery::free() {
    if (texture[FREE] != NULL) {
        SDL_DestroyTexture(texture[FREE]);
        texture[FREE] = NULL;
    }
}

// render gallery's texture
void Gallery::render(textureName name, int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture[name], NULL, &rect);
}

// render gallery's texture
void Gallery::render(textureName name, SDL_Rect *rect) {
    SDL_RenderCopy(renderer, texture[name], NULL, rect);
}

void createGalleryList() {
    gallery.updateTextureList(number1, "../Image/1.png");
    gallery.updateTextureList(number2, "../Image/2.png");
    gallery.updateTextureList(number3, "../Image/3.png");
    gallery.updateTextureList(number4, "../Image/4.png");
    gallery.updateTextureList(number5, "../Image/5.png");
    gallery.updateTextureList(number6, "../Image/6.png");
    gallery.updateTextureList(number7, "../Image/7.png");
    gallery.updateTextureList(number8, "../Image/8.png");

    gallery.updateTextureList(LIGHT_FLAG, "../Image/light_flag.png");
    gallery.updateTextureList(DARK_FLAG, "../Image/dark_flag.png");

    gallery.updateTextureList(LIGHT_BOMB, "../Image/light_bomb.png");
    gallery.updateTextureList(DARK_BOMB, "../Image/dark_bomb.png");
    
    gallery.updateTextureList(EASY_BACKGROUND, "../Image/easy_background.png");
    gallery.updateTextureList(MEDIUM_BACKGROUND, "../Image/medium_background.png");
    gallery.updateTextureList(HARD_BACKGROUND, "../Image/hard_background.png");

    gallery.updateTextureList(EASY_MUTE_BACKGROUND, "../Image/easy_mute_background.png");
    gallery.updateTextureList(MEDIUM_MUTE_BACKGROUND, "../Image/medium_mute_background.png");
    gallery.updateTextureList(HARD_MUTE_BACKGROUND, "../Image/hard_mute_background.png");

    gallery.updateTextureList(START_GAME_BACKGROUND, "../Image/start_game_background.png");

    gallery.updateTextureList(LIGHT_MODE_CELL, "../Image/light_mode_cell.png");
    gallery.updateTextureList(DARK_MODE_CELL, "../Image/dark_mode_cell.png");
    gallery.updateTextureList(LIGHT_ZERO_CELL, "../Image/light_zero_cell.png");
    gallery.updateTextureList(DARK_ZERO_CELL, "../Image/dark_zero_cell.png");
}

textureName changeNumberToTextureName(int number) {
    if (number == 1) return number1;
    if (number == 2) return number2;
    if (number == 3) return number3;
    if (number == 4) return number4;
    if (number == 5) return number5;
    if (number == 6) return number6;
    if (number == 7) return number7;
    if (number == 8) return number8;
    return FREE;
}
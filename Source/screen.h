SDL_Window* window = NULL;
SDL_Renderer* renderer;
TTF_Font* gFont;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

bool initEverything() {
    // Create SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() <<'\n';
        return 0;
    }

    // Create PNG
    int imgFlags = IMG_INIT_PNG;
    if ( !(IMG_Init(imgFlags) & imgFlags) ) {
        cout << "SDL_Image could not initialize! SDL_Image Error: " << IMG_GetError() <<'\n';
        return 0;
    }

    // Create TTF
    if (TTF_Init() == -1) {
        cout << "SDL_TTF could not initialize! SDL_TTF Error: " << TTF_GetError() <<'\n';
        return 0;
    }

    gFont = TTF_OpenFont("../Font/number_font.ttf", 24);
    if (gFont == NULL) {
        cout << "Failed to load bahnschrift font! SDL_TTF Error: " << TTF_GetError() <<'\n';
        return 0;
    }

    return 1;
}

void closeEverthing() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void drawPoint(int x, int y, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawPoint(renderer, x, y);
}

void drawLine(int x, int y, int z, int t, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawLine(renderer, x, y, z, t);
}

void drawRectangle(int x, int y, int w, int h, int r, int g, int b, int a) {
    SDL_Rect fillRect = {x, y, w, h};
    SDL_SetRenderDrawColor( renderer, r, g, b, a);        
    SDL_RenderFillRect(renderer, &fillRect);
}

void drawRectangle(SDL_Rect fillRect, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a);        
    SDL_RenderFillRect(renderer, &fillRect);
}

bool insideRectangle(int x, int y, int a, int b, int w, int h) {
    int c = a + w; int d = b + h;
    return (x >= a && x <= c && y >= b && y <= d);
}

string changeNumberToString(int number) {
    stringstream ss;
    string str;

    ss << number; ss >> str;
    return str;
}
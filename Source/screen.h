SDL_Window* window = NULL;
SDL_Renderer* renderer;
TTF_Font* gFont;
Mix_Music* music;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

// init SDL and properties
void initEverything() {
    // Create SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create window
    window = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Create PNG
    IMG_Init(IMG_INIT_PNG);

    // Create TTF
    TTF_Init();
    gFont = TTF_OpenFont("Font/main_font.ttf", 24);

    // Create Music and Sound
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 );
}

// finish SDL
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

void drawLine(SDL_Rect rect, int r, int g, int b, int a) {
    int x = rect.x; int y = rect.y; int z = rect.x + rect.w; int t = rect.y + rect.h;

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

// check whether point (x,y) is inside rectangle (a,b,a+w,b+h)
bool insideRectangle(int x, int y, int a, int b, int w, int h) {
    int c = a + w; int d = b + h;
    return (x >= a && x <= c && y >= b && y <= d);
}

bool insideRectangle(int x, int y, SDL_Rect rect) {
    int a = rect.x; int b = rect.y; int c = a + rect.w; int d = b + rect.h;
    return (x >= a && x <= c && y >= b && y <= d);
}

string changeNumberToString(int number) {
    stringstream ss;
    string str;

    ss << number; ss >> str;
    return str;
}

// random integer number between l and r
int Rand(int l, int r) {
    return rand() % (r - l + 1) + l;
}

// Change current time to form minute : second
string changeTime(Uint32 currentTime) {
    int minute = currentTime /60; int second = currentTime %60;

    string minuteText = changeNumberToString(minute);
    while (minuteText.size() < 2) minuteText = "0" + minuteText;

    string secondText = changeNumberToString(second);
    while (secondText.size() < 2) secondText = "0" + secondText;

    string timeText = minuteText + ':' + secondText;
    return timeText;
}
#include "class.h"


// display window size definition
static const int window_height = 1000 * 0.6;
static const int window_width = 600 * 0.6;

// const value
static int SPEED = 3;


// SDL command box definition
static SDL_Window* displayWindow;
static SDL_Renderer* renderer;

// assert path definition
static const char* again_png_path = "again.png";
static const char* background_png_path = "background.png";
static const char* bomb_png_path = "bomb.png";
static const char* bomb_supply_png_path = "bomb_supply.png";
static const char* bullet1_png_path = "bullet1.png";
static const char* bullet2_png_path = "bullet2.png";
static const char* bullet_supply_png_path = "bullet_supply.png";
static const char* enemy1_png_path = "enemy1.png";
static const char* enemy1_down1_png_path = "enemy1_down1.png";
static const char* enemy1_down2_png_path = "enemy1_down2.png";
static const char* enemy1_down3_png_path = "enemy1_down3.png";
static const char* enemy1_down4_png_path = "enemy1_down4.png";
static const char* enemy2_png_path = "enemy2.png";
static const char* enemy2_down1_png_path = "enemy2_down1.png";
static const char* enemy2_down2_png_path = "enemy2_down2.png";
static const char* enemy2_down3_png_path = "enemy2_down3.png";
static const char* enemy2_down4_png_path = "enemy2_down4.png";
static const char* enemy2_hit_png_path = "enemy2_hit.png";
static const char* enemy3_down1_png_path = "enemy3_down1.png";
static const char* enemy3_down2_png_path = "enemy3_down2.png";
static const char* enemy3_down3_png_path = "enemy3_down3.png";
static const char* enemy3_down4_png_path = "enemy3_down4.png";
static const char* enemy3_down5_png_path = "enemy3_down5.png";
static const char* enemy3_down6_png_path = "enemy3_down6.png";
static const char* enemy3_hit_png_path = "enemy3_hit.png";
static const char* enemy3_n1_png_path = "enemy3_n1.png";
static const char* enemy3_n2_png_path = "enemy3_n2.png";
static const char* gameover_png_path = "gameover.png";
static const char* life_png_path = "life.png";
static const char* me1_png_path = "me1.png";
static const char* me2_png_path = "me2.png";
static const char* me_destroy_1_png_path = "me_destroy_1.png";
static const char* me_destroy_2_png_path = "me_destroy_2.png";
static const char* me_destroy_3_png_path = "me_destroy_3.png";
static const char* me_destroy_4_png_path = "me_destroy_4.png";
static const char* pause_nor_png_path = "pause_nor.png";
static const char* pause_pressed_png_path = "pause_pressed.png";
static const char* resume_nor_png_path = ".resume_nor.png";
static const char* resume_pressed_png_path = "resume_pressed.png";
static const char* me_down_wav_path = "me_down.wav";
static const char* font_ttf_path = "font.ttf";
static const char* back_wave_path = "game_music.ogg";

// assert serface definition
static SDL_Surface* again_png = IMG_Load(again_png_path);
static SDL_Surface* background_png = IMG_Load(background_png_path);
static SDL_Surface* bomb_png = IMG_Load(bomb_png_path);
static SDL_Surface* bomb_supply_png = IMG_Load(bomb_supply_png_path);
static SDL_Surface* bullet1_png = IMG_Load(bullet1_png_path);
static SDL_Surface* bullet2_png = IMG_Load(bullet2_png_path);
static SDL_Surface* bullet_supply_png = IMG_Load(bullet_supply_png_path);
static SDL_Surface* enemy1_png = IMG_Load(enemy1_png_path);
static SDL_Surface* enemy1_down1_png = IMG_Load(enemy1_down1_png_path);
static SDL_Surface* enemy1_down2_png = IMG_Load(enemy1_down2_png_path);
static SDL_Surface* enemy1_down3_png = IMG_Load(enemy1_down3_png_path);
static SDL_Surface* enemy1_down4_png = IMG_Load(enemy1_down4_png_path);
static SDL_Surface* enemy2_png = IMG_Load(enemy2_png_path);
static SDL_Surface* enemy2_down1_png = IMG_Load(enemy2_down1_png_path);
static SDL_Surface* enemy2_down2_png = IMG_Load(enemy2_down2_png_path);
static SDL_Surface* enemy2_down3_png = IMG_Load(enemy2_down3_png_path);
static SDL_Surface* enemy2_down4_png = IMG_Load(enemy2_down4_png_path);
static SDL_Surface* enemy2_hit_png = IMG_Load(enemy2_hit_png_path);
static SDL_Surface* enemy3_down1_png = IMG_Load(enemy3_down1_png_path);
static SDL_Surface* enemy3_down2_png = IMG_Load(enemy3_down2_png_path);
static SDL_Surface* enemy3_down3_png = IMG_Load(enemy3_down3_png_path);
static SDL_Surface* enemy3_down4_png = IMG_Load(enemy3_down4_png_path);
static SDL_Surface* enemy3_down5_png = IMG_Load(enemy3_down5_png_path);
static SDL_Surface* enemy3_down6_png = IMG_Load(enemy3_down6_png_path);
static SDL_Surface* enemy3_hit_png = IMG_Load(enemy3_hit_png_path);
static SDL_Surface* enemy3_n1_png = IMG_Load(enemy3_n1_png_path);
static SDL_Surface* enemy3_n2_png = IMG_Load(enemy3_n2_png_path);
static SDL_Surface* gameover_png = IMG_Load(gameover_png_path);
static SDL_Surface* life_png = IMG_Load(life_png_path);
static SDL_Surface* me1_png = IMG_Load(me1_png_path);
static SDL_Surface* me2_png = IMG_Load(me2_png_path);
static SDL_Surface* me_destroy_1_png = IMG_Load(me_destroy_1_png_path);
static SDL_Surface* me_destroy_2_png = IMG_Load(me_destroy_2_png_path);
static SDL_Surface* me_destroy_3_png = IMG_Load(me_destroy_3_png_path);
static SDL_Surface* me_destroy_4_png = IMG_Load(me_destroy_4_png_path);
static SDL_Surface* pause_nor_png = IMG_Load(pause_nor_png_path);
static SDL_Surface* pause_pressed_png = IMG_Load(pause_pressed_png_path);
static SDL_Surface* resume_nor_png = IMG_Load(resume_nor_png_path);
static SDL_Surface* resume_pressed_png = IMG_Load(resume_pressed_png_path);

// assert texture definition
TTF_Font * font;

// game flag definition
GAME_STATUS game_flag = GAME_RESET;
PLAYER_STATUS player_flag = PLAYER_PLAYING;
SENCE_STATUS sence_flag = MENU;
static int time_count = 0;
static int player_health = 100;
static Player role;
// player status definition



// class definition
static std::vector<std::pair<int, int>> wall_vector = { 
    { 564*0.6 , 221*0.6},
{ 27*0.6, 352*0.6},
    { 526*0.6, 426 *0.6},
{ 119*0.6, 250*0.6},
{ 367*0.6, 633*0.6},
{ 421*0.6, 654*0.6},
{ 287*0.6, 713*0.6},
{ 600*0.6, 349*0.6
},
{ 378*0.6, 876*0.6},
{ 214*0.6, 25*0.6}
};

static std::vector<Enemy> enemy;
static std::vector<Bullet>bullet;

void init_game()
{
    while (game_flag == GAME_RESET) {
        Mix_AllocateChannels(10);
        reset_game();
    }
}

void reset_game()
{
    game_flag = GAME_PLAY;
    player_flag = PLAYER_PLAYING;
    sence_flag = MENU;
    time_count = 0;
    play_back_music();
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    font = TTF_OpenFont(font_ttf_path, 50);
    if (font == NULL) {
        SDL_Log("Can not open font, %s", TTF_GetError());
    }
	displayWindow = SDL_CreateWindow("Plane", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(displayWindow, -1, SDL_RENDERER_ACCELERATED);

    event_loop();
    SDL_DestroyWindow(displayWindow);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
    SDL_Quit();
}

void play_back_music()
{
    Mix_VolumeMusic(100);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    auto sound = Mix_LoadMUS(back_wave_path);
    Mix_PlayMusic(sound, -1);
}

void play_hit_music()
{
    auto chunk = Mix_LoadWAV(me_down_wav_path);
    
    Mix_PlayChannel(-1, chunk, 1);
}

void display_menu()
{
    display_back();
    display_text("WELCOME TO THE GAME !", { 0xff,0xff,0xff,0xff }, { 90,240,180,48 });
    display_text("Press <SPACE> to start game.", { 0xff,0xff,0xff,0xff }, { 60,300,240,30 });
}

void display_game()
{
    display_back();
    display_wall();
    display_enemy();
    display_bullet();
    display_player();
    display_time();
    display_health();
}

void display_win()
{
    display_back();
    display_text("YOU WIN!", { 0xff,0xff,0xff,0xff }, { 90,240,180,48  });
    display_text("Press <SPACE> to restart game.", { 0xff,0xff,0xff,0xff }, {60,300,240,30});
    display_text("Press <ENTER> to end game.", { 0xff,0xff,0xff,0xff }, {60,330,240,30});
}

void display_loss()
{
    display_back();
    display_text("YOU LOSS!", { 0xff,0xff,0xff,0xff }, { 90,240,180,48 });
    display_text("Press <SPACE> to restart game.", { 0xff,0xff,0xff,0xff }, { 60,300,240,30 });
    display_text("Press <ENTER> to end game.", { 0xff,0xff,0xff,0xff }, { 60,330,240,30 });
}

void display_text(const char* str, SDL_Color color, SDL_Rect dst)
{
    auto text = TTF_RenderUTF8_Blended(font, str, color);
    auto text_texture = SDL_CreateTextureFromSurface(renderer, text);
    SDL_RenderCopy(renderer, text_texture, NULL, &dst);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(text_texture);
    
}

void display_img(SDL_Surface* surface,  SDL_Rect dst)
{
    auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}




void display_player()
{
    display_img(me2_png, { role.x,role.y,PLANE_SIZE,PLANE_SIZE });
}

void display_enemy()
{
    std::vector<Enemy> t;
    for (auto it = enemy.begin();it!=enemy.end();it++) {
        display_img(enemy2_png, { it->x,it->y,PLANE_SIZE,PLANE_SIZE });
        it->auto_move();
        it->auto_shoot();
        if (pow(it->x - role.x, 2) + pow(it->y - role.y, 2) < PLANE_SIZE * PLANE_SIZE)
        {
            player_health -= 50;
            play_hit_music();
            if (player_health <= 0) {
                sence_flag = LOSS;
            }
            continue;
        }
        t.push_back(*it);
    }
    enemy = t;
}

bool is_bullet_exist(Bullet it) {
    bool flag_ = true;

    // out of sence
    if (!(it.x > 0 && it.x < 360 && it.y > 0 && it.y < 600))
        flag_ = false;

    // meet wall
    for (auto itt : wall_vector) {
        if (pow(it.x - itt.first, 2) + pow(it.y - itt.second, 2) < (PLANE_SIZE + PLANE_SIZE / 4) / 2 * (PLANE_SIZE + PLANE_SIZE / 4) / 2)
        {
            flag_ = false;
            break;
        }
    }

    // meet player
    if (pow(it.x - role.x, 2) + pow(it.y - role.y, 2) < (PLANE_SIZE + PLANE_SIZE / 4) / 2 * (PLANE_SIZE + PLANE_SIZE / 4) / 2)
    {
        flag_ = false;
        player_health -= 10;
        play_hit_music();

        if (player_health <= 0) {
            sence_flag = LOSS;
        }
    }
    return flag_;
}

void display_bullet()
{
    std::vector<Bullet> t;
    for (auto it = bullet.begin(); it != bullet.end(); it++) {
        display_img(bullet2_png, { it->x,it->y,PLANE_SIZE/4,PLANE_SIZE/4 });
        it->auto_move();
        if (is_bullet_exist(*it))
            t.push_back(*it);
    }
    bullet = t;
}

void display_time()
{
    time_count++;
    char s[20];
    sprintf(s, "Time: %ds", (FPS * 30 - time_count) / FPS);
    display_text(s, { 0xff,0xff,0xff,0xff }, { 30,30,90,30 });
    if (FPS * 30 < time_count) {
        level_up();
    }
}

void display_wall()
{
    for (auto it : wall_vector) {
        display_img(enemy2_down3_png, { it.first,it.second,PLANE_SIZE,PLANE_SIZE });
    }
}

void display_health()
{

    char s[20];
    sprintf(s, "Health: %d / 100", player_health);
    display_text(s, { 0xff,0xff,0xff,0xff }, { 150,30,150,30 });
}

void display_back()
{
	auto texture = SDL_CreateTextureFromSurface(renderer, background_png);
	SDL_Rect dst = { 0,0,window_width,window_height };
	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_DestroyTexture(texture);
}

void level_up()
{
    switch (sence_flag)
    {
    case MENU:
        Enemy e1;
        e1.shoot_count = 0;
        e1.x = 90;
        e1.y = 90;
        enemy.push_back(e1);
        e1.x = 180;
        e1.y = 150;
        enemy.push_back(e1);
        e1.x = 270;
        e1.y = 60;
        enemy.push_back(e1);
        SDL_RenderClear(renderer);
        display_back();
        time_count = 0;
        sence_flag = GAME1;
        player_health = 100;
        SPEED += 3;
        display_text("Level 1", { 0xff,0xff,0xff,0xff }, { 90,300,180,48 });
        SDL_RenderPresent(renderer);
        SDL_Delay(1500);
        break;
    case GAME1:
        time_count = 0;
        sence_flag = GAME2;
        player_health = 100;
        SPEED += 3;

        e1.shoot_count = 0;
        e1.x = 90;
        e1.y = 480;
        enemy.push_back(e1);
        e1.x = 180;
        e1.y = 360;
        enemy.push_back(e1);
        e1.x = 60;
        e1.y = 420;
        enemy.push_back(e1);
        SDL_RenderClear(renderer);
        display_back();
        time_count = 0;
        sence_flag = GAME2;
        player_health = 100;
        SPEED += 3;

        display_text("Level 2", { 0xff,0xff,0xff,0xff }, { 90,300,180,48 });
        SDL_RenderPresent(renderer);
        SDL_Delay(1500);
        break;
    case GAME2:
        time_count = 0;
        sence_flag = GAME3;
        player_health = 100;
        SPEED += 3;

        e1.shoot_count = 0;
        e1.x = 90;
        e1.y = 540;
        enemy.push_back(e1);
        e1.x = 180;
        e1.y = 540;
        enemy.push_back(e1);
        e1.x = 60;
        e1.y = 540;
        enemy.push_back(e1);
        SDL_RenderClear(renderer);
        display_back();
        time_count = 0;
        sence_flag = GAME3;
        player_health = 100;
        SPEED += 3;


        display_text("Level 3", { 0xff,0xff,0xff,0xff }, { 90,300,180,48 });
        SDL_RenderPresent(renderer);
        SDL_Delay(1500);
        break;
    case GAME3:
        sence_flag = WIN;
        break;
    default:
        break;
    }
}

void event_loop()
{
    while (1) {
        auto start = SDL_GetTicks();

        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || game_flag != GAME_PLAY) {
                break;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case UP_ARROW:
                    if (role.y > 0) role.y-= SPEED;
                    break;
                case DOWN_ARROW:
                    if (role.y < window_height) role.y+= SPEED;
                    break;
                case LEFT_ARROW:
                    if (role.x > 0) role.x-= SPEED;
                    break;
                case RIGHT_ARROW:
                    if (role.x < window_width) role.x+= SPEED;
                    break;
                case SPACE:
                    switch (sence_flag)
                    {
                    case MENU:
                        level_up();
                        break;
                    case WIN:
                    case LOSS:
                        game_flag = GAME_RESET;
                        break;
                    default:
                        break;
                    }
                    break;
                case ENTER:
                    switch (sence_flag)
                    {
                    case LOSS:
                    case WIN:
                        game_flag = GAME_OVER;
                    default:
                        break;
                    }
                    break;
                }
            }
        };

        draw();

        auto end = SDL_GetTicks();
        if (end - start < 1000 / FPS) {
            SDL_Delay(1000 / FPS - (end - start));
        }
    }
}

void draw()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    switch (sence_flag)
    {
    case MENU:
        display_menu();
        break;
    case GAME1:
    case GAME2:
    case GAME3:
        display_game();
        break;
    case WIN:
        display_win();
        break;
    case LOSS:
        display_loss();
        break;
    default:
        break;
    }

    SDL_RenderPresent(renderer);
}

void Enemy::auto_move()
{
    auto p = int(rand() % 4);
    switch (p)
    {
    case 0:
        if (x > 0) x -= SPEED;
        break;
    case 1:
        if (y > 0) y -= SPEED;
        break;
    case 2:
        if (x < window_width) x += SPEED;
        break;
    case 3:
        if (y < window_height) y += SPEED;
        break;

    default:
        break;
    }
}

void Enemy::auto_shoot()
{
    shoot_count++;
    if (shoot_count % FPS == 0) {
        Bullet n;
        n.x = x;
        n.y = y;
        n.display_count = 0;
        n.vx = rand() % SPEED + 1;
        n.vx *= pow(-1, rand() % 2);
        n.vy = rand() % SPEED + 1;
        bullet.push_back(n);
    }
    
}

void Bullet::auto_move()
{
    x += vx;
    y += vy;
}

#pragma once

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 900

#define SPLASH_STATE_SHOW_TIME 0.0

#define PIXEL_FONT "Resources/fonts/PixellettersFull.ttf"
#define DOSIS_FONT "Resources/fonts/Dosis-Light.ttf"

#define SPLASH_SCREEN "Resources/res/bajana_games.png"
#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/res/grass.jpg"
#define GAME_BACKGROUND_FILEPATH "Resources/res/grass3.jpg"
#define GAME_DIRT_BACKGROUND_FILEPATH "Resources/res/dirt.jpg"
#define GAME_DIRT2_BACKGROUND_FILEPATH "Resources/res/dirt2.jpg"
#define ROAD_FILEPATH "Resources/res/road.jpg"
#define GAME_OVER_BACKGROUND_FILEPATH "Resources/res/grass2.jpg"
#define GAME_GRASS_BACKGROUND_FILEPATH "Resources/res/grass.jpg"

#define GAME_TITLE_FILEPATH "Resources/res/title.png"
#define PLAY_BUTTON_FILEPATH "Resources/res/graj.png"
#define EXIT_BUTTON_FILEPATH "Resources/res/wyjdz.png"
#define NEW_SAVE_BUTTON_FILEPATH "Resources/res/nowy_zapis.png"
#define SAVE_BUTTON_FILEPATH "Resources/res/zapisz_gre.png"
#define RETURN_TO_MENU_BUTTON_FILEPATH "Resources/res/wroc_do_menu.png"
#define NEW_GAME_BUTTON_FILEPATH "Resources/res/nowa_gra.png"
#define RETURN_TO_GAME_BUTTON_FILEPATH "Resources/res/wroc_do_gry.png"
#define LOAD_GAME_BUTTON_FILEPATH "Resources/res/wczytaj_gre.png"
#define SELECT_CHAR_BUTTON_FILEPATH "Resources/res/zmien_postac.png"

#define PIPE_MOVEMENT_SPEED 200.0f
#define PIPE_SPAWN_FREQUENCY 1.5f

#define BIRD_ANIMATION_DURATION 0.4f

#define BIRD_STATE_STILL 1
#define BIRD_STATE_FALLING 2
#define BIRD_STATE_FLYING 3

#define GRAVITY 350.0f
#define FLYING_SPEED 350.0f

#define FLYING_DURATION 0.25f

#define ROTATION_SPEED 100.0f

enum GameStates
{
	eReady,
	ePlaying,
	eGameOver
};

#define FLASH_SPEED 1500.0f

#define TIME_BEFORE_GAME_OVER_APPEARS 1.5f

#define BRONZE_MEDAL_SCORE 0
#define SILVER_MEDAL_SCORE 5
#define GOLD_MEDAL_SCORE 25
#define PLATINUM_MEDAL_SCORE 100
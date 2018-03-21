#pragma once

#define WINDOW_TITLE "50_Jahre_Ths"

#define SCALE_FACTOR 2

#define SCREEN_WIDTH 10 * 32 * SCALE_FACTOR
#define SCREEN_HEIGHT 8 * 32 * SCALE_FACTOR

#define MAP_WIDTH 10 * 32 * SCALE_FACTOR
#define MAP_HEIGHT 5 * 32 * SCALE_FACTOR

#define NUM_TILES_X MAP_WIDTH / (32 * SCALE_FACTOR)
#define NUM_TILES_Y MAP_HEIGHT / (32 * SCALE_FACTOR)


#define SPLASH_STATE_SHOW_TIME 3.0f
#define LOGO_FILEPATH "Resources/res/newlogo.png"
#define SHADE_PIXELATE_FILEPATH "Resources/shaders/pixelate.shader"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <unistd.h>

int	main(void)
{
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	Mix_Chunk	*shot_sound = Mix_LoadWAV("assets/audio/gun_shot.wav");
	Mix_PlayChannel(-1, shot_sound, 0);
	usleep(500000000);
}

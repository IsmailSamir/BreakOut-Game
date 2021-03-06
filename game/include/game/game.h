#pragma once

#include "game/Exports.h"
#include "component/level.h"
#include "component/player_paddle.h"
#include "component/ball.h"

#include <renderer/renderer.h>
#include <renderer/window.h>

#include <vector>

namespace bko
{
	struct Game
	{
		enum STATE
		{
			STATE_ACTIVE,
			STATE_MENU,
			STATE_WON,
			STATE_LOSS
		};

		STATE state;
		GLboolean keys[1024];
		std::vector<Level> levels;
		GLuint current_level;
		GLuint lives;
		Player_Paddle player;
		Ball ball;
		Window window;
		Sprite_Renderer sprite_renderer;
	};

	GAME_EXPORT Game
	game_new(GLsizei width, GLsizei height);

	GAME_EXPORT void
	game_free(Game self);

	GAME_EXPORT void
	game_init(Game& self);

	GAME_EXPORT void
	game_run(Game self);

} //namespace end
#pragma once

#include "game/Exports.h"

#include <component/sprite.h>

#include <program/program.h>

namespace bko
{
	typedef struct ISprite_Renderer* Sprite_Renderer;
	
	GAME_EXPORT Sprite_Renderer
	sprite_renderer_new(const Program& program);

	GAME_EXPORT void
	sprite_renderer_free(Sprite_Renderer self);

	inline static void
	destruct(Sprite_Renderer self)
	{
		sprite_renderer_free(self);
	}

	GAME_EXPORT void
	sprite_renderer_render(Sprite_Renderer self, Sprite sprite);

} //namespace end
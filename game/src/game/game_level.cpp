#include "game/game_level.h"

#include <texture/texture.h>
#include <resource_manager/resource_manager.h>

#include <glm/glm.hpp>

#include <sstream>
#include <fstream>
#include <string>

using namespace std;
using namespace glm;

namespace bko
{
	static Resource_Manager rm = IResource_Manager::get_instance();

	// Helper Fucntions
	inline static vector<vector<GLuint>>
	_load_level_from_file(const char* file_path)
	{
		string line;
		ifstream fstream(file_path);
		vector<vector<GLuint>> tile_data;

		if (fstream)
		{
			GLuint tile_code;
			while (getline(fstream, line)) // Read each line from level file
			{
				istringstream sstream(line);
				vector<GLuint> row;
				while (sstream >> tile_code) // Read each word seperated by spaces
					row.push_back(tile_code);

				tile_data.push_back(row);
			}
		}

		return tile_data;
	}

	inline static void
	_init_level(vector<vector<GLuint>> tile_data, GLuint level_width, GLuint level_height, vector<Game_Object>& level)
	{
		// calculate dimensions
		GLuint height = tile_data.size();
		GLuint width = tile_data[0].size();
		GLfloat brick_width = GLfloat(level_width) / GLfloat(width);
		GLfloat brick_height = GLfloat(level_height) / GLfloat(height);

		// initialize level tiles based on tileData		
		for (GLuint y = 0; y < height; ++y)
		{
			for (GLuint x = 0; x < width; ++x)
			{
				Game_Object object{};
				// check block type from level data (2D level array)
				if (tile_data[y][x] == 1) // Solid
				{
					object = game_object_new(resource_manager_texture(rm, "block_solid"),
						vec3{ 0.8f, 0.8f, 0.7f },
						vec2{ brick_width * x, brick_height * y },
						vec2{ brick_width, brick_height },
						vec2{},
						0.0f,
						GL_TRUE,
						GL_FALSE);

					level.push_back(object);
				}
				else if (tile_data[y][x] > 1)	// Non-solid; now determine its color based on level data
				{
					vec3 color = vec3{ 1.0f }; // original: white
					if (tile_data[y][x] == 2)
						color = vec3{ 0.2f, 0.6f, 1.0f };
					else if (tile_data[y][x] == 3)
						color = vec3{ 0.0f, 0.7f, 0.0f };
					else if (tile_data[y][x] == 4)
						color = vec3{ 0.8f, 0.8f, 0.4f };
					else if (tile_data[y][x] == 5)
						color = vec3{ 1.0f, 0.5f, 0.0f };

					object = game_object_new(resource_manager_texture(rm, "block"),
						color,
						vec2{ brick_width * x, brick_height * y },
						vec2{ brick_width, brick_height },
						vec2{},
						0.0f,
						GL_FALSE,
						GL_FALSE);

					level.push_back(object);
				}
			}
		}
	}


	// API
	Game_Level
	game_level_new(GLuint level_width, GLuint level_height, const char* file_path)
	{
		Game_Level self{};

		vector<vector<GLuint>> tile_data = _load_level_from_file(file_path);
		_init_level(tile_data, level_width, level_height, self.bricks);

		return self;
	}

	void
	game_level_free(Game_Level self)
	{
		for (auto brick : self.bricks)
			destruct(brick);
	}
	
	GLboolean
	game_level_is_complete(Game_Level self)
	{
		for (auto brick : self.bricks)
			if (!brick.is_solid && !brick.is_destroyed)
				return GL_FALSE;
		return GL_TRUE;
	}
}
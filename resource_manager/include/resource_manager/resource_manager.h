#pragma once

#include "resource_manager/Exports.h"

#include <unordered_map>
#include <string>

#include <program/program.h>
#include <texture/texture.h>

namespace bko
{
	typedef struct IResource_Manager *Resource_Manager;

	struct IResource_Manager
	{
		std::unordered_map<std::string, bko::Program> programs;
		std::unordered_map<std::string, bko::Texture> textures;

		static Resource_Manager get_instance()
		{
			static IResource_Manager instance;
			return &instance;
		}		
	};

	RESOURCE_MANAGER_EXPORT void
	resource_manager_free(Resource_Manager self);

	RESOURCE_MANAGER_EXPORT void
	resource_manager_load_program(Resource_Manager self, std::string vshader_path, std::string fshader_path, std::string name);

	RESOURCE_MANAGER_EXPORT Program
	resource_manager_program(Resource_Manager self, std::string name);

	RESOURCE_MANAGER_EXPORT void
	resource_manager_load_texture(Resource_Manager self, std::string image_path, std::string name);

	RESOURCE_MANAGER_EXPORT Texture
	resource_manager_texture(Resource_Manager self, std::string name);

} //namespace end
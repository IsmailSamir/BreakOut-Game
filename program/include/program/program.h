#pragma once

#include "program/Exports.h"

#include <GL/glew.h>

#include <glm/glm.hpp>

namespace bko
{
	struct Program
	{		
		GLuint id;

		operator bool()
		{
			return id != 0;
		}
	};

	PROGRAM_EXPORT Program
	program_new(const char* vertex_shader_source, const char* fragment_shader_cource);

	PROGRAM_EXPORT void
	program_free(Program self);

	inline static void
	destruct(Program self)
	{
		program_free(self);
	}

	PROGRAM_EXPORT void
	program_use(Program self);

	PROGRAM_EXPORT void
	program_float_set(Program self, const char* name, GLfloat val);

	PROGRAM_EXPORT void
	program_int_set(Program self, const char* name, GLint val);

	PROGRAM_EXPORT void
	program_vec2f_set(Program self, const char* name, GLfloat x, GLfloat y);

	PROGRAM_EXPORT void
	program_vec2f_set(Program self, const char* name, const glm::vec2& val);

	PROGRAM_EXPORT void
	program_vec3f_set(Program self, const char* name, GLfloat x, GLfloat y, GLfloat z);

	PROGRAM_EXPORT void
	program_vec3f_set(Program self, const char* name, const glm::vec3& val);

	PROGRAM_EXPORT void
	program_vec4f_set(Program self, const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	PROGRAM_EXPORT void
	program_vec4f_set(Program self, const char* name, const glm::vec4& val);

	PROGRAM_EXPORT void
	program_mat4f_set(Program self, const char* name, const glm::mat4& matrix);

	constexpr static Program INVALID_PROGRAM = Program{};
} //namespace end
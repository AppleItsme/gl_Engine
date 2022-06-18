#pragma once

#include <stdint.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "global_types.h"

enum_t {
	rare,
	non_changing,
	dynamic
} attention;

struct_t {
	attention draw_type;
	vec3 color;
	vec3 position;

	uint32_t 
		shaderID,
		VAO,
		VBO,
		EBO;
	uint32_t indices_size, vertices_size;
	float *vertices;
	uint32_t *indices;
} entity;

void process_entity(entity *to_make, Window_t window);
void draw_entity(entity *to_draw);
void destruct_entity(entity *entity_obj);
void move(entity *obj, vec3 direction);

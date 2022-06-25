#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "entity.h"
#include "Application.h"
#include "global_variables.h"
#include <string.h>

void normalize(vec3 vec, size_t size) {
	for(int i = 0; i < size; i += 3) {
		vec[i] /= g_width; //x
		vec[i+1] /= g_height; //y
	}	
}

int getFileSize(FILE *file) {
    if(fseek(file, 0L, SEEK_END) != 0) {
		printf("file size seek couldn't work");
		return -1;
	}
    int size = ftell(file);
	printf("the file components: %s\n", file->_IO_read_base);
	fseek(file, 0L, SEEK_SET);
    return size;
}

void process_entity(entity* restrict to_make, Window_t restrict window, char* restrict vert_path, char* restrict frag_path) {

	FILE *file = fopen(vert_path, "r");
	if(file == NULL) {
		perror("Error in opening the file");
	}

	fseek(file, 0, SEEK_END);
	
	size_t fsize = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *vertex_shader = malloc((fsize+1) * sizeof(char));
	fread(vertex_shader, sizeof(char), fsize, file);
	vertex_shader[fsize] = '\0';

	fclose(file);
	
	file = fopen(frag_path, "r");
	fseek(file, 0, SEEK_END);	
	
	fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *fragment_shader = malloc((fsize+1) * sizeof(char));
	fread(fragment_shader, sizeof(char), fsize, file);
	fragment_shader[fsize-1] = '\0';
	fclose(file);

	uint32_t vertShader, fragShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertShader, 1, &vertex_shader, NULL);
	glShaderSource(fragShader, 1, &fragment_shader, NULL);
	glCompileShader(vertShader);
	
	free(vertex_shader);
	free(fragment_shader);

	int success;
	char info[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(vertShader, 512, NULL, info);
		printf("could not compile vert shader\n%s\n", info);
	}
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(fragShader, 512, NULL, info);
		printf("could not compile frag shader\n%s\n", info);
	}

	to_make->shaderID = glCreateProgram();
	
	glAttachShader(to_make->shaderID, vertShader);
	glAttachShader(to_make->shaderID, fragShader);
	glLinkProgram(to_make->shaderID);

	glGetProgramiv(to_make->shaderID, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(to_make->shaderID, 512, NULL, info);
		printf("failed to link");
	}

	int render_attention_of_entity = GL_DYNAMIC_DRAW;
	if(to_make->draw_type == rare) {
		render_attention_of_entity = GL_STREAM_DRAW;
	} else if(to_make->draw_type == non_changing) {
		render_attention_of_entity = GL_STATIC_DRAW;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	normalize(to_make->vertices, to_make->vertices_size);

	glGenVertexArrays(1, &to_make->VAO);
	glBindVertexArray(to_make->VAO);
	
	glGenBuffers(1, &to_make->VBO);
	glGenBuffers(1, &to_make->EBO);

    glBindBuffer(GL_ARRAY_BUFFER, to_make->VBO);
		
	glBufferData(GL_ARRAY_BUFFER, to_make->vertices_size * sizeof(float), to_make->vertices, render_attention_of_entity);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, to_make->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, to_make->indices_size * sizeof(uint32_t), to_make->indices, render_attention_of_entity);
	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	to_make->position[0] = to_make->vertices[0]; 
	to_make->position[1] = to_make->vertices[1]; 
	to_make->position[2] = to_make->vertices[2]; 
}
void draw_entity(entity *to_draw) {
	glUseProgram(to_draw->shaderID);
	glBindVertexArray(to_draw->VAO);
	glDrawElements(GL_TRIANGLES, to_draw->indices_size, GL_UNSIGNED_INT, 0);
}

void move(entity *obj, vec3 direction) {
	glUseProgram(obj->shaderID);
	glBindVertexArray(obj->VAO);
	uint32_t position = glGetUniformLocation(obj->shaderID, "pos2");
	
	normalize(direction, 3);

	glm_vec3_add(obj->position, direction, obj->position);
	glUniform3f(position, obj->position[0], obj->position[1], obj->position[2]);
}


void destruct_entity(entity *entity_obj){
	glDeleteBuffers(1, &entity_obj->EBO);
	glDeleteBuffers(1, &entity_obj->VBO);
	glDeleteVertexArrays(1, &entity_obj->VAO);
	glDeleteProgram(entity_obj->shaderID);
}

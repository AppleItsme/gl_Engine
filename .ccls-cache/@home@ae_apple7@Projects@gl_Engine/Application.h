#pragma once

#include <stdint.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/vec2.h>

#define Window_t GLFWwindow*

extern int resolution;

void new_application(uint32_t width, uint32_t height, char const *name);	
void run_Application();
void free_Application();

void get_resolution(int *x, int *y);

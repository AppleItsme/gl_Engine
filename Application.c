#include "Application.h"
#include "entity.h"
#include "stdio.h"

static Window_t window;

void get_resolution(int *x, int *y) {
	glfwGetWindowSize(window, x, y);
}

void resize_callback(Window_t window, int width, int height) {
	glViewport(0, 0, width, height);
}

void new_application(uint32_t width, uint32_t height, const char *name) {
	if(!glfwInit()) {
		printf("Could not initialize glfw");
		return;
	}
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	
	glfwSetFramebufferSizeCallback(window, resize_callback);

	if(window == NULL) {
		glfwTerminate();
		printf("could not generate the window");
	}
	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("could not initialize GLAD");
		return;
	}
	glViewport(0, 0, width, height);
	glfwSwapInterval(0);
}

void free_Application() {
	glfwTerminate();
}

void run_Application() {
	entity rectangle = {
		.vertices = (float[]) {
			600/2,  800/2, 0.0f,  // top right
			600/2, -800/2, 0.0f,  // bottom right
			-600/2, -800/2, 0.0f,  // bottom left
			-600/2,  800/2, 0.0f   // top left 
		},
		.vertices_size = 12,
		.indices = (uint32_t[]) {
			0, 1, 2,
			0, 2, 3
		},
		.indices_size = 6,
	};
	process_entity(non_changing, &rectangle);
	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.2, 0.2, 0.2, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		draw_entity(&rectangle);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

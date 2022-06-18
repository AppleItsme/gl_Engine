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
			600,  60/2, 1.0f,  // top right
			60/2, -60/2, 1.0f,  // bottom right
			-60/2, -60/2, 1.0f,  // bottom left
			-60/2,  60/2, 1.0f   // top left 
		},
		.vertices_size = 12,
		.indices = (uint32_t[]) {
			0, 1, 2,
			0, 2, 3
		},
		.indices_size = 6,
		.draw_type = dynamic
	};
	process_entity(&rectangle);
	uint32_t time = glfwGetTime();


	while(!glfwWindowShouldClose(window)) {
		glClearColor(0.2, 0.2, 0.2, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		draw_entity(&rectangle);
		glfwSwapBuffers(window);
		glfwPollEvents();
		time = glfwGetTime();
	}
	destruct_entity(&rectangle);
}

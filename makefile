LINKER_FLAGS = -lglfw -lGL -lm -Iinclude -Icglm/include
OUTPUT_NAME = my_opengl

make:
	gcc -O3 *.c -o $(OUTPUT_NAME) $(LINKER_FLAGS) 
debug:
	gcc -O3 *.c -o $(OUTPUT_NAME) $(LINKER_FLAGS) -g

LINKER_FLAGS = -lglfw -lGL -lm -Iinclude -Icglm/include
OUTPUT_NAME = my_opengl
#OPTIMISATION_LEVEL = -O2

make:
	gcc *.c -o $(OUTPUT_NAME) $(LINKER_FLAGS) 
debug:
	gcc *.c -o $(OUTPUT_NAME) $(LINKER_FLAGS) -g

include = -I src/engine
lib = -I lib
build_dir = build/
lib_files = lib/*.c 
src_files = src/*.c src/engine/io/*.c src/engine/render/*.c src/engine/*.c
libs = -lGL -lglfw -ldl -lm -lcglm
out_file = game
.PHONY: build
build:
	gcc -c $(lib_files) $(src_files) $(include) $(lib) $(libs)
	gcc *.o -o $(out_file) -Wall -O2 $(include) $(lib) $(libs)
	rm *.o
	./$(out_file)


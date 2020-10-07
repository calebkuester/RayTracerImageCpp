CC=g++ -std=gnu++11
FLAGS = -Wall -Wextra
DEPS = helloworld.h
ARGS = data/materials.mtl data/scene.obj data/commands false

all: asdf
asdf : camera.o light.o material.o camera.o raytracer.o raycast.o shape.o
	$(CC) raytracer.o -o asdf camera.o light.o material.o camera.o raycast.o shape.o
camera.o : Camera.cpp Camera.h
	$(CC) -c $(FLAGS) -g Camera.cpp -o camera.o
light.o : Light.cpp Light.h
	$(CC) -c $(FLAGS) -g Light.cpp -o light.o
material.o : material.cpp material.h
	$(CC) -c $(FLAGS) -g material.cpp -o material.o 
raytracer.o : raytracer.cpp raytracer.h
	$(CC) -c $(FLAGS) -g raytracer.cpp -o raytracer.o
raycast.o : raycast.cpp raycast.h
	$(CC) -c $(FLAGS) -g raycast.cpp -o raycast.o
shape.o : Shape.cpp Shape.h
	$(CC) -c $(FLAGS) -g Shape.cpp -o shape.o
clean :
	rm asdf* *.o
run: asdf
	./asdf $(ARGS)

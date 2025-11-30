CC		= g++
ASAN_FLAGS	= -fsanitize=address
CFLAGS		:= -Wall

objects := light.o render_obj.o material.o canvas.o color.o object.o ray.o matrix_transform.o matrix.o tuples.o double_eq.o world.o main.o

raytrace: $(objects)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $^ -o $@ 

main.o: light.h object.h canvas.h world.h main.cc
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c main.cc

world.o: world.cc ray.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c world.cc 

render_obj.o: render_obj.cc material.h light.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c render_obj.cc

light.o: light.cc ray.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c light.cc

material.o: material.cc ray.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c material.cc

canvas.o: canvas.cc color.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c canvas.cc

color.o: color.cc double_eq.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c color.cc

object.o: object.cc render_obj.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c object.cc

ray.o: ray.cc matrix_transform.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c ray.cc

matrix_transform.o: matrix_transform.cc matrix.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c matrix_transform.cc

matrix.o: matrix.cc tuples.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c matrix.cc

tuples.o: tuples.cc double_eq.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c tuples.cc

double_eq.o: double_eq.cc
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c double_eq.cc

%.cc:
	touch $@

clean:
	rm -f *.o

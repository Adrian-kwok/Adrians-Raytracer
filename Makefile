CC		= g++
ASAN_FLAGS	= -fsanitize=address
CFLAGS		:= -Wall

objects := main.o light.o canvas.o color.o object.o ray.o matrix_transform.o matrix.o tuples.o double_eq.o

raytrace: $(objects)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $^ -o $@ 

main.o: main.cc light.h object.h canvas.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c main.cc

light.o: light.cc ray.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c light.cc

canvas.o: canvas.cc color.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c canvas.cc

color.o: color.cc double_eq.h
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -c color.cc

object.o: object.cc ray.h
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

CC		= g++
CFLAGS	:= -Wall

objects := light.o concrete_material.o render_obj.o material.o canvas.o color.o object.o ray.o matrix_transform.o matrix.o tuples.o double_eq.o world.o main.o

raytrace: $(objects)
	$(CC) $(CFLAGS) $^ -o $@ 

main.o: light.h render_obj.h canvas.h world.h concrete_material.h main.cc
	$(CC) $(CFLAGS)  -c main.cc

concrete_material.o: material.o concrete_material.cc
	$(CC) $(CFLAGS)  -c concrete_material.cc

world.o: world.cc ray.h
	$(CC) $(CFLAGS)  -c world.cc 

render_obj.o: render_obj.cc material.h light.h
	$(CC) $(CFLAGS)  -c render_obj.cc

light.o: light.cc ray.h
	$(CC) $(CFLAGS)  -c light.cc

material.o: material.cc ray.h
	$(CC) $(CFLAGS)  -c material.cc

canvas.o: canvas.cc color.h
	$(CC) $(CFLAGS)  -c canvas.cc

color.o: color.cc double_eq.h
	$(CC) $(CFLAGS)  -c color.cc

object.o: object.cc render_obj.h
	$(CC) $(CFLAGS)  -c object.cc

ray.o: ray.cc matrix_transform.h
	$(CC) $(CFLAGS)  -c ray.cc

matrix_transform.o: matrix_transform.cc matrix.h
	$(CC) $(CFLAGS)  -c matrix_transform.cc

matrix.o: matrix.cc tuples.h
	$(CC) $(CFLAGS)  -c matrix.cc

tuples.o: tuples.cc double_eq.h
	$(CC) $(CFLAGS)  -c tuples.cc

double_eq.o: double_eq.cc
	$(CC) $(CFLAGS)  -c double_eq.cc

%.cc:
	touch $@

clean:
	rm -f *.o

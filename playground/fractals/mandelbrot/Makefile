.SILENT:

C = gcc

SRC = mandelbrot.c
OBJECTS = $(SRC:.c=.o)

fractal: $(OBJECTS)
	$(C) $(OBJECTS) -o fractal -lm

run: fractal
	./fractal

%.o: %c
	$(C) $^ -o $@ -lm

clean:
	rm -f fractal *.o

bin: matriz.c
	gcc $< -o $@ -lpthread
run:
	./bin
clean:
	rm bin
all:
	gcc -c ./src/dll.c -I ./include -o ./obj/dll.o
	gcc ./app/main.c ./obj/*.o -I ./include -o ./bin/app

run:
	./bin/app

clean:
	rm ./bin/* ./obj/*
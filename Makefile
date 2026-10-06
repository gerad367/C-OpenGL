all:
	cc -o out src/*.c -lglfw -lGL

clean:
	rm out

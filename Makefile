all:
	cc -o out src/*.c -lglfw -lGL -lm

clean:
	rm out

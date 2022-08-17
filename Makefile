rien: petitChevaux
	./output/petitChevaux

petitChevaux: src/*.c
	mkdir -p output
	gcc -Wall -Wpedantic -Wextra src/*.c -o output/petitChevaux
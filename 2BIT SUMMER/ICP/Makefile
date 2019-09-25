all: build

build:
	qmake -makefile -o qmakefile src/gui
	make -f qmakefile

doxygen:
	@doxygen src/doxy.config

run: build
	./chess
all: clean reload build exec

mkdir_build:
	[ -d ./cmake-build-debug ] | mkdir -p cmake-build-debug

build:
	cd cmake-build-debug;make

exec:
	./cmake-build-debug/linker_mihail_game

clean:
	rm -rf cmake-build-debug

reload: mkdir_build
	cd cmake-build-debug;cmake ..

fast_build:
	cd cmake-build-debug;make

run: fast_build exec
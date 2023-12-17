COMPILER = g++
EXE = game
LIBS = -I/usr/local/include -isystem. -L. -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lstdc++ -std=c++17 -lchipmunk
FlAGS =-Wall -Wno-sign-compare
#DEBUG = -g -ggdb
SOURCES = $(wildcard ./*.cpp) 
OBJ_DIR = obj
OBJECTS = $(patsubst ./%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))


all: $(EXE)	

$(EXE): $(OBJECTS) 
	$(COMPILER) -o $(EXE) $(DEBUG) $(OBJECTS) $(FlAGS) $(LIBS) 
$(OBJ_DIR)/%.o: ./%.cpp $(wildcard ./*.hpp)
	$(COMPILER) -c -o $@ $< $(FlAGS) $(LIBS) $(DEBUG)

web:	
	# cp -r resources/* resources.wasm
	# for file in ./resources.wasm/*.png; do convert $$file -rotate 180 -flop $$file; done
	rm -r ./build/*
	/home/foxmoss/Projects/emsdk/upstream/emscripten/em++ -o build/index.html $(SOURCES) ./libs/libraylib.a -L./libs $(FlAGS) $(LIBS) -s USE_GLFW=3 -s ASYNCIFY --shell-file ./minshell.html -DPLATFORM_WEB --preload-file resources -s TOTAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=1 -s FORCE_FILESYSTEM=1 -DWASM -s STACK_SIZE=655360
	cd build && zip -r package.zip *

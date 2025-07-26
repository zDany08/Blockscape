CC = g++
INC = inc
SRC = src
LIB = lib
OUT = build
OUT_NAME = game

all: build run

run:
	cd $(OUT) && ./$(OUT_NAME)

build: generate main.o glad.o imgui.o imgui_demo.o imgui_draw.o imgui_impl_glfw.o imgui_impl_opengl3.o imgui_tables.o imgui_widgets.o block.o chunk.o input.o instance.o logger.o physics.o player.o renderer.o rendering.o resources.o utils.o world.o compile clean

generate:
	mkdir -p $(OUT)/obj

compile:
	$(CC) $(OUT)/obj/main.o $(OUT)/obj/glad.o $(OUT)/obj/imgui.o $(OUT)/obj/imgui_demo.o $(OUT)/obj/imgui_draw.o $(OUT)/obj/imgui_impl_glfw.o $(OUT)/obj/imgui_impl_opengl3.o $(OUT)/obj/imgui_tables.o $(OUT)/obj/imgui_widgets.o $(OUT)/obj/block.o $(OUT)/obj/chunk.o $(OUT)/obj/input.o $(OUT)/obj/instance.o $(OUT)/obj/logger.o $(OUT)/obj/physics.o $(OUT)/obj/player.o $(OUT)/obj/renderer.o $(OUT)/obj/rendering.o $(OUT)/obj/resources.o $(OUT)/obj/utils.o $(OUT)/obj/world.o -Llib -lglfw3 -o $(OUT)/$(OUT_NAME)

clean:
	cd $(OUT) && rm -r obj

main.o:
	$(CC) -c $(SRC)/main.cpp -I$(INC) -o $(OUT)/obj/main.o

glad.o:
	$(CC) -c $(INC)/glad/glad.c -I$(INC) -o $(OUT)/obj/glad.o

imgui.o:
	$(CC) -c $(INC)/imgui/imgui.cpp -I$(INC) -o $(OUT)/obj/imgui.o

imgui_demo.o:
	$(CC) -c $(INC)/imgui/imgui_demo.cpp -I$(INC) -o $(OUT)/obj/imgui_demo.o

imgui_draw.o:
	$(CC) -c $(INC)/imgui/imgui_draw.cpp -I$(INC) -o $(OUT)/obj/imgui_draw.o

imgui_impl_glfw.o:
	$(CC) -c $(INC)/imgui/imgui_impl_glfw.cpp -I$(INC) -o $(OUT)/obj/imgui_impl_glfw.o

imgui_impl_opengl3.o:
	$(CC) -c $(INC)/imgui/imgui_impl_opengl3.cpp -I$(INC) -o $(OUT)/obj/imgui_impl_opengl3.o

imgui_tables.o:
	$(CC) -c $(INC)/imgui/imgui_tables.cpp -I$(INC) -o $(OUT)/obj/imgui_tables.o

imgui_widgets.o:
	$(CC) -c $(INC)/imgui/imgui_widgets.cpp -I$(INC) -o $(OUT)/obj/imgui_widgets.o

block.o:
	$(CC) -c $(SRC)/block.cpp -I$(INC) -o $(OUT)/obj/block.o

chunk.o:
	$(CC) -c $(SRC)/chunk.cpp -I$(INC) -o $(OUT)/obj/chunk.o

input.o:
	$(CC) -c $(SRC)/input.cpp -I$(INC) -o $(OUT)/obj/input.o

instance.o:
	$(CC) -c $(SRC)/instance.cpp -I$(INC) -o $(OUT)/obj/instance.o

logger.o:
	$(CC) -c $(SRC)/logger.cpp -I$(INC) -o $(OUT)/obj/logger.o

physics.o:
	$(CC) -c $(SRC)/physics.cpp -I$(INC) -o $(OUT)/obj/physics.o

player.o:
	$(CC) -c $(SRC)/player.cpp -I$(INC) -o $(OUT)/obj/player.o

renderer.o:
	$(CC) -c $(SRC)/renderer.cpp -I$(INC) -o $(OUT)/obj/renderer.o

rendering.o:
	$(CC) -c $(SRC)/rendering.cpp -I$(INC) -o $(OUT)/obj/rendering.o

resources.o:
	$(CC) -c $(SRC)/resources.cpp -I$(INC) -o $(OUT)/obj/resources.o

utils.o:
	$(CC) -c $(SRC)/utils.cpp -I$(INC) -o $(OUT)/obj/utils.o

world.o:
	$(CC) -c $(SRC)/world.cpp -I$(INC) -o $(OUT)/obj/world.o

CC := gcc
CFLAGS := 
BUILD ?= DEBUG
LDFLAGS := `pkg-config --libs --cflags sdl2 SDL2_image SDL2_ttf` -lm
INCLUDE := -I./framework/include/ -I./include/
C_FILES := ./src/*.c ./framework/source/*.c ./framework/source/*/*.c ./src/*/*.c

ifeq ($(BUILD), RELEASE)
	CFLAGS += -O2
else
	CFLAGS += -O0 -g -Wall
endif

OUT :=

ifeq ($(OS), Windows_NT)
	OUT += main.exe
	LDFLAGS += -mconsole
else
	OUT += main.out
endif

$(OUT) : $(C_FILES)
	$(CC) $(CFLAGS) -o $@ $(C_FILES) $(INCLUDE) $(LDFLAGS)

.PHONY: clean
clean:
	rm $(OUT)
CC := gcc
CFLAGS := 
BUILD ?= DEBUG

LDFLAGS := `pkg-config --libs --cflags sdl2 SDL2_image SDL2_ttf` -lm
INCLUDE := -I./framework/include/ -I./include/

C_FILES := ./src/*.c ./src/*/*.c ./framework/source/*.c ./framework/source/*/*.c
OBJECTS := $(patsubst %.c,%.o,$(wildcard $(C_FILES)))

ifeq ($(BUILD), RELEASE)
	CFLAGS += -O2
else
	CFLAGS += -O0 -g -Wall -fstrict-aliasing -Wstrict-aliasing 
endif

OUT :=

ifeq ($(OS), Windows_NT)
	OUT += main.exe
	LDFLAGS += -mconsole
else
	OUT += main.out
endif

$(OUT) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDE) $(LDFLAGS)

$(OBJECTS) : %.o : %.c
	gcc -o $@ -c $< $(INCLUDE) $(LDFLAGS) $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OUT) ./*.o ./*/*.o ./*/*/*.o
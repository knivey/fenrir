CC = gcc

BASE_CFLAGS = -std=c18 -pipe
DEBUG_CFLAGS = -O0 -g -DDEBUG -fsanitize=address,leak,undefined
RELEASE_CFLAGS = -march=native -flto -DNDEBUG

CFLAGS = $(BASE_CFLAGS) $(RELEASE_CFLAGS)
INCLUDES =
LFLAGS =
LIBS =

SRC_DIR = ./src
OBJ_DIR = ./obj
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS += -Wall -Wextra -pedantic -pedantic-errors -Wformat=2 -Wshadow	\
	  -Wstrict-prototypes -Wstrict-overflow=2 -Wredundant-decls	\
	  -Wnested-externs -Wfloat-equal -Wpointer-arith -Wpadded -Wvla	\
	  -Wcast-qual -Wundef -Winit-self -Wwrite-strings -Wlogical-op	\
	  -Wcast-align

CLANGD_FILE = compile_flags.txt
CLANGD_FLAGS = $(CFLAGS) -Wno-unused-function -Wno-empty-translation-unit

TARGET = fenrir

default: $(TARGET)

debug: CFLAGS := $(filter-out $(RELEASE_CFLAGS), $(CFLAGS))
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(TARGET)

$(TARGET): $(CLANGD_FILE)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir $@

$(CLANGD_FILE):
	@echo "$(CLANGD_FLAGS)" | tr " " "\n" > $@

.PHONY: clean
clean:
	$(RM) -r $(TARGET) $(OBJ_DIR) $(CLANGD_FILE) *~ gmon.out .clangd

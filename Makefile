SOURCES := $(wildcard src/*.c)
INCLUDE_PATHS := -Isrc -Iinclude
OUT_DIR := build
CC := gcc

.PHONY: all release debug build regen-token clean

all: release

release: BUILD_DIR := Release
release: CFLAGS := -O2 -Wall -DNDEBUG $(INCLUDE_PATHS)
release: OBJ_DIR := $(OUT_DIR)/Release
release: OUTPUT := $(OUT_DIR)/Release/main
release: build

debug: BUILD_DIR := Debug
debug: CFLAGS := -O0 -g -Wall -D_DEBUG $(INCLUDE_PATHS)
debug: OBJ_DIR := $(OUT_DIR)/Debug
debug: OUTPUT := $(OUT_DIR)/Debug/main
debug: build

# OBJECTS 必须在 OBJ_DIR 确定后定义，所以放在 build 目标里
build: $(OBJ_DIR)
	$(eval OBJECTS := $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SOURCES)))
	@echo ========================================
	@echo Building: $(OUTPUT)
	@echo ========================================
	@echo Objects: $(OBJECTS)
	$(MAKE) -f $(firstword $(MAKEFILE_LIST)) compile

compile: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(OUTPUT)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OUT_DIR)

regen-token:
	@echo "Regenerating token..."
	cd my-peg && python main.py ../Grammar/Tokens ../grammar.gram
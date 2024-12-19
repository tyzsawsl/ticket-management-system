CC = gcc
CFLAGS = -Wall -Wextra -I./include -I./src
BUILD_DIR = build

TARGET = $(BUILD_DIR)/ticket_system.exe

SRCS = src/main.c \
       src/admin.c \
       src/user.c \
       src/database.c \
       src/utils/auth.c \
       src/utils/file_handler.c

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: directories $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: %.c
	@if not exist "$(dir $(subst /,\,$@))" mkdir "$(dir $(subst /,\,$@))"
	@$(CC) $(CFLAGS) -c $< -o "$@"

clean:
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"

rebuild: clean all

.PHONY: directories
directories:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@if not exist "$(BUILD_DIR)\src" mkdir "$(BUILD_DIR)\src"
	@if not exist "$(BUILD_DIR)\src\utils" mkdir "$(BUILD_DIR)\src\utils"
	@if not exist "data" mkdir "data"

run: all
	@$(TARGET)
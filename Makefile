CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c11 -g

TARGET = c-toolbox
BUILD  = build

SRC = \
app/main.c \
app/cli.c \
logic/filters.c \
logic/sort.c \
core/vector/vector.c \
core/string/string_sso.c

OBJ = $(patsubst %.c,$(BUILD)/%.o,$(SRC))

# =========================

all: $(TARGET)

# LINK
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# COMPILE (FIX REAL MULTIFOLDER RULE)
$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. -c $< -o $@

# CLEAN
clean:
	rm -rf $(BUILD) $(TARGET)

re: clean all

.PHONY: all clean re
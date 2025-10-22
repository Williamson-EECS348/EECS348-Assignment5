SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC))

NAME=assignment5

.PHONY: all assignment5 clean always

all: assignment5

always:
	@mkdir -p $(BUILD_DIR)

assignment5: $(BUILD_DIR)/$(NAME).out

$(BUILD_DIR)/$(NAME).out: $(OBJ)
	@$(CC) $^ $(CLIBS) -o $@

$(BUILD_DIR)/%.o: %.c always
	@$(CC) -c $< $(CFLAGS) -o $@

clean:
	@rm -f $(BUILD_DIR)/$(NAME).out $(OBJ)
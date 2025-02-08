CC = gcc
CFLAGS = -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
EXEC = drone_arp

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/display_drone.c $(SRC_DIR)/display_inspection_window.c $(SRC_DIR)/display_obstacles.c $(SRC_DIR)/display_targets.c $(SRC_DIR)/get_keyboard_instructions.c $(SRC_DIR)/update_obstacles.c $(SRC_DIR)/update_position.c $(SRC_DIR)/update_targets.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

$(BIN_DIR)/$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ -lncurses

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/$(EXEC)

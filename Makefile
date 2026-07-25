# ==========================
# Compiler
# ==========================
CC = gcc

# ==========================
# Compiler Flags
# ==========================
CFLAGS = -Wall -Wextra -g

# ==========================
# Executable Names
# ==========================
SERVER = udp_server
CLIENT = udp_client

# ==========================
# Source Files
# ==========================
SERVER_SRC = src/udp_server.c
CLIENT_SRC = src/udp_client.c

# ==========================
# Default Target
# ==========================
all: $(SERVER) $(CLIENT)

# ==========================
# Build UDP Server
# ==========================
$(SERVER): $(SERVER_SRC)
	$(CC) $(CFLAGS) $(SERVER_SRC) -o $(SERVER)

# ==========================
# Build UDP Client
# ==========================
$(CLIENT): $(CLIENT_SRC)
	$(CC) $(CFLAGS) $(CLIENT_SRC) -o $(CLIENT)

# ==========================
# Remove Executables
# ==========================
clean:
	rm -f $(SERVER) $(CLIENT)

# ==========================
# Rebuild Everything
# ==========================
rebuild: clean all

# ==========================
# Phony Targets
# ==========================
.PHONY: all clean rebuild



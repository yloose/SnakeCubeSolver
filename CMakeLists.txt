cmake_minimum_required(VERSION 3.10)

# Set some basic project attributes
project (SnakeCube
	VERSION 0.1
	DESCRIPTION "Brute force snake cube puzzle.")

# Enable output of compile_commands.json for clangd lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

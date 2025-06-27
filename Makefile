# имя библиотеки
NAME = endgame

# папка с исходниками
SRC_DIR = src

# папка, куда будут складываться объектные файлы
OBJ_DIR = obj

# папка с хедерами
INC_DIR = inc

# папка с библиотекой SDL2
SDL_DIR = resources/SDL2

# флаги для компиляции с SDL2
SDL_FLAGS = -I $(SDL_DIR)

# список всех файлов в папке src, которые имеют расширение .с
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# добавить префикс obj/ к каждой записи из SRC_FILES и изменить расширение с .с на .о
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))

# компилятор для создания o-файлов
CC = clang

# флаги для компилятора
CFLAGS = -std=c11 $(addprefix -W, error pedantic) -g -Wunused-result

# архиватор для формирования библиотеки из о-файлов
AR = ar

# флаги для архиватора
AFLAGS = rcs

MKDIR = mkdir -p
RM = rm -rf

# исполняемый файл будет в главной директории
EXEC = $(NAME)

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR) $(SDL_FLAGS) -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
	@printf "\r\33[2K$@\033[32;1m created.\nWrite 'make run' to run the game. Please enable full screen mode.\033[0m\n"

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) $(SDL_FLAGS)
	@printf "\r\33[2K$(NAME)\033[33;1m compile \033[0m$(<:$(SRC_DIR)/%.c=%)\r"

$(OBJ_DIR):
	@$(MKDIR) $@

run: $(EXEC)
	@./$<

clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(EXEC)
	@printf "$(OBJ_DIR) and $(EXEC) in $(NAME)\t \033[31;1mdeleted.\033[0m\n"

uninstall:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(EXEC)
	@@printf "$(NAME) \033[31;1muninstalled.\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall run

## Made by PETECO, 2025

# Diretório de destino para os arquivos .o
OBJ_DIR = obj

# Lista dos diretórios que contêm os arquivos .cpp
SRC_DIRS := src
# Para adicionar novos diretórios, siga o padrão abaixo:
# SRC_DIRS := src \
#             src/Entidades \
#             src/Entidades/Personagens \
#             src/Entidades/Obstaculos \
#             src/Fases \
#             src/Gerenciadores \
#             src/Menu

# Lista dos diretórios que contêm os arquivos .h
INCLUDE_DIRS := SFML/include \
                include
# Para adicionar novos diretórios, siga o padrão abaixo:
# INCLUDE_DIRS := SFML/include \
#                 include \
#                 include/Entidades \
#                 include/Entidades/Personagens \
#                 include/Entidades/Personagens/Inimigos \
#                 include/Entidades/Projetil \
#                 include/Entidades/Obstaculos \
#                 include/Fases \
#                 include/Gerenciadores \
#                 include/Menu

# Lista de diretivas -I para os includes
HEADER_FILES := $(foreach dir,$(INCLUDE_DIRS),-I$(dir))

# Lista de arquivos .cpp
CPP_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

# Transforma arquivos .cpp em .o dentro de OBJ_DIR
OBJ_FILES := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(CPP_FILES))

# Regra padrão
all: clean create_obj_dirs compile link run

# Cria os diretórios de objetos recursivamente
create_obj_dirs:
	@mkdir -p $(OBJ_DIR)
	@for dir in $(SRC_DIRS); do \
		if echo "$$dir" | grep -q "^src/"; then \
			subdir=$${dir#src/}; \
			mkdir -p "$(OBJ_DIR)/$$subdir"; \
		fi \
	done

# Compila cada arquivo .cpp
$(OBJ_DIR)/%.o: src/%.cpp
	@echo "Compilando $<..."
	@g++ -c $< -o $@ $(HEADER_FILES)

compile: $(OBJ_FILES)

# Linka os .o em um executável
link:
	@echo "Linkando..."
	@g++ $(OBJ_FILES) -o main $(SFML_LIB_PATH) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL

# Executa o programa
run:
	@echo "Executando..."
	@./main

# Limpa os arquivos objeto e binários
clean:
	@echo "Makefile PETECO 2025"
	@echo "Limpando..."
	@rm -rf $(OBJ_DIR) main

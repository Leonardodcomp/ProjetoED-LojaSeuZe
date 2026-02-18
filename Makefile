# Se não for Windows(SO que fizemos o sistema de Seu Zé)
ifeq ($(OS),Windows_NT)
    target = programa.exe
    run_cmd = .\\programa.exe
else
    # Se não for Windows, assume Linux ou Mac
    target = programa
    run_cmd = ./programa
endif

all: $(target) run

$(target): main.c
	gcc main.c -o $(target)

run:
	@echo "--- Bom dia, seu Ze. Loja abrindo ---"
	$(run_cmd)
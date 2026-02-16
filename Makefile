all: programa run

programa:
	gcc main.c -o programa

run:
	@echo "--- Bom dia, seu Ze. Loja abrindo ---"
	.\programa.exe
all:
	@echo 'Compiling...'
	@nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin

clean:
	@echo 'Removing files...'
	@rm -rf ./bin/boot.bin
default:
	rm kernel.o
	riscv64-unknown-elf-gcc -Wall -Wextra -c -mcmodel=medany kernel.c -o kernel.o -ffreestanding
	riscv64-unknown-elf-as -c entry.S -o entry.o
	riscv64-unknown-elf-ld -T linker.ld -nostdlib kernel.o entry.o -o kernel.elf
		qemu-system-riscv64 -machine type=virt \
		-cpu rv64 \
		-accel tcg \
		-smp 1 \
		-bios none \
		-kernel kernel.elf \
		-serial mon:stdio \
		-nographic \
		-s \

qemu:
	qemu-system-riscv64 -machine type=virt \
		-cpu rv64 \
		-accel tcg \
		-smp 1 \
		-bios none \
		-kernel kernel.elf \
		-serial mon:stdio \
		-nographic \
		-s \

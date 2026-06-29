default:
	rm -f kernel.o
	# riscv64-unknown-elf-gcc -Wall -Wextra -c -mcmodel=medany kernel.c -o kernel.o -ffreestanding
	riscv64-unknown-elf-gcc -Wall -Wextra -c -mcmodel=medany kernel.c -o kernel.o -ffreestanding -g -O0
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
		-S

# -s \ # opens a GDB debugging server on port 1234
# -S # pauses the virtual machine's CPU immediately at startup.
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

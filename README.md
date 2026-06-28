# requirements
- RISC-V cross compiler

# installing RISC-V cross compiler


```bash
git clone https://github.com/riscv/riscv-gnu-toolchain.git
cd riscv-gnu-toolchain
./configure --prefix=/opt/riscv
make -j$(nproc)
echo "export PATH=/opt/risc/bin:\$PATH" >> ~/.bashrc
```
```

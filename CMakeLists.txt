cmake_minimum_required(VERSION 3.22)

project(Cos C)

set(CMAKE_C_STANDARD 17)

add_executable(Cos build.c)

add_custom_target(run COMMAND sudo ~/kvmtool/lkvm run -c 1 -k ../kernel.bin)

add_custom_command(TARGET Cos PRE_BUILD
        COMMAND echo "Build boot16 ..."
        COMMAND gcc -c ../boot16.S -o boot16.o
        COMMAND ld -Ttext=0x0 boot16.o -o boot16.elf
        COMMAND objcopy -O binary boot16.elf boot16.bin

        COMMAND echo "Build boot16 ..."
        COMMAND gcc -c ../boot32.S -o boot32.o
        COMMAND ld -Ttext=0x0 boot32.o -o boot32.elf
        COMMAND objcopy -O binary boot32.elf boot32.bin)

add_custom_target(clean-all
        COMMAND make clean
        COMMAND rm -rf *.elf *.o *.bin ../kernel.bin)

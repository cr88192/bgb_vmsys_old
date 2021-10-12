./scm2as tst2.scm tst2.as
nasm -f elf -g tst2.as
nasm -f elf -g tst_main.as
gcc -g -o tst2 tst2.o tst_main.o

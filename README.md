Ni hao
### Prepare the system
#### enable core dumps creation
```
ulimit -c unlimited
sudo sysctl -w kernel.core_pattern=/tmp/core-%e.%p.%h.%t
```
### Build sw
#### configure
```
> cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_PREFIX=.
-- The CXX compiler identification is GNU 13.2.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.3s)
-- Generating done (0.0s)
-- Build files have been written to: /home/weber/projects/t/build
```
#### build
```
> cmake --build build/  --parallel
[ 16%] Building CXX object src/lib/global/CMakeFiles/global.dir/global_lib.cpp.o
[ 33%] Linking CXX static library libglobal.a
[ 33%] Built target global
[ 50%] Building CXX object src/lib/class/CMakeFiles/class.dir/class_lib.cpp.o
[ 66%] Linking CXX shared library libclass.so
[ 66%] Built target class
[ 83%] Building CXX object src/app/CMakeFiles/stepper.dir/main.cpp.o
[100%] Linking CXX executable stepper
[100%] Built target stepper
```
#### install
```
> cmake --build build/  --parallel --target install
[ 33%] Built target global
[ 66%] Built target class
[100%] Built target stepper
Install the project...
-- Install configuration: "RelWithDebInfo"
-- Installing: /home/weber/projects/t/out/symbols
-- Installing: /home/weber/projects/t/out/symbols/class.ds
-- Installing: /home/weber/projects/t/out/symbols/stepper.ds
-- Installing: /home/weber/projects/t/out/bin/stepper
-- Set runtime path of "/home/weber/projects/t/out/bin/stepper" to "/home/weber/projects/t/out/lib"
-- Installing: /home/weber/projects/t/out/lib/libclass.so
-- Set runtime path of "/home/weber/projects/t/out/lib/libclass.so" to "/home/weber/projects/t/out/lib"
```
#### check
```bash
> ls out/bin/
stepper

> ls out/lib/
libclass.so

> ls out/symbols/
class.ds  stepper.ds

> file out/bin/stepper 
out/bin/stepper: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=cebdd49207bf24eba7d7fda4c3fb7825a59cf962, for GNU/Linux 3.2.0, stripped

> file out/lib/libclass.so 
out/lib/libclass.so: ELF 64-bit LSB shared object, x86-64, version 1 (GNU/Linux), dynamically linked, BuildID[sha1]=8b3b0c8d27731ae6230b066980aba7e1dbf87420, stripped

> file out/symbols/class.ds 
out/symbols/class.ds: ELF 64-bit LSB shared object, x86-64, version 1 (GNU/Linux), dynamically linked, BuildID[sha1]=8b3b0c8d27731ae6230b066980aba7e1dbf87420, with debug_info, not stripped

> file out/symbols/stepper.ds 
out/symbols/stepper.ds: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter *empty*, BuildID[sha1]=cebdd49207bf24eba7d7fda4c3fb7825a59cf962, for GNU/Linux 3.2.0, with debug_info, not stripped

> ldd out/bin/stepper
        linux-vdso.so.1 (0x00007ffdf40d9000)
        libclass.so => /home/weber/projects/t/out/lib/libclass.so (0x00007f0fbbc48000)
        libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f0fbb800000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f0fbbc11000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f0fbb400000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f0fbbb26000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f0fbbc67000)
```
### debug seg fault
#### create core
```bash
> out/bin/stepper 
start
object created
run execution
executing step 1
Segmentation fault (core dumped)
```
#### check core 
```asm
> ls /tmp/core* -l
-rw------- 1 weber weber 565248 дек  5 16:40 /tmp/core-stepper.2612778.compile.1701787231
-rw------- 1 weber weber 565248 дек  5 17:54 /tmp/core-stepper.2674192.compile.1701791669
```
#### run gdb
```bash
> gdb out/bin/stepper /tmp/core-stepper.2674192.compile.1701791669 
GNU gdb (Ubuntu 14.0.50.20230907-0ubuntu1) 14.0.50.20230907-git
Copyright (C) 2023 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from out/bin/stepper...
(No debugging symbols found in out/bin/stepper)

warning: exec file is newer than core file.
[New LWP 2674192]
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
Core was generated by `out/bin/stepper'.
Program terminated with signal SIGSEGV, Segmentation fault.
#0  0x00007f3768561c5b in globalFunc(int) () from /home/weber/projects/t/out/lib/libclass.so
```
### Debug in gdb
#### bt without symbols
```
(gdb) bt
#0  0x00007f3768561c5b in globalFunc(int) () from /home/weber/projects/t/out/lib/libclass.so
#1  0x00007f3768553f18 in A::run() () from /home/weber/projects/t/out/lib/libclass.so
#2  0x000055cfabddb17a in ?? ()
#3  0x00007f3767e280d0 in __libc_start_call_main (main=main@entry=0x55cfabddb130, argc=argc@entry=1, 
    argv=argv@entry=0x7ffdb2dbade8) at ../sysdeps/nptl/libc_start_call_main.h:58
#4  0x00007f3767e28189 in __libc_start_main_impl (main=0x55cfabddb130, argc=1, argv=0x7ffdb2dbade8, 
    init=<optimized out>, fini=<optimized out>, rtld_fini=<optimized out>, stack_end=0x7ffdb2dbadd8)
    at ../csu/libc-start.c:360
#5  0x000055cfabddb1e5 in ?? ()
```
#### load app symbols
```
(gdb) symbol-file out/symbols/stepper.ds 
Load new symbol table from "out/symbols/stepper.ds"? (y or n) y
Reading symbols from out/symbols/stepper.ds...
```
#### get shared library addr
```
(gdb) info sharedlibrary libclass.so
From                To                  Syms Read   Shared Object Library
0x00007f3768553ac0  0x00007f37685621eb  Yes (*)     /home/weber/projects/t/out/lib/libclass.so
(*): Shared library is missing debugging information.
```
#### load shared library symbols
```
(gdb) add-symbol-file out/symbols/class.ds 0x00007f3768553ac0
add symbol table from file "out/symbols/class.ds" at
        .text_addr = 0x7f3768553ac0
(y or n) y
Reading symbols from out/symbols/class.ds...
```
#### check bt with symbols
```
(gdb) bt
#0  globalFunc (v=1) at /home/weber/projects/t/src/lib/global/global_lib.cpp:10
#1  0x00007f3768553f18 in A::run (this=this@entry=0x7ffdb2dbacb4)
    at /home/weber/projects/t/src/lib/class/class_lib.cpp:24
#2  0x000055cfabddb17a in main () at /home/weber/projects/t/src/app/main.cpp:10

(gdb) f 1
#1  0x00007f3768553f18 in A::run (this=this@entry=0x7ffdb2dbacb4)
    at /home/weber/projects/t/src/lib/class/class_lib.cpp:24
24              step( );

(gdb) f 2
#2  0x000055cfabddb17a in main () at /home/weber/projects/t/src/app/main.cpp:10
10          obj.run( );
```
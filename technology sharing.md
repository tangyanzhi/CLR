This is a program composed of .Net virtual machine CLR, just-in-time compiler JIT, and front-end compiler Roslyn
Mainly to imitate the compilation process of C#.

Roslyn.h contains intermediate code, which is MSIL code similar to C#

The actual compiled code is in the project file

 The whole process of code:

1. Write intermediate code into Roslyn.h
2. Build memory model MethodDesc
3. Machine code JIT compilation part

It is mainly a simplified version and a very simplified version of the compilation process simulation. I wish you a happy play  


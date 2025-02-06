# Game.c

A game in c for Windows

## Compile and run

- Install and configure [msys2](https://www.msys2.org/)
- Add env variable, there's nice tutoriel on YouTube to help doing this

## Build command

### Minimal command

`gcc game.c paint.c -o game.exe`

### Small exe file build command

`gcc game.c paint.c -o game.exe -mwindows -Os -s -w -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-ident -fno-asynchronous-unwind-tables -fomit-frame-pointer`

Description

- `-lgdi32` Links the GDI (Graphics Device Interface) library, which is part of the Windows API used for rendering graphics.
- `-mwindows` Tells the linker that this is a GUI application, preventing a console window from opening.
- `-Os` Optimize for size.
- `-s` Strip all symbols from the executable.
- `-ffunction-sections -fdata-sections -Wl,--gc-sections` Enable garbage collection of unused functions and data.
- `-fno-ident` Remove the GCC version string from the binary.
- `-fno-asynchronous-unwind-tables` Prevent generation of unwind tables (not needed for simple applications).
- `-fomit-frame-pointer` Omits the frame pointer where possible, reducing binary size.

## Ressources

- [Windows API tutorials](https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program)
- [Direct2d](https://learn.microsoft.com/en-us/windows/win32/Direct2D/direct2d-portal)

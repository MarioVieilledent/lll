# Game.c

A game in c for Windows

## Compile and run

- Install and configure [msys2](https://www.msys2.org/)
- Add env variable, there's nice tutoriel on YouTube to help doing this

## Build command

`gcc game.c -o game.exe -lgdi32 -mwindows`

Description

- `-mwindows` Tells the linker that this is a GUI application, preventing a console window from opening.
- `-lgdi32` Links the GDI (Graphics Device Interface) library, which is part of the Windows API used for rendering graphics.

## Ressources

- [Windows API tutorials](https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program)
- [Direct2d](https://learn.microsoft.com/en-us/windows/win32/Direct2D/direct2d-portal)

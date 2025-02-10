gcc game.c paint.c -o game.exe -mwindows -Os -s -w -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-ident -fno-asynchronous-unwind-tables -fomit-frame-pointer
upx game.exe -o lll.exe
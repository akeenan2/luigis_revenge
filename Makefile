final: final.c
	gcc final.c gfx4.o -lX11 -lm -I/opt/X11/include/ -L/opt/X11/lib/ -o final
#include <framebuffer.h>

void framebuffer_put(unsigned int* memory, int pitch, int x, int y, int color){
	unsigned int offset = y*(pitch/4) + x;
	
	color |= 1 << 24;
	color |= 1 << 25;
	color |= 1 << 26;
	color |= 1 << 27;
	color |= 1 << 28;
	color |= 1 << 29;
	color |= 1 << 30;
	color |= 1 << 31;
	
	*(memory + offset) = color;
	
	return;
}

void framebuffer_put_rect(unsigned int* memory, int pitch, int x, int y, int w, int h, int color){
	for(int xx = 0; xx < w; xx++){
		for(int yy = 0; yy < h; yy++){
			framebuffer_put(memory, pitch, x+xx, y+yy, color);
		}
	}
	
	return;
}
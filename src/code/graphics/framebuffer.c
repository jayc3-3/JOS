#include <font.h>
#include <framebuffer.h>

unsigned int* fb_buffer;
int fb_pitch;
int fb_depth;
int fb_width;
int fb_height;

void fb_init(unsigned long long framebufferAddr, int pitch, int colorDepth, int width, int height){
	fb_buffer = (unsigned int*)((unsigned int)framebufferAddr);
	fb_pitch = pitch;
	fb_depth = colorDepth;
	fb_width = width;
	fb_height = height;

	return;
}

void fb_putPixel(int x, int y, int color){
	unsigned int position = y*(fb_pitch/4) + x;

	if(x > fb_width || y > fb_height)
		return;

	*(fb_buffer+position) = color;

	return;
}

void fb_clearScreen(int color){
	for(int x = 0; x < fb_width; x++){
		for(int y = 0; y < fb_height; y++){
			fb_putPixel(x, y, color);
		}
	}

	return;
}

void fb_drawRect(int x, int y, int w, int h, int color){;
	if(x > fb_width || y > fb_height || x+w > fb_width || y+h > fb_height){
		return;
	}

	for(int xx = 0; xx < w; xx++){
		for(int yy = 0; yy < h; yy++){
			fb_putPixel(x+xx, y+yy, color);
		}
	}
	
	return;
}

void fb_drawChar(char c, int x, int y, int color){
	if(x > fb_width || y > fb_height || x+16 > fb_width || y+16 > fb_height){
		return;
	}

	unsigned char* glyph = FONT[(int)c];

	for(int yy = 0; yy < 8; yy++){
		for(int xx = 0; xx < 8; xx++){
			if(glyph[yy] & (1 << xx)){
				fb_putPixel(x+(xx*2), y+(yy*2), color);
				fb_putPixel(x+(xx*2), y+(yy*2)+1, color);
				fb_putPixel(x+(xx*2)+1, y+(yy*2), color);
				fb_putPixel(x+(xx*2)+1, y+(yy*2)+1, color);
			}
		}
	}

	return;
}
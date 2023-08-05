#include <font.h>
#include <framebuffer.h>

unsigned int* fb_buffer;
int fb_pitch;
int fb_width;
int fb_height;

void fb_init(unsigned long long framebufferAddr, int pitch, int width, int height){
	fb_buffer = (unsigned int*)((unsigned int)framebufferAddr);
	fb_pitch = pitch;
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

void fb_drawChar(char c, int x, int y, int scale, int color){
	if(x+16 > fb_width || y+16 > fb_height){
		return;
	}

	unsigned char* glyph = FONT[(int)c];

	for(int yy = 0; yy < 8; yy++){
		for(int xx = 0; xx < 8; xx++){
			if(glyph[yy] & (1 << xx)){
				for(int xi = 0; xi < scale; xi++){
					for(int yi = 0; yi < scale; yi++){
						fb_putPixel(x+(xx*scale)+xi, y+(yy*scale)+yi, color);
					}
				}

			}
		}
	}

	return;
}

void fb_drawImage(int x, int y, int w, int h, int scale, int* pixels){
    int j;
	for (int l = j = 0; l < h; l++){
        for (int i = 0; i < w; i++, j++){
			for(int xi = 0; xi < scale; xi++){
				for(int yi = 0; yi < scale; yi++){
					fb_putPixel(x + (i*scale)+xi, y + (l*scale)+yi, pixels[j]);
				}
			}
        }
    }

	return;
}
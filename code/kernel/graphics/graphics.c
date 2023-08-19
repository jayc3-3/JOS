#include <bool.h>
#include <multiboot.h>
#include <graphics.h>
#include <framebuffer.h>
#include <font.h>

int graphics_width;
int graphics_height;
int graphics_pitch;
int graphics_bpp;
unsigned int* graphics_memory;

bool graphics_init(multiboot_info_t* multiboot_info){
	if(multiboot_info->framebuffer_type != MULTIBOOT_FRAMEBUFFER_TYPE_RGB)
		return false;
	
	graphics_width = multiboot_info->framebuffer_width;
	graphics_height = multiboot_info->framebuffer_height;
	graphics_pitch = multiboot_info->framebuffer_pitch;
	graphics_bpp = multiboot_info->framebuffer_bpp;
	graphics_memory = (unsigned int*)((unsigned int)multiboot_info->framebuffer_addr);
	
	return true;
}

void graphics_clear(int color){
	framebuffer_put_rect(graphics_memory, graphics_pitch, 0, 0, graphics_width, graphics_height, color);
	
	return;
}

void graphics_rect(int x, int y, int w, int h, int color){
	framebuffer_put_rect(graphics_memory, graphics_pitch, x, y, w, h, color);
	
	return;
}

bool graphics_putc(char c, int x, int y, int scale, int color){
	if(x+(8*scale) > graphics_width || y+(8*scale) > graphics_height)
		return false;
	if(x < 0 || y < 0)
		return false;
	
	unsigned char* glyph = font[(int)c];
	
	for(int yy = 0; yy < 8; yy++){
		for(int xx = 0; xx < 8; xx++){
			if(glyph[yy] & (1 << xx)){
				for(int xi = 0; xi < scale; xi++){
					for(int yi = 0; yi < scale; yi++)
						framebuffer_put(graphics_memory, graphics_pitch, x+(xx*scale)+xi, y+(yy*scale)+yi, color);
				}
			}
		}
	}
	
	return true;
}
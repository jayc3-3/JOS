#include <multiboot.h>
#include <framebuffer.h>
#include <string.h>
#include <console.h>

void JOSkernel(multiboot_info_t* mbInfo){
	fb_init(mbInfo->framebuffer_addr, mbInfo->framebuffer_pitch, mbInfo->framebuffer_pitch, mbInfo->framebuffer_width, mbInfo->framebuffer_height);
	console_init(mbInfo->framebuffer_width, mbInfo->framebuffer_height, 0xFFFFFF, 0x000000);

	for(;;){
	}
}
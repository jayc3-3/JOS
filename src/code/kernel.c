#include <multiboot.h>
#include <framebuffer.h>
#include <string.h>
#include <console.h>
#include <ports.h>
#include <ps2.h>
#include <JOSimage.h>
#include <ps2Keyboard.h>

void JOSkernel(multiboot_info_t* mbInfo){
	fb_init(mbInfo->framebuffer_addr, mbInfo->framebuffer_pitch, mbInfo->framebuffer_width, mbInfo->framebuffer_height);
	console_init(mbInfo->framebuffer_width, mbInfo->framebuffer_height, 2, 0xFFFFFF, 0x000000);

	if(!ps2_init())
		console_print("ERROR: Unable to initialize PS/2 controller\n");
	
	{
		int c = 1000000000;
		while(c > 0)
			c--;
	}

	displayJOSlogo();

	{
		int c = 1000000000;
		while(c > 0)
			c--;
	}
	
	console_clear();
	ps2Keyboard_init();
	console_print("Keyboard test zone | Press LSHIFT to toggle caps\n");

	for(;;){
		char c = ps2Keyboard_pollInput();
		ps2Keyboard_printInput(c);
	}
}
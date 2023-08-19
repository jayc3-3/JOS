#include <multiboot.h>
#include <bool.h>
#include <console.h>
#include <cpu.h>
#include <pic.h>
#include <interrupts.h>
#include <ps2.h>
#include <ps2_keyboard.h>

void halt(void){ // Infinite loop
	start_halt:
	asm("cli");
	asm("hlt");
	goto start_halt;
}

void jos_kernel(multiboot_info_t* multiboot_info){
	
	// Beginning of kernel initialization 
	
	if(!console_init(multiboot_info, 0xFFFFFF, 0xFFFFFF, 0xFFFF00, 0xFF0000, 0x000000, true))
		return;
	
	console_printi("CPU vendor string: ");
	{
		char temp_string[14];
		console_print(cpu_get_vendor_string(temp_string));
	}
	
	ps2_init();
	ps2_keyboard_init();
	
	idt_load();
	isr_init();
	
	pic_remap(0x20, 0x28);
	for(int i = 0; i < 16; i++)
		pic_set_mask(i);
	
	// End of kernel initialization / Start of userland initialization
	
	console_print("\nKeyboard test zone | Press LSHIFT to toggle capitalization\n");
	
	ps2_keyboard_enable_interrupts();
	
	console_active = true;
	//console_clear();
	
	// End of userland initialization / Beginning of userland loop
	
	asm("sti");
	
	for(;;){
		if(ps2_keyboard_key_pressed){
			ps2_keyboard_key_pressed = false;
			char translated_key = ps2_keyboard_translate(ps2_keyboard_pressed);
			if(translated_key != 0x00)
				console_printc(translated_key);
		}
	}
	
	// End of userland loop (should be impossible to reach)
	
	console_active = true; // Enable console (if not already enabled) 
	console_clear(); // Clear screen
	console_printe("System escaped userland loop; halting system\n"); // Print error message
	halt(); // Halt system
}
#include <bool.h>
#include <ps2.h>
#include <cpu.h>
#include <util.h>
#include <multiboot.h>
#include <console.h>

bool ps2 = false;
bool ps2_port1 = false;
bool ps2_port2 = false;

void ps2_byte_out(unsigned short port, unsigned char data){
	unsigned char status = cpu_byte_in(PS2_STAT);
	
	while(CHECK_BIT(status, 1))
		status = cpu_byte_in(PS2_STAT);
	
	cpu_byte_out(port, data);
	
	return;
}

unsigned char ps2_byte_in(unsigned short port){
	unsigned char status = cpu_byte_in(PS2_STAT);
	
	while(!CHECK_BIT(status, 0))
		status = cpu_byte_in(PS2_STAT);
	
	unsigned char data = cpu_byte_in(port);
	
	return data;
}

bool ps2_init(void){
	ps2_byte_out(PS2_COM, 0xAD);
	ps2_byte_out(PS2_COM, 0xA7);
	cpu_byte_in(PS2_DAT);
	
	ps2_byte_out(PS2_COM, 0x20);
	
	unsigned char config_byte = ps2_byte_in(PS2_DAT);
	
	config_byte &= ~(1 << 0);
	config_byte &= ~(1 << 1);
	config_byte &= ~(1 << 6);
	
	if(CHECK_BIT(config_byte, 5))
		ps2_port2 = true;
	
	ps2_byte_out(PS2_COM, 0x60);
	ps2_byte_out(PS2_DAT, config_byte);
	
	ps2_byte_out(PS2_COM, 0xAA);
	if(ps2_byte_in(PS2_DAT) != 0x55){
		console_printe("PS/2 controller test failed\n");
		ps2 = false;
		return false;
	}
	else{
		console_printi("PS/2 controller test passed\n");
		ps2 = true;
	}
	
	ps2_byte_out(PS2_COM, 0xAB);
	if(ps2_byte_in(PS2_DAT) != 0x00){
		console_printw("PS/2 port 1 failed test\n");
		ps2_port1 = false;
	}
	else{
		console_printi("PS/2 port 1 passed test\n");
		ps2_port1 = true;
	}
	
	ps2_byte_out(PS2_COM, 0xA9);
	if(ps2_byte_in(PS2_DAT) != 0x00){
		console_printw("PS/2 port 2 failed test\n");
		ps2_port2 = false;
	}
	else{
		console_printi("PS/2 port 2 passed test\n");
		ps2_port2 = true;
	}
	
	skip_port2:
	
	if(!ps2_port1 && !ps2_port2){
		console_printe("No PS/2 ports available\n");
		ps2 = false;
		return false;
	}
	
	if(ps2_port1){
		ps2_byte_out(PS2_COM, 0xAE);
		
		ps2_init_port1_reset:
		ps2_byte_out(PS2_DAT, 0xFF);
		
		unsigned char data = ps2_byte_in(PS2_DAT);
		
		switch(data){
			case 0xFA:
				console_printi("PS/2 port 1 device successfully reset\n");
				break;
			
			case 0xFE:
				goto ps2_init_port1_reset;
			
			default:
				console_printw("PS/2 port 1 device failed reset\n");
				break;
		}
		
		ps2_init_port1_disable:
		ps2_byte_out(PS2_DAT, 0xF5);
		switch(ps2_byte_in(PS2_DAT)){
			case 0xFA:
				break;
			
			case 0xFE:
				goto ps2_init_port1_disable;
			
			default: break;
		}
	}
	if(ps2_port2){
		ps2_byte_out(PS2_COM, 0xA8);
		
		ps2_init_port2_reset:
		ps2_byte_out(PS2_COM, 0xD4);
		ps2_byte_out(PS2_DAT, 0xFF);
		
		unsigned char data = ps2_byte_in(PS2_DAT);
		
		switch(data){
			case 0xFA:
				console_printi("PS/2 port 2 device successfully reset\n");
				break;
			
			case 0xFE:
				console_printw("PS/2 port 2 device failed reset\n");
				goto ps2_init_port2_reset;
			
			default:
				console_printw("PS/2 port 2 device failed reset\n");
				break;
		}
		
		ps2_init_port2_disable:
		ps2_byte_out(PS2_COM, 0xD4);
		ps2_byte_out(PS2_DAT, 0xF5);
		switch(ps2_byte_in(PS2_DAT)){
			case 0xFA:
				break;
			
			case 0xFE:
				goto ps2_init_port2_disable;
			
			default: break;
		}
	}
	
	done:
	
	console_printi("PS/2 controller successfully initialized\n");
	
	return true;
}
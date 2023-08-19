#include <bool.h>
#include <pic.h>
#include <cpu.h>

void pic_remap(int master_offset, int slave_offset){
	unsigned char master_mask, slave_mask;
	
	master_mask = cpu_byte_in(MPIC_DAT);
	slave_mask = cpu_byte_in(SPIC_DAT);
	
	cpu_byte_out(MPIC_COM, 0x10 | 0x01);
	cpu_wait();
	cpu_byte_out(SPIC_COM, 0x10 | 0x01);
	cpu_wait();
	cpu_byte_out(MPIC_DAT, master_offset);
	cpu_wait();
	cpu_byte_out(SPIC_DAT, slave_offset);
	cpu_wait();
	cpu_byte_out(MPIC_DAT, 4);
	cpu_wait();
	cpu_byte_out(SPIC_DAT, 2);
	cpu_wait();
	
	cpu_byte_out(MPIC_DAT, 0x01);
	cpu_wait();
	cpu_byte_out(SPIC_DAT, 0x01);
	cpu_wait();
	
	cpu_byte_out(MPIC_DAT, master_mask);
	cpu_wait();
	cpu_byte_out(SPIC_DAT, slave_mask);
	
	return;
}

void pic_set_mask(unsigned char line){
	unsigned short port;
	unsigned char value;
	
	if(line < 8){
		port = MPIC_DAT;
	}
	else{
		port = SPIC_DAT;
		line -= 8;
	}
	
	value = cpu_byte_in(port) | (1 << line);
	cpu_byte_out(port, value);
	
	return;
}

void pic_clear_mask(unsigned char line){
	unsigned short port;
	unsigned char value;
	
	if(line < 8){
		port = MPIC_DAT;
	}
	else{
		port = SPIC_DAT;
		line -= 8;
	}
	
	value = cpu_byte_in(port) & ~(1 << line);
	cpu_byte_out(port, value);
	
	return;
}

void pic_eoi(unsigned char irq){
	if(irq > 7){
		cpu_byte_out(SPIC_COM, 0x20);
		cpu_wait();
	}
	
	cpu_byte_out(MPIC_COM, 0x20);
	
	return;
}
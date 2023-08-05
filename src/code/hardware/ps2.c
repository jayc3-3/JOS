#include <ports.h>
#include <util.h>
#include <console.h>
#include <ps2.h>

int ps2Port1 = 0;
int ps2Port2 = 0;

unsigned char ps2_readPort(unsigned short port){
	char status = ports_byteIn(PS2_STATUS);
	while(!CHECK_BIT(status, 0)) {status = ports_byteIn(PS2_STATUS);}
	char data = ports_byteIn(port);
	return data;
}

void ps2_sendPort(unsigned short port, unsigned char data){
	char status = ports_byteIn(PS2_STATUS);
	while(CHECK_BIT(status, 1)) {status = ports_byteIn(PS2_STATUS);}
	ports_byteOut(port, data);
	return;
}

int ps2_init(void){
	console_print("INFO: Initalizing PS/2 driver\n");

	ps2_sendPort(PS2_COMMAND, 0x20);
	char configByte = ps2_readPort(PS2_DATA);

	configByte &= ~(1 << 0);
	configByte &= ~(1 << 1);
	configByte &= ~(1 << 6);
	if(CHECK_BIT(configByte, 5))
		//ps2Port2 = 1;

	ps2_sendPort(PS2_COMMAND, 0x60);
	ps2_sendPort(PS2_DATA, configByte);

	ps2_sendPort(PS2_COMMAND, 0xAD);
	ps2_sendPort(PS2_COMMAND, 0xA7);

	ports_byteIn(PS2_DATA);

	ps2_sendPort(PS2_COMMAND, 0xAA);
	if(ps2_readPort(PS2_DATA) != 0x55)
		return 0;
		
	ps2_sendPort(PS2_COMMAND, 0xAB);
	if(ps2_readPort(PS2_DATA) == 0x00)
		ps2Port1 = 1;
	
	ps2_sendPort(PS2_COMMAND, 0xA9);
	if(ps2_readPort(PS2_DATA) != 0x00)
		ps2Port2 = 0;

	if(!ps2Port1)
		console_print("WARNING: PS/2 port 1 unavailable for use\n");
	else
		console_print("INFO: PS/2 port 1 available for use\n");
	if(!ps2Port2)
		console_print("WARNING: PS/2 port 2 unavailable for use\n");
	else
		console_print("INFO: PS/2 port 2 available for use\n");

	console_print("INFO: PS/2 controller successfully initialized\n");

	return 1;
}
#ifndef __SOCKET_H
#define __SOCKET_H

extern void register_xfer(char *pskb);
extern void sw_update(char *pskb);
extern void get_temperature(char *pskb); 
extern void get_voltage(char *pskb);
extern void eeprom_xfer(char *pskb);
#endif

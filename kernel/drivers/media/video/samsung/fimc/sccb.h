#ifndef __SCCB_H__
#define __SCCB_H__

typedef unsigned char 	unint8;
typedef unsigned short 	unint16;
typedef unsigned int  	unint32;
typedef signed char 	int8;
typedef signed short	int16;
typedef signed int 		int32;


int     sccb_init(void);
void 	sccb_write(unint8 IdAddr, unint8 SubAddr, unint8 data);
unint8 	sccb_read(unint8 IdAddr, unint8 SubAddr);
void 	sccb_write16(unint8 IdAddr, unint16 SubAddr, unint8 data);
unint8 	sccb_read16(unint8 IdAddr, unint16 SubAddr);


#define SCCB

#endif// __SCCB_H__

#ifndef __SERIALCOMMUNICATE_H__
#define __SERIALCOMMUNICATE_H__
 
int Open_serial(unsigned char* port);
int Serial_Config (int folder);
int Write_serial(int folder, unsigned char* string, int sizeof_string);
int Read_serial(int folder, unsigned char* buff, int sizeof_buff);

 
#endif //__SERIALCOMMUNICATE_H__

#ifndef __SIM800L_H__
#define __SIM800L_H__
 
int AT_Commant(int folder, unsigned char* AT_write, unsigned char* AT_return);
int config_sim800l(int folder);
int sim800l_call(int folder, unsigned char* sdt);
int sim800l_sms(int folder, unsigned char* sdt, unsigned char* msg);


#endif //__SIM800L_H__

#include <sim800l.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // file control definitions
#include <errno.h> // error number definitions
#include "Serialcommunicate.h" // POISX terminal control definitions
#include <time.h>



int AT_Commant(int folder, unsigned char* AT_write, unsigned char* AT_return)
{
        unsigned char AT_buff[100];
        int AT_lengh_read,AT_lengh_write;

        // AT_lengh_read = Read_serial(folder, AT_buff, (sizeof(AT_buff)-1) );
        AT_lengh_write = Write_serial(folder,AT_write, strlen(AT_write) );
        if(AT_lengh_write < 0)
        {
                perror("write AT failed");
                return -1;
        }
        else
        {       
                sleep(0.5);
                AT_lengh_read = Read_serial(folder, AT_buff, (sizeof(AT_buff)-1) );
                sleep(0.5);
                if(AT_lengh_read >= 0) 
                {
                        if( (AT_buff[2] == AT_return[0]) & (AT_buff[3] == AT_return[1]) )
                        {
                                printf("%s", AT_buff);
                               return 0;
                        }
                        else
                        {       
                                printf("%s", AT_buff);
                               perror("faill return");
                               return -1;
                        }
                }
                else if (AT_lengh_read < 0)
                {
                        perror("Error from read");
                        return -1;
                }
        }
}

int config_sim800l(int folder)
{
        printf("start config sim800l\n");
        int AT_lengh_write;
        unsigned char buff[100];

        //sent AT
        AT_lengh_write = AT_Commant(folder,"AT\n\r", "OK\n\r" );
        if(AT_lengh_write < 0)
        {
                perror("write AT failed");
                sleep(1);
                return -1;
        }
        sleep(0.5);
        //sent baudrate = 115200
        AT_lengh_write = AT_Commant(folder,"AT+IPR=115200\n\r", "OK\n\r" );
        if(AT_lengh_write < 0)
        {
                perror("write baudrate failed");
                // sleep(1);
                return -1;
        }
        sleep(0.5);
        //sent echo = 0
        AT_lengh_write = AT_Commant(folder,"ATE0\n\r", "OK\n\r" );
        if(AT_lengh_write < 0)
        {
                perror("write echo failed");
                // sleep(1);
                return -1;
        }
        sleep(0.5);
        //sent msg -> text
        AT_lengh_write = AT_Commant(folder,"AT+CMGF=1\n\r","OK\n\r");
        if (AT_lengh_write == -1)
        {
                perror("failded to sms -> text");
                // sleep(1);
                return -1;
        }
        sleep(0.5);
        //sent AT&W -> save setup
        AT_lengh_write = AT_Commant(folder, "AT&W\n\r","OK\n\r");
        if(AT_lengh_write == -1)
        {
                perror("failed to save config");
                // sleep(1);
                return -1;
        }       

        printf("data lose from config\n");
        //read all data reciever lose
        sleep(5);
        AT_lengh_write = Read_serial(folder, buff, 100 );
        if(AT_lengh_write > 0)
        {
            printf("%s",buff);
        } 
        printf("end config\n");
        return 0;
}

int sim800l_call(int folder, unsigned char* sdt)
{
        printf("start call to: %s\n", sdt);
        int n;
        unsigned char buff[100];

        unsigned char atd[100];
        unsigned char end[100];
        strcpy(atd, "ATD");
        strcpy(end, ";\n\r");

        strcat(atd, sdt);
        strcat(atd, end);

        n = Write_serial(folder, atd, strlen(atd) );
        sleep(1);
        if (n < 0)
        {
                perror("faill to call");
                return -1;
        }
        n = Read_serial(folder, buff, (sizeof(buff) -1) );
        if ((n > 0)&(buff[2]=='O')&(buff[3]=='K'))
        {
                printf("%s",buff);
                return 0;
        }
        printf("%s",buff);
        return -1;
}

int sim800l_sms(int folder, unsigned char* sdt, unsigned char* msg)
{
        int n;
        unsigned char sms[100];
        unsigned char end_text[100];

        unsigned char buff1[100];
        unsigned char buff2[100];
        unsigned char buff3[100];

        unsigned char atd[100];
        unsigned char end[100];
        
        strcpy(atd, "AT+CMGS=\"");
        strcpy(end, "\"\n\r");
        strcat(atd, sdt);
        strcat(atd, end);

        strcpy(end_text, "\x1A");
        // strcpy(sms, "sms:");
        
        strcat(sms, msg);
        strcat(sms, end_text);

        n = Write_serial(folder,atd, strlen(atd) );
        if (n < 0)
        {
                perror("failded to sent sms 1");
                return -1;
        }
        printf("%s",atd);
        
        sleep(2);
        n = Read_serial(folder, buff2, (sizeof(buff2) -1) );
        printf("%s",buff2);
        // if (buff2[2] != '>')
        // {
        //         perror("failded to sent sms");
        //         return -1;                
        // }

        sleep(1);
        n = Write_serial(folder, sms, strlen(sms) );
        if (n<0)
        {
                perror("failded to sent sms 2");
                return -1;
        }

        printf("%s",sms);
        sleep(5);
        n = Read_serial(folder, buff3, (sizeof(buff3) -1) );
        printf("\n%s\n",buff3);
        // if (buff3[2] != 'O')
        // {
        //         perror("failded to sent sms 3");
        //         return -1;
        // }
        sleep(1);
        return 0;
}


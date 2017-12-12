#include <Serialcommunicate.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // file control definitions
#include <errno.h> // error number definitions
#include <termios.h> // POISX terminal control definitions
#include <time.h>

int Open_serial(unsigned char* port)
{
    int folder;
    folder = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    return folder;
}

/* set
 * - baudrate: 115200
 * - 8 bit data
 * - no parity
 * - 1 stop bit
 */
int Serial_Config (int folder)
{
    struct termios serial;
    /* get current option for port */
    tcgetattr(folder, &serial);
    /* set baudrate 115200 */
    cfsetispeed(&serial, B115200);
    cfsetospeed(&serial, B115200);
    /* enable receiver and set local mode */
    serial.c_cflag |= (CLOCAL | CREAD); // c_cflag: control flag
                                        //      CLOCAL: Local line - d$
                                        //      CREAD:  Enable receive$
    /* set 8 bit data,  np parity, 1 stop bit */

    serial.c_cflag &= ~PARENB;
    serial.c_cflag &= ~CSTOPB;
    serial.c_cflag &= ~CSIZE;
    serial.c_cflag |= CS8;

    /* disable hardware flow control */
    // serial.c_cflag &= ~CNEW_RTSCTS; 

    /* choose raw input */
    serial.c_lflag &= ~(ICANON | ECHOE | ISIG);

    /*serialchoose raw output */
    serial.c_oflag &= ~OPOST;

    /* set to port */
    if (tcsetattr(folder, TCSAFLUSH, &serial) != 0)  //        Flush $
    {
        perror("can not set configuration to serial port");
	return -1;
    }
    return 0;
}


//write serial
int Write_serial(int folder, unsigned char* string, int sizeof_string)
{
	return write(folder,string, sizeof_string);
}

//read serial
int Read_serial(int folder, unsigned char* buff, int sizeof_buff)
{
	return read(folder, buff, sizeof_buff);
}

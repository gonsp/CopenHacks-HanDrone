/////////////////////////////////////////////////
// Serial port interface program               //
/////////////////////////////////////////////////

#include <stdio.h> // standard input / output functions
#include <string.h> // string function definitions
#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <termios.h> // POSIX terminal control definitionss
#include <time.h>   // time calls


int open_port(void)
{
	int fd; // file description for the serial port
	
	fd = open("/dev/ttyACM0", O_RDWR );
	//fd = open("salida.txt", O_RDWR | O_NOCTTY | O_NDELAY);
	
	if(fd == -1) // if open is unsucessful
	{
		//perror("open_port: Unable to open /dev/ttyUSB0 - ");
		printf("open_port: Unable to open /dev/ttyACM0. \n");
	}
	else
	{
		fcntl(fd, F_SETFL, 0);
		printf("port is open.\n");
	}
	
	return(fd);
} //open_port

int configure_port(int fd)      // configure the port
{
	struct termios port_settings;      // structure to store the port settings in

	cfsetispeed(&port_settings, B115200);    // set baud rates
	cfsetospeed(&port_settings, B115200);

	port_settings.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
	port_settings.c_cflag &= ~CSTOPB;
	port_settings.c_cflag &= ~CSIZE;
	port_settings.c_cflag |= CS8;
	
	tcsetattr(fd, TCSANOW, &port_settings);    // apply the settings to the port
	return(fd);

} //configure_port

int query_modem(int fd)   // query modem with an AT command
{
	char n;
	fd_set rdfs;
	struct timeval timeout;
	
	// initialise the timeout structure
	timeout.tv_sec = 10; // ten second timeout
	timeout.tv_usec = 0;
	
	//Open the input_file
	int fi;
	fi = open("entry.txt", O_RDWR | O_NOCTTY | O_NDELAY);
	if(fi == -1) { printf("open_file: Unable to open entry. \n");}
	else {
		fcntl(fi, F_SETFL, 0);
		printf("entry is open.\n");
	}
	
	//Open the check_file
	int ff;
	ff = open("exit.txt", O_RDWR | O_NOCTTY | O_NDELAY);
	if(ff == -1) { printf("open_file: Unable to open exit. \n"); }
	else {
		fcntl(ff, F_SETFL, 0);
		printf("file is open.\n");
	}
	
        /*char test = 'a';
	write(fd, &test, sizeof(char));
	read(fd, &test, sizeof(char));
        write(ff, &test, sizeof(char));*/
        //Transfer data;
        char send_bytes[1];
        char recived_bytes[1];
        while(read(fi, send_bytes, 1)){

	  write(fd, send_bytes, 1);
	  //printf("Wrote the bytes. \n");
	  
	  read(fd, recived_bytes, 1);
	  write(ff, recived_bytes, 1);

        }

	return 0;
	
} //query_modem

int main(void)
{ 
	int fd = open_port();
	configure_port(fd);
	query_modem(fd);
	
	return(0);
	
} //main

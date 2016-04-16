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
	
	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
	//fd = open("salida.txt", O_RDWR | O_NOCTTY | O_NDELAY);
	
	if(fd == -1) // if open is unsucessful
	{
		//perror("open_port: Unable to open /dev/ttyUSB0 - ");
		printf("open_port: Unable to open /dev/ttyUSB0. \n");
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
	fi = open("test.txt", O_RDWR | O_NOCTTY | O_NDELAY);
	if(fi == -1) { // if open is unsucessful
		//perror("open_port: Unable to open /dev/ttyS0 - ");
		printf("open_port: Unable to open ttyUSB0. \n");
	}
	else {
		fcntl(fi, F_SETFL, 0);
		printf("port is open.\n");
	}
	
	unsigned char send_bytes[1];
	//Create byte array
	while( read(fi, send_bytes, 1) ){
	
	  write(fd, send_bytes, 1);  //Send data
	  printf("Wrote the bytes. \n");
	  
	 /* // do the select
	  n = select(fd + 1, &rdfs, NULL, NULL, &timeout);
	  
	  // check if an error has occured
	  if(n < 0)
	  {
	  perror("select failed\n");
	  }
	  else if (n == 0)
	  {
	  puts("Timeout!");
	  }
	  else
	  {
	  printf("\nBytes detected on the port!\n");
	  }
	}*/
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
#include "serial.h"
#include "get_core_details.h"

void get_hex_string(int num , char *hex_string, int string_size)
{
  int rmndr = 0, temp = 0;
  int quo = 0, i = 0, j = 0, k =0;
  quo = num;
  char store_hex_string[50]= {"0"};
  while(quo != 0)
  {
    temp = quo % 16;
    if(temp < 10) 
      temp = temp + 48;
   else
      temp = temp + 55;
   store_hex_string[i] = temp;
   quo =quo / 16;
   i++;
  }

  for(j = (i-1); j>= 0; j--)
  {
    hex_string[k]=store_hex_string[j];
    k++;
  }

}


/*make separate file main_switch*/
void main_switch(char check_case)
{
	switch(check_case) 
	{
	
	  case 'a':serial_tx("Help---- use below commands \r\n");
	           serial_tx("b: Get Running Core Details \r\n");   	
	         break; 
		
	  case 'b':get_core_details(); 	
	         break; 
	         
	  default:
	       serial_tx("Default case \r\n");	
	}
		
	
}



int c_entry(void)
{
	char str[32];
    int num = 45;
    int fret = 0;
    char hex_string[32] = {0};
    int i =0;
	serial_init(115200);
	int val = 0;
	serial_byte_rx();
	serial_tx("Welcome to 1st bootloader\r\n");
    //get_hex_string(num, hex_string, 32);
    serial_tx("Enter ? for help\r\n");    
    //serial_tx("\n");
    for (;;)
	{
		serial_tx("Cmd> ");
		serial_rx(str, 32);
		serial_tx("You entered: ");
		serial_tx(str);
		serial_tx("\r\n");
		main_switch(str[0]);  
		
	}
	serial_shut();
	return 0;
}




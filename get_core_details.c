#include "get_core_details.h"
#include "serial.h"

int set_string_zero(char *string, int size)
{
	int i =0;
	while(i < 50)
	{
	  string[i] = '\0';
	  i++;	
	}
   return 0;
}

unsigned long get_main_id(int *case_s)
{
	unsigned long reg_val;
	/* read c0 MAIN_ID */
	__asm__ __volatile__("mrc p15, 0, %0, c0, c0, 0\n" : "=r" (reg_val) : : );
	 *case_s = 1;
	return reg_val;
	
}	


unsigned long get_processor_feature_0(int *case_s)
{
	unsigned long reg_val;
	/* read c0 MAIN_ID */
	__asm__ __volatile__("mrc p15, 0, %0, c0, c1, 0\n" : "=r" (reg_val) : : );
	 *case_s = 2;
	return reg_val;
	
}


unsigned long get_processor_feature_1(int *case_s)
{
	unsigned long reg_val;
	/* read c0 MAIN_ID */
	__asm__ __volatile__("mrc p15, 0, %0, c0, c1, 1\n" : "=r" (reg_val) : : );
	 *case_s = 3;
	return reg_val;
	
}


unsigned long get_processor_multiprocessor_id(int *case_s)
{
	unsigned long reg_val;
	/* read c0 MAIN_ID */
	__asm__ __volatile__("mrc p15, 0, %0, c0, c0, 5\n" : "=r" (reg_val) : : );
	 *case_s = 4;
	return reg_val;
	
}

unsigned long get_processor_debug_feature_model(int *case_s)
{
	unsigned long reg_val;
	/* read c0 MAIN_ID */
	__asm__ __volatile__("mrc p15, 0, %0, c0, c1, 2\n" : "=r" (reg_val) : : );
	 *case_s = 5;
	return reg_val;
	
}

unsigned long get_processor_Secure_Configuration_Register(int *case_s)
{
	unsigned long reg_val;
	/* read c0 MAIN_ID */
	__asm__ __volatile__("mrc p15, 0, %0, c1, c1, 0\n" : "=r" (reg_val) : : );
	 *case_s = 6;
	return reg_val;
	
}


int detail_list(core_detail *reg_detail) 
{
	char hex_string[50] ={0};
	switch(reg_detail->detail_case) 
	{
	  case 1: serial_tx("Case 1: 	Core Main ID Detail = ");
	          get_hex_string( reg_detail->reg , hex_string, 50);
              serial_tx(hex_string);
	          serial_tx("\r\n");
	          break;
	          
	  case 2: set_string_zero(hex_string,50);
	          serial_tx("Case 2: 	Core Feature 0 = ");
	          get_hex_string( reg_detail->reg , hex_string, 50);
              serial_tx(hex_string);
	          serial_tx("\r\n");
	          break;       
	  
	  case 3: set_string_zero(hex_string,50);
	          serial_tx("Case 3: 	Core Feature 1 = ");
	          get_hex_string( reg_detail->reg , hex_string, 50);
              serial_tx(hex_string);
	          serial_tx("\r\n");
	          break;       

	  case 4: set_string_zero(hex_string,50);
	          serial_tx("Case 4: 	multiprocessor_id = ");
	          get_hex_string( reg_detail->reg , hex_string, 50);
              serial_tx(hex_string);
	          serial_tx("\r\n");
	          break;
	          
	  case 5: set_string_zero(hex_string,50);
	          serial_tx("Case 5: 	debug_feature_model = ");
	          get_hex_string( reg_detail->reg , hex_string, 50);
              serial_tx(hex_string);
	          serial_tx("\r\n");
	          break;	          

	  case 6: set_string_zero(hex_string,50);
	          serial_tx("Case 6: 	Secure_Configuration_Register = ");
	          get_hex_string( reg_detail->reg , hex_string, 50);
              serial_tx(hex_string);
	          serial_tx("\r\n");
	          break;	          
	          	          
	  case 0 :serial_tx("0 case  \r\n");
	          break;
      
      default :serial_tx("default case  \r\n");
               
      
	}
	
	return 0;
}



int get_core_details(void)
{
  	unsigned long res_detail = 0;
  	core_detail detail;
  	
  	detail.detail_case = 0;
  	detail.reg = 0;
  	
	detail.reg = get_main_id(&detail.detail_case);
	detail_list(&detail);
	
	detail.reg = 0;
	detail.reg = get_processor_feature_0(&detail.detail_case);
	detail_list(&detail);

    detail.reg = 0;
	detail.reg = get_processor_feature_1(&detail.detail_case);
	detail_list(&detail);

    detail.reg = 0;
	detail.reg = get_processor_multiprocessor_id(&detail.detail_case);
	detail_list(&detail);

    detail.reg = 0;
	detail.reg = get_processor_debug_feature_model(&detail.detail_case);
	detail_list(&detail);
	
    detail.reg = 0;
	detail.reg = get_processor_Secure_Configuration_Register(&detail.detail_case);
	detail_list(&detail);	


}

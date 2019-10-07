// Purpose: control 2 7-segment displays to LPC4088

#include"mbed.h" 
 
DigitalOut clk(p27);  //clock pin
DigitalOut rst(p28);  //Reset|Clear pin
DigitalOut data(p30); //Data pin
 
void EdgeClock(){ //This is the function where we sync the clock with data
 wait(0.000001); 
 clk = 1; 
 wait(0.000001); 
 clk=0; 
  
} 
int main(){ 
 rst = 0; //Reset is set to 0, ready to take data
 EdgeClock(); //Clock sequence
 rst = 1; //reset
 EdgeClock(); //Clock sequence
  
// We are using negative logic!!!!	
	
	// segment labels: {d,g,f,e,d,c,b,a}
			int arr[16][8] = {  
			{1,1,0,0,0,0,0,0}, //0 
      {1,1,1,1,1,0,0,1}, //1 
      {1,0,1,0,0,1,0,0}, //2 
      {1,0,1,1,0,0,0,0}, //3 
      {1,0,0,1,1,0,0,1}, //4 
      {1,0,0,1,0,0,1,0}, //5 
      {1,0,0,0,0,0,1,0}, //6 
      {1,1,1,1,1,0,0,0}, //7 
      {1,0,0,0,0,0,0,0}, //8 
      {1,0,0,1,1,0,0,0}, //9
			{1,0,0,0,1,0,0,0}, //A
 			{1,0,0,0,0,0,1,1}, //B
			{1,1,0,0,0,1,1,0}, //C
			{1,0,1,0,0,0,0,1}, //D
			{1,0,0,0,0,1,1,0}, //E
			{1,0,0,0,1,1,1,0}}; //F
			
      //{0,1,1,1,1,1,1,1}}; //dot 
			
 // We are displaying the decimal point last
 int dot[2][8] =  {{0,1,1,1,1,1,1,1}, //dot ON 
      {1,1,1,1,1,1,1,1}}; //dot OFF 
        
// Execute while logic=1
while(1){ 
	for (int m = 0; m< 16; m++)
	{
	for (int a = 0; a < 16; a++)
	{ //Loop going through the rows
		for(int i = 0; i < 16; i++)
		{ //Loop going through columns
			for (int j = 0; j < 8 ; j++) 
			{ //Here we add data to grid
          data = arr[i][j]; 
			    EdgeClock(); 
      } 
     
			for (int k = 0; k < 8 ; k++) 
			{ 
				data = arr[a][k]; 
				EdgeClock(); 
      }   
			for (int l = 0; l < 8 ; l++) //3 segement
			{ 
				data = arr[m][l]; 
				EdgeClock(); 
      }   
     wait(0.3); 
   }// end for 
 } 
	}
//Blink dots protocal 
for (int a = 1; a >= 0 ; a--){   
 for (int b = 0; b < 8; b++){ 
    data = dot[a][b]; 
    EdgeClock(); 
    } 
   } 
  wait(0.25); 
for (int a = 0; a < 2 ; a++){   
 for (int b = 0; b < 8; b++)
{ 
    data = dot[a][b]; 
    EdgeClock(); 
    } 
   } 
  wait(0.25); 
}//end while 
           
 
}//end main
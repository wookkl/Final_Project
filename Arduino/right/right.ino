#include <CapacitiveSensor.h>
#include <SoftwareSerial.h>
#define SBUF_SIZE 64
int EBimuAsciiParser(float *item, int number_of_item);
CapacitiveSensor   cs_2_3 = CapacitiveSensor(2, 3);
CapacitiveSensor   cs_5_6 = CapacitiveSensor(5, 6); 
SoftwareSerial bluetooth(4, 7);
//Flex-------------------------------------------
char rightHandFlex[6][40];  //flexData -> dtostrf
int flexData[6];            //get FlexData
float sensitivity = 0.1;
//-----------------------------------------------


//Ebimu------------------------------------------
char rightHandEbimu[6][40]; //axis_6 -> sprintf
float axis_6[6];            //get 6 axis(euler, acc)
char sbuf[SBUF_SIZE];
signed int sbuf_cnt=0;
//-----------------------------------------------


//Capacitor--------------------------------------
long capacitor_left;
long capacitor_right;
char capacitor_buff[2][40];
char vcc_buff[40];
//-----------------------------------------------


void setup()
{ 
  //Serial
  Serial.begin(115200);
  //Bluetooth
  bluetooth.begin(115200); 
} 

void loop() 
{
   capacitor_left = cs_2_3.capacitiveSensorRaw(30);    // 1번 터치패드 값 수신 <접촉시 55~60의 정수값 출력>
   capacitor_right = cs_5_6.capacitiveSensorRaw(30);    // 2번 터치패드 값 수신 <접촉시 55~60의 정수값 출력> 

   //test
      for(int i = 0; i < 6; i++){
        int value = analogRead(i);
        float filtered_value = value;
        filtered_value = filtered_value * (1 - sensitivity) + value * sensitivity;
        flexData[i] = int(filtered_value);

        if (i == 0){
//          Serial.println(flexData[i]);
          if (flexData[i] > 770){
            flexData[i] = 3000;
          }
          else{
            flexData[i] = 100;
          }
        }
        sprintf(rightHandFlex[i],"%d",flexData[i]); 
   }
   //test

   //Ebimu---------------------------------------------
   EBimuAsciiParser(axis_6,6);
   //Serial.print("  6 axis : ");
   for(int i = 0; i < 6; i++){
      dtostrf(axis_6[i],7,2,rightHandEbimu[i]);
   }
   //--------------------------------------------------

   
   //Capacitor-----------------------------------------
   if(capacitor_left > 80){
      sprintf(capacitor_buff[0],"true");
   }
   else{
      sprintf(capacitor_buff[0],"false");
   }
   if(capacitor_right > 65){
      sprintf(capacitor_buff[1],"true");
   }
   else{
      sprintf(capacitor_buff[1],"false");
   }
   
//   Serial.print("오른쪽 Capacitor : ");
//   Serial.print(capacitor_buff[0]);
//   Serial.print("  왼쪽 Capacitor : ");
//   Serial.println(capacitor_buff[1]);

   
   //Bluetooth Send------------------------------------
   for(int i = 0 ;i < 6; i++){
      bluetooth.write(rightHandEbimu[i]);
      bluetooth.write(",");
   }
   bluetooth.write(rightHandFlex[1]);
   bluetooth.write(",");
   bluetooth.write(rightHandFlex[5]);
   bluetooth.write(",");
   bluetooth.write(rightHandFlex[4]);
   bluetooth.write(",");
   bluetooth.write(rightHandFlex[3]);
   bluetooth.write(",");
   bluetooth.write(rightHandFlex[2]);
   bluetooth.write(",");
   bluetooth.write(rightHandFlex[0]);
   bluetooth.write(",");

//  Serial.print("엄지 : "); Serial.print(rightHandFlex[1]);
//  Serial.print("  검지 : "); Serial.print(rightHandFlex[5]);
//  Serial.print("  중지 : "); Serial.print(rightHandFlex[4]);
//  Serial.print("  약지 : "); Serial.print(rightHandFlex[3]);
//  Serial.print("  새끼 : "); Serial.print(rightHandFlex[2]);
//  Serial.print("  손목 : "); Serial.println(rightHandFlex[0]);
//
//  
//  Serial.print("  X : "); Serial.print(rightHandEbimu[0]);
//  Serial.print("  Y : "); Serial.print(rightHandEbimu[1]);
//  Serial.print("  Z : "); Serial.print(rightHandEbimu[2]);
//  Serial.print("  AccX : "); Serial.print(rightHandEbimu[3]);
//  Serial.print("  AccY : "); Serial.print(rightHandEbimu[4]);
//  Serial.print("  AccZ : "); Serial.println(rightHandEbimu[5]);

  
   for(int i = 0; i < 2; i++){
      bluetooth.write(capacitor_buff[i]);
      bluetooth.write(",");
   }
   bluetooth.write("5.00");
   bluetooth.write("\n");
   //--------------------------------------------------
   delay(5);
} 

int EBimuAsciiParser(float *item, int number_of_item)
{
    int n,i;
    int rbytes;
    char *addr; 
    int result = 0;
    
    rbytes = Serial.available();
    for(n=0;n<rbytes;n++)
    {
        sbuf[sbuf_cnt] = Serial.read();
        if(sbuf[sbuf_cnt]==0x0a)
        {
            addr = strtok(sbuf,",");
            for(i=0;i<number_of_item;i++)
            {
                item[i] = atof(addr);
                addr = strtok(NULL,",");
            }
            result = 1;
        }
        else if(sbuf[sbuf_cnt]=='*')
        {     
            sbuf_cnt=-1;
        }
 
        sbuf_cnt++;
        if(sbuf_cnt>=SBUF_SIZE) sbuf_cnt=0;
    }
    return result;
}

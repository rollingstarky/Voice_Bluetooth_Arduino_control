#include <SoftwareSerial.h>          
#define RxD 10                // 设置 RX 引脚为 10 
#define TxD 11                // 设置 TX 引脚为 11
#define LED_PIN 6          	  // 设置 LED 引脚为 6

SoftwareSerial btSerial(RxD,TxD);			//串口定义
String voice;								//定义 voice 变量保存字符串指令

void setup() {  
    pinMode(LED_PIN, OUTPUT);				// LED 引脚模式为输出（OUTPUT） 
    btSerial.begin(9600);					//串口码率
}

// 将串口传输的字符连接成完整的字符串指令
String getVoice(){
    while (btSerial.available()) {      
        delay(50);       
        char orderChar = btSerial.read();          
        if (orderChar == '#') 
            break;            
            voice += orderChar; 
    }  
    return voice;
}

//控制函数。解析字符串指令，调用相应的动作
void control(String voice){
	//打开 on
    if(voice.endsWith("on")){
        digitalWrite(LED_PIN,1);  
        Serial.println("Light ON");
    }
    //关闭 off
    if(voice.endsWith("off")){
        digitalWrite(LED_PIN,0);
        Serial.println("Light OFF");
    }
    //淡入 fade in
    if(voice.endsWith("in")){
        fade_in();
        Serial.println("fading in...");
    }
    //淡出 fade out
    if(voice.endsWith("out")){
      fade_out();
      Serial.println("fading out...");
    }
}

//淡入函数
void fade_in(){
    for(int value=0;value<=255;value+=5){
        analogWrite(LED_PIN,value);
        delay(100);
    }
}

//淡出函数
void fade_out(){
  for(int value=255;value>=0;value-=5){
      analogWrite(LED_PIN,value);
      delay(100);
  }
}

//主循环
void loop() {
    voice=getVoice();
    control(voice);
    voice="";			// voice 回到初始状态
}




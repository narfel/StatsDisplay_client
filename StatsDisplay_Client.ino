#include <LiquidCrystal_I2C.h>
#include <string.h>
LiquidCrystal_I2C lcd(0x27,16,2); //I2C address
int cpuTemp  = 0;
int cpuUsage = 0;
int gpuTemp  = 0;
int gpuUsage = 0;
int memUsage = 1;
int gpuMemUsage = 1;
String staticData = "";
unsigned long lastDataTime = 0;
const unsigned long errorTimeout = 1000;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Waiting for data");
  delay(1);
}

void loop() {
  if (Serial.available() > 0){
    lastDataTime = millis();
    staticData = Serial.readStringUntil('\n');
    Serial.println(staticData);
    cpuTemp = staticData.substring(1,4).toInt();
    cpuUsage = staticData.substring(5,8).toInt();
    gpuTemp = staticData.substring(9,12).toInt();
    gpuUsage = staticData.substring(13,16).toInt();
    memUsage = staticData.substring(17,20).toInt();
    gpuMemUsage = staticData.substring(21,24).toInt();
    
    // Only display the data if all of the values are valid
    if (cpuTemp >= 0 && cpuUsage >= 0 && gpuTemp >= 0 && gpuUsage >= 0 && memUsage >= 0 && gpuMemUsage >= 0){
      displayData();
    }
  } else if (millis() - lastDataTime > errorTimeout) {
    displayError(1);
  }
  delay(1000);
}

void displayError(int code){
  lcd.clear();
  lcd.noBacklight(); // Turn off the backlight when there is no data
  lcd.setCursor(0,1);
  switch (code){
    case 1:{
      lcd.print("No Data");
    }
  }
}

void displayData(){
    lcd.backlight(); // Turn on the backlight when data is available
    delay(50); // small delay for stability

    String cpuTempStr = (cpuTemp >= 0 && cpuTemp <= 99) ? String(cpuTemp) : "xx";
    String memUsageStr = (memUsage >= 0 && memUsage <= 99) ? String(memUsage) : "xx";
    String cpuUsageStr = (cpuUsage >= 0 && cpuUsage <= 99) ? String(cpuUsage) : "xx";

    lcd.setCursor(0, 0);
    lcd.print("C:");
    lcd.print(cpuTempStr);
    lcd.print("\xDF");
    lcd.print("C ");

    lcd.setCursor(7, 0);
    lcd.print("M");
    lcd.print(memUsageStr);
    lcd.print("% ");

    lcd.setCursor(12, 0);
    lcd.print("L");
    lcd.print(cpuUsageStr);
    lcd.print("%");

    String gpuTempStr = (gpuTemp >= 0 && gpuTemp <= 99) ? String(gpuTemp) : "xx";
    String gpuMemUsageStr = (gpuMemUsage >= 0 && gpuMemUsage <= 99) ? String(gpuMemUsage) : "xx";
    String gpuUsageStr = (gpuUsage >= 0 && gpuUsage <= 99) ? String(gpuUsage) : "xx";

    lcd.setCursor(0, 1);
    lcd.print("G:");
    lcd.print(gpuTempStr);
    lcd.print("\xDF");
    lcd.print("C ");

    lcd.setCursor(7, 1);
    lcd.print("M");
    lcd.print(gpuMemUsageStr);
    lcd.print("% ");

    lcd.setCursor(12, 1);
    lcd.print("L");
    lcd.print(gpuUsageStr);
    lcd.print("%");

}

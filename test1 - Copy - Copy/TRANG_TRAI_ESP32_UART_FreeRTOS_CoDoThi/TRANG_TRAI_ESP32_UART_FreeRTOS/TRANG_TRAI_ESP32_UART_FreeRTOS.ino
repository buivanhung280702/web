#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "webtrangTrai.h"
SemaphoreHandle_t dataSemaphore;

String Thoitiet;
String motaThoitiet;
String iconThoiTiet;
String forecast_weather[4];
String forecast_weather_sym[4];

String openWeatherMapApiKey = "41bc87da446a4e2b5aec138648ce1f9d";
String city = "Thủ%20Ðô%20Hà%20Nội";
String countryCode = "1581129";
String units = "metric";
String strjsonBuffer;
String ICONval[20];
DynamicJsonBuffer jsonBuffer;

WebServer server(80);
const char* ssid = "a";
const char* password = "012345678";

const int relayPins[] = {2, 18, 4, 5};
bool lightStates[] = {false, false, false, false};

char count_string = 0;
char arr_received1[50], count_string1 = 0;
unsigned int Count_Time = 0, Split_count = 0;
char temp_char, arr_received[15], *temp[15];

String tmp; 
String nhiet_do;
String do_am;
String do_am_dat;
String anh_sang;

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  Serial.println("Dang ket noi : ");
 
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("...");
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("HTTP server da bat dau");
  
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
  }

  server.on("/",handleRoot);
  server.on("/readHUMI",dataHUMI);
  server.on("/readTEMP",dataTEMP);
  server.on("/readLIGHT",dataLIGHT);
  server.on("/readSM",dataSM);
  server.on("/readTHOITIET",dataTHOITIET);
  server.on("/readMTTHOITIET",dataMTTHOITIET);
  server.on("/readICON",dataICONTT);
  server.on("/readLightState", HTTP_GET, readLightState);
  server.on("/toggleLight1", HTTP_POST, toggleLight1);
  server.on("/toggleLight2", HTTP_POST, toggleLight2); 
  server.on("/toggleLight3", HTTP_POST, toggleLight3); 
  server.on("/toggleLight4", HTTP_POST, toggleLight4);
  server.begin();
  
  // Khởi tạo Semaphore
  dataSemaphore = xSemaphoreCreateMutex();
  
  xTaskCreatePinnedToCore(
    GetWeatherDataTask,        // Function to implement the task
    "GetWeatherDataTask",      // Name of the task
    10000,                     // Stack size in words
    NULL,                      // Task input parameter
    1,                         // Priority of the task
    NULL,                      // Task handle.
    0                          // Core where the task should run
  );
  xTaskCreatePinnedToCore(
    ReadUARTDataTask,          // Function to implement the task
    "ReadUARTDataTask",        // Name of the task
    10000,                     // Stack size in words
    NULL,                      // Task input parameter
    1,                         // Priority of the task
    NULL,                      // Task handle.
    0                          // Core where the task should run
  );
 xTaskCreatePinnedToCore(
    SendUARTDataTask,          // Function to implement the task
    "SendUARTDataTask",        // Name of the task
    10000,                     // Stack size in words
    NULL,                      // Task input parameter
    1,                         // Priority of the task
    NULL,                      // Task handle.
    0                          // Core where the task should run
  );
}
/*************************************/
void loop() {
  server.handleClient();
  vTaskDelay(pdMS_TO_TICKS(10)); 
}
/**************************************/
void GetWeatherDataTask(void *pvParameters) {
  while (1) {
    Get_Weather_Data();
    vTaskDelay(pdMS_TO_TICKS(60000)); // Delay 10 phút (600000 milliseconds)
  }
}

void ReadUARTDataTask(void *pvParameters) {
  while (1) {
    DocUART(); // Đọc dữ liệu từ cổng UART
    vTaskDelay(pdMS_TO_TICKS(10)); // Delay giữa các lần đọc UART
  }
}

void SendUARTDataTask(void *pvParameters) {
  while (1) {
    sendLightStatesViaUART(); // gửi liệu từ cổng UART
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay giữa các lần gửi UART
  }
}

void handleRoot() {
  server.send(200,"text/html",webtrangTrai);
}

void dataTEMP() {
  // Lấy Semaphore trước khi truy cập vào biến toàn cục
  if (xSemaphoreTake(dataSemaphore, portMAX_DELAY) == pdTRUE) {
    String nhietdo = String(nhiet_do);
    server.send(200,"text/plane",nhietdo);
    // Trả lại Semaphore sau khi hoàn thành
    xSemaphoreGive(dataSemaphore);
  }
}

void dataHUMI() {
  if (xSemaphoreTake(dataSemaphore, portMAX_DELAY) == pdTRUE) {
    String doam = String(do_am);
    server.send(200,"text/plane",doam);
    xSemaphoreGive(dataSemaphore);
  }
}

void dataLIGHT() {
  if (xSemaphoreTake(dataSemaphore, portMAX_DELAY) == pdTRUE) {
    String anhsang = String(anh_sang);
    server.send(200,"text/plane",anhsang);
    xSemaphoreGive(dataSemaphore);
  }
}

void dataSM() {
  if (xSemaphoreTake(dataSemaphore, portMAX_DELAY) == pdTRUE) {
    String dat = String(do_am_dat);
    server.send(200,"text/plane",dat);
    xSemaphoreGive(dataSemaphore);
  }
}

void dataTHOITIET() {
  if (xSemaphoreTake(dataSemaphore, portMAX_DELAY) == pdTRUE) {
    String TTval = Thoitiet;
    server.send(200,"text/plane",TTval);
    xSemaphoreGive(dataSemaphore);
  }
}

void dataMTTHOITIET() {
  if (xSemaphoreTake(dataSemaphore, portMAX_DELAY) == pdTRUE) {
    String MTTTval = motaThoitiet;
    server.send(200,"text/plane",MTTTval);
    xSemaphoreGive(dataSemaphore);
  }
}

void dataICONTT() {
  if (xSemaphoreTake(dataSemaphore, portMAX_DELAY) == pdTRUE) {
    String ICONval = "<img src=\"http://openweathermap.org/img/w/" + iconThoiTiet + ".png\" alt=\"Weather Icon\">";
    server.send(200,"text/plane",ICONval);
    xSemaphoreGive(dataSemaphore);
  }
}
void readLightState() {
    String lightStateStr = "";
    for (int i = 0; i < 4; i++) {
      lightStateStr += (lightStates[i]) ? "ON" : "OFF";
      if (i < 3) lightStateStr += ",";
    }
    server.send(200, "text/plain", lightStateStr);
    xSemaphoreGive(dataSemaphore);
}

void toggleLight(int lightIndex) {
    lightStates[lightIndex] = !lightStates[lightIndex];
    digitalWrite(relayPins[lightIndex], lightStates[lightIndex] ? HIGH : LOW);
    readLightState(); 
    sendLightStatesViaUART(); 
    xSemaphoreGive(dataSemaphore);
}

void toggleLight1() {
  toggleLight(0);
}

void toggleLight2() {
  toggleLight(1);
}

void toggleLight3() {
  toggleLight(2);
}

void toggleLight4() {
  toggleLight(3);
}

void sendLightStatesViaUART() {
  String lightStateStr = "";
  for (int i = 0; i < 4; i++) {
    lightStateStr += (lightStates[i] ? "1" : "0");
  }
  Serial.println(lightStateStr);
}

void DocUART() {
  if (Serial.available()) {
    temp_char = Serial.read();
    if (temp_char == '!') {
      char Buffer[1000];
      unsigned int len_Buffer;
      Split_count = 0;
      count_string = 0;
      temp[0] = strtok(arr_received, " ");
      while (temp[Split_count] != NULL) {
        Split_count++;
        temp[Split_count] = strtok(NULL, " ");
      }
      nhiet_do =  String(temp[0]) ;
      do_am = String(temp[1]);
      do_am_dat =  String(temp[2]) ;
      anh_sang = String(temp[3]);
    } else {
      arr_received[count_string++] = temp_char;
    }
  }
}


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName);
int httpResponseCode = http.GET();
String payload = "{}";
if (httpResponseCode == 200) {
payload = http.getString();
}
else {
Serial.print("Error code: ");
Serial.println(httpResponseCode);
//delay(500);
}
http.end();
return payload;
}

void Get_Weather_Data() {
  if(WiFi.status()== WL_CONNECTED){
    String current_serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&units=" + units + "&APPID=" + openWeatherMapApiKey + "&lang=vi";
    strjsonBuffer = httpGETRequest(current_serverPath.c_str());
    JsonObject& root = jsonBuffer.parseObject(strjsonBuffer);
   if (!root.success()) {
    Serial.println("parseObject() failed");
    //delay(500);
    return;
  }
    String str_current_weather = root["weather"][0]["main"];
    Thoitiet = str_current_weather;
    String str_current_weather_Description = root["weather"][0]["description"];
    motaThoitiet = str_current_weather_Description;
    String str_current_weather_sym = root["weather"][0]["icon"];
    iconThoiTiet = str_current_weather_sym;
    jsonBuffer.clear();
  }
}

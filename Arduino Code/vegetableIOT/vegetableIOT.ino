//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "iot-control-b550e-default-rtdb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "0Mi0yC1ZaCMQufElLSN8hC2WxnyrITz1k4QArHsB"
#define WIFI_SSID "ROOM_WIFI_2.4G"
#define WIFI_PASSWORD "MR49Rdrjxx"


#define Relay_light1 D0
#define Relay_light2 D1
#define Relay_light3 D2
#define Relay_light4 D3
#define Relay_pump1 D4
#define Relay_pump2 D5
#define Relay_pump3 D6
#define Relay_pump4 D7

int potpin = A0;
int Soilval;


char ntp_server1[20] = "pool.ntp.org";
char ntp_server2[20] = "time.nist.gov";
char ntp_server3[20] = "time.uni.net.th";

int timezone = 7 * 3600;
int dst = 0;

int updatestatus = 0;
int timeupdate = 0;

int light1 = 0;
int light2 = 0;
int light3 = 0;
int light4 = 0;

int pump1 = 0;
int pump2 = 0;
int pump3 = 0;
int pump4 = 0;

int light1_day_sun = 0;
int light1_day_mon = 0;
int light1_day_tue = 0;
int light1_day_wed = 0;
int light1_day_thu = 0;
int light1_day_fri = 0;
int light1_day_sat = 0;
int light1_end_h = 0;
int light1_end_m = 0;
int light1_start_h = 0;
int light1_start_m = 0;

int light2_day_sun = 0;
int light2_day_mon = 0;
int light2_day_tue = 0;
int light2_day_wed = 0;
int light2_day_thu = 0;
int light2_day_fri = 0;
int light2_day_sat = 0;
int light2_end_h = 0;
int light2_end_m = 0;
int light2_start_h = 0;
int light2_start_m = 0;

int light3_day_sun = 0;
int light3_day_mon = 0;
int light3_day_tue = 0;
int light3_day_wed = 0;
int light3_day_thu = 0;
int light3_day_fri = 0;
int light3_day_sat = 0;
int light3_end_h = 0;
int light3_end_m = 0;
int light3_start_h = 0;
int light3_start_m = 0;

int light4_day_sun = 0;
int light4_day_mon = 0;
int light4_day_tue = 0;
int light4_day_wed = 0;
int light4_day_thu = 0;
int light4_day_fri = 0;
int light4_day_sat = 0;
int light4_end_h = 0;
int light4_end_m = 0;
int light4_start_h = 0;
int light4_start_m = 0;

int pump1_day_sun = 0;
int pump1_day_mon = 0;
int pump1_day_tue = 0;
int pump1_day_wed = 0;
int pump1_day_thu = 0;
int pump1_day_fri = 0;
int pump1_day_sat = 0;
int pump1_end_h = 0;
int pump1_end_m = 0;
int pump1_start_h = 0;
int pump1_start_m = 0;

int pump2_day_sun = 0;
int pump2_day_mon = 0;
int pump2_day_tue = 0;
int pump2_day_wed = 0;
int pump2_day_thu = 0;
int pump2_day_fri = 0;
int pump2_day_sat = 0;
int pump2_end_h = 0;
int pump2_end_m = 0;
int pump2_start_h = 0;
int pump2_start_m = 0;

int pump3_day_sun = 0;
int pump3_day_mon = 0;
int pump3_day_tue = 0;
int pump3_day_wed = 0;
int pump3_day_thu = 0;
int pump3_day_fri = 0;
int pump3_day_sat = 0;
int pump3_end_h = 0;
int pump3_end_m = 0;
int pump3_start_h = 0;
int pump3_start_m = 0;

int pump4_day_sun = 0;
int pump4_day_mon = 0;
int pump4_day_tue = 0;
int pump4_day_wed = 0;
int pump4_day_thu = 0;
int pump4_day_fri = 0;
int pump4_day_sat = 0;
int pump4_end_h = 0;
int pump4_end_m = 0;
int pump4_start_h = 0;
int pump4_start_m = 0;

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

FirebaseJson json;

void printResult(FirebaseData &data);

void setup()
{
  pinMode(Relay_light1, OUTPUT);
  pinMode(Relay_light2, OUTPUT);
  pinMode(Relay_light3, OUTPUT);
  pinMode(Relay_light4, OUTPUT);

  pinMode(Relay_pump1, OUTPUT);
  pinMode(Relay_pump2, OUTPUT);
  pinMode(Relay_pump3, OUTPUT);
  pinMode(Relay_pump4, OUTPUT);


  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData.setResponseSize(1024);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  
  configTime(timezone, dst, ntp_server1, ntp_server2, ntp_server3);
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
}

void loop() {

  // Display ------------------------------------------------------------------------
 
  Serial.print(light1); Serial.print(":");
  Serial.print(light2); Serial.print(":");
  Serial.print(light3); Serial.print(":");
  Serial.print(light4); Serial.print(":");
  Serial.print(pump1); Serial.print(":");
  Serial.print(pump2); Serial.print(":");
  Serial.print(pump3); Serial.print(":");
  Serial.print(pump4); Serial.print("\n");

  Serial.print(light1_day_sun); Serial.print(":");
  Serial.print(light1_day_mon); Serial.print(":");
  Serial.print(light1_day_tue); Serial.print(":");
  Serial.print(light1_day_wed); Serial.print(":");
  Serial.print(light1_day_thu); Serial.print(":");
  Serial.print(light1_day_fri); Serial.print(":");
  Serial.print(light1_day_sat); Serial.print(":");
  Serial.print(light1_start_h); Serial.print(":");
  Serial.print(light1_start_m); Serial.print(":");
  Serial.print(light1_end_h); Serial.print(":");
  Serial.print(light1_end_m); Serial.print("\n");

  Serial.print(light2_day_sun); Serial.print(":");
  Serial.print(light2_day_mon); Serial.print(":");
  Serial.print(light2_day_tue); Serial.print(":");
  Serial.print(light2_day_wed); Serial.print(":");
  Serial.print(light2_day_thu); Serial.print(":");
  Serial.print(light2_day_fri); Serial.print(":");
  Serial.print(light2_day_sat); Serial.print(":");
  Serial.print(light2_start_h); Serial.print(":");
  Serial.print(light2_start_m); Serial.print(":");
  Serial.print(light2_end_h); Serial.print(":");
  Serial.print(light2_end_m); Serial.print("\n");

  Serial.print(light3_day_sun); Serial.print(":");
  Serial.print(light3_day_mon); Serial.print(":");
  Serial.print(light3_day_tue); Serial.print(":");
  Serial.print(light3_day_wed); Serial.print(":");
  Serial.print(light3_day_thu); Serial.print(":");
  Serial.print(light3_day_fri); Serial.print(":");
  Serial.print(light3_day_sat); Serial.print(":");
  Serial.print(light3_start_h); Serial.print(":");
  Serial.print(light3_start_m); Serial.print(":");
  Serial.print(light3_end_h); Serial.print(":");
  Serial.print(light3_end_m); Serial.print("\n");
  
  Serial.print(light4_day_sun); Serial.print(":");
  Serial.print(light4_day_mon); Serial.print(":");
  Serial.print(light4_day_tue); Serial.print(":");
  Serial.print(light4_day_wed); Serial.print(":");
  Serial.print(light4_day_thu); Serial.print(":");
  Serial.print(light4_day_fri); Serial.print(":");
  Serial.print(light4_day_sat); Serial.print(":");
  Serial.print(light4_start_h); Serial.print(":");
  Serial.print(light4_start_m); Serial.print(":");
  Serial.print(light4_end_h); Serial.print(":");
  Serial.print(light4_end_m); Serial.print("\n");

  Serial.print(pump1_day_sun); Serial.print(":");
  Serial.print(pump1_day_mon); Serial.print(":");
  Serial.print(pump1_day_tue); Serial.print(":");
  Serial.print(pump1_day_wed); Serial.print(":");
  Serial.print(pump1_day_thu); Serial.print(":");
  Serial.print(pump1_day_fri); Serial.print(":");
  Serial.print(pump1_day_sat); Serial.print(":");
  Serial.print(pump1_start_h); Serial.print(":");
  Serial.print(pump1_start_m); Serial.print(":");
  Serial.print(pump1_end_h); Serial.print(":");
  Serial.print(pump1_end_m); Serial.print("\n");

  Serial.print(pump2_day_sun); Serial.print(":");
  Serial.print(pump2_day_mon); Serial.print(":");
  Serial.print(pump2_day_tue); Serial.print(":");
  Serial.print(pump2_day_wed); Serial.print(":");
  Serial.print(pump2_day_thu); Serial.print(":");
  Serial.print(pump2_day_fri); Serial.print(":");
  Serial.print(pump2_day_sat); Serial.print(":");
  Serial.print(pump2_start_h); Serial.print(":");
  Serial.print(pump2_start_m); Serial.print(":");
  Serial.print(pump2_end_h); Serial.print(":");
  Serial.print(pump2_end_m); Serial.print("\n");

  Serial.print(pump3_day_sun); Serial.print(":");
  Serial.print(pump3_day_mon); Serial.print(":");
  Serial.print(pump3_day_tue); Serial.print(":");
  Serial.print(pump3_day_wed); Serial.print(":");
  Serial.print(pump3_day_thu); Serial.print(":");
  Serial.print(pump3_day_fri); Serial.print(":");
  Serial.print(pump3_day_sat); Serial.print(":");
  Serial.print(pump3_start_h); Serial.print(":");
  Serial.print(pump3_start_m); Serial.print(":");
  Serial.print(pump3_end_h); Serial.print(":");
  Serial.print(pump3_end_m); Serial.print("\n");

  Serial.print(pump4_day_sun); Serial.print(":");
  Serial.print(pump4_day_mon); Serial.print(":");
  Serial.print(pump4_day_tue); Serial.print(":");
  Serial.print(pump4_day_wed); Serial.print(":");
  Serial.print(pump4_day_thu); Serial.print(":");
  Serial.print(pump4_day_fri); Serial.print(":");
  Serial.print(pump4_day_sat); Serial.print(":");
  Serial.print(pump4_start_h); Serial.print(":");
  Serial.print(pump4_start_m); Serial.print(":");
  Serial.print(pump4_end_h); Serial.print(":");
  Serial.print(pump4_end_m); Serial.print("\n");
  

  
   // Display ------------------------------------------------------------------------ 
   
  // NTP Server Time ------------------------------------------------------------------------
  
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);

  Serial.print(p_tm->tm_wday+1); Serial.print(":");
  Serial.print(p_tm->tm_hour); Serial.print(":");
  Serial.print(p_tm->tm_min); Serial.print(":");
  Serial.println(p_tm->tm_sec);
  Serial.print("\n");
  //Serial.println(ctime(&now)); 

  // NTP Server Time ------------------------------------------------------------------------

  
  // Auto Light 1  -----------------------------------------------------------------------

    if(((p_tm->tm_wday+1&&light1_day_sun)||(p_tm->tm_wday+1&&light1_day_mon)||(p_tm->tm_wday+1&&light1_day_tue)||(p_tm->tm_wday+1&&light1_day_wed)||(p_tm->tm_wday+1&&light1_day_thu)||(p_tm->tm_wday+1&&light1_day_fri)||(p_tm->tm_wday+1&&light1_day_sat))
    &&(p_tm->tm_hour==light1_start_h) && (p_tm->tm_min==light1_start_m))
    {
      light1 = 1;
    }
    else if(((p_tm->tm_wday+1&&light1_day_sun)||(p_tm->tm_wday+1&&light1_day_mon)||(p_tm->tm_wday+1&&light1_day_tue)||(p_tm->tm_wday+1&&light1_day_wed)||(p_tm->tm_wday+1&&light1_day_thu)||(p_tm->tm_wday+1&&light1_day_fri)||(p_tm->tm_wday+1&&light1_day_sat))
    &&(p_tm->tm_hour==light1_end_h) && (p_tm->tm_min==light1_end_m))
    {
      light1 = 0;
    }
  
  // Auto Light 1 -----------------------------------------------------------------------

  // Auto Light 2  -----------------------------------------------------------------------

    if(((p_tm->tm_wday+1&&light2_day_sun)||(p_tm->tm_wday+1&&light2_day_mon)||(p_tm->tm_wday+1&&light2_day_tue)||(p_tm->tm_wday+1&&light2_day_wed)||(p_tm->tm_wday+1&&light2_day_thu)||(p_tm->tm_wday+1&&light2_day_fri)||(p_tm->tm_wday+1&&light2_day_sat))
    &&(p_tm->tm_hour==light2_start_h) && (p_tm->tm_min==light2_start_m))
    {
      light2 = 1;
    }
    else if(((p_tm->tm_wday+1&&light2_day_sun)||(p_tm->tm_wday+1&&light2_day_mon)||(p_tm->tm_wday+1&&light2_day_tue)||(p_tm->tm_wday+1&&light2_day_wed)||(p_tm->tm_wday+1&&light2_day_thu)||(p_tm->tm_wday+1&&light2_day_fri)||(p_tm->tm_wday+1&&light2_day_sat))
    &&(p_tm->tm_hour==light2_end_h) && (p_tm->tm_min==light2_end_m))
    {
      light2 = 0;
    }
  
  // Auto Light 2 -----------------------------------------------------------------------

  // Auto Light 3  -----------------------------------------------------------------------

    if(((p_tm->tm_wday+1&&light3_day_sun)||(p_tm->tm_wday+1&&light3_day_mon)||(p_tm->tm_wday+1&&light3_day_tue)||(p_tm->tm_wday+1&&light3_day_wed)||(p_tm->tm_wday+1&&light3_day_thu)||(p_tm->tm_wday+1&&light3_day_fri)||(p_tm->tm_wday+1&&light3_day_sat))
    &&(p_tm->tm_hour==light3_start_h) && (p_tm->tm_min==light3_start_m))
    {
      light3 = 1;
    }
    else if(((p_tm->tm_wday+1&&light3_day_sun)||(p_tm->tm_wday+1&&light3_day_mon)||(p_tm->tm_wday+1&&light3_day_tue)||(p_tm->tm_wday+1&&light3_day_wed)||(p_tm->tm_wday+1&&light3_day_thu)||(p_tm->tm_wday+1&&light3_day_fri)||(p_tm->tm_wday+1&&light3_day_sat))
    &&(p_tm->tm_hour==light3_end_h) && (p_tm->tm_min==light3_end_m))
    {
      light3 = 0;
    }
  
  // Auto Light 3 -----------------------------------------------------------------------

  // Auto Light 4  -----------------------------------------------------------------------

    if(((p_tm->tm_wday+1&&light4_day_sun)||(p_tm->tm_wday+1&&light4_day_mon)||(p_tm->tm_wday+1&&light4_day_tue)||(p_tm->tm_wday+1&&light4_day_wed)||(p_tm->tm_wday+1&&light4_day_thu)||(p_tm->tm_wday+1&&light4_day_fri)||(p_tm->tm_wday+1&&light4_day_sat))
    &&(p_tm->tm_hour==light4_start_h) && (p_tm->tm_min==light4_start_m))
    {
      light4 = 1;
    }
    else if(((p_tm->tm_wday+1&&light4_day_sun)||(p_tm->tm_wday+1&&light4_day_mon)||(p_tm->tm_wday+1&&light4_day_tue)||(p_tm->tm_wday+1&&light4_day_wed)||(p_tm->tm_wday+1&&light4_day_thu)||(p_tm->tm_wday+1&&light4_day_fri)||(p_tm->tm_wday+1&&light4_day_sat))
    &&(p_tm->tm_hour==light4_end_h) && (p_tm->tm_min==light4_end_m))
    {
      light4 = 0;
    }
  
  // Auto Light 4 -----------------------------------------------------------------------

  // Auto Pump 1  -----------------------------------------------------------------------

    if(((p_tm->tm_wday+1&&pump1_day_sun)||(p_tm->tm_wday+1&&pump1_day_mon)||(p_tm->tm_wday+1&&pump1_day_tue)||(p_tm->tm_wday+1&&pump1_day_wed)||(p_tm->tm_wday+1&&pump1_day_thu)||(p_tm->tm_wday+1&&pump1_day_fri)||(p_tm->tm_wday+1&&pump1_day_sat))
    &&(p_tm->tm_hour==pump1_start_h) && (p_tm->tm_min==pump1_start_m))
    {
      pump1 = 1;
    }
    else if(((p_tm->tm_wday+1&&pump1_day_sun)||(p_tm->tm_wday+1&&pump1_day_mon)||(p_tm->tm_wday+1&&pump1_day_tue)||(p_tm->tm_wday+1&&pump1_day_wed)||(p_tm->tm_wday+1&&pump1_day_thu)||(p_tm->tm_wday+1&&pump1_day_fri)||(p_tm->tm_wday+1&&pump1_day_sat))
    &&(p_tm->tm_hour==pump1_end_h) && (p_tm->tm_min==pump1_end_m))
    {
      pump1 = 0;
    }
  
  // Auto Pump 1 -----------------------------------------------------------------------

  // Auto Pump 2  -----------------------------------------------------------------------

    if(((p_tm->tm_wday+1&&pump2_day_sun)||(p_tm->tm_wday+1&&pump2_day_mon)||(p_tm->tm_wday+1&&pump2_day_tue)||(p_tm->tm_wday+1&&pump2_day_wed)||(p_tm->tm_wday+1&&pump2_day_thu)||(p_tm->tm_wday+1&&pump2_day_fri)||(p_tm->tm_wday+1&&pump2_day_sat))
    &&(p_tm->tm_hour==pump2_start_h) && (p_tm->tm_min==pump2_start_m))
    {
      pump2 = 1;
    }
    else if(((p_tm->tm_wday+1&&pump2_day_sun)||(p_tm->tm_wday+1&&pump2_day_mon)||(p_tm->tm_wday+1&&pump2_day_tue)||(p_tm->tm_wday+1&&pump2_day_wed)||(p_tm->tm_wday+1&&pump2_day_thu)||(p_tm->tm_wday+1&&pump2_day_fri)||(p_tm->tm_wday+1&&pump2_day_sat))
    &&(p_tm->tm_hour==pump2_end_h) && (p_tm->tm_min==pump2_end_m))
    {
      pump2 = 0;
    }
  
  // Auto Pump 2 -----------------------------------------------------------------------

  // Auto Pump 3  -----------------------------------------------------------------------

    if(((p_tm->tm_wday+1&&pump3_day_sun)||(p_tm->tm_wday+1&&pump3_day_mon)||(p_tm->tm_wday+1&&pump3_day_tue)||(p_tm->tm_wday+1&&pump3_day_wed)||(p_tm->tm_wday+1&&pump3_day_thu)||(p_tm->tm_wday+1&&pump3_day_fri)||(p_tm->tm_wday+1&&pump3_day_sat))
    &&(p_tm->tm_hour==pump3_start_h) && (p_tm->tm_min==pump3_start_m))
    {
      pump3 = 1;
    }
    else if(((p_tm->tm_wday+1&&pump3_day_sun)||(p_tm->tm_wday+1&&pump3_day_mon)||(p_tm->tm_wday+1&&pump3_day_tue)||(p_tm->tm_wday+1&&pump3_day_wed)||(p_tm->tm_wday+1&&pump3_day_thu)||(p_tm->tm_wday+1&&pump3_day_fri)||(p_tm->tm_wday+1&&pump3_day_sat))
    &&(p_tm->tm_hour==pump3_end_h) && (p_tm->tm_min==pump3_end_m))
    {
      pump3 = 0;
    }
  
  // Auto Pump 3 -----------------------------------------------------------------------

  // Auto Pump 4  -----------------------------------------------------------------------

    if(((p_tm->tm_wday+1&&pump4_day_sun)||(p_tm->tm_wday+1&&pump4_day_mon)||(p_tm->tm_wday+1&&pump4_day_tue)||(p_tm->tm_wday+1&&pump4_day_wed)||(p_tm->tm_wday+1&&pump4_day_thu)||(p_tm->tm_wday+1&&pump4_day_fri)||(p_tm->tm_wday+1&&pump4_day_sat))
    &&(p_tm->tm_hour==pump4_start_h) && (p_tm->tm_min==pump4_start_m))
    {
      pump4 = 1;
    }
    else if(((p_tm->tm_wday+1&&pump4_day_sun)||(p_tm->tm_wday+1&&pump4_day_mon)||(p_tm->tm_wday+1&&pump4_day_tue)||(p_tm->tm_wday+1&&pump4_day_wed)||(p_tm->tm_wday+1&&pump4_day_thu)||(p_tm->tm_wday+1&&pump4_day_fri)||(p_tm->tm_wday+1&&pump4_day_sat))
    &&(p_tm->tm_hour==pump4_end_h) && (p_tm->tm_min==pump4_end_m))
    {
      pump4 = 0;
    }
  
  // Auto Pump 4 -----------------------------------------------------------------------
  
  // Manual Control ------------------------------------------------------------------------

  digitalWrite(Relay_light1,light1);
  digitalWrite(Relay_light2,light2);
  digitalWrite(Relay_light3,light3);
  digitalWrite(Relay_light4,light4);

  digitalWrite(Relay_pump1,pump1);
  digitalWrite(Relay_pump2,pump2);
  digitalWrite(Relay_pump3,pump3);
  digitalWrite(Relay_pump4,pump4);
  
  // Manual Control ------------------------------------------------------------------------
  
  Soilval = 1024-analogRead(potpin);
  //Serial.print("val = ");
  //Serial.println(Soilval);
  Soilval = map(Soilval, 0, 600, 0, 800);
  
  // Output Data To App------------------------------------------------------------------------
  
  Firebase.setInt(firebaseData, "Soil_Moisture/Volume", Soilval);

  // Output Data To App------------------------------------------------------------------------

  
  // Input Data From App-----------------------------------------------------------------------


if(Firebase.getInt(firebaseData, "Status/Updatestatus")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        updatestatus = firebaseData.intData();
    }
  }
  if(updatestatus == 1 ){

   if(Firebase.getInt(firebaseData, "Status/Light_1")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light1 = firebaseData.intData();
    }
  }
     if(Firebase.getInt(firebaseData, "Status/Light_2")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light2 = firebaseData.intData();
    }
  }
    if(Firebase.getInt(firebaseData, "Status/Light_3")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light3 = firebaseData.intData();
    }
  }
     if(Firebase.getInt(firebaseData, "Status/Light_4")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light4 = firebaseData.intData();
    }
  }
    if(Firebase.getInt(firebaseData, "Status/Pump_1")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump1 = firebaseData.intData();
    }
  }
     if(Firebase.getInt(firebaseData, "Status/Pump_2")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump2 = firebaseData.intData();
    }
  }
    if(Firebase.getInt(firebaseData, "Status/Pump_3")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump3 = firebaseData.intData();
    }
  }
     if(Firebase.getInt(firebaseData, "Status/Pump_4")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump4 = firebaseData.intData();
    }
  }

  updatestatus = 0;
  Firebase.setInt(firebaseData, "Status/Updatestatus", updatestatus);
  
 }

 
  // Input Data From App-----------------------------------------------------------------------

  // Time Update-----------------------------------------------------------------------
  
  if(Firebase.getInt(firebaseData, "Status/Timeupdate")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        timeupdate = firebaseData.intData();
    }
  }
  if(timeupdate == 1 ){

  // Time Update 1 -----------------------------------------------------------------------

  if(Firebase.getInt(firebaseData, "SetTime_Light_1/Day/Sun")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light1_day_sun = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_1/Day/Mon")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light1_day_mon = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_1/Day/Tue")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light1_day_tue = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_1/Day/Wed")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light1_day_wed = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_1/Day/Thu")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light1_day_thu = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_1/Day/Fri")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light1_day_fri = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_1/Day/Sat")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light1_day_sat = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_1/Start_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light1_start_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_1/Start_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light1_start_m = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_1/End_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light1_end_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_1/End_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light1_end_m = firebaseData.intData();
    }
  }

  // Time Update 1 -----------------------------------------------------------------------


  // Time Update 2 -----------------------------------------------------------------------

  if(Firebase.getInt(firebaseData, "SetTime_Light_2/Day/Sun")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light2_day_sun = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_2/Day/Mon")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light2_day_mon = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_2/Day/Tue")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light2_day_tue = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_2/Day/Wed")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light2_day_wed = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_2/Day/Thu")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light2_day_thu = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_2/Day/Fri")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light2_day_fri = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_2/Day/Sat")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light2_day_sat = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_2/Start_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light2_start_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_2/Start_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light2_start_m = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_2/End_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light2_end_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_2/End_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light2_end_m = firebaseData.intData();
    }
  }

  // Time Update 2 -----------------------------------------------------------------------


  // Time Update 3 -----------------------------------------------------------------------

  if(Firebase.getInt(firebaseData, "SetTime_Light_3/Day/Sun")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light3_day_sun = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_3/Day/Mon")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light3_day_mon = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_3/Day/Tue")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light3_day_tue = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_3/Day/Wed")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light3_day_wed = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_3/Day/Thu")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light3_day_thu = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_3/Day/Fri")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light3_day_fri = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_3/Day/Sat")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light3_day_sat = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_3/Start_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light3_start_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_3/Start_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light3_start_m = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_3/End_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light3_end_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_3/End_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light3_end_m = firebaseData.intData();
    }
  }

  // Time Update 3 -----------------------------------------------------------------------


  // Time Update 4 -----------------------------------------------------------------------

  if(Firebase.getInt(firebaseData, "SetTime_Light_4/Day/Sun")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light4_day_sun = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_4/Day/Mon")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light4_day_mon = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_4/Day/Tue")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light4_day_tue = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_4/Day/Wed")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light4_day_wed = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_4/Day/Thu")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light4_day_thu = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_4/Day/Fri")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light4_day_fri = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_4/Day/Sat")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light4_day_sat = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_4/Start_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light4_start_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_4/Start_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light4_start_m = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_4/End_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light4_end_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Light_4/End_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        light4_end_m = firebaseData.intData();
    }
  }

  // Time Update 4 -----------------------------------------------------------------------


  // Time Update 5 -----------------------------------------------------------------------

  if(Firebase.getInt(firebaseData, "SetTime_Pump_1/Day/Sun")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump1_day_sun = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_1/Day/Mon")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump1_day_mon = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_1/Day/Tue")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump1_day_tue = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_1/Day/Wed")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump1_day_wed = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_1/Day/Thu")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump1_day_thu = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_1/Day/Fri")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump1_day_fri = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_1/Day/Sat")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump1_day_sat = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_1/Start_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump1_start_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_1/Start_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump1_start_m = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_1/End_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump1_end_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_1/End_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump1_end_m = firebaseData.intData();
    }
  }

  // Time Update 5 -----------------------------------------------------------------------


  // Time Update 6 -----------------------------------------------------------------------

  if(Firebase.getInt(firebaseData, "SetTime_Pump_2/Day/Sun")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump2_day_sun = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_2/Day/Mon")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump2_day_mon = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_2/Day/Tue")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump2_day_tue = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_2/Day/Wed")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump2_day_wed = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_2/Day/Thu")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump2_day_thu = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_2/Day/Fri")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump2_day_fri = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_2/Day/Sat")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump2_day_sat = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_2/Start_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump2_start_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_2/Start_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump2_start_m = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_2/End_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump2_end_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_2/End_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump2_end_m = firebaseData.intData();
    }
  }

  // Time Update 6 -----------------------------------------------------------------------


  // Time Update 7 -----------------------------------------------------------------------

  if(Firebase.getInt(firebaseData, "SetTime_Pump_3/Day/Sun")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump3_day_sun = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_3/Day/Mon")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump3_day_mon = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_3/Day/Tue")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump3_day_tue = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_3/Day/Wed")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump3_day_wed = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_3/Day/Thu")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump3_day_thu = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_3/Day/Fri")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump3_day_fri = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_3/Day/Sat")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump3_day_sat = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_3/Start_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump3_start_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_3/Start_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump3_start_m = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_3/End_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump3_end_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_3/End_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump3_end_m = firebaseData.intData();
    }
  }

  // Time Update 7 -----------------------------------------------------------------------


  // Time Update 8 -----------------------------------------------------------------------

  if(Firebase.getInt(firebaseData, "SetTime_Pump_4/Day/Sun")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump4_day_sun = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_4/Day/Mon")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump4_day_mon = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_4/Day/Tue")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump4_day_tue = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_4/Day/Wed")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump4_day_wed = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_4/Day/Thu")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump4_day_thu = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_4/Day/Fri")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump4_day_fri = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_4/Day/Sat")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump4_day_sat = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_4/Start_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump4_start_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_4/Start_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump4_start_m = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_4/End_H")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump4_end_h = firebaseData.intData();
    }
  }
  if(Firebase.getInt(firebaseData, "SetTime_Pump_4/End_M")) 
  {
    if(firebaseData.dataType() == "int") 
    {
        pump4_end_m = firebaseData.intData();
    }
  }

  // Time Update 8 -----------------------------------------------------------------------
  
  delay(1000);
  timeupdate = 0;
  Firebase.setInt(firebaseData, "Status/Timeupdate", timeupdate);
  }
  

  // Time Update-----------------------------------------------------------------------


  
  delay(1);

    // Do something
}

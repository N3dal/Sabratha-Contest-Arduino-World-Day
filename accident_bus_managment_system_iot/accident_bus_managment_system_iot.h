#ifndef SMART_HOME_ESP32_H
#define SMART_HOME_ESP32_H

#include "defaults.h"


String create_html(void);
void connect_to_wifi(void);
void setup_lcd(void);
void lcd_logo(void);
void lcd_connect_to_network(void);
void lcd_information_print(int);
void setup_routing(void);
void handle_root(void);
void handle_led_1(void);
void handle_led_2(void);
void handle_led_3(void);
void handle_test_email(void);
void handle_changing_servers_ip_address(void);
void handle_set_ip(void);
void write_ip_to_eeprom(const IPAddress& ip_address, int);
IPAddress read_ip_from_eeprom(int);

void debug(void);


// Set web server port number to 80;
WebServer web_server(PORT);

LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t tilt_sensor_state = 1;
uint8_t seat_belt_sensor_state = 1;
uint8_t collision_sensor_state = 0;
uint8_t bus_engine_state = 0;
float motor_speed = 0.0;



void setup_lcd(void){
  lcd.begin();
  lcd.backlight();
  lcd.clear();


}

void lcd_logo(void){
    for (uint8_t index=0; index<TEAM_NAME.length() ; index++){
    lcd.setCursor(index+2, 0);
    lcd.print(TEAM_NAME[index]);
    delay(300);

  }
  lcd.clear();
}

void lcd_connect_to_network(void){
    lcd.setCursor(0, 0);
    lcd.print("Connect To");
    lcd.setCursor(0, 1);
    lcd.print("Network");
    delay(200);

}

void lcd_information_print(int speed){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Motor Speed Lvl:");
  lcd.setCursor(7, 1);
  lcd.print(String(speed) + "%");
}


String create_html()
{
    String ptr = "";
    ptr += "<html !DOCTYPE>";
    ptr += "<head>";
    ptr += "<!--minimum width => 575;-->";
    ptr += "<meta name=\"viewport\" content=\"width=device-width, user-scalable=no, initial-scale=1.0\">";
    ptr += "<meta http-equiv=\"refresh\" content=\"5\" charset=\"UTF-8\">";
    ptr += "<title>Smart Home Automation</title>";
    ptr += "<style>";
    ptr += "body {font-family: monospace;background-color: rgb(220, 220, 220);}";
    ptr += "h1 {color: rgb(0, 0, 0);text-align: center;margin: 20px;font-size: 18px;}";
    ptr += "";
    ptr += ".container{background-color: rgb(220, 220, 220);border: 0px solid black;width: 600px;justify-content: center;margin: 0px auto;align-items: center;display: flex;height: auto;flex-wrap: wrap;}";
    ptr += ".dashboard-title{background-color: rgb(220, 220, 220);height: 5%;display: inline;}";
    ptr += ".measurement_widget{background-color: rgb(91, 109, 205); width: 160px;height: 250px; border: 2px solid black; padding: 5px;margin: 10px;text-align: center;justify-content: center;align-items: center;border-radius: 50% 20% / 10%;}";
    ptr += ".widget_title{background-color: rgb(91, 109, 205); font-size: 15px;margin: 10px;color:white;}";
    ptr += ".widget_value{background-color: rgb(91, 109, 205); font-size: 32px;margin: 10px;margin: 0px;position: relative;top:40%;transform: translateY(-50%);color:white;}";
    ptr += ".control_button{        box-shadow:inset 0px 1px 0px 0px #fce2c1;";
    ptr += "background:linear-gradient(to bottom, #1c8dd8 5%, #076eb3 100%);";
    ptr += "background-color:#1c8dd8;";
    ptr += "border-radius:11px;";
    ptr += "width: 150px;";
    ptr += "height: 60px;";
    ptr += "border:0px solid #1c8dd8;";
    ptr += "display:inline-block;";
    ptr += "cursor:pointer;";
    ptr += "color:#ffffff;";
    ptr += "font-family:monospace;";
    ptr += "font-size:16px;";
    ptr += "font-weight:bold;";
    ptr += "padding:8px 18px;";
    ptr += "text-decoration:none;";
    ptr += "text-shadow:0px 1px 0px #1c8dd8;";
    ptr += "margin: 5px;";
    ptr += "}";
    ptr += ".control_button:hover{  background:linear-gradient(to bottom, #076eb3 5%, #1c8dd8 100%);";
    ptr += "background-color:#1c8dd8;}";
    ptr += ".control_button:active{ position:relative;";
    ptr += "top:1px;}";
    ptr += "._row{display:flex; flex-basis: 100%; align-items: center;justify-content: center;}";
    ptr += "";
    ptr += ".b_row{display:flex; flex-basis: 100%; align-items: center;justify-content: center;text-align: center;}";
    ptr += "";
    ptr += ".button_container{background-color: rgb(220, 220, 220); border: 0px solid black;width: 600px;justify-content: center;margin: 0px auto;align-items: center;display: flex;height: auto;flex-wrap: wrap;}";
    ptr += "";
    ptr += "";
    ptr += "</style>";
    ptr += "";
    ptr += "</head>";
    ptr += "<body>";
    ptr += "<!-- The Title -->";
    ptr += "<!-- <h1 style=\"color:rgb(0, 0, 0);\"> Smart Home Automation </h1> -->";
    ptr += "";
    ptr += "";
    ptr += "<div class=\"container\">";
    ptr += "";
    ptr += "<div class=\"_row\">";
    ptr += "";
    ptr += "<div class=\"measurement_widget\">";
    ptr += "<h1 class=\"widget_title\">Temperature</h1>";
    ptr += "<p class=\"widget_value\">";
    // ptr +=  String(temperature_value) + "°C";
    ptr += "</p>";
    ptr += "";
    ptr += "";
    ptr += "</div>";
    ptr += "";
    ptr += "";
    ptr += "<div class=\"measurement_widget\">";
    ptr += "<h1 class=\"widget_title\">Humidity</h1>";
    ptr += "<p class=\"widget_value\">";
    // ptr +=  String(humidity_value) + "%";
    ptr += "</p>";
    ptr += "</div>";
    ptr += "</div>";
    ptr += "";
    ptr += "<div class=\"_row\">";
    ptr += "";
    ptr += "<div class=\"measurement_widget\">";
    ptr += "<h1 class=\"widget_title\">Flame Status</h1>";
    ptr += "<p class=\"widget_value\">";
    // ptr += (flame_state) ? "Detected": "False"; 
    ptr += "</p>";
    ptr += "</div>";
    ptr += "";
    ptr += "";
    ptr += "<div class=\"measurement_widget\">";
    ptr += "<h1 class=\"widget_title\">Smoke Status</h1>";
    ptr += "<p class=\"widget_value\">";
    // ptr += (smoke_state) ? "Detected": "False";
    ptr += "</p>";
    ptr += "</div>";
    ptr += "</div>";
    ptr += "";
    ptr += "<div class=\"_row\">";
    ptr += "";
    ptr += "<div class=\"measurement_widget\">";
    ptr += "<h1 class=\"widget_title\">Gate Status</h1>";
    ptr += "<p class=\"widget_value\">";
    // ptr += (gate_state) ? "Opened": "Closed";
    ptr += "</p>";
    ptr += "</div>";
    ptr += "";
    ptr += "";
    ptr += "<div class=\"measurement_widget\">";
    ptr += "<h1 class=\"widget_title\">Light Status</h1>";
    ptr += "<p class=\"widget_value\">";
    // ptr += (led_state_1) ? "Off": "On"; 
    ptr += "</p>";
    ptr += "</div>";
    ptr += "</div>";
    ptr += "";
    ptr += "<div class=\"_row\">";
    ptr += "";
    ptr += "<div class=\"measurement_widget\">";
    ptr += "<h1 class=\"widget_title\">Detect Status</h1>";
    ptr += "<p class=\"widget_value\">";
    // ptr += (obj_detection_state) ? "Detected": "False"; 
    ptr += "</p>";
    ptr += "</div>";
    ptr += "</div>";
    ptr += "";
    ptr += "";
    ptr += "";
    ptr += "</div>";
    ptr += "";
    ptr += "<div class=\"button_container\">";
    ptr += "<div class=\"b_row\">";
    ptr += "<a href=\"/led1\"><button class=\"control_button\">Light 1</button></a>";
    ptr += "<a href=\"/led2\"><button class=\"control_button\">Light 2</button></a>";
    ptr += "";
    ptr += "</div>";
    ptr += "";
    ptr += "<div class=\"b_row\">";
    ptr += "<a href=\"/led3\"><button class=\"control_button\">Light 3</button></a>";
    ptr += "<a href=\"/test_email\"><button class=\"control_button\">Test Email</button></a>";
    ptr += "";
    ptr += "</div>";
    ptr += "</div>";
    ptr += "";
    ptr += "";
    ptr += "";
    ptr += "</body>";
    ptr += "</html>";

    return ptr;
}

void handle_changing_servers_ip_address(void){

  String ptr= "";
  ptr += "<!DOCTYPE HTML><html><head>";
  ptr += "<title>Settings</title>";
  ptr += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  ptr += "</head><body>";
  ptr += "<form action=\"/set_servers_ip\">";
  ptr += "Bus-Server-IP: <input type=\"text\" name=\"bus-ip-input\" value=\"";
  ptr += bus_server_ip_address.toString();
  ptr += "\">";
  ptr += "<br>";
  ptr += "<br>";
  ptr += "Police-Server-IP: <input type=\"text\" name=\"police-ip-input\" value=\"";
  ptr += police_server_ip_address.toString();
  ptr += "\">";
  ptr += "<br>";
  ptr += "<br>";
  ptr += "<input type=\"submit\" value=\"Save\">";
  ptr += "</form><br>";
  ptr += "</body></html>";

  web_server.send(200, "text/html", ptr);
}

void connect_to_wifi()
{
  // Connect to Wi-Fi network with SSID and PASSWORD
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  LOCAL_IP_ADDRESS = WiFi.localIP().toString();
  Serial.println(LOCAL_IP_ADDRESS);
}

void setup_routing(void)
{
  /*
    setup the route for the server;
  */


  web_server.on(F("/"), HTTP_GET, handle_root);
  web_server.on(F("/change_servers_ip"), HTTP_GET, handle_changing_servers_ip_address);
  web_server.on(F("/set_servers_ip"), HTTP_GET, handle_set_ip);
  web_server.begin();
}


void redirect_to_main_page(void){
  String redirect_tag = "<html><head><script>window.location.href = \'";
  redirect_tag +="http://";
  redirect_tag +=LOCAL_IP_ADDRESS;
  redirect_tag += "\';</script></head></html>";

  web_server.send(200, "text/html", redirect_tag);

}

void handle_root(void){
  web_server.send(200, "text/html", create_html()); //

}

void handle_set_ip(void){
  if (web_server.hasArg("bus-ip-input") || web_server.hasArg("police-ip-input")){

    String bus_ip_string = web_server.arg("bus-ip-input");
    Serial.print("[+]Bus-IP: ");
    Serial.println(bus_ip_string);
    String police_ip_string = web_server.arg("police-ip-input");
    IPAddress bus_new_ip_address;

    if (bus_new_ip_address.fromString(bus_ip_string)){
      bus_server_ip_address[0] = bus_new_ip_address[0];
      bus_server_ip_address[1] = bus_new_ip_address[1];
      bus_server_ip_address[2] = bus_new_ip_address[2];
      bus_server_ip_address[3] = bus_new_ip_address[3];

      write_ip_to_eeprom(bus_server_ip_address, BUS_SERVER_IP_ADDRESS_EEPROM_ADDR);
    }

    IPAddress police_new_ip_address;
    if (police_new_ip_address.fromString(police_ip_string)){
      police_server_ip_address[0] = police_new_ip_address[0];
      police_server_ip_address[1] = police_new_ip_address[1];
      police_server_ip_address[2] = police_new_ip_address[2];
      police_server_ip_address[3] = police_new_ip_address[3];

      write_ip_to_eeprom(police_server_ip_address, POLICE_SERVER_IP_ADDRESS_EEPROM_ADDR);
    }
    web_server.send(200, "text/html", "<h1>Servers IP address Updated. </h1>");

  }
  
}

void write_ip_to_eeprom(const IPAddress& ip_address, int address){

  EEPROM.begin(EEPROM_SIZE);
  byte* address_bytes = (byte*)&ip_address;
  for (int i=0; i<sizeof(ip_address); i++){
    EEPROM.write(address + i, address_bytes[i]);
  }

  EEPROM.commit();
  EEPROM.end();

}

IPAddress read_ip_from_eeprom(int address) {

  EEPROM.begin(EEPROM_SIZE);
  IPAddress ip_address;
  byte* address_bytes = (byte*)&ip_address;
  for (int i = 0; i < sizeof(ip_address); i++) {
    address_bytes[i] = EEPROM.read(address + i);
  }
  EEPROM.end();
  return ip_address;
}



void debug(void){

}

#endif
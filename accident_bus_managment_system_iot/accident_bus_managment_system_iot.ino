#include "accident_bus_managment_system_iot.h"



void setup(void){
  Serial.begin(115200);

  setup_lcd();
  lcd_logo();

  lcd_connect_to_network();
  connect_to_wifi();


  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(PWM_PIN, PWM_CHANNEL);

  pinMode(TILT_SENSOR_PIN, INPUT_PULLDOWN);
  pinMode(COLLISION_SENSOR_PIN, INPUT_PULLDOWN);
  pinMode(SEAT_BELT_SENSOR_PIN, INPUT_PULLDOWN);
  pinMode(BUS_ENGINE_STATE_SENSOR_PIN, INPUT_PULLDOWN);

  bus_server_ip_address = read_ip_from_eeprom(BUS_SERVER_IP_ADDRESS_EEPROM_ADDR);
  police_server_ip_address = read_ip_from_eeprom(POLICE_SERVER_IP_ADDRESS_EEPROM_ADDR);

  setup_routing();

}

void loop(void){

  web_server.handleClient();
  
  // create json object;
  StaticJsonBuffer<255> json_buffer;

  JsonObject& json_handler = json_buffer.createObject();



 
  bus_engine_state = digitalRead(BUS_ENGINE_STATE_SENSOR_PIN);
  collision_sensor_state = digitalRead(COLLISION_SENSOR_PIN);
  tilt_sensor_state = digitalRead(TILT_SENSOR_PIN);
  seat_belt_sensor_state = digitalRead(SEAT_BELT_SENSOR_PIN);

  if (bus_engine_state){
    long adc_read = analogRead(ADC_PIN);
    motor_speed = map(adc_read, 0, 4095, 0, 255);
    motor_speed = motor_speed / 255 * 100;
  }else{
    motor_speed = 0.0;
  }

  // Serial.print(tilt_sensor_state);
  // Serial.print(" | ");
  // Serial.print(seat_belt_sensor_state);
  // Serial.print(" | ");
  // Serial.print(collision_sensor_state);
  // Serial.print(" | ");
  // Serial.println(bus_engine_state);



  lcd_information_print(motor_speed);

  ledcWrite(PWM_CHANNEL, motor_speed);


  json_handler["bus-id"] = BUS_ID;
  json_handler["driver-id"] = DRIVER_ID;
  json_handler["driver-name"] = DRIVER_NAME;

  json_handler["engine-state"] = bus_engine_state;
  json_handler["collision-state"] = collision_sensor_state;
  json_handler["tilt-state"] = tilt_sensor_state;
  json_handler["motor-speed-level"] = motor_speed;
  json_handler["seat-belt-state"] = seat_belt_sensor_state;
  json_handler["system-state"] = 1;







  char json_msg_buffer[255];
  json_handler.prettyPrintTo(json_msg_buffer, sizeof(json_msg_buffer));

  // check from the wifi connection;
  WiFiClient client;
  
  HTTPClient bus_http_client;
  bus_http_client.begin(client, String("http://") + bus_server_ip_address.toString() + String(":8080") + "/send_data");
  bus_http_client.addHeader("Content-Type", "application/json");


  // int http_code = http.GET();
  int bus_client_http_code = bus_http_client.POST(json_msg_buffer);

  if (bus_client_http_code != 200){
  }else{
  }

  bus_http_client.end();

  if (collision_sensor_state == 1 ||  tilt_sensor_state == 1 ||  seat_belt_sensor_state == 0 ||  motor_speed >=75){

    if (collision_sensor_state == 1){
      current_event = COLLISION_ACCIDENT;
    }
    else if (tilt_sensor_state == 1){
      current_event = FLIP_ACCIDENT;
    }
    else if ( seat_belt_sensor_state == 0){
      current_event = SEAT_BELT_VIOLATION;
    }
    else{
      current_event = OVER_SPEED_LIMIT_VIOLATION;
    }

    if (current_event != last_event){
      
      HTTPClient police_http_client;
      police_http_client.begin(client, String("http://") + police_server_ip_address.toString() + String(":8080") + "/send_data");
      police_http_client.addHeader("Content-Type", "application/json");


      int police_client_http_code = police_http_client.POST(json_msg_buffer);

      if (police_client_http_code != 200){
      }else{
      }

      police_http_client.end();

      last_event = current_event;
    }

  }





  delay(150);

}



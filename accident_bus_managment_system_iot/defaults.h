#ifndef _DEFAUTLS_H
#define _DEFAUTLS_H
#include <IPAddress.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <ESPAsyncWebServer.h>
// suhail.altyif@outlook.com
// password: tqcxiqm1122

#define BUS_NUMBER 1
#define BUS_ID "BUS-0001"
#define DRIVER_ID "D-0001A"
#define DRIVER_NAME "Emad Aymen"


#define EEPROM_SIZE sizeof(IPAddress) * 2 // ip size is = 8

// the address where we will store the ip address;
#define BUS_SERVER_IP_ADDRESS_EEPROM_ADDR 0
#define POLICE_SERVER_IP_ADDRESS_EEPROM_ADDR 8



// the address where we will store the ip address;
#define IP_ADDRESS_EEPROM_ADDR 0

#define PWM_CHANNEL 2
#define PWM_PIN 2

#define PWM_FREQUENCY 540
#define PWM_RESOLUTION 8

#define MIN_SPEED 150
#define MAX_SPEED 255

#define TILT_SENSOR_PIN 25
#define COLLISION_SENSOR_PIN 26
#define SEAT_BELT_SENSOR_PIN 27
#define BUS_ENGINE_STATE_SENSOR_PIN 33


#define CW_DIRECTION 0
#define CCW_DIRECTION 1

#define ADC_PIN 34

#define PORT 80
#define TIMEOUT 50

#include <DHT.h>
#include <ESP32_Servo.h>
#include "email_handler.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

String TEAM_NAME = "VolTech Group";


// Replace with your network credentials;
// char *WIFI_SSID = "netis";
char *WIFI_SSID = "network";
char *WIFI_PASSWORD = "password";

String LOCAL_IP_ADDRESS = "";

IPAddress bus_server_ip_address(192, 168, 0, 111);
IPAddress police_server_ip_address(192, 168, 0, 112);



#endif
#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

// network configuration and credentials
const char* wifi_ssid = "";
const char* wifi_password = "";

// target mac address for magic packet (wake-on-lan)
uint8_t target_mac[6] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };

// ssh configuration (to be implemented later)
const char* ssh_server_ip = "192.168.1.100";
const char* ssh_password = "SSH_PASSWORD";

// pin configuration
const int button_pin = 0;   // adjust according to your board
const int led_pin    = LED_BUILTIN;

// button state tracking
unsigned long button_press_time = 0;
bool button_is_pressed = false;

// udp object for sending magic packet
WiFiUDP udp;

void send_magic_packet() {
    const int packet_size = 6 + 16 * 6;
    uint8_t packet[packet_size];

    memset(packet, 0xFF, 6);
    for (int i = 0; i < 16; i++) {
        memcpy(packet + 6 + i * 6, target_mac, 6);
    }

    udp.beginPacket("255.255.255.255", 9);
    udp.write(packet, packet_size);
    udp.endPacket();

    Serial.println("magic packet sent.");
}

void shutdown_remote() {
    Serial.println("ssh functionality for shutdown (to be implemented). ");
}

void setup() {
    Serial.begin(115200);
    pinMode(button_pin, INPUT_PULLUP);
    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, LOW);

    Serial.print("connecting to wifi ");
    Serial.print(wifi_ssid);
    WiFi.begin(wifi_ssid, wifi_password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nwifi connected.");
    Serial.print("ip address: ");
    Serial.println(WiFi.localIP());

    udp.begin(2390);
}

void loop() {
    int button_state = digitalRead(button_pin);
    
    if (button_state == LOW) { 
        if (!button_is_pressed) {
            button_is_pressed = true;
            button_press_time = millis();
        }
        else {
            unsigned long elapsed = millis() - button_press_time;
            
            if (elapsed >= 2000 && elapsed < 5000) {
                if ((millis() / 200) % 2 == 0) {
                    digitalWrite(led_pin, HIGH);
                } else {
                    digitalWrite(led_pin, LOW);
                }
            }
            else if (elapsed >= 5000) {
                digitalWrite(led_pin, HIGH);
            }
        }
    }
    else { 
        if (button_is_pressed) {
            unsigned long elapsed = millis() - button_press_time;
            
            if (elapsed >= 2000 && elapsed < 5000) {
                Serial.println("button released between 2 and 5 seconds.");
                send_magic_packet();
            }
            else if (elapsed >= 5000) {
                Serial.println("button released after 5 seconds.");
                shutdown_remote();
            }
            
            button_is_pressed = false;
            digitalWrite(led_pin, LOW);
        }
    }
}

#ifndef WebSerial_h
#define WebSerial_h

#include "Arduino.h"
#include <functional>

#define BUFFER_SIZE 500

#if defined(ESP8266)
#define HARDWARE "ESP8266"
#include "ESPAsyncWebServer.h"
#elif defined(ESP32)
#define HARDWARE "ESP32"
#include "ESPAsyncWebServer.h"
#endif

typedef std::function<void(uint8_t *data, size_t len)> RecvMsgHandler;

class WebSerialClass
{

public:
    void begin(AsyncWebServer *server, const char *url = "/webserial");
    void msgCallback(RecvMsgHandler _recv);

    // Print
    void print(String m = "");
    void print(const char *m);
    void print(char *m);
    void print(int m);
    void print(uint8_t m);
    void print(uint16_t m);
    void print(uint32_t m);
    void print(double m);
    void print(float m);

    // Print with New Line
    void println(String m = "");
    void println(const char *m);
    void println(char *m);
    void println(int m);
    void println(uint8_t m);
    void println(uint16_t m);
    void println(uint32_t m);
    void println(float m);
    void println(double m);

private:
    AsyncWebServer *_server;
    AsyncWebSocket *_ws;
    RecvMsgHandler _RecvFunc = NULL;

#if defined(DEBUG)
    void DEBUG_WEB_SERIAL(const char *message);
#endif
};

extern WebSerialClass WebSerial;
#endif
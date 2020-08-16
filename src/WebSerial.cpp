#include "WebSerial.h"

#include "Arduino.h"
#include "stdlib_noniso.h"
#include <functional>

#if defined(ESP8266)
#define HARDWARE "ESP8266"
#include "ESP8266WiFi.h"
#include "ESPAsyncTCP.h"
#include "ESPAsyncWebServer.h"
#elif defined(ESP32)
#define HARDWARE "ESP32"
#include "WiFi.h"
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"
#endif

#include "webserial_webpage.h"

void WebSerialClass::begin(AsyncWebServer *server, const char *url)
{
  _server = server;
  _ws = new AsyncWebSocket("/webserialws");

  _server->on(url, HTTP_GET, [](AsyncWebServerRequest *request) {
    // Send Webpage
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", WEBSERIAL_HTML, WEBSERIAL_HTML_SIZE);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  _ws->onEvent([&](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) -> void {
    if (type == WS_EVT_CONNECT)
    {
#if defined(DEBUG)
      DEBUG_WEB_SERIAL("Client connection received");
#endif
    }
    else if (type == WS_EVT_DISCONNECT)
    {
#if defined(DEBUG)
      DEBUG_WEB_SERIAL("Client disconnected");
#endif
    }
    else if (type == WS_EVT_DATA)
    {
#if defined(DEBUG)
      DEBUG_WEB_SERIAL("Received Websocket Data");
#endif
      if (_RecvFunc != NULL)
      {
        _RecvFunc(data, len);
      }
    }
  });

  _server->addHandler(_ws);

#if defined(DEBUG)
  DEBUG_WEB_SERIAL("Attached AsyncWebServer along with Websockets");
#endif
}

void WebSerialClass::msgCallback(RecvMsgHandler _recv)
{
  _RecvFunc = _recv;
}

// Print

void WebSerialClass::print(String m)
{
  if (_ws != NULL)
  {
    _ws->textAll(m);
  }
}

void WebSerialClass::print(const char *m)
{
  if (_ws != NULL)
  {
    _ws->textAll(m);
  }
}

void WebSerialClass::print(char *m)
{
  if (_ws != NULL)
  {
    _ws->textAll(m);
  }
}

void WebSerialClass::print(int m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m));
  }
}

void WebSerialClass::print(uint8_t m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m));
  }
}

void WebSerialClass::print(uint16_t m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m));
  }
}

void WebSerialClass::print(uint32_t m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m));
  }
}

void WebSerialClass::print(double m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m));
  }
}

void WebSerialClass::print(float m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m));
  }
}

// Print with New Line

void WebSerialClass::println(String m)
{
  if (_ws != NULL)
  {
    _ws->textAll(m + "\n");
  }
}

void WebSerialClass::println(const char *m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m) + "\n");
  }
}

void WebSerialClass::println(char *m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m) + "\n");
  }
}

void WebSerialClass::println(int m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m) + "\n");
  }
}

void WebSerialClass::println(uint8_t m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m) + "\n");
  }
}

void WebSerialClass::println(uint16_t m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m) + "\n");
  }
}

void WebSerialClass::println(uint32_t m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m) + "\n");
  }
}

void WebSerialClass::println(float m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m) + "\n");
  }
}

void WebSerialClass::println(double m)
{
  if (_ws != NULL)
  {
    _ws->textAll(String(m) + "\n");
  }
}

#if defined(DEBUG)
void WebSerialClass::DEBUG_WEB_SERIAL(const char *message)
{
  Serial.println("[WebSerial] " + message);
}
#endif

WebSerialClass WebSerial;
#include <Arduino.h>
#include <ArduinoJson.h>
#include <FS.h>

#if defined(ESP32)
#include <SPIFFS.h>
#endif

class FileSystem
{
private:
  DynamicJsonDocument getRelayJSON();

public:
  FileSystem();

  String getBoard();
  void setBoard(String board);

  boolean getRelayValue(String relay);
  void setRelayValue(String relay, boolean value);
};

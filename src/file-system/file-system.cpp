#include "file-system.h"

FileSystem::FileSystem() { }

String FileSystem::getBoard() {
  File file = SPIFFS.open("/board.txt", "r");
  String board = file.readStringUntil('\r');

  Serial.println("read board on file: " + board);

  file.close();

  return board;
}

void FileSystem::setBoard(String board) {
  SPIFFS.format();

  File file = SPIFFS.open("/board.txt", "w+");

  if(file){
    file.println(board);
    Serial.println("write board id on file: " + board);
  }

  file.close();
}

bool FileSystem::getRelayValue(String relay) {
  DynamicJsonDocument doc = this->getRelayJSON();

  bool value = doc[relay];
  Serial.println("read relay " + relay + " value from file: " + value);

  return value;
}

void FileSystem::setRelayValue(String relay, bool value) {
  DynamicJsonDocument doc = this->getRelayJSON();

  File file = SPIFFS.open("/relays.json", "w+");

  if(file) {
    doc[relay] = value;

    String output;
    serializeJson(doc, output);

    file.println(output);

    Serial.println("write relays values on file: " + output);
  }

  file.close();
}

DynamicJsonDocument FileSystem::getRelayJSON() {
  File file = SPIFFS.open("/relays.json", "r");

  String content = file.readStringUntil('\r');
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, content);

  Serial.println("read relays values from file: " + content);

  file.close();

  return doc;
}

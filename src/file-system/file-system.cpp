#include "file-system.h"

FileSystem::FileSystem() { }

String FileSystem::getBoard() {
  File file = SPIFFS.open("/board.txt", "r");
  String board = file.readStringUntil('\r');

  file.close();

  return board;
}

void FileSystem::setBoard(String board) {
  Serial.println("Formatting SPIFFS");
  SPIFFS.format();

  File file = SPIFFS.open("/board.txt", "w+");

  if(file){
    file.println(board);
  }

  file.close();
}

boolean FileSystem::getRelayValue(String relay) {
  DynamicJsonDocument doc = this->getRelayJSON();

  boolean value = doc[relay];

  return value;
}

void FileSystem::setRelayValue(String relay, boolean value) {
  DynamicJsonDocument doc = this->getRelayJSON();

  File file = SPIFFS.open("/relays.json", "w+");

  if(file) {
    doc[relay] = value;

    String output;
    serializeJson(doc, output);

    file.println(output);
  }

  file.close();
}

DynamicJsonDocument FileSystem::getRelayJSON() {
  File file = SPIFFS.open("/relays.json", "r");

  String content = file.readStringUntil('\r');
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, content);

  file.close();

  return doc;
}

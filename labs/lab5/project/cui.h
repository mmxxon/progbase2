#pragma once
#include "storage.h"

using namespace std;

class Cui {
  FileStorage* const storage_;
  void PhotosMainMenu();
  void PhotoMenu(int photo_id);
  void photoUpdateMenu(int photo_id);
  void photoDeleteMenu(int photo_id);
  void photoCreateMenu();

  void AlbumsMainMenu();
  void AlbumMenu(int album_id);
  void albumUpdateMenu(int album_id);
  void albumDeleteMenu(int album_id);
  void albumCreateMenu();

public:
  Cui(FileStorage* storage): storage_ {storage} {}
  void show();
};
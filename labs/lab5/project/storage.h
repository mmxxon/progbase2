#pragma once
#include "album.h"
#include "photo.h"

#include <fstream>
#include <iostream>
#include <optional>
#include <vector>
using namespace std;

class FileStorage {
  string dir_name_;
  fstream photos_file_;
  fstream album_file;
  vector<Photo> loadPhotos();
  void savePhotos(const vector<Photo>& photos);
  int getNewPhotoId();

  int getNewAlbumId();
  vector<Album> loadAlbum();
  void saveAlbums(const vector<Album>& album);

public:
  explicit FileStorage(const string& dir_name = "");
  void setName(const string& dir_name);
  string name();
  bool isOpen();
  bool open(bool issave = false, bool isal = false);
  void close();

  vector<Photo> getAllPhotos();
  optional<Photo> getPhotoById(int photo_id);
  bool updatePhoto(const Photo& photo);
  bool removePhoto(int photo_id);
  int insertPhoto(const Photo& photo);

  vector<Album> getAllAlbums();
  optional<Album> getAlbumById(int album_id);
  bool updateAlbum(const Album& album);
  bool removeAlbum(int album_id);
  int insertAlbum(const Album& album);
};
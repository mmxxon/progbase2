#include "storage.h"

#include "csv.h"

#include <string>
using namespace std;
static vector<Photo> createPhotoListFromTable(StringTable& csvTable) {
  vector<Photo> ls;
  for (int i = 1; i < csvTable.size_rows(); i++) {
    Photo ph;
    ph.id = atoi(csvTable.at(i, 0).c_str());
    ph.User = csvTable.at(i, 1);
    ph.likes = atoi(csvTable.at(i, 2).c_str());
    ph.comments = atoi(csvTable.at(i, 3).c_str());
    ls.push_back(ph);
  }
  return ls;
}
vector<Photo> FileStorage::loadPhotos() {
  if (!this->open()) {
    fprintf(stderr, "File can`t be open");
    exit(1);
  }
  string str2;
  string str;
  getline(photos_file_, str2);
  while (!photos_file_.eof()) {
    str.append(str2);
    str.push_back('\n');
    getline(photos_file_, str2);
  }
  str.append(str2);
  str.push_back('\n');
  this->close();
  StringTable inCsvTable = Csv_parse(str);
  vector<Photo> items = createPhotoListFromTable(inCsvTable);
  return items;
}
static StringTable createTableFromPhotoList(vector<Photo>& ls) {
  StringTable st {ls.size() + 1, 4};
  st.at(0, 0) = "id";
  st.at(0, 1) = "User";
  st.at(0, 2) = "Likes";
  st.at(0, 3) = "Comments";
  for (int i = 0; i < ls.size(); i++) {
    st.at(i + 1, 0) = to_string(ls[i].id);
    st.at(i + 1, 1) = ls[i].User;
    st.at(i + 1, 2) = to_string(ls[i].likes);
    st.at(i + 1, 3) = to_string(ls[i].comments);
  }
  return st;
}
void FileStorage::savePhotos(const vector<Photo>& photos) {
  vector<Photo> ph = photos;
  StringTable outCsvTable = createTableFromPhotoList(ph);
  string strout = Csv_toString(outCsvTable);
  if (!this->open(true)) {
    fprintf(stderr, "File can`t be open");
    exit(1);
  }
  photos_file_ << strout;
  this->close();
}
int FileStorage::getNewPhotoId() {
  fstream id(dir_name_ + "photos_id.csv");
  if (!id.is_open()) {
    fprintf(stderr, "File can`t be open");
    exit(1);
  }
  int m;
  id >> m;
  id.close();
  id.open(dir_name_ + "photos_id.csv", ios::out);
  if (m == 0) {
    vector<Photo> ph = this->loadPhotos();
    for (int i = 0; i < ph.size(); i++) {
      if (m < ph[i].id) m = ph[i].id;
    }
  }
  id << m + 1;
  id.close();
  return m + 1;
}
FileStorage::FileStorage(const string& dir_name) { dir_name_ = dir_name; }
void FileStorage::setName(const string& dir_name) { dir_name_ = dir_name; }
string FileStorage::name() { return dir_name_; }
bool FileStorage::isOpen() {
  if (photos_file_.is_open() == true && album_file.is_open() == true)
    return true;
  else
    return false;
}
bool FileStorage::open(bool issave, bool isal) {
  if (issave) {
    if (isal)
      album_file.open(this->name() + "album.csv", ios::out);
    else
      photos_file_.open(this->name() + "photos.csv", ios::out);
  } else {
    photos_file_.open(this->name() + "photos.csv");
    album_file.open(this->name() + "album.csv");
  }
  if (photos_file_.is_open() == true || album_file.is_open() == true)
    return true;
  else
    return false;
}
void FileStorage::close() {
  photos_file_.close();
  album_file.close();
}
vector<Photo> FileStorage::getAllPhotos() { return this->loadPhotos(); }
optional<Photo> FileStorage::getPhotoById(int photo_id) {
  vector<Photo> photos = this->loadPhotos();
  for (int i = 0; i < photos.size(); i++) {
    if (photos[i].id == photo_id) return photos[i];
  }
  return nullopt;
}
bool FileStorage::updatePhoto(const Photo& photo) {
  vector<Photo> photos = this->loadPhotos();
  for (int i = 0; i < photos.size(); i++) {
    if (photos[i].id == photo.id) {
      photos[i] = photo;
      this->savePhotos(photos);
      return true;
    }
  }
  return false;
}
bool FileStorage::removePhoto(int photo_id) {
  vector<Photo> photos = this->loadPhotos();
  auto it = photos.begin();
  auto it_end = photos.end();
  for (; it != it_end; it++) {
    if ((*it).id == photo_id) {
      photos.erase(it);
      this->savePhotos(photos);
      return true;
    }
  }
  return false;
}
int FileStorage::insertPhoto(const Photo& photo) {
  int newId = this->getNewPhotoId();
  Photo copy = photo;
  copy.id = newId;
  vector<Photo> photos = this->loadPhotos();
  photos.push_back(copy);
  this->savePhotos(photos);
  return newId;
}
static vector<Album> createAlbumListFromTable(StringTable& csvTable) {
  vector<Album> ls;
  for (int i = 1; i < csvTable.size_rows(); i++) {
    Album ph;
    ph.id = atoi(csvTable.at(i, 0).c_str());
    ph.name = csvTable.at(i, 1);
    ph.coverPhoto = atoi(csvTable.at(i, 2).c_str());
    ph.n_photos = atoi(csvTable.at(i, 3).c_str());
    ls.push_back(ph);
  }
  return ls;
}
vector<Album> FileStorage::loadAlbum() {
  if (!this->open()) {
    fprintf(stderr, "File can`t be open");
    exit(1);
  }
  string str2;
  string str;
  getline(album_file, str2);
  while (!album_file.eof()) {
    str.append(str2);
    str.push_back('\n');
    getline(album_file, str2);
  }
  str.append(str2);
  str.push_back('\n');
  this->close();
  StringTable inCsvTable = Csv_parse(str);
  vector<Album> items = createAlbumListFromTable(inCsvTable);
  return items;
}
static StringTable createTableFromAlbumList(vector<Album>& ls) {
  StringTable st {ls.size() + 1, 4};
  st.at(0, 0) = "id";
  st.at(0, 1) = "Name";
  st.at(0, 2) = "Photo cover";
  st.at(0, 3) = "Number of photos";
  for (int i = 0; i < ls.size(); i++) {
    st.at(i + 1, 0) = to_string(ls[i].id);
    st.at(i + 1, 1) = ls[i].name;
    st.at(i + 1, 2) = to_string(ls[i].coverPhoto);
    st.at(i + 1, 3) = to_string(ls[i].n_photos);
  }
  return st;
}
void FileStorage::saveAlbums(const vector<Album>& album) {
  vector<Album> al = album;
  StringTable outCsvTable = createTableFromAlbumList(al);
  string strout = Csv_toString(outCsvTable);
  if (!this->open(true)) {
    fprintf(stderr, "File can`t be open");
    exit(1);
  }
  album_file << strout;
  this->close();
}
int FileStorage::getNewAlbumId() {
  fstream id(dir_name_ + "album_id.csv");
  if (!id.is_open()) {
    fprintf(stderr, "File can`t be open");
    exit(1);
  }
  int m;
  id >> m;
  id.close();
  id.open(dir_name_ + "album_id.csv", ios::out);
  if (m == 0) {
    vector<Album> ph = this->loadAlbum();
    for (int i = 0; i < ph.size(); i++) {
      if (m < ph[i].id) m = ph[i].id;
    }
  }
  id << m + 1;
  id.close();
  return m + 1;
}
vector<Album> FileStorage::getAllAlbums() { return this->loadAlbum(); }
optional<Album> FileStorage::getAlbumById(int album_id) {
  vector<Album> album = this->loadAlbum();
  for (int i = 0; i < album.size(); i++) {
    if (album[i].id == album_id) return album[i];
  }
  return nullopt;
}
bool FileStorage::updateAlbum(const Album& album) {
  vector<Album> albums = this->loadAlbum();
  for (int i = 0; i < albums.size(); i++) {
    if (albums[i].id == album.id) {
      albums[i] = album;
      this->saveAlbums(albums);
      return true;
    }
  }
  return false;
}
bool FileStorage::removeAlbum(int album_id) {
  vector<Album> album = this->loadAlbum();
  auto it = album.begin();
  auto it_end = album.end();
  for (; it != it_end; it++) {
    if ((*it).id == album_id) {
      album.erase(it);
      this->saveAlbums(album);
      return true;
    }
  }
  return false;
}
int FileStorage::insertAlbum(const Album& album) {
  int newId = this->getNewAlbumId();
  Album copy = album;
  copy.id = newId;
  vector<Album> albums = this->loadAlbum();
  albums.push_back(copy);
  this->saveAlbums(albums);
  return newId;
}
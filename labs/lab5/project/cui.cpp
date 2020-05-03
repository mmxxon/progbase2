#include "cui.h"

#include <vector>
using namespace std;
void Cui::PhotosMainMenu() {
  vector<Photo> ph = storage_->getAllPhotos();
  cout << "Id,User" << endl;
  for (int i = 0; i < ph.size(); i++)
    cout << ph[i].id << "," << ph[i].User << endl;
  cout << endl;
  this->show();
}
void Cui::PhotoMenu(int photo_id) {
  optional<Photo> ph = storage_->getPhotoById(photo_id);
  if (!ph)
    cout << "Incorrect id\n";
  else {
    cout << "Id,User,likes,comments" << endl;
    cout << ph.value().id << "," << ph.value().User << "," << ph.value().likes
         << "," << ph.value().comments << endl;
  }
  this->show();
}
void Cui::photoUpdateMenu(int photo_id) {
  optional<Photo> photo = storage_->getPhotoById(photo_id);
  if (!photo)
    cout << "Incorrect id\n";
  else {
    Photo ph = photo.value();
    cout << "Please, choose, what you want to change:\n1. User\n2. likes\n3. "
            "comments"
         << endl;
    int com;
    cin >> com;
    while (com > 3 || com < 1) {
      cout << "Incorrect command, try again\n";
      cin >> com;
    }
    if (com == 1) {
      cout << "Enter new User" << endl;
      cin >> ph.User;
    }
    if (com == 2) {
      cout << "Enter new likes" << endl;
      cin >> ph.likes;
    }
    if (com == 3) {
      cout << "Enter new comments" << endl;
      cin >> ph.comments;
    }
    storage_->updatePhoto(ph);
  }
  this->show();
}
void Cui::photoDeleteMenu(int photo_id) {
  if (!storage_->removePhoto(photo_id)) cout << "Incorrect id" << endl;
  this->show();
}
void Cui::photoCreateMenu() {
  Photo ph;
  cout << "Please, enter User" << endl;
  cin >> ph.User;
  cout << "Please, enter likes" << endl;
  cin >> ph.likes;
  cout << "Please, enter comments" << endl;
  cin >> ph.comments;
  cout << "New Id:" << storage_->insertPhoto(ph) << endl;
  this->show();
}
void Cui::AlbumsMainMenu() {
  vector<Album> al = storage_->getAllAlbums();
  cout << "Id,Name" << endl;
  for (int i = 0; i < al.size(); i++)
    cout << al[i].id << "," << al[i].name << endl;
  cout << endl;
  this->show();
}
void Cui::AlbumMenu(int album_id) {
  optional<Album> al = storage_->getAlbumById(album_id);
  if (!al)
    cout << "Incorrect id\n";
  else {
    cout << "Id,Name,Cover Photo,Number of photos" << endl;
    cout << al.value().id << "," << al.value().name << ","
         << al.value().coverPhoto << "," << al.value().n_photos << endl;
  }
  this->show();
}
void Cui::albumUpdateMenu(int album_id) {
  optional<Album> album = storage_->getAlbumById(album_id);
  if (!album)
    cout << "Incorrect id\n";
  else {
    Album al = album.value();
    cout << "Please, choose, what you want to change:\n1. Name\n2. Cover "
            "Photo\n3. Number of photos"
         << endl;
    int com = 0;
    cin >> com;
    while (com > 3 || com < 1) {
      cout << "Incorrect command, try again\n";
      cin >> com;
    }
    if (com == 1) {
      cout << "Enter new Name" << endl;
      cin >> ws;
      getline(cin, al.name);
    }
    if (com == 2) {
      cout << "Enter new Cover photo" << endl;
      cin >> al.coverPhoto;
    }
    if (com == 3) {
      cout << "Enter new Number of photos" << endl;
      cin >> al.n_photos;
    }
    storage_->updateAlbum(al);
  }
  this->show();
}
void Cui::albumDeleteMenu(int album_id) {
  if (!storage_->removeAlbum(album_id)) cout << "Incorrect id" << endl;
  this->show();
}
void Cui::albumCreateMenu() {
  Album al;
  cout << "Please, enter Name" << endl;
  cin >> ws;
  getline(cin, al.name);
  cout << "Please, enter Cover Photo" << endl;
  cin >> al.coverPhoto;
  cout << "Please, enter Number of photos" << endl;
  cin >> al.n_photos;
  cout << "New Id:" << storage_->insertAlbum(al) << endl;
  this->show();
}
void Cui::show() {
  int com = 0;
  cout << "Please,enter Entity:\n1. Main entity(Photo)\n2. Extra "
          "Entity(Album)\n3. Finish programm\n";
  cin >> com;
  while (com > 3 || com < 1) {
    cout << "Incorrect command, try again\n";
    cin >> com;
  }
  if (com == 3) {
    cout << "Bye!\n";
    return;
  }
  if (com == 1) {
    cout << "Please, enter option:\n1. Show all photos\n2. Choose photo by "
            "id\n3. Add new photo\n";
    com = 0;
    cin >> com;
    while (com > 3 || com < 1) {
      cout << "Incorrect command, try again\n";
      cin >> com;
    }
    if (com == 1) this->PhotosMainMenu();
    if (com == 2) {
      cout << "Please, enter id\n";
      int id;
      cin >> id;
      cout << "Please, enter option with photo by id:\n1. Show more "
              "information about element\n2. Change a field\n3. Delete photo\n";
      cin >> com;
      while (com > 3 || com < 1) {
        cout << "Incorrect command, try again\n";
        cin >> com;
      }
      if (com == 1) this->PhotoMenu(id);
      if (com == 2) this->photoUpdateMenu(id);
      if (com == 3) this->photoDeleteMenu(id);
    }
    if (com == 3) { this->photoCreateMenu(); }
  } else {
    cout << "Please, enter option:\n1. Show all albums\n2. Choose album by "
            "id\n3. Add new album\n";
    com = 0;
    cin >> com;
    while (com > 3 || com < 1) {
      cout << "Incorrect command, try again\n";
      cin >> com;
    }
    if (com == 1) this->AlbumsMainMenu();
    if (com == 2) {
      cout << "Please, enter id\n";
      int id;
      cin >> id;
      cout << "Please, enter option with album by id:\n1. Show more "
              "information about element\n2. Change a field\n3. Delete album\n";
      cin >> com;
      while (com > 3 || com < 1) {
        cout << "Incorrect command, try again\n";
        cin >> com;
      }
      if (com == 1) this->AlbumMenu(id);
      if (com == 2) this->albumUpdateMenu(id);
      if (com == 3) this->albumDeleteMenu(id);
    }
    if (com == 3) { this->albumCreateMenu(); }
  }
}

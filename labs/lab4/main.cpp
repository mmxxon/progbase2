#include "cui.h"
using namespace std;


int main(){
    FileStorage storage{"./data/"};
    cout<<storage.name()<<endl;
    vector<Organisation> z;
    Cui cui=Cui(&storage);
    cui.show();
    storage.close();
    
    return 0;
}

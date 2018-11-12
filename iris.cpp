#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(){
 
  string s;
  int count = 0;
  vector<vector<string> > data;
  vector<string> temp;
  vector<string> names;
  ifstream file("iris.data");
  
  while(getline(file, s)){
    count++;
    stringstream stream(s);
    string token;  
    
    while(getline(stream, token, ',')) {
      if(count == 5){
	  names.push_back(token);
	  data.push_back(temp);
	  temp.clear();
	  count = 0;
      }
      else{
	  temp.push_back(token);
	  count++;
      }
    }  
  }
  file.close();
  for(int i = 0; i < data.size(); i++){
      for(int j = 0; j < data[i].size(); j++){
	  cout << data[i][j] << " ";
      }
      cout << names[i] << "\n";
  }
  return 0;
}
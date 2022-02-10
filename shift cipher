#include <bits/stdc++.h>
using namespace std;
string enc_shift_cipher(string cipher,int key){

  for(int i=0;i<cipher.length();i++){
    if(97<=cipher[i] && cipher[i]<=122)   // for small 
      cipher[i]=(cipher[i]-97+26-key)%26 +97; 
    else if(65<=cipher[i] && cipher[i]<=90) // for caps
      cipher[i]=(cipher[i]-65+26-key)%26 +65;
  }
  return cipher;
  
}
int main() {

  string message="My name is Shuchi";
  // cin>>message;

  srand(time(0));
  int key=rand()%26;
  
  for(int i=0;i<message.length();i++){
    if(97<=message[i] && message[i]<=122)     //for small
      message[i]=(message[i]-97+key)%26 +97; 
    else if(65<=message[i] && message[i]<=90) //for caps
      message[i]=(message[i]-65+key)%26 +65;
  }
  cout<<message<<endl;
  string ans=enc_shift_cipher(message,key);  

  cout<<ans;
}


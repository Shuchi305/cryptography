#include <bits/stdc++.h>
using namespace std;
string dec(string s,int b,int *k);
int l_n(char c){
    return c-97;
}
char n_l(int n){
    return 'a'+n;
}
string raw(string s){
    //remove all puntuation &cap->small;
    string ss;
    for(char c:s){
        if(c>=65 && c<=90)
            ss+=c+32;
        if(c>=97 && c<=122)
            ss+=c;
    }
    return ss;
}
int inv(int a){
    
    for(int i=1;i<26;i++){
        if((i*a)%26==1)
            return i;
    }
    // while(true){         //(a*ai)%26=1  => a*ai=26n+1 
    //     ai=((26*n)+1)/a;
    //     if(int(ai)==ai){
    //         break;
    //     }
    //     n++;
    // }
    return 0;
}
int in_range(int x){
    return ((x%26)+26)%26;  //+26 % 26 bcoz of neg no. (aii*(c-b) is giving values from -25 to +25. thus adding 26 to neg will work
}
bool comparator(const pair<int,char>& lhs,const pair<int,char>& rhs){  //for affine cipher
            return lhs.first>rhs.first;
}
vector<pair<int,char>> count_let(string s){     //to count number of letters
    map<char,int> m;
    for(char c:s){          // map of all char in random order(ig alphabetical) 
        m[c]++;
    }
    vector<pair<int,char>> vec;
    
    for(auto i : m){                    // vector with <int,char>
        vec.push_back({i.second,i.first});
    }
    
    sort(vec.begin(),vec.end(),&comparator);    //descending order of pairs in vector
    return vec;
}  
class shift{
    public:
    string enc(string s){
        srand(time(0));
        int k=rand()%26;
        s=raw(s);
        for(int i=0;i<s.size();i++){
            int m=l_n(s[i]);
            s[i]=n_l((m+k)%26);
        }
        return s;
    }
    string dec(string s,int k){
        for(int i=0;i<s.size();i++){
            int c=l_n(s[i]);
            s[i]=n_l( in_range( c-k ) );  
        }
        return s;
    }
    void crypt(string s){       // using brute force
        for(int i=0;i<26;i++){
            cout<<dec(s,i)<<endl;
        }
    }
    string crypt_f(string s){     //using frequency table
        vector<pair<int,char>> vec=count_let(s);
        for(int i=0;i<vec.size();i++){
            int k=l_n(vec[i].second)-l_n('e');
            string temp=dec(s,k);
            cout<<"is this your string: "<<temp<<"   (y/n) ";
            char c;
            cin>>c;
            if(c=='y')
                return temp;
        }
        return s;
    }
};
class affine{
    public:
    string enc(string s){
        int z_star[12]={1,3,5,7,9,11,15,17,19,21,23,25};
        srand(time(0));
        int a=z_star[rand()%12];
        int b=rand()%26;
        s=raw(s);
        for(int i=0;i<s.length();i++){
            int m=l_n(s[i]);
            s[i]=n_l( ( a*m + b ) %26 );
        }
        
        cout<<"enc "<<a<<b<<endl;
       // cout<<dec(s,a,b);
        return s;
    }
    string dec(string s,int a,int b){
        
        int ai=inv(a);
        
        for(int i=0;i<s.length();i++){
            int c=l_n(s[i]);
            s[i]=n_l( in_range( ai* (c-b) ) );  
        }
        return s;
    }
    string crypt(string s){
        

        vector<pair<int,char>>vec= count_let(s);
        // for(auto i:vec){
        //     cout<<i.first<<i.second<<endl;
        // }
        vector<char> freq={'e','t','a','o','i','n','s','h','r','d','l','c','u','m','w','f','y','g','p','b','v','k','j','q','x','z'};
        // the sorted order of frequency table using the sort function 
        // not actually used.. only 'e' and 't' are used
       
        int i1=l_n(freq[0]);
        int j2=l_n(freq[1]);
        // for(int i=0;i<26;i++){
        //     int i1=l_n(freq[0]);
        //     for(int j=0;j<26;j++){
        //         if(i==j)
        //             continue;
                for(int k=0;k<vec.size();k++){  
                    int k3=l_n(vec[k].second);
                    for(int l=0;l<vec.size();l++){
                        if(k==l)
                            continue;
                        int l4=l_n(vec[l].second);
                        int a=in_range(in_range(l4-k3)*inv((j2-i1)));
                        int b=in_range(l4-j2*a);
                       // cout<<a<<b<<endl;
                        if( __gcd(a,26)==1){
                            string temp=dec(s,a,b);
                            // if(temp==message){      //use this to check when string will appear
                            //     cout<<"vaola "<<a<<b;
                            //     return temp;
                            // }
                            cout<<"is your string "<<temp<<"   (y/n)";
                            char c;
                            cin>>c;
                            if(c=='y')
                                return temp;
                        }
                    }
            //     }
            // }
        }
        
        return s;
    }
};
class vigenere{
public:
    string enc(string s){
        srand(time(0));
        int r=rand()%4+4;   //4,5,6,7
        int k[r];
        for(int i=0;i<r;i++){
            k[i]=rand()%26;
        }
        int p=0,key=k[0];
        s=raw(s);
        for(int i=0;i<s.length();i++){
            key=k[(p+i)%r];
            int m=l_n(s[i]);
            s[i]=n_l((m+key)%26);
        }
        for(int i=0;i<r;i++)
            cout<<k[i]<<" ";
        cout<<endl;
        return s;
    }
    string dec(string s,int r,int* k){
        for(int i=0;i<s.length();i++){
            int c=l_n(s[i]);
            int key=*(k+(i%r));
            s[i]=n_l( in_range( c-key ) );
        }
        return s;
    }
    int find_r(string s){       
        int rr=1;
        float pp=0;
        for(int r=1;r<10;r++){
            double summ=0;
            for(int j=0;j<r;j++){
                
                double sum=0;
                int x=0;
                map<char,int> m;
                for(int i=0;i<s.size();i=i+r){
                    m[s[i]]++;
                    x++;
                }
                //vector<pair<int,char>> vec=count_let(ss);
                for(auto ii:m){
                    sum+=pow(ii.second,2);
                }
                sum=sum/pow(x,2);
                summ+=sum;
            } 
            
            summ=summ/r;
            cout<<summ<<" ";
            if(summ>pp){
                rr=r;
                pp=summ;
                // if(summ-0.065)
                //     return r;
            }
        }
        return rr;
    }
    string crypt(string s){
        int r=find_r(s);
        int key[r];
        map<char,float> m2={{'a',0.082}, {'b',0.015}, {'c',0.028}, {'d',0.043}, {'e',0.127}, {'f',0.222}, {'g',0.020}, 
                {'h',0.061}, {'i',0.070}, {'j',0.002}, {'k',0.008}, {'l',0.040}, {'m',0.024}, {'n',0.067}, {'o',0.075},
                {'p',0.019}, {'q',0.001}, {'r',0.060}, {'s',0.063}, {'t',0.091}, {'u',0.028}, {'v',0.010}, {'w',0.023},
                {'x',0.001}, {'y',0.020}, {'z',0.001}
             };
        for(int i=0;i<r;i++){
            int ss=0;
            map<char,int> m;
            for(int j=i;j<s.size();j=j+r){
                ss++;
                m[s[j]]++;
            }
            double Mg=0,K=0,sum2=0;
            for(int g=0;g<26;g++){   
                double  mg=0;
                for(auto i:m2){
                    int l=l_n(i.first);
                    mg+=i.second*m[n_l((l+g)%26)];
                    sum2+=pow(m[n_l((l+g)%26)],2);
                }
                mg=mg/ss;
                sum2=sum2/pow(ss,2);
                if(abs(mg-sum2)<abs(Mg-sum2)){
                    K=g;
                    Mg=mg;
                }
            }
            key[i]=K;
        }
        
        for(int i=0;i<r;i++)
            cout<<key[i]<<" ";
        cout<<endl;
        string mes=dec(s,r,key);
        return mes;
    }
};
int main()
{
    
    // affine obj;
    // string message="this is the code for affine cipher. it is doing well. for small texts it runs several times before giving the correct output. however for long texts it is giving correct output in one go .i am happy";
    // string cipher=obj.enc(message);
    // cout<<obj.crypt(cipher);
    
    //shift obj2;
    //string message="this is for shift cipher. brute force as well as using frequency table can be used.";
    //obj2.crypt(s);
    // cout<<obj2.crypt_f(cipher);
    // string message="asdf";
    
    // vigenere obj3;
    // string message="A purely peer-to-peer version of electronic cash would allow onlinepayments to be sent directly from one party to another without going through afinancial institution. Digital signatures provide part of the solution, but the mainbenefits are lost if a trusted third party is still required to prevent double-spending.We propose a solution to the double-spending problem using a peer-to-peer network.The network timestamps transactions by hashing them into an ongoing chain ofhash-based proof-of-work, forming a record that cannot be changed without redoingthe proof-of-work. The longest chain not only serves as proof of the sequence ofevents witnessed, but proof that it came from the largest pool of CPU power. Aslong as a majority of CPU power is controlled by nodes that are not cooperating toattack the network, they'll generate the longest chain and outpace attackers. Thenetwork itself requires minimal structure. Messages are broadcast on a best effortbasis, and nodes can leave and rejoin the network at will, accepting the longestproof-of-work chain as proof of what happened while they were gone.Commerce on the Internet has come to rely almost exclusively on financial institutions serving astrusted third parties to process electronic payments. While the system works well enough formost transactions, it still suffers from the inherent weaknesses of the trust based model.Completely non-reversible transactions are not really possible, since financial institutions cannotavoid mediating disputes. The cost of mediation increases transaction costs, limiting theminimum practical transaction size and cutting off the possibility for small casual transactions,and there is a broader cost in the loss of ability to make non-reversible payments for nonreversible services. With the possibility of reversal, the need for trust spreads. Merchants mustbe wary of their customers, hassling them for more information than they would otherwise need.A certain percentage of fraud is accepted as unavoidable. These costs and payment uncertaintiescan be avoided in person by using physical currency, but no mechanism exists to make paymentsover a communications channel without a trusted party.What is needed is an electronic payment system based on cryptographic proof instead of trust,allowing any two willing parties to transact directly with each other without the need for a trustedthird party. Transactions that are computationally impractical to reverse would protect sellersfrom fraud, and routine escrow mechanisms could easily be implemented to protect buyers. Inthis paper, we propose a solution to the double-spending problem using a peer-to-peer distributedtimestamp server to generate computational proof of the chronological order of transactions. Thesystem is secure as long as honest nodes collectively control more CPU power than anycooperating group of attacker nodes.";    // string cipher=obj2.enc(message);
    // string cipher=obj3.enc(message);
    // cout<<obj3.find_r(cipher);
    // cout<<obj3.crypt(cipher);
    
    return 0;
 }

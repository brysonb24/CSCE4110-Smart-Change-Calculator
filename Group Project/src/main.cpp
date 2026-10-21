#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
struct Result { bool possible=false; vector<int> coins; long long operations=0; double microseconds=0; };
vector<int> normalized(vector<int> c) { sort(c.begin(),c.end()); c.erase(unique(c.begin(),c.end()),c.end()); return c; }
Result greedy(int amount, vector<int> coins) {
    Result r; auto start=chrono::steady_clock::now();
    sort(coins.rbegin(),coins.rend());
    int left=amount;
    for(int coin:coins){++r.operations; int count=left/coin; left%=coin; for(int i=0;i<count;++i)r.coins.push_back(coin);}
    r.possible=(left==0); if(!r.possible)r.coins.clear();
    r.microseconds=chrono::duration<double,micro>(chrono::steady_clock::now()-start).count(); return r;
}
Result dynamicProgramming(int amount,const vector<int>& coins){
    Result r; auto start=chrono::steady_clock::now();
    const int INF=amount+1; vector<int> dp(amount+1,INF),previous(amount+1,-1); dp[0]=0;
    for(int a=1;a<=amount;++a)for(int coin:coins){++r.operations;
        if(coin<=a && dp[a-coin]!=INF && dp[a-coin]+1<dp[a]){dp[a]=dp[a-coin]+1;previous[a]=coin;}
    }
    r.possible=(dp[amount]!=INF);
    if(r.possible)for(int a=amount;a>0;a-=previous[a])r.coins.push_back(previous[a]);
    r.microseconds=chrono::duration<double,micro>(chrono::steady_clock::now()-start).count(); return r;
}
string breakdown(const Result& r){if(!r.possible)return "No solution";if(r.coins.empty())return "(no coins)";
    vector<int> c=r.coins;sort(c.rbegin(),c.rend());ostringstream os;
    for(size_t i=0;i<c.size();){size_t j=i;while(j<c.size()&&c[j]==c[i])++j;if(i)os<<" + ";os<<c[i]<<"c x "<<(j-i);i=j;}return os.str();}
void display(const string& name,const Result& r){cout<<name<<": "<<breakdown(r)<<"\n";
    cout<<"  Coins: "<<(r.possible?to_string(r.coins.size()):"N/A")<<", operations: "<<r.operations
        <<", elapsed: "<<fixed<<setprecision(2)<<r.microseconds<<" us\n";}
void exportRow(int amount,const vector<int>& coins,const Result& g,const Result& d){
    const string file="results.csv";ifstream in(file);bool header=!in.good()||in.peek()==ifstream::traits_type::eof();
    ofstream out(file,ios::app);if(!out){cerr<<"Could not write "<<file<<"\n";return;}
    if(header)out<<"amount,denominations,greedy_possible,greedy_count,greedy_operations,greedy_microseconds,dp_possible,dp_count,dp_operations,dp_microseconds\n";
    ostringstream ds;for(size_t i=0;i<coins.size();++i){if(i)ds<<";";ds<<coins[i];}
    out<<amount<<",\""<<ds.str()<<"\","<<g.possible<<","<<(g.possible?int(g.coins.size()):-1)<<","<<g.operations<<","<<g.microseconds<<","<<d.possible<<","<<(d.possible?int(d.coins.size()):-1)<<","<<d.operations<<","<<d.microseconds<<"\n";
    cout<<"Saved comparison to "<<file<<"\n";
}
void compare(int amount,vector<int> coins,bool save){coins=normalized(coins);Result g=greedy(amount,coins),d=dynamicProgramming(amount,coins);
    cout<<"\nAmount: "<<amount<<" cents | Denominations: ";for(int c:coins)cout<<c<<" ";cout<<"\n";
    display("Greedy",g);display("Dynamic programming",d);
    if(!d.possible)cout<<"Conclusion: exact change is impossible.\n";
    else if(!g.possible)cout<<"Conclusion: greedy got stuck, but DP found a solution.\n";
    else if(g.coins.size()>d.coins.size())cout<<"Conclusion: greedy used "<<(g.coins.size()-d.coins.size())<<" extra coins.\n";
    else cout<<"Conclusion: greedy achieved the optimal coin count.\n";
    if(save)exportRow(amount,coins,g,d);
}
int main(int argc,char** argv){
    if(argc>1&&string(argv[1])=="--demo"){
        compare(30,{1,10,25},true);compare(6,{3,4},true);compare(3,{2,4},true);compare(87,{1,5,10,25},true);return 0;
    }
    cout<<"SMART CHANGE CALCULATOR - Greedy vs Dynamic Programming\n";
    while(true){cout<<"\nEnter amount in cents (0-100000, q to quit): ";string line;if(!getline(cin,line)||line=="q"||line=="Q")break;
        istringstream a(line);int amount;string extra;if(!(a>>amount)||(a>>extra)||amount<0||amount>100000){cout<<"Invalid amount.\n";continue;}
        cout<<"Enter positive coin denominations separated by spaces (e.g. 1 10 25): ";if(!getline(cin,line))break;
        istringstream input(line);vector<int> coins;int c;bool bad=false;while(input>>c){if(c<=0||c>100000){bad=true;break;}coins.push_back(c);}
        if(!input.eof()||bad||coins.empty()){cout<<"Invalid denominations; use positive whole numbers only.\n";continue;}
        compare(amount,coins,true);
    }
    return 0;
}


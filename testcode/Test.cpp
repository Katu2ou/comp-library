#include<iostream>
using namespace std;

long dp[1000001][10];
int main(){
  int n;
  cin>>n;
  for(int i=1;i<=9;i++)dp[0][i]=1;
  for(int i=1;i<n;i++){
    for(int j=1;j<=9;j++){
      dp[i][j]=0;
      for(int dis=-1;dis<=1;dis++){
        if(j+dis>=1 &&j+dis<=9)dp[i][j]=(dp[i][j]+dp[i-1][j+dis])%998244353;
      }
    }
  }
  long long ans=0;
  for(int i=1;i<=9;i++)ans+=dp[n-1][i];
  cout<<ans%998244353<<endl;
}
// This problem is stupid, that it only accepts solve2.
// namely I can only 
#include <stdio.h>

#include <cmath>
#include <string>
using namespace std;

int N, K;
double s[10100];

bool isOk(double c) {
  int count = 0;
  for (int i = 0; i < N; ++i) {
    count += (int)(s[i] / c);
    if (count >= K) {
      return true;
    }
  }
  return false;
}

double getRes() {
  double low = 0, high = 1000000;
  while (high - low > 1e-5) {
    double mid = (high + low) / 2;
    if (isOk(mid)) {
      low = mid;
    } else {
      high = mid;
    }
  }
  /*
  int t = (int)(low * 100);
  if (isOk((t + 1) * 0.01)) {
    return (t + 1) * 0.01;
  }
  return t * 0.01;
  */
  printf("low = %lf\n", low);
  double t = ((int)(low  * 100) / 100.0) + 0.02;
  //printf("low = %lf, t = %lf\n", low, t);
  while (t > (0.01 - 1e-9) && !isOk(t)) {
    t -= 0.01;
  }
  printf("t = %lf\n", t);
  return t;
}

string solve2()  
{  
    double lb=0,ub=100100;  
    while(ub-lb>1e-5){
        double mid=(lb+ub)/2;  
        if(isOk(mid)){  
            lb=mid;
        }
        else{
            ub=mid;
        }
    }
    //printf("ub = %lf, floor(ub*100) = %lf, floor(ub*100)/100 = %lf\n",
    //    ub, floor(ub*100), floor(ub*100)/100);
    char buf[20]; 
    snprintf(buf, sizeof(buf), "%.2f\n",floor(ub*100)/100);  
    return string(buf);
}

/*
int main() {
  freopen("CableMaster.in", "r", stdin);
  scanf("%d%d", &N, &K);
  for (int i = 0; i < N; ++i) {
    scanf("%lf", &s[i]);
  }
  double res = getRes();
  char buf[20];
  snprintf(buf, sizeof(buf), "%.2lf\n", res);
  string s1 = buf;
  string s2 = solve2();
  if (s1 != s2) {
    printf("s1 != s2\n");
    printf("s1 = %s, s2 = %s\n", s1.c_str(), s2.c_str());
    return 1;
  }
  printf("%s", s1.c_str());
  return 0;
}
*/

#include <stdio.h>

//int N, K;
int data[10000];

bool isOk(int c) {
  int count = 0;
  for (int i = 0; i < N; ++i) {
    count += (data[i] / c);
    if (count >= K) {
      return true;
    }
  }
  return false;
}

int main() {
  freopen("CableMaster.in", "r", stdin);
  scanf("%d%d", &N, &K);
  for (int i = 0; i < N; ++i) {
    double a;
    scanf("%lf", &a);
    s[i] = a;
    data[i] = (int)(a*100+0.1);
  }
  int low = 0;
  int high = 10000000;
  while (high > low + 1) {
    int mid = (high + low) / 2;
    if (isOk(mid)) {
      low = mid;
    } else {
      high = mid;
    }
  }
  if (isOk(high)) {
    low = high;
  }
  char buf[20];
  snprintf(buf, sizeof(buf), "%.2lf\n", low / 100.0);
  string s2 = solve2();
  if (s2 != buf) {
    /*
    while (1);
    printf("s1 != s2\n");
    printf("s1 = %s, s2 = %s\n", buf, s2.c_str());
    return 1;
    */
  }
  printf("%s", s2.c_str());
  return 0;
}

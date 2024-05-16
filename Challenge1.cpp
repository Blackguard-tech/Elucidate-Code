#include <bits/stdc++.h>
using namespace std;

#define num long long int
#define v vector
#define vi v<num>

v<pair<num,num>> contests, problems; // contests[i] = (m[i], s[i]). problems[j] = (q[j], d[j])
vi B; // Bob builds this later
num c, p; // number of contests and problems

int main() {
  // accept input
  cin >> c >> p;
  contests.assign(c, {0,0}); 
  problems.assign(p, {0,0});

  for(int i=0; i<c; i++) {
    num m, s; cin >> m >> s; // m[i] and s[i]
    contests[i].first = m;
    contests[i].second = s;
  }
  for(int j=0; j<p; j++) {
    num q, d; cin >> q >> d;
    problems[j].first = q;
    problems[j].second = d;
  }

  sort(contests.begin(), contests.end()); // sort the contests

  // time for Bob!
  B.assign(c, 0);
  B[0] = contests[0].second; 
  for(int i=1; i<c; i++) B[i] = max(B[i-1], contests[i].second);

  // main program 
  num answer = 0; 
  for(int j=0; j<p; j++) {
    num q = problems[j].first;
    // for each problem, binary search best m[i]
    int l=0, r=c-1;
    int i=-1;
    while(l<=r)
    {
    	int mid = (l+r)/2;
    	if(contests[mid].first <= q){
    		i = mid;
    		l = mid+1;
		} else r = mid-1;
	}
    // Now we check for B[i]!

    if (i!=-1) answer += max(0LL, B[i]-problems[j].second);
    
  }

  cout << answer << endl; // output the answer

  return 0;
}


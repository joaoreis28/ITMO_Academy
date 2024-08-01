#include <bits/stdc++.h>
 
using namespace std;
#define MAX 212345
#define MAXI 1123456789

typedef long long ll;



ll v[MAX];
ll seg[4*MAX];
ll n, m, a, b, option;


ll build(ll p, ll l, ll r)
{
    if (l ==  r)
        return seg[p] = v [l];
    ll m = (l + r)/2;

    return seg[p] =  min(build(2*p, l, m), build(2*p +1, m+ 1, r));
}


ll query(ll a, ll b ,ll p, ll l, ll r)
{
    if( b < l || a > r)
        return MAXI;
    if( a <= l && b >= r)
        return seg[p] ;
    ll m = (l + r)/2;

    return min(query(a, b, 2*p, l, m), query(a, b, 2*p +1, m+ 1, r));
}


ll update(ll i, ll x, ll p, ll l, ll r)//muda valor da posicao i para x
{
    if(i < l  || r < i)
        return seg[p];
    if(l == r) 
        return seg[p] = x;
    ll m = (l + r) /2;
    return seg[p] = min(update(i , x, 2*p, l, m), update(i , x, 2*p + 1, m + 1, r));
}

 
int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> n >> m;
    for(ll i = 0; i < n; i++)
        cin >> v[i];

    build(1, 0, n-1);


    for(ll i = 0; i< m; i++)
    {
        cin >> option >> a >>b;

        if(option == 1)
            update(a , b  ,1,0, n-1);
        if(option == 2)
            cout << query(a , b - 1, 1, 0, n -1) << endl;

    }
        
    
   
 
    
 
    return 0;
}
 
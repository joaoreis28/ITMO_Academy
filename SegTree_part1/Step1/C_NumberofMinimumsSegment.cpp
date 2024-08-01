#include <bits/stdc++.h>
 
using namespace std;
#define MAX 212345
#define MAXI 1123456789

typedef long long ll;



ll v[MAX];
vector < pair<ll,ll> > seg(4*MAX);
ll n, m, a, b, option;


pair <ll, ll> build(ll p, ll l, ll r)
{
    if (l ==  r)
    {
        pair <ll,ll> par = make_pair(v[l], 1);
        return seg[p] = par;
    }
        
    ll m = (l + r)/2;

    pair <ll, ll> esq = build(2*p, l, m);
    pair <ll, ll> dir = build(2*p + 1, m + 1, r);


    if( esq.first == dir .first)
        return seg[p] = make_pair(esq.first, esq.second + dir.second);
    
    return seg[p] =  min(esq, dir);
}


pair<ll,ll> query(ll a, ll b ,ll p, ll l, ll r)
{
    if( b < l || a > r)
        return make_pair(MAXI, 1);
    if( a <= l && b >= r)
        return seg[p] ;
    ll m = (l + r)/2;


    pair <ll, ll> esq = query(a, b,2*p, l, m);
    pair <ll, ll> dir = query(a, b,2*p + 1, m + 1, r);

    if(esq.first == dir.first)
        return  make_pair(esq.first, esq.second + dir.second);

    return min(esq, dir);
}


pair<ll,ll> update(ll i, ll x, ll p, ll l, ll r)//muda valor da posicao i para x
{
    if(i < l  || r < i)
        return seg[p];
    if(l == r) 
        return seg[p] = make_pair(x, 1);
    ll m = (l + r) /2;


    pair <ll, ll> esq = update(i, x, 2*p, l, m);
    pair <ll, ll> dir = update(i, x, 2*p + 1, m + 1, r);


    if( esq.first == dir .first)
        return seg[p] = make_pair(esq.first, esq.second + dir.second);
    
    return seg[p] =  min(esq, dir);

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
        {
            pair <ll,ll> resp = query(a , b - 1, 1, 0, n -1);
            cout << resp.first << " " << resp.second << endl;
        }

    }
 
    
 
    return 0;
}
 
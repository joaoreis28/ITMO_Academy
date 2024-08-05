#include <bits/stdc++.h>
 
using namespace std;
#define MAX 212345
#define MAXI 1123456789
const int MIN = INT_MIN;

typedef long long ll;



struct valores
{
    ll sum;
    ll suf;
    ll pref;
    ll seg;

};


ll v[MAX];
vector < valores> seg(4*MAX);
ll n, m;


valores build(ll p, ll l, ll r)
{
    if (l ==  r)
    {
        valores cur = {v[l],
        v[l],
        v[l],
        v[l]};

        return seg[p] = cur;
    }
    ll m = (l + r)/2;


    valores esq = build(2*p, l , m);
    valores dir = build(2*p+1, m+1, r);

    valores resp = {
        esq.sum + dir.sum,
        max(dir.suf, dir.sum + esq.suf),
        max(esq.pref, esq.sum + dir.pref),
        max(esq.seg, max(dir.seg, esq.suf + dir.pref) )};


    

    return seg[p] =  resp;
}


valores query(ll a, ll b ,ll p, ll l, ll r)
{
    if( b < l || a > r)
    {
        valores cur = {0, MIN, MIN, MIN};
        return cur;
    }
    if( a <= l && b >= r)
        return seg[p] ;
    ll m = (l + r)/2;

    valores esq = query(a, b,2*p, l , m);
    valores dir = query(a, b,2*p+1, m+1, r);

    valores resp = {
        esq.sum + dir.sum,
        max(dir.suf, dir.sum + esq.suf),
        max(esq.pref, esq.sum + dir.pref),
        max(esq.seg, max(dir.seg, esq.suf + dir.pref) )
        };



    return resp;
}


valores update(ll i, ll x, ll p, ll l, ll r)//muda valor da posicao i para x
{
    if(i < l  || r < i)
        return seg[p];
    if(l == r)
    {
        valores cur = 
        {
            x,x, x,x
        };
        return seg[p] = cur;
    }

    ll m = (l + r) /2;

    valores esq = update(i, x,2*p, l , m);
    valores dir = update(i, x,2*p+1, m+1, r);

    valores resp = {
        esq.sum + dir.sum,
        max(dir.suf, dir.sum + esq.suf),
        max(esq.pref, esq.sum + dir.pref),
        max(esq.seg, max(dir.seg, esq.suf + dir.pref) )};


    return seg[p] = resp;
}

 


int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> n >> m;
    for(ll i = 0; i < n; i++)
        cin >> v[i];

    build(1, 0, n-1);


    valores resp = query(0, n-1, 1, 0, n- 1);
    if(resp.seg < 0)
        cout << 0 << endl;
    else
        cout << resp.seg << endl;


    while(m--)
    {
        int i, x;
        cin >> i >> x;

        update(i, x, 1, 0, n-1);

        valores aba  = query(0, n- 1, 1, 0, n-1);

        if(aba.seg < 0)
            cout << 0 << endl;
        else
            cout << aba.seg << endl;



    }


        
    
   
 
    
 
    return 0;
}
 
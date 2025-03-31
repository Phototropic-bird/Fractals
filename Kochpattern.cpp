/*
Copy the output and put it directly into desmos
*/
#include <bits/stdc++.h>
using namespace::std;
#define tr 0.017453
float length=2;
char backslash=92;
int degrees[]={0,60,120,180,240,300};
map<int,pair<float,float>> vc;

class thepoint
{
public:
    float x,y;
    thepoint(float x,float y):
    x(x), y(y) {}
    void print_xrange(thepoint t){
        float mn=min(t.x,this->x);
        float mx=max(t.x,this->x);
        printf("%cleft%c{%6f<=x<=%6f%cright%c}\n",backslash,backslash,mn,mx,backslash,backslash);
    } 
};
typedef struct thepoint point;
typedef point* dot;
void ini_vc(){
    for(int i=0; i<6; i++) vc[degrees[i]]={length*cos(degrees[i]*tr),length*sin(degrees[i]*tr)};
}
float powfixed(float a,float b){
    if(b=0) return 0;
    while(b>1) a*=a;
    return a;
}
void print_line(point st,point af){
    float delta_x=af.x-st.x;
    float delta_y=af.y-st.y;
    float slope=delta_y/delta_x;
    printf("y-%6f=%6f(x-%6f)",st.y,slope,st.x);
    st.print_xrange(af);
}
point Kochcurve(int order,point p,int slope_degree){
    slope_degree+=360;
    slope_degree%=360;
    if(order==0){
        point af=point(p.x+vc[slope_degree].first,p.y+vc[slope_degree].second);
        print_line(p,af);
        return af;
    }else{
        point temp(p);
        temp=Kochcurve(order-1,p,slope_degree);
        temp=Kochcurve(order-1,temp,slope_degree+60);
        temp=Kochcurve(order-1,temp,slope_degree-60);
        temp=Kochcurve(order-1,temp,slope_degree);
        return temp;
    }
}
void Kochsnowflake(int order){
    point temp(0,0);
    temp=Kochcurve(order,temp,60);
    temp=Kochcurve(order,temp,-60);
    Kochcurve(order,temp,180);
}
int main(){
    ini_vc();
    Kochcurve(4,point(0,0),0);
    //Kochsnowflake(3);
    return 0;
}

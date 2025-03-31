/*
Copy the output and put it directly into desmos
As for the variables :
you can change "n" to set the degree of your pattern.
you can change "R" to make your pattern more or less complicated.
you can change "length" to set the length of each side of your pattern.
*/
#include<bits/stdc++.h>
using namespace::std;
#define tr 0.017453
char bs=92;

double R=7;   //order
int n=90;   //degree
double length=5; //length

double lenc;    //csc(n/2)
double degree;    //per degree
int blcm;
map<double,pair<double,double>> vc;

class point{
    public:
    double x,y;
    void print_xrange(point other){
        double mn=min(this->x,other.x);
        double mx=max(this->x,other.x);
        printf("%cleft%c{%6f<=x<=%6f%cright%c}\n",bs,bs,mn,mx,bs,bs);
    }

    point(double x=0,double y=0):
    x(x),y(y) {}

    point operator+(point other){
        return point(this->x+other.x,this->y+other.y);
    }
    point operator/(double n){
        return point(this->x/n,this->y/n);
    }
};
void print_line(point a,point b){
    if((a.x-b.x)==0){
        printf("x=%6f",a.x);
        printf(" %cleft%c{%6f<=y<=%6f%cright%c}\n",bs,bs,min(a.y,b.y),max(a.y,b.y),bs,bs);
        return;
    }
    double slope=(a.y-b.y)/(a.x-b.x);
    printf("y-%6f=%6f(x-%6f) ",a.y,slope,a.x);
    a.print_xrange(b);
}
int GCD(int a,int b){
    if(b==0) return a;
    return GCD(b,a%b);
}
int LCM(int a,int b){
	int g=GCD(a,b);
    return (a*b)/g;
}
void ini_vector(){
    lenc=(1/sin((n/2)*tr));

    degree=(double(180-n)/2);
    int temp=((180-n)%2==0)?degree : (180-n);
    blcm=LCM(360,temp);

    double sum=0;
    while(sum<=blcm){
        vc[sum]={cos(sum*tr),sin(sum*tr)};
        //printf("degree:%6f  x : %6f  y : %6f\n",sum,vc[sum].first,vc[sum].second);
        sum+=degree;
    }
    sum=-degree;
    while(sum>=-blcm){
        vc[sum]={cos(sum*tr),sin(sum*tr)};
        sum-=degree;
    }
}
double correction(double a){
    while(a>blcm) a-=blcm;
    return a;
}
point n_curve(int order,point p,double slope_degree,double len){
    slope_degree=correction(slope_degree);
    if(order==0){ //draw line
        point af=point(p.x+len*vc[slope_degree].first,p.y+len*vc[slope_degree].second);
        print_line(p,af);
        return af;
    }else{  //conduct recursion
        point temp(p);
        temp=n_curve(order-1,p,slope_degree+degree,len);
        temp=n_curve(order-1,temp,slope_degree-degree,len);
        return temp;
    }
}
void n_curve_pattern(int r,double len){
    point p(0,0);
    p=n_curve(r,p,degree,len);
    n_curve(r,p,-degree,len);
}
void all_n_curve(int order,double len){
    if(order>R) return;
    else{
        n_curve_pattern(order,len);
        all_n_curve(order+1,len*lenc/2);
    }
}
int main(){
    ini_vector();
    n_curve_pattern(R,length);
    //all_n_curve(0,length);
    return 0;
}

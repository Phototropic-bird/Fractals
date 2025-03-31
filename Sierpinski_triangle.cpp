/*
Copy the output and put it directly into desmos
*/
#include<bits/stdc++.h>
using namespace::std;
#define tr 0.017453
char bs=92;
double length=5;
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
}A,B,C;
class triangle{
    public:
    point a,b,c;
    triangle(point a={0,0},point b={0,0},point c={0,0}):
    a(a),b(b),c(c) {}
}T;
void print_line(point a,point b){
    double slope=(a.y-b.y)/(a.x-b.x);
    printf("y-%6f=%6f(x-%6f) ",a.y,slope,a.x);
    a.print_xrange(b);
}
void ini(){
    A={0,0};
    B={length/2,length*sin(60*tr)};
    C={length,0};
    T={A,B,C};
    print_line(A,B);
    print_line(B,C);
    print_line(A,C);
}
void Sierpinski(int order,triangle H,int section){
    if(order==0) return;

    if(section==1) print_line(H.b,H.c);
    else if(section==2) print_line(H.a,H.c);
    else if(section==3) print_line(H.b,H.a);

    Sierpinski(order-1,{H.a,(H.a+H.b)/2,(H.a+H.c)/2},1);    //section
    Sierpinski(order-1,{(H.a+H.b)/2,H.b,(H.b+H.c)/2},2);
    Sierpinski(order-1,{(H.a+H.c)/2,(H.b+H.c)/2,H.c},3);
}
int main(){
    ini();
    Sierpinski(6,T,0); //order 0=1
    return 0;
}

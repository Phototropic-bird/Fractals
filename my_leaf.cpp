/*
Copy the output and put it directly into desmos
As for the variables :
you can change "node amount" to give your leaf more or less nodes.
you can change "degree" to make your leaf more or less complicated.
you can change "per_l" to make your leaf's nodes closer or farther.
you can change "len_dcrease" to adjust the distance decline rate of your leaf's nodes.
*/
#include<bits/stdc++.h>
using namespace::std;
#define tr 0.017453
#define pi 3.1415926
char bs=92;
int node_amount=4;
int degree=3;
double edge_width=0.08;
double edge_len=50;
double per_l=4;//distance between point//edge_len/(2*node_amount+1);
double len_dcrease=0.2;//when degree++ ,per_l=per_l*len_dcrease
class point{
    public:
    double x,y;
    void print_xrange(point other){
        double mn=min(this->x,other.x);
        double mx=max(this->x,other.x);
        printf("%cleft%c{%.4f<=x<=%.4f%cright%c}\n",bs,bs,mn,mx,bs,bs);
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
class para{
    public:
    double open,slope;
    point bottom;

    para(double x=0,double y=0,point p=point(0,0)):
    open(x),slope(y),bottom(p) {}

    bool empty(){
        if(open==0 && slope==0 && bottom.x==0 && bottom.y==0) return true;
        return false;
    }
};
class expon{
    public:
    double open,slope;
    point bottom;

    expon(double x=0,double y=0,point p=point(0,0)):
    open(x),slope(y),bottom(p) {}
};
class line{
    public:
    double open,slope;
    point bottom;

    line(double x,double y,point p=point(0,0)):
    open(x),slope(y),bottom(p) {}
};
point matrix(point p,double slope,point rot){
    double cs=cos(-slope),sn=sin(-slope);
    p.x-=rot.x;
    p.y-=rot.y;
    return point(p.x*cs-p.y*sn+rot.x,p.x*sn+p.y*cs+rot.y);
}
void print_line(point a,point b){
    if((a.x-b.x)==0){
        printf("x=%.4f",a.x);
        printf(" %cleft%c{%.4f<=y<=%.4f%cright%c}\n",bs,bs,min(a.y,b.y),max(a.y,b.y),bs,bs);
        return;
    }
    double slope=(a.y-b.y)/(a.x-b.x);
    printf("y-%.4f=%.4f(x-%.4f) ",a.y,slope,a.x);
    a.print_xrange(b);
}
void print_edge(){
    printf("%.4fx=(%csin%cleft(3.14159*y/%.4f%cright))/(%ccos%cleft(3.14159*y/%.4f%cright)-2) ",edge_width,bs,bs,edge_len,bs,bs,bs,edge_len,bs); //up based
    printf("%cleft%c{0<y<%.4f%cright%c}\n",bs,bs,edge_len,bs,bs);    //up based
    printf("-%.4fx=(%csin%cleft(3.14159*y/%.4f%cright))/(%ccos%cleft(3.14159*y/%.4f%cright)-2) ",edge_width,bs,bs,edge_len,bs,bs,bs,edge_len,bs); //up based
    printf("%cleft%c{0<y<%.4f%cright%c}\n",bs,bs,edge_len,bs,bs);    //up based
}
void print_edge_as_range(){
    printf("%cleft%c{%.4fx>(%csin%cleft(3.14159*y/%.4f%cright))/(%ccos%cleft(3.14159*y/%.4f%cright)-2) %cright%c}",bs,bs,edge_width,bs,bs,edge_len,bs,bs,bs,edge_len,bs,bs,bs);
    printf("%cleft%c{-%.4fx>(%csin%cleft(3.14159*y/%.4f%cright))/(%ccos%cleft(3.14159*y/%.4f%cright)-2) %cright%c}",bs,bs,edge_width,bs,bs,edge_len,bs,bs,bs,edge_len,bs,bs,bs);
}
bool bottom_over_edge(point p){
    double son=sin(pi*p.y/edge_len);
    double mother=cos(pi*p.y/edge_len)-2;
    p.y=son/mother;
    p.x=edge_width*p.x;
    if(p.x<p.y || (-p.x)<p.y) return true;
    return false;
}
double Arithmetic_sequence(int nums,double sum,double a1){
    return (2*sum-2*a1*nums)/(nums*(nums-1));
}
template <typename T>
void fix_queue(queue<T> &a){
    while (a.size()>4) a.pop();
}
//line
double line_max_open_range=2;//leaf botton open range
double line_min_open_range=5;//leaf top open range
double li_op_increase=1.5;
double li_a1=0;

vector<double> li_op_ranges;
//ini
void li_ini_open_range(){
    double t=line_min_open_range-line_max_open_range;
    double d1=Arithmetic_sequence(2*node_amount-1,t,li_a1);
    double bk=line_max_open_range;
    double r=li_a1;
    for(int i=0; i<=2*node_amount; i++){    //cause the top need another one
        li_op_ranges.push_back(bk);
        bk+=r;
        r+=d1;
    }
}
//print
void model_print_line(line l,int flag){ //1 =   // 2 < up   // 3 > low
    double sn=sin(l.slope);
    double cs=cos(l.slope);
    if(flag==1)
    printf("(x-%.4f)*%.4f+(y-%.4f)*%.4f=%.4f%cleft|((x-%.4f)*%.4f-(y-%.4f)*%.4f)%cright|"
    ,l.bottom.x,sn,l.bottom.y,cs,l.open,bs,l.bottom.x,cs,l.bottom.y,sn,bs);
    if(flag==2)
    printf("%cleft%c{(x-%.4f)*%.4f+(y-%.4f)*%.4f<%.4f%cleft|((x-%.4f)*%.4f-(y-%.4f)*%.4f)%cright|%cright%c}"
    ,bs,bs,l.bottom.x,sn,l.bottom.y,cs,l.open,bs,l.bottom.x,cs,l.bottom.y,sn,bs,bs,bs);
    if(flag==3)
    printf("%cleft%c{(x-%.4f)*%.4f+(y-%.4f)*%.4f>%.4f%cleft|((x-%.4f)*%.4f-(y-%.4f)*%.4f)%cright|%cright%c}"
    ,bs,bs,l.bottom.x,sn,l.bottom.y,cs,l.open,bs,l.bottom.x,cs,l.bottom.y,sn,bs,bs,bs);
}
void line_print_line(line l,queue<line> up_vec,queue<line> low_vec){    //1 top//2 mid//3 down
    if(bottom_over_edge(l.bottom)) return;
    model_print_line(l,1);
    while(!up_vec.empty()){
        model_print_line(up_vec.front(),2);
        up_vec.pop();
    }
    while(!low_vec.empty()){
        model_print_line(low_vec.front(),3);
        low_vec.pop();
    }
    print_edge_as_range();  //leaf edge //up based
    printf("\n");
}
//math
pair<point,double> get_line_poi_slope(double x,line l){
    double y=l.open*abs(x-l.bottom.x)+l.bottom.y;
    point p(x,y);
    p=matrix(p,l.slope,l.bottom);
    double slope=(x-l.bottom.x>0) ? l.open : -l.open;
    slope=1/slope;
    slope=atan(slope);  //reset slope//case the degree problem made by y=x^2
    slope+=l.slope;
    return {p,slope};
}
vector<line> make_l(double len,line l,double op){
    double orix=l.bottom.x;
    vector<line> vec_li;
    for(int i=0; i<=2*node_amount; i++){    //cause the top need another one
        orix+=len;
        pair<point,double> new_p=get_line_poi_slope(orix,l);
        vec_li.push_back(line(li_op_ranges[i]*op,new_p.second,new_p.first));
    }
    return vec_li;
}
//recursion
void line_recursion(line l,line based_on_line,queue<line> up_vec,queue<line> low_vec,double len,int d,double op,bool flag,int side){//1==right//2==left//3 begin
    if(d==0) return;
    line_print_line(l,up_vec,low_vec);
    vector<line> new_bo_right=make_l(len,l,op);
    vector<line> new_bo_left=make_l(-len,l,op);
    for(int i=1; i<2*node_amount; i+=2){    //right
            queue<line> copy_up_vec=up_vec;
            queue<line> copy_low_vec=low_vec;
            copy_up_vec.push(new_bo_right[i+1]);
            copy_low_vec.push(new_bo_right[i-1]);
            if(flag){
                if(side==1) copy_up_vec.push(based_on_line);
                else copy_low_vec.push(based_on_line);
            }
            fix_queue<line>(copy_up_vec);
            fix_queue<line>(copy_low_vec);
            line_recursion(new_bo_right[i],l,copy_up_vec,copy_low_vec,len*len_dcrease,d-1,op*li_op_increase,1,1);
    }
    for(int i=1; i<2*node_amount; i+=2){    //left
            queue<line> copy_up_vec=up_vec;
            queue<line> copy_low_vec=low_vec;
            copy_up_vec.push(new_bo_left[i+1]);
            copy_low_vec.push(new_bo_left[i-1]);
            if(flag){
                if(side==1) copy_low_vec.push(based_on_line);
                else copy_up_vec.push(based_on_line);
            }
            fix_queue(copy_up_vec);
            fix_queue(copy_low_vec);
            line_recursion(new_bo_left[i],l,copy_up_vec,copy_low_vec,len*len_dcrease,d-1,op*li_op_increase,1,2);
    }
}
void line_draw_ini_line(point p){
    print_line(p,point(p.x,p.y+edge_len));
    li_ini_open_range();
    vector<line> vec;
    for(int i=0; i<=2*node_amount; i++){    //cause the top need another one
        p.y+=per_l;
        line l(li_op_ranges[i],0,p);
        vec.push_back(l);
    }
    for(int i=1; i<2*node_amount; i+=2){
        queue<line> up_vec;
        queue<line> low_vec;
        up_vec.push(vec[i+1]);
        low_vec.push(vec[i-1]);
        line_recursion(vec[i],line(0,pi/2,(0,0)),up_vec,low_vec,per_l*len_dcrease,degree,1,1,3);
    }
}
//line

//parabola
double parabola_max_open_range=0.1;//leaf botton open range
double parabola_min_open_range=0.3;//leaf top open range
double pa_op_increase=1.5;
double pa_a1=0;

vector<double> op_ranges;
//ini
void pa_ini_open_range(){
    double t=parabola_min_open_range-parabola_max_open_range;
    double d1=Arithmetic_sequence(2*node_amount-1,t,pa_a1);
    double bk=parabola_max_open_range;
    double r=pa_a1;
    for(int i=0; i<=2*node_amount; i++){    //cause the top need another one
        op_ranges.push_back(bk);
        bk+=r;
        r+=d1;
    }
}
//print
void model_print_parabola(para bo,int flag){    //1 =   // 2 < up   //3 > low
    double sn=sin(bo.slope);
    double cs=cos(bo.slope);
    if(flag==1)
    printf("%.4f(x-%.4f)+%.4f(y-%.4f)=%.4f(%.4f(x-%.4f)-%.4f(y-%.4f))^2 "
    ,sn,bo.bottom.x,cs,bo.bottom.y,bo.open,cs,bo.bottom.x,sn,bo.bottom.y);
    if(flag==2)
    printf("%cleft%c{%.4f(x-%.4f)+%.4f(y-%.4f)<%.4f(%.4f(x-%.4f)-%.4f(y-%.4f))^2 %cright%c}"
    ,bs,bs,sn,bo.bottom.x,cs,bo.bottom.y,bo.open,cs,bo.bottom.x,sn,bo.bottom.y,bs,bs);
    if(flag==3)
    printf("%cleft%c{%.4f(x-%.4f)+%.4f(y-%.4f)>%.4f(%.4f(x-%.4f)-%.4f(y-%.4f))^2 %cright%c}"
    ,bs,bs,sn,bo.bottom.x,cs,bo.bottom.y,bo.open,cs,bo.bottom.x,sn,bo.bottom.y,bs,bs);
}
void print_parabola(para bo,queue<para> up_vec,queue<para> low_vec){    //1 top//2 mid//3 down
    if(bottom_over_edge(bo.bottom)) return;
    model_print_parabola(bo,1);
    while(!up_vec.empty()){
        model_print_parabola(up_vec.front(),2);
        up_vec.pop();
    }
    while(!low_vec.empty()){
        model_print_parabola(low_vec.front(),3);
        low_vec.pop();
    }
    print_edge_as_range();  //leaf edge //up based
    //printf(" %cleft%c{0<y<%.4f%cright%c}",bs,bs,edge_len,bs,bs);   // y's range //up based 
    printf("\n");
}
//math
pair<point,double> get_para_poi_slope(double x,para bo){
    double y=bo.open*(x-bo.bottom.x)*(x-bo.bottom.x)+bo.bottom.y;
    point p(x,y);
    p=matrix(p,bo.slope,bo.bottom);
    double slope=2*bo.open*(x-bo.bottom.x);
    slope=1/slope;
    slope=atan(slope);  //reset slope//case the degree problem made by y=x^2
    slope+=bo.slope;
    return {p,slope};
}
vector<para> make_bo(double len,para bo,double op){
    double orix=bo.bottom.x;
    vector<para> vec_bo;
    for(int i=0; i<=2*node_amount; i++){    //cause the top need another one
        orix+=len;
        pair<point,double> new_p=get_para_poi_slope(orix,bo);
        vec_bo.push_back(para(op_ranges[i]*op,new_p.second,new_p.first));
    }
    return vec_bo;
}
//recursion
void parabola(para bo,para based_on_para,queue<para> up_vec,queue<para> low_vec,double len,int d,double op,bool flag,int side){//1==right//2==left//3 begin
    if(d==0) return;
    print_parabola(bo,up_vec,low_vec);
    vector<para> new_bo_right=make_bo(len,bo,op);
    vector<para> new_bo_left=make_bo(-len,bo,op);
    for(int i=1; i<2*node_amount; i+=2){    //right
            queue<para> copy_up_vec=up_vec;
            queue<para> copy_low_vec=low_vec;
            copy_up_vec.push(new_bo_right[i+1]);
            copy_low_vec.push(new_bo_right[i-1]);
            if(flag){
                if(side==1) copy_up_vec.push(based_on_para);
                else copy_low_vec.push(based_on_para);
            }
            fix_queue<para>(copy_up_vec);
            fix_queue<para>(copy_low_vec);
            parabola(new_bo_right[i],bo,copy_up_vec,copy_low_vec,len,d-1,op*pa_op_increase,1,1);
    }
    for(int i=1; i<2*node_amount; i+=2){    //left
            queue<para> copy_up_vec=up_vec;
            queue<para> copy_low_vec=low_vec;
            copy_up_vec.push(new_bo_left[i+1]);
            copy_low_vec.push(new_bo_left[i-1]);
            if(flag){
                if(side==1) copy_low_vec.push(based_on_para);
                else copy_up_vec.push(based_on_para);
            }
            fix_queue<para>(copy_up_vec);
            fix_queue<para>(copy_low_vec);
            parabola(new_bo_left[i],bo,copy_up_vec,copy_low_vec,len,d-1,op*pa_op_increase,1,2);
    }
}
void pa_draw_ini_line(point p){
    print_line(p,point(p.x,p.y+edge_len));
    pa_ini_open_range();
    vector<para> vec;
    for(int i=0; i<=2*node_amount; i++){    //cause the top need another one
        p.y+=per_l;
        para bo(op_ranges[i],0,p);
        vec.push_back(bo);
    }
    for(int i=1; i<2*node_amount; i+=2){
        queue<para> up_vec;
        queue<para> low_vec;
        up_vec.push(vec[i+1]);
        low_vec.push(vec[i-1]);
        parabola(vec[i],para(0,0,(0,0)),up_vec,low_vec,per_l*len_dcrease,degree,1,0,3);
    }
}
//parabola

//exponent
double exponent_max_open_range=2;//leaf botton open range
double exponent_min_open_range=5;//leaf top open range
double ex_op_increase=1.5;
double ex_a1=0;

vector<double> ex_op_ranges;
//ini
void ex_ini_open_range(){
    double t=exponent_min_open_range-exponent_max_open_range;
    double d1=Arithmetic_sequence(2*node_amount-1,t,ex_a1);
    double bk=exponent_max_open_range;
    double r=ex_a1;
    for(int i=0; i<=2*node_amount; i++){    //cause the top need another one
        ex_op_ranges.push_back(bk);
        bk+=r;
        r+=d1;
    }
}
//print
void model_print_exponent(expon ex,int flag){    //1 =   // 2 < up   //3 > low
    double sn=sin(ex.slope);
    double cs=cos(ex.slope);
    if(flag==1)
    printf("%.4f(x-%.4f)+%.4f(y-%.4f)+1=%.4f^{%cleft|%.4f(x-%.4f)-%.4f(y-%.4f)%cright|}"
    ,sn,ex.bottom.x,cs,ex.bottom.y,ex.open,bs,cs,ex.bottom.x,sn,ex.bottom.y,bs);
    if(flag==2)
    printf("%cleft%c{%.4f(x-%.4f)+%.4f(y-%.4f)+1<%.4f^{%cleft|%.4f(x-%.4f)-%.4f(y-%.4f)%cright|} %cright%c}"
    ,bs,bs,sn,ex.bottom.x,cs,ex.bottom.y,ex.open,bs,cs,ex.bottom.x,sn,ex.bottom.y,bs,bs,bs);
    if(flag==3)
    printf("%cleft%c{%.4f(x-%.4f)+%.4f(y-%.4f)+1>%.4f^{%cleft|%.4f(x-%.4f)-%.4f(y-%.4f)%cright|} %cright%c}"
    ,bs,bs,sn,ex.bottom.x,cs,ex.bottom.y,ex.open,bs,cs,ex.bottom.x,sn,ex.bottom.y,bs,bs,bs);
}
void print_exponent(expon ex,queue<expon> up_vec,queue<expon> low_vec){    //1 top//2 mid//3 down
    if(bottom_over_edge(ex.bottom)) return;
    model_print_exponent(ex,1);
    while(!up_vec.empty()){
        model_print_exponent(up_vec.front(),2);
        up_vec.pop();
    }
    while(!low_vec.empty()){
        model_print_exponent(low_vec.front(),3);
        low_vec.pop();
    }
    print_edge_as_range();  //leaf edge //up based
    printf(" %cleft%c{0<y<%.4f%cright%c}",bs,bs,edge_len,bs,bs);   // y's range //up based 
    printf("\n");
}
//math
pair<point,double> get_expon_poi_slope(double x,expon ex){
    double y=pow(ex.open,fabs(x-ex.bottom.x))+ex.bottom.y;
    point p(x,y);
    p.y-=1;
    p=matrix(p,ex.slope,ex.bottom);
    double slope=(x-ex.bottom.x>=0) ? log(ex.open)*pow(ex.open,x-ex.bottom.x) : -log(ex.open)*pow(ex.open,-(x-ex.bottom.x));
    slope=1/slope;
    slope=atan(slope);  //reset slope//case the degree problem // the oringinal degree is based on x axis
    slope+=ex.slope;
    return {p,slope};
}
vector<expon> make_ex(double len,expon ex,double op){//here
    double orix=ex.bottom.x;
    vector<expon> vec_ex;
    for(int i=0; i<=2*node_amount; i++){    //cause the top need another one
        orix+=len;
        pair<point,double> new_p=get_expon_poi_slope(orix,ex);
        vec_ex.push_back(expon(ex_op_ranges[i]*op,new_p.second,new_p.first));
    }
    return vec_ex;
}
//recursion
void exponents(expon ex,expon based_on_para,queue<expon> up_vec,queue<expon> low_vec,double len,int d,double op,bool flag,int side){//1==right//2==left//3 begin
    if(d==0) return;
    print_exponent(ex,up_vec,low_vec);
    vector<expon> new_ex_right=make_ex(len,ex,op);
    vector<expon> new_ex_left=make_ex(-len,ex,op);
    for(int i=1; i<2*node_amount; i+=2){    //right
            queue<expon> copy_up_vec=up_vec;
            queue<expon> copy_low_vec=low_vec;
            copy_up_vec.push(new_ex_right[i+1]);
            copy_low_vec.push(new_ex_right[i-1]);
            if(flag){
                if(side==1) copy_up_vec.push(based_on_para);
                else copy_low_vec.push(based_on_para);
            }
            fix_queue<expon>(copy_up_vec);
            fix_queue<expon>(copy_low_vec);
            exponents(new_ex_right[i],ex,copy_up_vec,copy_low_vec,len,d-1,op*ex_op_increase,1,1);
    }
    for(int i=1; i<2*node_amount; i+=2){    //left
            queue<expon> copy_up_vec=up_vec;
            queue<expon> copy_low_vec=low_vec;
            copy_up_vec.push(new_ex_left[i+1]);
            copy_low_vec.push(new_ex_left[i-1]);
            if(flag){
                if(side==1) copy_low_vec.push(based_on_para);
                else copy_up_vec.push(based_on_para);
            }
            fix_queue<expon>(copy_up_vec);
            fix_queue<expon>(copy_low_vec);
            exponents(new_ex_left[i],ex,copy_up_vec,copy_low_vec,len,d-1,op*ex_op_increase,1,2);
    }
}
void ex_draw_ini_line(point p){
    print_line(p,point(p.x,p.y+edge_len));
    ex_ini_open_range();
    vector<expon> vec;
    for(int i=0; i<=2*node_amount; i++){    //cause the top need another one
        p.y+=per_l;
        expon ex(ex_op_ranges[i],0,p);
        vec.push_back(ex);
    }
    for(int i=1; i<=2*node_amount; i+=2){
        queue<expon> up_vec;
        queue<expon> low_vec;
        up_vec.push(vec[i+1]);
        low_vec.push(vec[i-1]);
        exponents(vec[i],expon(0,0,(0,0)),up_vec,low_vec,per_l*len_dcrease,degree,1,0,3);
    }
}
//exponent
int main(){
    print_edge();
    //pa_draw_ini_line(point(0,0));      //parabola
    ex_draw_ini_line(point(0,0));       //exponential leaf
    //line_draw_ini_line(point(0,0));  //straight line leaf
    return 0;
}

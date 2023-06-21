# include <iostream>
using namespace std;

class A{
public:
    A(){
        cout<<"A called"<<endl;
    }
    virtual void alpha() = 0;
    ~A(){
        cout<<"A  distructor called"<<endl;
    }
    virtual void alpha1() = 0;
    virtual void alpha2() = 0;
};
class B:public A{
public:
    int a = 5;
    B(){
        cout<<"B called"<<endl;
    }
    void alpha(){
        cout<<"Alpha called"<<endl;
    }
    ~B(){
        cout<<"B  distructor called"<<endl;
    }
    virtual void alpha1() = 0;
    virtual void alpha2() = 0;
};
class D:public B{
public:
};
class C: public D{
public:
    void alpha1(){
        cout<<"Alpha1 called"<<endl;
        cout<<a<<endl;
    }
    void alpha2(){
        cout<<"Alpha1 called"<<endl;
        // cout<<a<<endl;
    }
};
int main(){
    // B alp1;
    A* alp = new C;
    // alp->alpha();
    // alp->B::alpha1();
    alp->alpha2();
}
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
struct DebugTools
{
    DebugTools() {}
    void strMsgInline(string data){
        cout<<data;
    }
    void strMsg(string data){
        cout<<data<<endl;
    }
    void intMsg(int val){
        cout<<val<<endl;
    }
    void doubMsg(double val){
        //ostringstream msg;
        //msg<<val;
        //this->strMsg(msg.str());
        cout<<val<<endl;
    }
    void boolMsg(bool expr){
        expr==1?
        cout<<"true"<<endl:
        cout<<"false"<<endl;
    }
};
/*
#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H
#include <string>

class DebugTools
{
public:
    DebugTools();
    void message(std::string data);
    void message(int val);
    void message(bool expr);
};

#endif // DEBUGTOOLS_H
*/

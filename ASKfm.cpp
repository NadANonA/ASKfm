#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

struct User
{
    string passwd , Name ;
    int Id;
};
struct Q
{
    string q ;
    int fromq , toq , qid;
};
struct A
{
    string ans;
    int fromu , tou , qid , aid;
};

    fstream users("users.txt");
    fstream Qs("Questions.txt");
    fstream Ans("Answers.txt");

    vector<User> v;
    vector<Q> g;
    vector<A> h;
    bool flag=0;

    int getRandomId() {
    // Seed the random number generator with current time
        srand(static_cast<unsigned int>(time(nullptr)));

    // Generate a random ID between 1 and 10000
        int randomId = rand() % 10000 + 1;

        return randomId;
    }


/*void enter(int c){
    string name , pass;
    if(c==1){
        cout<<"Name : "; cin>>name;
        cout<<"Password : ";cin>>pass;
        string s , p;
        while(s!=name && p!=pass){
            //nps>>s>>p;
        }   
        if(s==name && p==pass) cout<<"Hello "<<name<<endl;
        else{
            cout<<"User not found , be sure name and password are correct"<<endl;
            enter(c);
        } 
    }
    else if(c==2){
        cout<<"Name : "; cin>>name;
        cout<<"Password : ";cin>>pass;
        //nps<<name<<" "<<pass<<endl;
        
        cout<<"Hello "<<name<<endl;
   }
}*/

void UserToVector(fstream x){
    int i=0;
    while(!x.eof()){
        x>>v[i].Id>>v[i].Name>>v[i].passwd;
        i++;
    }
}
void toVector(fstream x){
    int i=0;
    while(!x.eof()){
        x>>g[i].fromq>>g[i].toq>>g[i].qid;
        getline(x,g[i].q,'?');
    }
}

class Account{
    string name , pass ;
    int id1;
public:
    Account(){}
    void setName(string n){
        name=n;
    }
    void setPass(string p){
        pass=p;
    }
    void setid(){
        id1=getRandomId();
    }
    int getid(){
        return id1;
    }
    void signup(){
        string p , s;
        cout<<"Name : "; cin>>s;
        cout<<"Password : ";cin>>p;
        //nps<<name<<" "<<pass<<endl;
        setid();
        User x;
        x.Name=s;
        x.Id=getid();
        x.passwd=p;
        v.push_back(x);
        cout<<"Hello "<<s<<endl;
    }

    void login(){
        string s , p , ss , pp ;
        cout<<"Name : "; cin>>s;
        cout<<"Password : ";cin>>p;
        int i=0 ;
        while(s!=ss && p!=pp && i<v.size()){
            ss=v[i].Name; pp=v[i].passwd; 
            i++;
        }   
        i--;
        if(s==ss && p==pp){
            id1=v[i].Id;
            cout<<"Hello "<<s<<endl;
            
        } 
        else{
            cout<<"User not found , be sure name and password are correct"<<endl;
            flag=1;
        } 
    }

    void logout(){
        int i=0;
        string s , p ;
        while(v[i].Name!=s && v[i].passwd!=p){
            i++;
        }
        v.erase(v.begin()+i);
    }
};

class State{
    int from , to ;
    string ques;
public:
    void Setq(string s){
        ques=s;
    }
    string Getq(){
        return ques;
    }
    void Seto(int x){
        to=x;
    }
    int Geto(){
        return to;
    }
    void Setfrom(int d){
        from=d;
    }
    int Getfrom(){
        return from;
    }
    //virtual int x()=0;
    
};
class Question : public State {
public:
    
    void Askq(){
        string qq;
        cout<<"Write your Question please : ";
        getline(cin,qq,'?');
        Setq(qq);
        Q x;
        x.q=qq;
        x.fromq=Getfrom();
        x.toq=Geto();
        x.qid=getRandomId();
        g.push_back(x);
    }

    void Delq(int x){
        int i=0;
        while(g[i].qid!=x){
            i++;
        }
        //cout<<Getfrom()<<endl;
        if(g[i].fromq==Getfrom()){
            g.erase(g.begin()+i);
            i=0;
            while(i<h.size()){
                if(h[i].qid==x){
                    h.erase(h.begin()+i);
                    break;
                }
            }
            cout<<"Delete is Done "<<endl;
        } 
        else{
            cout<<"You can not delete others Questions !!"<<endl;
        }
    }

    void EditQ(int eid){
        int i=0;
        while(g[i].qid!=eid && i<g.size()){
            i++;
        }
        if(g[i].fromq==Getfrom()){
            string qq;
            cout<<"Enter the new Question : ";
            getline(cin,qq,'?');
            g[i].q="";
            g[i].q=qq;
            cout<<"Edit is done"<<endl;
        }
        else if(i>=g.size()){
            cout<<"Question not found !"<<endl;
        }
        else {
            cout<<"You can not Edit others Questions !!"<<endl;
        }
    }
};

class Answer : public State {
public:
    void AnsQ(int x){// qid , from , to , ans
        int i=0;
        string s;
        cout<<"Write your Answer : ";
        getline(cin,s,'.');
        while(g[i].qid!=x){
            i++;
        }
        A c;
        c.qid=x;
        c.fromu=Getfrom();
        c.tou=g[i].fromq;
        c.ans=s;
        c.aid=getRandomId();
        h.push_back(c);
    } 

    void EditA(int eid){
        int i=0;
        while(h[i].qid!=eid && i<h.size()){
            i++;
        }
        if(h[i].fromu==Getfrom() && i<h.size()){
            string aa;
            cout<<"Enter the new Answer : ";
            getline(cin,aa,'.');
            h[i].ans="";
            h[i].ans=aa;
            cout<<"Edit is done"<<endl;
        }
        else if(i>=h.size()){
            cout<<"Answer not found !"<<endl;
        }
        else {
            cout<<"You can not Edit others Answer !!"<<endl;
        }
    }
};

void menu1();
void menu2();
/////////////////////////////////////////////////////////////////////////////////////////

int main(){
    int i=0;
    Q qs;
    while(Qs>>qs.fromq>>qs.toq>>qs.qid){
        getline(Qs,qs.q);
        g.push_back(qs);
    }
    User ur;
    while(users>>ur.Id>>ur.Name>>ur.passwd){
       v.push_back(ur);
    }
    A an;
    while( Ans>>an.fromu>>an.tou>>an.qid>>an.aid){
       getline(Ans,an.ans);
       h.push_back(an);
    }
    Qs.close();
    users.close();
    Ans.close();

    int choice;
    while(choice!=1 && choice!=2){
        menu1();
        try{
            cin>>choice;
            if(choice>2) throw "error";
        }
        catch(...){
            cerr<<"wrong input , enter from the menu please !"<<endl;
        }
    }
    
    Account a;
    Question w;
    Answer m;
    if(choice==1){
        a.login();
        w.Setfrom(a.getid());
    }
    else if(choice==2){
        a.signup();
    }
    
while(flag==0){
    menu2();
    try{
        cin>>choice;
        if(choice>10) throw "error";
    }
    catch(...){
        cerr<<"wrong input , enter from the menu please !"<<endl;
        continue;
    }
    cout<<endl;
    if(choice==1){
        int i=0;
        cout<<"Qid      fromID      Qustion"<<endl;
        while(i<g.size()){
            if(a.getid()==g[i].toq){
                cout<<g[i].qid;cout<<"    "<<g[i].fromq;
                cout<<"    "<<g[i].q<<'?'<<endl;
            }
            i++;
        }
    }
    else if(choice==2){
        i=0;
        cout<<"Qid      Question"<<endl;
        while(i<g.size()){
            if(a.getid()== g[i].fromq){
                cout<<g[i].qid<<"  "<<g[i].q<<'?'<<endl;
            }
            i++;
        }
    }
    else if(choice==3){
        int x ;
        cout<<"Enter Question id : ";
        cin>>x;
        m.AnsQ(x);
    }
    else if(choice==4){
        int x;
        cout<<"Enter the id of the Question you want to delete : ";
        cin>>x;
        
        w.Delq(x);
    }
    else if(choice==5){
        int b;
        cout<<"Enter user id : ";
        cin>>b;
        w.Seto(b);
        int bb=a.getid();
        w.Setfrom(bb);
        w.Askq();
    }
    else if(choice==6){
        cout<<"ID"<<"    "<<"Name"<<endl<<endl;
        for(int i=0;i<v.size();i++){
            cout<<v[i].Id<<"    "<<v[i].Name<<endl;
        }
    }
    else if(choice==7){
        i=0;
        int j=0;
        cout<<"Qid    Answer"<<endl;
        while(i<h.size()){
            /*while(j<g.size()){
                if(h[i].qid==g[j].qid){
                    cout<<g[j].qid<<"   "<<g[j].q<<'?'<<" "<<h[i].ans<<endl;
                    break;
                }
                j++;
            }*/
            cout<<h[i].qid<<" "<<h[i].ans<<endl;
            i++;
        }
    }
    else if(choice==8){
        char edit;
        int eid;
        cout<<"do you want to edit A or Q :";
        cin>>edit;
        if(edit=='Q'){
            cout<<"Enter Question id : ";
            cin>>eid;
            w.EditQ(eid);
        }
        else if(edit=='A'){
            cout<<"Enter Question id : ";
            cin>>eid;
            m.EditA(eid);
        }
        else {
            cout<<"Wrontg input , write A or Q "<<endl;
        }
    }
    else if(choice==9){
        a.logout();
        break;
    }
    else if(choice==10){
        break;
    }
}
    ofstream users1("users.txt");
    ofstream Qs1("Questions.txt");
    ofstream Ans1("Answers.txt");
    /*while(i<v.size()){
        users1<<v[i].Id<<" "<<v[i].Name<<" "<<v[i].passwd<<endl;
        cout<<v[i].Id<<" "<<v[i].Name<<" "<<v[i].passwd<<endl;
        i++;
    }
    i=0;
    while(i<g.size()){
        Qs1<<g[i].fromq<<" "<<g[i].toq<<" "<<g[i].qid<<" "<<g[i].q<<endl;
        cout<<g[i].fromq<<" "<<g[i].toq<<" "<<g[i].qid<<" "<<g[i].q<<endl;
        i++;
    }*/
    users1.seekp(0);
    for (const auto& user : v) {
        users1<<user.Id<<" "<<user.Name<<" "<<user.passwd<<endl;
    }
    Qs1.seekp(0);
    for (const auto& gg : g) {
        Qs1<<gg.fromq<<" "<<gg.toq<<" "<<gg.qid<<" "<<gg.q<<endl;
    }
    Ans1.seekp(0);
    for(const auto& hh : h){
        Ans1<<hh.fromu<<" "<<hh.tou<<" "<<hh.qid<<" "<<hh.aid<<" "<<hh.ans<<endl;
    }
}

void menu1(){
    cout<<"     1 login"<<endl;////
    cout<<"     2 sign up"<<endl;////
    cout<<endl;
    cout<<"enter the number of your choice : ";////
}

void menu2(){
    cout<<endl;
    cout<<"     1   Print all Qustions to me"<<endl;////
    cout<<"     2   Print all Questions from me"<<endl;////
    cout<<"     3   Answer Question"<<endl;
    cout<<"     4   Delete Question"<<endl;////
    cout<<"     5   Ask Question"<<endl;// 
    cout<<"     6   Print all users"<<endl;////
    cout<<"     7   Print Answered Questions"<<endl;
    cout<<"     8   Edit Question or Answer"<<endl;
    cout<<"     9   logout"<<endl;////
    cout<<"     10  Exit program"<<endl;////
    cout<<endl;
    cout<<"enter the number of your choice : ";////
}

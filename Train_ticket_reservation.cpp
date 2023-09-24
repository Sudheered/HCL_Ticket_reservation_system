
#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <unordered_map>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define ll long long
class Train_Ticket_Reservation_system{
public:
    map<int,int>traintrips;
    map<int,vector<int>>traincapacity;
    map<int,pair<pair<string,string>,int>>tripdetails;
    map<pair<pair<string,string>,int>,set<int>>tripno;
    map<int,vector<string>>bording;
    map<int,vector<string>>droping;
    map<int,pair<pair<float,float>,int>>timing;
    map<string,pair<string,vector<int>>>user;
    string user_or_manager;
    vector<int> mounth;
    string passwards;
    Train_Ticket_Reservation_system(){
        passwards="admin@123";
        mounth={0,31,28,31,30,31,30,31,31,30,31,30,31};
        rand();
        Get_user_needs();
    }
    void rand(){
        cout<<"should i enter random train trips if yes then press 1 else press any other key"<<endl;
        char a;
        cin>> a;
        if(a=='1'){
            traintrips[1]=1;
            traincapacity[1]={10,10};
            tripdetails[1]={{"salem","chennai"},0};
            tripno[{{"salem","chennai"},0}].insert(1);
            bording[1].push_back("busstand");
            droping[1]={"tambaram","central"};
            timing[1]={{12.12,12.12},1};
        }
    }
    bool is_strong(string s){
        if(s.size()<8)return false;
        bool num=false;
        bool u=false;
        bool l=false;
        for(auto it:s){
            if(it>='a'&&it<='z')l=true;
            else if(it>='A'&&it<='Z')u=true;
            else if(it>='0'&&it<='9')num=true;
        }
        if(num&&u&&l)return true;
        return false;
    }
    bool login(string& username){
        int temp=0;
        while(++temp){
            if(temp==8){
                cout<<"you have failed more than 7 times"<<endl;
                Get_user_needs();
                return false;
            }
            string curr;
            cout<<"please enter your user name"<<endl;
            cin>>curr;
            if(user.find(curr)==user.end()){
                cout<<"you have entered a wrong user name "<<endl<<" To try again enter 1 "<<" to go back to the main menu press any other key "<<endl;
                char pro;
                cin>>pro;
                if(pro!='1'){
                    Get_user_needs();
                    return false;
                }
            }
            else{
                username=curr;
                break;
            }
        }
        temp=0;
        while(++temp){
            if(temp==8){
                cout<<"you have failed more than 7 times"<<endl;
                Get_user_needs();
                return false;
            }
            string curr;
            cout<<"Please enter your passward"<<endl;
            cin>> curr;
            if(user[username].first!=curr){
                cout<<"The passward that you entered is not strong enough"<<endl<<"to try again press 1"<<"to go back to the main menu press any other key"<<endl;
                char pro;
                cin>>pro;
                if(pro!='1'){
                    Get_user_needs();
                    return false;
                }
            }
            else{
                break;
            }
        }
        cout<<"You have successfully loged into your account"<<endl;
        return true;
    }
    void regestration(){
        string username;
        string passward;
        int temp=0;
        while(++temp){
            if(temp==8){
                cout<<"you have failed more than 7 times"<<endl;
                Get_user_needs();
                return;
            }
            string curr;
            cout<<"Please enter a unique username"<<endl;
            cin>>curr;
            if(user.find(curr)!=user.end()){
                char pro;
                cout<<"This user name is already taken"<<endl<<"to try again press 1"<<"to go back to the main menu press any other key"<<endl;
                cin>>pro;
                if(pro!='1'){
                    Get_user_needs();
                    return;
                }
            }
            else{
                username=curr;
                break;
            }
        }
        temp=0;
        while(++temp){
            if(temp==8){
                cout<<"you have failed more than 7 times"<<endl;
                Get_user_needs();
                return;
            }
            cout<<"Please enter a strong passward with utleast 8 charectors, utleast one number,utleast one upper case charector,utleast one lower case charector"<<endl;
            string curr;
            cin>>curr;
            if(is_strong(curr)){
                passward=curr;
                break;
            }
            else {
                char pro;
                cout<<"The passward that you entered is not strong enough"<<endl<<"to try again press 1"<<"to go back to the main menu press any other key"<<endl;
                cin>>pro;
                if(pro!='1'){
                    Get_user_needs();
                    return;
                }
                
            }
        }
        user[username]={passward,{}};
        cout<<"You have successfully created a new account"<<endl;
    }
    void booking(){
        string username;
        if(!login(username))return;
        string from;
        string to;
        cout<<"Enter your from location"<<endl;
        cin>>from;
        cout<<"Enter your to location"<<endl;
        cin>>to;
        int days=0;
        int date;
        string dates;
        int temp=0;
        while(++temp){
            if(temp==8){
                cout<<"You have tried more than 7 times"<<endl<<"to go back to the main menu press 1"<<endl<<"to try again press any other key"<<endl;
                int pro;
                cin>>pro;
                if(pro==1){
                    Get_user_needs();
                    return ;
                }
                booking();
                return;
            }
            string curr;
            cout<<"Enter the date you want to book ticket for in the following format,the year should be current year"<<endl<<"DD/MM/YYYY"<<endl;
            cin>>curr;
            if(curr.size()!=10||curr[2]!='/'||curr[5]!='/'){
                char pro;
                cout<<"You have entered the wrong format"<<"To tryagain press 1"<<"To go back to the mainmenu press any other button"<<endl;
                cin>>pro;
                if(pro!='1'){
                    Get_user_needs();
                    return;
                }
                continue;
            }
            int day=stoi(curr.substr(0,2));
            int mon=stoi(curr.substr(3,2));
            int year=stoi(curr.substr(6,4));
            if(year!=2023||mon<=0||mon>12){
                char pro;
                cout<<"You have entered the wrong format"<<"To tryagain press 1"<<"To go back to the mainmenu press any other button"<<endl;
                cin>>pro;
                if(pro!='1'){
                    Get_user_needs();
                    return;
                }
                continue;
            }
            if(day<=0||mounth[mon]<day){
                char pro;
                cout<<"You have entered the wrong format"<<"To tryagain press 1"<<"To go back to the mainmenu press any other button"<<endl;
                cin>>pro;
                if(pro!='1'){
                    Get_user_needs();
                    return;
                }
                continue;
            }
            for(int i=1;i<mon;i++){
                days+=mounth[i];
            }
            days+=day;
            days--;
            date=days;
            days%=7;
            dates=curr;
            break;
        }
        if(tripno.find({{from,to},days})==tripno.end()){
            cout<<"There is no trains avalable for the searched locations on that date"<<endl<<"To tryagain press 1"<<"To go back to the mainmenu press any other button"<<endl;
            char pro;
            cin>>pro;
            if(pro!='1'){
                Get_user_needs();
                return;
            }
            else{
                booking();
                return;
            }
        }
        cout<<"The trains avalable are:"<<endl;
        for(auto it:tripno[{{from,to},days}]){
            cout<<"  trip number:"<<it;
            cout<<"  |  Train_no:"<<traintrips[it];
            date+=timing[it].second;
            int cm;
            for(int i=1;i<mounth.size();i++){
                if(date>=mounth[i]){
                    cm++;
                    date-=mounth[i];
                }
            }
            string pro=to_string(date)+"/"+to_string(cm)+"/2023";
            cout<<"  |  leaveing date and time:"<<dates<<","<<timing[it].first.first;
            cout<<"  |  reaching date and time:"<<pro<<","<<timing[it].first.second;
            cout<<"  |  Boarding points:";
            for(auto jt:bording[it]){
                cout<<jt;
            }
            cout<<"  |  Dropping points:";
            for(auto jt:droping[it]){
                cout<<jt;
            }
        }
    }
    void manager(){
        cout<<"Enter the manager passward"<<endl;
        string pas;
        cin>>pas;
        if(pas!=passwards){
            cout<<"you have entered the wrong passward"<<endl;
            return;
        }
        cout<<"To insert new train press '1'"<<endl;
        cout<<"To remove already avalable train trip '2'"<<endl;
        int n;
        cin>>n;
        if(n==1){
            int ctn;
            int temp=0;
            while(++temp){
                if(temp==8){
                    cout<<"You have tried more than 7 times"<<endl;
                    manager();
                    return;
                }
                int curr;
                cout<<"Enter a unique trip number of the trip"<<endl;
                cin>>curr;
                if(traintrips.find(curr)==traintrips.end()){
                    ctn=curr;
                    break;
                }
                else{
                    cout<<"The trip number you have entered already exist"<<endl;
                }
            }
            int cttn;
            cout<<"Enter the Train number that is going to mack this trip"<<endl;
            cin>>cttn;
            traintrips[ctn]=cttn;
            int sl;
            int seat;
            cout<<"Enter the number of sleaper seats avalable"<<endl;
            cin>>sl;
            cout<<"Enter the number of seater seats avalable"<<endl;
            cin>>seat;
            traincapacity[ctn]={sl,seat};
            string from;
            cout<<"Enter the from location of the trip"<<endl;
            cin>> from;
            string to;
            cout<<"Enter the to location of the trip"<<endl;
            cin>> to;
            int day;
            cout<<"Enter the day of the trip "<<"sunday:press 1 "<<"monday:press 2 "<<"tuesday:press 3 "<<"wednesday:press 4 "<<"thersday:press 5 "<<"friday:press 6 "<<"saturday:press 7 "<<endl;
            cin>>day;
            day--;
            tripdetails[ctn]={{from,to},day};
            tripno[{{from,to},day}].insert(ctn);
            int nb;
            cout<<"Enter the number of bording points for the trip"<<endl;
            cin>>nb;
            temp=1;
            while(nb--){
                string curr;
                cout<<"enter the "<<temp<<"th bording point"<<endl;
                temp++;
                cin>>curr;
                bording[ctn].push_back(curr);
            }
            int nd;
            cout<<"Enter the number of dropping points for the trip"<<endl;
            cin>>nd;
            temp=1;
            while(nd--){
                string curr;
                cout<<"enter the "<<temp<<"th dropping point"<<endl;
                temp++;
                cin>>curr;
                droping[ctn].push_back(curr);
            }
            cout<<"Enter the bording time in HH.MM format"<<endl;
            float bt;
            float dt;
            cin>>bt;
            cout<<"Enter te dropping time in HH.MM format"<<endl;
            cin>>dt;
            int nod;
            cout<<"Enter the number of days of the trip(if same day of bording and dropping then enter 0)"<<endl;
            cin>>nod;
            timing[ctn]={{bt,dt},nod};
            cout<<"You have successfully created a new trip for the railway station"<<endl<<"To go back to the main menu press 1"<<"to mack more changes pres any other button"<<endl;
            char promax;
            cin>> promax;
            if(promax=='1'){
                Get_user_needs();
                return ;
            }
            else {
                manager();
                return;
            }
        }
    }
    void Get_user_needs(){
        int n;
        cout<<"Press '1' for new Regestration"<<endl;
        cout<<"Press '2' for booking tickets"<<endl;
        cout<<"Press '3' for customer service"<<endl;
        cout<<"Press '4' if you are a manager"<<endl;
        cout<<"Press '5' for end"<<endl;
        cin>>n;
        if(n==1){
            regestration();
            Get_user_needs();
        }
        else if(n==2){
            booking();
            Get_user_needs();
        }
        else if(n==3){
            Get_user_needs();
        }
        else if(n==4){
            manager();
            Get_user_needs();
        }
        else if(n==5)return ;
        else{
            cout<<"invalid input"<<endl;
            Get_user_needs();
        }
    }
};
int main(){
    Train_Ticket_Reservation_system user;
    return 0;
}

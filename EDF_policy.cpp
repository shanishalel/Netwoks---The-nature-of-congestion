#include <stdlib.h>
#include <string>
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include "stdio.h"

using namespace std;

typedef pair<int, int> my_pair;
static int dropped;
static int transmitt_p;
static int transmitt_v;
static int arrived_packets;


/*insert to the queue*/
void insert(priority_queue<my_pair, vector<my_pair>, greater<my_pair>> &myQ, int p, int s, int v, int size){
bool smaller=false;
    while(p>0 && !smaller){
        if(size==myQ.size()){
            pair<int, int> top_que = myQ.top(); 
            if(s>top_que.first){
            dropped++;
            myQ.pop();//remove the min slack
            myQ.push(make_pair(s, v)); 
            p--;
            }
            else{
                smaller=true;
                dropped+=p;
            }
        
        }
        else{
            myQ.push(make_pair(s, v));
            p--;
        }
        
    }    
    
}

//decrease all the queue by 1
void decrease(priority_queue<my_pair, vector<my_pair>, greater<my_pair>> &myQ){
    priority_queue<my_pair, vector<my_pair>, greater<my_pair>> q2;
    //pop out and decrease 
    while (!myQ.empty())
		{
            pair<int, int> top_que = myQ.top(); 
			myQ.pop();
            pair<int, int> tmp=make_pair(top_que.first-1,top_que.second);//decrease by 1
            q2.push(tmp);
		}
    //push back to myQ after decrease
     while (!q2.empty())
		{
            pair<int, int> top_que = q2.top(); 
			q2.pop();
            pair<int, int> tmp=make_pair(top_que.first,top_que.second);
            myQ.push(tmp);
		}    

}

//processing the min slack packets, if the slack is zero we throw the packt
void processing(priority_queue<my_pair, vector<my_pair>, greater<my_pair>> &myQ ){
   pair<int, int> top_que = myQ.top(); 
   //if slack==0
   while(top_que.first==0 && myQ.size()>1 ){
    //    cout<<top_que.first<<endl;
	    myQ.pop();//is ==zero throw 
        dropped++;//if slack== 0 drop it
       top_que = myQ.top();
    } 
    //if slack ==0 but the last one 
    pair<int, int> top_e = myQ.top(); 
    if(top_e.first==0){
        dropped++;
       	myQ.pop();//processing

    }
    //slack!=0
    else{
        myQ.pop();//processing
        transmitt_p++;
        transmitt_v+=top_e.second;
    }
    

}



void print_queue(priority_queue<my_pair, vector<my_pair>, greater<my_pair>> myQ)
{
	while (!myQ.empty())
		{
            pair<int, int> top_que = myQ.top(); 
			cout << "first : "<<top_que.first <<" second : "<<top_que.second<< endl;
			myQ.pop();
		}
}

//when we gets to the eof we decrease and processing until empty
void end_of_file(priority_queue<my_pair, vector<my_pair>, greater<my_pair>> &myQ){
    int size=myQ.size()-1;
    while(!myQ.empty()){
        // cout<<"decrease :"<<endl;//delete
        decrease(myQ);
        // print_queue(myQ);//delete
        processing(myQ);
        // cout<<"processing :"<<endl;//delete
        // print_queue(myQ);//delete

    }

    //printing all the staff
    cout<<"Total arrived packets : "<<arrived_packets<<endl;
    cout<<"Total dropped : "<<dropped<<endl;
    cout<<"Total transmitted : "<<transmitt_p<<endl;
    cout<<"Total transmitted val : "<<transmitt_v<<endl;

}

/*read from the file and intialize the queue*/
void read_file(int size, string name,priority_queue<my_pair, vector<my_pair>, greater<my_pair>> &myQ){
char p;
string num;
int p_total;
ifstream MyReadFile(name);
    while (MyReadFile.get(p)) {
       
            if(p=='('){
                //packet
                MyReadFile.get(p);
                // cout<<"p= "<<p<<endl;//delete
                num+=p;
                while(p!=','){
                    MyReadFile.get(p);
                    num+=p;
                }
                int packet=stoi(num);
                arrived_packets+=packet;
                // cout<<packet<<endl;//delete the print
                num="";
                MyReadFile.get(p);
                num+=p;
                while(p!=','){
                    MyReadFile.get(p);
                    num+=p;
                }
                int slack=stoi(num);
                // cout<<slack<<endl;//delete the print
                num="";
                MyReadFile.get(p);
                num+=p;
                while(p!=')'){
                    MyReadFile.get(p);
                    num+=p;
                }
                int value=stoi(num);
                num="";
                // cout<<value<<endl;//delete the print
                 insert(myQ,packet, slack, value,size);
                //  cout<<"insert"<<endl;
                //  print_queue(myQ);//delete

            }
        
         if(p=='\n'){
            //next line
            // cout<<"printing"<<endl;//delete
            // print_queue(myQ);//delete
            decrease(myQ);
            // cout<<"after decrease"<<endl;//delete
            // print_queue(myQ);//delete

            processing(myQ);
            // cout<<"after processing "<<endl;
            // print_queue(myQ);//delete
   
        }
    
    }
    //eof

end_of_file(myQ);
MyReadFile.close();
       
}

 


// "./edf queue_size file_name"
int main(int argc, char *argv[]){
    priority_queue<my_pair, vector<my_pair>, greater<my_pair>> myQ; 
   int queue_size=atoi(argv[1]);
    string file_name(argv[2]);
    read_file(queue_size, file_name,myQ);
    // read_file(4, "test.txt",myQ);
    // print_queue(myQ);


}


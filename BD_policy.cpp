#include <stdlib.h>
#include <string>
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

typedef pair<int, int> my_pair;

static int dropped;
static int transmitt_p;
static int transmitt_v;
static int arrived_packets;

void processing(priority_queue<my_pair, vector<my_pair>, greater<my_pair>> &myQ ){
    priority_queue<my_pair, vector<my_pair>> q1;
    while(!myQ.empty()){
        pair<int, int> top_que = myQ.top(); 
        if(top_que.second==0){
            dropped++;
        }
        else{
             q1.push(top_que);
        }
        myQ.pop();
    }  

    //if myQ (slack) ==0 in all places
    if(!q1.empty()){
        pair<int, int> max= q1.top();
        transmitt_p++;
        transmitt_v+=max.first;
        q1.pop();
    }
    
    while(!q1.empty()){
        pair<int, int> top_que = q1.top(); 
        q1.pop();
        myQ.push(top_que);
    }

}



//for insert function
void delete_max(priority_queue<my_pair, vector<my_pair>, greater<my_pair>> &myQ ){
    int size=myQ.size()-1;
    priority_queue<my_pair, vector<my_pair>, greater<my_pair>>q2;
    while (size>0)
            {
                pair<int, int> top_que = myQ.top(); 
                myQ.pop();
                q2.push(top_que);
                size--;
            }
            pair<int, int> max = myQ.top();
             myQ.pop();
            dropped++;

        //push back to myQ after decrease
    while (!q2.empty())
            {
                pair<int, int> top_que = q2.top(); 
                q2.pop();
                myQ.push(top_que);
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


/*insert to the queue*/
void insert(priority_queue<my_pair, vector<my_pair>, greater<my_pair>> &myQ, int p, int s, int v, int size){
bool smaller=false;
    while(p>0 && !smaller){
        if(size==myQ.size()){
            pair<int, int> top_que = myQ.top(); 
            if(v>top_que.first){
            myQ.pop();//remove the min slack
            dropped++;
            myQ.push(make_pair(v, s)); 
            p--;
            }
            else{
                smaller=true;
                dropped++;
            }
        
        }
        else{
            myQ.push(make_pair(v, s));
            p--;
        }
        
    }    
    
}

//decrease all the queue by 1
//attention- here the pair is diffrent <value, slack>
void decrease(priority_queue<my_pair, vector<my_pair>, greater<my_pair>> &myQ){
    priority_queue<my_pair, vector<my_pair>, greater<my_pair>> q2;
    //pop out and decrease 
    while (!myQ.empty())
		{
            pair<int, int> top_que = myQ.top(); 
			myQ.pop();
            pair<int, int> tmp=make_pair(top_que.first,top_que.second-1);//decrease by 1
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


#include <queue>
#include <iostream>
#include <array>
using namespace std;
//Main Idea:
// we have an array that holds all of our bills. A queue of customers which we use to check the change.
// we have an int customer that we push into our queue.
//    bool make_change that returns:
//    false if not every customer gets change
//    true if every customer gets change

bool make_change(int payment,int change, double arr[4])
//false if NOT every customer gets change/true if every customer gets change
{
    //these integers will hold the quantity of the bills. we will increment as much as the change needs to be given. Then at the end we take it out of array
    int twenties=0;
    int tens=0;
    int fives=0;
    int ones=0;
    //here we are going in decresing order
    if(change >= 20){
        int num=change/20;      //By dividing we get how many bills of 20 we will need
        while(arr[3]>=num && change!=0){            //now check that our array actually have those many bills and while our change is not 0, keep going.
            --arr[3];                           //keep decrement the array and the change while incrementing that number of 20s you will need to give
            change -= 20;
            --num;
            twenties++;
        }
    }
    //now we get rid of the 20, we go to the 10's
    if(change >= 10){
        int num=change/10;     //find the bills of 10s that we should give back.
        while(arr[2]>=num && change!=0){        //now check that our array actually have those many bills and while our change is not 0, keep going.
            --arr[2];                              //keep decrement the array and the change while incrementing that number of tens you will need to give
            change -= 10;
            --num;
            tens++;
        }
    }
    
    if(change >= 5){
        int num=change/5;                        //find the bills of 5s that we should give back.
        while(arr[1]>=num && change!=0){        //now check that our array actually have those many bills and while our change is not 0, keep going.
            --arr[1];
            change -= 5;                            //keep decrement the array and the change while incrementing that number of fives you will need to give
            --num;
            fives++;
        }
    }
    
    if(change >= 1){                         //find the bills of 1s that we should give back.
        int num=change;                      //now check that our array actually have those many bills and while our change is not 0, keep going.
        while(arr[0]>=num && change!=0){       //keep decrement the array and the change while incrementing that number of ones you will need to give
            --arr[0];
            change--;
            --num;
            ones++;
        }
    }
    
    if(change==0){              //if the change is now 0, return true and all change has been given
        return true;
    }
    
    //now if you went through your entire register and STILL were not able to give the change.
    //You add everything you took out back into the array
    arr[3]+=twenties;
    arr[2]+=tens;
    arr[1]+=fives;
    arr[0]+=ones;
    
    return false;
}
//Implement double total_revenue to compute: Xavier's total revenue
double total_revenue(double arr[4]){
    return (20*arr[3]) + (10*arr[2]) + (5*arr[1]) + arr[0];
}
//MODIFICATION: double sold_product_avg: ice creams sold/per customer
double sold_product_avg(double iceCream, std::queue<double> customers){ //icecreams per customer
    return (100-iceCream)/customers.size();
}
//MODIFICATION: double revenue_avg: revenue/per customer
double revenue_average(std::queue<double>customers, double arr[4]){//revenue per customer
    return total_revenue(arr)/customers.size();
}

int main(){
    
    std::queue<double> customers;
    int balance = 0;
    int n;//number of ice creams to be ordered
    int cost = 2;
    int payment = 0;
    double arr[4]= {0,0,0,0}; //this is keeping track of bills.
    //arr[0] is the number of 1's
    //arr[1] is the number of 5's
    //arr[2] is the number of 10's
    //arr[3] is the number of 20's
    int p1,p5,p10,p20,option;
    int change;
    double iceCream = 100;
    int customer = 0;
    bool getsChange=true;
    //This is a continuation of our queue and we see what the input is going.
    //While you input a 1 it will keep going and when you input a 0 and it will stop.
    while(true)
    {
        cout<<"Any more customers?? INPUT 0 so queue ends, else INPUT 1 :"<<endl;
        cin>>option;
        
        if(option==0)
        {
            cout<<"No more customers left in queue. The summary of our business is as follows::"<<endl;
            if(iceCream != 0){
                cout<<"Xavier has " << iceCream << " ice creams left" << endl;
            }
            break;
        }
        
        if(iceCream == 0){
            cout << "No icecreams left. Xavier is sold out at the "<< customers.size() <<"th customer."<<endl;
            break;
        }
        
        cout<<"How many ice creams will you be buying? " << endl;
        cin >> n;
        cout<<"How many 1's are you giving? " << endl;
        cin>>p1;
        cout<<"How many 5's are you giving? " << endl;
        cin>>p5;
        cout<<"How many 10's are you giving? " << endl;
        cin>>p10;
        cout<<"How many 20's are you giving? " << endl;
        cin >> p20;
        
        payment = p1 + 5*p5 + 10*p10 + 20*p20;
        
        
        if(payment < (cost*n)){
            cout<<"Order did not get place. You did not pay enough.\n";
            continue;
        }
        if(n>iceCream)
        {
            cout<<"Sorry, there are only" << iceCream << "icecreams left"<<endl;
            continue;
        }
        
        change = payment-(cost*n);
        customers.push(customer);
        
        //adding payment to the register
        arr[0]+=p1;
        arr[1]+=p5;
        arr[2]+=p10;
        arr[3]+=p20;
        
        if(make_change(payment, change, arr)){
            iceCream -= n;
            customer += 1;
        }else{
            cout<<"We do not have change sorry"<<endl;
            //if change could not be given, give the customer their money back: take aay payment from register
            arr[0]-=p1;
            arr[1]-=p5;
            arr[2]-=p10;
            arr[3]-=p20;
            customers.pop();
            getsChange=false;
        }
        
    }
    if(getsChange){
        cout<<"Every customer recieved change."<<endl;
    } else {
        cout<<"Changes could not be given for one or more customers"<<endl;
    }
    
    cout<<"Money with Xavier : "<<total_revenue(arr)<<endl;
    cout<<"sold average : "<<sold_product_avg(iceCream, customers)<<endl;
    cout<<"revenue average : "<<revenue_average(customers, arr)<<endl;
    
    return 0;
}

#include <bits/stdc++.h> 
using namespace std; 
  
struct Item 
{ 
    float weight; 
    int value;
}; 
  
struct Node 
{ 
    int profit;
    queue<int> track;
    float weight; 
};

bool search(queue<int> Q, int x){
    queue<int> temp = Q;
    while(!temp.empty()){
        int y = temp.front();
        if(y==x){
            return true;
        }
        temp.pop();
    }
    return false;
}

Node knapsack(int W, Item arr[], int n) 
{ 
    int maxprofit = 0;
    Node maxNode;
    queue<Node> Q;

    Node v;
    v.profit = 0;
    v.weight = 0;
    v.track.push(-1);
    Q.push(v);

    while (!Q.empty()) 
    {
        Node v = Q.front();
        Q.pop();
        for(int i=0;i<n;i++){
            if(!search(v.track,i)){
                Node u;
                u.profit = v.profit + arr[i].value;
                u.weight = v.weight + arr[i].weight;
                u.track = v.track;
                u.track.push(i);
                if(u.weight<=W){
                    Q.push(u);
                    if(u.profit>maxprofit){
                        maxprofit = u.profit;
                        maxNode = u;
                    }
                }
            }
        }        
    }
    return maxNode;
}

int main() 
{ 
    int n;
    int W;  
    cout<<"      Welcome to knapsack problem!     "<<endl;
    cout<<"Enter the total no. of items: ";
    cin>>n;
    Item arr[n];
    for(int i=0;i<n;i++){
        cout<<"Item "<<i<<" -> "<<endl;
        cout<<"   Weight: ";
        cin >> arr[i].weight;
        cout<<"   Value: ";
        cin >> arr[i].value;
    }
    cout<<"Maximum weight knapsack can carry: ";
    cin>>W;   
    
    Node result = knapsack(W,arr,n); 
    queue<int> track = result.track;
    cout<<"Sequence of selection of items is ";
    while(!track.empty()){
        if(track.front()==-1){
            track.pop();
            continue;
        }
        cout<<" -> "<<track.front();
        track.pop();
    }
    cout<<endl;
    cout<<"The maximum profit can be "<<result.profit<<endl;
    return 0; 
}

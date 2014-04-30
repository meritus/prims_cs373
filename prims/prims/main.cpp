//
//  main.cpp
//  prims
//
//  Created by Edison Liu on 4/29/14.
//  Copyright (c) 2014 ___CS373___. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;

struct node{
    int name;
    int weight;
};

//used to sort the heap
bool compare(const node *lhs, const node *rhs) {
    return lhs->weight>rhs->weight;
}


int *array_maker(int a, int b, int c, int d);
int *prims(int num_nodes, int start_node, int **adj);

int main(int argc, const char * argv[])
{
    node one;
    node two;
    node three;
    one.name=1;
    one.weight=10;
    two.name=2;
    two.weight=12;
    three.name=3;
    three.weight=6;
    
    vector<node> pq;
    pq.push_back(two);
    pq.push_back(one);
    pq.push_back(three);
    //make_heap(pq.begin(), pq.end(), &compare);
    
    //cout<<pq.front().name<<endl;
    
    int **adj_mat = new int*[4];
    adj_mat[0]=array_maker(0, 7, -1, 15);
    adj_mat[1]=array_maker(7,0,9,-1);
    adj_mat[2]=array_maker(-1, 9, 0, -1);
    adj_mat[3]=array_maker(15, -1, -1, 0);
    
    /*
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
            cout<<adj_mat[i][j]<<" ";
        cout<<endl;
    }
    */
    
    prims(4,0,adj_mat);
}

int *array_maker(int a, int b, int c, int d){
    int *ret = new int[4];
    ret[0]=a;
    ret[1]=b;
    ret[2]=c;
    ret[3]=d;
    return ret;
}


int *prims(int num_nodes, int start_node, int **adj){
    vector<node*> pq;
    int answer[num_nodes];
    node nodes_arr[num_nodes];
    bool in_pq[num_nodes];
    //initalize the nodes and put into priorityqueue
    for(int i=0;i<num_nodes;i++){
        nodes_arr[i].name=i;
        nodes_arr[i].weight=INT_MAX;
        answer[i]=0;
        if(i==start_node)
            nodes_arr[i].weight=0;
        pq.push_back(&nodes_arr[i]);//put node onto vector
        make_heap(pq.begin(), pq.end(), &compare); //generate heap
        in_pq[i]=true;
    }
    while (pq.size()>0){
        node *u=pq.front(); //get min items
        //rearrage the elementes to heap is shortened by 1, min item moves to the end of heap
        pop_heap(pq.begin(), pq.end(), &compare);
        pq.pop_back(); //pop it off
        in_pq[u->name]=false;
        cout<<"current popped: "<<"index: "<<u->name<<endl;
        for(int i=0;i<num_nodes;i++){ //so that it loops through all the possible adj nodes
            if(adj[u->name][i]==-1) continue; //means that it's not adj
            node v;
            v.name=i;
            v.weight=adj[u->name][i];
            if(in_pq[i] && adj[u->name][i]<nodes_arr[i].weight){ //if in queue weight less than key
                nodes_arr[i].weight=adj[u->name][i]; //decrease key
                make_heap(pq.begin(), pq.end(), &compare); //generate heap
                answer[i]=adj[u->name][i]; //the pi thingy
            }
        }
    }
    for(int i=0;i<num_nodes;i++){
        cout<<"index: "<<i<<", minimum: "<<answer[i]<<endl;
    }
    return 0;
}


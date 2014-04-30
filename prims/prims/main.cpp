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
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct Node{
    int name;
    int weight;
};

//used to sort the heap
bool compare(const Node *lhs, const Node *rhs) {
    return lhs->weight>rhs->weight;
}


int *array_maker(int a, int b, int c, int d);
int *prims(int num_nodes, int start_node, int **adj);
int** createUserGraph();
void printGraph(int** graph);

int main(int argc, const char * argv[])
{
    int** graph;
    int node;
    //if user entered a file than use that file
	if(argv[1])
	{
		
		string inputFile;
		ifstream infile(argv[1]);
		//check if file is there
		if(!infile)
		{
			cout << "Could not open input file" << endl;
			exit(0);
		}
		//opens input file and stores it in varible input
		if(infile.is_open())
		{
			infile >> inputFile;
		}
		else
		{
			exit(0);
		}
		//convert first line to int because that line determines number of nodes
		node = atoi( inputFile.c_str());
		//creates 2 dimensionanl array with row and cols eqaul to node
		graph = new int*[node];
        for(int i = 0; i < node; i++)
		{
            graph[i] = new int[node];
			for(int j = 0; j < node; j++)
            {
                graph[i][j] = (i+j);
            }
        }
		int temp = -1;
		// inserst into nodes and column form mteh file
		for(int i = 0; i<node; i++)
        {
			//set inputfile to next line
			infile >> inputFile;
			int temp2 = 0;
			for(int j = 0; j<node; j++)
            {
                //checks current line until - whic means new number thatn everything before that is value sotred
                string tempstr;
                int x = temp2;
                while( x < inputFile.length())
                {
                    if(inputFile[x] != ',')
                    {
                        tempstr += inputFile[x];
                    }
                    else
                    {
                        x = inputFile.length()+1;
                    }
                    x++;
                    temp2++;
                }
                //convert to a int
                temp = atoi( tempstr.c_str());
                //if the value is zero set it to 1 that means it is infinty
                //else set it to the value indicated by user
                //if the the value is zero than we dont have direct acces to that node form this spot whci means we dont know how far away its so its infinty
                //-1=infinty
                
                graph[i][j] = temp;
                //temp = -1;
            }
        }
		//close the file
		infile.close();
	}
	else
	{
		//printGraph(createUserGraph());
	}
    
    prims(node,0,graph);
}

void printGraph(int** graph)
{
	for (int x=0; x<7; x++)
	{
        
        for (int y=0; y<7; y++)
        {
            
	        cout<<graph[x][y] <<" ";
        }
        cout<<endl;
	}
	
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
    vector<Node*> pq;
    int answer[num_nodes];
    Node nodes_arr[num_nodes];
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
        Node *u=pq.front(); //get min items
        //rearrage the elementes to heap is shortened by 1, min item moves to the end of heap
        pop_heap(pq.begin(), pq.end(), &compare);
        pq.pop_back(); //pop it off
        in_pq[u->name]=false;
        cout<<"current popped: "<<"index: "<<u->name<<endl;
        for(int i=0;i<num_nodes;i++){ //so that it loops through all the possible adj nodes
            if(adj[u->name][i]==-1) continue; //means that it's not adj
            Node v;
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

//if return -1 it failed 0 passed
int** createUserGraph()
{
	int node = -1;
	//ask for the amoutn of nodes from user
	//has to be postive non zero number
	while(node <= 0)
	{
		cout << "Enter (positve non-zero) amount of nodes for the graph: ";
		cin>>node;
	}
	//creates 2 dimensional array node by node
	int** graph = new int*[node];
    for(int i = 0; i < node; i++)
	{
        graph[i] = new int[node];
        for(int j = 0; j < node; j++)
        {
            graph[i][j] = (i+j);
        }
    }
	int temp = -1;
	cout<< "Enter the Adjency matrix values"<<endl;
	for(int i = 0; i<node; i++)
    {
		for(int j = 0; j<node; j++)
        {
            //get value from user
            //test so user will input a positve vaule if negative or does not input a value than asks again till correct
            
            cout<<"Enter a postive value for row "<< (i+1) << " col " << (j+1) << endl;
            cin >>temp;
            
            //if the value is zero set it to 1 that means it is infinty
            //else set it to the value indicated by user
            //if the the value is zero than we dont have direct acces to that node form this spot whci means we dont know how far away its so its infinty
            //-1=infinty
            
            graph[i][j] = temp;
            
			
        }
    }
	//return the graph
	return graph;
}



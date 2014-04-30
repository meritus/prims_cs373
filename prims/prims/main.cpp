//
//  main.cpp
//  prims
//
//  Created by Edison Liu on 4/29/14.
//  Copyright (c) 2014 ___CS373___. All rights reserved.
//

#include <iostream>

using namespace std;


//create a grpah of nodes with distance between adjecnt nodes
//compute the prim algorithm on the graph and print out result



int main(int argc, char* argv[])
{

//if users typed a a file name than use it else use ask user for input
	cout<<"hello world"<<endl;
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
		int node = atoi( inputFile.c_str());
		//creates 2 dimensionanl array with row and cols eqaul to node
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
						if(inputFile[x] != '-')
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
					if(temp == 0)
					{
						graph[i][j] = INT_MAX;
					}
					else
					{
						graph[i][j] = temp;
					}
					temp = -1;
				}
			}
		//close the file
		infile.close();
		printGraph(graph);
	}
	else
	{
		printGraph(createUserGraph());
	}
	
	return 0;
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
				if(temp == 0)
				{
					graph[i][j] = INT_MAX;
				}
				else
				{
					graph[i][j] = temp;
				}
			
			}
		}	
	//return the graph
	return graph;
}

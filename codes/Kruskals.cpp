/*
	Notes:
	1- It used edge list 
	2- Sort all edges according to the weights
	3- Then start selecting edges 1 by 1 
	4- Only select an edge if it doesnt form a cycle 
    6- Time Complexity O(ElogV)
	7- Space Complexity O(V)
    5-  Purpose: Finds the Minimum Spanning Tree (MST) in an undirected, weighted graph. The MST connects all vertices
       with the minimum possible total edge weight, without forming cycles.

*/ 




class Solution
{
	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
 
    static bool comp(vector<int>&a, vector<int>&b)
	{
	    return a[2] < b[2];
	}
	
	int findparent(int n, vector<int>&parent)
	{
	    if(parent[n] == n)
	      return n;
	    int x = findparent(parent[n], parent);
	    return x;
	}
	
    int spanningTree(int v, vector<vector<int>> adj[])
    {
        
         vector<vector<int>>arr;
        for(int i=0; i<v; i++)
        {
            for(x: adj[i])
            {
                int neibh = x[0];
                int wt = x[1];
                
                vector<int>temp;
                temp.push_back(i);
                temp.push_back(neibh);
                temp.push_back(wt);
                arr.push_back(temp);
            }
        }
        
        sort(arr.begin(), arr.end(), comp);
        
        vector<int>parent(v, 0);
        for(int i=0; i<v; i++)
           parent[i] = i;
           
        int sum = 0;
        for(int i=0; i<arr.size(); i++)
        {
            int x = findparent(arr[i][0], parent);
            int y = findparent(arr[i][1], parent);
            if(x != y)
            {
                sum = sum + arr[i][2];
                parent[max(x, y)] = min(x, y);
            }
        }
        return sum;
    }
    
    
};

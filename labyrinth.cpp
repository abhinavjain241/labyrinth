/* GSoC-2015 JdeRobot- Universidad Rey Juan Carlos
C++ Challenge

Submission by Abhinav Jain, abhinavjain241@gmail.com | www.github.com/abhinavjain241
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#define pb(X) push_back(X)
#define mp make_pair
#define PT pair<int,int>

using namespace std;

//Make a structure path_ which will store starting coordinates and length of the path
typedef struct path_{
	int start_i, start_j;
	int length;
}path;

//Compare function for std::sort function later used
bool comp(path a, path b) { return a.length < b.length; }

int main()
{
	ifstream file("schema.txt");	
	string a;
	vector<string> matrix;
	while(std::getline(file, a))
	{
		matrix.pb(a);
	}
	vector<string> final(matrix);
	int id = 1, i,j,k,l, r = matrix.size(), c = matrix[0].length();
	vector<path> paths;
	vector<vector<int> > visited(r,vector<int>(c,0));
	//BFS , hence queue
	queue<PT> open_list;  
	//Using Breadth First Search
	for(i = 0; i < r ; i++)
		{
			for(j = 0 ; j < c; j++)
			{
				if(matrix[i][j]=='#'||visited[i][j]>0)
					continue;
				open_list.push(mp(i,j));
				int len = 0;
				while(!open_list.empty())
				{
					PT top = open_list.front();
					open_list.pop();
					visited[top.first][top.second] = id;
					len++;
					for(k=top.first-1;k<=top.first+1;k++)
						{
							for(l=top.second-1;l<=top.second+1;l++)
							{
								if((k==top.first-1&&l==top.second-1)||(k==top.first-1&&l==top.second+1)||(k==top.first+1&&l==top.second+1)||(k==top.first+1&&l==top.second-1))
									continue; 
								if(k<0||l<0||k>r-1||l>c-1)
									continue;
								if(matrix[k][l]=='#'||visited[k][l]>0)
									continue;
								PT next = mp(k,l);
								visited[k][l] = id;
								open_list.push(next);
							}
						}
				}
				path nextpath = {i,j,len};
				paths.pb(nextpath);
				id++;
			}
		}
	std::sort(paths.begin(),paths.end(),comp);
	//Make the visited array all zeroes again
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			visited[i][j]=0;
	char cnt = '0';
	//Push the starting position of the path of maximum length
	open_list.push(mp(paths[paths.size()-1].start_i,paths[paths.size()-1].start_j));
	final[paths[paths.size()-1].start_i].replace(paths[paths.size()-1].start_j,1,1,cnt);	
	//Again applying breadth first search to only the path with maximum length	
	while(!open_list.empty())
	{
		PT top = open_list.front();
		open_list.pop();
		visited[top.first][top.second] = id;
		for(k=top.first-1;k<=top.first+1;k++)
			{
				for(l=top.second-1;l<=top.second+1;l++)
				{
					if((k==top.first-1&&l==top.second-1)||(k==top.first-1&&l==top.second+1)||(k==top.first+1&&l==top.second+1)||(k==top.first+1&&l==top.second-1))
						continue; 
					if(k<0||l<0||k>r-1||l>c-1)
						continue;
					if(matrix[k][l]=='#'||visited[k][l]>0)
						continue;
					PT next = mp(k,l);
					cnt++;
					final[k].replace(l,1,1,cnt);
					visited[k][l] = id;
					open_list.push(next);
				}
			}
	}
	//Display Path Length
	cout << ++cnt << endl;
	for(i = 0;i < r; i++)
		{
			for(j = 0; j < c; j++)
				cout << final[i][j];
			cout << endl;
		}
	return 0;
}

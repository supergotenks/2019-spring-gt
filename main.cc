/* 
  ///////////////////////////////////  Your main program goes here
*/
#include <iostream>
#include <vector>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;




int Vertex_Number_getting(vector<Vertex*> node_vlist, string vertex) ;
int distance_getting_fromBFS(vector<Vertex*> node_vlist,string start_vertex, string end_vertex);
vector<Vertex*> path_getting_fromBFS(vector<Vertex*> node_vlist,string start_vertex, string end_vertex);


// create NetworkManager first
NetworkManager *nm = new NetworkManager();

int main(int argc, char** argv){

    /* start your program */

    //read the graph/////
    nm->interpret("topo.txt");
    /////calculate the degree of each vertex  
    Vertex *node = nm->get_all_nodes();
    vector<Vertex *> node_vlist;
    vector<Vertex *> odd_vertex;
    int i;
    int j;
    int numberofvertex;
    
    
    while(node !=0)
    {
      node_vlist.push_back(node);
      node=node->next;
    }
      
    
    numberofvertex = node_vlist.size();
    
    int degree[numberofvertex];
    for(i=0;i<numberofvertex;i++)
      degree[i]=0;
      
    for(i=0;i<numberofvertex;i++){
      for(j=0;j<numberofvertex;j++){
        if(!(nm->connected(node_vlist[i]->name,node_vlist[j]->name))==1){
          degree[i]=degree[i]+1;
      
          
        }
        
      }
    }
       
    for(i=0;i<numberofvertex;i++){
      if(degree[i]%2==1){
        odd_vertex.push_back(node_vlist[i]);
      }    
    }
      
   //////////////////////////////connect two odd_vertex
  /* 
    for(i=0;i<odd_vertex.size();i+=2)
    nm->connect(odd_vertex[i+1]->name,odd_vertex[i]->name);
    
  */  
  
/////////////using BFS to find the shortest distance of two point
int distance_from_start_to_end;
 distance_from_start_to_end = distance_getting_fromBFS(node_vlist,node_vlist[0]->name,node_vlist[5]->name);
 cout<<"distance_from_start_to_end:"<<distance_from_start_to_end<<endl; 

 
 
 
/////////////find the shortest path 
vector<Vertex*> path_from_start_to_end; 
 path_from_start_to_end = path_getting_fromBFS(node_vlist,node_vlist[2]->name,node_vlist[0]->name);
cout<<"path_from_start_to_end:"<<path_from_start_to_end.at(0)->name<<endl;
cout<<"path_from_start_to_end:"<<path_from_start_to_end.at(1)->name<<endl;
cout<<"path_from_start_to_end:"<<path_from_start_to_end.at(2)->name<<endl;


  
     ///////////////////////odd_vertex debug check
   /*
    cout<<degree[0]<<endl;
    cout<<degree[1]<<endl;
    cout<<degree[2]<<endl;
    cout<<degree[3]<<endl;
    cout<<degree[4]<<endl;
    
    cout<<odd_vertex[0]->name<<endl;
    cout<<odd_vertex[1]->name<<endl;
    cout<<odd_vertex[2]->name<<endl;
    cout<<odd_vertex[3]->name<<endl;
    cout<<odd_vertex[4]->name<<endl;
    */
 
    
   /////////////////////////////Euler circuit 
    vector<Vertex *> tempPath;
    vector<Vertex *> finalpath;
    
    int h=0;
    int q=0;
    int t;
    //nm->print_all_e();
    while(h<numberofvertex){
    
      for(t=0;t<numberofvertex;t++){
        if(nm->connected(node_vlist[h]->name,node_vlist[t]->name)==0){
          cout<<"t in q=0:"<<t<<endl;
          tempPath.push_back(node_vlist[h]);
          nm->linkdown(node_vlist[h],node_vlist[t]);
          
        break;
        }
        else if(nm->elist==0){
          tempPath.push_back(node_vlist[h]);
          q=2;
        break;
        }
        else if(t==numberofvertex-1){
          tempPath.pop_back();
          finalpath.push_back(node_vlist[h]);
          q=1;
        break;
        }  
      }  
    cout<<"check the situation"<<q<<endl;  
    if(q==1){
      h= tempPath.size();
    }  
    else if(q==2){
      break;
    }
    else{
     
      h=t; 
    cout<<"check the next head:"<<h<<endl;  
    }
 
  
  }
  
  for(int v=tempPath.size();v>0;v--){
    finalpath.push_back(tempPath.back());
    tempPath.pop_back();
  }  
  //////////////////////// debug for Euler circuit
 /* cout<<"finalpath:"<<finalpath.at(0)->name<<endl;
  cout<<finalpath.at(1)->name<<endl;
  cout<<finalpath.at(2)->name<<endl;
  cout<<finalpath.at(3)->name<<endl;
  cout<<finalpath.at(4)->name<<endl;
  cout<<finalpath.at(5)->name<<endl;
  cout<<finalpath.at(6)->name<<endl;
  cout<<finalpath.at(7)->name<<endl;
  cout<<finalpath.at(8)->name<<endl;
*/
  
  
    


    
    
    
    /////////////////////////////////

    return 0;
}
/////////////////transfer from vertex name to vertex number
int Vertex_Number_getting( vector<Vertex*> node_vlist, string vertex){
  int Vertex_Number=0;
  while(vertex != node_vlist[Vertex_Number]->name)
    Vertex_Number++;
  return Vertex_Number;
}  
  
 /////////////////////////////BFS algo for distance
 int distance_getting_fromBFS(vector<Vertex*> node_vlist,string start_vertex, string end_vertex){
   vector<Vertex *> queue;
   int numberofvertex = node_vlist.size();
   int distance[numberofvertex];
   int color[numberofvertex];
   int predecessor[numberofvertex];
   int i;
   int j;
   
   
    for( i=0;i<numberofvertex;i++){
      color[i]=0;
      predecessor[i]=-1;
      distance[i]= numberofvertex +1;
    } 
    int start_vertex_number;
    start_vertex_number= Vertex_Number_getting(node_vlist,start_vertex);
    i = start_vertex_number;
    cout<<"i="<<i<<endl;  
    for( j=0;j<numberofvertex;j++){
      if(color[i]==0){
        color[i] = 1;
        distance[i]=0;
        predecessor[i]=-1;
        queue.push_back(node_vlist[i]);

        while(!queue.empty()){
        int u;
        u= Vertex_Number_getting(node_vlist,queue.front()->name);
        int itr;  
          for(itr=0;itr<numberofvertex;itr++){
            if(nm->connected(node_vlist[u]->name,node_vlist[itr]->name)==0){
              cout<<"u="<<u<<"and itr="<<itr<<endl;
              if(color[itr]==0){
                color[itr]=1;
                distance[itr]=distance[u]+1;
                predecessor[itr] =u;
                queue.push_back(node_vlist[itr]);
              }
            }  
          }
          queue.erase(queue.begin());  
          color[u]=2;
        }
      }  
      i=j;
      cout<<"I="<<i<<endl;
    }   

  for(int i = 0 ; i < numberofvertex ; i++ )
    cout<<"Distance betweem Vertex \""<<start_vertex<<"\" and Vertex \""<<node_vlist[i]->name<<"\" is "<<distance[i]<<endl;
    
  int End_Vertex_Number ;
  End_Vertex_Number = Vertex_Number_getting(node_vlist,end_vertex ) ;
  return distance[End_Vertex_Number] ;
}


/////////////////////////////BFS algo for path
vector<Vertex*> path_getting_fromBFS(vector<Vertex*> node_vlist,string start_vertex, string end_vertex){
   vector<Vertex *> queue;
   int numberofvertex = node_vlist.size();
   int distance[numberofvertex];
   int color[numberofvertex];
   int predecessor[numberofvertex];
   int i;
   int j;
   vector<Vertex*> record_path; 
   
   
    for( i=0;i<numberofvertex;i++){
      color[i]=0;
      predecessor[i]=-1;
      distance[i]= numberofvertex +1;
    } 
    int start_vertex_number;
    start_vertex_number= Vertex_Number_getting(node_vlist,start_vertex);
    i = start_vertex_number;
    cout<<"i="<<i<<endl;  
    for( j=0;j<numberofvertex;j++){
      if(color[i]==0){
        color[i] = 1;
        distance[i]=0;
        predecessor[i]=-1;
        queue.push_back(node_vlist[i]);

        while(!queue.empty()){
        int u;
        u= Vertex_Number_getting(node_vlist,queue.front()->name);
        int itr;  
          for(itr=0;itr<numberofvertex;itr++){
            if(nm->connected(node_vlist[u]->name,node_vlist[itr]->name)==0){
              if(color[itr]==0){
                color[itr]=1;
                distance[itr]=distance[u]+1;
                predecessor[itr] =u;
                queue.push_back(node_vlist[itr]);
              }
            }  
          }
          queue.erase(queue.begin());  
          color[u]=2;
        }
      }  
      i=j;
  
    }
  int End_Vertex_Number ;
  End_Vertex_Number = Vertex_Number_getting(node_vlist,end_vertex );  
  record_path.push_back(node_vlist[End_Vertex_Number]);
  i= End_Vertex_Number;
  while(i>-1){
    j=predecessor[i];
    record_path.push_back(node_vlist[j]);
    i=j;
  }  
  return record_path;
}

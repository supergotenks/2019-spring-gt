/* 
  ///////////////////////////////////  Your main program goes here
*/
#include <iostream>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"

using namespace std;

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
   for(i=0;i<odd_vertex.size();i+=2)
    nm->connect(odd_vertex[i+1]->name,odd_vertex[i]->name);
    
    
    
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
  cout<<"finalpath:"<<finalpath.at(0)->name<<endl;
  cout<<finalpath.at(1)->name<<endl;
  cout<<finalpath.at(2)->name<<endl;
  cout<<finalpath.at(3)->name<<endl;
  cout<<finalpath.at(4)->name<<endl;
  cout<<finalpath.at(5)->name<<endl;
  cout<<finalpath.at(6)->name<<endl;
  cout<<finalpath.at(7)->name<<endl;
  cout<<finalpath.at(8)->name<<endl;

  
  
    
    ///////////////////////debug for odd_vertex
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

    
    
    
    /////////////////////////////////

    return 0;
}
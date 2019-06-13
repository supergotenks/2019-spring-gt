# Graph-Theory-Project-Template
Project template of course - Graph Theory (EE6622E) in National Cheng Kung University.

## How to run

### Linux

```
# clone first (with submodule)
$ git clone --recursive https://github.com/<your-name>/Graph-Theory-Project-Template.git
# (Option) build libfakemn.a
$ cd fake-mininet && make lib && cd .. && cp fake-mininet/libfakemn.a .
# build
$ make 
# run 
$ ./main.out
```

### Windows

If your PC is `window 10`, then you need to install the related dependencies. For example, if you are using `VSCode` as your IDE, then you can install the plugin of `C/C++` in your vscode. And then install the following programs/packages:
* mingw
* git

Step by step to create `c_cpp_properties.json` and `tasks.json`:
* `Ctrl+Shift+P` -> `C/C++: Edit Configuration` -> then you have the first JSON file.
* `Ctrl+Shift+P` -> `Tasks: Configure Task` -> then you have the second JSON file.

Here is the setting of `c_cpp_properties.json` and `tasks.json`:
```json
# c_cpp_properties.json (If your mingw installed in another folder, then you have to change the value in `compilterPath`)
{
    "configurations": [
        {
            "name": "MinGW",
            "intelliSenseMode": "gcc-x64",
            "includePath": [
                "$(workspaceFolder)"
            ],
            "compilerPath": "C:/mingw/bin/gcc.exe",
            "cStandard": "c11",
            "cppStandard": "c++11"
        }
    ],
    "version": 4
}

# tasks.json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-g",
                "main.cc",
                "-o",
                "main.exe",
                "-Ifake-mininet/lib",
                "-g3",
                "-L.",
                "-lfakemn_win",
                "-std=c++11"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

After all the settings have been done, we can press `Ctrl+Shift+B` to run the task, if your settings is correct, then there will have an executable file which named `main.exe`.

Or you can just [DOWNLOAD a pre-built VM images](http://gofile.me/39GpL/XU5tznyO6) provided by TA.

> [Guide of environment setting](https://hackmd.io/-5WZQC-1QqOeV3KUX65tEw?view) on Windows.

## TODO - Your descriptions about solutions/algorithms/results
### Chinese Postman Problem
#### Abstract
A mail carrier must traverse all edges in a road network, starting and ending at the Post 
office

The edges have nonnegative weights representing distance or time.
We seek a closed walk of minimum total lenth that uses all the edges.

keypoints:
  If every vertex is even, then the graph is Eulerian and the answer is the sum of the edge 
  weights.
  Otherwise,we must repeat edges.
and we can find the ideal solution is the Euler path

#### algorithms
first,I find every degree of all vertex and identify which vertex has odd degree.
Put them into odd_vertex vector.
If the number of the odd_vertex size is 0,the graph is a Euler circuit
We can find the Euler path and the finalpath is the answer
if the number of the odd_vertex size is 2 or bigger than 2,it can be consider two situation

1.These two vertex are connected.
  Directly build the connection between these two vertex.
2.These two vertex are not connected.
  Find the shortest path between these two vertex, and connect each vertex in shortest path.
this program can find the bestsolution under the condition that the number of vertex with an odd degree is 2
and not finish bigger than two yet.

use BFS to find the shortest path and record the path of two odd_vertex
since all the weight is 1,we can use BFS instead of Dijkstra's algorithm to find the shortest path.

To find the Euler path of the graph
I use two vector
one is tempPath and the other is finalpath.
first, I check which point is connected to start point
and push the head which is the start point into tempPath.
and delete the edge between head and tail
second,use the tail to be the next head and repeat the first step
if can't find any edge,push the last vector of tempPath to finalpath
and delete the last vector of tempPath
after this it can find other path if the last vector of tempPath have other connection
repeat the first step until all edge is deleted

#### program
Vertex_Number_getting is transfer the node to a number
distance_getting_fromBFS is calculate the shortest distance of two vertex
path_getting_fromBFS is record the shortest path

#### file name identification
1.main.cc:The main program.

2.topo.txt:The input graph.

5.Euler_Path.dot:The dot file of result.

6.Euler_Path.png:The png file of result.

7.Euler_Path.txt:The txt file of result.

  
  

# Chews-Triangulation

It was originally an "Attempt Towards Computing Constrained Delaunay Triangulation (CDT) in expected linear time".

This internship intended to implement an alternative algorithm to that of Jonathan Richard Shewchuk’s––”Fast segment insertion and incremental construction of constrained Delaunay triangulations''. This work was inspired by Kolja Junginger’s and Evanthia Papadopoulou’s work on “Deletion in abstract voronoi diagram and its application to CDT”, which solved a century old problem in computational geometry: deletion of a site in an abstract voronoi diagram in expected linear time. A trivial solution to the problem would involve removing a site and recomputing the Voronoi diagram, however the aforementioned paper only considers and uses the arcs of the voronoi region of the site being deleted to construct a voronoi-like diagram within the region. So the algorithm does not exactly compute an abstract voronoi diagram in the affected region but an abstract voronoi-like diagram, which is a relaxed version of an abstract voronoi diagram. The algorithm starts off by removing the arcs of the affected region, which are representatives for the sites, until 3 arcs remain. The 3 arcs are connected using the auxiliary arcs and the voronoi-like diagram of the arcs are then computed. The insertion of the arcs is then randomized which eventually results in a complete abstract voronoi-like diagram in expected linear time. This internship thus attempted to update a CDT after segment insertion in expected linear time by computing the dual of the abstract voronoi-like diagram in the affected voronoi region after the deletion of line segment. Significant portion of the time was spent understanding the 2 papers, analyzing various abstract voronoi diagrams using Ipe and constructing & understanding the dual algorithm. Due to the nature of the work, robust inCircle tests and other predicates were required hence CGAL was used for this task. A lot of time was also spent on learning CGAL and experimenting with various in-built data structures and classes. Ultimately I ended up implementing a standard C++ code using CGAL functionalities. Due to shortage of time and difficulty of the task, I got to the point of implementing and visualizing Chews algorithm, which is a portion of the entire algorithm. The difficulties that were encountered in the task were: deleting and traversing triangles for concave polygons and building a well designed Doubly connected edge list.


# Preliminaries
 - Install CGAL.
 - Navigate to examples/ and insert Chews-Triangulation.
 - Run ```./call_creator.sh```
 - Open CMakeLists.txt.
 - Update ```find_package... ```to ```find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5).```
 - After the line of hashtags, insert 
```
add_executable( chews  chews.cpp )
add_to_cached_list( CGAL_EXECUTABLE_TARGETS chews )
if(CGAL_Qt5_FOUND)
target_link_libraries(chews PUBLIC CGAL::CGAL_Basic_viewer)
endif()
target_link_libraries(chews PRIVATE CGAL::CGAL )
```
 -  Run ```mkdir build```
 - Run ```cmake -DCGAL_DIR=XXXXXX -DQt5_DIR=XXXXX -DCMAKE_BUILD_TYPE=Release . -B build```
 -  Run ```./builder.sh```
 - Run executable ```./build/chews```
 

The file explorer is accessible using the button in left corner of the navigation bar. You can create a new file by clicking the **New file** button in the file explorer. You can also create folders by clicking the **New folder** button.

## Changing point configurations
In the main function of Chews.cpp the point configurations can be easily modified.

## Output
![Polygon1](/img/polygon1.png?raw=true "polygon1")
![Polygon2](/img/polygon2.png?raw=true "polygon2")
![Polygon3](/img/polygon3.png?raw=true "polygon3")
![Polygon4](/img/polygon4.png?raw=true "polygon4")



## Additional Output for verifying Delaunay property

After the rendering is closed, the terminal will show which vertices lie on (0) the the circle passing throught the triangle vertices and which ones lie outside (-1). A small snapshot of the output corresponding to polygon 3 was taken. It shows that for a specific triangle, 2 points lie outside of the circle passing through vertices of triangle and the other 3 points of the polygon i.e. the triangle vertices themselves lie on the the circle.
![verify](/img/verify.png?raw=true "verify")

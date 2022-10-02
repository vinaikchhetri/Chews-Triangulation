# Chews-Triangulation

It was originally an "Attempt Towards Computing Constrained Delaunay Triangulation (CDT) in expected linear time".


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

DataStructure
=============

一些数据结构练习，目前有AvlTree与Octree
-----------------------------------------------

###Octree

Octree的基本数据结构包含在Octree/lib里面，是[GTEngine](http://www.geometrictools.com/) 里面的内容		
STLReader用于读取STL格式的文件<br>
demo.cpp里包含应用Octree的API与时间比较，用于比较利用Octree求交与Brute force的差别<br>
下图是VS2013 debug模式下1条线段与69664个三角面片求交100次的时间比较<br>
![cmptime](https://github.com/THTBSE/DataStructure/blob/master/cmptime.jpg)<br>

###AvlTree
AvlTree的简单实现，用于删除不多的情形，使用lazy deletion
		
		

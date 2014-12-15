DataStructure
=============

数据结构的轮子，目前有AvlTree与Octree
-----------------------------------------------

###Octree

实现八叉树的基本数据结构(向量、矩阵、三角面片等)包含在Octree/lib，基于[GTEngine](http://www.geometrictools.com/)<br>    
STL格式文件的读取代码在STLReader中(只是为了测试八叉树，没有去除冗余)<br>
应用八叉树的API以及与Brute force时间比较在demo.cpp里<br>

######时间比较
VS2013 debug模式下1条线段与69664个三角面片求交100次的时间比较<br>
![debug](https://github.com/THTBSE/DataStructure/blob/master/debug_time.bmp)<br>

VS2013 release模式下1条线段与69664个三角面片求交100次的时间比较<br>
![release](https://github.com/THTBSE/DataStructure/blob/master/release_time.bmp)<br>

###AvlTree
AvlTree的简单实现，用于删除不多的情形，使用lazy deletion
		
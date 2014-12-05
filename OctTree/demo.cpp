#include "Octree.h"
#include <iostream>
#include <chrono>

extern void read_stl_file(const char *filename, std::vector<gte::Triangle3<double>>& TriList);
extern gte::AlignedBox3<double> GenerateAABB(const std::vector<gte::Triangle3<double>>& TriList);

//compare intersection query time of using Octree to Brute force method.
void time_test(const std::vector<gte::Segment3<double>>& segs, const TOctree& octree, const std::vector<gte::Triangle3<double>>& mesh)
{
	std::chrono::time_point<std::chrono::system_clock> octree_start, octree_end, brute_start, brute_end;

	gte::FIQuery<double, gte::Segment3<double>, gte::Triangle3<double>> fiq;
	double minDist = std::numeric_limits<double>::max();
	gte::Vector3<double> IntrPoint;

	brute_start = std::chrono::system_clock::now();
	for (const auto &seg : segs)
	{
		for (const auto &tri : mesh)
		{
			auto ret = fiq(seg, tri);
			if (ret.intersect)
			{
				double dist = gte::Length(ret.point - seg.p[0]);
				if (dist < minDist)
				{
					minDist = dist;
					IntrPoint = ret.point;
				}
			}
		}
	}
	brute_end = std::chrono::system_clock::now();

	octree_start = std::chrono::system_clock::now();
	TOctree::Result Result;
	for (const auto &seg : segs)
		Result = octree.IntrQuery(seg);
	octree_end = std::chrono::system_clock::now();

	

	std::chrono::duration<double> octree_clock, brute_clock;
	octree_clock = octree_end - octree_start;
	brute_clock = brute_end - brute_start;

	double octree_time = octree_clock.count();
	double brute_time = brute_clock.count();

	std::cout << "The intersection time by Octree is : " << octree_time << std::endl
		<< "The intersection point of Octree is :(" << Result.point[0] << ", " <<
		Result.point[1] << ", " << Result.point[2] << ")" << std::endl;

	std::cout << "The intersection time by Brute force is : " << brute_time << std::endl
		<< "The intersection point of Brute force is :(" << IntrPoint[0] << ", " <<
		IntrPoint[1] << ", " << IntrPoint[2] << ")" << std::endl;
}


int main()
{
	//Triangle List to store mesh facets
	std::vector<gte::Triangle3<double>> TriList;

	char *filename = "dragon.stl";
	read_stl_file(filename, TriList);

	//generate bounding box of triangle mesh
	auto aabb = GenerateAABB(TriList);

	//build Octree 
	TOctree octree(TriList, aabb, 8);

	//segment which need to query 
	gte::Segment3<double> seg(gte::Vector3<double>(-3.3, 2.3, 0.5), gte::Vector3<double>(100.0, 100.0, 100.0));

	std::vector<gte::Segment3<double>> segs;
	for (size_t i = 0; i < 100; ++i)
		segs.push_back(seg);

	time_test(segs, octree, TriList);

	//auto Result = octree.IntrQuery(seg);

	//if (Result.intersect)
	//{
	//	std::cout << "The nearest intersection of segment and triangle mesh is at point :(" <<
	//		Result.point[0] << ", " << Result.point[1] << ", " << Result.point[2] << ")" << std::endl;
	//}
	//else
	//{
	//	std::cout << "Non intersection of segment and triangle mesh" << std::endl;
	//}

	return 0;
}
#ifndef _FCL_OCTREE_H_
#define _FCL_OCTREE_H_
#include <vector>
#include <memory>
#include "../Mathematics/GteAlignedBox3.h"
#include "../Mathematics/GteTriangle3.h"
#include "../Mathematics/GteSegment3.h"

//pointer of a triangle
typedef std::shared_ptr<gte::Triangle3<double>> TriPtr;

class TOctreeNode
{
public:
	gte::AlignedBox3<double> aabb;
	std::shared_ptr<TOctreeNode> children[8];
	std::vector<TriPtr> objects;
};

class TOctree
{
public:
	TOctree(const std::vector <gte::Triangle3<double>>& TriList, 
		const gte::AlignedBox3<double>& aabb, int StopDepth);
	//only take nearest intersection point
	struct Result
	{
		Result() :intersect(false){}
		bool intersect;
		gte::Vector3<double> point;
	};

	Result IntrQuery(const gte::Segment3<double>& seg);
private:
	std::shared_ptr < TOctreeNode >
		BuildOctreeFromMesh(std::vector<TriPtr>& objects, const gte::AlignedBox3<double>& aabb,
		int stopDepth);
	std::shared_ptr<TOctreeNode> root;
};






#endif
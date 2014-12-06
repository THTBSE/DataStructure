#include "Octree.h"
#include <queue>
#include <unordered_set>
#include <map>
#include <algorithm>


typedef gte::Vector3<double> GVec3;
typedef gte::Segment3<double> GSeg3;
typedef std::shared_ptr<TOctreeNode> TreeNodePtr;
static gte::Segment3<double> IntrSeg;

//Getting Cube by it's center and extent
static inline void GetCubeFromCenter(gte::Vector3<double>& center, double extent, gte::AlignedBox3<double>& cube)
{
	double dist = 0.5 * sqrt(3.0) * extent;
	auto vec = dist * gte::Vector3<double>(1.0, 1.0, 1.0);
	auto min = center - vec;
	auto max = center + vec;
	for (size_t i = 0; i < 3; ++i)
	{
		cube.min[i] = min[i];
		cube.max[i] = max[i];
	}
}

//split AxisAlignedBox aabb to eight boxes.
//aabb is a cube,so e1(aabb.max[0]-aabb.min[0]) == e2(aabb.max[1]-aabb.min[1])
// == e3(aabb.max[2]-aabb.min[2]) , we can use anyone extent.
static void SplitBoxToEight(const gte::AlignedBox3<double>& aabb, gte::AlignedBox3<double> boxes[8])
{
	double extent = aabb.max[0] - aabb.min[0];
	//dist equal to [sqrt(3)/4] * extent  ,it's the distance of center to other child-box's center
	double dist = 0.25 * sqrt(3.0) * extent;

	GVec3 basisVec[4] = { GVec3(1.0, 1.0, 1.0), GVec3(1.0, 1.0, -1.0), GVec3(1.0, -1.0, 1.0), GVec3(-1.0, 1.0, 1.0) };
	GVec3 center = GVec3(aabb.min[0], aabb.min[1], aabb.min[2]) + 2 * dist * GVec3(1.0, 1.0, 1.0);
	GVec3 subCenter[8];
	for (size_t i = 0; i < 4; ++i)
	{
		size_t idx = 2 * i;
		subCenter[idx] = center + dist * basisVec[i];
		subCenter[idx+1] = center - dist * basisVec[i];
	}

	double sub_extent = 0.5 * extent;
	for (size_t i = 0; i < 8; ++i)
	{
		GetCubeFromCenter(subCenter[i], sub_extent, boxes[i]);
	}
}

//function for testing triangle intersecting with cube
//triangle represent as three segments of it's edges.
static inline bool TriBoxIntrsect(const std::vector<gte::Segment3<double>>& tri, gte::AlignedBox3<double>& cube)
{
	gte::TIQuery<double, gte::Segment3<double>, gte::AlignedBox3<double>> tiq;
	for (const auto & seg : tri)
	{
		auto ret = tiq(seg, cube);
		if (ret.intersect)
			return true;
	}
	return false;
}


TOctree::TOctree(const std::vector <gte::Triangle3<double>>& TriList,
	const gte::AlignedBox3<double>& aabb, int StopDepth)
{
	std::vector<TriPtr> Mesh;
	for (const auto &tri : TriList)
	{
		Mesh.push_back(TriPtr(new gte::Triangle3<double>(tri)));
	}
	root = BuildOctreeFromMesh(Mesh, aabb, StopDepth);
	
}

std::shared_ptr<TOctreeNode>
TOctree::BuildOctreeFromMesh(std::vector<TriPtr>& objects, const gte::AlignedBox3<double>& aabb,
int stopDepth)
{
	// stop if reached certain depth or certain number of objects
	// the node is a leaf which contain objects.
	if (stopDepth < 0 || objects.size() < 10)
	{
		std::shared_ptr<TOctreeNode> leaf(new TOctreeNode());
		leaf->aabb = aabb;
		leaf->objects = objects;
		return leaf;
	}

	//split to 8 cubes
	gte::AlignedBox3<double> boxes[8];
	SplitBoxToEight(aabb, boxes);

	//crete a node
	std::shared_ptr<TOctreeNode> node(new TOctreeNode());
	node->aabb = aabb;
	
	std::vector<TriPtr> boxObjects[8];
	//for each triangle check intersection with 8 boxes
	for (const auto &tri : objects)
	{
		std::vector<GSeg3> segs{ GSeg3(tri->v[0], tri->v[1]), GSeg3(tri->v[1], tri->v[2]),
			GSeg3(tri->v[2], tri->v[0]) };
		for (size_t boxId = 0; boxId < 8; ++boxId)
		{
			if (TriBoxIntrsect(segs, boxes[boxId]))
				boxObjects[boxId].push_back(tri);
		}
	}

	//Loop through boxes and divide them more.
	for (size_t i = 0; i < 8; ++i)
	{
		if (!boxObjects[i].empty())
		{
			node->children[i] = BuildOctreeFromMesh(boxObjects[i], boxes[i], stopDepth - 1);
		}
	}

	return node;
}

TOctree::Result
TOctree::IntrQuery(const gte::Segment3<double>& seg) const
{
	Result ret;
	gte::TIQuery<double, gte::Segment3<double>, gte::AlignedBox3<double>> tiq;

	//if there is non intersection with boundingbox 
	auto TIRet = tiq(seg, root->aabb);
	if (!TIRet.intersect)
	{
		ret.intersect = false;
		return ret;
	}

	IntrSeg = seg;
	//compute the nearest intersection recursively
	IntrNode(root, ret);

	return ret;
}

gte::AlignedBox3<double>
GenerateAABB(const std::vector<gte::Triangle3<double>>& TriList)
{
	if (TriList.empty())
		return gte::AlignedBox3<double>();

	double minX = TriList[0].v[0][0], maxX = minX;
	double minY = TriList[0].v[0][1], maxY = minY;
	double minZ = TriList[0].v[0][2], maxZ = minZ;

	for (const auto& tri : TriList)
	{
		for (size_t i = 0; i < 3; i++)
		{
			if (tri.v[i][0] < minX)
				minX = tri.v[i][0];
			else if (tri.v[i][0] > maxX)
				maxX = tri.v[i][0];

			if (tri.v[i][1] < minY)
				minY = tri.v[i][1];
			else if (tri.v[i][1] > maxY)
				maxY = tri.v[i][1];

			if (tri.v[i][2] < minZ)
				minZ = tri.v[i][2];
			else if (tri.v[i][2] > maxZ)
				maxZ = tri.v[i][2];
		}
	}

	double min = std::min(minX, std::min(minY, minZ));
	double max = std::max(maxX, std::max(maxY, maxZ));

	return gte::AlignedBox3<double>(min, min, min, max, max, max);
}

void TOctree::IntrNode(std::shared_ptr<TOctreeNode> aabb, Result& result) const
{
	//if the intersection is found , do nothing
	if (result.intersect)
		return;
	
	//arrive the leaf 
	if (!aabb->objects.empty())
	{
		gte::FIQuery<double, gte::Segment3<double>, gte::Triangle3<double>> fiqTri;
		double minDist = std::numeric_limits<double>::max();
		GVec3 tempPoint;
		for (auto tri : aabb->objects)
		{
			auto triRet = fiqTri(IntrSeg, *tri);
			if (triRet.intersect)
			{
				double dist = gte::Length(triRet.point - IntrSeg.p[0]);
				if (dist < minDist)
				{
					minDist = dist;
					tempPoint = triRet.point;
				}
			}
		}
		if (minDist < std::numeric_limits<double>::max())
		{
			result.intersect = true;
			result.point = tempPoint;
		}
		return;
	}

	//if we don't arrive the leaf, going deep to find the intersection.
	//a segment may has two intersection with a box,we only use the nearest
	//one is enough for the algorithm.
	gte::FIQuery<double, gte::Segment3<double>, gte::AlignedBox3<double>> fiq;
	std::multimap<double, std::shared_ptr<TOctreeNode>> intrNode;
	for (int i = 0; i < 8; ++i)
	{
		if (aabb->children[i] != nullptr)
		{
			auto ret = fiq(IntrSeg, aabb->children[i]->aabb);
			if (ret.intersect)
			{
				double dist = gte::Length(ret.point[0] - IntrSeg.p[0]);
				intrNode.insert(std::make_pair(dist, aabb->children[i]));
			}
		}
	}

	for (auto iter = intrNode.begin(); iter != intrNode.end(); ++iter)
	{
		IntrNode(iter->second, result);
	}

}
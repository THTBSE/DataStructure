#include <sys/stat.h>
#include <stdio.h>
#include <map>
#include <vector>
#include "lib/GteTriangle3.h"

#define COND_READ(cond, where, len) do { if ((cond) && !fread((void *)&(where), (len), 1, f)) return false; } while (0)

class VertexComp;
typedef gte::Vector3<double> GVec3;
typedef std::map<GVec3, int, VertexComp> VertexMap;
typedef gte::Triangle3<double> GTri3;
bool read_stl(const char *filename, std::vector<GTri3>& TriList);
bool load_stl(const char *filename, std::vector<GTri3>& TriList);
bool is_text_file(const char *strFileName);

void read_stl_file(const char *filename, std::vector<GTri3>& TriList)
{
	if (is_text_file(filename))
		read_stl(filename, TriList);
	else
		load_stl(filename, TriList);
}

//test a STL file is binary format or Ascii format 
static bool is_text_file(const char* strFileName)
{
	if (strFileName == NULL) return false;
	struct stat f_stat;
	if (stat(strFileName, &f_stat) == -1)
	{
		return false;
	}
	long lngFilesize = 0;
	lngFilesize = (long)f_stat.st_size;
	if (lngFilesize <= 0) return false;
	FILE *ft;
	fopen_s(&ft, strFileName, "rb");
	if (ft == NULL)
	{
		return false;
	}
	char btData[1];
	long lngReadPos;
	long lngMaxRead = 40960;
	if (lngMaxRead>lngFilesize) lngMaxRead = lngFilesize;
	for (lngReadPos = 1; lngReadPos <= lngMaxRead; lngReadPos++)
	{
		fread(&btData, 1, 1, ft);
		if (btData[0] == '\0')
		{
			fclose(ft);
			return false;
		}
	}
	fclose(ft);
	return true;
}

// Figure out whether this machine is little- or big-endian
static bool we_are_little_endian()
{
	char buf[4];
	*(int *)(&buf[0]) = 1;
	return (buf[0] == 1);
}

// Byte swap uints, ints, and floats
static inline void swap_unsigned(volatile unsigned &x)
{
	x = (x << 24u) |
		((x << 8u) & 0x00ff0000u) |
		((x >> 8u) & 0x0000ff00u) |
		(x >> 24u);
}

static inline void swap_int(int &x)
{
	swap_unsigned(*(unsigned *)(&x));
}

static inline void swap_float(float &x)
{
	swap_unsigned(*(unsigned *)(&x));
}

static bool load_stl(const char *filename, std::vector<GTri3>& TriList)
{

	FILE *f = fopen(filename, "rb");
	bool need_swap = !we_are_little_endian();

	char header[80];
	COND_READ(true, header, 80);

	int nfacets;
	COND_READ(true, nfacets, 4);
	if (need_swap)
		swap_int(nfacets);

	if (!TriList.empty())
	{
		TriList.clear();
	}

	TriList.reserve(nfacets);
	for (int i = 0; i < nfacets; i++)
	{
		float fbuf[12];
		COND_READ(true, fbuf, 48);
		if (need_swap) {
			for (int j = 3; j < 12; j++)
				swap_float(fbuf[j]);
		}
		TriList.push_back(GTri3(GVec3(fbuf[3], fbuf[4], fbuf[5]), 
			GVec3(fbuf[6], fbuf[7], fbuf[8]),
			GVec3(fbuf[9], fbuf[10], fbuf[11])));
		unsigned char att[2];
		COND_READ(true, att, 2);
	}
	fclose(f);
	return true;
}

static bool read_stl(const char *filename, std::vector<GTri3>& TriList)
{
	FILE *file;
	if ((file = fopen(filename, "r")) == 0)
		return false;
	char str[80];

	if (!TriList.empty())
	{
		TriList.clear();
	}

	while (fscanf(file, "%s", str) == 1)
	{
		if (strncmp(str, "normal", 6) == 0)
		{
			GVec3 p[3];
			double x, y, z;
			fscanf(file, "%f %f %f", &(x), &(y), &(z));               
			fscanf(file, "%*s %*s");
			fscanf(file, "%*s %f %f %f", &(p[0][0]), &(p[0][1]), &(p[0][2]));
			fscanf(file, "%*s %f %f %f", &(p[1][0]), &(p[1][1]), &(p[1][2]));
			fscanf(file, "%*s %f %f %f", &(p[2][0]), &(p[2][1]), &(p[2][2]));
			TriList.push_back(GTri3(p[0], p[1], p[2]));
		}
	}
	TriList.shrink_to_fit();
	return true;
}
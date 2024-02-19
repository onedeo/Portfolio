#pragma once

// >> : Point3D
using Point3D = Vec3;

// << : Point3D

// >> : Line3D
struct Line3D
{
	Point3D start = Point3D(0.f);
	Point3D end = Point3D(0.f);

	float Lenghth() { return Vec3::Distance(start, end); }
	float LengthSq() { return Vec3::DistanceSquared(start, end); }
};
// << : Line3D

// >> : Ray3D
struct Ray3D
{
	Point3D origin = Point3D(0.f);
	Vec3 direction = Vec3(0.f);

	void NormalizeDirection() { direction.Normalize(); }

	static Ray3D FromPoints(const Point3D& from, const Point3D& to) { return Ray3D{ from, to - from }; }
};
// << : Ray3D

// >> : Sphere3D
struct Sphere3D
{
	Point3D position;
	float radius;
};
// << : Sphere3D

// >> : AABB3D
struct AABB3D
{
	Point3D position = Vec3(0.f);
	Vec3 size = Vec3(1.f);

	static Vec3 GetMin(const AABB3D& aabb)
	{
		Vec3 p1 = aabb.position + aabb.size;
		Vec3 p2 = aabb.position - aabb.size;
		return Vec3(fminf(p1.x, p2.x), fminf(p1.y, p2.y), fminf(p1.z, p2.z));
	}
	static Vec3 GetMax(const AABB3D& aabb)
	{
		Vec3 p1 = aabb.position + aabb.size;
		Vec3 p2 = aabb.position - aabb.size;
		return Vec3(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y), fmaxf(p1.z, p2.z));
	}
	static AABB3D FromMinMax(const Vec3& min, const Vec3& max)
	{
		return AABB3D((min + max) / 2, (max - min) / 2);
	}

};
// << : AABB3D

// >> : OBB3D
struct OBB3D
{
	Point3D position;
	Vec3 size;
	Matrix orientation;
};
// << : OBB3D

// >> : Plane3D
 // 정점 3개
 // 정점 1개 + 노말
 // 노말 + 원점에서의 거리
struct Plane3D
{
	Vec3 normal;
	float distance;
 }; 
// << : Plane3D

// >> : Triangle3D
struct Trangle3D
{
	union
	{
		struct
		{
			Point3D a;
			Point3D b;
			Point3D c;
		};
		Point3D points[3];
		float values[9];
	};
};
// << : Triangle3D
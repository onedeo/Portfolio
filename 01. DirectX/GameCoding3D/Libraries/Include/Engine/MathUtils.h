#pragma once
#include "Primitive3D.h"

struct MathUtils
{
	// >> : Point Test

	// Sphere2Point
	static bool PointInSphere(const Point3D& point, const Sphere3D sphere);
	static Point3D ClosestPoint(const Sphere3D& sphere, const Point3D& point);

	// AABB2Point
	static bool PointInAABB(const Point3D& point, const AABB3D& aabb);
	static Point3D ClosestPoint(const Point3D& point, const AABB3D& aabb);

	// OBB2Point
	static bool PointInOBB(const Point3D& point, const OBB3D& obb);
	static Point3D ClosestPoint(const Point3D& point, const OBB3D& obb);

	// Plane2Point
	static bool PointInPlane(const Point3D& point, const Plane3D& plane);
	static Point3D ClosestPoint(const Point3D& point, const Plane3D& plane);

	// Line2Point
	static bool PointInLine(const Point3D& point, const Line3D& line);
	static Point3D ClosestPoint(const Point3D& point, const Line3D& line);

	// Ray2Point
	static bool PointInRay(const Point3D& point, const Ray3D& ray);
	static Point3D ClosestPoint(const Point3D& point, const Ray3D& ray);

	// << : Point Test

};


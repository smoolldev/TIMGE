#ifndef UTILS_VECTOR_HPP
#define UTILS_VECTOR_HPP

namespace TIMGE
{
	template<typename Type_T>
	struct Vector2D
	{
		Type_T x;
		Type_T y;
	};

	template<typename Type_T>
	struct Vector3D
	{
		Type_T x;
		Type_T y;
		Type_T z;
	};

	template<typename Type_T>
	struct Vector4D
	{
		Type_T x;
		Type_T y;
		Type_T z;
		Type_T w;
	};
}

#endif // UTILS_VECTOR_HPP

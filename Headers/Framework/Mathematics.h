#pragma once

// Header with all relevant math headers & helper functions
#include <cmath>

// (3D) Math
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <detail/type_mat4x4.hpp>

#define PI 3.14159265359
#define PI2 6.28318530718

inline glm::vec3 Lerp(glm::vec3& a, glm::vec3 b, float t)
{
	return a * (1.0f - t) + b * t;
}
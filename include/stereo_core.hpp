#pragma once

#include "common.hpp"

namespace cp
{
	CP_EXPORT void lookat(const cv::Point3d& from, const cv::Point3d& to, cv::Mat& destR);
	CP_EXPORT void Eular2Rotation(const double pitch, const double roll, const double yaw, cv::OutputArray dest);
	CP_EXPORT void Rotation2Eular(cv::InputArray src, double& pitch, double& roll, double& yaw);

	CP_EXPORT void rotPitch(cv::InputArray src, cv::OutputArray dest, const double pitch);
	CP_EXPORT void rotYaw(cv::InputArray src, cv::OutputArray dest, const double yaw);
}
#pragma once

#include "common.hpp"

namespace cp
{
	
	//D. Min, J. Lu, and M. N. Do. "Depth video enhancement based on weighted mode filtering." IEEE Transactions on Image Processing 21(3), pp. 1176-1190, 2011.
	
	enum class WHF_HISTOGRAM_WEIGHT
	{
		IMPULSE,
		LINEAR,
		QUADRIC,
		GAUSSIAN,//original paper

		SIZE
	};

	enum WHF_OPERATION
	{
		NO_WEIGHT_MODE = 0,
		GAUSSIAN_MODE,
		BILATERAL_MODE,
		NO_WEIGHT_MEDIAN,
		GAUSSIAN_MEDIAN,
		BILATERAL_MEDIAN
	};

	CP_EXPORT void weightedHistogramFilter(cv::InputArray src, cv::InputArray guide, cv::OutputArray dst, const int r, const double sigmaColor, const double sigmaSpace, const double sigmaHistogram, const WHF_HISTOGRAM_WEIGHT weightFunctionType, const WHF_OPERATION method, const int borderType = cv::BORDER_DEFAULT, cv::InputArray mask = cv::noArray());
	CP_EXPORT void weightedModeFilter(cv::InputArray src, cv::InputArray guide, cv::OutputArray dst, const int r, const double sigmaColor, const double sigmaSpace, const double sigmaHistogram, const int borderType = cv::BORDER_DEFAULT, cv::InputArray mask = cv::noArray());
	
	/*
	CP_EXPORT void weightedMedianFilter(cv::InputArray src, cv::InputArray guide, cv::OutputArray dst, int r, int truncate, double sigmaColor, double sigmaSpace, const WHF_HISTOGRAM_WEIGHT weightFunctionType, int method);
	
	CP_EXPORT void weightedweightedMedianFilter(cv::InputArray src, cv::InputArray wmap, cv::InputArray guide, cv::OutputArray dst, int r, int truncate, double sigmaColor, double sigmaSpace, const WHF_HISTOGRAM_WEIGHT weightFunctionType, int method);
	CP_EXPORT void weightedweightedMedianFilter(cv::InputArray src, cv::InputArray wmap, cv::InputArray guide, cv::OutputArray dst, int r, int truncate, double sigmaColor1, double sigmaColor2, double sigmaSpace, const WHF_HISTOGRAM_WEIGHT weightFunctionType, int method);

	CP_EXPORT void weightedweightedModeFilter(cv::InputArray src, cv::InputArray wmap, cv::InputArray guide, cv::OutputArray dst, int r, int truncate, double sigmaColor, double sigmaSpace, const WHF_HISTOGRAM_WEIGHT weightFunctionType, int method);
	CP_EXPORT void weightedweightedModeFilter(cv::InputArray src, cv::InputArray wmap, cv::InputArray guide, cv::OutputArray dst, int r, int truncate, double sigmaColor1, double sigmaColor2, double sigmaSpace, const WHF_HISTOGRAM_WEIGHT weightFunctionType, int method);
	//with mask
	CP_EXPORT void weightedweightedModeFilter(cv::InputArray src, cv::InputArray wmap, cv::InputArray guide, cv::InputArray mask, cv::OutputArray dst, int r, int truncate, double sigmaColor, double sigmaSpace, const WHF_HISTOGRAM_WEIGHT weightFunctionType, int method);
	CP_EXPORT void weightedweightedMedianFilter(cv::InputArray src, cv::InputArray wmap, cv::InputArray guide, cv::InputArray mask, cv::OutputArray dst, int r, int truncate, double sigmaColor, double sigmaSpace, const WHF_HISTOGRAM_WEIGHT weightFunctionType, int method);
	CP_EXPORT void weightedweightedModeFilter(cv::InputArray src, cv::InputArray wmap, cv::InputArray guide, cv::InputArray mask, cv::OutputArray dst, int r, int truncate, double sigmaColor1, double sigmaColor2, double sigmaSpace, const WHF_HISTOGRAM_WEIGHT weightFunctionType, int method);
	CP_EXPORT void weightedweightedMedianFilter(cv::InputArray src, cv::InputArray wmap, cv::InputArray guide, cv::InputArray mask, cv::OutputArray dst, int r, int truncate, double sigmaColor1, double sigmaColor2, double sigmaSpace, const WHF_HISTOGRAM_WEIGHT weightFunctionType, int method);
	*/
}
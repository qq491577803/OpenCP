#include "downsample.hpp"
#include "inlineMathFunctions.hpp"
using namespace std;
using namespace cv;

namespace cp
{
	string getDowsamplingMethod(const Downsample method)
	{
		string ret = "";
		switch (method)
		{
		case Downsample::INTER_NEAREST:
			ret = "INTER_NEAREST"; break;
		case Downsample::INTER_LINEAR:
			ret = "INTER_LINEAR"; break;
		case Downsample::INTER_CUBIC:
			ret = "INTER_CUBIC"; break;
		case Downsample::INTER_AREA:
			ret = "INTER_AREA"; break;
		case Downsample::INTER_LANCZOS4:
			ret = "INTER_LANCZOS4"; break;
		case Downsample::CP_NEAREST:
			ret = "CP_NEAREST"; break;
		case Downsample::CP_LINEAR:
			ret = "CP_LINEAR"; break;
		case Downsample::CP_CUBIC:
			ret = "CP_CUBIC"; break;
		case Downsample::CP_AREA:
			ret = "CP_AREA"; break;
		case Downsample::CP_LANCZOS:
			ret = "CP_LANCZOS"; break;
		case Downsample::CP_GAUSS:
			ret = "CP_GAUSS"; break;
		case Downsample::CP_GAUSS_FAST:
			ret = "CP_GAUSS_Fast"; break;

		default:
			ret = "NO METHOD"; break;
		}

		return ret;
	}

	template <typename T>
	static void downsampleNN_(const Mat& src, Mat& dest, const int scale)
	{
		if (src.channels() == 1)
		{
			for (int j = 0, n = 0; j < src.rows; j += scale, n++)
			{
				const T* s = src.ptr<T>(j);
				T* d = dest.ptr<T>(n);
				for (int i = 0, m = 0; i < src.cols; i += scale, m++)
				{
					d[m] = s[i];
				}
			}
		}
		else
		{
			for (int j = 0, n = 0; j < src.rows; j += scale, n++)
			{
				const T* s = src.ptr<T>(j);
				T* d = dest.ptr<T>(n);
				for (int i = 0, m = 0; i < 3 * src.cols; i += 3 * scale, m += 3)
				{
					d[m + 0] = s[i + 0];
					d[m + 1] = s[i + 1];
					d[m + 2] = s[i + 2];
				}
			}
		}
	}

	static void hatConvolution(const Mat& src, Mat& dst, const int r)
	{
		const float invr = 1.f / r;
		const int d = 2 * r + 1;
		Mat kernel(d, 1, CV_32F);

		float wsum = 0.f;
		for (int i = -r; i <= r; i++)
		{
			const float dist = abs(i * invr);
			const float w = max(1.f - dist, 0.f);

			kernel.at<float>(i + r) = w;
			wsum += w;
		}

		for (int i = 0; i <= 2 * r; i++)
		{
			kernel.at<float>(i) /= wsum;
		}

		sepFilter2D(src, dst, src.depth(), kernel, kernel);
	}

	template <typename T>
	static void downsampleLinear_(const Mat& src, Mat& dest, const int scale, const int r)
	{
		Mat conv;
		hatConvolution(src, conv, r);
		downsampleNN_<T>(conv, dest, scale);
	}

	static void cubicConvolution(const Mat& src, Mat& dst, const int r, const double alpha)
	{
		const float invr = 1.0f / r;
		const float a = (float)alpha + 0.01f;
		const int d = 2 * r + 1;
		Mat kernel(d, 1, CV_32F);

		float wsum = 0.f;
		for (int i = -r; i <= r; i++)
		{
			const float dist = abs((float)i * invr);
			const float w = cp::cubic(dist, -a);
			//cout << w << endl;
			wsum += w;
			kernel.at<float>(i + r) = w;
		}
		//cout << "a: " << a << endl;
		//cout << kernel << endl;

		for (int i = 0; i <= 2 * r; i++)
		{
			kernel.at<float>(i) /= wsum;
		}

		sepFilter2D(src, dst, src.depth(), kernel, kernel);
	}

	template <typename T>
	static void downsampleCubic_(const Mat& src, Mat& dest, const int scale, const int r, const double alpha = 1.5)
	{
		Mat conv;
		cubicConvolution(src, conv, r, alpha);
		downsampleNN_<T>(conv, dest, scale);
	}

	template <typename T>
	static void downsampleArea_(const Mat& src_, Mat& dest, const int scale, const int r)
	{
		Mat src;
		const int d = 2 * r + 1;
		blur(src_, src, Size(d, d));

		downsampleNN_<T>(src, dest, scale);
	}

	static void LanczosConvolution(const Mat& src, Mat& dst, const int r, const int order)
	{
		const float invr = float(order) / r;
		const int d = 2 * r + 1;
		Mat kernel(d, 1, CV_32F);

		float wsum = 0.f;
		for (int i = -r; i <= r; i++)
		{
			const float dist = abs(i * invr);
			float w = cp::lanczos(dist, (float)order);
			kernel.at<float>(i + r) = w;
			wsum += w;
		}

		for (int i = 0; i <= 2 * r; i++)
		{
			kernel.at<float>(i) /= wsum;
		}

		sepFilter2D(src, dst, src.depth(), kernel, kernel);
	}

	template <typename T>
	static void downsampleLanczos_(const Mat& src, Mat& dest, const int scale, const int r, const int order = 4)
	{
		Mat conv;
		LanczosConvolution(src, conv, r, order);
		downsampleNN_<T>(conv, dest, scale);
	}


	template <typename T>
	static void downsampleGauss_(const Mat& src, Mat& dest, const int scale, const int r, const double sigma_clip = 3.0)
	{
		Mat conv, src32f;
		const int d = 2 * r + 1;

		src.convertTo(src32f, CV_32F);
		GaussianBlur(src32f, src32f, Size(d, d), r / sigma_clip);
		src32f.convertTo(conv, CV_8U);

		downsampleNN_<T>(conv, dest, scale);
	}

	template <typename T>
	static void downsampleGaussFast_(const Mat& src, Mat& dest, const int scale, const int r, const double sigma_clip = 3.0)
	{
		Mat conv;
		const int d = 2 * r + 1;
		GaussianBlur(src, conv, Size(d, d), r / sigma_clip);

		downsampleNN_<T>(conv, dest, scale);
	}

	void downsample(cv::InputArray src_, cv::OutputArray dest_, const int scale, const Downsample downsample_method, const double parameter, double radius_ratio)
	{
		int r = scale >> 1;
		r = int(radius_ratio * r);

		if ((int)downsample_method <= INTER_LANCZOS4)
		{
			resize(src_, dest_, Size(), 1.0 / scale, 1.0 / scale, (int)downsample_method);
		}
		else
		{
			dest_.create(src_.size() / scale, src_.type());
			Mat src = src_.getMat();
			Mat dest = dest_.getMat();
			switch (downsample_method)
			{
			case Downsample::CP_NEAREST:
				downsampleNN_<uchar>(src, dest, scale); break;
			case Downsample::CP_LINEAR:
				downsampleLinear_<uchar>(src, dest, scale, r); break;
			case Downsample::CP_CUBIC:
				if (parameter == 0)downsampleCubic_<uchar>(src, dest, scale, r);
				else downsampleCubic_<uchar>(src, dest, scale, r, parameter);
				break;
			case Downsample::CP_AREA:
				downsampleArea_<uchar>(src, dest, scale, r); break;
			case Downsample::CP_LANCZOS:
				if (parameter == 0)downsampleLanczos_<uchar>(src, dest, scale, (4 + 1) * r);
				else downsampleLanczos_<uchar>(src, dest, scale, int(parameter + 1) * r, (int)parameter);
				break;
			case Downsample::CP_GAUSS:
				if (parameter == 0)downsampleGauss_<uchar>(src, dest, scale, r);
				else downsampleGauss_<uchar>(src, dest, scale, r, parameter);
				break;
			case Downsample::CP_GAUSS_FAST:
				if (parameter == 0)downsampleGaussFast_<uchar>(src, dest, scale, r);
				else downsampleGaussFast_<uchar>(src, dest, scale, r, parameter);
				break;
			default:
				cout << "no method in downsample" << endl;
				break;
			}
		}
	}
}
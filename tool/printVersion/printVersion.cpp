#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void printVersionInfo()
{
    cout << "OpenCV 2 or 3? ";
#if CV_MAJOR_VERSION == 2
    cout << "2" << endl;
#elif CV_MAJOR_VERSION == 3
    cout << "3" << endl;
#else
#error "Unrecognized OpenCV version!"
#endif
    cout << "OpenCV version: " << CV_VERSION << endl;
    // CV_MAJOR_VERSION CV_MINOR_VERSION CV_SUBMINOR_VERSION
}

void printHardwareSupport()
{
    string cpu_features;

    if (checkHardwareSupport(CV_CPU_POPCNT)) cpu_features += " popcnt";
    if (checkHardwareSupport(CV_CPU_MMX)) cpu_features += " mmx";
    if (checkHardwareSupport(CV_CPU_SSE)) cpu_features += " sse";
    if (checkHardwareSupport(CV_CPU_SSE2)) cpu_features += " sse2";
    if (checkHardwareSupport(CV_CPU_SSE3)) cpu_features += " sse3";
    if (checkHardwareSupport(CV_CPU_SSSE3)) cpu_features += " ssse3";
    if (checkHardwareSupport(CV_CPU_SSE4_1)) cpu_features += " sse4.1";
    if (checkHardwareSupport(CV_CPU_SSE4_2)) cpu_features += " sse4.2";
    if (checkHardwareSupport(CV_CPU_AVX)) cpu_features += " avx";
    if (checkHardwareSupport(CV_CPU_AVX2)) cpu_features += " avx2";
    if (checkHardwareSupport(CV_CPU_FMA3)) cpu_features += " fma3";
    if (checkHardwareSupport(CV_CPU_AVX_512F)) cpu_features += " avx-512f";
    if (checkHardwareSupport(CV_CPU_AVX_512BW)) cpu_features += " avx-512bw";
    if (checkHardwareSupport(CV_CPU_AVX_512CD)) cpu_features += " avx-512cd";
    if (checkHardwareSupport(CV_CPU_AVX_512DQ)) cpu_features += " avx-512dq";
    if (checkHardwareSupport(CV_CPU_AVX_512ER)) cpu_features += " avx-512er";
    if (checkHardwareSupport(CV_CPU_AVX_512IFMA512)) cpu_features += " avx-512ifma512";
    if (checkHardwareSupport(CV_CPU_AVX_512PF)) cpu_features += " avx-512pf";
    if (checkHardwareSupport(CV_CPU_AVX_512VBMI)) cpu_features += " avx-512vbmi";
    if (checkHardwareSupport(CV_CPU_AVX_512VL)) cpu_features += " avx-512vl";
    if (checkHardwareSupport(CV_CPU_NEON)) cpu_features += " neon";

    cpu_features.erase(0, 1); // erase initial space

    cout << "CPU features: " << cpu_features << endl;
}

int main(/*int argc, char** argv*/)
{
    printVersionInfo();

    printHardwareSupport();

    return 0;
}

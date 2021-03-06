#include <opencv2/opencv.hpp>
#include <oloader.h>

int main()
{

	oc::oloader animal_classifier;
	animal_classifier.load(L"animal-darknet19-compress.dll", oc::oloader::MODULE_TYPE::__DLL); /// 모델을 로드할수있는 dll 


	cv::Mat image = cv::imread("D:\\OpenCodeModuleDeep\\ConsoleExample\\x64\\Debug\\1_1_0_cat.jpg");  /// 이미지 경로.
	cv::Mat convert;
	image.convertTo(convert, CV_32F);



	oc::variant initParam;
	initParam << (const char *)"D:\\OpenCodeModuleDeep\\ConsoleExample\\x64\\Debug\\animal-darknet19-compress.pb";  /// 모델 경로.
	initParam << convert.cols;  // 이미지 너비
	initParam << convert.rows;  // 이미지 높이
	initParam << 3;             // 이미지 채널.


	oc::variant imageParam;
	bool phase = false;
	imageParam << (float *)convert.data;   /// image pointer
	imageParam << &phase;                  /// Batch normalization turn off


	try {
		oc::variant init_output = animal_classifier.initialize(initParam);
		oc::variant run_output = animal_classifier.run(imageParam);
		std::cout << "message : " << run_output[0].get<const char *>() << std::endl;
		std::cout << "score list :" << run_output[1].get<float>() << std::endl;
		std::cout << "score list :" << run_output[2].get<float>() << std::endl;
		std::cout << "score list :" << run_output[3].get<float>() << std::endl;
		std::cout << "score list :" << run_output[4].get<float>() << std::endl;
		std::cout << "score list :" << run_output[5].get<float>() << std::endl;
	}
	catch (std::runtime_error e) {
		std::cout << e.what() << std::endl;
	}

	cv::imshow("input image", image);
	cv::waitKey();

	return 0;
}
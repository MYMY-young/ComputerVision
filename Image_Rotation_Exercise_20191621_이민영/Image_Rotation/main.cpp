#include <iostream>
#include <opencv2\opencv.hpp>


cv::Mat problem_a_rotate_forward(cv::Mat img, double angle){
	cv::Mat output;
	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	cv::Mat output1;
	cv::Mat rotate;
	angle = angle * CV_PI / 180;
	
	
	int Width = img.rows;
	int Height = img.cols;
	cv::Point_<float>  center((img.rows ) / 2.0, (img.cols )/2.0);
	
	output1 = img.clone();
	
	for (int i = 0;i < output1.cols;i++) {
		for (int j = 0;j < output1.rows;j++) {
			for (int c = 0;c < output1.channels();c++) {
				output1.at<cv::Vec3b>(j, i)[c] = 0;
			}
		}
	}

	
	int size_y = abs(Width * sin(angle)) + abs(Height * cos(angle));
	int size_x = abs(Height * sin(angle)) + abs(Width* cos(angle));
	
	resize(output1, output, cv::Size(size_y, size_x));
	

	for (int i = 0; i< Height;i++) {
		for (int j = 0;j < Width;j++) {
			for (int c = 0;c < img.channels();c++) {
				
				int temp_i = i;
				int temp_j = j;

				temp_i = temp_i - center.y;
				temp_j = temp_j - center.x;

				int new_X = (temp_i * sin(angle)) + (temp_j * cos(angle)) + size_x/2;
				int new_Y = (temp_i * cos(angle)) - (temp_j * sin(angle)) + size_y/2;

				
				if ((new_Y >= 0 && new_Y < size_y) && (new_X >= 0 && new_X < size_x)) {
			
					output.at<cv::Vec3b>(new_X, new_Y)[c] = img.at<cv::Vec3b>(j, i)[c];
			
				}
				
			}
		}
	}
	
	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////
	cv::imshow("a_output", output); cv::waitKey(0);
	return output;
}

cv::Mat problem_b_rotate_backward(cv::Mat img, double angle){
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////

	cv::Mat output1;
	cv::Mat rotate;
	angle = angle * CV_PI / 180;
	
	int Width = img.rows;
	int Height = img.cols;
	cv::Point_<int>  center((img.rows) / 2.0, (img.cols) / 2.0);
	output1 = img.clone();

	
	for (int i = 0;i < output1.cols;i++) {
		for (int j = 0;j < output1.rows;j++) {
			for (int c = 0;c < output1.channels();c++) {
				
				output1.at<cv::Vec3b>(j, i)[c] = 0;
			}
		}
	}
	
	int size_y = abs(Width * sin(angle)) + abs(Height * cos(angle));
	int size_x = abs(Height * sin(angle)) + abs(Width * cos(angle));
	
	resize(output1, output, cv::Size(size_y, size_x));
	
	for (int new_Y = 0; new_Y < size_y;new_Y++) {
		for (int new_X = 0;new_X < size_x;new_X++) {
			for (int c = 0;c < img.channels();c++) {
			
				int temp_X = new_X - size_x/2;
				int temp_Y = new_Y - size_y/2;
				
				int j = (temp_X * cos(-angle)) + (temp_Y * sin(-angle)) + center.x;
				int i = -(temp_X * sin(-angle)) + (temp_Y * cos(-angle)) + center.y;
			
				if ((i >= 0 && i < Height) && (j >= 0 && j < Width)) {

					output.at<cv::Vec3b>(new_X, new_Y)[c] = img.at<cv::Vec3b>(j, i)[c];
				
				}
			

			}
		}
	}
	

	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////

	cv::imshow("b_output", output); cv::waitKey(0);

	return output;
}

cv::Mat problem_c_rotate_backward_interarea(cv::Mat img, double angle){
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////



	cv::Mat output1;
	cv::Mat rotate;
	
	int Width = img.rows;
	int Height = img.cols;
	
	angle = angle * CV_PI / 180;

	cv::Point_<int> center((img.rows) / 2.0, (img.cols) / 2.0);
	
	output1 = img.clone();
	
	for (int i = 0;i < output.cols;i++) {
		for (int j = 0;j < output.rows;j++) {
			for (int c = 0;c < output.channels();c++) {
				output1.at<cv::Vec3b>(j, i)[c] = 0;
			}
		}
	}

	int size_y = abs(Width * sin(angle)) + abs(Height * cos(angle));
	int size_x = abs(Height * sin(angle)) + abs(Width * cos(angle));

	double d_size_y = fabs(Width * sin(angle)) + fabs(Height * cos(angle));
	double d_size_x = fabs(Height * sin(angle)) + fabs(Width * cos(angle));
	
	resize(output1, output, cv::Size(size_y, size_x));
	
	for (int i = 0; i < size_y;i++) {
		for (int j = 0;j < size_x;j++) {
			for (int c = 0;c < img.channels();c++) {

				double ii = 0;
				double jj = 0;
				
				double t[3], multi[3];
				double rotate_[9];
				
				t[0] = j - (double)d_size_x/2;
				t[1] = i - (double)d_size_y/2;
				t[2] = 1;
				
				ii = -(t[0] * sin(-angle)) + (t[1] * cos(-angle)) + center.y;
				jj = (t[0] * cos(-angle)) + (t[1] * sin(-angle)) + center.x;
		
					
					
				 
				if ((ii + 1 < Height && ii>= 0)&& (jj + 1 < Width && jj >= 0)) {
						int a_x = jj; int a_y = ii+1;
						int b_x = jj; int b_y = ii;
						int c_x = jj + 1; int c_y = ii;
						int d_x = jj + 1; int d_y = ii+1;
						
						
						double A = img.at<cv::Vec3b>(a_x, a_y)[c];
						double B = img.at<cv::Vec3b>(b_x, b_y)[c];
						double C = img.at<cv::Vec3b>(c_x, c_y)[c];
						double D = img.at<cv::Vec3b>(d_x, d_y)[c];
						
						double q = c_x - jj;
						double beta = ii - b_y;
						double alpha = a_y - ii;
						double p = jj - a_x;
						
						output.at<cv::Vec3b>(j, i)[c] = (int)(q * beta * A) + (q * alpha * B) + (p * beta * D) + (p * alpha * C);
						
						


				}
				 
				
				else {
					output.at<cv::Vec3b>(j, i)[c] = 0;


				}

			}
		}
	}





	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////

	cv::imshow("c_output", output); cv::waitKey(0);

	return output;
}

cv::Mat Example_change_brightness(cv::Mat img, int num, int x, int y) {
	/*
	img : input image
	num : number for brightness (increase or decrease)
	x : x coordinate of image (for square part)
	y : y coordinate of image (for square part)

	*/
	cv::Mat output = img.clone();
	int size = 100;
	int height = (y + 100 > img.rows) ? img.rows : y + 100;
	int width = (x + 100 > img.cols) ? img.cols : x + 100;

	for (int i = x; i < width; i++)
	{
		for (int j = y; j < height; j++)
		{
			for (int c = 0; c < img.channels(); c++)
			{
				int t = img.at<cv::Vec3b>(i, j)[c] + num;
				output.at<cv::Vec3b>(i, j)[c] = t > 255 ? 255 : t < 0 ? 0 : t;
			}
		}

	}
	cv::imshow("output1", img);
	cv::imshow("output2", output);
	cv::waitKey(0);
	return output;
}

int main(void){

	double angle = -15.0f;

	cv::Mat input = cv::imread("lena.jpg");
	//Fill problem_a_rotate_forward and show output
	problem_a_rotate_forward(input, angle);
	//Fill problem_b_rotate_backward and show output
	problem_b_rotate_backward(input, angle);
	//Fill problem_c_rotate_backward_interarea and show output
	problem_c_rotate_backward_interarea(input, angle);
	//Example how to access pixel value, change params if you want
	Example_change_brightness(input, 100, 50, 125);
}
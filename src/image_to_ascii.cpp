/*
** titanfrigel
** my_ai
** File description:
** image_to_ascii.cpp
*/

#include "my.h"
#include <cmath>
#include <string>
#include <opencv2/opencv.hpp>
#include <ncurses.h>

int image_to_ascii(int argc, char **argv)
{
	std::string greyscale = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
	reverse(greyscale.begin(), greyscale.end());
	cv::VideoCapture cap(0);

	if (argc > 1 && argv[1] == "-h") {
		printf("Usage: ./itoa [-s]\n\t-s: show the video feed\n\t-h: show this help\n\tESC: exit\n");
		return (0);
	}
	if (!cap.isOpened()) {
		std::cout << "Error opening video stream or file" << std::endl;
		return (84);
	}
	initscr();
	while (11) {
		cv::Mat frame;
		std::string buffer;

		cap >> frame;
		if (argc > 1 && argv[1] == "-s")
			cv::imshow("Frame", frame);
		double scale = MIN((double)COLS / frame.cols ,(double)LINES / frame.rows);
		cv::resize(frame, frame, cv::Size(0, 0), MIN(scale * 3, LINES), scale);
		for (size_t i = 0; &frame.data[i] != frame.dataend; i += 3) {
			if (i % (frame.cols * 3) == 0 && i != 0)
				buffer.push_back('\n');
			buffer.push_back(greyscale[round((0.114 * frame.data[i] + 0.587 * frame.data[i + 1] +
			0.299 * frame.data[i + 2]) * (greyscale.size() - 1) / 255)]);
		}
		clear();
		addstr(buffer.c_str());
		refresh();
		nodelay(stdscr, true);
		char c = getch();
		if (c == 27)
			break;
	}
	cap.release();
	cv::destroyAllWindows();
	endwin();
	return (0);
}

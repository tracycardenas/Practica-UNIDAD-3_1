

all:
	g++ Parte2.cpp LBPDescriptor.cpp histogram.cpp ./package_lbp/olbp/OLBP.cpp ./package_lbp/oclbp/OCLBP.cpp -I//home/computacion/opencv/opencvi/include/opencv4/ -L/home/computacion/opencv/opencvi/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_video -lopencv_videoio -lopencv_objdetect -o vision.bin --std=c++17 -lstdc++fs


run:
	./vision.bin
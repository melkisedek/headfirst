#include <opencv/highgui.h>

int main(int argc, char *argv[]){
	CvCapture* webcam = cvCreateCameraCapture(0);
	if(!webcam)
	puts("Camera no Detected");
	int i;
	for (i = 0; i <20; i++){
	IplImage* image = cvQueryFrame(webcam);
		if(image){
		cvSaveImage("images.jpg", image, 0);
		}
	}
	return 0;
}

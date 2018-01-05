#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <stdlib.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fixedfann.h>
//g++ sanityTest.cpp -o sanityTest $(pkg-config --cflags --libs opencv)-lfann -lm

using namespace std;
using namespace cv;

int main(int argc, char const *argv[]) {
  if(argc != 2){
    cout << "Usage: capchaProc [training file]" << endl;
    exit(EXIT_FAILURE);
  }

  namedWindow( "Display window", CV_WINDOW_AUTOSIZE );
  resizeWindow("Display window", 100,100);


  //image
  Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  Mat img;

  if(!image.data){
    cout << "could not open or find the image" << endl;
  }
  cvtColor( image, image, CV_BGR2GRAY );

  //fann
  struct fann *ann = fann_create_from_file("letterRecognition.net");
  fann_type* out;

  //settings
  Mat openkernel = getStructuringElement( MORPH_RECT, Size( 2, 2 ));

  for(int i=0; i< 5; i++){
    img = image(Rect(i*42,0,42,42));
    imshow( "Display window", img );
    waitKey(0);

    threshold( img, img, 90, 255, 0);
    erode(img, img, openkernel);

    imshow( "Display window", img );
    waitKey(0);

    printf("%i ",img.data[0]);
    out = fann_run(ann, (int*)img.data);

    for(int j = 0; j < 26; j++){
      printf("%i ", out[j]);
    }
    cout << endl;

  }
  cout << endl;


  return 0;
}

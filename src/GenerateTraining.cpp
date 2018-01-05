#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <stdlib.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//g++ capchaProc.cpp -o capchaProc $(pkg-config --cflags --libs opencv)

#define BUFSIZE 512

using namespace std;
using namespace cv;

#define THRESHOLD_TYPE 0
#define THRESHOLD_VALUE 110
#define MAX_BINARY_THRESHOLD 255


int main(int argc, char const *argv[]) {
  if(argc != 2){
    cout << "Usage: capchaProc [training file]" << endl;
    exit(EXIT_FAILURE);
  }

  char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  ifstream fs;
  ofstream os;
  os.open("training.txt");
  os << "71 1764 26" << endl;
  char buffer[BUFSIZE];
  map<string, string> items;
  int index;
  fs.open(argv[1],fstream::in);
  fs.getline(buffer, BUFSIZE);
  while(!fs.eof()){
    string line(buffer);
    index = line.find(",");
    //cout << line.substr(0, index) << " : ";
    //cout << line.substr(index+1, line.length()) << endl;
    items.insert( pair<string,string>(line.substr(0, index), line.substr(index+1, line.length())) );
    fs.getline(buffer, BUFSIZE);
  }

  namedWindow( "Display window", CV_WINDOW_AUTOSIZE );


  for(map<string,string>::iterator it=items.begin(); it != items.end(); it++){
    Mat image = imread(it->first, CV_LOAD_IMAGE_COLOR);
    Mat m;


    if(!image.data){
      cout << "could not open or find the image" << endl;
    }


    cvtColor( image, image, CV_BGR2GRAY );
    // imshow( "Display window", image );                   // Show our image inside it.
    // waitKey(0);

    Rect roi;
    Mat openkernel = getStructuringElement( MORPH_RECT, Size( 2, 2 ));
    Mat closekernel = getStructuringElement( MORPH_RECT, Size( 3, 3 ));

      resizeWindow("Display window", 100,100);
      for(int i=0; i< 5; i++){
        roi = Rect(i*42,0,42,42);
        m = image(roi);
        // imshow( "Display window", m );
        // waitKey(0);
        //adaptiveThreshold( image, image, MAX_BINARY_THRESHOLD, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 101, 10 );
        threshold( m, m, 90, MAX_BINARY_THRESHOLD, 0);
        // imshow( "Display window", m );
        // waitKey(0);

        // morphologyEx(m,m, MORPH_OPEN, openkernel);
        erode(m,m,openkernel);
        // imshow( "Display window", m );
        // waitKey(0);


        for(int i=0; i<m.rows; i++){
          for(int j=0; j<m.cols; j++){
            if(m.at<bool>(i,j) > 0){
              os << "0 ";
            } else {
              os << "255 ";
            }
          }
        }
        os << endl;
        char output = it->second[i];
        for(int j = 0; j < 26; j++){
          if(output==alphabet[j]){
            os << "1 ";
          } else {
            os << "0 ";
          }
        }
        os << endl;
      }
  }
  return 0;
}

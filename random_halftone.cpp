#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <ctime>

int main(int argc, char *argv[])
    int height = 400;
    int width = 600;
    // Allocate image data array
    if (!(file=fopen(argv[1],"rb"))) {

	unsigned char OutputImage [height][width][1];
	srand((unsigned)time(0));
    int random;

	for(int i=0; i<height; ++i){
        for( int j=0; j< width; ++j){
            random = rand()%255;
            if(Imagedata[i][j][0] <= random){
            OutputImage[i][j][0] =  0;
            }
            else{
                OutputImage[i][j][0] = 255;
            }
        }
	}
     if (!(file=fopen(argv[2],"wb"))) {

}
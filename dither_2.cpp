#include <stdio.h>
#include <cmath>
#include <fstream>
    int height = 400;
    int width = 600;

	unsigned char OutputImage[height][width][BytesPerPixel];

	int dither[2][2] = {{1,2},{3,0}};
	int n = 2;
	float thresh[2][2];
	for(int i =0; i<2; ++i){
        for(int j=0; j<2; ++j){
            thresh[i][j] = (dither[i][j]+ 0.5)/(n*n*1.0) * 255.0;
           // cout<<thresh[i][j]<<endl;
        }
	}

	for(int i=0; i<height;++i){
        for(int j=0; j< width; ++j){
            if((int)(Imagedata[i][j][0])<=thresh[i%n][j%n]){

                OutputImage[i][j][0] =  0;
            }
            else{
                //cout<<(int)(Imagedata[i][j][0])<<endl;
                //cout<<(thresh[i%n][j%n])<<endl;
                OutputImage[i][j][0] =  255;
            }
        }
	}

	if (!(file=fopen(argv[2],"wb"))) {
	cout<<"written"<<endl;
	return 0;
}
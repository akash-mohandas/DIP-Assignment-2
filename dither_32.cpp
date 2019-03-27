#include <stdio.h>
#include <cmath>
#include <fstream>
int dither[2][2] = {{1,2},{3,0}};
int getDither(int i, int j, int n){
    //cout<<i<<":"<<j<<":"<<n<<endl;
    if(n==2){
        //cout<<dither[i][j]<<endl;
        return dither[i][j];
    }
    else if(i*2/n==0 && j*2/n==0){
        int a = 4*(getDither(i%(n/2),j%(n/2),n/2)) + 1;
        //cout<<a<<endl;
        return a;
    }
    else if(i*2/n==0 && j*2/n==1){
        int a = 4*(getDither(i%(n/2),j%(n/2),n/2)) + 2;
        //cout<<a<<endl;
        return a;
    }
    else if(i*2/n==1 && j*2/n==0){
        int a = 4*(getDither(i%(n/2),j%(n/2),n/2)) + 3;
        //cout<<a<<endl;
        return a;
    }
    else{
        int a = 4*(getDither(i%(n/2),j%(n/2),n/2));
        //cout<<a<<endl;
        return a;
    }
}
    int height = 400;
    int width = 600;

	unsigned char OutputImage[height][width][BytesPerPixel];


	int dither_ [32][32];
	int n = 32;
	float thresh[32][32];
	for(int i=0; i<32;++i){
        for(int j=0; j<32; ++j){
            dither_[i][j] = getDither(i,j,32);
            cout<<dither_[i][j]<<endl;
        }
	}
	//int a = getDither(0,2,8);
	//cout<<a<<endl;
	for(int i =0; i<32; ++i){
        for(int j=0; j<32; ++j){
            thresh[i][j] = (dither_[i][j]+ 0.5)/(n*n*1.0) * 255.0;
            //cout<<thresh[i][j]<<endl;
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
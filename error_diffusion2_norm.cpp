#include <stdio.h>
#include <cmath>
#include <fstream>

    int height = 400;
    int width = 600;

	unsigned char OutputImage[height][width][BytesPerPixel];
	float error;
	float Reimage[height+4][width+4][1];
	for(int j=0; j<2; ++j){
        for(int i=2; i<2+width; ++i){
            Reimage[j][i][0] = Imagedata[2-j][i-2][0];
        }
	}
	cout<<"first"<<endl;
	for(int j=0; j<2; ++j){
        for(int i=2; i<2+width; ++i){
            Reimage[height+j+2][i][0] = Imagedata[height-j-2][i-2][0];
        }
	}
    cout<<"second"<<endl;
	for(int i=0; i<2; ++i){
        for(int j=2; j<2+height; ++j){
            Reimage[j][i][0] = Imagedata[j-2][2-i][0];
        }
	}

	for(int i=0; i<2; ++i){
        for(int j=2; j<2+height; ++j){
            Reimage[j][width+2+i][0] = Imagedata[j-2][width-i-2][0];
        }
	}
	cout<<"continued"<<endl;
	Reimage[0][0][0] = Reimage[0][4][0];
	Reimage[0][1][0] = Reimage[0][3][0];
	Reimage[1][0][0] = Reimage[1][4][0];
	Reimage[1][1][0] = Reimage[1][3][0];
	Reimage[0][width+2][0] = Reimage[0][width][0];
	Reimage[0][width+3][0] = Reimage[0][width-1][0];
	Reimage[1][width+2][0] = Reimage[1][width][0];
	Reimage[1][width+3][0] = Reimage[1][width-1][0];
	Reimage[height+2][0][0] = Reimage[height+2][4][0];
	Reimage[height+2][1][0] = Reimage[height+2][3][0];
	Reimage[height+3][0][0] = Reimage[height+3][4][0];
	Reimage[height+3][1][0] = Reimage[height+3][3][0];
	Reimage[height+2][width+2][0] = Reimage[height+2][width][0];
	Reimage[height+2][width+3][0] = Reimage[height+2][width-1][0];
	Reimage[height+3][width+2][0] = Reimage[height+3][width][0];
	Reimage[height+3][width+3][0] = Reimage[height+3][width-1][0];

    for(int j=0; j<height; ++j){
        for(int i=0; i<width; ++i){
            Reimage[j+2][i+2][0] = Imagedata[j][i][0];
            //cout<<Reimage[j+2][i+2][0]<<endl;
        }
    }

	int i=2;
	int j=2;
	while(true){

        if (Reimage[i][j][0] <= 128){
            OutputImage[i-2][j-2][0] = 0;
        }
        else{
            OutputImage[i-2][j-2][0] = 255;
        }
        error = Reimage[i][j][0] - OutputImage[i-2][j-2][0];
        Reimage[i][j+1][0] += 7*error/48.0;
        Reimage[i][j+2][0] += 5*error/48.0 ;
        Reimage[i+1][j+2][0] += 3*error/48.0;
        Reimage[i+1][j+1][0] += 5*error/48.0;
        Reimage[i+1][j][0]+= 7*error/48.0;
        Reimage[i+1][j-1][0] += 5*error/48.0 ;
        Reimage[i+1][j-2][0] += 3*error/48.0 ;
        Reimage[i+2][j+2][0] += 1*error/48.0 ;
        Reimage[i+2][j+1][0] += 3*error/48.0 ;
        Reimage[i+2][j][0] += 5*error/48.0 ;
        Reimage[i+2][j-1][0] += 3*error/48.0 ;
        Reimage[i+2][j-2][0] += 1*error/48.0 ;

        if(j==width+1){
            i+=1;
            j=0;
        }
        else{
            j+=1;
        }

    if(i==height+1 && j== width+1)
        break;
    }


	if (!(file=fopen(argv[2],"wb"))) {


	cout<<"written"<<endl;
	return 0;
}
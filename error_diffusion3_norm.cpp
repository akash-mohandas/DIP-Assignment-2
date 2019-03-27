#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <cmath>
#include <fstream>using namespace std;
int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 400;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}
    int height = 400;
    int width = 600;	// Allocate image data array	unsigned char Imagedata[height][width][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);

	unsigned char OutputImage[height][width][BytesPerPixel];
	float Reimage[404][604][1];
	float error;
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
        Reimage[i][j+1][0] += 8*error/42.0;
        Reimage[i][j+2][0] += 4*error/42.0 ;
        Reimage[i+1][j+2][0] += 2*error/42.0;
        Reimage[i+1][j+1][0] += 4*error/42.0;
        Reimage[i+1][j][0]+= 8*error/42.0;
        Reimage[i+1][j-1][0] += 4*error/42.0 ;
        Reimage[i+1][j-2][0] += 2*error/42.0 ;
        Reimage[i+2][j+2][0] += 1*error/42.0 ;
        Reimage[i+2][j+1][0] += 2*error/42.0 ;
        Reimage[i+2][j][0] += 4*error/42.0 ;
        Reimage[i+2][j-1][0] += 2*error/42.0 ;
        Reimage[i+2][j-2][0] += 1*error/42.0 ;
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


	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] <<endl;		exit(1);	}	fwrite(OutputImage, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);


	cout<<"written"<<endl;
	return 0;
}

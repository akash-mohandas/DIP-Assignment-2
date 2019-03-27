#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <cmath>
#include <fstream>using namespace std;
int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 400;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}
    int height = 400;
    int width = 600;	// Allocate image data array	unsigned char Imagedata[height][width][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);

	unsigned char OutputImage[height][width][BytesPerPixel];
	float ***Reimage = new float**[height+2];
	for(int i =0; i< height+2; ++i){
        Reimage[i] = new float* [width+2];
        for(int j=0; j< width+2; ++j){
            Reimage[i][j] = new float[1];
        }
	}
	for(int j=0; j<1; ++j){
        for(int i=1; i<1+width; ++i){
            Reimage[j][i][0] = Imagedata[1-j][i-1][0];
        }
	}
	cout<<"first"<<endl;
	for(int j=0; j<1; ++j){
        for(int i=1; i<1+width; ++i){
            Reimage[height+j+1][i][0] = Imagedata[height-j-2][i-1][0];
        }
	}
    cout<<"second"<<endl;
	for(int i=0; i<1; ++i){
        for(int j=1; j<1+height; ++j){
            Reimage[j][i][0] = Imagedata[j-1][1-i][0];
        }
	}

	for(int i=0; i<1; ++i){
        for(int j=1; j<1+height; ++j){
            Reimage[j][width+1+i][0] = Imagedata[j-1][width-i-2][0];
        }
	}
	cout<<"continued"<<endl;

	Reimage[0][0][0] = Reimage[0][2][0];
	Reimage[0][width+1][0] = Reimage[0][width-1][0];
	Reimage[height+1][0][0] = Reimage[height+1][2][0];
	Reimage[height+1][width+1][0] = Reimage[height+1][width-1][0];

    for(int j=0; j<height; ++j){
        for(int i=0; i<width; ++i){
            Reimage[j+1][i+1][0] = Imagedata[j][i][0];
        }
    }


	int i=1;
	int j=1;
	float error;
	while(true){
        if (Reimage[i][j][0] <= 127){
            OutputImage[i-1][j-1][0] = 0;
        }
        else{
            OutputImage[i-1][j-1][0] = 255;
        }
        error = Reimage[i][j][0] - OutputImage[i-1][j-1][0];
        Reimage[i][j+1][0] += 7*error/16.0;
        Reimage[i+1][j+1][0] += 1*error/16.0;
        Reimage[i+1][j][0] += 5*error/16.0;
        Reimage[i+1][j-1][0]+= 3*error/16.0;
        if(j==width){
            i+=1;
            j=1;
        }
        else{
            j+=1;
        }
        if(i==height && j== width)
            break;
    }


	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] <<endl;		exit(1);	}	fwrite(OutputImage, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);


	cout<<"written"<<endl;
	return 0;
}

#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <cmath>
#include <fstream>using namespace std;int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 400;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}
    int height = 400;
    int width = 600;	// Allocate image data array	unsigned char Imagedata[height][width][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);

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

	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] <<endl;		exit(1);	}	fwrite(OutputImage, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);
	cout<<"written"<<endl;
	return 0;
}

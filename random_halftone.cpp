#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;
int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 256;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}
    int height = 400;
    int width = 600;
    // Allocate image data array	unsigned char Imagedata[height][width][BytesPerPixel];
    if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);

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
     if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(OutputImage, sizeof(unsigned char), (height)*(width)*1, file);	fclose(file);
	return 0;
}

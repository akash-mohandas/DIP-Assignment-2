#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <cmath>
#include <fstream>using namespace std;
int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 400;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 3; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}
    int height = 375;
    int width = 500;	// Allocate image data array	unsigned char Imagedata[height][width][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);

    for(int i=0; i<height; ++i){
        for(int j=0; j<width; ++j){
            Imagedata[i][j][0] = 255-Imagedata[i][j][0];
            Imagedata[i][j][1] = 255-Imagedata[i][j][1];
            Imagedata[i][j][2] = 255-Imagedata[i][j][2];
        }
    }

	unsigned char OutputImage[height][width][BytesPerPixel];
	float ***Reimage = new float**[height+2];
	for(int i =0; i< height+2; ++i){
        Reimage[i] = new float* [width+2];
        for(int j=0; j< width+2; ++j){
            Reimage[i][j] = new float[3];
        }
	}
	cout<<"yes"<<endl;
	for(int j=0; j<1; ++j){
        for(int i=1; i<1+width; ++i){
            Reimage[j][i][0] = Imagedata[1-j][i-1][0];
            Reimage[j][i][1] = Imagedata[1-j][i-1][1];
            Reimage[j][i][2] = Imagedata[1-j][i-1][2];
        }
	}
	cout<<"first"<<endl;
	for(int j=0; j<1; ++j){
        for(int i=1; i<1+width; ++i){
            Reimage[height+j+1][i][0] = Imagedata[height-j-2][i-1][0];
            Reimage[height+j+1][i][1] = Imagedata[height-j-2][i-1][1];
            Reimage[height+j+1][i][2] = Imagedata[height-j-2][i-1][2];
        }
	}
    cout<<"second"<<endl;
	for(int i=0; i<1; ++i){
        for(int j=1; j<1+height; ++j){
            Reimage[j][i][0] = Imagedata[j-1][1-i][0];
            Reimage[j][i][1] = Imagedata[j-1][1-i][1];
            Reimage[j][i][2] = Imagedata[j-1][1-i][2];
        }
	}

	for(int i=0; i<1; ++i){
        for(int j=1; j<1+height; ++j){
            Reimage[j][width+1+i][0] = Imagedata[j-1][width-i-2][0];
            Reimage[j][width+1+i][1] = Imagedata[j-1][width-i-2][1];
            Reimage[j][width+1+i][2] = Imagedata[j-1][width-i-2][2];
        }
	}
	cout<<"continued"<<endl;

	Reimage[0][0][0] = Reimage[0][2][0];
	Reimage[0][width+1][0] = Reimage[0][width-1][0];
	Reimage[height+1][0][0] = Reimage[height+1][2][0];
	Reimage[height+1][width+1][0] = Reimage[height+1][width-1][0];

    Reimage[0][0][1] = Reimage[0][2][1];
	Reimage[0][width+1][1] = Reimage[0][width-1][1];
	Reimage[height+1][0][1] = Reimage[height+1][2][1];
	Reimage[height+1][width+1][1] = Reimage[height+1][width-1][1];

	Reimage[0][0][2] = Reimage[0][2][2];
	Reimage[0][width+1][2] = Reimage[0][width-1][2];
	Reimage[height+1][0][2] = Reimage[height+1][2][2];
	Reimage[height+1][width+1][2] = Reimage[height+1][width-1][2];

    for(int j=0; j<height; ++j){
        for(int i=0; i<width; ++i){
            Reimage[j+1][i+1][0] = Imagedata[j][i][0];
            Reimage[j+1][i+1][1] = Imagedata[j][i][1];
            Reimage[j+1][i+1][2] = Imagedata[j][i][2];
        }
    }


	int i=1;
	int j=1;
	float error;
	while(true){
        if(i%2==1){
            if (Reimage[i][j][0] <= 128){
                OutputImage[i-1][j-1][0] = 0;
            }
            if(Reimage[i][j][0] > 128){
                OutputImage[i-1][j-1][0] = 255;
            }
            if(Reimage[i][j][1] <= 128){
                OutputImage[i-1][j-1][1] = 0;
            }
            if(Reimage[i][j][1] > 128){
                OutputImage[i-1][j-1][1] = 255;
            }
            if(Reimage[i][j][2] > 128){
                OutputImage[i-1][j-1][2] = 255;
            }
            if(Reimage[i][j][2] <= 128){
                OutputImage[i-1][j-1][2] = 0;
            }
            error = Reimage[i][j][0] - OutputImage[i-1][j-1][0];
            Reimage[i][j+1][0] += 7*error/16.0;
            Reimage[i+1][j+1][0] += 1*error/16.0;
            Reimage[i+1][j][0] += 5*error/16.0;
            Reimage[i+1][j-1][0]+= 3*error/16.0;

            error = Reimage[i][j][1] - OutputImage[i-1][j-1][1];
            Reimage[i][j+1][1] += 7*error/16.0;
            Reimage[i+1][j+1][1] += 1*error/16.0;
            Reimage[i+1][j][1] += 5*error/16.0;
            Reimage[i+1][j-1][1]+= 3*error/16.0;

            error = Reimage[i][j][2] - OutputImage[i-1][j-1][2];
            Reimage[i][j+1][2] += 7*error/16.0;
            Reimage[i+1][j+1][2] += 1*error/16.0;
            Reimage[i+1][j][2] += 5*error/16.0;
            Reimage[i+1][j-1][2]+= 3*error/16.0;

            if(j==width){
                    i+=1;
            }
            else{
                    j+=1;
            }
        }
        else{
            if(Reimage[i][j][0] <= 128){
                OutputImage[i-1][j-1][0] = 0;
            }
            if(Reimage[i][j][0] > 128){
                OutputImage[i-1][j-1][0] = 255;
            }
            if(Reimage[i][j][1] <= 128){
                OutputImage[i-1][j-1][1] = 0;
            }
            if(Reimage[i][j][1] > 128){
                OutputImage[i-1][j-1][1] = 255;
            }
            if(Reimage[i][j][2] <= 128){
                OutputImage[i-1][j-1][2] = 0;
            }
            if(Reimage[i][j][2] > 128){
                OutputImage[i-1][j-1][2] = 255;
            }
            error = Reimage[i][j][0] - OutputImage[i-1][j-1][0];
            Reimage[i][j-1][0] += 7*error/16.0;
            Reimage[i+1][j-1][0] += 1*error/16.0;
            Reimage[i+1][j][0] += 5*error/16.0;
            Reimage[i+1][j+1][0]+= 3*error/16.0;

            error = Reimage[i][j][1] - OutputImage[i-1][j-1][1];
            Reimage[i][j-1][1] += 7*error/16.0;
            Reimage[i+1][j-1][1] += 1*error/16.0;
            Reimage[i+1][j][1] += 5*error/16.0;
            Reimage[i+1][j+1][1]+= 3*error/16.0;

            error = Reimage[i][j][2] - OutputImage[i-1][j-1][2];
            Reimage[i][j-1][2] += 7*error/16.0;
            Reimage[i+1][j-1][2] += 1*error/16.0;
            Reimage[i+1][j][2] += 5*error/16.0;
            Reimage[i+1][j+1][2]+= 3*error/16.0;

            if(j==1){
                    i+=1;
            }
            else{
                    j-=1;
            }
        }
    if(i==height && j== width)
        break;
    }

    for(int i=0; i<height; ++i){
        for(int j=0; j<width; ++j){
            OutputImage[i][j][0] = 255- OutputImage[i][j][0];
            OutputImage[i][j][1] = 255- OutputImage[i][j][1];
            OutputImage[i][j][2] = 255- OutputImage[i][j][2];
        }
    }

	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] <<endl;		exit(1);	}	fwrite(OutputImage, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);


	cout<<"written"<<endl;
	return 0;
}

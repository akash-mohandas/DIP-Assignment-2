#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <cmath>
#include <fstream>using namespace std;

int getMBVQ(int r, int g, int b){
    if((r+g) >255){
        if((g+b)>255){
            if((r+g+b)>510){
                return 1;
            }
            else{
                return 2;
            }
        }
        else{
            return 3;
        }
    }
    else
        {
            if(!((g+b) >255)){
                if(!((r+g+b) > 255)){
                    return 4;
                }
                else{
                    return 5;
                }
            }
            else{
                return 6;
            }
        }
}

int getVertex(int n,int r, int g, int b){
    int vertex;
    switch(n){
        case 1: vertex = 1;
                if(b < 128){
                    if(b<=r){
                        if(b<=g){
                            vertex = 2;
                        }
                    }
                }
                if(g<128){
                    if(g<=b){
                        if(g<=r){
                            vertex = 4;
                        }
                    }
                }
                if(r<128){
                    if(r<=b){
                        if(r<=g){
                            vertex = 3;
                        }
                    }
                }
                break;
        case 2: vertex = 4;
                if(g>=b){
                    if(r>=b){
                        if(r>=128){
                            vertex = 2;
                        }
                        else{
                            vertex = 5;
                        }
                    }
                }
                if(g>=r){
                    if(b>=r){
                        if(b>=128){
                            vertex = 3;
                        }
                        else{
                            vertex = 5;
                        }
                    }
                }
                break;
        case 3: if(b>128){
                    if(r>128){
                        if(b>=g){
                            vertex = 4;
                        }
                        else{
                            vertex = 2;
                        }
                    }
                    else{
                        if(g>(b+r)){
                            vertex = 5;
                        }
                        else{
                            vertex = 4;
                        }
                    }
                }
                else{
                    if(r>=128){
                        if(g>=128){
                            vertex = 2;
                        }
                        else{
                            vertex = 6;
                        }
                    }
                    else{
                        if(r>=g){
                            vertex = 6;
                        }
                        else{
                            vertex = 5;
                        }
                    }
                }
                break;
        case 4: vertex = 8;
                if(b>128){
                    if(b>=r){
                        if(b>=g){
                            vertex = 7;
                        }
                    }
                }
                if(g>128){
                    if(g>=b){
                        if(g>=r){
                            vertex = 5;
                        }
                    }
                }
                if(r>128){
                    if(r>=b){
                        if(r>=g){
                            vertex = 6;
                        }
                    }
                }
                break;
        case 5: vertex = 5;
                if(r>g){
                    if(r>=b){
                        if(b<128){
                            vertex = 6;
                        }
                        else{
                            vertex = 4;
                        }
                    }
                }
                if(b>g){
                    if(b>=r){
                        if(r<128){
                            vertex = 7;
                        }
                        else{
                            vertex = 4;
                        }
                    }
                }
                break;
        case 6: if(b>128){
                    if(r>128){
                        if(g>=r){
                            vertex = 3;
                        }
                        else{
                            vertex = 4;
                        }
                    }
                    else{
                        if(g>128){
                            vertex = 3;
                        }
                        else{
                            vertex = 7;
                        }

                    }
                }
                else{
                    if(r>128){
                        if((r-g+b)>=128){
                            vertex = 4;
                        }
                        else{
                            vertex = 5;
                        }
                    }
                    if(g>=b){
                        vertex = 5;
                    }
                    else{
                        vertex = 7;
                    }
                }
                break;
    }
    return vertex;
}
int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 400;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 3; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}
    int height = 375;
    int width = 500;	// Allocate image data array	unsigned char Imagedata[height][width][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);

	unsigned char OutputImage[height][width][BytesPerPixel];
	float ***Reimage = new float**[height+2];
	float error;
	for(int i =0; i< height+2; ++i){
        Reimage[i] = new float* [width+2];
        for(int j=0; j< width+2; ++j){
            Reimage[i][j] = new float[3];
        }
	}
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
	while(true){
        int n = getMBVQ((int)Reimage[i][j][0], (int)Reimage[i][j][1],(int)Reimage[i][j][2]);
        int vertex = getVertex(n,(int)Reimage[i][j][0],(int)Reimage[i][j][1],(int)Reimage[i][j][2]);
        switch(vertex){
            case 8:     OutputImage[i-1][j-1][0] = 0;
                        OutputImage[i-1][j-1][1] = 0;
                        OutputImage[i-1][j-1][2] = 0;
                        break;
            case 7:     OutputImage[i-1][j-1][0] = 0;
                        OutputImage[i-1][j-1][1] = 0;
                        OutputImage[i-1][j-1][2] = 255;
                        break;
            case 5:     OutputImage[i-1][j-1][0] = 0;
                        OutputImage[i-1][j-1][1] = 255;
                        OutputImage[i-1][j-1][2] = 0;
                        break;
            case 6:     OutputImage[i-1][j-1][0] = 255;
                        OutputImage[i-1][j-1][1] = 0;
                        OutputImage[i-1][j-1][2] = 0;
                        break;
            case 3:     OutputImage[i-1][j-1][0] = 0;
                        OutputImage[i-1][j-1][1] = 255;
                        OutputImage[i-1][j-1][2] = 255;
                        break;
            case 4:     OutputImage[i-1][j-1][0] = 255;
                        OutputImage[i-1][j-1][1] = 0;
                        OutputImage[i-1][j-1][2] = 255;
                        break;
            case 2:     OutputImage[i-1][j-1][0] = 255;
                        OutputImage[i-1][j-1][1] = 255;
                        OutputImage[i-1][j-1][2] = 0;
                        break;
            case 1:     OutputImage[i-1][j-1][0] = 255;
                        OutputImage[i-1][j-1][1] = 255;
                        OutputImage[i-1][j-1][2] = 255;
                        break;
        }

        if(i%2==1){

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
    cout<<"loop terminated"<<endl;

	if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] <<endl;		exit(1);	}	fwrite(OutputImage, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);


	cout<<"written"<<endl;
	return 0;
}

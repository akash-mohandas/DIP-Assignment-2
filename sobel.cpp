#include <stdio.h>#include <iostream>#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <math.h>using namespace std;
float convolution(int,int,float [][3],float***);

float minimum(float*** arr){
    float minimum = arr[0][0][0];
    for(int i=0; i<321; ++i){
        for(int j=0; j<481; ++j){
            if(arr[i][j][0]< minimum)
                minimum = arr[i][j][0];
        }
    }
    return minimum;
}
float maximum(float*** arr){
    float maximum = arr[0][0][0];
    for(int i=0; i<321; ++i){
        for(int j=0; j<481; ++j){
            if(arr[i][j][0]> maximum)
                maximum = arr[i][j][0];
        }
    }
    return maximum;
}
int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Size = 256;	// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;		return 0;	}	// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 3; // default is grey image	}	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 5){			Size = atoi(argv[4]);		}	}
    int height = 321;
    int width = 481;
    // Allocate image data array	unsigned char Imagedata[height][width][BytesPerPixel];
    if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);	fclose(file);

	float kernalX[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
	float kernalY[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
	float ***Imagedata_gray = new float**[323];
	for(int i = 0; i < height+2; ++i) {
        Imagedata_gray[i] = new float*[483];
        for(int j = 0; j < width+2; ++j) {
            Imagedata_gray[i][j] = new float[1];
        }
	}
	//unsigned char Imagedata_gray[height][width][1];

    for(int i=0; i<height; ++i){
        for(int j=0; j<width; ++j){
            Imagedata_gray[i][j][0] = (0.3*Imagedata[i][j][0]+0.59*Imagedata[i][j][1]+0.11*Imagedata[i][j][2])/3.0;
        }
    }
	float ***Reimage = new float**[323];
	for(int i = 0; i < height+2; ++i) {
        Reimage[i] = new float*[483];
        for(int j = 0; j < width+2; ++j) {
            Reimage[i][j] = new float[1];
        }
	}

	for(int j=0; j<1; ++j){
        for(int i=1; i<1+width; ++i){
            Reimage[j][i][0] = Imagedata_gray[1-j][i-1][0];
        }
	}
	cout<<"first"<<endl;
	for(int j=0; j<1; ++j){
        for(int i=1; i<1+width; ++i){
            Reimage[height+j+1][i][0] = Imagedata_gray[height-j-2][i-1][0];
        }
	}
    cout<<"second"<<endl;
	for(int i=0; i<1; ++i){
        for(int j=1; j<1+height; ++j){
            Reimage[j][i][0] = Imagedata_gray[j-1][1-i][0];
        }
	}

	for(int i=0; i<1; ++i){
        for(int j=1; j<1+height; ++j){
            Reimage[j][width+1+i][0] = Imagedata_gray[j-1][width-i-2][0];
        }
	}
	cout<<"continued"<<endl;
	Reimage[0][0][0] = Reimage[0][2][0];
	Reimage[0][width+1][0] = Reimage[0][width-1][0];
	Reimage[height+1][0][0] = Reimage[height+1][2][0];
	Reimage[height+1][width+1][0] = Reimage[height+1][width-1][0];

    for(int j=0; j<height; ++j){
        for(int i=0; i<width; ++i){
            Reimage[j+1][i+1][0] = Imagedata_gray[j][i][0];
        }
    }
	// Read image (filename specified by first argument) into image data matrix
	float ***ImageX = new float**[height];
	for(int i = 0; i < height; ++i) {
        ImageX[i] = new float*[width];
        for(int j = 0; j < width; ++j) {
            ImageX[i][j] = new float[1];
        }
	}
    float ***ImageY = new float**[height];
	for(int i = 0; i < height; ++i) {
        ImageY[i] = new float*[width];
        for(int j = 0; j < width; ++j) {
            ImageY[i][j] = new float[1];
        }
	}
	cout<<0<<endl;
	unsigned char EdgeImage[height][width][1];	float ***Grad = new float**[height];
	for(int i = 0; i < height; ++i) {
        Grad[i] = new float*[width];
        for(int j = 0; j < width; ++j) {
            Grad[i][j] = new float[1];
        }
	}


	//unsigned char EdgeImage[height][width][1];
    cout<<"yes"<<endl;
    float value;
	for(int i=0; i< height; ++i){
        for(int j=0; j<width; ++j){
            //cout<<0<<endl;
            ImageX[i][j][0] = convolution(i,j,kernalX,Reimage);
            //cout<<ImageX[i][j][0]<<endl;
            ImageY[i][j][0] = convolution(i,j,kernalY,Reimage);
            //cout<<ImageY[i][j][0]<<endl;
            /*value = ceil(sqrt(pow(ImageX[i][j][0],2) + pow(ImageY[i][j][0],2)));
            //cout<<value<<endl;
            EdgeImage[i][j][0] = (unsigned char) value;
            if(EdgeImage[i][j][0]>165){
                EdgeImage[i][j][0] = 255;
            }
            else{
                EdgeImage[i][j][0] = 0;
            }*/
        }
	}
	float min1 = minimum(ImageX);
	float max1 = maximum(ImageX);
	float min2 = minimum(ImageY);
	float max2 = maximum(ImageY);


    unsigned char ImageX_norm[height][width][1];
    unsigned char ImageY_norm[height][width][1];
    unsigned char gradientMagnitude[height][width][1];
	for(int i=0; i< height; ++i){
        for(int j=0; j< width; ++j){
            ImageX_norm[i][j][0] = (unsigned char)((ImageX[i][j][0] - min1)*255/(max1 - min1));
            ImageY_norm[i][j][0] = (unsigned char)((ImageY[i][j][0] - min2)*255/(max2 - min2));
            value = ceil(sqrt(pow(ImageX[i][j][0],2) + pow(ImageY[i][j][0],2)));
            //cout<<value<<endl;
            EdgeImage[i][j][0] = (unsigned char) value;
            gradientMagnitude[i][j][0] = (unsigned char) value;
            Grad[i][j][0] = value;
            /*value/=255;
            if(value>0.1){
                EdgeImage[i][j][0] = 0;
            }
            else{
                EdgeImage[i][j][0] = 255;
            }
            */
        }
	}
    float minim = minimum(Grad);
	float maxim = maximum(Grad);

    unsigned char Grad_save[height][width][1];
    for(int i=0; i< height; ++i){
        for(int j=0; j<width; ++j){
            Grad_save[i][j][0] = (unsigned char)((Grad[i][j][0] - minim)*255/(maxim - minim));
        }
    }

	int hist[256]={0};
	float cum_hist[256];
	for(int i=0; i< height; ++i){
        for(int j=0; j< width; ++j){
            hist[EdgeImage[i][j][0]]+=1;
        }
	}

	cum_hist[0] = hist[0];
	for(int i=1; i<256; ++i){
        cum_hist[i]=cum_hist[i-1] + hist[i];
	}
	for(int i=0; i<256; ++i){
        cum_hist[i]/=(float)cum_hist[255];
	}
	float thresh;
    for(int i=0; i<256; ++i){
        if(cum_hist[i]>=0.85){
            thresh = i;
            break;
        }
	}
	for(int i=0; i<height; ++i){
        for(int j=0; j<width; ++j){
            if (EdgeImage[i][j][0] >= thresh){
                EdgeImage[i][j][0] = 0;
            }
            else{
                EdgeImage[i][j][0] = 255;
            }
        }
	}

	cout<<"converted"<<endl;

    if (!(file=fopen("Grad.raw","wb"))) {		cout << "Cannot open file: " << "Grad.raw" << endl;		exit(1);	}	fwrite(Grad_save, sizeof(unsigned char), (height)*(width)*1, file);	fclose(file);

    if (!(file=fopen("imageX.raw","wb"))) {		cout << "Cannot open file: " << "imageX.raw" << endl;		exit(1);	}	fwrite(ImageX_norm, sizeof(unsigned char), (height)*(width)*1, file);	fclose(file);

	if (!(file=fopen("gradientMagnitude.raw","wb"))) {		cout << "Cannot open file: " << "gM.raw" << endl;		exit(1);	}	fwrite(gradientMagnitude, sizeof(unsigned char), (height)*(width)*1, file);	fclose(file);

	if (!(file=fopen("imageY.raw","wb"))) {		cout << "Cannot open file: " << "imageY.raw"<< endl;		exit(1);	}	fwrite(ImageY_norm, sizeof(unsigned char), (height)*(width)*1, file);	fclose(file);

    if (!(file=fopen(argv[2],"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(EdgeImage, sizeof(unsigned char), (height)*(width)*1, file);	fclose(file);
	cout<<"written"<<endl;
	return 0;

}

float convolution(int i, int j, float kernel[][3], float*** image){
    float pix = 0.0;
    for(int k=i; k<i+3; ++k){
        for(int l=j; l<j+3; ++l){
            pix+= (image[k][l][0] * kernel[k-i][l-j]);
            //cout<<pix<<endl;
        }
    }
    return pix;
}

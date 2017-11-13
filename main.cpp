#include<iostream>
#include <vector>
#include <string>
#include "bitmap.h"

using namespace std;

/*
* The function reads input from the user. It either reads max of 10 files or till done is entered.
*
* Input: vector of strings
* Output: vector of strings
*/
void readUserInput(vector<string>& fileNames);

/*
* The function removes all the invalid files which has been entered by user.
* It checks if each file exists or is a valid bmp file.
* It takes width and height of first file and
compares each file with that and if there is any difference, rejecty that file as well.
*
* Input: vector of all string of file Path.
* Output: vector of valid strings of file Path
*/
void removeInvalidFiles(vector<string>& fileNames);

/*
* The function process the files by reading each file and merging the content into a final file.
* After merging, it takes average of each pixel of R, G and B.
*
* Input: vector of valid strings of files.
* Output: void
*/
void doProcessing(vector<string>& fileNames);

/*
* Writes output file of the merged PixelMatrix.
*
* Input: PixelMatrix.
* Output: void
*/
void writeOutput(PixelMatrix pixels);

int main() {
//Variable declaration.
vector<string> fileNames;

//Processing.
readUserInput(fileNames);
removeInvalidFiles(fileNames);
doProcessing(fileNames);
return 0;
}

void readUserInput(vector<string>& fileNames) {
string input;
while(fileNames.size() <= 10) {
cout << "Enter a file name for creating a composite bitmap: ";
cin >> input;
if(input == "DONE" || input == "done") {
break;
}
fileNames.push_back(input);
}
}

void removeInvalidFiles(vector<string>& fileNames) {
bool firstValidFound = false;
bool validBmpFile;
int validWidth = 0, validHeight = 0, width = 0, height = 0;;
PixelMatrix pixels;

for (std::vector<string>::iterator it = fileNames.begin() ; it != fileNames.end();) {
Bitmap image;
validBmpFile = false;
image.open(*it);
validBmpFile = image.isImage();
if(!validBmpFile) {
cout << "Not a valid bmp file. Removed " << *it << endl;
fileNames.erase(it);
} else {
pixels = image.toPixelMatrix();
width = pixels.size();
height = pixels[0].size();
cout << "width:" << width << " height: " << height << endl;
if(!firstValidFound) {
firstValidFound = true;
validWidth = width;
validHeight = height;
}
if(height != validHeight || width != validWidth) {
cout << "Width/Height doesn't match the first file found. Removed " << *it << endl;
fileNames.erase(it);
} else {
++it;
}
}
}
}

void doProcessing(vector<string>& fileNames) {
if(fileNames.size() < 2) {
cout << "Exit. The number of valid BMP files is less than 2. So exiting the program." << endl;
} else {
vector <vector <Pixel> > bmpImg, finalBmp;
Pixel rgb, rgbFinal;

//Array for imageBitMap
Bitmap imageBitMapArr[fileNames.size()];

//Load each image.
for(int i = 0; i < fileNames.size(); i++) {
imageBitMapArr[i].open(fileNames[i]);
}
finalBmp = imageBitMapArr[0].toPixelMatrix();
cout << fileNames[0] << " has been processed. " << endl;

for(int index = 1; index < fileNames.size(); index++) {
bmpImg = imageBitMapArr[index].toPixelMatrix();
for(int i = 0; i < bmpImg.size(); i++) {
for(int j = 0; j < bmpImg[i].size(); j++) {
rgb = bmpImg[i][j];
rgbFinal = finalBmp[i][j];
rgbFinal.red += rgb.red;
rgbFinal.green += rgb.green;
rgbFinal.blue += rgb.blue;
finalBmp[i][j] = rgbFinal;
}
}
cout << fileNames[index] << " has been processed. " << endl;
}

for(int i = 0; i < finalBmp.size(); i++) {
for(int j = 0; j < finalBmp[i].size(); j++) {
rgbFinal = finalBmp[i][j];
rgbFinal.red = rgbFinal.red / fileNames.size();
rgbFinal.green = rgbFinal.green / fileNames.size();
rgbFinal.blue = rgbFinal.blue / fileNames.size();
finalBmp[i][j] = rgbFinal;
}
}
writeOutput(finalBmp);
}
}

void writeOutput(PixelMatrix pixels) {
Bitmap finalImage;
finalImage.fromPixelMatrix(pixels);
finalImage.save("composite-halketbi1.bmp");
}

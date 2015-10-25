#include "../LeapSDK/include/Leap.h"
#include "Controls.h"
#include <iostream>
#include <vector>
#include <typeinfo>
#include <cmath>
#include <unistd.h>

using namespace Leap;

std::vector<Frame> fetchData(std::string str){
    std::vector<Frame> deserializedFrames;
    std::string inFilename = str; std::ifstream in(inFilename, std::fstream::in);
    std::string contents;
    if (in)
    {
        in.seekg(0, std::ios::beg);
        long nextBlockSize = 0;
        in >> nextBlockSize;
        while (!in.eof()){
            contents.resize(nextBlockSize);
            in.read(&contents[0], nextBlockSize);
            Frame newFrame;
            newFrame.deserialize(contents);
            if(newFrame.isValid()) deserializedFrames.push_back(newFrame);
            in >> nextBlockSize;
        }
        in.close();
    }
    else if (errno){
        std::cout << "Error: " << errno << std::endl;
        std::cout << "Couldn't open " << inFilename << " for reading." << std::endl;
    }
    return deserializedFrames;
}

Vector PositionDifferences(const Vector &self, const Vector &other){
    float a = std::abs((self[0] - other[0]) / self[0]);
    float b = std::abs((self[1] - other[1]) / self[1]);
    float c = std::abs((self[2] - other[2]) / self[2]);
    return Vector(a,b,c);
}

std::vector<Vector> FrameDifferences(std::vector<Frame> &self, const std::vector<Frame> &other){
    std::vector<Vector> result;
    for (int i = 0; i < int(self.size()) && i < int(other.size()); i++){
        Vector self_Vector = self[i].hands().rightmost().palmPosition();
        Vector other_Vector = other[i].hands().leftmost().palmPosition();
        result.push_back(PositionDifferences(self_Vector, other_Vector));
    }
    return result;
}

bool calculateAccuracy(std::vector<Vector> &vec){
    const float MOE = .3;
    for (int i = 0; i < int( vec.size()); i++){
        for(int j = 0; j < 2; j++){
            if(vec[i][j] > MOE){
                return false;   
            }
        }
    }
    return true;
}

void shiftVector(Vector vec, Vector &shifter){
    vec += shifter;
}

void shiftFrame(std::vector<Frame> &vec, Vector &shifter){
    for (std::vector<Frame>::iterator it = vec.begin(); it != vec.end(); it++){
        shiftVector(it->hands().rightmost().palmPosition(), shifter);
        shiftVector(it->hands().leftmost().palmPosition(), shifter);
    }
}

void handPosNormalized(std::vector<Frame> &self, std::vector<Frame> &other){
    Vector righthand = self[20].hands().rightmost().palmPosition() - other[20].hands().rightmost().palmPosition();
    Vector lefthand = self[20].hands().leftmost().palmPosition() - other[20].hands().leftmost().palmPosition();
    Vector shifter = righthand - lefthand;
    shiftFrame(other, shifter);
}



void writeData(){
    getData_listener listener;
    Controller controller;
    controller.addListener(listener);

    std::cin.get();

    controller.removeListener(listener);
}

int main(int argc, char* *argv){
    writeData();
    std::string filename;
    std::cout << "enter" << std::endl;

    std::cin >> filename;
    std::vector<Frame> vector_frames1;
    vector_frames1 = fetchData(filename);

    std::cin >> filename;
    std::vector<Frame> vector_frames2;
    vector_frames2 = fetchData(filename);

    handPosNormalized(vector_frames1, vector_frames2);
    std::vector<Vector> Differences = FrameDifferences(vector_frames1, vector_frames2);
    std::cout << calculateAccuracy(Differences) << std::endl;
    for (std::vector<Vector>::iterator it = Differences.begin(); it != Differences.end(); it++){
        std::cout << it->x << std::endl;
        std::cout << it->y << std::endl;
        std::cout << it->z << std::endl;
        usleep(1000);
    }
}











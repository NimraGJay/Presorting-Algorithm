#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h>
#include <algorithm>
#include<bits/stdc++.h>
#include <map>
#include <utility>
#include <set>

using namespace std;

// ============= User Defined types ==================================
class Point{
	
private:	
	int x;
	int y;
	//double quality;
public:
	Point(){
		x=0;
		y=0;

	}
	Point(int xx, int yy){
		x=xx;
		y=yy;
		
	}
	//getter+setters
	void setx(int xx){
		x=xx;
	}
	void sety(int yy){
		y=yy;
	}
	double getSlope(Point p){
		if(this->x!=p.x && this->y!=p.y){
			return (double)(double(this->y-p.y)/double(this->x-p.x));
		}else if(this->x==p.x){
			return INT_MAX;
		}else{
			return INT_MIN;
		}
	}	
	void print(){
		cout<<"(" <<x<<","<<y<<")";
	}
	bool operator == (const Point &p){
	if(this->x==p.x && this->y==p.y )
		return true;
	else
		return false;
	}
	bool operator < (  Point &p){
	if(this->x<=p.x)
	{
		if(this->y>=p.y)
		return 1;
		else return 0;
	}
	return 0;
	}
	
	friend ostream& operator<<(ostream& os, const Point &p);
	
};

ostream& operator<<(ostream& os, const Point &p)
{
   os<<"(" <<p.x<<","<<p.y<<")";
    return os;
}


// ============= Variables ===========================================

typedef vector<Point> PointVector;
char cTextFileName[]  = "RI/RI10000.txt";
int gNumRecs=0;
PointVector PointsFromFile; 
vector<PointVector> ColinearPoints;

// ============= Functions ===========================================


bool ReadFile(char FileName[]){
	ifstream fin;
	fin.open(FileName);
	int counter;
	if(!fin.good()){
		return false;	
	}else{
		fin>>gNumRecs;
		counter=gNumRecs;
		int x,y;
	
		while (counter>0){
			fin>>x;
			fin>>y;
//			cout<<"("<<x<<","<<y<<")\t";
			Point pTemp(x,y);
//			pTemp.print();
//			cout<<"\n";
			PointsFromFile.push_back(pTemp);
			counter--;
		}
	cout<<gNumRecs<<endl;
	}
	
	fin.close();

}
bool checkIfAllExists(vector<Point> vec1 , vector<Point> vec2){
	
	//int counter=0;
	vector<Point>::iterator it;
	for(int i = 0 ; i < vec2.size(); i++){
		it= find(vec1.begin(), vec1.end(),vec2[i]);
		//cout<<i;vec2[i].print();cout<<"\n";
		if(it==vec1.end()){
		//	cout<<"Check this out"<<i;vec2[i].print();cout<<"\n";
			return false;
		}
	}
	return true;
	
}
bool check(PointVector &temp, vector<PointVector> &pointArrays ){

	for(int i =0 ; i < pointArrays.size(); i++){
		if(temp.size()==pointArrays[i].size()){
			if(checkIfAllExists(pointArrays[i],temp)){
			
				return false;
			};
			
		}else if (pointArrays[i].size()>temp.size()){
			if(checkIfAllExists(pointArrays[i],temp)){
				return false;
			};
			
		}else if (temp.size()>pointArrays.size()){
			if(checkIfAllExists(temp,pointArrays[i])){
				swap(temp,pointArrays[i]);
				return false;
			};
		}
		
	}
	return true;
}
void FindColinearPointsBruteForce(PointVector p){
int size=p.size();
double slope1, slope2, slope3;
PointVector pTemp;
bool proceed;
for(int i = 0 ; i < size ; i++){
	for(int j = i+1; j < size; j++){
		slope1=slope2=slope3=0.0;
		if(p[i]==p[j]) continue;
		slope1=p[i].getSlope(p[j]);
		for(int k= j+1; k < size; k++){
			if(p[j]==p[k]) continue;
			slope2=p[j].getSlope(p[k]);
			if(slope1==slope2){
				pTemp.push_back(p[i]);
				pTemp.push_back(p[j]);
				pTemp.push_back(p[k]);
				for(int l = k+1; l<size; l++){
					if(p[k]==p[l]) continue;
					slope3= p[k].getSlope(p[l]);
					if(slope2==slope3){
						pTemp.push_back(p[l]);
					}	
				}
				if(pTemp.size()>=4){
					proceed=check(pTemp,ColinearPoints);
					if(proceed==true){
						ColinearPoints.push_back(pTemp);
					}
				}		
			}
			pTemp.clear();
			}	
		}	
	}
}

void PrintVectorOfPoints(PointVector &p){
	for(int i =0 ; i < p.size(); i++){
		p[i].print();
		if(i!=p.size()-1)
			cout<<"::";
	}
 cout<<endl;
}
void PrintColinearPoints(vector<PointVector> ColinearPoints){
	for(int i = 0 ; i<ColinearPoints.size();i++){
	//	cout<<"Array: "<<i<<" of size: "<<ColinearPoints[i].size()<<" :";
		PrintVectorOfPoints(ColinearPoints[i]);
		cout<<endl;
	}
}

// ============= Main Function =======================================

int main(int argc, char** argv) {
	ReadFile(cTextFileName);

	FindColinearPointsBruteForce(PointsFromFile);
	
	PrintColinearPoints(ColinearPoints);
	cout<<"colinear size: "<<ColinearPoints.size();
	cout<<"\n";


}




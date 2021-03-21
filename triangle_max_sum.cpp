#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// in this program, The triangle input is taken from a text.
//summation is done from the leaves towards to the root.
// the case that all the numbers in a row are prime numbers is considered, the program goes to the at the end of the pyramid as much as possible. 

bool nonprime(int val){
	if(val<=1)
		return true;
	else{
		for(int i=2;i<=val/2;i++){
			if(val%i==0)
				return true;
		}
		return false;
	}
}
void findmaxsum(vector<vector<int>> &formedmatrix,int&size,bool&repeat){
	vector<vector<int>> checked(size,vector<int>(size,0));
	//i created checked matrix since we can get a prime number as sum of numbers in this case it should not be taken as prime number, it was not originally
	//if checked in that place is 1, it denotes that it is a result of a sum and dont check whether it is prime or not.
	repeat=false;
	int temp;
	bool finish=false;
	for (int i=size-1;i>=0;i--){
		int j=0;
		int notentered=0;
		while(j<i){
			if(checked[i][j]==1 && checked[i][j+1]==1){ // no need to check whether they are prime or not.
				temp=max(formedmatrix[i][j],formedmatrix[i][j+1]);
				if(i!=0){
					int val=formedmatrix[i-1][j];
					if(nonprime(formedmatrix[i-1][j])){
						formedmatrix[i-1][j]=formedmatrix[i-1][j]+temp;
						checked[i-1][j]=1;
					}
					else
						notentered++;
				}
			}
			else if(checked[i][j]==0 || checked[i][j+1]==0){
				if(checked[i][j]==0 && checked[i][j+1]==0){
					if(nonprime(formedmatrix[i][j]) && nonprime(formedmatrix[i][j+1])){
						temp=max(formedmatrix[i][j],formedmatrix[i][j+1]);
					}
					else if(nonprime(formedmatrix[i][j])){
						temp=formedmatrix[i][j];
					}
					else if(nonprime(formedmatrix[i][j+1])){
						temp=formedmatrix[i][j+1];
					}
					if(i!=0){
						if(nonprime(formedmatrix[i-1][j])){
							formedmatrix[i-1][j]=formedmatrix[i-1][j]+temp;
							checked[i-1][j]=1;
						}
						else
							notentered++;
	 				}
				}
				else if( checked[i][j]==1 ){
					if(nonprime(formedmatrix[i][j+1])){
						temp=max(formedmatrix[i][j],formedmatrix[i][j+1]);
					}
					else
						temp=formedmatrix[i][j];
					if(i!=0){
						if(nonprime(formedmatrix[i-1][j])){
							formedmatrix[i-1][j]=formedmatrix[i-1][j]+temp;
							checked[i-1][j]=1;
						}
						else
							notentered++;
					}
				}
				else if(checked[i][j+1]==1){
					if(nonprime(formedmatrix[i][j])){
						temp=max(formedmatrix[i][j],formedmatrix[i][j+1]);
					}
					else
						temp=formedmatrix[i][j+1];
					if(i!=0){
						if(nonprime(formedmatrix[i-1][j])){
							formedmatrix[i-1][j]=formedmatrix[i-1][j]+temp;
							checked[i-1][j]=1;
						}
						else
							notentered++;
					}
				}
			}
			if(notentered==i){ // it means all of them in that nodes are prime the path not avaliable.
				size=i-1;
				repeat=true;
			}
			j++;
		}
		if(repeat)
			break;
	}
}
int main(){
	ifstream matrixfile;
	string matrixname;
	cout<<"Please enter file name:";
	cin>>matrixname;
	string line;

	matrixfile.open(matrixname.c_str()); 
	int count=0;
	if (!matrixfile.fail()){//if it is opened
		while(!matrixfile.eof()){//if the end of file is not reach, continue to read the file.
			getline(matrixfile,line);
			count++;// count of the line number 
		}
	}
	matrixfile.close();
	matrixfile.clear();
	matrixfile.open(matrixname.c_str());

	int rowcount=0;
	int value;
	vector<vector<int>> formedmatrix(count,vector<int>(count,0));//default matrix is formed
	if(!matrixfile.fail()){
		while(!matrixfile.eof()){
			getline(matrixfile,line);
			istringstream iss(line);
			int colcount=0;
			while(iss>>value){
				formedmatrix[rowcount][colcount]=value;
				colcount++;
			}
			rowcount++;
		}
	}
	int size=formedmatrix.size();
	bool repeat=false;
	findmaxsum(formedmatrix,size,repeat);
	while(repeat==true)
		findmaxsum(formedmatrix,size,repeat);
	int maxsum=formedmatrix[0][0];
	cout<< " The maximum sum of the numbers according to the rules is " <<maxsum<<endl;
	return 0;
}
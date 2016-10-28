#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <windows.h>

using namespace std;

double get_cpu_time() {
	FILETIME a, b, c, d;
	if (GetProcessTimes(GetCurrentProcess(), &a, &b, &c, &d) != 0) {
		unsigned long long kernel = c.dwLowDateTime | ((unsigned long long)c.dwHighDateTime << 32);
		unsigned long long user   = d.dwLowDateTime | ((unsigned long long)d.dwHighDateTime << 32);
		return (double)(kernel + user) * 0.0000001;
	}
	else { return 0; } // TODO: Handle error
}
template <typename Comparable,typename T>
void merge(std::vector<Comparable> & weight,std::vector<T> & width, std::vector<Comparable> & tmpArray, std::vector<T> & tmpArray2, size_t leftPos, size_t rightPos, size_t rightEnd)
{
	size_t leftEnd = rightPos - 1;
	size_t tmpPos = leftPos;
	size_t numElements = rightEnd - leftPos + 1;
	//std::vector<Comparable> tmpArray2(a.size());


	// Main loop
	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if (weight[leftPos] <= weight[rightPos])
		{
            tmpArray2[tmpPos] = std::move(width[leftPos]);
			tmpArray[tmpPos++] = std::move(weight[leftPos++]);



		}
		else
		{
		    tmpArray2[tmpPos] = std::move(width[rightPos]);
			tmpArray[tmpPos++] = std::move(weight[rightPos++]);

		}
	}
	while (leftPos <= leftEnd) // Copy rest of first half
	{
	    tmpArray2[tmpPos] = std::move(width[leftPos]);
		tmpArray[tmpPos++] = std::move(weight[leftPos++]);

	}
	while (rightPos <= rightEnd) // Copy rest of right half
	{
	    tmpArray2[tmpPos] = std::move(width[rightPos]);
		tmpArray[tmpPos++] = std::move(weight[rightPos++]);

	}

	// Copy tmpArray back
	for (size_t i = 0; i < numElements; ++i, --rightEnd) {
        weight[rightEnd] = std::move(tmpArray[rightEnd]);

        width[rightEnd] = std::move(tmpArray2[rightEnd]);
	}
}

template <class Comparable, typename T>
void insertionSort(std::vector<Comparable> & weight,std::vector<T> & width, size_t left, size_t right)
{
	for (size_t i = left+1; i <= right; ++i)
	{
		Comparable temp = std::move(weight[i]);
		T temp2 = std::move(width[i]);
		size_t j;
		for (j = i; j > left && temp < weight[j - 1]; --j){
			weight[j] = std::move(weight[j - 1]);
			width[j] = std::move(width[j - 1]);

		}
		width[j] = std::move(temp2);
        weight[j] = std::move(temp);


	}
}
template <typename Comparable, typename T>
void timSort(std::vector<Comparable> & weight,std::vector<T> & width, std::vector<Comparable> & tmpArray, std::vector<T> & tmpArray2, size_t left, size_t right)
{
	if (left  < right)
	{
		size_t center = (left + right) / 2;
		timSort(weight,width, tmpArray, tmpArray2, left, center);
		timSort(weight,width, tmpArray, tmpArray2, center + 1, right);
		merge(weight,width, tmpArray, tmpArray2, left, center + 1, right);
	}
	else
	{
		insertionSort(weight,width, left, right);
	}
}
    template <typename Comparable, typename T>
void timSort(std::vector<Comparable> & weight, std::vector<T> & width)
{ww

	std::vector<Comparable> tmpArray(weight.size());
	std::vector<T> tmpArray2(names.size());
	timSort(weight,width, tmpArray, tmpArray2, 0, weight.size() - 1);

}
  template <typename Comparable, typename T>
void packageMerge(std::vector<Comparable> & weight, std::vector<T> & width)
{

    //sort widths in increasing value by weight
    timsort(weight,width);

    for(int i = weight.size();i>=1;i--)
    {
        //if the length of the vector is odd then remove the heaviest item
        if(weight.size()%2==1)
        {
            width.remove(weight.size()-1);
            weight.remove(weight.size-1);
        }
        for(int i = 0;i<=weight.size()-1;i+=2)
        {
            //packages the two lowest weights into a package
            std::vector<Comparable> A(grades.size());
            A.push_back(weight[i]);
            A.push_back(weight[i+1]);

            //puts the package into a list
            std::vector<Comparable> B(A.size()/2);
            B.push_back(A);
        }
    }

}


int main()
{

    vector <double> width;
    vector <double> weight;

    string words;
    cout<<"Enter the name file."<<endl;

    string input;
    cin>>input;
    ifstream textFile(input.c_str());

    double numbers;
    cout<<"Enter the data file."<<endl;
    string input2;
    cin>>input2;
    ifstream textFile2(input2.c_str());


while(textFile >> words){

    width.push_back(words);

}
while(textFile2 >> numbers){

    weight.push_back(numbers);

}


double begin=get_cpu_time();

packageMerge(weight,width);


double end = get_cpu_time();

double elapsedSecs = end-begin/1000;



cout<<"Time running: "<<elapsedSecs<<endl;

for(int i = 0;i<names.size();i++){
cout<<width[i]<<": ";
cout<<weight[i]<<endl;

}
cout<<"names size: "<<names.size()<<endl;

cout<<"grades size: "<<grades.size()<<endl;
}

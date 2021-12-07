#include <iostream>



int main(){
    int arr[10000];
    for(int i = 0; i < 10000; i++){
        arr[i] = rand()%100;
    }

    int count;
    for(int i=0;i<1000;i+=2){

        for(int j = count; j < count + 10; j++){
            std::cout<<"("<<arr[j]<<","<<arr[j+1]<<")";
        }
        std::cout<<std::endl;
        count+=10;
    }
    return 0;
}
    


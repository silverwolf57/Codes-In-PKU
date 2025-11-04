#include <iostream>

int fibonacci(int n){
    if(n==1)return 1;
    if(n==2)return 1;
    return fibonacci(n-1)+fibonacci(n-2);
}

int main() {
	int n;
	std::cin>>n;
	for(int i=0;i<n;i++){
	    int a;
	    std::cin>>a;
	    std::cout<<fibonacci(a)<<std::endl;
	}
	return 0;
}

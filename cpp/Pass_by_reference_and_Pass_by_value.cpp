// Pass by reference and pass by value example using sum function
#include <bits/stdc++.h>
using namespace std;

//The addresses of the variables a and b are passed
int sum_by_reference(int *a,int *b){
	return *a + *b; // '*' is a dereference operator
}

//The values of the variables a and b are passed
int sum_by_value(int a, int b){
	return a + b;
}

int main(){
	int a=3,b=4;
	int s_ref = sum_by_reference(&a,&b);
	int s_val = sum_by_value(a,b);
	cout << "The sum of " << a << " and " << b << " from sum_by_reference and sum_by_value are " << s_ref << " " << s_val << endl;
	return 0;
}

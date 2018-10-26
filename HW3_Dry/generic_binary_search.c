#include <stdio.h>

#define FIRST 0
#define LAST(e) ((e)-1)
#define LEFT(e) ((e)-1)
#define RIGHT(e) ((e)+1)
#define MIDDLE(e,w) (((e)+(w))/2)

typedef void* Element;

typedef int (*CompFunc) (Element e1,Element e2);
/*Gets 2 elements and make comparison between them
 * if e1 < e2 return -1,  if e1=e2 return 0 if e1>e2 return 1*/

int binaryFind(Element *elements,int size,Element find_me,CompFunc cmp) {
/*Gets an element to find and sorted elements array
 * using binary search looking for the element in the array,
 * if the element founded return it's index if not return -1*/
    int low=FIRST;
    int high=LAST(size);
    while(low <= high){
        int mid=MIDDLE(low,high);
        int result=cmp(find_me,elements[mid]);
        if(result<0){
            high=LEFT(mid);
            //choosing left side of the current array
        }
        else if(result>0)
            low=RIGHT(mid);
            //choosing right side of the current array
        else
            return mid;
        //element is found return it's index
    }
    return -1;//here when element is not found
}

int intCmp(void *e1,void *e2 ){
    int a=*(int*)e1;
    int b=*(int*)e2;
    return -1*(a<b) + 0*(a==b) + 1*(a>b);
}

int main() {
    int n=9;
    int arr[]={2,6,7,8,10,11,12,40,50};
    Element elements[n];
    for(int i=0;i<n;i++){
        elements[i]=&arr[i];
    }
    int find_me=9;

    printf("Results: %d\n", binaryFind(elements, n, &find_me, intCmp));
    return 0;
}
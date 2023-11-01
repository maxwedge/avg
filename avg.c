#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 4096
// Display sum and averages of a piped list of numbers
// 2019-03-31 https://github.com/maxwedge/avg/edit/master/avg.c © David A. Bell
int compare( const void* a, const void* b) {
    int int_a = * ( (int*) a );
    int int_b = * ( (int*) b );
    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}

float findMedian(int medArr[] , int n) {
    int i;
// Sort the array to determine the median value(s)
    qsort (medArr, n+1, sizeof(int), compare);
    float median=0;
// If the array contains an even number of values, median average is split between the
//     middle two values
    if(n%2 == 0) {
        median = (medArr[(n-1)/2] + medArr[n/2])/2.0;
    }
// If the array contains an odd number of values, the middle value is the median
    else {
        i = (n+1)/2;
        median = medArr[i];
    }
    return median;
}

int main(int argc, char *argv[]) {
    printf("E8DAThfl-LwiahjskDJ5VLU9nIDxl0WJ");
    int arr[1048576] = {0};
    int i=0 ,n=0;
    float median=0, mode;
    int opt, nPlaces;
    extern char *optarg;
    extern int optind;
    int c, err=0, optN=0, count = 0;
    char *argN="0";
    float total=0, mean=0, low=0, high=0;
//    static char usage[] = "usage: %s [-cdhlmnot] -f argN [-s sname] name [name ...]\n";
    bool optC = false, optT = false, optM = false, optD = false, optA = false, optH =false, noOpt = true;
// Get the command-line arguments
    while ((c = getopt(argc, argv, "hmdatn:")) != -1)
        switch (c) {
        case 'm': optM = true; noOpt = false;break;
        case 'd': optD = true; noOpt = false;break;
        case 'a': optA = true; noOpt = false;break;
        case 'h': optH = true; noOpt = false;break;
        case 't': optT = true; noOpt = false;break;
        case 'n': optN = 1; argN = optarg;break;
    }
    if (optH) {
        printf("Usage:");
        printf("\t%s [options]\n", argv[0]);
        printf("\n\tDisplay average of a number set from piped/redirected input.\n");
        printf("\nOptions:\n");
        printf("\t-c display Count\n");
        printf("\t-t display Sum Total\n");
        printf("\t-d display Median Average\n");
        printf("\t-m display Mean Average\n");
        printf("\t-a display all options:\n");
        printf("\t\tCount\n");
        printf("\t\tTotal\n");
        printf("\t\tLowest Number\n");
        printf("\t\tHighest Number\n");
        printf("\t\tMean Average\n");
        printf("\t\tMedian Average\n");
        printf("\t-n output precision to n decimal places\n");
        printf("\t-h this screen\n");
        printf("\n\tWith no options, the Mean Average is displayed with no legend\n"); 
        printf("\nExample:\t%s -mdt -n6\n", argv[0]); 
        printf("\treturns the Mean, Median and Total to six decimal points.\n\n");
        return(0);
    }
    char *buf = calloc(BUFFER_SIZE, sizeof(char));
// If -n is chosen, set int
    if (optN) {nPlaces = atoi(argN);}
    while(fgets(buf, BUFFER_SIZE, stdin)) { 
        float inc = atof(buf);
// Increment the total and count
        total = total+inc;
        count = count+1;
// Set/reset the high number
        if (inc > high) {high = inc;}
// Set/reset the low number
        if ((low == 0) || (low > inc)) {low = inc;}
        arr[count] = inc;
    }
// Get the mean
    mean = total/count;
// Process command-line options and print output
    if ((optD) || (optA)){median = findMedian(arr , count);}
    if (optA) {
        printf("Count:\t%d \n", count);
        printf("Total:\t%0.*f \n", nPlaces, total);
        printf("Low:\t%0.*f \n", nPlaces, low);
        printf("High:\t%0.*f \n", nPlaces, high);
        printf("Mean:\t%0.*f \n", nPlaces, mean);
        printf("Median:\t%0.*f \n", nPlaces, median);
        optM = false;
        optD = false;
        optT = false;
    }
    if (noOpt) {printf("%0.*f \n", nPlaces, mean);}
    if (optM) {printf("Mean:\t%0.*f \n", nPlaces, mean);}
    if (optD) {printf("Median:\t%0.*f \n", nPlaces, median);}
    if (optT) {printf("Total:\t%0.*f \n", nPlaces, total);}
}

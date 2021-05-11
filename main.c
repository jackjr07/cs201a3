#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

void printArr(int data[], int length, int i){
    if(i == length) return;
    printf("%d-", data[i]);
    return printArr(data, length, ++i);
}

int * toBinary(int mansa[], int data, int fracBits){
    if(fracBits < 0) return mansa;
    mansa[fracBits] = data % 2;
    data = data / 2;
    return toBinary(mansa, data, --fracBits); 
}

float calMansa(int mansa[], int i, float carry, int fracBits){
    if(i >= fracBits) {
        printf("%f -fcarry", carry);
        return carry;
    }
    int temp = (i+1) * -1;
    if(mansa[i] == 1){
        carry += pow(2, temp);
        printf("Infunc: %f-c %d-t\n", carry, temp);
    }
    return calMansa(mansa, ++i, carry, fracBits);
}

int checkInf(int mansa[], int check, int i){
    if(i == strlen(mansa)-1){
        if(check == strlen(mansa)) return 1;
        else return 0;
    }
    if(mansa[i] == 1){
        check += 1;
    }
    return checkInf(mansa, check);
}
int main(int argc, char * argv[]){
    //base case
    if(argc < 3){
        printf("Usage: fp_parse <# of frac_bit> <# of exp_bit> <Hex>\n");
        return 0;
    }

    int expBits = atoi(argv[2]);
    int fracBits = atoi(argv[1]);
    if(expBits < 3 || expBits > 5){
        printf("Invalid number of exponent bits (%d), should be between 3-5\n", expBits);
        return 0;
    }
    if(fracBits < 2 || fracBits > 10){
        printf("Invalid number of fraction bits (%d), should be between 2-10\n", fracBits);
        return 0;
    }

    int length = strlen(argv[3]);
    if(length > expBits){
        int temp = pow(2, expBits) -1;
        printf("Number of %s exceeds maximun number of Bits. only %d allowed here\n", argv[3], temp);
        return 0;
    }
    int neg= 0;
    int data[length];
    for(int i =0; i<length; ++i){
        data[i] = argv[3][i];
        if(data[i] >= 48 && data[i] <= 57){
            data[i] -= 48;
        }else if(data[i] >= 97 && data[i] <= 102){
            data[i] -= 87;
        }else{
            printf("Argument 3 is not a hexadecimal(%s)\n", argv[3]);
            return 0;
        }
    }

    printArr(data, length, 0);

    int bias = pow(2, expBits-1) -1;
    printf("Bias: %d\n ", bias);
    
    int expo = 0;
    int frac = 0;
    if(length == 2){
        expo = data[0];
        neg = 1;
        frac = data[1];
    }else{
       expo = data[1];
       frac = data[2];
       neg = -1;
    }
    if(expo > bias){
        expo = expo - bias;
    }else{
        expo = expo + bias;
    }

    printf("Expo: %d\n ", expo);

    float expoF = pow(2, expo);
    printf("Expo: %f\n ", expoF);

    int mansa[fracBits];
    toBinary(mansa, frac, fracBits-1);
    printArr(mansa, fracBits, 0);
    
    int check = checkInf(mansa, 0, 0);
    printf("%d - inf\n", check);

    float carry = 1;
    float mansaF = calMansa(mansa, 0, carry, fracBits);
    printf("\n%f -mansa\n", mansaF);

    float answer = neg *expoF * mansaF;
    printf("\n%f -ans\n", answer);


    //printf("Exp: %s, Frac: %s, Hex: %s\n", argv[2], argv[1], argv[3]);


    printf("exp: %d", expBits);

    return 0;
}

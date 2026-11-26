#include <stdio.h>

int AlternateBits(int a){
        if (a==0){
                return 1;
        }       
        
        int TotalBits = sizeof(int)*8;
        int HighBitPos=0;

        for(int i = TotalBits -1; i>=0; i--){
                if ((a>>i)& 1){
                        HighBitPos = i;
                        break;
                }
        }

        int PrevBit  = a&1;
        for (int i=1; i<= HighBitPos; i++){
                int CurBit=(a>>i)& 1;
                if (CurBit == PrevBit){
                        return 0;
                }
                PrevBit=CurBit;
        }
        return 1;
}
int main(){
        int number;
        printf("Введите целое число:");
        scanf("%d",&number);

        if(AlternateBits(number)){
                printf("Значащие биты в числе %d чередуются.\n",number);
        }else{
                printf("Значащие биты в числе %d НЕ чередуются.\n",number);
        }
        return 0;
}
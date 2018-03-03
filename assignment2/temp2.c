#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



double find_page_rank(char *url)
{
   char number[50];
   char url_with_comma[50];
   double rank;
   strcpy(url_with_comma, url);
   strcat(url_with_comma,",");
   FILE *fp = fopen("pagerankList.txt","r");
   while((fscanf(fp,"%s",number)==1))
   {
      
      
      if(0==strcmp(url_with_comma, number))
      {
         fscanf(fp,"%s",number);
         fscanf(fp,"%s",number);
         rank = strtod(number,NULL);
         return rank;
      }
   }
   printf("url not found!\n");
   return 0;
   
}

int main(void)
{
   //printf("%f\n",find_page_rank(left_urls[i]));
   printf("%f\n",find_page_rank("url11"));
   return 0;
}



/*

int find_search_terms(const char* urlname, const char*keyword)
{
   int counter =0;
   char tempword[50];
   strcpy(tempword, urlname);
   strcat(tempword,".txt");
   FILE *fp = fopen(tempword,"r");
   while(fscanf(fp,"%s",tempword)==1)
   {
      if(strcmp(tempword,keyword)==0)
      {
          counter ++;
      }
   }
   return counter;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define N_WORDS 10000
#define WORD_LENGTH 100
#define URL_LENTH 10

void normalize(char *p);
int is_in_the_array(char* tempwords,char array[][WORD_LENGTH], int word_counter);
int myCompare(const void* a, const void* b);

void readUrlsInCollection(int num_urls,char urls[][URL_LENTH]);


int numberOfUrlsInCollection()
{
   FILE *f = fopen("collection.txt","r");
   char buf[1000];
   int count = 0;
   while(fscanf(f, "%s", buf)==1)
   {
     count++;
   }
   fclose(f);
   return count;
}
void readUrlsInCollection(int num_urls, char urls[][URL_LENTH])
{
  
  FILE *f = fopen("collection.txt","r");
  char buf[1000];
  int i = 0;
  while(fscanf(f, "%s", buf)==1)
  {
    strcpy(urls[i], buf);
    i++;
  }
  fclose(f);

}

int main (int argc, char* argv[]) {
   int num_urls = numberOfUrlsInCollection();
   char urls[num_urls][URL_LENTH];

   readUrlsInCollection(num_urls,urls);
   char filename[50];
   int url_counter =0;
   int words_counter = 0;
   char words[N_WORDS][WORD_LENGTH];
   char tempwords[50];
   char *start_word = "Section-2";
   char *end_word = "#end";
   
   //loop through each file
   while(url_counter < num_urls )
   {
      //open the url?.txt filename
      strcpy(filename,urls[url_counter]);
      //printf("%s\n",filename);
      strcat(filename,".txt");
      //printf("%s\n",filename);
      FILE * fp_url = fopen(filename, "r");
      //loop through each words in that file untill meet the start_word
      while((fscanf(fp_url,"%s",tempwords))==1 )
      {
          //printf("I was here\n");
         //
         if(strcmp(tempwords, start_word)==0)
         {
            //printf("MET THE START WORD!\n");
            break;
         }
         //collecting each word into the words[] array after normalize
      }
      
      
      
      //loop through each word untill meet the end_word
      while((fscanf(fp_url,"%s",tempwords))==1)
      {
             //printf("1now, words[0] is %s\n",words[words_counter]);
      
            if(strcmp(tempwords, end_word)==0)
            {
               //go to the next file
               break;
            }
            else
            {
              // printf("%s\n",tempwords);
               normalize(tempwords);
               
               
               if(!is_in_the_array(tempwords, words,words_counter))
               {
                  //add tempwords into the array
                  //printf("putting %s into the array\n",tempwords);
                  strcpy(words[words_counter],tempwords);
                  
                  words_counter=words_counter+1;
                 
               }
            }
            //printf("\n");
       }
      url_counter++;
      fclose(fp_url);
  }
  
  
 // printf("///////////////////////////////////////////\n");
  
  
  qsort(words[0], words_counter, sizeof(*words), myCompare);

  //printf("words_counter is %d\n",words_counter);
  
  FILE *output = fopen("invertedIndex.txt","w");
  for(int i=0;i<words_counter;i++)
  {
      fprintf(output,"%s",words[i]);
      url_counter =0;
      while(url_counter < num_urls )
      {
         strcpy(filename,urls[url_counter]);
         strcat(filename,".txt");
         FILE * fp_url = fopen(filename, "r");
         
         while((fscanf(fp_url,"%s",tempwords))==1 )
         {
              //printf("I was here\n");
              //printf("%s\n",tempwords);
              //
              if(strcmp(tempwords, start_word)==0)
              {
                //printf("MET THE START WORD!\n");
                break;
              }
                //collecting each word into the words[] array after normalize
          }
          
          while((fscanf(fp_url,"%s",tempwords))==1)
          {
             //printf("1now, words[0] is %s\n",words[words_counter]);
                 if(strcmp(tempwords, end_word)==0)
                 {
                    //go to the next file
                    break;
                 }
                 normalize(tempwords);
                 
                 if(strcmp(words[i],tempwords)==0)
                 {
                     fprintf(output," %s",urls[url_counter]);
                     break;
                 }
         
           }
           url_counter++;
           fclose(fp_url);
       }
       
       fprintf(output,"\n");
   }
   return 0;
   
}



int is_in_the_array(char* tempwords, char array[][WORD_LENGTH], int word_counter)
{

   if(word_counter==0)
   {
      return 0;
   }
   //printf("determin if %s is in the array\n",tempwords);
   int i = 0;
   for(i =0 ;i< word_counter ;i++)
   {
      if(strcmp(array[i],tempwords)==0)
      {
         //printf("found the same! array[%d]=%s and tempwords=%s\n",i,array[i],tempwords);
         return 1;
      }
   }
   //printf("it is not in\n");
   return 0;
}


//get rid of '.' (dot), ',' (comma), ';' (semicolon), ? (question mark) in the string and make lowercase
void normalize(char *p)
{
    char *src = p, *dst = p;

    while (*src)
    {
       if (ispunct((unsigned char)*src))
       {
          /* Skip this character */
          src++;
       }
       else if (isupper((unsigned char)*src))
       {
          /* Make it lowercase */
          *dst++ = tolower((unsigned char)*src);
          src++;
       }
       else if (src == dst)
       {
          /* Increment both pointers without copying */
          src++;
          dst++;
       }
       else
       {
          /* Copy character */
          *dst++ = *src++;
       }
    }

    *dst = 0;
}
int myCompare(const void* a, const void* b)
{
    const char* aa = (const char*)a;
    const char* bb = (const char*)b;
    return strcmp(aa, bb);
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

char* intal_add(const char* intal1, const char* intal2)
{
    int n1=strlen(intal1);
    int n2=strlen(intal2);

    int sum=0;
    int carry=0;

    char* a=malloc(2001);
    strcpy(a,intal1);

    char* b=malloc(2001);
    strcpy(b,intal2);


    char* result=malloc(2001);
    char* real_result=malloc(2001);

    if((intal_compare(a,"0")==0) && (intal_compare(b,"0")==0))
    {
        strcpy(result,"0");
        free(a);
        free(b);
        free(real_result);
        return(result);
    }

    int tail1=n1-1;                                      //to start adding from the tail of the 2 numbers
    int tail2=n2-1;

    int result_counter;
                                                        //result counter is the position used to store the digits in result array
    if(n1>n2)
        result_counter=n1;

    else if(n2>n1)
        result_counter=n2;

    else
        result_counter=n1;
   
    int last=result_counter+1;                          //used to put '\0' at the end

    while(tail1>=0 || tail2>=0)                            
    {
        if (tail1 >= 0 && tail2 >= 0)                   //if not consumed both numbers fully
        {
            sum = ((a[tail1]-'0') + (b[tail2]-'0') + carry) % 10;
            carry = ((a[tail1]-'0') + (b[tail2]-'0') + carry) / 10;
            tail1--;
            tail2--;
        }
        else if (tail1 == -1 && tail2 >= 0)             //if we have consumed 1st number but not yet 2nd
        {
            sum = ((b[tail2]-'0') + carry) % 10;
            carry = ((b[tail2]-'0') + carry) / 10;
            tail2--;
        }
        else if (tail1>= 0 && tail2 == -1)               //if we have consumed 2nd number but not yet 1st
        {
            sum = ((a[tail1]-'0') + carry) % 10;
            carry = ((a[tail1]-'0') + carry) / 10;
            tail1--;
        }
        result[result_counter--] = sum + '0';               //to store the sum digit on each addition to result array
    }
   
    result[result_counter]=carry + '0';
    result[last]='\0';

    int flag=0;
    int i;
    int j;

    for(i=0,j=0;result[i]!='\0';i++)                        //to trim the trailing zeroes and store it in real_result
    {
        if(flag==0 && result[i]=='0')
        {
            ;
        }
        else
        {
            flag=1;
            real_result[j++]=result[i];
        }
    }
    real_result[j]='\0';

    free(a);
    free(b);
    free(result);

    return(real_result);

}

int intal_compare(const char* intal1, const char* intal2)
{
    int n1=strlen(intal1);
    int n2=strlen(intal2);

    char* a=malloc(2001);
    strcpy(a,intal1);

    char* b=malloc(2001);
    strcpy(b,intal2);


    if(n1>n2)                                           //to pad zeroes to the left of 2nd number
    {
        int i=n1-1;
        int j=n2-1;
        b[n1]='\0';
        while(j>=0)
        {
            b[i]=b[j];
            i--;
            j--;
        }

        for(int k=0;k<n1-n2;k++)
        {
            b[k]='0';
        }
    }
    else if(n2>n1)                                        //to pad zeros to the left of 1st number
    {
        int i=n2-1;
        int j=n1-1;
        a[n2]='\0';

        while(j>=0)
        {
            a[i]=a[j];
            i--;
            j--;
        }

        for(int k=0;k<n2-n1;k++)
        {
            a[k]='0';
        }
    }

    int p=0;
    int q=0;

    while(a[p]!='\0' || b[q]!='\0')                          
    {
        if (a[p]!='\0' && b[q]!='\0')
        {
            if(a[p]==b[q])               // if digits are equal,dont do anything and keeps moving forward
            {
                ;
            }
            else if(a[p]>b[q])          //if 1st digit>2nd digit,returns 1
            {
                free(a);
                free(b);
                return(1);
            }
            else                        //if 2nd digit greater than first,return -1
            {
                free(a);
                free(b);
                return(-1);
            }
           
        }
        p++;
        q++;
    }
    free(a);
    free(b);

    return(0);
}

char* intal_diff(const char* intal1, const char* intal2)
{
    int difference=0;
    int borrow=0;

    char* a=malloc(2001);
    strcpy(a,intal1);

    char* b=malloc(2001);
    strcpy(b,intal2);

    char* result=malloc(2001);

    char* real_result=malloc(2001);

    int bigger=intal_compare(a,b);                            
    if(bigger==0)
    {
       strcpy(result,"0");
       return(result);
    }
   
    char* bigger_string;
    char* smaller_string;
                                              //to find the string which is bigger in value
    if(bigger==1)
    {  
        bigger_string=a;
        smaller_string=b;
    }
    else if(bigger==-1)
    {
        bigger_string=b;
        smaller_string=a;
    }

    int bigger_string_len=strlen(bigger_string);
    int smaller_string_len=strlen(smaller_string);

    int i=bigger_string_len - 1;                 //starts from tail of bigger number and goes left
    int j=smaller_string_len - 1;               //starts from tail of smaller number and goes left

    int result_counter=bigger_string_len - 1;    //position var used to store difference digit in result array
    result[bigger_string_len]='\0';

    while (i>=0 || j>=0)
    {
        if (i>=0 && j>=0)                       //if not consumed both numbers yet
        {
            if ((bigger_string[i]-'0') + borrow >= (smaller_string[j]-'0'))
            {
                difference = ((bigger_string[i]-'0') + borrow - (smaller_string[j]-'0'));
                borrow = 0;
            }
            else
            {
                difference = ((bigger_string[i]-'0') + borrow + 10 - (smaller_string[j]-'0'));
                borrow = -1;
            }
            i--;
            j--;
        }
        else if (i>=0 && j==-1)             //if consumed smaller number
        {
            if ((bigger_string[i]-'0') >= 1)
            {
                difference = ((bigger_string[i]-'0') + borrow);
                borrow = 0;
            }
            else
            {  
                if((bigger_string[i]-'0') + borrow >=0)
                {
                    difference = bigger_string[i] - '0';
                }
                else
                {
                    difference=(bigger_string[i]-'0') + borrow +10;
                }
                 
            }
            i--;
        }
        result[result_counter--]=difference + '0';    //storing the difference into result array
    }
   
    int flag=0;
    int i1;
    int j1;
                                                    //to trim the trailing zeroes
    for(i1=0,j1=0;result[i1]!='\0';i1++)
    {
        if(flag==0 && result[i1]=='0')
        {
            ;
        }
        else
        {
            flag=1;
            real_result[j1++]=result[i1];
        }
    }

    real_result[j1]='\0';
    free(a);
    free(b);
    free(result);

    return(real_result);

}

char* intal_multiply(const char* intal1, const char* intal2)
{
    int prod=0;
    int carry=0;

    char* a=malloc(2001);
    strcpy(a,intal1);

    char* b=malloc(2001);
    strcpy(b,intal2);

    char* result=malloc(2001);
    strcpy(result,"0");

    if((intal_compare(a,"0")==0) || (intal_compare(b,"0")==0))    //if one of the numbers is 0,return 0
    {
        free(a);
        free(b);
        return(result);
    }


    char* temp_result=malloc(2001);
    char* real_temp_result=malloc(2001);

    int bigger=intal_compare(a,b);

    char* bigger_string;
    char* smaller_string;

    if(bigger==1)                                     //to find the bigger string in terms of value
    {  
        bigger_string=a;
        smaller_string=b;
    }
    else if(bigger==-1)
    {
        bigger_string=b;
        smaller_string=a;
    }
    else
    {
        bigger_string=a;
        smaller_string=b;
    }

    int bigger_string_len=strlen(bigger_string);
    int smaller_string_len=strlen(smaller_string);

    for(int i=smaller_string_len-1;i>=0;i--)                    //till we consume smaller string from the tail
    {
        carry=0;
        int k=bigger_string_len;

        for(int j=bigger_string_len-1;j>=0;j--)                //till we consume bigger string from the tail
        {
            prod=((bigger_string[j] - '0')*(smaller_string[i] - '0') + carry) % 10;
            carry=((bigger_string[j] - '0')*(smaller_string[i] - '0') + carry )/ 10;
            temp_result[k--]=prod + '0';                        //storing the product into result array
                   
        }

        temp_result[k]=carry + '0';                         //storing final carry into left-most position of result array
        temp_result[bigger_string_len + 1]='\0';
        int r=bigger_string_len + 1;

        for(int s=0;s<smaller_string_len -1 - i;s++)        //to pad zeroes to the right of intermediate products from 2nd digit of smaller string onwards
        {
            temp_result[r++]='0';
        }
        temp_result[r]='\0';

        int flag=0;
        int i1;
        int j1;

        for(i1=0,j1=0;temp_result[i1]!='\0';i1++)         //to trim trailing zeroes and storing in real_result
        {
            if(flag==0 && temp_result[i1]=='0')
            {
                ;
            }
            else
            {
                flag=1;
                real_temp_result[j1++]=temp_result[i1];
            }
        }

        real_temp_result[j1]='\0';
        char* t=intal_add(result,real_temp_result);
        free(result);
        result=t;
    }
    free(a);
    free(b);
    free(temp_result);
    free(real_temp_result);

    return(result);
}

static char* zero_padding(const char* a,int n)          //pads zeroes to the right of smaller length intal on being called from intal_mod
{
    int n1 = strlen(a);
    int size=n1+n+1;

    char* result = malloc(size);
    strcpy(result,a);

    int k=n1+n;

    if(n==0)
    {
        return(result);
    }

    for(int j=n1;j<(n1+n);j++)
    {
        result[j]='0';
    }
   
    result[k]='\0';

    return(result);

}


char* intal_mod(const char* intal1, const char* intal2)
{
    int n1 = strlen(intal1);
    int n2 = strlen(intal2);

    int d = intal_compare(intal1, intal2);


    char* a=malloc(2001);
    strcpy(a,intal1);


    char* b=malloc(2001);
    strcpy(b,intal2);

    if((intal_compare(a,"0")==0) || (intal_compare(b,"0")==0))      //if one of them is 0,return 0 but actually its undefined
    {
        char* result=malloc(2001);
        free(a);
        free(b);
        strcpy(result,"0");
        return(result);
    }

    if(d<0)                                                     // if intal1<intal2 return intal1
    {
        char* result = malloc(2001);
        strcpy(result,a);
        free(a);
        free(b);
        return(result);
    }
    else if(d==0)                                           //if intal1==intal2 return 0
    {
        char* result=malloc(sizeof(char)*2);
        strcpy(result,"0");
        free(a);
        free(b);
        return(result);
    }
    else
    {  
        char* temp;
        char* result = malloc(2001);
        char* temp_result;
        strcpy(result,a);

        int i=n1-n2;

        while(i>=0)                                 
        {
            temp = zero_padding(b,i);           //pads zeroes to right of smaller intal

            while(intal_compare(result,temp)>0) //loops till result on continous subtraction produces a result lesser than intal2
            {
                temp_result = intal_diff(result,temp);
                free(result);
                result=temp_result;
            }
            if(intal_compare(result,temp)==0)       //if result is equal to intal2,return 0
            {
                free(result);
                free(temp);

                result=malloc(sizeof(char)*2);
                strcpy(result,"0");

                free(a);
                free(b);

                return(result);
            }

            free(temp);
            i--;
        }

        free(a);
        free(b);

        return(result);
    }
   
}

char* intal_pow(const char* intal1, unsigned int n)
{
   char* result=malloc(sizeof(char)*2001);
   strcpy(result,"1");

    if(intal_compare(intal1,"0")==0)              //  0^n is 0
    {
        strcpy(result,"0");
        return(result);
    }

   char* temp=malloc(sizeof(char)*2001);

   int i;

   while(n>1)
   {
       strcpy(temp,intal1);

       for(i=1;2*i<n;i*=2)                                      //keep squaring while till the closest value to power
       {
           char* t=intal_multiply(temp,temp);
           free(temp);
           temp=t;
       }
        char* p=intal_multiply(result,temp);
        free(result);
        result=p;
       n-=i;                                                    //finds the remaining power to be found

   }

   if(n==1)                                                      //if n==1 multiply once with intal1
   {
       char* q=intal_multiply(result,intal1);
       free(result);
       result=q;
   }

   free(temp);

   return(result);
}

char* intal_gcd(const char* intal1,const char* intal2)
{
   char* a=malloc(2001);
   strcpy(a,intal1);

   char* b=malloc(2001);
   strcpy(b,intal2);

   char* c=malloc(2001);
   char* d=malloc(2001);

    while(1)
    {
        if(intal_compare(a,"0")==0 && intal_compare(b,"0")==0)   //if both are 0,returns 0
        {
            strcpy(a,"0");
            free(b);
            free(c);
            free(d);
            return(a);
        }
        if(intal_compare(a,"0")==0)                          //if a is 0 returns b as 0%b is b
        {
            free(a);
            free(c);
            free(d);
            return(b);
        }
        else if(intal_compare(b,"0")==0)                 //if b is 0,returns a as a%0 is 0
        {
            free(b);
            free(c);
            free(d);
            return(a);
        }
        else
        {                                                // equivalent to recursive call of gcd(b,a%b)
            strcpy(c,b);
            strcpy(d,a);
            strcpy(a,b);
            char* t=intal_mod(d,c);
            free(b);
            b=t;
        }
    }
}

char* intal_fibonacci(unsigned int n)
{
    char a[2001]="0";          
    char b[2001]="1";


    char* c=malloc(sizeof(char)*2001);

    if(n==0)                   //f(0) is 0
    {
        strcpy(c,"0");
        return(c);
    }

    if(n==1)                //f(1) is 1
    {
        strcpy(c,"1");
        return(c);
    }

    for(int i=1;i<n;i++)        //finds f(i) =f(i-1)+f(i-2)
    {
        char* t=intal_add(a,b);
        free(c);
        c=t;
        strcpy(a,b);
        strcpy(b,c);
    }

    return(c);             // returns f(n)
}

static int string_to_int(char* i)   //converts string to integer
{
    int res=0;
    int n=strlen(i);

    for(int j=0;j<n;j++)
    {
        res=res*10 + i[j] -'0';
    }

    return(res);
}

char* intal_factorial(unsigned int n)
{
    char* result=malloc(2001);
    char* i=malloc(2001);
    strcpy(result,"1");

    for(strcpy(i,"1");string_to_int(i)<=n;)      //keeps multiplying till n
    {
        char* t=intal_multiply(result,i);            //multiplies previous product with current counter
        free(result);
        result=t;

        char* a=intal_add(i,"1");       //for increasing counter for loop condition
        free(i);
        i=a;
    }

    free(i);
    return(result);
}

static int minimum(int a,int b)
{
    if(a<b)
        return(a);
    else
        return(b);
}


char* intal_bincoeff(unsigned int n, unsigned int k)
{
    if(k>n/2)
    {
        k=n-k;
    }
    char* arr[k+1];

    arr[0]=malloc(sizeof(char)*2001);               //to store NC0 which is 1
    strcpy(arr[0],"1");


    for(int i=1;i<k+1;i++)                          //mallocing k+1 arrays to store the dp values
    {
        arr[i]=malloc(sizeof(char)*2001);
        strcpy(arr[i],"0");
    }


    for (int i = 1; i <= n; i++)            
    {  
        for (int j = minimum(i,k); j > 0; j--)      //uses the concept of pascal's trianlge where next row is calculated using the previous row
        {
            char* t=intal_add(arr[j],arr[j-1]);
            free(arr[j]);
            arr[j]=t;
        }
    }

    for(int i=0;i<k;i++)                      //frees the dp table except the last array as that's the result which is at position k
    {
        strcpy(arr[i],"0");
        free(arr[i]);
    }

    return(arr[k]);
}

int intal_max(char **arr, int n)
{
    char max[2001];
    strcpy(max,arr[0]);
   
    for (int i=1;i<n;i++)                             //finds max intal
    {
        if (intal_compare(arr[i],max)==1)
        {
           strcpy(max,arr[i]);
        }
    }

    for(int i=0;i<n;i++)                                //finds first occurence of max intal
    {
        if(intal_compare(arr[i],max)==0)
        {
            return(i);
        }
    }
}


int intal_min(char **arr, int n)
{
     char minimum[2001];
     strcpy(minimum,arr[0]);
   
    for (int i=1;i<n;i++)                           //finds min intal
    {
        if (intal_compare(arr[i],minimum)==-1)
        {
           strcpy(minimum,arr[i]);
        }
    }

    for(int i=0;i<n;i++)                        //finds first occuerence of min intal
    {
        if(intal_compare(arr[i],minimum)==0)
        {
            return(i);
        }
    }
}


int intal_search(char **arr, int n,const char* key)
{
    int key_length=strlen(key);
    int c;
    int j;

    for(int i=0;i<n;i++)
    {
        j=strlen(arr[i]);
       
        if(j!=key_length)              //if intal length is not same as key length,doesnt even compare as they cant be same
        {
            ;
        }
        else
        {
            c=intal_compare(arr[i],key);
            if(c==0)
            {
                return(i);        //finds first occurence of intal which is same as key
            }
        }
       
    }

    return(-1);
}

char* coin_row_problem(char **arr, int n)
{
    char *p=malloc(2001);
    strcpy(p,"0");

    char *q=malloc(2001);
    strcpy(q,arr[0]);

    char *r=NULL;
       
    char *result=malloc(2001);
   
    if(n==0)                                //if n is 0,answer is 0
    {
        strcpy(result,p);
        free(p);
        free(q);
    }
    else
    {
        for(int i=2;i<=n;i++)                           //loop that places finds max(previous value,previous to previous value+current input value) into result
        {
            char *s = intal_add(p,arr[i-1]);
            int c = intal_compare(s,q);

            if(c==0 || c==1)                
            {
                r=s;
            }  
            else
            {
                r=q;
                free(s);
            }
            if(p!=q)                    //as they might point to same location
                free(p);
            p=q;
            q=r;

        }
       
        strcpy(result,q);
        free(q);
    }

    return(result);

}

static void merge(char **arr, int start, int mid, int end)
{
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 =  end - mid;
 
    char* temp1[2001];
    char* temp2[2001];

    for(int i=0;i<2001;i++)                                           //allocating space for storing intals into temp1,temp2
    {
        temp1[i]=malloc(sizeof(char)*2001);
        temp2[i]=malloc(sizeof(char)*2001);
    }
 
    for (i = 0; i < n1; i++)                                        //copying upto n1 into temp1
    {
        strcpy(temp1[i],arr[start+i]);
    }  
    for (j = 0; j < n2; j++)                                        //copying upto n2 into temp2
    {
        strcpy(temp2[j],arr[mid+1+j]);
    }
 
    i = 0;
    j = 0;
    k = start;
     
    while (i < n1 && j < n2)              //merges the arrays by putting lower one first(sorting)
    {
        if (intal_compare(temp1[i],temp2[j])==-1)
        {
            strcpy(arr[k],temp1[i]);
            i++;
        }
        else
        {
            strcpy(arr[k],temp2[j]);
            j++;
        }
        k++;
    }
 
    while (i < n1)          //copies 1st half into arr
    {
        strcpy(arr[k],temp1[i]);
        i++;
        k++;
    }
 
    while (j < n2)          //copies 2nd half into arr
    {
        strcpy(arr[k],temp2[j]);
        j++;
        k++;
    }
    for(int i=0;i<2001;i++)  //de-allocates memory allocated for storing the intals temporarily
    {
        free(temp1[i]);
        free(temp2[i]);
    }
}

void intal_sort(char **arr, int n)
{
    int size;
    int start;
                                                                //keeps dividing the arrays and calling merge
   for (size=1;size<=n-1;size=2*size)
   {
       for (start=0;start<n-1;start += 2*size)
       {
           int mid = minimum(start + size - 1, n-1);
           int end = minimum(start + 2*size - 1, n-1);
           merge(arr,start, mid,end);
       }
   }
}    


int intal_binsearch(char **arr, int n,const char* key)
{
    int l=0;
    int r=n-1;
    int result=-1;

    while (l <= r)
    {
        int m = l + (r-l)/2;          //finds mid position

        if(intal_compare(arr[m],key)==0)            //if key is at mid,checks to its left for an earlier occurence
        {  
            result=m;
           
            if(m>=1 && (intal_compare(arr[m],arr[m-1])==1))
            {
                return(result);
            }
            r=m-1;  
        }
        if(intal_compare(arr[m],key)==-1)     //if key is greater uses right side of mid to search
            l = m + 1;  
 
        else                                    //if key is lesser uses left side of mid to search
            r = m - 1;  
    }

  return(result);
}

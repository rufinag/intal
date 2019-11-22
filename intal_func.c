#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "intal.h"

void* intal_create(const char* str)
{
	int i,j;
	char a;

	if(str == NULL)
	{
		return NULL;
	}

	int size = strlen(str);
	char* n;

	if(isalpha(str[0]))
	{
		char* z = intal_create("0");

		return z;
	}
	for(i=0;i<size;i++)
	{
		a = str[i];
		if(!isdigit(a))
		{
			break;
		}
	}
	n = (char*)malloc(sizeof(char)*(i+1));

	for(j=0;j<i;j++)
	{
		n[j] = str[j];
	}

	return n;
}


void intal_destroy(void* intal)
{
	if(intal!=NULL)
		free(intal);
}


char* intal2str(void* intal)
{
	if(intal == NULL)
	{
		char* nan = "NaN";
		return nan;
	}
	int i=0,j;
	char* x = (char*)intal;
	int size = strlen(x);

	char* s = (char*)malloc(sizeof(char)*(size+1));

	if(x[0]=='0'&&size==1)
	{
		s[0] = '0';
		s[1] = '\0';
		return s;
	}

	if(x[0]=='0')
	{
		while(x[i]=='0')
			i++;
	}
	size = size-i;

	for(j=0;j<size && i<strlen(x);j++,i++)
	{
		s[j] = x[i];
	}
	s[j] = '\0';
	return s;

}


void* intal_increment(void* intal)
{

	if(intal == NULL)
	{
		return NULL;
	}
	char* s;
	int dec,length,num,i;
	s = intal2str(intal);
	length = strlen(s);
	num = atoi(s);
	num++;
	dec = num/((int)(pow(10,length-1)));
	if(dec>9)
	{
		length++;
		//free(intal);
	}
	char* p = (char*)malloc(sizeof(char)*length);
	i = length;
	p[i-1]='\0';
	int j=0;
	for(i=length;i>0;i--)
	{
		int exp;//,j=0;
		exp = (int)pow(10,i-1);
		int div = num/exp;
		p[j]= (div%10)+'0'; 
		j++;
	}
	return p;
}

void* intal_decrement(void* intal)
{
	if(intal == NULL)
	{
		return NULL;
	}
	char* s;
	int dec,length,num,i;
	s = intal2str(intal);
	length = strlen(s);
	num = atoi(s);
	if(num==0)
	{
		return intal;
	}
	num--;
	dec = num/((int)(pow(10,length-1)));
	if(dec<1)
	{
		length--;
		//free(intal);
	}
	char* p = (char*)malloc(sizeof(char)*length);
	i = length;
	p[i-1]='\0';
	int j=0;
	for(i=length;i>0;i--)
	{
		int exp;
		exp = (int)pow(10,i-1);
		int div = num/exp;
		p[j]= (div%10)+'0'; 
		j++;
	}
	return p;
}




void* intal_add(void* intal1, void* intal2)
{
	if((intal1==NULL)||(intal2==NULL))
	{
		return NULL;
	}
	char* num1;
	char* num2;
	char* numcpy;
	char* sum;
	int i,len,carry=0,sm,diff;
	num1 = intal2str(intal1);
	num2 = intal2str(intal2);
	if(strlen(num1)>strlen(num2))
	{
		len = strlen(num1);
		diff = len - strlen(num2);
		numcpy = (char*)malloc(sizeof(char)*(len));
		for(i=0;i<diff;i++)
			numcpy[i] = '0';
		for(;i<len;i++)
			numcpy[i] = num2[i-diff];
		numcpy[i] = '\0';
		num2 = numcpy;
	}
	else if(strlen(num1)<strlen(num2))
	{
		len = strlen(num2);
		diff = len - strlen(num1);
		numcpy = (char*)malloc(sizeof(char)*(len));
		for(i=0;i<diff;i++)
			numcpy[i] = '0';
		for(;i<len;i++)
			numcpy[i] = num1[i-diff];
		numcpy[i] = '\0';
		num1 = numcpy;
	}
	else
	{
		len = strlen(num2);
	}
		sum = (char*)malloc(sizeof(char)*(len+1));
	int j = len;
	sum[j]='\0';

	for(i=len-1;i>=0;i--,j--)
	{
		//j--;
		sm = (num1[i]-'0') + (num2[i]-'0') + carry;
		carry= (sm/10);
		sm = sm%10;
		sum[j] = sm + '0';
	}
	sum[j] = carry + '0';
	sum = intal2str(sum);
	return sum;
}


void* intal_diff(void* intal1, void* intal2)
{
	char* num1;
	char* num2;
	int cmp;
	cmp = intal_compare(intal1,intal2);
	switch(cmp)
	{
		case -1: num1 = intal2str(intal2);
			num2 =  intal2str(intal1);
			break;
		case 1: 
		case 0: num1 = intal2str(intal1);
			num2 = intal2str(intal2);
			break;
		case -2: exit(0);
			break;
	}
	char* numcpy;
	char* difference;
	int i,len,borrow=0,sub,diff;
	if(strlen(num1)>strlen(num2))
	{
		len = strlen(num1);
		
		diff = len - strlen(num2);
		numcpy = (char*)malloc(sizeof(char)*(len));
		for(i=0;i<diff;i++)
			numcpy[i] = '0';
		for(;i<len;i++)
			numcpy[i] = num2[i-diff];
		numcpy[i] = '\0';
		num2 = numcpy;
	}
	len = strlen(num1);
	difference = (char*)malloc(sizeof(char)*(len+1));
	difference[len]='\0';
	for(i=len-1;i>=0;i--)
	{
		borrow =0;
		if(num1[i]<num2[i])
		{
			num1[i-1] = num1[i-1]-1;
			borrow = 1;
		}
		sub = ((borrow*10)+ (num1[i]-'0'))-(num2[i]-'0');
		difference[i]=sub+'0';
	}
	return difference;
}


void* intal_multiply(void* intal1, void* intal2)
{
	char* num1;
	char* num2;
	char* product;
	char* temp;
	void* mult;
	void* buffer;
	int cmp,i,j;
	int prod,car;
	cmp = intal_compare(intal1,intal2);
	switch(cmp)
	{
		case -1: num1 = intal2str(intal2);
			num2 =  intal2str(intal1);
			break;
		case 1: 
		case 0: num1 = intal2str(intal1);
			num2 = intal2str(intal2);
			break;
		case -2: return NULL;
			break;
	}
	j = strlen(num1)+strlen(num2);

	int prod_len = j;
	product = (char*)malloc(sizeof(char)*j);
	mult = product;
	product[j--]='\0';
	int len = strlen(num2);
	for(i=0;i<len;i++)
	{
		car=0;
		if(i>0)
		{	
			j = prod_len-i;
			temp = (char*)malloc(sizeof(char)*(j+1));
			buffer = temp;
			temp[j] = '\0';
		}
		while(j>(strlen(num1)-1))
		{
			if(i==0)
			{
				product[j] = '0';
			}
			else if(i>0)
			{
				temp[j] = '0';
			}
			j--;	
		}
		for(;j>=0;j--)
		{
			if(i==0)
			{
				prod = (num1[j]-'0')*(num2[i]-'0') + car;
				car = prod/10;
				prod = prod%10;
				product[j+1] = prod + '0';
			}
			else
			{
				prod = (num1[j]-'0')*(num2[i]-'0') + car;
				car = prod/10;
				prod = prod%10;
				temp[j+1] = prod + '0';
			}
		}

		if(i>0)
		{
			temp[0] = '0';
			mult = intal_add(mult,buffer);
			product = intal2str(mult);
			free(temp);
		}
		else
		{
			product[0] = car+'0';
		}
	}
	return product;
}


void* intal_divide(void* intal1, void* intal2)
{
	char* num1;
	char* num2;
	int cmp;
	num1 = intal2str(intal1);
	num2 = intal2str(intal2);
	if(atoi(num2) == 0)
	{
		return NULL;
	}
	cmp = intal_compare(intal1,intal2);
	if(cmp==0)
	{
		return intal_create("1");
	}
	else if(cmp==-1)
	{
		return intal_create("0");
	}
	else if(cmp==-2)
	{
		return NULL;
	}
	char* quotient;
	char* remainder;
	void* q;
	void* r; 
	quotient = "0";
	remainder = num1;
	q = quotient;
	r = remainder;
	while(intal_compare(r,intal2)>=0)
	{
		q = intal_increment(q);
		
		r = intal_diff(r,num2);
	}
	quotient = (char*)q;
	return quotient;
}


int intal_compare(void* intal1, void* intal2)
{
	char* num1;
	char* num2;
	int i,c1=0,c2=0;
	num1 = intal2str(intal1);
	num2 = intal2str(intal2);
	if(num1==NULL||num2==NULL)
	{
		return -2;
	}
	if(strlen(num1)>strlen(num2))
	{
		return 1;
	}
	else if(strlen(num1)<strlen(num2))
	{
		return -1;
	}
	else
	{
		for(i=0;i<strlen(num1);i++)
		{
			if(num1[i]>num2[i])
			{
				c1++;
			}
			else if(num1[i]<num2[i])
			{
				c2++;
			}
		}
		if(c1>c2)
			return 1;
		return -1;
	}
}


void* intal_pow(void* intal1, void* intal2)
{
	if((intal1==NULL)||(intal2==NULL))
	{
		return NULL;
	}
	char* num1;
	char* num2;
	void* count;
	count = intal2;
	num1 = intal2str(intal1);
	num2 = intal2str(intal2);
	void* p = intal_create("0");
	void* exp = intal_create("1");

	if(atoi(num2)==0)
	{
		return intal2str(exp);
	}
	else if(intal_compare(p,intal2)==0)
	{
		return num1;
	}
	else if(atoi(num1)==0)
	{
		return intal2str(p);
	}
	
	while(atoi(intal2str(count))>0)
	{
		exp = intal_multiply(exp,intal1);
		count = intal_decrement(count);
	}
	return intal2str(exp);
}
#include<iostream>
#include<algorithm>
#include<queue>
#include<fstream>
#include<stack>
#include<cstring>
#include<bitset>
#include<time.h>
#include<string>

using namespace std;

typedef char S[50];

class Tnode						//The Node represting an element of huffman tree
{
	//unsigned long freq;
	char ch;
	S str;
	Tnode  * left;
	Tnode  * right;
	
  public:
  	
  	Tnode()
  	{
  	  // freq=0;
  	   ch='\0';
  	   str[0]='\0';
  	   left=NULL;
  	   right=NULL;
  	}
  	
  	char* get_str()
  	{
  	  return str;
  	}
  	
  	void set_str(S A)
  	{
  	  strcat(str,A);
  	}
  	
  	/*unsigned long get_freq()
  	{
  	   return freq;
 	}
 	
 	void set_freq(unsigned long p)
 	{
 	   freq=p;
 	}*/
 	
 	char get_ch()
 	{
 	  return ch;
 	}
 	
 	void set_ch(char c)
 	{
 	   ch=c;
 	}
 	
 	Tnode* get_left()
 	{
 	   return left;
    	}
    	
    	void set_left(Tnode* l)
    	{
    	   left=l;
    	
    	}
    	
    	Tnode* get_right()
 	{
 	   return right;
    	}
    	
    	void set_right(Tnode* r)
    	{
    	   right=r;
    	}
    	
    /*	bool operator < (Tnode T) const
    	{
    	  if(freq > T.freq)
    	  return true;
    	  else return false;
	}*/
	
	//friend ostream & operator <<(ostream &,Tnode &);
	
};




	/*ostream & operator <<(ostream & cout,Tnode & T)
	{
	  cout<<T.freq<<"  "<<T.ch<<endl;
	  return cout;
	}*/
	
class convert
{

  Tnode * root;
  S  enc_file,dec_file,key_file; 
  public:
  
  convert()
  {
    root=NULL;
  }
  
  convert(char * enc_file,char * key_file)
  {
    root=NULL;
    strcpy(this->enc_file,enc_file);
    strcpy(this->key_file,key_file);
  }
  convert(char * enc_file)
  {
    root=NULL;
    strcpy(this->enc_file,enc_file);
    strcpy(key_file,"key.txt");
  }
  
    void Create()					//This File Generates Huffman Key from key_file
  {
    char ch;
    fstream file(key_file);
    if(root==NULL)
    {
      Tnode * temp;
      temp=new Tnode();
      root=temp;
    }
    Tnode * p;
    p=root;
    int count=0;
    S c;
    while(file.get(ch))
    {
       if((ch=='0' || ch=='1') && count==0)
      {
        Tnode * temp;
        temp=new Tnode();
        if(ch=='0')
        {
          if(p->get_left()==NULL)
          {
            strcpy(c,p->get_str());
            strcat(c,"0");
            temp->set_str(c);
            p->set_left(temp);
          }
          p=p->get_left();
        }
        else
        {
          if(p->get_right()==NULL)
          {
            strcpy(c,p->get_str());
            strcat(c,"1");
            temp->set_str(c);
            p->set_right(temp);
          }
          p=p->get_right();
        }
      }
      else if(count==1)
      {
         p->set_ch(ch);
         p=root;
         count=0;
      }
      else if(ch=='~')count=1;
    }
    file.close();
  }
  
  
  void decode()								//Decodes the File Provided using the key provided
  {
  
     fstream file,dec;
     file.open(enc_file,ios::binary | ios::in);
     dec.open("./decoded.txt",ios::out);
     Tnode * p;
     p=root;
     char ch;
     while(file.read((char*)& ch,sizeof(ch)))
     {
        bitset <8> x(ch);
        string S;
        S=x.to_string();
        int i=0;
        while(i!=8)
        {
            if(S[i]=='0' )
           {
              p=p->get_left();
              cout<<'0';
           }
           else if(S[i]=='1')
           {
              p=p->get_right();
              cout<<'1';
           }
           
            if(p->get_left()==NULL && p->get_right()==NULL)
           {
             dec<<p->get_ch();
             cout<<"-"<<p->get_ch()<<endl;
             p=root;
           }
           i++;
        }
     }
     file.close();
     dec.close();
  }
  
  

};


int main(int argc,char * argv[])
{

     clock_t t=clock();
     
   if(argc==1)
   {
     convert O;
     O.Create();
     O.decode();

   }
   if(argc==2)
   {
     convert O(argv[1]);
     O.Create();
     O.decode();

   }
   if(argc==3)
   {
     convert O(argv[1],argv[2]);
     O.Create();
     O.decode();

   }
  
      cout<<endl<<endl<<"TIME REQUIRED:-"<<(float)(clock()-t)/CLOCKS_PER_SEC<<"sec"<<endl;
}

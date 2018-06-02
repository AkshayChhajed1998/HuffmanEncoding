/* Module to Create encode file after generation of huffman key file.
	
	usage:-
			1]  huffmanencode   file_name_to_be_encoded    file_name_where_to_save_encoding   key_file
			2]  huffmanencode   file_name_to_be_encoded    file_name_where_to_save_encoding  
				(when key file name is key.txt)
			3]  huffmanencode   file_name_to_be_encoded
				(when default key file name is key.txt and encoded file name is encoded.txt)
*/


#include<iostream>
#include<algorithm>
#include<queue>
#include<fstream>
#include<stack>
#include<cstring>
#include<time.h>

using namespace std;

typedef char S[50];

class Tnode						//Tnode class for generation of tree nodes from key.txt
{
	//unsigned long freq;
	char ch;
	S str;
	Tnode  * left;
	Tnode  * right;
	
  public:
  	
  	Tnode()
  	{
  	   //freq=0;
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
    	
    	/*bool operator < (Tnode T) const
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
	

class convert					//Covert Class for complete encoding process
{
  Tnode * root;
  S fs,fsa,key;
  public:
  convert()
  {root=NULL;}
  
  
  convert(S s,S p,S q)
  {
    root=NULL;
    strcpy(fs,s);
    strcpy(fsa,p);
    strcpy(key,q);
  }
  
  convert(S s,S p)
  {
    root=NULL;
    strcpy(fs,s);
    strcpy(fsa,p);
    strcpy(key,"./key.txt");
  }
  
  convert(S s)
  {
    root=NULL;
    strcpy(fs,s);
    strcpy(fsa,"./encoded.txt");
    strcpy(key,"./key.txt");
  }
  
  void Create()					//This function creates Huffman Tree from key.txt
  {
    char ch;
    fstream file(key);
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
  
  
   Tnode* Search(char ch)					//This is search method to search given character
  {
    Tnode* temp;
    stack <Tnode *> s;
    temp=root;
    do
    {
    while(temp!=NULL)
    {
      s.push(temp);
      if(temp->get_left()==NULL && temp->get_right()==NULL)
      if(temp->get_ch()==ch)
      {
         return temp;
      }
      temp=temp->get_left();
    }
    if(s.empty()!=1)
    {
      temp=s.top();
      s.pop();
      temp=temp->get_right();
      if(temp!=NULL)
      if(temp->get_left()==NULL && temp->get_right()==NULL)
      if(temp->get_ch()==ch)
      {
        return temp;
      }
    }
    }while(s.empty()!=1 || temp!=NULL);
  }
 
 
  void encode()							//This method takes a character from file and covert it encoded char
  {
    char ch;
    int count=-1;
    char bitbuff=0;
    int bit;
    char * S;
    fstream enc(fsa,ios::out | ios::binary);
    fstream file(fs,ios::in);
    Tnode * p;
    while(file.get(ch))
    {
      p=Search(ch);
      if(p!=NULL)
      {
      strcpy(S,p->get_str());
      int i=0;
      while(*(S+i)!='\0')
      {
        bit=(int)(*(S+i)-'0');
        count++;i++;
        if(bit!=0)
        bitbuff |= (1<<(7-count));
        if(count==7)
        {
          enc.write((char*)&bitbuff,sizeof(char));
          bitbuff=0;
          count=-1;  
        }
      }
      }
    }
    if(count != -1)
    enc.write((char*)&bitbuff,sizeof(char));
    file.close();
    enc.close();
  }
  
  
  void inorder_display()				//display inorder transversal(To Display all character and there key in key.txt)
 {
  stack<Tnode *> s;
  Tnode *temp;
  temp=root;
  do
  {
   while(temp!=NULL)
   {
    s.push(temp);
    temp=temp->get_left();
   }
   if(s.empty()!=1)
   {
    temp=s.top();s.pop();
    cout<<temp->get_ch()<<"---"<<temp->get_str()<<endl;
    temp=temp->get_right();
   }
  }
  while(s.empty()!=1 || temp != NULL); 
 }
  
};

int main(int argc,char * argv[])
{
  
  clock_t t=clock();
  if(argc==2)
  {
    convert O(argv[1]);
    O.Create();
    O.encode();
    O.inorder_display();
  }
  else if(argc=3)
  {
    convert O(argv[1],argv[2]);
    O.Create();
    O.encode();
    O.inorder_display();
   }
   else if(argc==3)
   {
      convert O(argv[1],argv[2],argv[3]);
      O.Create();
      O.encode();
      O.inorder_display();
   }
   else
   {
     cout<<"The Format Must Be:-\n";
     cout<<"Huffmanencode <file_to_be_encoded>\n";
     cout<<"Huffmanencode <file_to_be_encoded> <file_in_which_to_save>\n";
     cout<<"Note:-In 1st Case file will be saved as encoded.txt\n";
     return 0;
   }
   cout<<endl<<endl<<"TIME REQUIRED:-"<<(float)(clock()-t)/CLOCKS_PER_SEC<<"sec"<<endl;
}




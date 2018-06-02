#include<iostream>
#include<algorithm>
#include<queue>
#include<fstream>
#include<stack>
#include<cstring>
#include<time.h>

using namespace std;

typedef char S[50];

class Tnode						//This is node using which we will form Huffman Tree
{
	unsigned long freq;
	char ch;
	S str;
	Tnode  * left;
	Tnode  * right;
	
  public:
  	
  	Tnode()
  	{
  	   freq=0;
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
  	
  	unsigned long get_freq()
  	{
  	   return freq;
 	}
 	
 	void set_freq(unsigned long p)
 	{
 	   freq=p;
 	}
 	
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
    	
    	bool operator < (Tnode T) const
    	{
    	  if(freq > T.freq)
    	  return true;
    	  else return false;
	}
	
	friend ostream & operator <<(ostream &,Tnode &);
	
};




	ostream & operator <<(ostream & cout,Tnode & T)
	{
	  cout<<T.freq<<"  "<<T.ch<<endl;
	  return cout;
	}
	
	
	
	
	
	
class Que							//This Class is Used for Creation of Huffman Tree
{
  private:
  deque <Tnode *> Q;
  deque <Tnode *>::iterator it,it1;
  char ch;
  int count;
  unsigned long l;
  Tnode * T;
  S cc,kf;
  
  public:
  
  Que(char * STR)
  {
    strcpy(cc,STR);
    strcpy(kf,"key.txt");
  }
  
  Que(char * STR,char * key_f)
  {
    strcpy(cc,STR);
    strcpy(kf,key_f);
  }
  
  void sort()						   //Sorting the Elements in the Queue on basis of count of that word in file
  {
      for(it=Q.begin();it<Q.end();it++)
     {
       for(it1=it+1;(it1<Q.end());it1++)
       {
         if((*it1)->get_freq()<(*it)->get_freq())
         {
           T=*it;
          *it=*it1;
          *it1=T;
         }
      }
    }
  }
  
 void display()						//Dispalyinf the Single Node of Tree
  {
    while(!Q.empty())
    {
      T=Q.front();
      Q.pop_front();
      cout<<*T;
    }
  }
  
   void inorder(Tnode * r)		//This inorder method traverse the Huffman tree and write each char entry to key_file
 {
   stack<Tnode *> s;
   Tnode *temp;
   char* c;
   fstream writ(kf,ios::out);
   temp=r;
   do
   {
    while(temp!=NULL)
    {
     s.push(temp);
     strcpy(c,temp->get_str());
     temp=temp->get_left();
     if(temp!=NULL)
     {
      strcat(c,"0");
      temp->set_str(c);
      if(temp->get_ch()!='\0')
      writ<<temp->get_str()<<"~"<<temp->get_ch()<<endl;
     }
    }
    if(s.empty()!=1)
    {
     temp=s.top();
     s.pop();
     cout<<temp->get_ch()<<" ";
     strcpy(c,temp->get_str());
     temp=temp->get_right();
     if(temp!=NULL)
     {
      strcat(c,"1");
      temp->set_str(c);
      if(temp->get_ch()!='\0')
      writ<<temp->get_str()<<"~"<<temp->get_ch()<<endl;
     }
    }
   }
   
  while(s.empty()!=1 || temp != NULL); 
 }
   
 void  queue_generation()                                       //This method Generates queue of element in the file and there count 
 {
 
  fstream file;
  file.open(cc);
  while(file.get(ch))
  {
    	count=0;
    	for(it=Q.begin();it<Q.end();it++)
    	{
      	   if((*it)->get_ch()==ch)
      	   {
             (*it)->set_freq((*it)->get_freq()+1);
             count++;
           }
        }
        if(count==0)
        {
          T=new Tnode;
          T->set_freq(1);
          T->set_ch(ch);
          Q.push_front(T);
        }
  }
  sort();                                                                  //sorts dequeue in increasing order of count 

  do                                                                               //Creating Huffman Tree from dequeue
  {
     Tnode * temp;
     temp=new Tnode;
     temp->set_left(Q.front());Q.pop_front();
     temp->set_right(Q.front());Q.pop_front();
     temp->set_freq(temp->get_left()->get_freq()+temp->get_right()->get_freq());
     Q.push_front(temp);
     sort();
   }while(Q.begin()+1!=Q.end());
   
   inorder(Q.front());
  }
  
  Tnode* roots()
  {
    return Q.front();
  }
 
  
  
};


int main(int argc,char* argv[])
{
  int i=1;
  if(argc!=2)
  {
    cout<<"Doesnt Match the Format: ./huffmankeygen <file_name>"<<endl;
    cout<<"					    ./huffmankeygen <file_name> <key_file_name>";
  }
  else
  {
    Que O(argv[1]);
    clock_t t=clock();
    O.queue_generation();
    cout<<endl<<endl<<"TIME REQUIRED:-"<<(float)(clock()-t)/CLOCKS_PER_SEC<<"sec"<<endl;
    O.display();
  }
  return 0;
}

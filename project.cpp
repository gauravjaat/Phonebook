#include<bits/stdc++.h>


using namespace std;

class conDetails{
public:
	long long int mob;
	long long int regCode;
	int speed=0;
};
class avlNode
{
public:
	int asc;
	multimap<string,conDetails> s;
	avlNode *l;
	avlNode *r;
	int h;
};
avlNode *newnode(int key,string sname,conDetails D)
{
	avlNode *n= new avlNode;
	n->asc=key;
	n->s.insert(make_pair(sname,D));
	n->r=NULL;
	n->l=NULL;
	n->h=1;
	return n;
}
int max(int a,int b)
{
	return (a > b)? a : b;
}

int height(avlNode *n)
{
	if(n==NULL)
		return 0;
	return n->h;
}
avlNode* rotateR(avlNode *n)
{
	avlNode *x=n->l;
	avlNode *t2=x->r;
	x->r=n;
	n->l=t2;
	n->h= max(height(n->l),height(n->r)) + 1;
	x->h= max(height(x->l),height(x->r)) + 1;
	return x;
}
avlNode *rotateL(avlNode *n)
{
	avlNode *x=n->r;
	avlNode *t2=x->l;
	x->l=n;
	n->r=t2;
	n->h = 1 + max(height(n->l),height(n->r));
	x->h = 1 + max(height(x->l),height(x->r));
	return x;
}
int getbalance(avlNode *n)
{
	if(n==NULL)
		return 0;
	 return height(n->l) - height(n->r);
}

int searchInsert(avlNode *n,int val,string sname,conDetails D)
{
	while(n!=NULL)
	{
		if(n->asc==val)
		{
			n->s.insert(make_pair(sname,D));
			return 0;
		}
		else
		{
			if(val >= n->asc)
				return searchInsert(n->r,val,sname,D);
			else
			   return searchInsert(n->l,val,sname,D);
		}
	}
	return 1;
}

int searchCon(avlNode *n,string sname)
{
	int val=(int)sname[0];
	while(n!=NULL)
	{
		if(n->asc==val)
		{
			for(auto i=n->s.begin();i!=n->s.end();i++)

			{

				if(i->first==sname)
				{
					cout<<i->first<<"\t\t|\t\t"<<i->second.mob<<endl;
				}
		}
		return 0;
		}
		else
		{
			if(val >= n->asc)
				return searchCon(n->r,sname);
			else
			   return searchCon(n->l,sname);
		}
	}
	return 1;
}
void speed(avlNode *n,long long int f,int x)
{
	if(n!=NULL)
	{
		speed(n->l,f,x);
		for(auto i=n->s.begin();i!=n->s.end();i++)
			{
				if((i->second.regCode)==f)
					{
						i->second.speed=x;
						cout<<" Speed Dial added successfully \n";
						return;
					}
			}
		speed(n->r,f,x);
	}
}
void callspeed(avlNode *n,int x)
{
	if(n!=NULL)
	{
		callspeed(n->l,x);
		for(auto i=n->s.begin();i!=n->s.end();i++)
			{
				if((i->second.speed)==x)
					{
						cout<<i->first<<"\t|\t"<<i->second.mob<<"\t|\t"<<i->second.regCode<<endl;
						return;
					}
			}
		callspeed(n->r,x);
	}
}

avlNode *insertNode(avlNode *tempnode,int key,string sname,conDetails D)
{
	if(tempnode==NULL)
	 	return newnode(key,sname,D);
	if(key > tempnode->asc)
	{
		tempnode->r=insertNode(tempnode->r,key,sname,D);
	}
	else if(key < tempnode->asc)
		tempnode->l=insertNode(tempnode->l,key,sname,D);
	else
		return tempnode;
	tempnode->h=max(height(tempnode->l),height(tempnode->r)) + 1;

	int b=getbalance(tempnode);

	if(b>1 && key < tempnode->l->asc)
		return rotateR(tempnode);
	if(b<-1 && key > tempnode->r->asc)
		return rotateL(tempnode);
	if(b>1 && key > tempnode->l->asc)
	{
		tempnode->l=rotateL(tempnode->l);
		return rotateR(tempnode);

	}
	if(b<-1 && key < tempnode->r->asc)
	{
		tempnode->r=rotateR(tempnode->r);
		return rotateL(tempnode);
	}
	return tempnode;
}

void printin(avlNode *root)
{
	if(root!=NULL)
	{
		printin(root->l);
		cout<<(char)root->asc<<endl;
		for(auto i=root->s.begin();i!=root->s.end();i++)
			cout<<i->first<<"\t|\t"<<i->second.mob<<"\t|\t"<<i->second.regCode<<endl;
		printin(root->r);
	}
}

avlNode *insertion(avlNode *root,string sname,conDetails D)
{
	static long long int code=0;
	D.regCode=++code;
	char temp=sname[0];
	int key=(int)temp;
	int res=searchInsert(root,key,sname,D);
	if(res==1)
	root=insertNode(root,key,sname,D);

	return root;
}
int edit(avlNode *n,string sname,conDetails D,avlNode *root)
{
	long long int x;
	string s;
	int val=(int)sname[0];
	while(n!=NULL)
	{
		if(n->asc==val)
		{
			for(auto i=n->s.begin();i!=n->s.end();i++)
				if(i->first==sname)
					cout<<i->first<<"\t\t|\t\t"<<i->second.mob<<endl;


		cout<<"Enter number : ";
		cin>>x;
		for(auto i=n->s.begin();i!=n->s.end();i++)
			{
				if((i->first==sname) && (i->second.mob==x))
				{
					cout<<"Enter new name : ";
					std::getline(std::cin >> std::ws, s);
					cout<<"Enter new Number :";
					cin>>D.mob;
					root=insertion(root,s,D);
					n->s.erase(i);
					return 0;
				}
			}
		}
		else
		{
			if(val >= n->asc)
				return edit(n->r,sname,D,root);
			else
			   return edit(n->l,sname,D,root);
		}
	}
	return 1;
}
int del(avlNode *n,string sname,conDetails D,avlNode *root)
{
	long long int x;
	string s;
	int val=(int)sname[0];
	while(n!=NULL)
	{
		if(n->asc==val)
		{
			for(auto i=n->s.begin();i!=n->s.end();i++)
				if(i->first==sname)
					cout<<i->first<<"\t\t|\t\t"<<i->second.mob<<endl;


		cout<<"Enter number : ";
		cin>>x;
		for(auto i=n->s.begin();i!=n->s.end();i++)
			{
				if((i->first==sname) && (i->second.mob==x))
				{
					n->s.erase(i);
					return 0;
				}
			}
		}
		else
		{
			if(val >= n->asc)
				return del(n->r,sname,D,root);
			else
			   return del(n->l,sname,D,root);
		}
	}
	return 1;
}
int main()
{
    conDetails person;
    avlNode *root=NULL;
    string temp_name;
    int choice,flag=0,flag1,x;

    cout<<"* PHONEBOOK *"<<endl;


    do
    {
        cout<<"\n\n\n";
        cout<<"0. Show contacts"<<endl
        <<"1. Add Contact"<<endl
        <<"2. Edit Contact"<<endl
        <<"3. Delete Contact"<<endl
        <<"4. Search"<<endl
        <<"5. Add Speed Dial"<<endl
        <<"6. Speed Dial"<<endl
        <<"7. Quit" <<endl<<endl
        <<"Your choice...";
        cin >> choice;

        switch(choice)
        {
            case 0:
                cout<< "Showing Contacts\n"<<endl;
                cout<<"Name \t"<<"|"<<"\tMobile Number"<<"\t|\t"<<"RegCode"<<endl;

                printin(root);

                if(root==NULL)
                    cout << "No contacts found!" << endl;
                break;
            case 1:
            	cout<<" Name : ";
            	std::getline(std::cin >> std::ws, temp_name);
            	cout<<"Mobile no. : ";
            	cin>>person.mob;
            	root=insertion(root,temp_name,person);
            	break;
            case 2:
            	cout<<"Enter contact name to be edited : ";
            	std::getline(std::cin >> std::ws, temp_name);
            	edit(root,temp_name,person,root);
            	break;
            case 3:
            	cout<<"Enter contact name to be Deleted : ";
            	std::getline(std::cin >> std::ws, temp_name);
            	del(root,temp_name,person,root);
            	break;
            case 4:
            	cout<<"Enter Name to be searched : ";
            	std::getline(std::cin >> std::ws, temp_name);
            	flag=searchCon(root,temp_name);
            	if(flag==1)
            		cout<<"No such contact exists "<<endl;
            	break;
            case 5:
            	cout<<"Name \t"<<"|"<<"\tMobile Number"<<"\t|\t"<<"RegCode"<<endl;
				printin(root);

            	cout<<"Enter RegCode for Speed Dial : ";
            	cin>>flag1;
            	cout<<"Enter Speed Dial priority : ";
            	cin>>x;
            	speed(root,flag1,x);
            	break;
            case 6:
            	cout<<"Enter Speed Dial : ";
            	cin>>flag1;
            	callspeed(root,flag1);
            	break;
            case 7:
				cout << "Bye Bye" << endl;
				break;

        }
    } while(choice!=7);

    return 0;
}

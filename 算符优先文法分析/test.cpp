#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

int state[100];
 
int sn_c=0;
//.............................

char table[20][20];                    //算符优先关系表
char s[100];                          
char str_in[20][10];                  
char T_label[20];                      
char input_s[100];                      
int FVT[10]={0};                    
int LVT[10]={0};                   
int k,j;
char a,q;
int r;                                //文法规则个数
int r1;
int m,n,N;                             
char grammar[10][30];                    //用来存储文法产生式
char FIRSTVT[10][10];                   //FIRSTVT集
char LASTVT[10][10];                    //LASTVT集



int test_s();                          //字串分析
int is_T(char c);               
int index(char c);                 
void stack_p(int j,int k,char *s);      //打印
void firstvt(char c);                //求FIRSTVT集
void lastvt(char c);                 //求LASTVT集
void P_table();						//生成算符文法优先关系表

typedef struct TNode
{
    char *table;
    int n;
    struct TNode *child[10];
} TreeNode;

void printTree(TreeNode *root, int depth, unsigned char flag)
{
    int i, tmp;
    unsigned char newflag;
     
    for (i = 0; i < depth; ++i)
    {
        switch (state[i])
        {
            case 0: printf("  "); break;
            case 1: printf("│"); break;
            case 3: printf("├"); break;
            case 4: printf("└"); break;
            case 2: printf("─"); break;
            default: ;
        }
        if (i < depth - 1) printf("  ");
        else printf("─");
    }
    printf("%s\n", root->table);
 
    if (depth > 0)
    {
        if (flag & 1) state[depth - 1] = 0;
        else if (flag & 2) state[depth - 1] = 1;
    }
 
    if (root->n == 0) return;
    for (i = 0; i < root->n; ++i)
    {
        newflag = 0;
        if (i == 0) newflag |= 2;
        if (i == root->n - 1) 
        {
            newflag |= 1;
            state[depth] = 4;
        } else state[depth] = 3;
 
        tmp = state[depth - 1];
        if (state[depth - 1] != 0 && state[depth - 1] != 1)
            state[depth - 1] = 1;
        printTree(root->child[i], depth + 1, newflag);
        state[depth - 1] = tmp;
    }
}
 
void add_node(TreeNode* node, TreeNode *sub)
{
    node->child[node->n++] = sub;
}
 
void deleteTree(TreeNode *root)
{
    int i;
    if (!root) return;
    for (i = 0; i < root->n; ++i)
        deleteTree(root->child[i]);
    free(root);
}

TreeNode* new_node(char *table)
{
    TreeNode *node = (TreeNode*) malloc(sizeof (TreeNode));
    node->table = table ;
    node->n = 0;
    return node;
}

TreeNode *sn[20];
                       

void P_table()
{
	char text[20][10];
	int i,j,k,t,l,x=0,y=0;
	int m,n;
	x=0;
	for(i=0;i<r;i++)
	{
		firstvt(grammar[i][0]);
		lastvt(grammar[i][0]);
	}
	for(i=0;i<r;i++)
	{
		text[x][y]=grammar[i][0];
		y++;
		for(j=1;grammar[i][j]!='\0';j++)
		{
			if(grammar[i][j]=='|')
			{
				text[x][y]='\0';
				x++;
				y=0;
				text[x][y]=grammar[i][0];
				y++;
				text[x][y++]='-';
				text[x][y++]='>';
			}
			else
			{
				text[x][y]=grammar[i][j];
				y++;
			}
		}
		text[x][y]='\0';
		x++;
		y=0;
	}
	r1=x;
	printf("产生式展开\n");
	for(i=0;i<x;i++)                                  
	{
		printf("%s\n",text[i]);
	}
	for(i=0;i<x;i++)                         
	{
		str_in[i][0]=text[i][0];

		for(j=3,l=1;text[i][j]!='\0';j++,l++)
			str_in[i][l]=text[i][j];

		str_in[i][l]='\0';
	}

	

	for(i=0;i<x;i++)
	{
		for(j=1;text[i][j+1]!='\0';j++)
		{
			if(is_T(text[i][j])&&is_T(text[i][j+1]))
			{
				m=index(text[i][j]);
				n=index(text[i][j+1]);
				if(table[m][n]=='='|table[m][n]=='<'|table[m][n]=='>')
				{
					printf("该文法不是算符优先文法\n");
					exit(-1);
				}
				table[m][n]='=';
			}
			if(text[i][j+2]!='\0'&&is_T(text[i][j])&&is_T(text[i][j+2])&&!is_T(text[i][j+1]))
			{
				m=index(text[i][j]);
				n=index(text[i][j+2]);
				if(table[m][n]=='='|table[m][n]=='<'|table[m][n]=='>')
				{
					printf("该文法不是算符优先文法\n");
					exit(-1);
				}
				table[m][n]='=';
			}
			if(is_T(text[i][j])&&!is_T(text[i][j+1]))
			{
				for(k=0;k<r;k++)
				{
					if(grammar[k][0]==text[i][j+1])
					break;
				}
				m=index(text[i][j]);
				for(t=0;t<FIRSTVT[k][0];t++)
				{
					n=index(FIRSTVT[k][t+1]);
					if(table[m][n]=='='|table[m][n]=='<'|table[m][n]=='>')
					{
						printf("该文法不是算符优先文法\n");
						exit(-1);
					}
					table[m][n]='<';
				}
			}
			if(!is_T(text[i][j])&&is_T(text[i][j+1]))
			{
				for(k=0;k<r;k++)
				{
					if(grammar[k][0]==text[i][j])
					break;
				}
				n=index(text[i][j+1]);
				for(t=0;t<LASTVT[k][0];t++)
				{
					m=index(LASTVT[k][t+1]);
					if(table[m][n]=='='|table[m][n]=='<'|table[m][n]=='>')
					{
						printf("该文法不是算符优先文法\n");
						exit(-1);
					}
					table[m][n]='>';
				}
			}
		}
	}
	m=index('#');
	for(t=0;t<FIRSTVT[0][0];t++)
	{
		n=index(FIRSTVT[0][t+1]);
		table[m][n]='<';
	}
	n=index('#');
	for(t=0;t<LASTVT[0][0];t++)
	{
		m=index(LASTVT[0][t+1]);
		table[m][n]='>';
	}
	table[n][n]='=';
}


void firstvt(char c)               
{
	int i,j,k,m,n;
	for(i=0;i<r;i++)
	{
		if(grammar[i][0]==c)
		break;
	}
	if(FVT[i]==0)
	{
		n=FIRSTVT[i][0]+1;
		m=0;
		do
		{
			if(m==2||grammar[i][m]=='|')
			{
				if(is_T(grammar[i][m+1]))
				{
					FIRSTVT[i][n]=grammar[i][m+1];
					n++;
				}
			else
			{
				if(is_T(grammar[i][m+2]))
				{
					FIRSTVT[i][n]=grammar[i][m+2];
					n++;
				}
				if(grammar[i][m+1]!=c)
				{
					firstvt(grammar[i][m+1]);
					for(j=0;j<r;j++)
					{
						if(grammar[j][0]==grammar[i][m+1])
						break;
					}
					for(k=0;k<FIRSTVT[j][0];k++)
					{
						int t;
						for(t=0;t<n;t++)
						{
							if(FIRSTVT[i][t]==FIRSTVT[j][k+1])
							break;
						}
						if(t==n)
						{
						 FIRSTVT[i][n]=FIRSTVT[j][k+1];
						 n++;
						}
					}
				}
			}
		}
		m++;
	}
	while(grammar[i][m]!='\0');
	FIRSTVT[i][n]='\0';
	FIRSTVT[i][0]=--n;
	FVT[i]=1;
	}
}


void lastvt(char c)                                    
{
	int i,j,k,m,n;
	for(i=0;i<r;i++)
	{
		if(grammar[i][0]==c)
			break;
	}
 
	if(LVT[i]==0)
	{ 
		n=LASTVT[i][0]+1; 
		m=0;
  
		do 
		{  
			if(grammar[i][m+1]=='\0'||grammar[i][m+1]=='|')  
			{   
				if(is_T(grammar[i][m]))   
				{
    				LASTVT[i][n]=grammar[i][m];
					n++;
				}    
				else    
				{    
					if(is_T(grammar[i][m-1]))     
					{      
						LASTVT[i][n]=grammar[i][m-1];     
						n++;     
					}
     
					if(grammar[i][m]!=c)    	
					{      
						lastvt(grammar[i][m]);	  
						for(j=0;j<r;j++)     
							if(grammar[j][0]==grammar[i][m])     
								break;    
    
						for(k=0;k<LASTVT[j][0];k++)     
						{     
							int t;	 
							for(t=0;t<n;t++)     
								if(LASTVT[i][t]==LASTVT[j][k+1])      
									break;      
      
							if(t==n)      
							{     
								LASTVT[i][n]=LASTVT[j][k+1];       
								n++;      
							}    
						}    
					}  
				}  
			}  
			m++;
		}while(grammar[i][m]!='\0');

		LASTVT[i][n]='\0'; 
		LASTVT[i][0]=--n;
		LVT[i]=1;
	}
}


int test_s()
{
	int i,j,x,y,z;                                            
	k=1;
	s[k]='#';                                         
	printf("栈             输入串         动作\n");
	for(i=0;input_s[i]!='\0';i++);                     
	z=i--;
	i=0;
	while((a=input_s[i])!='\0')
	{
		if(is_T(s[k]))
		j=k;
		else
		j=k-1;
		x=index(s[j]);
		y=index(a);
		if(table[x][y]=='>')
		{
			stack_p(1,k,s);
			printf("%c",a);
			stack_p(i+1,z,input_s);
			printf("规约\n");
			do
			{
				q=s[j];
				if(is_T(s[j-1]))
				{
					j=j-1;
					if(j<=0)
					{
						printf("输入串错误\n");
						exit(-1);
					}
				}
				else 
				{
					j=j-2;
					if(j<=0)
					{
						printf("输入串错误\n");
						exit(-1);
					}
				}
				x=index(s[j]);
				y=index(q);
			}while(table[x][y]!='<');
			
			int m,n,N;

			int N1;//存放规约符号标号
			char tep[100];//存放最左素短语
			for(int x=j+1;x<=k;x++)
			{
				tep[x]=s[x];
			}

			for(m=j+1;m<=k;m++)  
			{		
				for(N=0;N<r1;N++)		
					for(n=1;str_in[N][n]!='\0';n++)		
					{			
						if(!is_T(s[m])&&!is_T(str_in[N][n]))			
						{				
							if(is_T(s[m+1])&&is_T(str_in[N][n+1])&&s[m+1]==str_in[N][n+1])					
							{						
								s[j+1]=str_in[N][0];
								N1=N;
								break;					
							}
						}
						else				
							if(is_T(s[m]))
								if(s[m]==str_in[N][n])
								{
									s[j+1]=str_in[N][0];
									N1=N;
									break;
								}
					}
			}

			//.................
			//N为根节点,s[j+1--k]为子节点
			char *c_n=new char[2];
			c_n[0]=str_in[N1][0];
			c_n[1]='\0';
			TreeNode *s2 = new_node(c_n);
			
			for(int x=k;x>=j+1;x--)
			{
				char *c_t=new char[2];
				c_t[0]=tep[x];
				c_t[1]='\0';
				TreeNode *s1 = new_node(c_t);
				if(tep[x]>='A'&&tep[x]<='Z')
				{
					add_node(s2,sn[sn_c]);
					sn_c--;
				}
				else
				{
					add_node(s2,s1);
				}
			}
			sn_c++;
			sn[sn_c]=s2;
			//......................


			k=j+1;
	
			if(k==2&&a=='#')
			{
				stack_p(1,k,s);
				printf("%c",a);
				stack_p(i+1,z,input_s);
				printf("接受\n");
				printf("accept\n");

				printf("\n生成的语法树: \n");
				printTree(sn[sn_c],0,0);
				deleteTree(sn[sn_c]);
				return 1;                               //规约成功
			}
		}
  
		else   
			if(table[x][y]=='<'||table[x][y]=='=')   
			{                                                //移进操作  
				stack_p(1,k,s);	
				printf("%c",a);  
				stack_p(i+1,z,input_s);   
				printf("移进\n");   
				k++;   
				s[k]=a;  
				i++;   
			}
			else   
			{    
				printf("\n该单词串不是该文法的句子\n");
				return 0;
			}
	}
 
	printf("\n该单词串不是该文法的句子\n");
	return 0;
}

void stack_p(int j,int k,char *s)
{
	int n=0;
	int i;

	for(i=j;i<=k;i++)
	{
		printf("%c",s[i]);
		n++;
	}
 
	for(;n<15;n++)
	{
		printf(" ");
	}
}

int index(char c)                    //计算下标
{
	int i;
	for(i=0;T_label[i]!='\0';i++)
	{
		if(c==T_label[i])
			return i;
	}
	return -1;
}

int is_T(char c)                       //判断非终结符
{
	int i;
	for(i=0;T_label[i]!='\0';i++)
	{
		if(c==T_label[i])
			return 1;
	}
	return 0;
}

int main()     
{
	int i,j,k=0;
	r = 0;
	bool flag=0;
	printf("输入产生式，以#结束");
	//S->a|^|(T)
	//T->T,S|S
	for(i=0;;i++)
	{
		scanf("%s",grammar[i]);    
		FIRSTVT[i][0]=0;            
		LASTVT[i][0]=0;
		for (j = 0;grammar[i][j]; j++)
			if (grammar[i][j] == '#')
			{
				if (j)
					r = i+1;
				else
					r = i;
				flag = 1;
				grammar[i][j] = '\0';
				break;
			}
		if (flag)
			break;
	}

	for(i=0;i<r;i++)                           //判断是否为算符文法
	{
		for(j=0;grammar[i][j]!='\0';j++)
		{
			if(grammar[i][0]<'A'||grammar[i][0]>'Z')
			{
				printf("该文法不是算符文法\n!");
				exit(-1);
			}
			if(grammar[i][j]>='A'&&grammar[i][j]<='Z')
			{
			    if(grammar[i][j+1]>='A'&&grammar[i][j+1]<='Z')
			   {
				   printf("该文法不是算符文法\n!");
				   exit(-1);
			   }
			}
		}
	}
	for(i=0;i<r;i++)
	{
		for(j=0;grammar[i][j]!='\0';j++)
		{
			if((grammar[i][j]<'A'||grammar[i][j]>'Z')&&grammar[i][j]!='-'&&grammar[i][j]!='>'&&grammar[i][j]!='|') 
				T_label[k++]=grammar[i][j];
		}
	}
	T_label[k]='#';
	T_label[k+1]='\0';
	P_table();
	printf("\nFIRSTVT集\n");    
	for(i=0;i<r;i++)
	{
		printf("%c: ",grammar[i][0]);
		for(j=0;j<FIRSTVT[i][0];j++)
		{
			printf("%c ",FIRSTVT[i][j+1]);
		}
		printf("\n");
	}
	printf("\nLASTVT集\n");    
	for(i=0;i<r;i++)
	{
		printf("%c: ",grammar[i][0]);
		for(j=0;j<LASTVT[i][0];j++)
		{
			printf("%c ",LASTVT[i][j+1]);
		}
		printf("\n");
	}
	printf("\n算符优先分析表:\n");

	for(i=0;T_label[i]!='\0';i++)
		printf("\t%c",T_label[i]);
	
	printf("\n");

	for(i=0;i<k+1;i++)
	{
		printf("%c\t",T_label[i]);

		for(j=0;j<k+1;j++)
		{
			printf("%c\t",table[i][j]);
		}
		printf("\n");
	}

	printf("\n输入单词串\n");
	// (a,(a,a))#
	scanf("%s",input_s);
	
	test_s();
	return 0;
}
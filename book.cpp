#include<stdio.h>
#include<windows.h>
#include<mysql.h>
#include <winsock.h>
#include<iostream>
#include<stdlib.h>
#include<conio.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"libmysql.lib")

MYSQL mysql;
MYSQL_RES *result;
MYSQL_ROW row;
char id[5],bookname[50],author[30],bookconcern[50];//书的id号,书名，作者，出版社

char ch[2];
void showmenu();
void showall();
void addbooks();
void modify();
void deletebook();
void query();
void inquire();
int connect();
int main()
{
     int n;
	 showmenu();
	 scanf("%d",&n);
	 while(n)
	 {
	       switch(n)
		   {
		      case 1:
				  showall();
				  break;
			  case 2:
				  addbooks();
				  break;
			  case 3:
				  modify();
				  break;
			  /*case 4:
				  deletebook();
				  break;
			  case 5:
				  query();
				  break;
			  case 6:
				  exit(0);*/
			  default:break;
		   }
		   scanf("%d",&n);
	 }
	 return 0;
}
void showmenu()
{
     system("cls");
	 printf("\n\n\n\n\n");
	 printf("\t|-------------------------------------------|\n");
	 printf("\t|       Welcome To Learn Books System       |\n");
	 printf("\t|-------------------------------------------|\n");
	 printf("\t|\t1-show all                          |\n");
	 printf("\t|\t2-add books                         |\n");
	 printf("\t|\t3-modify book                       |\n");
	 printf("\t|\t4-delete book                       |\n");
	 printf("\t|\t5-query book                        |\n");
	 printf("\t|\t6-exit                              |\n");
	 printf("\t        ENTER YOUR CHOICE(1-6):");
}
void inquire()
{
     printf("\tshow the main menu?(y/n):");
	 scanf("%s",ch);
	 if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
	 {
	     showmenu();
	 }
	 else
	 {
	    exit(0);
	 }
}
//连接数据库的方法
int connect()
{
	 if (NULL != mysql_init(&mysql)) {
        cout << "mysql_init() succeed" << endl;
    } else {
        cout << "mysql_init() failed" << endl;
        return 0;
    } 
    
	if (0 == mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk")) {
        cout << "mysql_options() succeed" << endl;
    } else {
        cout << "mysql_options() failed" << endl;
        return 0;
	}
    if(!mysql_real_connect(&mysql,"127.0.0.1","root","lixiao116611","db_book",3306,NULL,0))
	{
	   // printf("\n\t Can not connect bookmanager\n");
		return 0;
	}
	else
	{
	    // printf("成功\n");
		 return 1;
	}
}
//显示所有图书信息
void showall()
{   system("cls");

    if(!connect())
	{
	    printf("\n\t Can not connect bookmanager\n");
	}
	else
	{
	     printf("成功\n");
		 if(mysql_query(&mysql,"select*from tb_books"))
		 {
		     printf("\n\tQuery tb_books failed\n");
		 }
		 else
		 {
		     result=mysql_store_result(&mysql);
			 if(mysql_num_rows(result)!=0)
			 {
			         
					 printf("\n\n\n\n\n");
					 printf("\t|--------------------------------------------------|\n");
					 printf("\t|               Show all the books                 |\n");
					 printf("\t|--------------------------------------------------|\n");
					    printf("\t|ID      BookName     Author       Bookconcern     |\n");
					 printf("\t|--------------------------------------------------|\n");
					 while((row=mysql_fetch_row(result)))
					 {
					    printf("\t|%-2s     %-8s     %-6s       %-11s      |\n",row[0],row[1],row[2],row[3]);
					 }
					    printf("\t|--------------------------------------------------|\n");
			 }
			 else
			 {
			     printf("no record\n");
			 }
			 mysql_free_result(result);
		 }
		 mysql_close(&mysql);
	}
	inquire();
}
void addbooks()
{   char dest[100]={""};
    char*sql;
    if(!connect())
	{
	    printf("\n\t Can not connect bookmanager\n");
	}
	else
	{
	    printf("\t-----------------------------------------\n");
		printf("\t               ADD Books                 \n");
		printf("\t-----------------------------------------\n");
		printf("ID:");
		   
		scanf("%s",id);
		sql="select*from tb_books where ID=";
		strcat(dest,sql);
		strcat(dest,id);
		if(mysql_query(&mysql,dest))
		{
		    printf("\n\t the query failed!\n");
			
		}
		else
		{
		   result=mysql_store_result(&mysql);
		   
		   //row=mysql_fetch_row(result);
		   
		   
		   if(mysql_num_rows(result)!=0)
		   {
			     cout<<mysql_num_rows(result)<<endl;
		         printf("\n The ID has existe!\n");
				 
		   }
		   else
		   {     //mysql_free_result(result);
				 //mysql_close(&mysql);
			     printf("\nbookname:");
		         scanf("%s",bookname);
		         printf("\nauthor:");
		         scanf("%s",author);
		         printf("\nbookconcern:");
		         scanf("%s",bookconcern);
				 char dest2[100]={""};
				 sql="insert into tb_books(ID,bookname,author,bookconcern) values(";
				 strcat(dest2,sql);
				 strcat(dest2,"'");
				 strcat(dest2,id);
				 
				 strcat(dest2,"','");
				 strcat(dest2,bookname);
				 strcat(dest2,"','");
				 strcat(dest2,author);
				 strcat(dest2,"','");
				 strcat(dest2,bookconcern);
				 strcat(dest2,"')");
		         if(mysql_query(&mysql,dest2)!=0)
				 {
				      fprintf(stderr,"can not insert record!",mysql_error(&mysql));
					 
				 }
				 else
				 {
				      printf("插入成功\n");
					  
				 }
		   }
		   mysql_free_result(result);
		}
	}mysql_close(&mysql);
	inquire();
}
//修改图书信息方法modify()
void modify()
{   char id[5];
    char dest[100]={""};
	char dest2[100]={""};
	char*sql;
    if(!connect())
	{
	    printf("\n\t Can not connect bookmanager\n");
	}
	else
	{
	    printf("\tplease input the book'ID that you want to modify!:");
		scanf("%s",id);
		sql="select * from tb_books where ID=";
		strcat(dest,sql);
		strcat(dest,id);
		mysql_query(&mysql,dest);
		result=mysql_store_result(&mysql);
		if(mysql_num_rows(result)==0)
		{
		     printf("\n\t您要修改的书的ID不存在！");
		}
		else
		{
		     printf("\n\t找到相关记录，显示出来吗（y/n）:");
			 scanf("%s",ch);
			 if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)
			 {
			     printf("\n\t---------------------------------------");
				 printf("\n\t       Show   Book                     ");
				 printf("\n\t---------------------------------------");
				 printf("\n\tID    BookName    Author    Bookconcern");
				 row=mysql_fetch_row(result);
				 printf("\n\t%-2s    %-8s    %-6s    %-11s",row[0],row[1],row[2],row[3]);
				 printf("\n\t---------------------------------------");
				 printf("\n\tBookname:");
				 scanf("%s",bookname);
				 printf("\n\tAuthor:");
				 scanf("%s",author);
				 printf("\n\tBookconcern:");
				 scanf("%s",bookconcern);
				 sql="update tb_books set bookname='";
				 strcat(dest2,sql);
				 strcat(dest2,bookname);
				 strcat(dest2,"',author='");
				 strcat(dest2,author);
				 strcat(dest2,"',bookconcern='");
				 strcat(dest2,bookconcern);
				 strcat(dest2,"'where ID=");
				 strcat(dest2,id);
				 if(mysql_query(&mysql,dest2)!=0)
				 {
				      fprintf(stderr,"\n\tcan not modify record!\n",mysql_error(&mysql));
				 }
				 else
				 {
				     printf("\tModify success!\n");
				 }
			 }
		}mysql_free_result(result);
	}
	mysql_close(&mysql);
	inquire();
}

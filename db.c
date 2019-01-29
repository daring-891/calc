#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"

attend_rec db[100];
int db_size = 0;

/* reset the database for testing */
int clear_db()
{
  db_size = 0;
  return TRUE;
}

/*
  Story 1: As a teacher, I want a user interface for my database.
*/

int is_whitespace(char c) {
  return (' ' == c || '\t' == c || '\n' == c);
}

char get_first_non_white(char *s) {
  for (int i = 0; '\0' != s[i] && i < 80; i++) {
    if (!is_whitespace(s[i])) {
      return(s[i]);
    }
  }
  return('\0');
}

char get_command()
{
  char buffer[80];
  printf("Enter operator> ");
  scanf("%80s", buffer);
  return get_first_non_white(buffer);
}

// Returns FALSE when 'x' enter; TRUE otherwise
int execute_command(char c)
{
  int sno;
  attend_rec ar;
  switch (c) {
  case 'a':
    scanf_attend(&ar);
    add(ar);
    printf_attend(ar);
    return TRUE;
  case 'l':
    list();
    return TRUE;
  case 'i':
    initialize_db();
    return TRUE;
  case 'f':
    sno = get_sno();
    ar = find(sno);
    if (ar.sno == -1) {
      printf("Student %d not found\n", sno);
    } else {
      printf_attend(ar);
    }
    return TRUE;
  case 'm':
    scanf_attend(&ar);
    modify(ar);
    return TRUE;
  case 'd':
    sno = get_sno();
    delete(sno);
    return TRUE;
  case 'x':
    	exit(0);
	return TRUE;
  default:
    printf("Invalid command\n");
    return TRUE;
  }
}

/*
  Story 2: As a teacher, I want to add a student to my database, so I
  can track his or her record.
*/

void scanf_attend(attend_rec *r)
{ 
	int i=0;
	printf("enter serial number>");
	scanf("%d",&r->sno);
	printf("Enter name>");
	scanf("%s",r->name);
	printf("Enter Attenance>");
	scanf("%d",&r->present);
	while(r->present!=1&&r->present!=0&&i<10)
	{
		printf("wrong input try again");
		scanf("%d",&r->present);
		i++;
	}
}

void printf_attend(attend_rec r)
{
	printf("%s",r.name);
	if(r.present==1)
	printf(" is present\n");
	else if(r.present==0)
	printf("is absent\n");
}

int add(attend_rec r)
{
	if(db_size<100)
{
	db[db_size]=r;
	db_size++;
}
	else 
	printf("db is full\n"); 
 return TRUE;
}

/*
  Story 3: As a teacher, I want to be see all of the students in my
  class, so I can see who is present and absent.
 */
void list()
{
	for(int i=0;i<db_size;i++)
	{
		printf("%d\t",db[i].sno);
		printf("%s",db[i].name);
		printf("\t%s\n",(db[i].present==1? "present" : "absent"));	

	}


}
/*
   Story 4: As a programmer, I want to add a set of records to my
   database for testing purposes.
*/

void initialize_db()
{	
	if(db_size+10<100)
	{
		for(int i=db_size;i<db_size+10;i++)
		{
			 db[i].sno=i;
			strcpy(db[i].name,"student");
			db[i].name[7]=i+'0';
			db[i].present=rand()%2;

		}
		db_size+=10;
	}
	else
	{
		printf("not enough space available\n");
	}
}


/*
  Story 5: As a teacher, I want to be find a student's record so I can
  see whether a student was present or absent for a class.
*/

// We need a special record to return when the one we are looking for
// is not found
attend_rec not_found = {.sno = -1,
			.name = "none",
			.present = -1};

// Prompt the user for a serial number and read from keyboard
int get_sno()
{	
		int sno=0;
	printf("Enter student's Sno>");
	scanf("%d",&sno);
	
  return sno;
}

attend_rec find(int sno)
{
	int i;
	for(i=0;i<db_size;i++)
	{
		if(db[i].sno==sno)
		break;
	}
	if(i==db_size)
	return not_found;
	else
  return db[i];
}

/*
  Story 6: As a teacher, I want to modify a student's record, so I can
  correct mistakes.
*/

int modify(attend_rec r)
{	int i;
	char ch;
	for(i=0;i<db_size;i++)
	{
		if(db[i].sno==r.sno)
		{	
			db[i]=r;
			break;
		}
	}
	if(i==db_size)
	{
		printf("no match found \n Dp you want to add(y/n)> ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
		{
			add(r);
			list();
		}
		return TRUE;
	}
		
		
	else
	{
		printf("%d: %s %s \n ",db[i].sno,db[i].name,(db[i].present==1 ? "present" : "absent"));
	 	return TRUE;
	}

}
/*
  Story 7: As a teacher, I want to delete a student's record, so I can
  drop a student from the class.
*/

int find_index(int sno)
{
	int i=0;
	for(i=0;i<db_size;i++)
	{
		if(db[i].sno==sno)
		break;
	}
	if(i==db_size)
  return -1;
	else
	return i;
}

int delete(int sno)
{	int pos,i;
	pos=find_index(sno);
	if(pos==-1)
	{
		printf("Student not found\n");
		return TRUE;
	}
	else
	{

	for(i=pos;i<db_size-1;i++ )
	{
		db[i]=db[i+1];
		
	}
		db_size--;
		list();
		return TRUE;
	}
}

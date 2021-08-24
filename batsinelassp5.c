/* -----------------------------------------------------------------------------------------------

Program file:  friends_program.c
Author:        Stavros Batsinelas
Date:          July 24, 2021
Assignment:    #5
Objective:     This program receives people's data from a file and outputs it. The user inputs 
			   the file name then selects to either create a report, sorted by last name, or 
			   shipping labels, sorted by zip code. The program prints copies of the sorted info 
			   to the screen and to an output file.

----------------------------------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


/* Define structures */

	struct date
	{
		int yyyy;
		int mm;
		int dd;
	}; /* end date */

	struct name
	{
		char lname[15];
		char fname [10];
		char middle_initial;
	}; /* end name */

	struct info
 	{
		struct name lfm;
		char address[20];
		char city[15];
		char state[3];
		long zip;
		struct date fdate;
 	}; /* end struct info */


/* Function prototypes */

char nice_time(char[]);

void sort_them(struct info *, int, char); 


main()
{	
 	
 	/* Declare variables */
 	
 	struct  info people[100], *people_ptr = &people[0]; 
 	FILE    *in_file_ptr, *out_file_ptr;
 	char    file_name[30], big_name[22], date_and_time[30]=" ", c, sort_by;
 	int     i, count = 0, menu;
 	
 	char    header1[] = "                             My Friends Report";
 	char 	header2[] = "  Name               Address              City         "
					  " State   Zip      Friended";
					  
 	
 	/* Print welcome message and receive input for file name */
 	
 	printf("Welcome to the Friends program.\n\n");
 	
	printf("Enter file name: ");
	scanf("%29[^\n]", file_name);
	while ((c = getchar () != '\n') && c != EOF);
 	
 	
	/* Open the input file. */
 	
	in_file_ptr = fopen (file_name, "r");

	if (in_file_ptr == NULL)
	{
		printf ("\n Cannot open file %s for reading.\n", file_name);
		return 1;
	} /* end if */
   	
   	
   	/* add data from file to people structure, up to 100 */
   	
   	for (i = 0; !feof(in_file_ptr) && i < 100; i++)
   	{
 
   		fscanf (in_file_ptr, "%[^\n]\n", &people[i].lfm.lname);   	                                        /* read last name  */
   		fscanf (in_file_ptr, "%[^\n]\n", &people[i].lfm.fname);   	                                        /* read first name  */
   		fscanf (in_file_ptr, "%[^\n]\n", &people[i].lfm.middle_initial);                                    /* read middle initial  */
      	fscanf (in_file_ptr, "%[^\n]\n", &people[i].address);                                               /* read address  */
      	fscanf (in_file_ptr, "%[^\n]\n", &people[i].city);                                                  /* read city  */
       	fscanf (in_file_ptr, "%[^\n]\n", &people[i].state);                                                 /* read state */
      	fscanf (in_file_ptr, "%d", &people[i].zip);                                                         /* read zip   */
      	fscanf (in_file_ptr, "%d/%d/%d", &people[i].fdate.mm, &people[i].fdate.dd, &people[i].fdate.yyyy);  /*read date friended */
      	
        count++;

      	/* Read in either the \n after the data friended, or the EOF indicator and end of input file.    */
 
      	fgetc (in_file_ptr);
 
   	}  /* end for loop */
   	
   	
   	/* Call nice time function to calculate current time */
  	 		
	nice_time(date_and_time);
   	
   	
   	/* Print friends count */
   	
   	printf("\nYou have %i friends.\n", count);
   	
   	
   	/* do loop that ensures menu runs until user exits program */
   	
   	do 
	{
		printf("\n     Main Menu     \n");
		printf("--------------------\n");
		printf("(1)   Print Report\n");
		printf("(2)   Print Labels\n");
		printf("(3)   Exit Program\n\n");
   	
		printf("Please enter your selection: ");
		scanf("%i", &menu);
		while ((c = getchar () != '\n') && c != EOF);
		
   	
   		/* Option 1 - Print Report */
   	
   		if (menu == 1)
   		{
   			
  	 		/* Call sort function to sort people by last name */
  	 		
  	 		sort_by = 'n';
  	 		
  	 		sort_them(people_ptr, count, sort_by);
  	 		
  	 		
   			/* open the output file */
   	
   			out_file_ptr = fopen ("report5.txt", "w");

   			if ( out_file_ptr == NULL )
   			{
    	   		printf ("\n Cannot open file report5.txt for writing.\n");
     	   		return 1;
  	 		}// end if
  	 		
  	 		
  	 		/* print report header to screen */
  	 		
  	 		printf ("\n%s          %s\n", header1, date_and_time);
			printf ("\n%s\n", header2);
			
			for ( i=1; i<=82; i++ ) 
				printf ("-");  
				
			printf ("\n");
			
			
			/* print copy of report header to output file */
			
			fprintf (out_file_ptr, "%s          %s\n", header1, date_and_time);
			fprintf (out_file_ptr, "\n%s\n", header2); 
			
			for ( i=1; i<=82; i++ ) 
				fprintf (out_file_ptr, "-"); 
				
			fprintf (out_file_ptr, "\n");
			
  	 	
  	 		/* for loop copies each person to output file then prints for report */
  	 		
  	 		for ( i = 0; i < count; i++ )
   			{
   				
   				/* concatenates each person's name structure to variable big_name in format "Last, First Middle" */
				
				strcpy(big_name, people[i].lfm.lname);
				strcat(big_name, ", ");
				strcat(big_name, people[i].lfm.fname);
				strcat(big_name, " ");
				strncat(big_name, &people[i].lfm.middle_initial, 1);
   				
   				
      			/* Write name, address, city, state, and zip code to output file. */
      			
    			fprintf (out_file_ptr, "%-20s%-20s %-15s %-4s  %.5d    %.2d/%.2d/%.4d\n\n", big_name, people[i].address, 
						 people[i].city, people[i].state, people[i].zip, people[i].fdate.mm, people[i].fdate.dd, 
						 people[i].fdate.yyyy);		
				
				
				/* echo data to display screen */
				
  				printf ("%-20s%-20s %-15s %-4s  %.5d    %.2d/%.2d/%.4d\n\n", big_name, people[i].address, people[i].city, 
				  		 people[i].state, people[i].zip, people[i].fdate.mm, people[i].fdate.dd, people[i].fdate.yyyy);

   			} /* end for */
   			
   			
   			/* close output file and print confirmation of its creation */
   			
   			fclose (out_file_ptr);
   			
   			printf ("                    (Report has been sent to report5.txt)\n\n");
   			
   		} /* end if */
   		
   		
   		/* Option 2 - Print Labels */

		if (menu == 2)
   		{
   			
   			/* Call sort function to sort people by zip code */
   			
   			sort_by = 'z';
  	 		
  	 		sort_them(people_ptr, count, sort_by);
   			
   			
   			/* open the output file */
   	
   			out_file_ptr = fopen ("label5.txt", "w");

   			if ( out_file_ptr == NULL )
   			{
    	   		printf ("\n Cannot open file label5.txt for writing.\n");
     	   		return 1;
  	 		}/* end if */
  	 		
  	 		
  	 		/* for loop creates labels for each person, copies to output file, and prints to screen */
  	 		
  	 		for ( i = 0; i < count; i++ )
   			{
   				
   				/* concatenates each person's name structure to variable big_name in format "First Middle Last" */
   				
   				strcpy(big_name, people[i].lfm.fname);
				strcat(big_name, " ");
				strncat(big_name, &people[i].lfm.middle_initial, 1);
				strcat(big_name, " ");
				strcat(big_name, people[i].lfm.lname);
				
				
				/* Copy person's info in label format to output file */
				
				fprintf (out_file_ptr, "%s\n", big_name);
				fprintf (out_file_ptr, "%s\n", people[i].address);
				fprintf (out_file_ptr, "%s, %s %.5d\n\n", people[i].city, people[i].state, people[i].zip);
				
				
				/* Print a copy of info to screen */
				
				printf("\n%s\n", big_name);
				printf("%s\n", people[i].address);
				printf("%s, %s %.5d\n", people[i].city, people[i].state, people[i].zip);
   			
   			} /* end for */
  	 		
  	 		
  	 		/* close output file and print confirmation of its creation */
   			
   			fclose (out_file_ptr);
  	 		
  	 		printf ("\n(Labels have been sent to label5.txt)\n\n");
  	 		
   		} /* end if */
   		
   		
   		/* Error message if a valid menu option is not input */
   		
   		if (menu != 1 && menu != 2 && menu != 3)
   			printf ("\nYour entry was invalid. Please try again.\n");
	 
	} while (menu != 3);
	
	
	/* if Option 3 is selected close input file and print goodbye message */
   			
	fclose (in_file_ptr);
	
	printf ("\nThank you for using this program. Goodbye!\n");
	
} /* end main */


/* Function nice_time */

char nice_time(char str2[])
{

    char str1[27], ampm[5] = "a.m.";
	char day[4], mon[4], dow[3], tim[9], yr[5];
	char hra[3];
	int i, j, hr;
	

	/* time stuff starts here */
	
	time_t rawtime;   
    struct tm *timeptr;
    
    time(&rawtime);
  	timeptr = localtime(&rawtime);

   	/* time stuff ends here */
	strncpy(str1, asctime(timeptr), 24);

	strncpy(str2, str1, 4);
	strncat(str2, &str1[4], 4);
	strncat(str2, &str1[8], 2);
	strcat(str2,", ");
	strncat(str2, &str1[20], 4);
	strcat(str2," ");	
	strncpy(tim, &str1[11], 8);
 	
    hr = atoi(tim);

   	if(hr >= 12)  
   	  ampm[0] = 'p';
   	  
   	if (hr==24) strcat(str2, "12");
	if (hr==23) strcat(str2, "11");
	if (hr==22) strcat(str2, "10");
	if (hr==21) strcat(str2, "9");
	if (hr==20) strcat(str2, "8");
	if (hr==19) strcat(str2, "7");
	if (hr==18) strcat(str2, "6");
	if (hr==17) strcat(str2, "5");
	if (hr==16) strcat(str2, "4");
	if (hr==15) strcat(str2, "3");
	if (hr==14) strcat(str2, "2");
	if (hr==13) strcat(str2, "1");
	if (hr==12) strcat(str2, "12");
   	if (hr==11) strcat(str2, "11");
	if (hr==10) strcat(str2, "10");
	if (hr==9) strcat(str2, "9");               
	if (hr==8) strcat(str2, "8");
	if (hr==7) strcat(str2, "7");
	if (hr==6) strcat(str2, "6");
	if (hr==5) strcat(str2, "5");
	if (hr==4) strcat(str2, "4");
	if (hr==3) strcat(str2, "3");
	if (hr==2) strcat(str2, "2");
	if (hr==1) strcat(str2, "1");


	strncat(str2, &tim[2], 3);
	strcat(str2," ");
	strcat(str2,ampm);
 
} /* end nice time */


/* Function sort_them */

void sort_them(struct info *them, int entries, char sort_by)
{
	
	char swap = 'y';
	struct info temp, *that, *next, *end = them + entries;

	while(swap == 'y')
	{
		
		that = them;
		next = them;
		next++;
		swap = 'n';
	  		  	
 		while(next != end)
	  	{	
	  	
			if( (sort_by == 'n' && strcmp(that->lfm.lname, next->lfm.lname) > 0)
				|| (sort_by == 'n' && strcmp(that->lfm.lname, next->lfm.lname) == 0 && strcmp(that->lfm.fname, next->lfm.fname) > 0)
				|| (sort_by == 'n' && strcmp(that->lfm.lname, next->lfm.lname) == 0 && strcmp(that->lfm.fname, next->lfm.fname) == 0 && strcmp(that->lfm.middle_initial, next->lfm.middle_initial) > 0)
				|| (sort_by == 'z' && that->zip > next->zip)  )
			{
				temp = *that;
				*that = *next;
				*next = temp;	
				
				swap = 'y';	    
			} /* end if */
			
			that++;
			next++;	
				
	  	}  /* end while */
	  	
	} /* end while */
	
}  /* end sort_them */

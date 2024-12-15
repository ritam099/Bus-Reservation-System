#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char ADMINID[6] = "adm12";         //define admin id
const char ADMINPASS[10] = "admin123";   //define admin password

int NUMBER_OF_BUSES = 50;
int NUMBER_OF_TICKETS = 100;               //store the number of tickets in the ticketdetails file
int NUMBER_OF_USERS = 50;

#define MAXDROP 5    //maximum drop point for a bus

struct user {
	int user_id;
	char user_name[10];
	char user_password[15];
	char phone_no[10];
};

struct bus {
	int bus_no;
	char boarding_point[20];
	int num_drop_loc;
	char drop_locations[MAXDROP][20];
	int no_of_seats;
	int available_no_seats;
	int boarding_time[4];
};

struct ticket {
	char user_name[10];
	int ticket_id;
	char board_point[10];
	char drop_point[10];
	int bus_no;
	float price;
	int num_passenger;
	char date[10];
	int time;
};
struct dates {
	int month;
	char date[3];
};


void main()
{

	int ch;            //main menu choice
	FILE *ptr;           //file pointer
	struct bus b;        //object of bus that stores records of file
	int bp;         //user boarding point
	int user_dp;    //user drop point
	struct ticket t;
	struct dates d;
	char user[10];
	char mon[15];
	char dropName[10];

	do {
		printf("\nChoose User");           //main menu
		printf("\n1. Admin ");
		printf("\n2. User");
		printf("\n3. EXIT");

		printf("\nEnter your choice:(1-3) ");
		scanf("%d",&ch);

		switch(ch)
		{
		case 1: //ADMIN
			char adminID[6],adminPass[10];

			printf("\nEnter AdminID: ");
			scanf("%s",adminID);

			printf("\nEnter Password: ");
			scanf("%s",adminPass);

			if((strcmp(ADMINID,adminID)==0) && (strcmp(ADMINPASS,adminPass)==0))      //admin authentication
			{
				int chA;
				do {
					printf("\nAdmin MENU");
					printf("\n1. Add a Bus");
					printf("\n2. View Bus Details (in ascending order)");
					printf("\n3. Add a User");
					printf("\n4. View Users (in ascending order)");
					printf("\n5. Logout");
					printf("\nEnter your choice (1-5): ");
					scanf("%d",&chA);

					switch(chA)
					{
					case 1: //Add a bus
						int dp;
						ptr = fopen("bus","ab");
						if(ptr==NULL)
						{
							printf("File not found");
							break;
						}

						printf("\nEnter Bus No: ");                //write bus details to file
						scanf("%d",&b.bus_no);

						printf("\nEnter Boarding Point: ");
						scanf("%s",b.boarding_point);

						printf("\nEnter No of Drop Points: ");
						scanf("%d",&b.num_drop_loc);
						for(int i = 0; i<b.num_drop_loc; i++)
						{
							printf("Enter Destination %d: ",i+1);
							scanf("%s",b.drop_locations[i]);
						}

						printf("\nEnter No of Seats: ");
						scanf("%d",&b.no_of_seats);

						b.available_no_seats = b.no_of_seats;

						for(int k=0; k<4; k++)
						{
							printf("\nEnter Boarding time %d: ",k+1);
							scanf("%d",&b.boarding_time[k]);
						}

						fwrite(&b,sizeof(struct bus),1,ptr);

						fclose(ptr);
						break;

					case 2: //View Buses
						struct bus *b3 = malloc(NUMBER_OF_BUSES * sizeof(struct bus));
						ptr = fopen("bus","rb");
						if(ptr==NULL)
						{
							printf("\nFile not found");
							free(b3);
							break;
						}
						size_t resultB = fread(b3,sizeof(struct bus),NUMBER_OF_BUSES,ptr);
						
						
						for(int i=0;i<resultB-1;i++)
						{
							for (int j = i + 1; j < resultB; j++) 
							{
								if(b3[i].bus_no > b3[j].bus_no)
								{
									struct bus temp = b3[i];
									b3[i] = b3[j];
									b3[j] = temp;
								}
							}
						}

						for(int i=0; i<resultB; i++)                       //display bus details after reading from file
						{
							if(b3[i].bus_no==0)
							{
								break;
							}
							printf("\nBus Number: %d\n",b3[i].bus_no);
							printf("\nBoarding Point: %s\n",b3[i].boarding_point);
							for(int j=0; j<b3[i].num_drop_loc; j++)
							{
								printf("\nDrop location: %d %s\n",j+1,b3[i].drop_locations[j]);
							}
							printf("\nNumber of seats: %d",b3[i].no_of_seats);
							printf("\n---------------------------------\n");
						}
						free(b3);
						fclose(ptr);
						break;

					case 3: //Add user
						struct user u;
						ptr = fopen("userDetails","ab");
						if(ptr==NULL)
						{
							printf("\nFile not found");
							break;
						}

						printf("\nEnter User ID: ");
						scanf("%d",&u.user_id);

						printf("\nEnter UserName: ");
						scanf("%s",u.user_name);

						printf("\nEnter User Password: ");
						scanf("%s",u.user_password);

						printf("\nEnter User Phone No: ");
						scanf("%s",u.phone_no);

						fwrite(&u,sizeof(struct user),1,ptr);
						fclose(ptr);
						break;

					case 4: //displaying users in ascending order
						struct user *u2 = malloc(NUMBER_OF_USERS * sizeof(struct user));
						ptr = fopen("userDetails","rb");
						if(ptr==NULL)
						{
							printf("\nFile not found");
							break;
						}
						size_t users = fread(u2,sizeof(struct user),NUMBER_OF_USERS,ptr);
                        fclose(ptr);
                        
						for(int i=0;i<users-1;i++)
						{
							for (int j = i + 1; j < users; j++) 
							{
								if(strcmp(u2[i].user_name,u2[j].user_name)>0)
								{
									struct user temp = u2[i];
									u2[i] = u2[j];
									u2[j] = temp;
								}
							}
						}

						for(int i=0;i<users;i++)
						{
							printf("\n----------------");
							printf("\nUser %d",i+1);
							printf("\nUser ID: %d",u2[i].user_id);
							printf("\nUserName: %s",u2[i].user_name);
							printf("\nPhoneNo: %s",u2[i].phone_no);
						}
						free(u2);
						break;
					case 5: //Logout
						strcpy(adminID,"");
						strcpy(adminPass,"");
						break;

					default:
						printf("\nInvalid Entry!!");
						break;
					}

				} while(chA!=4);
			}
			else
			{
				printf("\nWrong ID and Password");
			}
			break;

		case 2:
			int flag = 0;
			struct user u2;
			char userName[10],userPass[15];

			printf("\nEnter UserName: ");
			scanf("%s",userName);

			printf("\nEnter Password: ");
			scanf("%s",userPass);

			ptr = fopen("userDetails","rb");



			for(int i = 0; i<NUMBER_OF_USERS; i++)
			{
				size_t result = fread(&u2,sizeof(struct user),1,ptr);
				if((strcmp(u2.user_name,userName)==0) && (strcmp(u2.user_password,userPass)==0))
				{
					flag = 1;
					strcpy(user,u2.user_name);
				}
			}
			fclose(ptr);
			if(flag==0)
			{
				printf("\nUser not found!");
				break;
			}
			else
			{
				printf("\nLogin Successful");
			}

			int chU;
			if(flag==1)
			{
				do {
					printf("\n\nUser MENU");
					printf("\n1. Book seats");
					printf("\n2. Check My Ticket");
					printf("\n3. Logout");
					printf("\nEnter your choice: ");
					scanf("%d",&chU);
					switch(chU)
					{

					case 1:
						struct bus *b2 = malloc(NUMBER_OF_BUSES * sizeof(struct bus)); //bus structure defined
						int busNo,chT;
						ptr = fopen("bus","rb");
						if(ptr==NULL)
						{
							printf("\nFile not found");
							break;
						}
						size_t result = fread(b2,sizeof(struct bus),NUMBER_OF_BUSES,ptr);
						if(!result==NUMBER_OF_BUSES)
						{
							printf("\nError reading the data");
						}
						fclose(ptr);

						for(int i=0; i<result; i++)          //to display all the boarding points
						{
							if(strcmp(b2[i].boarding_point, "") == 0)
							{
								break;
							}
							else
							{
								printf("\n%d.%s",i+1,b2[i].boarding_point);
							}

						}
						printf("\nEnter your boarding point(1-%zu): ",result); //result stores number of records to retrieve and %zu is the format specifier for size_t data type
						scanf("%d",&bp);                                //user is choosing which boarding point

                        int flagBP = 0,no_drops;
						for(int i=0; i<NUMBER_OF_BUSES; i++)
						{
							if(strcmp(b2[i].boarding_point,b2[bp-1].boarding_point)==0)
							{
								for(int j=0; j<b2[i].num_drop_loc; j++)  //display the drop locations based on the chosen boarding point
								{
									printf("\n%d. %s",j+1,b2[i].drop_locations[j]);
									no_drops++;
								}
								break;
							}
							if(i==(result-1))
							{
							    printf("\nInvalid Boarding Point. Try again!");
							    flagBP = 1;
							    break;
							}
							
						}
						if(flagBP==1) //if flag is 1 then the boarding point is invalid and needs to restart
						{
						    break;
						}
						printf("\nEnter the drop location(1-%d): ",no_drops);
						scanf("%d",&user_dp);

						for(int i=0; i<NUMBER_OF_BUSES; i++)         //display drop points based on the boarding point
						{
							if((strcmp(b2[i].boarding_point,b2[bp-1].boarding_point)==0) && (user_dp < result))
							{
								busNo = b2[i].bus_no;
								printf("\nBus_No is: %d", b2[i].bus_no);
								printf("\nYour Boarding Point is: %s",b2[bp-1].boarding_point);
								printf("\nYour Drop Location is: %s", b2[i].drop_locations[user_dp-1]);
								strcpy(dropName,b2[i].drop_locations[user_dp-1]);
								break;
							}
							if(i==(result-1))
							{
							    printf("\nInvalid Dropping Point. Try again!");
							    flagBP = 1;
							    break;
							}
							
						}
						if(flagBP==1) //if flag is 1 means that the drop location is invalid and needs to restart
						{
						    break;
						}
							
						float cost = 100 * user_dp;                 //calculate cost per ticket
						printf("\nCost per ticket: %.2f", cost);

						char confirm;                               //store user confirmation whether to book or not
						printf("\nDo you want to book a seat?(Y/N)\nDISCLAIMER: Ticket is not cancellable nor refundable! ;D\n\n");
						scanf("%s",&confirm);

						int seats;
						if(confirm == 'Y')                //if user confirms then get date,time
						{
							printf("\nHow many seats do you want to book? ");
							scanf("%d",&seats);
							printf("\nOn what date do you want to travel (1-31): ");
							scanf("%s",d.date);
							printf("\nIn what month do you want to travel (1-12): ");
							scanf("%d",&d.month);
							if(d.month == 1)
							{
								strcpy(mon," January");
							}
							else if(d.month == 2)
							{
								strcpy(mon," February");
							}
							else if(d.month == 3)
							{
								strcpy(mon," March");
							}
							else if(d.month == 4)
							{
								strcpy(mon," April");
							}
							else if(d.month == 5)
							{
								strcpy(mon," May");
							}
							else if(d.month == 6)
							{
								strcpy(mon," June");
							}
							else if(d.month == 7)
							{
								strcpy(mon," July");
							}
							else if(d.month == 8)
							{
								strcpy(mon," August");
							}
							else if(d.month == 9)
							{
								strcpy(mon," September");
							}
							else if(d.month == 10)
							{
								strcpy(mon," October");
							}
							else if(d.month == 11)
							{
								strcpy(mon," November");
							}
							else if(d.month == 12)
							{
								strcpy(mon," December");
							}
							else {
								printf("\nInvalid Entry!!");
							}
                            
                            int z;
							for(int i=0; i<NUMBER_OF_BUSES; i++)
							{
								if(b2[i].bus_no == busNo)
								{
									printf("\nChoose Boarding Time: ");
									for(z=0; z<4; z++)
									{
										printf("\n%d. %d",z+1,b2[i].boarding_time[z]);
									}
								}
							}
							printf("\nChoose the time (1-%d): ",z);
							scanf("%d",&chT);

							for(int i=0; i<NUMBER_OF_BUSES; i++)
							{
								if(b2[i].bus_no == busNo)
								{
									t.time = b2[i].boarding_time[chT-1];
								}
							}

							for(int i=0; i<NUMBER_OF_BUSES; i++)       //reducing number of seats required from the available number of seats
							{
								if(b2[i].bus_no == busNo)
								{
									b2[i].available_no_seats -= seats;
								}
							}
							strcpy(t.user_name, user);
							t.ticket_id=rand();    //using rand function to generate ticket id for each user
							strcpy(t.board_point, b2[bp-1].boarding_point);
							strcpy(t.drop_point,dropName);
							t.bus_no=busNo;
							t.price=cost;
							t.num_passenger=seats;
							strcpy(t.date,d.date);
							strcat(t.date,mon);

							ptr = fopen("ticketDetails","ab");
							if(ptr==NULL)
							{
								printf("\nFile not found");
								break;
							}
							fwrite(&t,sizeof(struct ticket),1,ptr);
							fclose(ptr);
							printf("\nYour ticket has been booked");

						}
						else{
						    printf("\n\nSorry to hear that. Check our menu to proceed next!");
						}

						break;

					case 2:
						struct ticket *t1 = malloc(NUMBER_OF_TICKETS * sizeof(struct ticket));

						ptr = fopen("ticketDetails","rb");
						if(ptr==NULL)
						{
							printf("\nError in opening the file");
						}
						size_t tickets = fread(t1, sizeof(struct ticket),NUMBER_OF_TICKETS,ptr);


						for(int i=0; i<NUMBER_OF_TICKETS; i++)
						{
							if(strcmp(t1[i].user_name,user)==0)
							{
								printf("\n----------TICKET----------");
								printf("\nTicket ID: %d",t1[i].ticket_id);
								printf("\nBoarding Point: %s",t1[i].board_point);
								printf("\nDropping Point: %s",t1[i].drop_point);
								printf("\nBus No: %d",t1[i].bus_no);
								printf("\nPrice: %.2f",t1[i].price);
								printf("\nNo of Seats: %d",t1[i].num_passenger);
								printf("\nDate: %s",t1[i].date);
								printf("\nTime: %d",t1[i].time);
							}
						}
						free(t1);
						fclose(ptr);
						break;


					case 3:
						strcpy(user,"");
						break;

					}
				} while(chU!=3);

			}
			break;

		case 3:
			break;

		}
	} while(ch!=3);
}
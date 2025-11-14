#include"utility.h"
extern int total_slots;
void load_state(Vehicle *parking)
{
   FILE *fp = fopen(DATAFILE,"r");
   if(!fp)
   {
        for(int i =0;i<total_slots;i++)
        {
            parking[i].occupied =0;
            parking[i].slot_no = i+1;
            parking[i].plate[0]='\0';
            parking[i].owner[0] = '\0';
            parking[i].in_time = 0;
        }
        return;
   }
   if(fscanf(fp,"%d\n",&total_slots)!=1)
   {
    fclose(fp);
    return;
   }
   for(int i =0;i<total_slots;i++)
   {
    char line[256];
    if(!fgets(line,sizeof(line),fp))
    break;
    trim_newline(line);
    char *tok = strtok(line,"|");
    if(!tok)
    continue;
    int slotno = atoi(tok);
    tok = strtok(NULL,"|");
    if(!tok)
    continue;
    if(strcmp(tok,"FREE")==0)
    {
        parking[i].occupied =0;
        parking[i].slot_no = slotno;
        parking[i].plate[0]='\0';
        parking[i].owner[0] = '\0';
        parking[i].in_time = 0;
    }
    else
    {
        strcpy(parking[i].plate,tok);
        tok =strtok(NULL,"|");
        if(!tok)
        tok = " ";
        strcpy(parking[i].owner,tok);
        tok = strtok(NULL,"|");
        long t =0;
        if(tok)
        {
            t=atoi(tok);
            parking[i].in_time=(time_t)t;
            parking[i].occupied =1;
            parking[i].slot_no=slotno;
        }
    }
   }
   fclose(fp);
}
void trim_newline(char *str)
{
    if(!str)
    return;
    int len = strlen(str);
    if(len && str[len-1]=='\n')
    str[len-1]='\0';
}


void display_status(Vehicle *parking)
{
    printf("\n--- Parking Status (Total slots: %d) ---\n", total_slots);
    printf("%-6s %-12s %-20s %-20s\n", "Slot", "Status", "Plate", "In Time");
    for(int i = 0; i < total_slots; ++i)
    {
        printf("%-6d ", parking[i].slot_no);
        if(parking[i].occupied)
        {
            printf("%-12s %-20s ", "OCCUPIED", parking[i].plate);
            display_time(parking[i].in_time);
            printf("\n");
        }
        else
        {
            printf("%-12s %-20s %-20s\n", "FREE", "-", "-");
        }
    }
}

void display_time(time_t t)
{
    if(t==0)
    {
        printf("N/A");
        return;
    }
    struct tm *tm_info = localtime(&t);
    char buf[64];
    strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S",tm_info);
    printf("%s",buf);
}

void park_vehicle(Vehicle *parking)
{
    char plate[MAX_PLATES];
    char owner[MAX_OWNER];
    printf("\nEnter vehicle plate number: ");
    scanf(" %[^\n]",plate);
    if(strlen(plate) == 0) 
    {
        printf("Plate cannot be empty.\n");
        return;
    }
    if(find_by_plate(plate,parking)!=not_exist)
    {
        printf("Vehicle with plate '%s' is already parked.\n", plate);
        return;
    }
    printf("Enter owner name (optional): ");
    scanf(" %[^\n]",owner);
    int slot = find_free_slot(parking);
    if(slot==full)
    {
        printf("Parking Full! No free slots.\n");
        return;
    }
    parking[slot].occupied=1;
    strcpy(parking[slot].plate,plate);
    strcpy(parking[slot].owner,owner);
    parking[slot].in_time = time(NULL);
    printf("Parked at slot %d at ", parking[slot].slot_no);
    display_time(parking[slot].in_time);
    printf("\n");
    save_state(parking);
}

void save_state(Vehicle *parking)
{
    FILE *fp = fopen(DATAFILE,"w");
    if(!fp)
    {
        perror("Failed to save state");
        return;
    }
    fprintf(fp,"%d\n",total_slots);
    for(int i=0;i<total_slots;i++)
    {
        if(parking[i].occupied)
        {
            fprintf(fp,"%d|%s|%s|%ld\n",parking[i].slot_no,parking[i].plate,parking[i].owner,parking[i].in_time);
        }
        else
        {
            fprintf(fp,"%d|FREE|\n",parking[i].slot_no);
        }
    }
    fclose(fp);
}


Status find_free_slot(Vehicle *parking)
{
    for(int i =0;i<total_slots;i++)
    {
        if(!parking[i].occupied)
        return i;
    }
    return full;
}

Status find_by_plate(const char *plate,Vehicle *parking)
{
    for(int i =0;i<total_slots;i++)
    {
        if(strcmp(parking[i].plate,plate)==0)
        {
            return i;
        }
    }
    return not_exist;
}

void remove_vehicle(Vehicle *parking)
{
    char plate[MAX_PLATES];
    printf("\nEnter plate number to remove: ");
    scanf(" %[^\n]",plate);
    int idx = find_by_plate(plate,parking);
    if(idx==not_exist)
    {
        printf("Vehicle not found.\n");
        return;
    }
    time_t out_t =time(NULL);
    printf("Vehicle found at slot %d. In time: ", parking[idx].slot_no);
    display_time(out_t);
    printf("\n");
    double fee = compute_fee_hours(parking[idx].in_time,out_t);
    printf("Parking fee: %.2f (Rate: %d per hour)\n", fee, RATE_PER_HOUR);

    parking[idx].occupied = 0;
    parking[idx].plate[0] = '\0';
    parking[idx].owner[0]= '\0';
    parking[idx].in_time =0;
    save_state(parking);
}

double compute_fee_hours(time_t in_t, time_t out_t)
{
    double seconds = difftime(out_t,in_t);
    if(seconds<0)
    seconds = 0;
    double hours = seconds/3600.0;
    if(hours<1.0)
    hours = 1.0;
    return hours*RATE_PER_HOUR;

}

void search_vehicle(Vehicle *parking)
{
    char plate[MAX_PLATES];
    printf("\nEnter plate number to search: ");
    scanf(" %[^\n]",plate);
    int idx = find_by_plate(plate,parking);
    if(idx == not_exist)
    {
        printf("Vehicle not found.\n");
        return;
    }
    printf("\nFound at slot %d\nOwner: %s\nIn time: ", parking[idx].slot_no, parking[idx].owner);
    display_time(parking[idx].in_time);
    printf("\n");
}
void change_total_slots(Vehicle *parking)
{
    printf("\nCurrent total slots = %d\n", total_slots);
    printf("Enter new total slots (1 - %d): ", MAX_SLOTS);
    int new_slots;

    if (scanf("%d", &new_slots) != 1) {
        printf("Invalid input.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if(new_slots < 1 || new_slots > MAX_SLOTS)
    {
        printf("Out of range.\n");
        return;
    }

    if (new_slots < total_slots)
    {
        for(int i = new_slots; i < total_slots; i++)
        {
            if(parking[i].occupied)
            {
                printf("Cannot reduce: slot %d is occupied. Free it first.\n", parking[i].slot_no);
                return;
            }
        }

        for (int i = new_slots; i < total_slots; i++) {
             parking[i].occupied = 0;
             parking[i].plate[0] = '\0';
             parking[i].owner[0] = '\0';
             parking[i].in_time = 0;
        }
    }

    if (new_slots > total_slots)
    {
        for(int i = total_slots; i < new_slots; i++)
        {
            parking[i].occupied = 0;
            parking[i].slot_no = i + 1;
            parking[i].plate[0] = '\0';
            parking[i].owner[0] = '\0';
            parking[i].in_time = 0;
        }
    }

    total_slots = new_slots;
    save_state(parking);
    printf("Total slots updated to %d\n", total_slots);
}
void press_enter_to_continue() 
{
    printf("\nPress ENTER to continue...");
    getchar();
    while (getchar() != '\n');
}
#include"utility.h"
int total_slots=10;
int main()
{
    Vehicle parking[MAX_SLOTS];
    for(int i=0;i<total_slots;i++)
    {
        parking[i].slot_no=i+1;
    }
    printf("\n===== Digital Parking Management =====\n");
    
    load_state(parking);
    
    while (1) 
    {
        printf("\n===== Digital Parking Management =====\n");
        printf("1. Display parking status\n");
        printf("2. Park vehicle\n");
        printf("3. Remove vehicle\n");
        printf("4. Search vehicle by plate\n");
        printf("5. Change total slots\n");
        printf("6. Exit\n");
        printf("Choose option: ");
        int opt;
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
            display_status(parking);
            press_enter_to_continue();
            break;

            case 2:
            park_vehicle(parking);
            press_enter_to_continue();
            break;

            case 3:
            remove_vehicle(parking);
            press_enter_to_continue();
            break;

            case 4:
            search_vehicle(parking);
            press_enter_to_continue();
            break;

            case 5:
            change_total_slots(parking);
            press_enter_to_continue();
            break;

            case 6:
            return 0;
            break;
            
            default:
            printf("Invalid option.\n");
        }

    }
    

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 30
#define MAX_LINE 256

enum depart {General = 1, Pharmacy, Surgical, Counselling};

typedef struct Patient{
    char *id;
    char *name;
    char *condition;
    enum depart departmentName;
    int priority;
    struct Patient* next;
}Patient;

typedef struct Department{
    char departName[MAX_NAME];
    char doctorName[MAX_NAME];
    int counter;
    Patient* patientdepart;
}Department;

typedef struct List{
    Patient* head;
    Patient* tail;
}List;

void checkOpenFile(FILE* fp, char* fileName)
{
    if(fp == NULL)
    {
        printf("file did not openned\n");
        exit(1);
    }
    else
    {
        printf("file (%s) openned \n", fileName);
    }
}

void myCloseFile(FILE* fp)
{
    fclose(fp);
    printf("file closed\n");
}

List makeEmptyList()
{
    List lst;
    lst.head = lst.tail = NULL;

    return lst;
}

Department openNewDepartment(char* depName, char* doctorName)
{
    Department dep;
    dep.counter = 0;
    strcpy(dep.departName, depName);
    strcpy(dep.doctorName, doctorName);
    dep.patientdepart = NULL;

    return dep;
}

int isEmpty(List* lst)
{
    return lst->head == NULL;
}

Patient* createNewPatient(Patient* next)
{
    Patient* newPat = (Patient*)calloc(1, sizeof(Patient));

    newPat->next = next;

    return newPat;
}
/*
int checkDoublePatient(List* lst, char* pId)
{
    Patient* temp;

    temp = lst->head;
    while(temp != NULL)
    {
        if(strcmp(temp->id, pId) == 0)
        {
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}
*/
void insertPatientToHead(List* lst, char* str)
{
    Patient* newPat = createNewPatient(lst->head);
    if(isEmpty(lst))
    {
        lst->head = lst->tail = newPat;
    }
    else
    {
        lst->head = newPat;
    }

    char* cutHere = strtok(str, ",");
    newPat->id = strdup(cutHere);
    cutHere = strtok(NULL, ",");
    newPat->name = strdup(cutHere);
    cutHere = strtok(NULL, ",");
    newPat->condition = strdup(cutHere);
    cutHere = strtok(NULL, ",");
    
    if(strcmp(cutHere, "General") == 0)
    {
        newPat->departmentName = 1;
    }
    else if(strcmp(cutHere, "Pharmacy") == 0)
    {
        newPat->departmentName = 2;
    }
    else if(strcmp(cutHere, "Surgical") == 0)
    {
        newPat->departmentName = 3;
    }
    else
    {
        newPat->departmentName = 4;
    }

    cutHere = strtok(NULL, ",");
    sscanf(cutHere, "%d", &newPat->priority);
    if(newPat->priority > 4)
    {
        newPat->priority = 4;
    }
}

void insertPatientToDepartment(Department* dep, Patient temp)
{ 
    Patient* newPat = createNewPatient(dep->patientdepart);

    newPat->id = strdup(temp.id);
    newPat->name = strdup(temp.name);
    newPat->condition = strdup(temp.condition);
    newPat->departmentName = temp.departmentName;
    newPat->priority = temp.priority;

    dep->patientdepart = newPat;
}

void myFree(List* lst)
{
    Patient* temp;
    temp = lst->head;

    while(temp != NULL)
    {
        lst->head = temp->next;
        free(temp);
        temp = lst->head;
    }
}

void myFreeDepartments(Department* dep)
{
    Patient* temp;
    temp = dep->patientdepart;

    while(temp != NULL)
    {
        dep->patientdepart = temp->next;
        free(temp);
        temp = dep->patientdepart;
    }
}

void sortToDepartments(List* lst, Department* generalList, Department* pharmacyList, Department* surgicalList, Department* counsellingList)
{
    Patient temp;
    Patient* ptr;

    ptr = lst->head;
    while(ptr != NULL)
    {
        temp = *ptr;
        if(ptr->departmentName == General)
        {
            insertPatientToDepartment(generalList, temp);
            generalList->counter++;
        }
        else if(ptr->departmentName == Pharmacy)
        {
            insertPatientToDepartment(pharmacyList, temp);
            pharmacyList->counter++;
        }
        else if(ptr->departmentName == Surgical)
        {
            insertPatientToDepartment(surgicalList, temp);
            surgicalList->counter++;
        }
        else
        {
            insertPatientToDepartment(counsellingList, temp);
            counsellingList->counter++;
        }

        ptr = ptr->next;
    }
}

//the sort
void swapPriority(Patient* a, Patient* b)
{
    Patient temp;

    //put a into temp
    temp.id = strdup(a->id);
    temp.name = strdup(a->name);
    temp.condition = strdup(a->condition);
    temp.departmentName = a->departmentName;
    temp.priority = a->priority;

    //put b into a
    a->id = strdup(b->id);
    a->name = strdup(b->name);
    a->condition = strdup(b->condition);
    a->departmentName = b->departmentName;
    a->priority = b->priority;

    //put temp into b
    b->id = strdup(temp.id);
    b->name = strdup(temp.name);
    b->condition = strdup(temp.condition);
    b->departmentName = temp.departmentName;
    b->priority = temp.priority;
}

void sortDepartmentByPriority(Department* dep)
{
    Patient* temp1;
    Patient* temp2;

    if(dep->patientdepart == NULL)
    {
        return;
    }

    temp1 = dep->patientdepart;
    while(temp1 != NULL)
    {
        temp2 = temp1->next;
        while(temp2 != NULL)
        {
            if(temp1->priority > temp2->priority)
            {
                swapPriority(temp1, temp2);
            }

            temp2 = temp2->next;
        }

        temp1 = temp1->next;
    }
}

void printTritment(FILE* fp, char* doctor, Patient* pat, char* depName)
{
    fprintf(fp, "Doctor's name: %s\n", doctor);
    fprintf(fp, "Patient's details: %s, %s, %s, %s, %d\n", pat->id, pat->name, pat->condition, depName, pat->priority);
}

void patientTritment(Department* depG, Department* depP, Department* depS, Department* depC, FILE* fp)
{
    Patient* tempG = depG->patientdepart;
    Patient* tempP = depP->patientdepart;
    Patient* tempS = depS->patientdepart;
    Patient* tempC = depC->patientdepart;
    int count1=0, count2=0, count3=0, count4=0;

    while(tempG != NULL || tempP != NULL || tempS != NULL || tempC != NULL)
    {
        if(tempG != NULL)
        {
            count1++;
            printTritment(fp, depG->doctorName, tempG, depG->departName);
            tempG = tempG->next;
        }
        if(tempP != NULL)
        {
            count2++;
            printTritment(fp, depP->doctorName, tempP, depP->departName);
            tempP = tempP->next;
        }
        if(tempS != NULL)
        {
            count3++;
            printTritment(fp, depS->doctorName, tempS, depS->departName);
            tempS = tempS->next;
        }
        if(tempC != NULL)
        {
            count4++;
            printTritment(fp, depC->doctorName, tempC, depC->departName);
            tempC = tempC->next;
        }
    }

    fprintf(fp, "There were %d patients in the General department\n", count1);
    fprintf(fp, "There were %d patients in the Pharmacy department\n", count2);
    fprintf(fp, "There were %d patients in the Surgical department\n", count3);
    fprintf(fp, "There were %d patients in the Counselling department\n", count4);
}

void printFileDepartment(Department* dep, FILE* fp)
{
    Patient* temp;
    int i=1;
    temp = dep->patientdepart;   

    fprintf(fp, "Department's name: %s\n", dep->departName);
    fprintf(fp, "Doctor's name: %s\n", dep->doctorName);
    fprintf(fp, "Number of patients: %d\n", dep->counter);
    fprintf(fp, "Patients:\n");
    if(temp == NULL)
    {
        fprintf(fp, "There is no patients in that department\n");
    }
    while(temp != NULL)
    {
        fprintf(fp, "%d. %s, %s, %s, %s, %d\n", i, temp->id, temp->name, temp->condition, dep->departName, temp->priority);

        temp = temp->next;
        i++;
    }
}

int main(int arvc, char* argv[]) 
{
    FILE* fg;
    FILE* fp;
    char str[MAX_LINE];
    char* fileName1 = argv[1];
    char* fileName2 = argv[2];
    int choice, counter=0;
    List lst;
    Department generalList;
    Department pharmacyList;
    Department surgicalList;
    Department counsellingList;
    Patient tempPatient;

    lst = makeEmptyList();
    generalList = openNewDepartment("General", "Anar Abdoullaev");
    pharmacyList = openNewDepartment("Pharmacy", "Daniel Modelevsky");
    surgicalList = openNewDepartment("Surgical", "Yaniv Zlotnik");
    counsellingList = openNewDepartment("Counselling", "Maxim Ushakov");
    
    fp = fopen(fileName2, "w");
    checkOpenFile(fp, fileName2);

    START:
    fg = fopen(fileName1, "r");
    checkOpenFile(fg, fileName1);

    while(fgets(str, MAX_LINE, fg) != NULL)
    {
        counter++;
        insertPatientToHead(&lst, str);
    }

    printf("There is %d patients in total\n", counter);

    sortToDepartments(&lst, &generalList, &pharmacyList, &surgicalList, &counsellingList);
    sortDepartmentByPriority(&generalList);
    sortDepartmentByPriority(&pharmacyList);
    sortDepartmentByPriority(&surgicalList);
    sortDepartmentByPriority(&counsellingList);

    patientTritment(&generalList, &pharmacyList, &surgicalList, &counsellingList, fp);

    PAGAIN:
    printf("Please choose: \n");
    printf("1. put new file\n");
    printf("2. exit\n");
    scanf("%d", &choice);

    if(choice == 1)
    {
        myCloseFile(fg);
        generalList.counter = 0;
        pharmacyList.counter = 0;
        surgicalList.counter = 0;
        counsellingList.counter = 0;
        myFree(&lst);
        myFreeDepartments(&generalList);
        myFreeDepartments(&pharmacyList);
        myFreeDepartments(&surgicalList);
        myFreeDepartments(&counsellingList);
        counter = 0;
        printf("put file's name with the list:\n");
        fseek(stdin,0,SEEK_END);
        fflush(stdin);
        gets(fileName1);
        goto START;
    }
    else if(choice == 2)
    {
        printFileDepartment(&generalList, fp);
        printFileDepartment(&pharmacyList, fp);
        printFileDepartment(&surgicalList, fp);
        printFileDepartment(&counsellingList, fp);
        printf("Have a good day :)\n");
    }
    else
    {
        goto PAGAIN;
    }
    
    myCloseFile(fg);
    myCloseFile(fp);
    myFree(&lst);
    myFreeDepartments(&generalList);
    myFreeDepartments(&pharmacyList);
    myFreeDepartments(&surgicalList);
    myFreeDepartments(&counsellingList);
}
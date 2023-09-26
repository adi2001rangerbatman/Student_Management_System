#include<stdio.h>
#include<string.h>

// student course data structure
struct stucoursedata{
    char coursename[20];
    char grade[20];
};
// student structure
struct student{
    char name[50];
    char id[10];
    char department[20];
    struct stucoursedata stucourse[10];
    int subcount;
};
// course details structure
struct course{
    char cid[50];
    char cname[50];
    float value;
};

// functions for selection choice

void addstudentdata(){

    system("COLOR B");
    printf("\n\t\t\t\t<<<<<<-PRESS ANY KEY TO CONTINUE->>>>>>");
    getch();
    system("cls");

    printf("\n\t\t\t\t**********************************************");
    printf("\n\t\t\t\t<<<<<<<<<<<<<<-(ADD NEW STUDENT)->>>>>>>>>>>>>");
    printf("\n\t\t\t\t**********************************************\n");

    FILE *studentfile;
    struct student stu;
    int sub_co;

    printf("\n\t\t\t\tEnter Name : ");
    scanf("%s",&stu.name);
    printf("\t\t\t\tEnter Register No : ");
    scanf("%s",&stu.id);
    printf("\t\t\t\tEnter Department : ");
    scanf("%s",&stu.department);

    printf("\n\t\t\t\tHow Many Courses You Following : ");
    scanf("%d",&sub_co);
    stu.subcount = sub_co;

    for (int i = 0; i <stu.subcount; i++)
    {
      printf("\n\t\t\t\tEnter %d Subject Name :",i+1);
      scanf("%s",&stu.stucourse[i].coursename);
      printf("\t\t\t\tEnter Grade (A,B,C,D,E Or if you absent AB): ");
      scanf("%s",&stu.stucourse[i].grade);
    }

    studentfile = fopen("studentdata.txt","a");
    fwrite(&stu,sizeof(struct student),1,studentfile);
    fclose(studentfile);
    printf("\n\t\t\t\tData has been saved Successfully !!!!\n");
    printf("\n");


    // choice selecter
    char choise;
    printf("\n\t\t\t\tDo you want to Add a new Student Y/N : ");
    scanf("%s",&choise);
    if(choise == 'Y'){
        addstudentdata();
    }else if(choise == 'N'){
        mainwindowdesign();
    }else{
    system("cls");
    printf("\n\t\t\t\tDo you want to Add a new Student Y/N : ");
    scanf("%s",&choise);
    }
}

void addcoursedetails(){

    system("COLOR B");
    printf("\n\t\t\t\t<<<<<<-PRESS ANY KEY TO CONTINUE->>>>>>");
    getch();
    system("cls");

    printf("\n\t\t\t\t********************************************");
    printf("\n\t\t\t\t<<<<<<<<<<<<- ADD COURSE DATA ->>>>>>>>>>>>>");
    printf("\n\t\t\t\t********************************************\n");

    FILE * coursedata;
    struct course cdata;

    printf("\n\t\t\t\tEnter Course ID : ");
    scanf("%s",&cdata.cid);
    printf("\t\t\t\tEnter Course Name : ");
    scanf("%s",&cdata.cname);
    printf("\t\t\t\tEnter Credit Value : ");
    scanf("%f",&cdata.value);

    coursedata = fopen("coursedata.txt","a");
    fwrite(&cdata,sizeof(struct course),1,coursedata);
    fclose(coursedata);
    printf("\n\t\t\t\t Data has been saved Successfully!!\n");

    // choice selecter
    printf("\n\t\t\t\t<<<<<<-PRESS ANY KEY TO CONTINUE->>>>>>");
    getch();
    system("cls");

    char choise;
    printf("\n\t\t\t\tDo you want to Add a new Course Y/N : ");
    scanf("%s",&choise);
    if(choise == 'Y'){
        addcoursedetails();
    }else{
        mainwindowdesign();
    }

}

void viewstudentdata(){

    system("COLOR B");
   printf("\n\t\t\t\t<<<<<<-PRESS ANY KEY TO CONTINUE->>>>>>");
    getch();
    system("cls");

    printf("\n\t\t\t\t*********************************************");
    printf("\n\t\t\t\t<<<<<<<<<<<<<-View Student Data->>>>>>>>>>>");
    printf("\n\t\t\t\t*********************************************\n");

    FILE *studentdata,*coursedata;
    struct student stu;
    struct course cdata;
    char indexno[10];
    studentdata = fopen("studentdata.txt","r");
    coursedata = fopen("coursedata.txt","r");
    int available = 0;

    float total_GPA=0.0;
    int tot_credit=0;
    float c_grade=0.0;


    printf("\n\t\t\t\tEnter student Index Number You need :- ");
        scanf("%s",indexno);


    while(fread(&stu,sizeof(struct student),1,studentdata)){
        if(strcmp(indexno,stu.id) == 0){
            int num=1;

            printf("\n\t\t\t\tName       : %s\n",stu.name);
            printf("\n\t\t\t\tIndex NO   : %s\n",stu.id);
            printf("\n\t\t\t\tDepartment : %s\n",stu.department);
            printf("\n\t\t\t\t|Courses and Grads   ");



            int k;
               while(fread(&cdata,sizeof(struct course),1,coursedata)){
                    for( k=0; k<stu.subcount;k++){

                    if(strcmp(stu.stucourse[k].coursename,cdata.cname)==0){
                        tot_credit+=cdata.value;

                        if(strcmp("A",stu.stucourse[k].grade)==0){
                            c_grade += cdata.value *4.0;
                        }
                        else if(strcmp("B",stu.stucourse[k].grade)==0){
                            c_grade += cdata.value *3.0;
                        }
                        else if(strcmp("C",stu.stucourse[k].grade)==0){
                            c_grade += cdata.value *2.5;
                        }
                        else if(strcmp("D",stu.stucourse[k].grade)==0){
                            c_grade += cdata.value *1.5;
                        }
                        else if(strcmp("E",stu.stucourse[k].grade)==0){
                            c_grade += cdata.value*0.0;
                        }

                        else if(strcmp("AB",stu.stucourse[k].grade)==0){
                            c_grade += cdata.value *0.0;
                        }
                        printf("\n|%s",stu.stucourse[k].coursename);
                        printf("\t\t\t%s\t|",stu.stucourse[k].grade);
                    }

               }

            }

            printf("\n\n");//line break

            total_GPA+=c_grade/tot_credit;
            printf("\t\t\t\tThe total GPA: %.2f ",total_GPA);
            printf("\n");//line break
        }
    }



    fclose(studentdata);
    fclose(coursedata);
    printf("\n\t\t\t\t============================================\n");

    printf("\n\t\t\t\t<<<<<<-PRESS ANY KEY TO CONTINUE->>>>>>");
    getch();
    system("cls");

    // choice selecter
    char choise;
    printf("\n\t\t\t\tDo you want to view Again Y/N : ");
    scanf("%s",&choise);
    if(choise == 'Y'){
        viewstudentdata();
    }else{
        mainwindowdesign();
    }
}



void viewcoursedata(){

    system("COLOR B");
    printf("\n\t\t\t\t<<<<<<-PRESS ANY KEY TO CONTINUE->>>>>>");
    getch();
    system("cls");

    printf("\n\t\t\t\t*******************************************");
    printf("\n\t\t\t\t<<<<<<<<<<<<-View Course Data->>>>>>>>>>>>>");
    printf("\n\t\t\t\t*******************************************\n");

    FILE *coursedetails;
    struct course cde;
    coursedetails=fopen("coursedata.txt","r");

    while(fread(&cde,sizeof(struct course),1,coursedetails)){
        printf("\n\t\t\t\tCourse ID           : %s\n",cde.cid);
        printf("\t\t\t\tCourse Name         : %s\n",cde.cname);
        printf("\t\t\t\tCredit Value        : %.1f\n",cde.value);
        printf("\n");
    }
     printf("\n\n\t\t\t\t===========================================\n");



    // choice selecter
    char choise;
    printf("\n\t\t\t\tDo you want to Exit Y/N : ");
    scanf("%s",&choise);
    if(choise == 'Y'){
        printf("\n\t\t\t\t<<<<<<-PRESS ANY KEY TO CONTINUE->>>>>>");
        getch();
        system("cls");
        mainwindowdesign();
    }else if(choise == 'N'){
        system("cls");
        viewcoursedata();
    }else{
        printf("\n\t\t\t\tInvalid character!!");
        mainwindowdesign();
    }

}

void createfiles(){

    FILE *studentdata;
    FILE *coursedata;

    if (studentdata = fopen("studentdata.txt","r+") == NULL)
    {
        studentdata = fopen("studentdata.txt","w");
        fclose(studentdata);
    }

    if (coursedata = fopen("coursedata.txt","r+") == NULL)
    {
        coursedata = fopen("coursedata.txt","w");
        fclose(coursedata);
    }
}

void mainwindowdesign(){

    system("cls");
    system("COLOR B");
    printf("\n\t\t\t\t*************************************************");
    printf("\n\t\t\t\t<<<<<<<<<(-STUDENT MANAGEMENT SYSTEM-)>>>>>>>>>>>");
    printf("\n\t\t\t\t*************************************************\n");



    printf("\n\t\t\t\t 1.Add Student Details");
    printf("\n\t\t\t\t 2.Add Course Details");
    printf("\n\t\t\t\t 3.View Student Details");
    printf("\n\t\t\t\t 4.View Course Details");
    printf("\n\t\t\t\t 5.Update Student Details");
    printf("\n\t\t\t\t 6.View All Registered Students");
    printf("\n\t\t\t\t 0.Exit\n");
}

void updatestudent(){
    system("COLOR B");
    printf("\n\t\t\t\t<<<<<<-PRESS ANY KEY TO CONTINUE->>>>>>");
    getch();
    system("cls");

    printf("\n\t\t\t\t*********************************************");
    printf("\n\t\t\t\t<<<<<<<<<<<-UPDATE STUDENT DATA->>>>>>>>>>>>");
    printf("\n\t\t\t\t*********************************************\n");

    FILE *studentDetails;
    FILE *temp;

    int found;
   int Subject_count;
   struct student stu;
   char index_no[20];

   studentDetails=fopen("studentdata.txt","r");
   temp=fopen("temp.txt","w");

  printf("\n\t\t\t\tEnter Student Index NO : ");
  scanf("%s",index_no);


  while(fread(&stu,sizeof(struct student),1,studentDetails)){
    if(strcmp(index_no,stu.id)==0){
        found=1;

        printf("\t\t\t\tEnter Student New Name : ");
        scanf(" %[^\n]s",stu.name);
        printf("\t\t\t\tEnter Student New Department : ");
        scanf(" %[^\n]s",stu.department);
        printf("\t\t\t\tEnter Student Index NO : ");
        scanf(" %[^\n]s",stu.id);
        printf("\n\t\t\t\tHow Many Courses are followed by this student : ");
        scanf("%d",&Subject_count);
        stu.subcount=Subject_count;
        printf("\n");

        for(int y=0;y<Subject_count;y++){
            printf("\t\t\t\tEnter NO %d Course Name : ",y+1);
            scanf(" %[^\n]s",stu.stucourse[y].coursename);
            printf("\t\t\t\tEnter The Grade ('A', 'B', 'C', 'D', 'E' or if absent 'N') : ");
            scanf("%s",stu.stucourse[y].grade);
            printf("\n");
        }

  }

    fwrite(&stu,sizeof(struct student),1,temp);

    }


    fclose(studentDetails);
    fclose(temp);

    if(found){
            studentDetails=fopen("studentdata.txt","w");
            temp=fopen("temp.txt","r");
            while(fread(&stu,sizeof(struct student),1,temp)){
                fwrite(&stu,sizeof(struct student),1,studentDetails);
            }
            fclose(studentDetails);
            fclose(temp);

    }
    remove(temp);

    // choice selecter
    char choise;
    printf("\n\t\t\t\tDO YOU WANT TO UPDATE AGAIN Y/N : ");
    scanf("%s",&choise);
    if(choise == 'Y'){
    updatestudent();
    }else {
    mainwindowdesign();
    }
}

void viewallstudentdata(){

    printf("\n\t\t\t\t<<<<<<-PRESS ANY KEY TO CONTINUE->>>>>>");
    getch();
    system("cls");

    system("COLOR B");
    printf("\n\t\t\t\t*********************************************");
    printf("\n\t\t\t\t<<<<<<<<<<<<<<-ALL STUDENTS->>>>>>>>>>>>>>>>>");
    printf("\n\t\t\t\t*********************************************\n");
    FILE *studentdata;
    struct student stu;
    studentdata=fopen("studentdata.txt","r");

    while(fread(&stu,sizeof(struct student),1,studentdata)){
        printf("\n\t\t\tIndex :%s\t\t\tDepartment:%s\t\t\tName:%s\n",stu.id ,stu.department ,stu.name);
    }
   printf("\t\t\t\t================================================\n");

    // choice selecter
    char choise;
    printf("\n\t\t\t\tDo you need see again Y/N : ");
    scanf("%s",&choise);
    if(choise == 'Y'){
    printf("\n\t\t\t\t<<<<<<-PRESS ANY KEY TO CONTINUE->>>>>>");
    getch();
    system("cls");
    viewallstudentdata();

    }else if(choise == 'N'){
        mainwindowdesign();
    }else{
        printf("\n\t\t\t\tInvalid character!!");
        getch();
        mainwindowdesign();
    }

}

void exitwindowdesign(){
    system("COLOR B");
    char ch;
    printf("\n\t\t\t\tARE YOU SURE WANT TO EXIT THE SYSTEM ? (y/n):  ");
    printf("\n\t\t\t\t");
    fflush(stdin);
    scanf("%c",&ch);

    if('y'==ch)
    {
        printf("\n\t\t\t\t*********************************************");
        printf("\n\t\t\t\t((((((((((((-(HAVE A GOOD DAY)-)))))))))))))");
        printf("\n\t\t\t\t*********************************************\n");

     exit(1);
    }
    else
    {
    mainwindowdesign();
    }

}

// main function
int main(){
    int choice;
    do
    {
    mainwindowdesign();       // main window design
    createfiles();           // if the not created data save file , create txt files
    printf("\n\t\t\t\tSelect Your Option number : ");
    scanf("%d",&choice);
    printf("\n");

    if(choice == 1){
        addstudentdata();    // add student data
    }
    else if(choice == 2){
        addcoursedetails();  // add course data
    }
    else if(choice == 3){
        viewstudentdata();   // view student data
    }
    else if(choice == 4){
        viewcoursedata();    // view course details
    }
    else if(choice == 0){
        exitwindowdesign();
        printf("\n");
    }
    else if(choice == 5){   // update student details
        updatestudent();
        }
        else if(choice == 6){
        viewallstudentdata();    // view all registed students
        }
    else{
        main();
    }
    } while (choice !=0 );
}

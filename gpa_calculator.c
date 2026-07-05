#include <stdio.h>
struct subjects{  
    char name[20];
    double average_quiz;
    double midterm;
    double finalExam;
    double quiz_pourcentage;
    double midterm_pourcentage;
    double final_pourcentage;
    double attendanceLab;
    double attendanceLab_pourcentage;
    int subjectCoeficient;

};
struct french_subjects{
    char name[20];
    double average_quiz;
    double midterm;
    double finalExam;
    double attendanceLab;
    double attendanceLab_pourcentage;
    int subjectCoeficient;

};
int subject_count(FILE *file){
    if (file == NULL) return 0;
    int count = 1;
    char ch;
    
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    
    rewind(file); // Reset file pointer to the beginning
    return count;
}
//will load the subjets,the average quiz grade, the midterm grade and the final exam grade from the file and will also load the pourcentage of each grade
void load_grades(int subject_count, struct subjects subjects[], FILE *file){
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    char line[100];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL && count < subject_count) {
        //calculus,85(17),90(27),95(40)
        sscanf(line, "%49[^,],%lf(%lf),%lf(%lf),%lf(%lf),%lf(%lf),%d", subjects[count].name, &subjects[count].average_quiz,&subjects[count].quiz_pourcentage, &subjects[count].midterm,&subjects[count].midterm_pourcentage, &subjects[count].finalExam,&subjects[count].final_pourcentage, &subjects[count].attendanceLab,&subjects[count].attendanceLab_pourcentage, &subjects[count].subjectCoeficient);
        count++;
    }
    fclose(file);
}
void load_grades_french(int subject_count, struct french_subjects frenchSubjects[], FILE *file){
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    char line[100];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL && count < subject_count) {
        //calculus,85(17),90(27),95(40)
        sscanf(line, "%49[^,],%lf,%lf,%lf,%lf,%d", frenchSubjects[count].name, &frenchSubjects[count].average_quiz, &frenchSubjects[count].midterm, &frenchSubjects[count].quiz_pourcentage, &frenchSubjects[count].finalExam,&frenchSubjects[count].final_pourcentage, &frenchSubjects[count].attendanceLab,&frenchSubjects[count].attendanceLab_pourcentage, &frenchSubjects[count].subjectCoeficient);
        count++;
    }
    fclose(file);
}
void save_subjects(int subject_count, struct subjects subjects[]){
    FILE *f = fopen("grade.txt", "w"); 
    if (f == NULL) {
        printf("Error opening file\n");
        return;
    }
    for (int i = 0; i < subject_count; i++) {
        fprintf(f, "%s,%lf(%lf),%lf(%lf),%lf(%lf),%lf(%lf),%d\n", subjects[i].name, subjects[i].average_quiz, subjects[i].quiz_pourcentage, subjects[i].midterm, subjects[i].midterm_pourcentage, subjects[i].finalExam, subjects[i].final_pourcentage, subjects[i].attendanceLab, subjects[i].attendanceLab_pourcentage, subjects[i].subjectCoeficient);
    }
    fclose(f);
}

double grade_to_gpa(double grade) {
    if (grade >= 97) return 4.0;
    else if (grade >= 93) return 4.0;
    else if (grade >= 90) return 3.7;
    else if (grade >= 87) return 3.3;
    else if (grade >= 83) return 3.0;
    else if (grade >= 80) return 2.7;
    else if (grade >= 77) return 2.3;
    else if (grade >= 74) return 2.0;
    else if (grade >= 70) return 1.7;
    else if (grade >= 67) return 1.3;
    else if (grade >= 65) return 1.0;
    else return 0.0;
}

double grade_computer(double finalGrade, int scorePourcentage) {
    return (finalGrade * scorePourcentage) / 100.0;
}
double final_score_computer(struct subjects subject) {
    double totalPourcentage = 0;

  
       totalPourcentage = subject.average_quiz * (subject.quiz_pourcentage / 100) + subject.midterm * (subject.midterm_pourcentage / 100) + subject.finalExam * (subject.final_pourcentage / 100) + subject.attendanceLab * (subject.attendanceLab_pourcentage / 100);
   
   return totalPourcentage;


}

// will compute the gpa based on the grades and the pourcentage of each grade and the coeficient of each subject
double compute_gpa(int subjectNumber, struct subjects subject[]) {
    double totalGPA = 0;
    int totalCoeficient = 0;

    for (int i = 0; i < subjectNumber; i++) {
        double final_grade = final_score_computer(subject[i]);
        double finalGrade = grade_computer(final_grade, 100);
        double gpa = grade_to_gpa(finalGrade);
        totalGPA += gpa * subject[i].subjectCoeficient;
    
// }
        totalCoeficient += subject[i].subjectCoeficient;
    }

    return totalGPA / totalCoeficient;
}


double average_quiz(double quiz[], int quizNumber) {
    double totalQuiz = 0;

    for(int i = 0; i < quizNumber; i++) {

        totalQuiz = totalQuiz + quiz[i];
    }

    return totalQuiz / quizNumber;
}


int main(){
    int choice = 0;
    int subjectNumber = 0;
    printf("\t Welcome to the GPA calculator\n");
    printf("\t This program will help you calculate your GPA based on your grades\n");
    printf("\t You can either enter your grades manually or load them from a file\n");
    printf("\t if u want to compute youSvt,95(20),94(30),94(40),100(10),7r grades from a file modify the grade.txt file and put your grades in it\n");
    printf("Press enter to continue...\n");
    getchar();
    printf("Are you in the american system or the french system? (1 for american, 2 for french): ");
    int systemChoice;
    scanf("%d", &systemChoice);
    if (systemChoice == 2) {
        printf("You have chosen the french system.\n");
    }
    else{
        printf("You have chosen the american system.\n");
    
    printf("Press 1 if  you want to enter grades\n ");
    printf("Press 2 if you want to compute your gpa from grade.txt\n");
    printf("Press 3 if you want to compute your average gpa in 1 subject\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);
    if(choice == 1){
        printf("Do you want to enter the default subjects? (y/n)(freshman II): ");
        char subjectChoice;
        scanf(" %c", &subjectChoice);

        // Load default subjects from file if user chooses 'y'
        //will only ask for grades
        if(subjectChoice == 'y' || subjectChoice == 'Y'){
            int subjectNumber = subject_count(fopen("gradeDefault.txt", "r"));
            struct subjects subjects[subjectNumber];
            load_grades(subjectNumber, subjects, fopen("gradeDefault.txt", "r"));
            

            printf("Default subjects loaded.\n");
            printf("You can now enter your grades for each subject.\n");
            for (int i =0;i < subjectNumber;i++){
                printf("Enter the number of quiz for %s: ", subjects[i].name);
                int quizNumber = 0;
                scanf("%d", &quizNumber);
                double quizGrades[quizNumber];
                for(int j = 0; j < quizNumber; j++){
                    printf("Enter the quiz number %d: ", j + 1);
                    scanf("%lf", &quizGrades[j]);
                }
            
                subjects[i].average_quiz = average_quiz(quizGrades, quizNumber);
              
                printf("Enter your midterm grade in %s: ", subjects[i].name);
                scanf("%lf", &subjects[i].midterm);
            

                printf("Enter your final exam grade in %s: ", subjects[i].name);
                scanf("%lf", &subjects[i].finalExam);
                printf("Do you want the default lab and attendance grades ? (y/n): ");
                char labChoice;
                scanf(" %c", &labChoice);
                if (labChoice == 'y' || labChoice == 'Y') {
                    printf("Default lab and attendance grades will be used.\n");
                    subjects[i].attendanceLab = 100; // Default lab and attendance grade
                }
                else{
                    printf("Enter your lab and attendance grade combined: ");
                    scanf(" %lf",&subjects[i].attendanceLab);
                }
            
                
                    double final_grade = subjects[i].average_quiz * (subjects[i].quiz_pourcentage / 100) + subjects[i].midterm * (subjects[i].midterm_pourcentage / 100) + subjects[i].finalExam * (subjects[i].final_pourcentage / 100) + subjects[i].attendanceLab * (subjects[i].attendanceLab_pourcentage / 100);
                    double finalGrade = grade_computer(final_grade, 100);
                    double gpa = grade_to_gpa(finalGrade);
                    printf("Final grade for %s: %.2f\n", subjects[i].name, finalGrade);
                    printf("GPA for %s: %.2f\n", subjects[i].name, gpa);
                
                
            }
           

            fclose(fopen("gradeDefault.txt", "r"));
            

        }else if(subjectChoice == 'n' || subjectChoice == 'N'){

            printf("How many subjects do you want to enter? ");
            scanf("%d", &subjectNumber);
            struct subjects subjects[subjectNumber];
            for(int i = 0; i < subjectNumber; i++){
                
                printf("Enter the name of subject %d: ", i+1);
                scanf("%s", subjects[i].name);
                printf("How many quizzes do you have in %s? ", subjects[i].name);
                int quizNumber = 0;
                scanf("%d", &quizNumber);
                
                double quizGrades[quizNumber];
                
                for(int i = 0;i < quizNumber;i++){
                printf("Enter the quiz number %d: ",i + 1);
                scanf("%lf",&quizGrades[i]);
                }

                subjects[i].average_quiz = average_quiz(quizGrades, quizNumber);
                printf("Enter the pourcentage of quizzes in %s: ", subjects[i].name);
                scanf("%lf", &subjects[i].quiz_pourcentage);
                printf("Enter your midterm grade in %s: ", subjects[i].name);
                scanf("%lf", &subjects[i].midterm);
                printf("Enter the pourcentage of midterm in %s: ", subjects[i].name);
                scanf("%lf", &subjects[i].midterm_pourcentage);
                printf("Enter your final exam grade in %s: ", subjects[i].name);
                scanf("%lf", &subjects[i].finalExam);
                printf("Enter the pourcentage of final exam in %s: ", subjects[i].name);
                scanf("%lf", &subjects[i].final_pourcentage);
                save_subjects(subjectNumber, subjects);
        }
    }
}

    // COMPUTE GPA from grade.txt

    if(choice == 2){
    FILE *f = fopen("grade.txt", "r");
    if (f == NULL) {
        printf("Error: grade.txt does not exist yet.\n");
    } else {
        int subjectNumber = subject_count(f);
        struct subjects subjects[subjectNumber];
        load_grades(subjectNumber, subjects, f);
        printf("Do you want to know your grade in each subject(y/n)? ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            for (int i = 0; i < subjectNumber; i++) {
                printf("Grade for %s: %.2f\n", subjects[i].name, final_score_computer(subjects[i]));
            }
        }
        if (subjectNumber > 0)
            printf("your gpa is %lf\n", compute_gpa(subjectNumber, subjects));
        else
            printf("no grade found in grade.txt\n");
    }
}
}
    return 0;
}

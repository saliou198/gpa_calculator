#include <stdio.h>
struct subjects{  
    char name[50];
    float average_quiz;
    float midterm;
    float finalExam;
    float quiz_pourcentage;
    float midterm_pourcentage;
    float final_pourcentage;
    float attendanceLab;
    float attendanceLab_pourcentage;
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
        sscanf(line, "%49[^,],%f(%f),%f(%f),%f(%f),%f(%f),%d", subjects[count].name, &subjects[count].average_quiz,&subjects[count].quiz_pourcentage, &subjects[count].midterm,&subjects[count].midterm_pourcentage, &subjects[count].finalExam,&subjects[count].final_pourcentage, &subjects[count].attendanceLab,&subjects[count].attendanceLab_pourcentage, &subjects[count].subjectCoeficient);
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
        fprintf(f, "%s,%f(%f),%f(%f),%f(%f),%f(%f),%d\n", subjects[i].name, subjects[i].average_quiz, subjects[i].quiz_pourcentage, subjects[i].midterm, subjects[i].midterm_pourcentage, subjects[i].finalExam, subjects[i].final_pourcentage, subjects[i].attendanceLab, subjects[i].attendanceLab_pourcentage, subjects[i].subjectCoeficient);
    }
    fclose(f);
}

float grade_to_gpa(float grade) {
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

float grade_computer(float finalGrade, int scorePourcentage) {
    return (finalGrade * scorePourcentage) / 100.0;
}
float final_score_computer(struct subjects subject) {
    float totalPourcentage = 0;

  
       totalPourcentage = subject.average_quiz * (subject.quiz_pourcentage / 100) + subject.midterm * (subject.midterm_pourcentage / 100) + subject.finalExam * (subject.final_pourcentage / 100) + subject.attendanceLab * (subject.attendanceLab_pourcentage / 100);
   
   return totalPourcentage;


}
float compute_gpa(int subjectNumber, struct subjects subject[]) {
    float totalGPA = 0;
    int totalCoeficient = 0;

    for (int i = 0; i < subjectNumber; i++) {
        //float final_grade = subject[i].average_quiz * (subject[i].quiz_pourcentage / 100) + subject[i].midterm * (subject[i].midterm_pourcentage / 100) + subject[i].finalExam * (subject[i].final_pourcentage / 100) + subject[i].attendanceLab * (subject[i].attendanceLab_pourcentage / 100);
        float final_grade = final_score_computer(subject[i]);
        float finalGrade = grade_computer(final_grade, 100);
        float gpa = grade_to_gpa(finalGrade);
        totalGPA += gpa * subject[i].subjectCoeficient;
    
// }
        totalCoeficient += subject[i].subjectCoeficient;
    }

    return totalGPA / totalCoeficient;
}


float average_quiz(float quiz[], int quizNumber) {
    float totalQuiz = 0;

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
    printf("\t if u want to compute your grades from a file modify the grade.txt file and put your grades in it\n");
    printf("Press enter to continue...\n");
    getchar();
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
                float quizGrades[quizNumber];
                for(int j = 0; j < quizNumber; j++){
                    printf("Enter the quiz number %d: ", j + 1);
                    scanf("%f", &quizGrades[j]);
                }
            
                subjects[i].average_quiz = average_quiz(quizGrades, quizNumber);
              
                printf("Enter your midterm grade in %s: ", subjects[i].name);
                scanf("%f", &subjects[i].midterm);
            

                printf("Enter your final exam grade in %s: ", subjects[i].name);
                scanf("%f", &subjects[i].finalExam);
                printf("Do you want the default lab and attendance grades ? (y/n): ");
                char labChoice;
                scanf(" %c", &labChoice);
                if (labChoice == 'y' || labChoice == 'Y') {
                    printf("Default lab and attendance grades will be used.\n");
                    subjects[i].attendanceLab = 100; // Default lab and attendance grade
                }
                else{
                    printf("Enter your lab and attendance grade combined: ");
                    scanf(" %f",&subjects[i].attendanceLab);
                }
            
                
                    float final_grade = subjects[i].average_quiz * (subjects[i].quiz_pourcentage / 100) + subjects[i].midterm * (subjects[i].midterm_pourcentage / 100) + subjects[i].finalExam * (subjects[i].final_pourcentage / 100) + subjects[i].attendanceLab * (subjects[i].attendanceLab_pourcentage / 100);
                    float finalGrade = grade_computer(final_grade, 100);
                    float gpa = grade_to_gpa(finalGrade);
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
                
                float quizGrades[quizNumber];
                
                for(int i = 0;i < quizNumber;i++){
                printf("Enter the quiz number %d: ",i + 1);
                scanf("%f",&quizGrades[i]);
                }

                subjects[i].average_quiz = average_quiz(quizGrades, quizNumber);
                printf("Enter the pourcentage of quizzes in %s: ", subjects[i].name);
                scanf("%f", &subjects[i].quiz_pourcentage);
                printf("Enter your midterm grade in %s: ", subjects[i].name);
                scanf("%f", &subjects[i].midterm);
                printf("Enter the pourcentage of midterm in %s: ", subjects[i].name);
                scanf("%f", &subjects[i].midterm_pourcentage);
                printf("Enter your final exam grade in %s: ", subjects[i].name);
                scanf("%f", &subjects[i].finalExam);
                printf("Enter the pourcentage of final exam in %s: ", subjects[i].name);
                scanf("%f", &subjects[i].final_pourcentage);
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
            printf("your gpa is %f\n", compute_gpa(subjectNumber, subjects));
        else
            printf("no grade found in grade.txt\n");
    }
}
    return 0;
}

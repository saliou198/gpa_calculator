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

};
int subject_count(FILE *file){
    if (file == NULL) return 0;
    int count = 0;
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
        sscanf(line, "%49[^,],%f(%f),%f(%f),%f(%f),%f(%f)", subjects[count].name, &subjects[count].average_quiz,&subjects[count].quiz_pourcentage, &subjects[count].midterm,&subjects[count].midterm_pourcentage, &subjects[count].finalExam,&subjects[count].final_pourcentage, &subjects[count].attendanceLab,&subjects[count].attendanceLab_pourcentage);
        count++;
    }
    fclose(file);
}
void save_subjects(int subject_count, struct subjects subjects[]){
    FILE *f = fopen("grades.txt", "w*"); 
    if (f == NULL) {
        printf("Error opening file\n");
        return;
    }
    for (int i = 0; i < subject_count; i++) {
        fprintf(f, "%s,%f(%f),%f(%f),%f(%f),%f(%f)\n", subjects[i].name, subjects[i].average_quiz, subjects[i].quiz_pourcentage, subjects[i].midterm, subjects[i].midterm_pourcentage, subjects[i].finalExam, subjects[i].final_pourcentage, subjects[i].attendanceLab, subjects[i].attendanceLab_pourcentage);
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
float grade_computer(float score[], int scoreNumber, int scorePourcentage) {
    float totalScore = 0;

    for(int i = 0; i < scoreNumber; i++) {
        totalScore += score[i];
    }

    float average = totalScore / scoreNumber;
    return (average * scorePourcentage) / 100.0;
}
float final_grade_computer(float quizPourcentage,float midtermPourcentage,float finalPourcentage){
    float totalPourcentage = quizPourcentage + midtermPourcentage + finalPourcentage;
    return totalPourcentage;
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
    
    printf("PEACE N LOVE \n");
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
            printf("Do you want the default lab and attendance grades ? (y/n): ");
            char labChoice;
            scanf(" %c", &labChoice);
            if (labChoice == 'y' || labChoice == 'Y') {
                printf("Default lab and attendance grades will be used.\n");
            } 
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

                final_grade_computer(subjects[i].quiz_pourcentage, subjects[i].midterm_pourcentage, subjects[i].final_pourcentage);
                for(int i = 0; i < subjectNumber; i++) {
                    float finalGrade = grade_computer((float[]){subjects[i].average_quiz, subjects[i].midterm, subjects[i].finalExam}, 3, final_grade_computer(subjects[i].quiz_pourcentage, subjects[i].midterm_pourcentage, subjects[i].final_pourcentage));
                    float gpa = grade_to_gpa(finalGrade);
                    printf("Final grade for %s: %.2f\n", subjects[i].name, finalGrade);
                    printf("GPA for %s: %.2f\n", subjects[i].name, gpa);
                }
                
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

    // COMPUTE GPA from grade.txt

    // if(choice == 2){
    //     int subjectNumber = subject_count(fopen("grade.txt","r+"));
       
    //     struct subjects subjects[subjectNumber];
    //     load_grades(subjectNumber, subjects, fopen("grade.txt", "r+"));
        
    //     printf("your gpa is %f",compute_gpa(subjectNumber, subjects));
    // }
    return 0;
}
}


    

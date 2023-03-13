// /∗
// ∗ CSCI3180 Principles of Programming Languages
// ∗
// ∗ --- Declaration --- 
// ∗
// ∗ I declare that the assignment here submitted is original except for source
// ∗ material explicitly acknowledged. I also acknowledge that I am aware of
// ∗ University policy and regulations on honesty in academic work, and of the
// ∗ disciplinary guidelines and procedures applicable to breaches of such policy
// 6
// ∗ and regulations, as contained in the website
// ∗ http://www.cuhk.edu.hk/policy/academichonesty/ 
// ∗
// ∗ Assignment 1
// ∗ Name : ZHANG Jingze
// ∗ Student ID : 1155107857
// ∗ Email Addr : jzzhang8@cse.cuhk.edu.hk 
// ∗/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INS_LINE_LEN 127
#define CAND_LINE_LEN 148 
#define SKILL_LEN 15
#define TA_ID_LEN 11
#define COURSE_ID_LEN 5


int ins_readline(FILE* insfp, char* insline){
	int idx = 0;
	char c;
	while(  (idx < INS_LINE_LEN) && ((c = getc(insfp)) != EOF)  ){
		insline[idx] = c;
		idx++;
	}
	if(idx < INS_LINE_LEN){
		if(idx == 0) return 0;
		else{
			printf("ERROR: instructors.txt format read error\n");
		}
	}
	return 1;
}

int cand_readline(FILE* candfp, char* candline){
	int idx = 0;
	char c;
	while(  (idx < CAND_LINE_LEN)  &&  (( c = getc(candfp) ) != EOF) ){
		candline[idx] = c;
		idx++;
	}

	if(idx < CAND_LINE_LEN){
		if(idx == 0)
			return 0;
		else{
			printf("ERROR: candidates.txt format read error\n");
		}
	}
	return 1;

}

int skill_cmp(char* s1, char* s2){
	if(memcmp(s1,s2, SKILL_LEN) == 0){
		return 1;
	}
	return 0;
}

int course_cmp(char* c1, char* c2){
	if(memcmp(c1,c2,COURSE_ID_LEN) == 0){
		return 1;
	}
	return 0;
}

void ta_id_cpy(char* s1, char* s2){
	memcpy(s1,s2,TA_ID_LEN);
}

void course_cpy(char* c1, char* c2){
	memcpy(c1,c2,COURSE_ID_LEN);
}

void initialize_ta_id(char* ta_id){
	memset(ta_id,'0',TA_ID_LEN);
	ta_id[TA_ID_LEN-1] = ' ';
}

int main()
{
	// 5 + 15x8  [+ 2] = 125 + 2
	char *insline = (char *)malloc(sizeof(char) * INS_LINE_LEN);
	// \r\n included

	// 11 + 15x8 + 5x3  [+ 2] = 146 + 2
	char *candline = (char *)malloc(sizeof(char) * CAND_LINE_LEN);
	// \r\n included

	char* ta_id1 = (char *)malloc(sizeof(char) * TA_ID_LEN);
	char* ta_id2 = (char *)malloc(sizeof(char) * TA_ID_LEN);
	char* ta_id3 = (char *)malloc(sizeof(char) * TA_ID_LEN);
	char* current_id = (char *)malloc(sizeof(char) * TA_ID_LEN);

	char* current_course = (char *)malloc(sizeof(char) * COURSE_ID_LEN);

	// 1 score here refers to 0.5 score in the specification
	int score1 = 0;
	int score2 = 0;
	int score3 = 0;
	int current_score = 0;

	FILE* insfp = NULL;
	FILE* candfp = NULL;
	FILE* outfp = NULL;

	// store the start location for the cols
	int req_skills[3];
	req_skills[0] = 5;
	req_skills[1] = 20;
	req_skills[2] = 35;

	int opt_skills[5];
	opt_skills[0] = 50;
	opt_skills[1] = 65;
	opt_skills[2] = 80;
	opt_skills[3] = 95;
	opt_skills[4] = 110;

	int ta_skills[8];
	ta_skills[0] = 11;
	ta_skills[1] = 26;
	ta_skills[2] = 41;
	ta_skills[3] = 56;
	ta_skills[4] = 71;
	ta_skills[5] = 86;
	ta_skills[6] = 101;
	ta_skills[7] = 116;

	int ta_prefer[3];
	ta_prefer[0] = 131;
	ta_prefer[1] = 136;
	ta_prefer[2] = 141;


	int idx = 0;
	if(NULL == (insfp = fopen("instructors.txt","rb"))){
		printf("non-existing file!\n");
		exit(0);
	}

	if(getc(insfp) == EOF){
		printf("ERROR: instructors.txt EMPTY\n");
		exit(0);
	}
	fclose(insfp);

	if(NULL == (candfp = fopen("candidates.txt","rb"))){
		printf("non-existing file!\n");
		exit(0);
	}

	if(getc(candfp) == EOF){
		printf("Warning: candidates.txt EMPTY\n");
		// exit(0);
	}
	fclose(candfp);

	if(NULL == (outfp = fopen("output.txt","wb"))){
		printf("ERROR: output.txt open error\n");
		exit(0);
	}

	insfp = fopen("instructors.txt","rb");
	while(ins_readline(insfp, insline)){
		candfp = fopen("candidates.txt","rb");
		// set the current course for output
		course_cpy(current_course, insline);


		score1 = 0;
		score2 = 0;
		score3 = 0;
		current_score = 0;

		initialize_ta_id(ta_id1);
		initialize_ta_id(ta_id2);
		initialize_ta_id(ta_id3);

		while(cand_readline(candfp, candline)){
			//printf("  %s\n",candline );
			int req_num = 0;
			current_score = 0;
			ta_id_cpy(current_id, candline);
			
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 8; j++){
					if(skill_cmp(insline + req_skills[i], candline + ta_skills[j] )){
						req_num += 1;
					}
				}
			}
			for(int i = 0; i < 5; i++){
				for(int j = 0; j < 8; j++){
					if(skill_cmp(insline + opt_skills[i], candline + ta_skills[j] )){
						current_score += 2;
					}
				}
			}

			if(course_cmp(current_course, candline + ta_prefer[0])){
				current_score += 3;
			}
			if(course_cmp(current_course, candline + ta_prefer[1])){
				current_score += 2;
			}
			if(course_cmp(current_course, candline + ta_prefer[2])){
				current_score += 1;
			}

			// not all required skills satisfied
			if(req_num < 3){
				current_score = 0;
			}else if(req_num == 3){
				current_score += 2;
			}else{
				printf("ERROR: Req-num more than 3\n");
				exit(0);
			}

			if(current_score > score1){

				score3 = score2;
				score2 = score1;
				score1 = current_score;
				ta_id_cpy(ta_id3,ta_id2);
				ta_id_cpy(ta_id2,ta_id1);
				ta_id_cpy(ta_id1,current_id);

			}else if(current_score > score2){

				score3 = score2;
				score2 = current_score;
				ta_id_cpy(ta_id3,ta_id2);
				ta_id_cpy(ta_id2,current_id);

			}else if(current_score > score3){

				score3 = current_score;
				ta_id_cpy(ta_id3,current_id);

			}else{

			}
			//printf("  [%s] score: %d\n", current_id, current_score);

		}
		fclose(candfp);
		
		fprintf(outfp, "%s%s%s%s\n",current_course,ta_id1,ta_id2,ta_id3);
		//printf("[%s][%s][%s][%s]\n",current_course,ta_id1,ta_id2,ta_id3);

	}
	fclose(insfp);
	fclose(outfp);

	return 0;
}









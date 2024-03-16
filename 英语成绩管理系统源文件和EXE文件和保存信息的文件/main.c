#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TF_QUESTION 100//�ж�����Ŀ�������Ϊ100
#define OPTION 50//ѡ����ѡ��������Ϊ50
#define CHOICE_QUESTION 100//ѡ������Ŀ�������Ϊ100
#define GF_QUESTION 100//�������Ŀ�������Ϊ100
#define GF_ANSWER 30//�����𰸵������Ϊ30
#define ANSWER_LEN 2//�ж����ѡ����������Ϊ2
#define ALL_ANSWER_LEN 15//�ж����ѡ����ֱ�������Ϊ15
#define NAME_LEN 10//ѧ�����ֵĳ����Ϊ10
#define CLASS_NAME_LEN 3//�༶���ֵĳ����Ϊ3
#define MAJORITY 10//רҵ���ֵĳ����Ϊ10
#define ORIGINAL_PASSWROD 1111//ѧ����ʼ����Ϊ1111
#define LINE_LEN 64//һ�еĳ����Ϊ64
#define TALKING_FILE_NAME 35//����Ϊ�ı����ֵĳ����Ϊ30

//ѧ�������Ϣ(��������,�༶,רҵ,ѧ��,����)
typedef struct _Student{
	//name����ѧ������(�ַ�������),class����ѧ�����ڰ༶(�ַ�������),majority����ѧ����ѡרҵ(�ַ�������)
	char name[NAME_LEN],class[CLASS_NAME_LEN],majority[MAJORITY];
	//id����ѧ����ѧ��(����),password����ѧ��������(����)(ѧ����ʼ����Ϊ1111)
	int id,password;
	//grade����ѧ���Ŀ��Գɼ�(�����ȸ�������)
	float grade;
	//examination_status(����)����ѧ������״̬,���ֵΪ1,��˵���ÿ����Ѿ���������,���Ϊ0,��˵���ÿ�����δ����(��ʼ��Ϊ0)
	int examination_status;
}Student;//Student����struct _Student

//ѧ�������Ϣ������(����ѧ����Ϣ,ָ����һ�ڵ��ָ��)
typedef struct _list{
	//Stu����һ��ѧ��
	Student Stu;
	//nextָ����һ���ڵ�,˵��ָ����һ��ѧ��
	struct _list *next;
}stu;//stu����struct _list

//�ж���ṹ��(������Ŀ,��,�������,ָ����һ�ڵ��ָ��)
typedef struct _TF_questions{
	//tf_questions�����ж�����Ŀ,tf_answer�����ж����
	char tf_question[TF_QUESTION],tf_answer[ANSWER_LEN];
	//nextָ����һ�ڵ�,˵��ָ����һ���ж���
	struct _TF_questions *next;
	//tf_score������ж���ķ���(�����ȸ�������)
	float tf_score;
}TF_questions;//TF_question����struct _TF_questions

//ѡ�����ѡ��ṹ��(����A��B��C��D�ĸ�ѡ�������)
typedef struct _Options{
	//option_a����ѡ��A(�����һ������)
	char option_a[OPTION],option_b[OPTION],option_c[OPTION],option_d[OPTION];
}Option;//Option����struct _Options

//ѡ����ṹ��(������Ŀ,ѡ�������,��,�������,ָ����һ�ڵ��ָ��)
typedef struct _Choice_questions{
	//choice_question����ѡ������Ŀ,cq_answer����ѡ�����
	char choice_question[CHOICE_QUESTION],cq_answer[ANSWER_LEN];
	//cq_score�����ѡ�����
	float cq_score;
	//option�������Ŀ��ѡ��
	Option option;
	//nextָ����һ�ڵ�,˵��ָ����һ��ѡ����
	struct _Choice_questions *next;
}Choice_questions;//Choice_questions����struct _Choice_questions

//�����ṹ��(������Ŀ,��,�������,ָ����һ�ڵ��ָ��)
typedef struct _GF_questions{
	//gf_question�����������Ŀ,gf_answer����������
	char gf_question[GF_QUESTION],gf_answer[GF_ANSWER];
	//gf_score������������(�����ȸ�����)
	float gf_score;
	//nextָ����һ�ڵ�,˵��ָ����һ�������
	struct _GF_questions *next;
}GF_questions;//GF_questions����struct _GF_questions

//����Ŀ�ṹ��(�����ж���ṹ��,ѡ����ṹ��,�����ṹ��,���������ֵ)
typedef struct _Timu{
	//tf_questions����ָ��TF_question���͵�ָ��
	TF_questions *tf_questions;
	//choice_questions����ָ��Choice_questions���͵�ָ��
	Choice_questions *choice_questions;
	//gf_questions����ָ��GF_questions���͵�ָ��
	GF_questions *gf_questions;
	//full_mark����������ķ���(�����ȸ�������)
	float full_mark;
}Timu;//Timu����struct _Timu

//���뵽stu.txt����Ҫ������,��stu(clear)��ȡ����Ҫ�Ľṹ��
typedef struct _Student_timu{
	//Stu���溬��ѧ����Ϣ
	Student Stu;
	//stu_tf_answer�����ѧ�����ж�������д�
	char stu_tf_answer[ALL_ANSWER_LEN];
	//stu_choice_answer�����ѧ����ѡ��������д�
	char stu_choice_answer[ALL_ANSWER_LEN];
	//stu_gf_answer�����ѧ�������������д�
	char stu_gf_answer[ALL_ANSWER_LEN][GF_ANSWER];
	//stu_full_mark�����ѧ��������ķ���(��ʼ����Ϊ0)
	float stu_full_mark;
}Student_timu;//Student_timu����struct _Student_timu

//������ɺ��������ļ���ѧ����ݺͿ�����Ϣ(���ڴ��ļ�stu.txt�ж�ȡ���ݵ����������)
typedef struct _Student_timu_List{
	//stu_timu����һ��ѧ���������Ϣ�Ϳ�����Ϣ
	Student_timu stu_timu;
	//nextָ����һ�ڵ�,˵��ָ����һ��ѧ��
	struct _Student_timu_List *next;
}Student_timu_list;//Student_timu_list����struct _Student_timu_List

stu *stu_list = NULL;//��ѧ�������Ϣ������Ϊ��(NULL)
Timu timu = {NULL,NULL,NULL,0};//������Ŀ����
Student_timu_list *student_timu_list = NULL;//��ѧ��������Ϣ������Ϊ��(NULL)

//��ʼʱ����ѧ����Ϣ�ļ�
int read_id_studentinfo_file(void);
//��ѧ����Ϣ����
Student_timu *creat_student_timu(stu *mark);
//���뿼������
int read_timu_file(int flag);
//ɾ������Ŀ�������
void delete_timu(void);
//����ѧ����Ϣ
void save_id_studentinfo(void);
//���û��������֮����ʾ�û������������������
void input_again(void);
//�����ַ���ʱ����0����
int char_return_by_zero(char flag[]);
//���ջس���
void take_in_line_break(void);
//ѧ����¼����
void student_login_menu(void);
//ѧ���˵�
void student_menu(stu **mark);
//ѧ����ʼ����
void start_exam(Student_timu *student_timu,stu **mark);
//��ӡ��Ŀ
void print_timu(int flag);
//����ɼ�
float calculate_score(Student_timu *student_timu,int gf_questions_count);
//ѧ������ѧ���ɼ���stu.txt��
void stu_save_stu(Student_timu *student_timu);
//��ʦ����ɼ���stu.txt��
void tea_save_stu(int flag);
//ѧ���޸�����
void change_password(stu **mark);
//ѧ����������
void stu_talking(stu *mark);
//��ʦ�˵�
void teacher_menu(void);
//��ʦ��������
void post_examination(void);
//�������Բ˵�
int post_exam_menu(int *i11,int *i22,int *i33);
//������Ŀ����
void save_timu(int i11,int i22,int i33);
//��ʦ��ʼ��ͬѧ�ɼ�Ϊ��
void initialize_grade(void);
//��ʦ¼��ѧ����Ϣ
void input_studentinfo(void);
//��ʦ��ӡȫ��ѧ���ɼ�
void print_studentinfo(void);
//���������Զ���ͳ��ѧ��
void Custom_statistics(Student *ranking,int count);
//��ʦ��ѧ��ѧ������
void id_rank(Student *ranking,int count);
//ѧ��˳������
void id_order_rank(Student *ranking,int count);
//ѧ����������
void id_reverse_order_rank(Student *ranking,int count);
//��ʦ���ɼ�����
void grade_rank(Student *ranking,int count);
//�ɼ�˳������
void grade_order_rank(Student *ranking,int count);
//�ɼ���������
void grade_reverse_order_rank(Student *ranking,int count);
//��ʦͳ��ȫ���ֺܷ�ƽ����
void print_wholescore_and_avgscore(void);
//��ʦ�鿴����ѧ���ɼ�
void seek_studentinfo(void);
//��ʦ��ѧ��ѧ�Ų鿴ѧ���ɼ�
void seek_by_id(void);
//��ʦ��ѧ���ɼ��ߵͲ鿴ѧ���ɼ�
void seek_by_name(void);
//��ʦ�޸�ѧ����Ϣ
void modify_studentinfo(void);
//��ʦͨ��ѧ���޸�
void modify_by_id(void);
//��ʦͨ�������޸�
void modify_by_name(void);
//��ʦɾ��ѧ�������Ϣ
void remove_student_id_info(void);
//ͨ��ѧ��ɾ��ѧ�������Ϣ
void remove_id_by_id(void);
//ͨ������ɾ��ѧ�������Ϣ
void remove_id_by_name(void);
//ɾ��ѧ��������Ϣ
void remove_student_exam_info(void);
//ͨ��ѧ��ɾ��ѧ��������Ϣ
void remove_exam_by_id(void);
//ͨ������ɾ��ѧ��������Ϣ
void remove_exam_by_name(void);
//��stu.txt�ļ�����ѧ��������Ϣ����
void read_stu_exam_list(void);
//��ѧ��������Ϣ����ɾ��
void delete_stu_exam_list(void);
//������Ϣ��stu1.txt�ļ���
void save_stu1(int delete_stu_id);
//�鿴�ѱ�ɾ����ѧ��������Ϣ
void print_stu_deleted_exam_info(void);
//��ʦ��������
void tea_talking(void);
//������Ϣ
void receive_message(char filename[]);
//������Ϣ
void send_message(char filename[],char username[]);

//������
int main(int argc, char *argv[])
{
	read_id_studentinfo_file();//��ʼʱ��ȡѧ����Ϣ�ļ�
	int choice;//����ѡ����
	
	while(1)
	{
		printf("||==============================================||\n");
		printf("||\t��ӭʹ��ѧ��Ӣ��ɼ�����ƽ̨V1.0\t||\n");
		printf("||==============================================||\n");
		printf("||\t\t��ѡ��ģʽ\t\t\t||\n");
		printf("||==============================================||\n");
		printf("||\t\t1.ѧ��ģʽ\t\t\t||\n");
		printf("||\t\t2.��ʦģʽ\t\t\t||\n");
		printf("||\t\t3.�˳�ϵͳ\t\t\t||\n");
		printf("||==============================================||\n||");

		if(scanf("%d",&choice) != 1)//���choice��Ϊ�������������if���
		{
			input_again();//��ʾ�û���������
			continue;//����ѭ��
		}

		switch (choice)
		{
			case 1://ѧ��ģʽ
				student_login_menu();//����ѧ����¼����
				break;
			case 2://��ʦģʽ
				system("cls");
                teacher_menu();//�����ʦ����
				break;
			case 3://�˳�ϵͳ
				printf("||�����ɹ��˳�!����\n");
                exit(0);//�˳�����
			default://��������
				input_again();//��ʾ�û���������
				break;
		}
	}//while(1)ѭ��
	return 0;
}

//����Ϊ"studentinfo.txt"���ļ���ȡ��������
int read_id_studentinfo_file(void)
{
	//����Ϊ"studentinfo"���ı��ļ�,�����ص�ָ�븳��fpr
	FILE *fpr = fopen("studentinfo.txt","r");

	if(fpr == NULL)//��ʧ��ʱ
		return 0;
	else//���ļ��ɹ�
		while(1)
		{
			stu *p = (stu*)malloc(sizeof(stu));
			//���ļ���ѧ����Ϣ���뵽������
			fscanf(fpr,"%d %s %s %s %d %f %d",&(p->Stu.id),p->Stu.name,
			p->Stu.class,p->Stu.majority,&(p->Stu.password),
			&(p->Stu.grade),&(p->Stu.examination_status));
            //�Ƚ��ļ����룬�������õ�������ʱ�յģ���ʱ������ж��Լ���ȡ���ļ�ĩβ����Ȼ���ǲ�����ֹ��һ������
			if(feof(fpr)) break;//����ĩβ����ѭ��
            p->next = NULL;
            if(stu_list)//�����ͷ��Ϊ��,��ͷ����p��ĩβ,�ٽ�ͷ����Ϊp
	        {
			//ͷ�巨
            //�������9
	        //����ǰ��5->4->3->1->NULL
	        //�����9->5->4->3->1->NULL
	    	    p->next=stu_list;
	    	    stu_list=p;
		    }
		    else stu_list=p;//�����ͷΪ��,��ֱ�ӽ�p������ͷ
		    //�������7
		    //����ǰ:NULL
		    //�����:7->NULL
		}
		fclose(fpr);//�ر��ļ�
}

//����0�˳�
//return_by_zero��һ�������������͵����ĺ���
//����Ϊһ��������
//��������ԭ��:����õ��Ĳ�����Ϊ0�򷵻�0,����õ��Ĳ���Ϊ0�򷵻�1,����ʾ�û��˳��ɹ�
//������ѧ����½���桢�޸�����ȹ���ʱ,����0�˳�����
int return_by_zero(int flag)
{
	if(flag == 0)
	{
		printf("||�˳��ɹ�!\n||");
		system("pause");
		system("cls");
		return 1;
	}
	return 0;
}

//��ʾ�û���������
void input_again(void)
{
	printf("||!������������������롿!\n||");
	take_in_line_break();//���ջس���
	system("pause");//��ͣ���û������Ϣ
	system("cls");
}

//�������뻻�з�
void take_in_line_break(void)
{
	while(getchar() != '\n');//ֱ���ַ���Ϊ���з�(�س���)
}

//ѧ����½����
void student_login_menu(void)
{
	system("cls");
	int self_id,self_password,flag = 0;//����ѧ�������ѧ�ź�����,��flag�ж�ѧ�ź������Ƿ�Ե���
	stu *mark = stu_list;//����һ��stu���͵�ָ��mark,������ͷ����mark
	
	while(1)
	{
		printf("||=====================================================||\n");
	    printf("||���������ѧ��(1000~9999)(����0�˳�ѧ����¼����,ͬ��)||\n||");//��ʾ�û�����ѧ��
	    if(scanf("%d",&self_id) != 1)//������벻Ϊ���������if���
	    {
	    	printf("||��������λ����\n");
		    input_again();//��ʾ�û���������
		    continue;//���¿�ʼѭ��
		}
 		//�������Ϊ0���˳�ѧ����¼����
		if(return_by_zero(self_id))break;
		if( self_id >9999 || self_id < 1000)
		{
	    	printf("||��������λ����\n");
			input_again();//��ʾ�û���������
		    continue;//���¿�ʼѭ��
		}
		
		take_in_line_break();
		printf("||=====================================================||\n");
	    printf("||  �������������(��λ��)(��ʼ����Ϊ1111)(����0�˳�)  ||\n");
		printf("||=====================================================||\n||");
	    if(scanf("%d",&self_password) != 1)//������벻Ϊ���������if���
	    {
		    input_again();//��ʾ�û���������
		    continue;//���¿�ʼѭ��
		}
		//�������Ϊ0���˳�ѧ����¼����
		if(return_by_zero(self_password))return;
		
		take_in_line_break();
		printf("||=====================================================||\n");
	    for(mark = stu_list;mark;mark = mark->next)//��������
		    if(mark->Stu.id == self_id && mark->Stu.password == self_password)
		    //ע�ⲻҪ��©mark = stu_list��Ȼ,�û��ڶ�������ʱmark�Ի�ָ������ĩβ,�����������
			{//�ж�ѧ������������ѧ���Ƿ�ƥ��(���ļ�"studentInfo.txt"�����ο�)
			    flag = 1;//���ƥ�������1����flag
			    break;
            }
	    if(flag)//���flagΪ1,��������
	    {
			printf("||������¼�ɹ�,����ѧ���˵�!����\n||");//��ʾ�û���½�ɹ�
			system("pause");//��ͣ���û������Ϣ
			system("cls");
			student_menu(&mark);
            //����ѧ���˵�(���ҽ��õ��ĵ�ǰѧ����Ϣ�ĵ�ַ��������)
            //����ĵ�ַ�������޸�,�����޸�ѧ������
			break;
	    }
	    else//���flagΪ0,��˵��ƥ�䲻��
	    {
	    	//��ʾ�û��������,����ʾ�û���һ������
			printf("||!���˺Ż��������!\n||");
			system("pause");//��ͣ���û������Ϣ
			system("cls");
	    }
	}
	system("cls");
}

//ѧ���˵�
void student_menu(stu **mark)
{
	//creat_student_timu�Ƿ���Student_timu����ָ��ĺ���
	//����ǰѧ���������Ϣ����
	Student_timu student_timu = *creat_student_timu(*mark);
	int choice;//�����û���ѡ��
	
	while(1)
	{
		system("cls");
		printf("||=======================================================================================||\n");
		printf("||\t\t��ǰΪѧ��ģʽ\t\t\t\t\t\t\t\t ||\n");
		printf("||=======================================================================================||\n");
		printf("||ѧ��\t\t����\t\t�༶\t\tרҵ\t\t����״̬\t����\t ||\n");
		printf("||=======================================================================================||\n");
		printf("||%d\t\t%s\t\t%s\t\t%s\t\t%d\t\t%.2f\t ||\n",(*mark)->Stu.id,(*mark)->Stu.name,(*mark)->Stu.class,
		(*mark)->Stu.majority,(*mark)->Stu.examination_status,(*mark)->Stu.grade);
		//ͨ���õ���ѧ����Ϣ,��ѧ������Ϣ��ӡ����(��ȷ���û��Ƿ��¼���Լ����˺�)
		printf("||=======================================================================================||\n");
		printf("||\t\t��ѡ����\t\t\t\t\t\t\t\t ||\n");//��ʾ�û�ѡ����
		printf("||=======================================================================================||\n");
		printf("||\t\t1.��ʼ����\t\t\t\t\t\t\t\t ||\n");
		printf("||\t\t2.�鿴�ɼ�\t\t\t\t\t\t\t\t ||\n");
		printf("||\t\t3.��������\t\t\t\t\t\t\t\t ||\n");
		printf("||\t\t4.�޸�����\t\t\t\t\t\t\t\t ||\n");
		printf("||\t\t5.�����ܲ˵�\t\t\t\t\t\t\t\t ||\n");
		printf("||=======================================================================================||\n||");

		if(scanf("%d",&choice) != 1)//���choice�����������������if���
		{
			input_again();//��ʾ�û���������
			continue;//����ѭ��
		}
		take_in_line_break();

		switch (choice)
		{
			case 1://ѧ����ʼ����
                //start_exam�ǲ�������ֵ�ĺ���,����student_timu�ĵ�ַ,���Զ�student_timu�����ݽ��в���
                //�罫ѧ������״̬�ĳ�1
				start_exam(&student_timu,mark);
				break;
			case 2://ѧ���鿴�ɼ�
                //print_studentinfo�ǲ�������ֵ�ĺ���,Ҳ���β�
				print_studentinfo();
				break;
			case 3://ѧ����������
                //stu_talking�ǲ�������ֵ�ĺ���,�β�*mark�������ǽ�ѧ������Ϣ����ȥ
                //*mark�ڵ�����������ע������
				stu_talking(*mark);
				break;
			case 4://ѧ���޸�����
                //������ָ��mark����ȥ���޸�����
				change_password(mark);
				break;
			case 5://�����ܲ˵�
			    printf("||�����ɹ����ء���\n");
                return;
			default ://�������붼Ϊ��������,�����ʾ�û���������
				input_again();
				break;
		}
	}
}

//��ѧ����Ϣ����
Student_timu *creat_student_timu(stu *mark)
{
    Student_timu *p = (Student_timu *)malloc(sizeof(Student_timu));
	p->Stu = mark->Stu;//��mark�еĽṹ��Stu��Ϣ����p��Ȼ�󷵻�p

	return (p);
	free(p);//�ͷ�p
	p = NULL;//��������ָ��
}

//��ȡ��������
//read_timu_file������һ�������������͵ĺ���,�����᷵��1��0,����1��˵������Ŀ,����0��˵��û��Ŀ���ߴ��ļ�ʧ��
//flag�����ж�ʹ�ú����Ĳ����û���ѧ���û����ǽ�ʦ�û�,1��ѧ���û�,2�ǽ�ʦ�û�
int read_timu_file(int flag)
{
	//��ֻ���ķ�ʽ����Ϊ"timu(clear)"���ı��ļ�,�������ص�ָ�븳��fpr
	FILE *fpr = fopen("timu(clear).txt","r");
	//i1,i2,i3�����ֱ��ȡ�ж���,ѡ����,��������Ŀ
	//i01,i02,i03����ѭ����ӡ��Ŀ,ch�����ж��ļ��Ƿ�Ϊ��,i���������ļ�����,j��������ѡ����ѡ��
	int i = 0,j = 0,i1 = 0,i2 = 0,i3 = 0,i01 = 0,i02 = 0,i03 = 0,ch = 0;
	char temp;//temp������ʱ�����ļ���һ���ַ�,�ж��Ƿ�õ����ַ����쳣�����Ƿ�Ϊ��ȡ������

	if(fpr == NULL)//��ʧ��ʱ
		return 0;
	else
	{
		ch = fgetc (fpr);//ch��ȡ�ļ��еĵ�һ���ַ�
		fseek(fpr,0,SEEK_SET);//���»ص��ļ���ͷ
		//�ֱ��i1,i2,i3�����ж���,ѡ����,����������
		fscanf(fpr,"%d,%d,%d\n",&i1,&i2,&i3);
		
		if(flag == 1)//���flagΪ1,�����if���,flagΪ1��ʾ���û�Ϊѧ���û�
		{
			//��������ļ��ĵ�һ���ַ�Ϊ��,��������������Ϊ0,�����if���
		    if(ch == EOF || (i1 == 0) && (i2 == 0) && (i3 == 0))
		    {
		    	system("cls");
			    printf("������ʦ��δ�������ԡ���\n");//��ʾ�û���ʦ��δ��������
		 	    return 0;
		    }
		}
		if(flag == 2)//���flag��Ϊ2,�����if���,flagΪ2��ʾ���û�Ϊ��ʦ�û�
			//��������ļ��ĵ�һ���ַ�Ϊ��,��������������Ϊ0,�����if���
		    if(ch == EOF || (i1 == 0) && (i2 == 0) && (i3 == 0))
		    {
		    	system("cls");
			    printf("������δ¼�뿼����Ϣ����\n");//��ʾ�û���ʦ��δ��������
			    system("pause");//��ͣ���û������Ϣ
			    system("cls");
		 	    return 0;
		    }
		//i01(��ʾ��ǰ��ӡ��������Ŀ��)��ʼΪ0,��i01С��i1(���ж�����)ʱ�˳�whileѭ��
		while(i01 < i1)
		{
			//��p1����TF_questions���͵�ָ��
			TF_questions *p1 = (TF_questions *)malloc(sizeof(TF_questions));
			if(p1 == NULL)//�������ʧ�������if���
			{
				printf("||�����ڴ�ʧ��,���ܴ�ӡ�ж�����Ŀ\n||");//��ʾ�û������ڴ�ʧ��
				break;//������ǰwhileѭ��
			}
			
			//��������ڴ�ɹ�,�����ļ��ж�ȥ�ж�����Ϣ(����Ŀ���𰸺ͷ���)
			//��ȡ�ж�����Ŀ
			for(i = 0;;i++)
			{
                //temp��ʱ�洢��ȡ�ļ����ַ�
				temp = fgetc(fpr);
				if(temp == EOF)
				{
					//��ʾ�û�����ԭ��
					printf("��ȡ����\n");
					system("pause");//��ͣ���û������Ϣ
					system("cls");
					break;
				}
				if(temp == 35)break;
				p1->tf_question[i] = temp;
			}
			//����Ч�ַ���ĩβ��Ϊ'\0'
			p1->tf_question[i] = '\0';
			
			//��ȡ���ж����
			p1->tf_answer[0] = fgetc(fpr);
			p1->tf_answer[1] = '\0';
			//�ڶ�ȡ�ж���𰸺ͷ�ֵ֮����ַ�
			temp = fgetc(fpr);

            //��ȡ���ж����ֵ�Լ����з�(��ȡ���з������������ڶ�ȡ��һ��)
	        fscanf(fpr,"%f\n",&(p1->tf_score));
			if(feof(fpr)) break;//��������ļ�ĩβ�������ǰѭ��
			p1->next = NULL;//��p1ָ���next��ΪNULL(����Ұָ��)
			if(timu.tf_questions)//�������timu.tf_questions��ͷ�ڵ㲻Ϊ��,�����if���
			{
			    //����TF_questions���͵�ָ��pָ��timu.tf_questions��ͷ�ڵ�
				TF_questions *p = timu.tf_questions;
                //for������:��ָ��p��forѭ��ָ������timu.tf_questions��ĩβ
                //�����������ڵ�����Ϊ3->2->9->1->NULL
				//��ʼforѭ��ǰpָ��3��p->nextָ��2
				//forѭ��������pָ��1,p->nextָ��NULL
				for(;p->next;p = p->next);
				p->next = p1;//��p1����p->nextָ���NULL
			}
			//�������timu.tf_questions��ͷ�ڵ�Ϊ��,�����else���
			//��p1����ͷ�ڵ�
			else timu.tf_questions = p1;
			i01++;//i01��1,���ڽ���while����ж��Ƿ��ӡ��һ���ж���
		}
		if(temp == EOF)return 0;
		
 		//i02(��ʾ��ǰ��ӡ��������Ŀ��)��ʼΪ0,��i02С��i2(���ж�����)ʱ�˳�whileѭ��
		while(i02 < i2)
		{
			//��p2����Choice_questions���͵�ָ��
			Choice_questions *p2 = (Choice_questions *)malloc(sizeof(Choice_questions));
			if(p2 == NULL)//�������ʧ�������if���
			{
				printf("||�����ڴ�ʧ��,���ܴ�ӡ�ж�����Ŀ\n||");//��ʾ�û������ڴ�ʧ��
				break;//������ǰwhileѭ��
			}
            //��������ڴ�ɹ�,�����ļ��ж�ȥѡ������Ϣ(����Ŀ��ѡ��a.b.c.d���𰸺ͷ���)
            //��ȡѡ������Ŀ
			for(i = 0;;i++)
			{
				//temp��ʱ�������ļ��ж�ȡ�ĵ�һ���ַ�
				temp = fgetc(fpr);
				if(temp == EOF)
				{
					//��ʾ�û������ԭ��
					printf("��ȡ����\n");
					system("pause");//��ͣ���û����
					system("cls");
					break;
	}
				if(temp == 35)break;
				p2->choice_question[i] = temp;
			}
			//����Ч�ַ���ĩβ��Ϊ'\0'
			p2->choice_question[i] = '\0';
			
			//����һ����ά����������ѡ������ĸ�ѡ��
			char Option_all[4][OPTION];
			
			//��ȡѡ�������ѡ��
			//j����ABCDѡ��
			for(j = 0;j < 4;j++)
			{
				//i����ѡ���еĸ����ַ�
				for(i = 0;;i++)
				{
					//temp��ʱ�����ȡ�ļ����ַ�
					temp = fgetc(fpr);
					if(temp == EOF)
					{
						//��ʾ�û������ԭ��
						printf("��ȡ����\n");
					    system("pause");//��ͣ���û����
					    system("cls");
					    break;
					}
					if(temp == 35)break;
					Option_all[j][i] = temp;
				}
				if(temp == EOF)break;
				//��ѡ�����Ч�ַ���ĩβ��Ϊ'\0'
                Option_all[j][i] = '\0';
			}
			
			//��ȡ��ѡ����Ĵ�
			p2->cq_answer[0] = fgetc(fpr);
			p2->cq_answer[1] = '\0';
			//��ȡ�𰸺ͷ�ֵ֮����ַ�
			temp = fgetc(fpr);
			
			//�ֱ�Option_all�ĸ���Ԫ�ظ��Ƹ�p2��ָ�ĸ���ABCDѡ��
		    strcpy(p2->option.option_a,*Option_all);
		    strcpy(p2->option.option_b,*(Option_all+1));
		    strcpy(p2->option.option_c,*(Option_all+2));
		    strcpy(p2->option.option_d,*(Option_all+3));
			
			//��ȡ��ѡ�����ֵ�Լ����з�(��ȡ���з������������ڶ�ȡ��һ��)
			fscanf(fpr,"%f\n",&p2->cq_score);
			if(feof(fpr))break;//��������ļ�ĩβ�������ǰѭ��
			p2->next = NULL;//��p2ָ���next��ΪNULL(����Ұָ��)
			if(timu.choice_questions)//�������timu.choice_questions��ͷ�ڵ㲻Ϊ��,�����if���
			{
				//����Choice_questions���͵�ָ��pָ��timu.choice_questions��ͷ�ڵ�
				Choice_questions *p = timu.choice_questions;
				//for������:��ָ��p��forѭ��ָ������timu.choice_questions��ĩβ
                //�����������ڵ�����Ϊ2->4->11->3->NULL
				//��ʼforѭ��ǰpָ��3��p->nextָ��4
				//forѭ��������pָ��3,p->nextָ��NULL
				for(;p->next;p = p->next);
				p->next = p2;//��p2����p->nextָ���NULL
			}
			//�������timu.choice_questions��ͷ�ڵ�Ϊ��,�����else���
			//��p2����ͷ�ڵ�
			else timu.choice_questions = p2;
			i02++;//i02��1,���ڽ���while����ж��Ƿ��ӡ��һ��ѡ����
		}
 		if(temp == EOF)return 0;
		
		//i03(��ʾ��ǰ��ӡ��������Ŀ��)��ʼΪ0,��i03С��i3(���ж�����)ʱ�˳�whileѭ��
		while(i03 < i3)
		{
			//��p3����GF_questions���͵�ָ��
			GF_questions *p3 = (GF_questions *)malloc(sizeof(GF_questions));
  			if(p3 == NULL)//�������ʧ�������if���
			{
				printf("||�����ڴ�ʧ��,���ܴ�ӡ�ж�����Ŀ\n||");//��ʾ�û������ڴ�ʧ��
				break;//������ǰwhileѭ��
			}
            //��������ڴ�ɹ�,�����ļ��ж�ȥ�����Ϣ(����Ŀ���𰸺ͷ���)
            //��ȡ�������Ŀ
			for(i = 0;;i++)
			{
				//��tempʱ�����ļ��ж�ȡ���ַ�
				temp = fgetc(fpr);
				if(temp == EOF)
				{
					//��ʾ�û������ԭ��
					printf("��ȡ����\n");
					system("pause");//��ͣ���û����
					system("cls");
					break;
				}
				if(temp == 35)break;
				p3->gf_question[i] = temp;
			}
			//����Ч�ַ���ĩβ��Ϊ'\0'
			p3->gf_question[i] = '\0';

			//��ȡ�����ı�׼��
			for(i = 0;;i++)
			{
				temp = fgetc(fpr);
				if(temp == EOF)
				{
					//��ʾ�û�����ԭ��
					printf("��ȡʧ��\n");
					system("pause");//��ͣ���û����
					system("cls");
					break;
				}
				if(temp == 35)break;
				p3->gf_answer[i] = temp;
			}
			//����Ч�ַ���ĩβ��Ϊ'\0'
			p3->gf_answer[i] = '\0';
			
			//��ȡ��������ֵ�Լ����з�(��ȡ���з������������ڶ�ȡ��һ��)
			fscanf(fpr,"%f\n",&p3->gf_score);
			if(feof(fpr))break;//��������ļ�ĩβ�������ǰѭ��
			p3->next = NULL;//��p3ָ���next��ΪNULL(����Ұָ��)
			if(timu.gf_questions)//�������timu.gf_questions��ͷ�ڵ㲻Ϊ��,�����if���
			{
				//����GF_questions���͵�ָ��pָ��timu.gf_questions��ͷ�ڵ�
				GF_questions *p = timu.gf_questions;
   				//for������:��ָ��p��forѭ��ָ������timu.gf_questions��ĩβ
                //�����������ڵ�����Ϊ32->1->10->34->NULL
				//��ʼforѭ��ǰpָ��32��p->nextָ��1
				//forѭ��������pָ��34,p->nextָ��NULL
				for(;p->next;p = p->next);
				p->next = p3;//��p3����p->nextָ���NULL
			}
  			//�������timu.gf_questions��ͷ�ڵ�Ϊ��,�����else���
			//��p3����ͷ�ڵ�
			else timu.gf_questions = p3;
			i03++;//i03��1,���ڽ���while����ж��Ƿ��ӡ��һ�����
		}
 		if(temp == EOF)return 0;
		//���ļ��иÿ��Ե����ַ�ֵ����timu.full_mark
		fscanf(fpr,"%f\n",&timu.full_mark);

		return 1;//����1��ʾ�ļ�����Ŀ
	}

	fclose(fpr);//�ر��ļ�
}

//ѧ����ʼ����
//start_exam�ǲ�����ֵ�ĺ���
//�β�һ����Student_timu���͵�ָ����������ѧ���û��Ĵ����¼
//��һ����Stu���͵Ķ���ָ��mark,�����޸Ŀ���״̬�ͱ���ѧ���ɼ�
void start_exam(Student_timu *student_timu,stu **mark)
{
	TF_questions *p111 = NULL;//����ĩβ�����ж�����Ŀ(ͬ��)
	Choice_questions *p222 = NULL;
	GF_questions *p333 = NULL;
	//tf_questions_count,Choice_questions_count,gf_questions_count�ֱ����ж���,ѡ���������������
	//i������ѭ���˶�ѧ���жϺ�ѡ����𰸺͸�ѧ������������,choice����ѡ��Ҫ�޸ĵ���Ŀ
	int tf_questions_count = 0,Choice_questions_count = 0,gf_questions_count = 0,i = 0,count = 0,choice = 0;

	//read_timu_file���������Ƕ�ȡ"timu(clear)"�ı��ļ��е���Ŀ,���ں���print_timu��ӡ��Ŀ
	//read_timu_file����������β�Ϊ1����,��ȡ���û�Ϊѧ���û�,read_timu_file�������ص�ֵ���Ϊ0�����if���
	if(!read_timu_file(1))
	{
		printf("||!��������Ϣ��ȡʧ�ܡ�!\n||");//��ʾ�û���Ϣ��ȡʧ��
		system("pause");//��ͣ���û������Ϣ
		system("cls");
		return;//�ص�ѧ���˵�
	}
	//��ֻ���ķ�ʽ����Ϊ"timu(clear)"���ı��ļ�,�������ص�ָ�븳��fpr
	FILE *fpr = fopen("timu(clear).txt","r");
    //���ļ��ж�ȡ��������Ŀ��
	fscanf(fpr,"%d,%d,%d",&tf_questions_count,&Choice_questions_count,&gf_questions_count);
	fclose(fpr);//�ر��ļ�
	
	//examination_status��������Ŀ���״̬,�������1��������
	if((*mark)->Stu.examination_status == 1)
	{
		//��ʾ���û��Ѿ���������,�����ٿ�����
		printf("��������������⵽���Ѿ�������,���Բ������ٴο����ˡ�����������\n");
		system("pause");//��ͣ���û����
		system("cls");
		return;//����ѧ���˵�
	}
    (*mark)->Stu.examination_status = 1;//�������״̬Ϊ0,���丳Ϊ1,Ȼ��ʼ����Ŀ���
    system("cls");
    print_timu(4);
    system("pause");
    system("cls");
    
	do
	{
		system("cls");
	    print_timu(1);//��ӡ���������Ŀ
	    printf("=============================\n");
	    printf("||�������ж����(��YNNYNY)\n||");//��ʾ�û������ж����
	    //�������Ĵ�Ϊ�س������whileѭ�����������𰸵�����֪������Ĵ𰸲�Ϊ�س�(ͬ��)
	    while(strcmp(gets(student_timu->stu_tf_answer),"\n") <= 0)
	        printf("||");//||Ϊ�˺�����߶���(ͬ��)
		count = 0;
        for(i = 0;i < tf_questions_count;i++)
        	if(student_timu->stu_tf_answer[i] != 'Y'&&student_timu->stu_tf_answer[i] != 'N')
				count++;
		if(count)
		{
		    printf("||����%d���ⲻ������дҪ��,��Ҫ������д\n||",count);
		    system("pause");
		    continue;
		}
		student_timu->stu_tf_answer[i] = '\0';
		break;
	}while(1);
	
	do
	{
 	    system("cls");
		print_timu(2);
		printf("=============================\n");
	    printf("||������ѡ�����(��AACDBA)\n||");//��ʾ�û�����ѡ�����
	    while(strcmp(gets(student_timu->stu_choice_answer),"\n") <= 0)
	        printf("||");
	 	count = 0;
	    for(i = 0;i < Choice_questions_count;i++)
			if(student_timu->stu_choice_answer[i] != 'A' && student_timu->stu_choice_answer[i] != 'B' && student_timu->stu_choice_answer[i] != 'C' && student_timu->stu_choice_answer[i] != 'D')
				count++;
			//����Ϊ�����Ĵ���
			//_choice_answer[i] != 'B' && student_timu->stu_choice_answer[i
			//] != 'C' && student_timu->stu_choice_answer[i] != 'D')
   		if(count)
		{
		    printf("||����%d���ⲻ������дҪ��,��Ҫ������д\n||",count);
		    system("pause");
		    continue;
		}
		student_timu->stu_choice_answer[i] = '\0';
		break;
    }while(1);
    
    system("cls");
    print_timu(3);
	//��ʼ��i=0,����forѭ��,���iС���������Ŀ�������ѭ��,�������ѭ��
	for(i = 0;i < gf_questions_count;i++)
	{
		printf("=============================\n");
	    printf("||�������%d��������\n||",i+1);
 	    while(strcmp(gets(student_timu->stu_gf_answer[i]),"\n") <= 0)
	        printf("||");
	}
	printf("||===================================\n");
	//��ʾ�û��Ƿ�����޸�,���Ҫ�޸�������y,������޸������������ַ�
	printf("||�������\n||");
	system("pause");
	system("cls");

	do//��ѭ��,�����������������choice��������õ�,����и�break���ڽ���ѭ��
	{
		system("cls");
		printf("||==============================||\n");
		printf("||����Ҫ�޸���?\t\t\t||\n");//��ʾ�û�ѡ����
		printf("||==============================||\n");
		printf("||��Ҫ�޸���������Ҫ�޸ĵ�����  ||\n");
		printf("||������Ҫ������4\t\t||\n");
		printf("||==============================||\n");
	    printf("||1.�ж���\t\t\t||\n");
	    printf("||2.ѡ����\t\t\t||\n");
	    printf("||3.�����\t\t\t||\n");
	    printf("||4.�����޸�\t\t\t||\n");
	    printf("||==============================||\n||");
		
	    if(scanf("%d",&choice) != 1)//���choice��Ϊ�������������if���
	    {
		    input_again();//��ʾ�û���������
		    continue;//����ѭ��
	    }
	    take_in_line_break();
	    system("cls");

		switch(choice)//ѡ����
		{
		  	case 1:
			 	do
	            {
		            system("cls");
	                print_timu(1);//��ӡ���������Ŀ
	                printf("=============================\n");
	                printf("||�������ж����(��YNNYNY)\n||");//��ʾ�û������ж����
	                //�������Ĵ�Ϊ�س������whileѭ�����������𰸵�����֪������Ĵ𰸲�Ϊ�س�(ͬ��)
	                while(strcmp(gets(student_timu->stu_tf_answer),"\n") <= 0)
	                    printf("||");//||Ϊ�˺�����߶���(ͬ��)
		            count = 0;
                    for(i = 0;i < tf_questions_count;i++)
        	            if(student_timu->stu_tf_answer[i] != 'Y'&&student_timu->stu_tf_answer[i] != 'N')
				            count++;
		            if(count)
		            {
		                printf("||����%d���ⲻ������дҪ��,��Ҫ������д\n||",count);
		                system("pause");
		                continue;
		            }
		            student_timu->stu_tf_answer[i] = '\0';
		            break;
	            }while(1);
	            break;
	        case 2:
				do
	            {
 	                system("cls");
		            print_timu(2);
		            printf("=============================\n");
	                printf("||������ѡ�����(��AACDBA)\n||");//��ʾ�û�����ѡ�����
	                while(strcmp(gets(student_timu->stu_choice_answer),"\n") <= 0)
	                    printf("||");
	 	            count = 0;
	                for(i = 0;i < Choice_questions_count;i++)
			            if(student_timu->stu_choice_answer[i] != 'A' && student_timu->stu_choice_answer[i] != 'B' && student_timu->stu_choice_answer[i] != 'C' && student_timu->stu_choice_answer[i] != 'D')
				            count++;
   		            if(count)
		            {
		                printf("||����%d���ⲻ������дҪ��,��Ҫ������д\n||",count);
		                system("pause");
		                continue;
		            }
		            student_timu->stu_choice_answer[i] = '\0';
		            break;
                }while(1);
	            break;
	        case 3:
		 		printf("||==============================||\n||");
	        	printf("��Ҫ�޸ĵڼ���������?\n||");//��ʾ�û�����������
		  		if(scanf("%d",&i) != 1)//���i��Ϊ�������������if���
		        {
		            printf("||���벻��Ϊ������\n");//��ʾ�û�����ԭ��
			        input_again();//��ʾ�û���������
			        continue;//����ѭ��
		        }
		        else
					if(i > gf_questions_count || i <= 0)
					{
						//������������Ϊ�������ǲ�����Ŀ����Χ��Ҳ����if���
					    //��ʾ�û�����ԭ��
						printf("||���������Ҫ������Ч��Ŀ����Χ��(1~%d)\n",gf_questions_count);
	  			        input_again();//��ʾ�û���������
			            continue;//����ѭ��
					}
	            take_in_line_break();
	            printf("||�������%d��������\n||",i);
 	            while(strcmp(gets(student_timu->stu_gf_answer[i-1]),"\n") <= 0)
	                printf("||");
	            break;
            case 4://�������4���˳�ѭ������ѧ���˵�
            	system("cls");
				break;
			default://��������ַ������input_again�����������
			 	input_again();
				break;
		}
		printf("||�޸ĳɹ�\n||");
		system("pause");
		if(choice == 4)break;
	}while(1);
	
   	printf("||�������\n");//������ʾ�û��������
    printf("||����ing......\n");//������ʾ�û����ڼ���ɼ�
    //��ѧ���ɼ���ֵ
    (*mark)->Stu.grade = calculate_score(student_timu,gf_questions_count);
    student_timu->Stu.examination_status = 1;
    student_timu->Stu.grade = (*mark)->Stu.grade;
	printf("||������Ϣing......\n");//��ʾ�û����ڱ�����Ϣ
	stu_save_stu(student_timu);//����ѧ������Ŀ��Ϣ(��ѧ����Ŀ��������������в���)
	save_id_studentinfo();//����ѧ����Ϣ
	delete_timu();//ɾ����Ŀ�����е���Ŀ
}

//��ӡ��Ŀ
void print_timu(int flag)
{
	TF_questions *p111 = NULL;//ָ��TF_questions���͵�ָ��p111��������ĩβ�����ж�����Ŀ(ͬ��)
	Choice_questions *p222 = NULL;
	GF_questions *p333 = NULL;
	int i1 = 0,i2 = 0,i3 = 0,i = 0,count = 0;//count������ӡ���,i����ѭ����ѧ������������

    //��ֻ���ķ�ʽ����Ϊ"timu(clear)"���ı��ļ�,�������ص�ָ�븳��fpr
	FILE *fpr = fopen("timu(clear).txt","r");
	if(fpr == NULL)
	{
		printf("||��ȡ��Ŀ�ļ�ʧ��\n||");
		system("pause");
		system("cls");
		return;
	}
	//��i1,i2,i3�ֱ��ȡ�ж��⡢ѡ�������������Ŀ��
	fscanf(fpr,"%d,%d,%d",&i1,&i2,&i3);
	fclose(fpr);//�ر��ļ�
	
	if(flag == 4)
	{
	    printf("||=====================================\n");
	    printf("||��Ŀ����:\n");//��ʾ�û�������Ŀ
	    //���¶�����һ������
	    printf("||һ���ж���\n");
	    //����p111ָ��timu.tf_questions��ͷ�ڵ�,��p111Ϊ��ʱ����forѭ��
	    for(p111 = timu.tf_questions,count = 0;p111;p111 = p111->next,count++)
	    //��ӡ������Ч������:||1.This is a egg.
	    //                   ||��ֵ:3.000000
	    //                   ||
	    //                   ||2.This is an egg.
	    //......................................................
		    printf("||%d.%s\n||��ֵ:%f\n||\n",count+1,p111->tf_question,p111->tf_score);
	    printf("||����ѡ����\n");
	    for(p222 = timu.choice_questions,count = 0;p222;p222 = p222->next,count++)
	    //��ӡ������Ч������:||1.What color is this?
	    //                   ||ѡ��:A:red.    B:blue.    C:yellow.    D:black.
	    //                   ||��ֵ:3.000000
	    //                   ||
	    //                   ||2.What color does Gogo like?
	    //......................................................
            printf("||%d.%s\n||ѡ��:A:%s.   B:%s.   C:%s.   D:%s.\n||��ֵ:%f\n||\n",
			count+1,p222->choice_question,p222->option.option_a,p222->option.option_b,
			p222->option.option_c,p222->option.option_d,p222->cq_score);
	    printf("||���������\n");
	    for(p333 = timu.gf_questions,count = 0;p333;p333 = p333->next,count++)
	    //��ӡ������Ч������:||1.This is a ____.
	    //                   ||��ֵ:3.000000
	    //                   ||
	    //                   ||2.I like ___.
	    //......................................................
		    printf("||%d.%s\n||��ֵ:%f\n||\n",count+1,p333->gf_question,p333->gf_score);
	    //��ʾ�û��þ����Ŀ����������Ϣ
	    printf("||Ŀǰ����:%d\tĿǰ����:%.2f\n",i1+i2+i3,timu.full_mark);
	    printf("||====================================\n||");
	}
	if(flag == 1)
	{
 	    printf("||һ���ж���\n");
	    //��p111ָ��timu.tf_questions��ͷ�ڵ�,��p111Ϊ��ʱ����forѭ��
	    for(p111 = timu.tf_questions,count = 0;p111;p111 = p111->next,count++)
		    printf("||%d.%s\n||��ֵ:%f\n||\n",count+1,p111->tf_question,p111->tf_score);
	}
	if(flag == 2)
	{
 	    printf("||����ѡ����\n");
	    for(p222 = timu.choice_questions,count = 0;p222;p222 = p222->next,count++)
            printf("||%d.%s\n||ѡ��:A:%s.   B:%s.   C:%s.   D:%s.\n||��ֵ:%f\n||\n",
			count+1,p222->choice_question,p222->option.option_a,p222->option.option_b,
			p222->option.option_c,p222->option.option_d,p222->cq_score);
	}
	if(flag == 3)
	{
 	    printf("||���������\n");
	    for(p333 = timu.gf_questions,count = 0;p333;p333 = p333->next,count++)
		    printf("||%d.%s\n||��ֵ:%f\n||\n",count+1,p333->gf_question,p333->gf_score);
	}
}

//����ɼ�
//calculate_score�Ǹ�����һ�������ȸ��������ĺ���,����Ϊ�������֮���ѧ���ɼ�
//������һ���β�ָ��Student_timu���͵�ָ��student_timu,��ָ��ָ��ǰѧ���Ŀ�����Ϣ,���ں����ڲ��𰸵ĺ˶�����
//�����ڶ����β�ʱһ��������gf_questions_count,ѭ���˶������Ĵ�
float calculate_score(Student_timu *student_timu,int gf_questions_count)
{
	//i1,i2,i3��������Ŀ����ݹ�
	int i1,i2,i3;
	TF_questions *p1 = NULL;//����ָ��TF_questions���͵�ָ�����p1,��������ж�����Ŀ(ͬ��)
	Choice_questions *p2 = NULL;
	GF_questions *p3 = NULL;

    //���Ƚ�ѧ���ķָ�ֵΪ��
    student_timu->stu_full_mark = 0;
    //�ж���𰸺˶Լ���ͼ,ѡ����������ͬ��
    //����ѧ����:YYNYNNY(ע���ʱ��������һ���,Ϊһ����ֵ)
	//��׼��Ϊ:YYYYNNN(ע��ô���ʵ��һ�������໥���ӵ�,��Y->Y->Y->Y->N->N->N->NULL)
    //��ʼi0 = 0��p1ָ��timu.tf_questions���׵�ַ(��Y�ĵ�ַ)
	//�ж�student_timu->stu_tf_answer[i1]�Ƿ�Ϊ'\0'(����������forѭ��,������һ�����;�������ѭ��)
	//���ѧ���𰸵�i1��Ԫ��(��student_timu->stu_tf_answer[i1])����p1��ָ���ж���𰸵ĵ�һ��Ԫ��,�����if���
	//�������if���ѧ���ķ��������ӵ�ǰp1��ָ�Ľڵ�ķ���(������ķ�ֵ),Ȼ�������һ��
	//if���������������if���֮��i1��1,p1ָ��ǰ�ڵ���ָ�����һ���ڵ�
	//Ȼ���ٴν���for�����ж�����
	for(p1 = timu.tf_questions,i1 = 0;student_timu->stu_tf_answer[i1] != '\0';i1++,p1 = p1->next)
        if(student_timu->stu_tf_answer[i1] == p1->tf_answer[0])
        	student_timu->stu_full_mark += p1->tf_score;
	for(p2 = timu.choice_questions,i2 = 0;student_timu->stu_choice_answer[i2];i2++,p2 = p2->next)
		if(student_timu->stu_choice_answer[i2] == p2->cq_answer[0])
			student_timu->stu_full_mark += p2->cq_score;
	for(p3 = timu.gf_questions,i3 = 0;i3 < gf_questions_count;i3++,p3 = p3->next)
		if(strcmp(student_timu->stu_gf_answer[i3],p3->gf_answer) == 0)
			student_timu->stu_full_mark += p3->gf_score;
	printf("||�����������!����\n");//��ʾ�û��������
	
	return student_timu->stu_full_mark;//���ؼ���֮��ѧ���ķ���
}

//����ѧ��������Ϣ
//stu_save_stu��һ��������ֵ�ĺ���
//�β���һ��ָ��Student_timu���͵�ָ��student_timu
//���ڽ�ѧ��������Ϣ����ĩβ׷�ӵķ�ʽ���뵽��Ϊ"stu"��"stu(clear)"���ļ�
void stu_save_stu(Student_timu *student_timu)
{
	read_stu_exam_list();
	//��ֻд�ķ�ʽ�ֱ�򿪵���Ϊ"stu"��"stu(clear)"���ļ�,�������ص�ָ��ֱ𸳸�fpw1��fpw2
	FILE *fpw1 = fopen("stu(clear).txt","w");
	FILE *fpw2 = fopen("stu.txt","w");
	//i����ѭ����ѧ������������,gf_questions_count���ڱ����������Ŀ��
	int i = 0,gf_questions_count = 0;
	Student_timu_list *p = student_timu_list;
	Student_timu_list *p1 = student_timu_list;

    //��ֻ���ķ�ʽ����Ϊ"timu(clear)"���ļ�,�������ص�ָ�븳��fpr
	FILE *fpr = fopen("timu(clear).txt","r");
	if(fpr == NULL)
	{
		printf("||�����ļ�ʧ��\n||");
		system("pause");
		system("cls");
		return;
	}
	//��ȡ�������Ŀ��
	fscanf(fpr,"%*d,%*d,%d",&gf_questions_count);
	fclose(fpr);//�ر��ļ�
	
	//���ȴ�ӡ��"stu"�ı��ļ���(stu�������)
	
	for(p = student_timu_list;p;p = p->next)
	    if(p->stu_timu.Stu.id == student_timu->Stu.id)
	    {
			p->stu_timu = *student_timu;
			p->stu_timu.Stu.examination_status = student_timu->Stu.examination_status;
			p->stu_timu.Stu.grade = student_timu->Stu.grade;
			break;
		}

	for(p1 = student_timu_list;p1;p1 = p1->next)
	{
		fprintf(fpw1,"%s %s %d %s %f %s %s ",p1->stu_timu.Stu.majority,
		p1->stu_timu.Stu.class,p1->stu_timu.Stu.id,p1->stu_timu.Stu.name,
		p1->stu_timu.Stu.grade,p1->stu_timu.stu_tf_answer,p1->stu_timu.stu_choice_answer);
		for(i = 0;i < gf_questions_count-1;i++)
			fprintf(fpw1,"%s#",p1->stu_timu.stu_gf_answer[i]);
		fprintf(fpw1,"%s",p1->stu_timu.stu_gf_answer[gf_questions_count-1]);
		fprintf(fpw1,"\n");
	}

	fclose(fpw1);

	fprintf(fpw2,"רҵ******�༶*****ѧ��******����******�ɼ�******ѧ���ж����*****ѧ��ѡ�����*****ѧ��������\n");
	for(p1 = student_timu_list;p1;p1 = p1->next)
	{
	    fprintf(fpw2,"%s\t%s\t%d\t%s\t%f\t%s\t\t%s\t\t",p1->stu_timu.Stu.majority,
		p1->stu_timu.Stu.class,p1->stu_timu.Stu.id,p1->stu_timu.Stu.name,
		p1->stu_timu.Stu.grade,p1->stu_timu.stu_tf_answer,p1->stu_timu.stu_choice_answer);
	    for(i = 0;i < gf_questions_count;i++)
		    fprintf(fpw2,"(%d).%s\t",i+1,p1->stu_timu.stu_gf_answer[i]);
	    fprintf(fpw2,"\n");
	}

	fclose(fpw2);//�ر�"stu(clear)"�ļ�
	delete_stu_exam_list();
}

//ɾ����Ŀ����(����ɾ��ȫ�ֱ���timu)
//delete_timu�ǲ�����ֵ�ĺ���,Ҳ���β�
void delete_timu(void)
{
	TF_questions *p1 = timu.tf_questions;
	Choice_questions *p2 = timu.choice_questions;
	GF_questions *p3 = timu.gf_questions;
	
	if(p1 == NULL || p2 == NULL || p3 == NULL)//���p1��p2��p3�õ���ָ���Ϊ�ս������
	{//����ifp1��p2��p3�����з����ڴ�ʧ��
		printf("||!�������ļ�ʧ�ܡ�!\n||");
		system("pause");//��ͣ���û����
		return;//����
	}
	
	//���ж���Ϊ��,�����ѡ����������Ҳһ��
	//���p1�Ĳ�Ϊ��,�����if���(˵������ͷ��Ϊ��)
	while(p1)
	{
		//��ָ��p1����p11
        TF_questions *p11 = p1;
        //Ȼ��ָ��p1ָ����һ���ڵ��ͷ
        p1 = p1->next;
        //Ȼ�󽫵�ǰ��ͷ�ڵ��ͷ�,��ʱԭ���ڶ����ڵ��Ϊͷ(Ҳ���ǵ�һ���ڵ�)
        free(p11);
        p11 = NULL;
	}
    //����ٰ�ͷ�ڵ���Ϊ��,����������˽��ж�������ĵ�����ȫ��ɾ����
    timu.tf_questions = NULL;

    //����ͬ�ж���
	while(p2)
	{
        Choice_questions *p22 = p2;
        p2 = p2->next;
        free(p22);
        p22 = NULL;
	}
    timu.choice_questions = NULL;
		
    //����ͬ�ж���
	while(p3)
	{
        GF_questions *p33 = p3;
        p3 = p3->next;
        free(p33);
        p33 = NULL;
	}
	timu.gf_questions = NULL;
	
	//��󽫾���������Ϊ0(����ʾ�þ�û����Ŀ)
	timu.full_mark = 0;
}

//ѧ���޸�����
//change_password��һ����������ֵ�ĺ���,�β�mark��һ������ָ��,�����������ַ���ı�ֵ��
void change_password(stu **mark)
{
	//new_password��������ѧ����������,re_new_password����ѧ���ٴ�ȷ������
	//flag���������жϵ�һ�κ͵ڶ�������������Ƿ�һ��,���������ж�����������Ƿ�����Ҫ��
	int new_password,re_new_password,flag = 1;
	
	system("cls");
	printf("||======================================================================||\n");
	printf("||�㵱ǰ������Ϊ%d\n",(*mark)->Stu.password);//��ʾ�û���ǰ������
	
	do
	{
		//���flagΪ0�����if���
		if(flag == 0)
		{
			printf("||======================================================================||\n");
			//��ʾ�û����������,��Ҫ�����������һ������
			printf("||ǰ�������벻һ��!!!�����������һ��������(������λ��)(����0�˳�����)  ||\n||");
		}
		//���flagΪ1�����if���
		if(flag == 1)
		{
			printf("||======================================================================||\n");
			//��ʾ�û������Լ���Ҫ�ı��������
	        printf("||���������������(������λ��)(����0�˳�����)\n||");
	    }
	    
 		if(scanf("%d",&new_password) != 1)//���new_password��Ϊ�������������if���
		{
			input_again();//��ʾ�û���������
			continue;//����ѭ��
		}
		//��ʱif��������new_passwordΪ��������
	    take_in_line_break();
	    system("cls");
	    
	    //����return_by_zero�������˳��ù���
	    //����ԭ��:�����õ��û��������(��new_password)
		//����û�Ϊ0�����ʾ�û��˳��ɹ�����ͣ�ҷ���1,���򷵻�0
	    //�������ֵΪ1,�����if���;�������ֵΪ0,������if���
	    if(return_by_zero(new_password))return;
	    //�����һ��������������Ҫ��ͽ���if���,��������if���
	    if(new_password < 10000 && new_password > 999)
	    {
			do//����ѭ������ѭ������ڶ���������,��ʱ�õ��ĵڶ���������Ϊ��������
			{
	    	    //��ʾ�û��ڶ�������������
		        printf("||���ٴ��������������(����0�˳�����)\t\t\t\t\t||\n||");
		        if(scanf("%d",&re_new_password) != 1)//���re_new_password��Ϊ�������������if���
		        {
			        input_again();//��ʾ�û���������
			        continue;//����ѭ��
		        }
	            take_in_line_break();
	            break;//�˳���ѭ��
	        }while(1);
	        
	        //����return_by_zero�������˳��ù���
	        //����ԭ��:�����õ��û��������(��re_new_password)
			//����û�Ϊ0�����ʾ�û��˳��ɹ�����ͣ�ҷ���1,���򷵻�0
	        //�������ֵΪ1,�����if���;�������ֵΪ0,������if���
	        if(return_by_zero(re_new_password))return;
	        
            //����ڶ��������������Ϊ��λ����������
	        if(re_new_password < 10000 && re_new_password > 999)
	        {
	        	//�жϵ�һ�κ͵ڶ���������������Ƿ�һ��,�����һ�������if���,�����������
			    if(new_password != re_new_password)
			    {
			    	//�����һ����flag��Ϊ0,���ż���ѭ��
			    	flag = 0;
			    	continue;
			    }
			    //��ʱ��һ�κ͵ڶ������������һ��,�˳�ѭ��,�˳�ѭ��֮��ͽ�ѧ����������Ϊ������
		        break;
            }
            
            //����ڶ�������������벻Ϊ��λ�������else���
            else
			{
				//��ʾ�û���������ԭ��
			    printf("||����������벻����Ҫ��(Ҫ����λ����)\t\t\t\t\t||\n");
			    printf("||======================================================================||\n");
			    flag = 0;//��flag��Ϊ0
			}
	    }
	    
	    //�����һ������������벻Ϊ��λ����������
	    else
		{
			//��ʾ�û���������ԭ��
		    printf("||����������벻����Ҫ��(Ҫ����λ����)\t\t\t\t\t||\n");
		    printf("||======================================================================||\n");
		}
	    system("pause");//��ͣ���û������Ϣ
	    system("cls");
	}while(1);
	//�������븳����ǰ����ѧ��������
	(*mark)->Stu.password = re_new_password;
	//��ʾ�û�����ɹ�
	printf("||���������޸ĳɹ�!����\n");
	printf("||======================================================================||\n");
	save_id_studentinfo();//����ѧ����Ϣ
	system("pause");//��ͣ���û������Ϣ
	system("cls");
}

//ѧ����������
//stu_talking��һ����������ֵ�ĺ���,�β�markʱ����ȷ��������Ϣ���û�������
void stu_talking(stu *mark)
{
	system("cls");
	int choice = 0;//����ѡ����
	//����teacher_t���ڸ��û���ʦ�������ļ�(������ʦ������Ⱥ)
	char teacher_t[TALKING_FILE_NAME] = "stu_and_tea_communication.txt";
	//����student_t���ڸ��û���ѧ�������ļ�(������ѧ������Ⱥ)
	char student_t[TALKING_FILE_NAME] = "stu_and_stu_communication.txt";

	do
	{
		//��ʾ�û������ѧ����������˵�
		system("cls");
	    printf("||==============================||\n");
	    printf("||1.����ѧ������Ⱥ\t\t||\n");
	    printf("||2.����ʦ������Ⱥ\t\t||\n");
	    printf("||3.�˳���������,���ز˵�\t||\n");
	    printf("||==============================||\n||");
	    
 		if(scanf("%d",&choice) != 1)//���choice��Ϊ�������������if���
		{
			input_again();//��ʾ�û���������
			continue;//����ѭ��
		}//if���֮���choiceΪ�������͵���
		
		//����û�ѡ��1��2�����if���
	    if(choice == 1 ||choice == 2)
	    {
	    	//����û�ѡ��1�����if���(1�����ѧ���ǽ���)
	        if(choice == 1)
	        {
	        	//������Ϣ,�����û�Ҫ�򿪵��ļ���(��ʱ�û�Ҫ��ѧ������Ⱥ���ļ�)
                receive_message(student_t);
                //������Ϣ,�����û�Ҫ�򿪵��ļ������û�����(��ʱ�û�Ҫ��ѧ������Ⱥ���ļ�)
		        send_message(student_t,mark->Stu.name);
	        }
	        //����û�ѡ��2�����if���(2�������ʦ����)
	        if(choice == 2)
	        {
	        	//������Ϣ,�����û�Ҫ�򿪵��ļ���(��ʱ�û�Ҫ��ʦ������Ⱥ���ļ�)
		        receive_message(teacher_t);
		        //������Ϣ,�����û�Ҫ�򿪵��ļ������û�����(��ʱ�û�Ҫ��ʦ������Ⱥ���ļ�)
		        send_message(teacher_t,mark->Stu.name);
	        }
	    }
	    
	    //�����ѡ��1��2�����else���
	    else
		{
			//���ѡ��3�����if���(3�����˳�����)
		    if(choice == 3)
		    {
			    printf("||�˳��ɹ�\n||");//��ʾ�û��˳��ɹ�
			    system("pause");//��ͣ���û������Ϣ
			    system("cls");
			    return;
		    }
		    
		    //����������������������else���
			else
		    {
		    	//��ʾ�û��������,����������
			    printf("||�����������������\n||");
			    system("pause");//��ͣ���û������Ϣ
			    system("cls");
			    continue;
		    }
		}
	}while(1);

	system("cls");
}

//��ʦ�˵�
void teacher_menu(void)
{
	int choice;//���ڽ�ʦѡ����
	
	while(1)
	{
		//��ʾ�û�ѡ����
		printf("||==============================================||\n");
		printf("||\t\t��ǰΪ��ʦģʽ\t\t\t||\n");//��ʾ�û���ǰ����Ϣ
		printf("||==============================================||\n");
		printf("||\t\t��ѡ����\t\t\t||\n");
		printf("||==============================================||\n");
		printf("||\t\t1.��������\t\t\t||\n");
		printf("||\t\t2.¼��ѧ����Ϣ\t\t\t||\n");
		printf("||\t\t3.�鿴ȫ��ѧ���ɼ�\t\t||\n");
		printf("||\t\t4.���Ҹ���ѧ����Ϣ\t\t||\n");
		printf("||\t\t5.�޸�ѧ����Ϣ\t\t\t||\n");
		printf("||\t\t6.ɾ��ѧ�������Ϣ\t\t||\n");
		printf("||\t\t7.ɾ��ѧ��������Ϣ\t\t||\n");
		printf("||\t\t8.�鿴ɾ����ѧ�����Լ�¼\t||\n");
		printf("||\t\t9.��������\t\t\t||\n");
		printf("||\t\t10.�����ܲ˵�\t\t\t||\n");
		printf("||==============================================||\n||");

		//�Ӽ��̻��1,2,3,4,5,6,7,8,9
		if(scanf("%d",&choice) != 1)//���choice�����������������if���
		{
			input_again();//��ʾ�û���������
			continue;//����ѭ��
		}
		take_in_line_break();

		switch (choice)
		{
			case 1://��������
				post_examination();
            	break;
			case 2://¼��ѧ����Ϣ
				input_studentinfo();
				break;
			case 3://�鿴ȫ��ѧ���ɼ�
				print_studentinfo();
				break;
			case 4://�鿴����ѧ����Ϣ
				seek_studentinfo();
				break;
			case 5://�޸�ѧ����Ϣ
				modify_studentinfo();
				break;
            case 6://ɾ��ѧ�������Ϣ
				remove_student_id_info();
            	break;
            case 7://ɾ��ѧ��������Ϣ
				remove_student_exam_info();
            	break;
		    case 8://�鿴�ѱ�ɾ����ѧ����Ϣ
				print_stu_deleted_exam_info();
            	break;
		    case 9://��ʦ��������
				tea_talking();
            	break;
			case 10://�����ܲ˵�
			    printf("||�ɹ�����\n||");
	            system("pause");//��ͣ���û������Ϣ
	            system("cls");
                return;
			default ://��������
				input_again();
				break;
		}
	}
}

//��������
void post_examination(void)
{
	//ch����ȷ���û��Ƿ�Ҫ¼��
	char ch;
	//i0����ѭ��,i1��ǵ�ʱ��Ҫ���õ��ж�������,i11������ж�������(��������ͬ��)
	int i0,i1 = 0,i11 = 0,i2 = 0,i22 = 0,i3 = 0,i33 = 0,count = 0;
	//Timu_flag�����ж��û��Ƿ񻹼���¼����Ŀ,TF_flag�����ж��ж�����Ƿ�ΪY��N
	//Option_flag�����ж�¼���ѡ������Ƿ�ΪABCD����֮һ
	int Timu_flag = 0,TF_flag = 0,Option_flag = 0;

	//����post_exam_menu����,���������ص�ֵ����flag
	Timu_flag = post_exam_menu(&i11,&i22,&i33);
	//������ص�ֵΪ0,����if���,˵���û�ѡ���˳�
	if(Timu_flag == 0)return;

	do
	{
		//��ʾ�û�ÿ������Ҫ���ö��ٵ���
		system("cls");

		do
		{
            printf("||��Ҫ���ö��ٵ��ж���?(����С�ڵ������˳�����)||\n||");
            if(scanf("%d",&i1) != 1)//���i1�����������������if���
		    {
			    input_again();//��ʾ�û���������
			    continue;//����ѭ��
		    }
			break;
		}while(1);
        take_in_line_break();
        if(i1 < 0)break;
        
       system("cls");

		do
		{
            printf("||��Ҫ���ö��ٵ�ѡ����?(����С�ڵ������˳�����)||\n||");
            if(scanf("%d",&i2) != 1)//���i2�����������������if���
		    {
			    input_again();//��ʾ�û���������
			    continue;//����ѭ��
		    }
		    break;
		}while(1);
        take_in_line_break();
        if(i2 < 0)break;
        
        system("cls");

		do
		{
            printf("||��Ҫ���ö��ٵ��������?(����С�ڵ������˳�����)||\n||");
            if(scanf("%d",&i3) != 1)//���i3�����������������if���
		    {
			    input_again();//��ʾ�û���������
			    continue;//����ѭ��
		    }
		    break;
		}while(1);
        take_in_line_break();
        if(i3 < 0)break;
        if(i1 == 0 && i2 == 0 && i3 == 0)break;

        system("cls");

		//��ѭ�����ڸ���ʦ¼���ж���
	    for(i0 = 0;i0 < i1;i0++,i11++)
	    {
	    	//����һ��TF_questions��С���ڴ�,�õ���ָ�븳��p11,���ⶨ��һ��ָ��TF_questions���͵�ָ��p
		    TF_questions *p11 = (TF_questions *)malloc(sizeof(TF_questions)),*p = NULL;
		    
		    if(p11 == NULL)//���p11�õ���ָ��Ϊ��,�����if���,����˵�������ڴ�ʧ��,���˳�¼���ж���
		    {
		    	//��ʾ�û�����ʧ�ܵ�ԭ��
		    	printf("||!�������ڴ�ʧ�ܡ�!\n||");
		    	printf("pause");//��ͣ���û������Ϣ
		    	system("cls");
		    	break;
			}
			
		    //��p11��next��ΪNULL
            p11->next = NULL;
            //����timu.tf_questions�����ж��������,��ʱ���������ͷ,�����Ϊ�������if���
	        if(timu.tf_questions)
	        {
	        	//β�巨
	        	//����һ��ָ��TF_questions���͵�ָ��tf_tail,����tf_tailָ���ж��������ͷ�ڵ�
	        	TF_questions *tf_tail = timu.tf_questions;
                //����ѭ��ֱ��tf_tailΪ���һ���ڵ�
	        	for(;tf_tail->next;tf_tail = tf_tail->next);
	        	//��ʱ��tf_tail��nextΪ��,���丳Ϊp11
	    	    tf_tail->next = p11;
		    }
		    else//���timu.tf_questions����ͷΪ�������else���
                //��p11��������ͷ�ڵ�
			    timu.tf_questions = p11;
            //��ʾ�û�������ж�����Ŀ
		    printf("||�����������%d���ж�����Ŀ����\n||",i11+1);
  	        while(strcmp(gets(p11->tf_question),"\n") <= 0)
	            printf("||");
            //��ʾ�û�������ж������
		    printf("||�����������%d���ж���Ĵ�(Y or N)����\n||",i11+1);
		    do
		    {
		    	//���ж���������־��Ϊ0(0��ʾ��δ�д𰸻���õ��Ĵ𰸲�����¼���׼)
		    	TF_flag = 0;
		        scanf("%s",p11->tf_answer);
		        //���¼��Ĵ�ΪY��N���ñ�־��Ϊ1
		        if(p11->tf_answer[0] == 'Y')TF_flag = 1;
		        if(p11->tf_answer[0] == 'N')TF_flag = 1;
		        //�����־Ϊ0�����if�����˵���õ���¼��𰸴���
		        if(TF_flag == 0)
		        {
		        	//��ʾ¼��𰸴����ԭ��,����ʾ�û���������
		  		    printf("||ѡ���ֻ���Ǵ�дY��N\n");
		        	printf("||�����������ж����\n||");
					continue;
				}
                //¼�����ȷ���˳�ѭ��
				break;
		    }while(1);
            take_in_line_break();

            do
            {
            	//��ʾ�û�������ж������ֵ
		        printf("||�����������%d���ж�����Ŀ�ķ�ֵ����\n||",i11+1);
		        if(scanf("%f",&p11->tf_score) != 1)
		        {
			        input_again();//��ʾ�û���������
			        continue;//����ѭ��
			    }
			    //�������ķ�ֵС��0
			    if(p11->tf_score <= 0)
			    {
			    	printf("||����ķ�ֵ��Ҫ����0,����������\n");
		            continue;
				}
				//¼��ķ�ֵ��ȷ���˳�ѭ��
			    break;
			}while(1);
            take_in_line_break();
            //����ǰ�������Ӹ��ж������ֵ�õ��µĵ�ǰ����
		    timu.full_mark += p11->tf_score;
		    system("cls");
		    //��ʾ�û��ж�����Ŀ��Ϣ(��ӡ����)
	 		printf("||======================================||\n");
		    printf("||Ŀǰ����%d���ж���:\n",i11+1);
		    for(p = timu.tf_questions; p ;p = p->next)
		        printf("||��Ŀ:%s    ��:%s    ��ֵ:%.2f\n||\n",p->tf_question,p->tf_answer,p->tf_score);
	    	printf("||Ŀǰ����ֵΪ��%0.2f\n",timu.full_mark);
	 		printf("||======================================||\n||");
	    	p11 = p11->next;
	    	free(p11);//p11����֮���ͷ��ڴ�
	    	system("pause");//��ͣ���û����
	    	system("cls");
        }
        
        //��ѭ�����ڸ���ʦ¼��ѡ����
	    for(i0 = 0;i0 < i2;i0++,i22++)
	    {
            //����һ��Choice_questions��С���ڴ�,�õ���ָ�븳��p22,���ⶨ��һ��ָ��Choice_questions���͵�ָ��p
		    Choice_questions *p22 = (Choice_questions *)malloc(sizeof(Choice_questions)),*p = NULL;
		    
  		    if(p22 == NULL)//���p22�õ���ָ��Ϊ��,�����if���,����˵�������ڴ�ʧ��,���˳�¼��ѡ����
		    {
		    	//��ʾ�û�����ʧ�ܵ�ԭ��
		    	printf("||!�������ڴ�ʧ�ܡ�!\n||");
		    	printf("pause");//��ͣ���û������Ϣ
		    	system("cls");
		    	break;
			}
			
		    //��p22��next��Ϊ��
            p22->next = NULL;
            //����timu.choice_questions�����ж��������,��ʱ���������ͷ,�����Ϊ�������if���
	        if(timu.choice_questions)
	        {
	        	//����һ��ָ��Choice_questions���͵�ָ��cq_tail,����cq_tailָ��ѡ���������ͷ�ڵ�
	        	Choice_questions *cq_tail = timu.choice_questions;
	        	//����ѭ��ֱ��cq_tailΪ���һ���ڵ�
	    	    for(;cq_tail->next;cq_tail = cq_tail->next);
	    	    //��ʱ��cq_tail��nextΪ��,���丳Ϊp22
	    	    cq_tail->next = p22;
		    }
		    else//���timu.choice_questions����ͷΪ�������else���
				//��p22��������ͷ�ڵ�
			    timu.choice_questions = p22;
			    
            //��ʾ�û������ѡ������Ŀ
		    printf("||�����������%d��ѡ������Ŀ����\n||",i22+1);
  		    while(strcmp(gets(p22->choice_question),"\n") <= 0)
	            printf("||");
		    //��ʾ�û������ѡ����ĸ���ѡ��
		    printf("||��������������Aѡ�������\n||");
  	        while(strcmp(gets(p22->option.option_a),"\n") <= 0)
	            printf("||");
		    printf("||��������������Bѡ�������\n||");
  	        while(strcmp(gets(p22->option.option_b),"\n") <= 0)
	            printf("||");
		    printf("||��������������Cѡ�������\n||");
  	        while(strcmp(gets(p22->option.option_c),"\n") <= 0)
	            printf("||");
		    printf("||��������������Dѡ�������\n||");
  	        while(strcmp(gets(p22->option.option_d),"\n") <= 0)
	            printf("||");
            //��ʾ�û������ѡ�����
            printf("||�����������%d��ѡ����Ĵ�(A��B��C��D)����\n||",i22+1);
            
            //do-whileѭ�����ڸ���Option_flag�������õ��Ĵ��Ƿ���ABCD����֮һ
            do
            {
            	//�Ƚ�ѡ����ѡ����жϱ�־��Ϊ0
            	Option_flag = 0;
		        scanf("%s",p22->cq_answer);
		        //�ж�¼���ѡ�����,������ϱ�׼��Option_flag��Ϊ1
		        if(p22->cq_answer[0] == 'A')Option_flag = 1;
		        else if(p22->cq_answer[0] == 'B')Option_flag = 1;
		        else if(p22->cq_answer[0] == 'C')Option_flag = 1;
		        else if(p22->cq_answer[0] == 'D')Option_flag = 1;
		        //����õ���¼��ѡ����𰸲�����Ҫ����������
		        if(Option_flag == 0)
		        {
		        	//��ʾ�û���ѡ��������ԭ��,��Ҫ����������
		        	printf("||ѡ���ֻ���Ǵ�дABCD����֮һ\n");
		        	printf("||����������ѡ���\n||");
					continue;
				}
				//��ʱ�õ���¼���ѡ����𰸷��ϱ�׼�˳�ѭ��
				break;
		    }while(1);
		    
            take_in_line_break();
            
            //do-whileѭ�����ڼ��õ���ѡ�����ֵ�������Ƿ���ȷ(��������ķ�ֵΪ������)
            do
            {
                //��ʾ�û������ѡ�������ֵ
		        printf("||�����������%d��ѡ����ķ�ֵ����\n||",i22+1);
		        if(scanf("%f",&p22->cq_score) != 1)
		        {
		        	input_again();
					continue;
			    }
			    if(p22->cq_score <= 0)
			    {
			    	printf("||����ķ�ֵӦ�ô���0\n");
			    	continue;
				}
			    break;
			}while(1);
            take_in_line_break();
            
            //����ѡ����ķ�ֵ���뵽��ǰ���ַ�ֵ������µ����ַ�ֵ
		    timu.full_mark += p22->cq_score;
		    
		    system("cls");
		    //��ʾ�û�Ŀǰ��ѡ������Ϣ
    	 	printf("||=====================================||\n");
		    printf("||Ŀǰ����%d��ѡ����:\n",i22+1);
            //��timu.choice_questions����ı�ͷ����p,p����forѭ����ѡ�����ӡ����
		    for(p = timu.choice_questions; p ;p = p->next)
		        printf("||��Ŀ��%s\n||ѡ�A:%s   B:%s   C:%s   D:%s\n||�𰸣�%s    ��ֵ��%f\n||\n",
				p->choice_question,p->option.option_a,p->option.option_b,p->option.option_c,
				p->option.option_d,p->cq_answer,p->cq_score);
	    	printf("||Ŀǰ����ֵΪ��%f\n",timu.full_mark);
    	 	printf("||=====================================||\n||");
	    	p22 = p22->next;
	    	free(p22);//��p22���ڴ��ͷ�
	    	system("pause");//��ͣ���û����
	    	system("cls");
        }
        
        //���ڸ���ʦ¼�������
        for(i0 = 0;i0 < i3;i0++,i33++)
	    {
	        //����һ��GF_questions��С���ڴ�,�õ���ָ�븳��p33,���ⶨ��һ��ָ��GF_questions���͵�ָ��p
		    GF_questions *p33 = (GF_questions *)malloc(sizeof(GF_questions)),*p;
		    
  		    if(p33 == NULL)//���p33�õ���ָ��Ϊ��,�����if���,����˵�������ڴ�ʧ��,���˳�¼�������
		    {
		    	//��ʾ�û�����ʧ�ܵ�ԭ��
		    	printf("||!�������ڴ�ʧ�ܡ�!\n||");
		    	printf("pause");//��ͣ���û������Ϣ
		    	system("cls");
		    	break;
			}
			
			//��p33��next
            p33->next = NULL;
            //����timu.gf_questions��������������,��ʱ���������ͷ,�����Ϊ�������if���
	        if(timu.gf_questions)
	        {
	        	//����һ��ָ��GF_questions���͵�ָ��gf_tail,����gf_tailָ������������ͷ�ڵ�
	        	GF_questions *gf_tail = timu.gf_questions;
	        	//����ѭ��ֱ��gf_tailΪ���һ���ڵ�
	    	    for(;gf_tail->next;gf_tail = gf_tail->next);
	    	    //��ʱ��gf_tail��nextΪ��,���丳Ϊp33
	    	    gf_tail->next = p33;
		    }
		    else//���timu.gf_questions����ͷΪ�������else���
				//��p33��������ͷ�ڵ�
			    timu.gf_questions = p33;
			//��ʾ�û�������������Ŀ
		    printf("||�����������%d���������Ŀ����\n||",i33+1);
    	    while(strcmp(gets(p33->gf_question),"\n") <= 0)
	            printf("||");
		    printf("||�����������%d�������Ĵ𰸡���\n||",i33+1);
		    while(strcmp(gets(p33->gf_answer),"\n") <= 0)
	            printf("||");
		    
		    do
            {
            	//��ʾ�û��������������ֵ
		        printf("||�����������%d�������ķ�ֵ����\n||",i33+1);
		        if(scanf("%f",&p33->gf_score) != 1)
		        {
			        input_again();//��ʾ�û���������
			        continue;//����ѭ��
			    }
			    if(p33->gf_score <= 0)
			    {
			    	printf("||����ķ�ֵӦ�ô���0\n");
					continue;
				}
			    //¼��ķ�ֵ��ȷ���˳�ѭ��
			    break;
			}while(1);
            take_in_line_break();
            
            //����ǰ�������Ӹ����ֵ�õ��µĵ�ǰ����
		    timu.full_mark += p33->gf_score;
		    
		    system("cls");
		    //��ʾ�û���ǰ���������Ϣ(��ӡ��Ŀ)
		    printf("||=========================||\n");
		    printf("||Ŀǰ����%d�������:\n",i33+1);
		    for(p = timu.gf_questions; p ;p = p->next)
		        printf("||��Ŀ��%s\n||�𰸣�%s\n||��ֵ��%f\n||\n",p->gf_question,
				p->gf_answer,p->gf_score);
	    	printf("||Ŀǰ����ֵΪ��%.2f\n",timu.full_mark);
	    	printf("||=========================||\n||");
	    	p33 = p33->next;
	    	free(p33);//�ͷ�p33���ڴ�
	    	system("pause");
	    	system("cls");
        }
        
        //����Ŀ����
	    save_timu(i11,i22,i33);
	    system("cls");
	    //��ӡ��Ŀ���û����¼������Ŀ
	    print_timu(4);
	    //��ʾ�û��Ƿ���Ҫ¼��
	    printf("===============================================================\n");
	    printf("||�����㻹Ҫ����¼����Ŀ��?(��Ҫ������y,�����ַ��򷵻ز˵�)����\n||");
	    ch = getchar();
 	    //����û�ֻ����س��������ѭ��ֱ��������س���Ϊֹ
        while(ch == '\n')
        {
        	printf("||");
		    scanf("%c",&ch);
		    continue;
	    }
    }while(ch == 'y');
	if(i1 < 0 || i2 < 0 || i3 < 0)
	{
		printf("||�˳��ɹ�\n||");
		system("pause");
		system("cls");
	    return;
	}
	if(i1 == 0 && i2 == 0 && i3 == 0)
	{
		printf("||�����������������0,���Է���\n||");
		system("pause");
		system("cls");
		return;
	}
    //¼������Ŀ֮�����ʼ������ѧ���ķ����Ϳ���״̬
    initialize_grade();
    //����ѧ����Ϣ
    save_id_studentinfo();
    //����¼��֮�����Ŀ���ļ���
    save_timu(i11,i22,i33);
    //����ǰ��Ŀ�����е���Ŀɾ��
    delete_timu();
	tea_save_stu(1);
	system("cls");
}

//��ʦ��ѧ���ɼ��Ϳ���״̬��ʼ���ɼ�Ϊ0
void initialize_grade(void)
{
	//����һ��ָ��stu���͵�ָ��p,����pָ��ǰѧ������ı�ͷ
	stu *p = stu_list;
	
	//��for����������
	for(;p;p = p->next)
	{
		//������ѧ���ĳɼ��Ϳ���״̬����Ϊ0
		p->Stu.grade = 0;
		p->Stu.examination_status = 0;
	}
	//��ʾ�û���ʼ���ɹ�
	printf("||������ʼ���ɼ��ɹ�!����\n");
}

//�������ԵĲ˵�
//post_exam_menu�Ƿ���һ���������͵ĺ���
//�βηֱ�Ϊ�ж���,ѡ����,��������Ŀ��(���Ҫ����¼������Ϊ0)������ָ��
//���صĺ���ֵ�����ж��û��Ƿ�¼�뿼����Ŀ
//�������1��˵��Ҫ����¼���������¼����Ŀ;�����˳��������Թ���,���ؽ�ʦ�˵�
int post_exam_menu(int *i11,int *i22,int *i33)
{
	//choice����ѡ����
	char choice;
	
	//2�����ʦ���,read_timu_file���������ȡ��Ŀ����
	//�����������ֵ��Ϊ0�����if���(��ʱ����ֵΪ1,˵���п�����Ŀ),��������if���
	if(read_timu_file(2))
	{
		system("cls");
		
		//��ֻ���ķ�ʽ����Ϊ"timu(clear)"���ļ�
		FILE *fpr = fopen("timu(clear).txt","r");
		//�ֱ��ж��⡢ѡ�������������Ŀ������i11,i22,i33
	    fscanf(fpr,"%d,%d,%d",i11,i22,i33);
	    fclose(fpr);//�ر��ļ�
	    
	    print_timu(4);//��ӡ��Ŀ
	    system("pause");//��ͣ���û������Ϣ
	    system("cls");
	    
		do
		{
			system("cls");
			//��ʾ�û�ѡ����
	        printf("||======================================||\n");
		    printf("||��ǰ�Ѿ�¼����Ŀ����������������²���||\n");
		    printf("||======================================||\n");
		    printf("||1.����¼��\t\t\t\t||\n");
		    printf("||2.����¼��\t\t\t\t||\n");
		    printf("||3.�˳��ù��ܷ��ز˵�\t\t\t||\n");
		    printf("||======================================||\n||");
		    
		    //�û�����ѡ��
			scanf("%c",&choice);
            take_in_line_break();
            
		    //����û�ֻ����س��������ѭ��ֱ��������س���Ϊֹ
            while(choice == '\n')
            {
		        printf("||");
		        scanf("%c",&choice);
		        continue;
	        }
	        
	        //�������Ĺ��ܲ�Ϊ1��2��3�����if���
	        if(choice != '1' && choice != '2' && choice != '3')
	        {
	        	//��ʾ�û��������
			    printf("||��������������������\n");
			    printf("||�������,����������||\n");
			    printf("||��������������������\n||");
			    system("pause");
			}
		//����û����벻Ϊ1��2��3�����ѭ��
        }while(choice != '1' && choice != '2' && choice != '3');

		switch (choice)
		{
			case '1':
				//��ʾ�û���ʼ¼��
				printf("||������ʼ����¼��.....����\n||");
				system("pause");//��ͣ���û������Ϣ
				return 1;
			case '2':
				delete_timu();//ɾ����Ŀ(���Ҫ����¼���Ҫ����ǰ��Ŀ�������ɾ��)
				*i11 = *i22 = *i33 = 0;//����Ŀ����Ϊ0
                //��ʾ�û���ʼ����¼��
				printf("||������ʼ����¼��.....����\n||");
				system("pause");//��ͣ���û������Ϣ
				return 1;
				break;
			case '3':
				printf("||�����˳��ɹ�����\n||");
				system("pause");
				system("cls");
				delete_timu();
				return 0;
		}
	}
	else//���read_timu_file(2)���ص�ֵ��Ϊ0�����else���
	{
		//��ʾ�û���δ¼����Ŀ
	    printf("||��������������������������������||\n");
		printf("||������δ��¼����Ŀ,���Խ���¼�� ||\n");
		printf("||��������������������������������||\n");
		system("pause");//��ͣ���û������Ϣ
		return 1;
	}
	
	system("cls");
}

//��������Ŀ
void save_timu(int i11,int i22,int i33)
{
	//���ļ���Ϊ"timu(clear)"��"timu"���ļ�,�������ص�ָ��ֱ𸳸�fpw1��fpw2
	FILE *fpw1 = fopen("timu(clear).txt","w");
	FILE *fpw2 = fopen("timu.txt","w");
	
	//����ָ��TF_questions���͵�ָ��p1,����p1ָ��timu.tf_questions�����ͷ(p2��p3ͬ��)
	TF_questions *p1 = timu.tf_questions;
	Choice_questions *p2 = timu.choice_questions;
	GF_questions *p3 = timu.gf_questions;
	int count;//count������������Ŀ��ӡ���ļ���
	
	//���fpw1��fpw2Ϊ�������if���(˵�����ļ�ʧ��)
	if( fpw1 == NULL || fpw2 ==NULL)
	{
		//��ʾ�û�����ԭ��,���˳�
		printf("!������ʧ�ܡ�!\n");
		system("pause");
		return;
	}
	
	//����Ŀ���ж��⡢ѡ����������ֱ��ӡ��"timu(clear)"�и�ʽΪx,y,z(�س�)
	fprintf(fpw1,"%d,%d,%d\n",i11,i22,i33);
	//ѭ������Ŀ�����¸�ʽ���뵽�ļ�
	//�����ж�����Ŀ:This is an egg ��:Y ��ֵ2.000000
	//�����뵽�ļ��ĸ�ʽΪThis is an egg.#Y#2.000000(�����ж���ͬ��)
	for(p1 = timu.tf_questions; p1 ;p1 = p1->next)
	    fprintf(fpw1,"%s#%s#%f\n",p1->tf_question,p1->tf_answer,p1->tf_score);
    //ѭ������Ŀ�����¸�ʽ���뵽�ļ�
	//�����ж�����Ŀ:What color does Gogo like?
	//          ѡ��:A.red    B.blue    C.yellow    D.green    ��:A ��ֵ2.000000
	//�����뵽�ļ��ĸ�ʽΪWhat color does Gogo like?#red#blue#yellow#green#A 2.000000(����ѡ����ͬ��)
	for(p2 = timu.choice_questions; p2 ;p2 = p2->next)
	    fprintf(fpw1,"%s#%s#%s#%s#%s#%s %f\n",p2->choice_question,p2->option.option_a,p2->option.option_b,p2->option.option_c,p2->option.option_d,p2->cq_answer,p2->cq_score);
	//ѭ������Ŀ�����¸�ʽ���뵽�ļ�
	//�����ж�����Ŀ:I like ___. ��:study ��ֵ2.000000
	//�����뵽�ļ��ĸ�ʽΪI like ___.#study#2.000000(���������ͬ��)
	for(p3 = timu.gf_questions; p3 ;p3 = p3->next)
	    fprintf(fpw1,"%s#%s#%f\n",p3->gf_question,p3->gf_answer,p3->gf_score);
    //���þ�������뵽�ļ�
	fprintf(fpw1,"%f\n",timu.full_mark);
	fclose(fpw1);//�ر��ļ�
	//��ӡ����Ϊ"timu"���ı��ļ���
	//����Ϊ��ʽ
//  ��Ŀ����:
//  һ���ж���
//  1.This is an egg.
//  ��:Y    ��ֵ:2.000000
//
//  2.This is my dad.
//  ��:Y    ��ֵ:2.000000
//
//  ����ѡ����
//  1.What color does Gogo like?
//  ѡ��:A:red   B:blue   C:yellow   D:green
//  ��:A2    ��ֵ:2.000000
//
//  2.This does Gogo doing in this pA
//  ѡ��:A:reading   B:drawing   C:writing   D:runing
//  ��:Ao    ��ֵ:3.000000
//
//  ���������
//  2.Gogo don't like ___?
//  ��:sleeping    ��ֵ:2.000000
//
//  3.I like ___.
//  ��:study    ��ֵ:2.000000
//
//  Ŀǰ����ֵΪ��17.000000
//  ����8����Ŀ
	fprintf(fpw2,"��Ŀ����:\n");
	fprintf(fpw2,"һ���ж���\n");
	//��p1ָ��timu.tf_questionsͷ�ڵ�,����ѭ�����뵽�ļ���
	for(p1 = timu.tf_questions,count = 0;p1;p1 = p1->next,count++)
		fprintf(fpw2,"%d.%s\n��:%s    ��ֵ:%f\n\n",count+1,p1->tf_question,p1->tf_answer,p1->tf_score);
	fprintf(fpw2,"����ѡ����\n");
	//��p2ָ��timu.choice_questionsͷ�ڵ�,����ѭ�����뵽�ļ���
	for(p2 = timu.choice_questions,count = 0;p2;p2 = p2->next,count++)
        fprintf(fpw2,"%d.%s\nѡ��:A:%s   B:%s   C:%s   D:%s\n��:%s    ��ֵ:%f\n\n",count+1,
		p2->choice_question,p2->option.option_a,p2->option.option_b,p2->option.option_c,
		p2->option.option_d,p2->cq_answer,p2->cq_score);
	//��p3ָ��timu.gf_questionsͷ�ڵ�,����ѭ�����뵽�ļ���
	fprintf(fpw2,"���������\n");
	for(p3 = timu.gf_questions,count = 0;p3;p3 = p3->next,count++)
		fprintf(fpw2,"%d.%s\n��:%s    ��ֵ:%f\n\n",count+1,p3->gf_question,p3->gf_answer,p3->gf_score);
	//���ļ��������ֺ���Ŀ��
    fprintf(fpw2,"Ŀǰ����ֵΪ��%f\n����%d����Ŀ\n",timu.full_mark,i11+i22+i33);
	fclose(fpw2);//�ر��ļ�
	//��ʾ�û�¼����Ŀ�ɹ�
	printf("||¼��ɹ�!");
	system("pause");//��ͣ���û������Ϣ
}

//��ʦ¼��ѧ����Ϣ
void input_studentinfo(void)
{
	system("cls");
    //ch�����ж��û��Ƿ�Ҫ¼��,input_nameԭ�����û�����Ҫ¼���ѧ������
	char ch,input_name[NAME_LEN];
	//input_id�������û�����Ҫ¼���ѧ��ѧ��,class_number������¼���,i������¼���λ��
	int input_id = 0,class_number = 0,i = 0,id_flag = 0;
	stu *find = stu_list;//����һ��stu���͵�ָ��ָ��ѧ����Ϣ������,���ڲ���¼���ѧ���Ƿ����ظ�
	
	do
	{
		do
		{
	        system("cls");
	        id_flag = 0;
		    //��ʾ�û�����Ҫ¼��ѧ����ѧ��
	        printf("||������������Ҫ¼��ѧ����ѧ��(��Χ1000~9999)(����0�˳�)����\n");
	        printf("||�������������С������������¼�롪��\n||");
	        if(scanf("%d",&input_id) != 1)
	        {
		        take_in_line_break();
	            //��ʾ�û�����ԭ��
			    printf("||!��Ҫ��������λ������!\n||");
			    system("pause");
				system("cls");
	            continue;
	        }
	        take_in_line_break();
	        //����û�����0���˳�ѭ��
	        if(!input_id)break;
	        //����û�����
	        else if(input_id > 9999 ||input_id <1000)
	        {
	     	    //��ʾ�û�������λ����
	     	    printf("||!��Ҫ��������λ������!\n||");
	     	    system("pause");
			    system("cls");
	            continue;
		    }
  		    //��������,�鿴ѧ���Ƿ����ظ�
            for(find = stu_list;find;find = find->next)
            {
            	//���ѧ���ظ�����ʾ�û���������
        	    if(find->Stu.id == input_id)
        	    {
        	    	id_flag = 1;
				    printf("||�����ѧ�ź͵�ǰѧ�������е�ĳ��ѧ��ѧ����ͬ,����������\n||");
			        system("pause");
			        system("cls");
	            }
	            if(id_flag)break;
		    }
		    if(id_flag)continue;
		    break;
		}while(1);
        //����0�˳�
        if(return_by_zero(input_id))return;
        system("cls");
        //��ʾ�û�����Ҫ¼��ѧ��������
	    printf("||������������Ҫ¼��ѧ��������(����0�˳�)����\n||");
	    scanf("%s",input_name);
		take_in_line_break();
        //�������"0"�˳�
        if(char_return_by_zero(input_name))return;
	    stu *p = (stu *)malloc(sizeof(stu));
	    //����ڴ����ʧ�������if���
	    if(p == NULL)
	    {
	    	//��ʾ�û�����ԭ��
	    	printf("||�����ڴ�ʧ��\n");
	    	system("pause");//��ͣ���û����
	    	system("cls");
	    	return;
		}
		//��p��next��Ϊ��
	    p->next = NULL;
	    p->Stu.id = input_id;
	    strcpy(p->Stu.name,input_name);
	    //���ѧ����Ϣ�����ͷ��Ϊ�������if���
	    if(stu_list)
	    {
	    	//��ͷ�巨����
	    	//����ǰhead->node1->node2->node3->NULL
	    	//�����head->p->node1->node2->node3->NULL
	    	//��p��nextָ���ͷ�ٽ�pѧ����Ϣ�ṹ�帳����ͷ,��ʱ��ͷΪ�²���Ľṹ��
	    	p->next = stu_list;
	    	stu_list = p;
		}
		//���ѧ����Ϣ�����ͷΪ�������else���
		else
		    stu_list = p;
        do
        {
        	system("cls");
            //��ʾ�û�Ҫ¼��ѧ���İ༶
            printf("||������������Ҫ¼��ѧ���İ༶(Ҫ�������14����ֻ����14����)\n||(ֻ������һ����λ��)(����0�˳�)����\n");
            printf("||�����������С����ȡ��������\n||");
            if(scanf("%d",&class_number) != 1)
            {
            	take_in_line_break();
            	printf("||Ҫ����������\n||");
            	system("pause");
            	system("cls");
            	continue;
		    }
		    take_in_line_break();
		    if(class_number > 99 ||class_number < 0)
		    {
		    	printf("||Ҫ������һ����λ��\n||");
		    	system("pause");
		    	system("cls");
		    	continue;
			}
			break;
        }while(1);
		if(return_by_zero(class_number))return;
		if(class_number > 9 )
		{
			p->Stu.class[0] = class_number/10+'0';
			p->Stu.class[1] = class_number%10+'0';
			p->Stu.class[2] = '\0';
		}
		else
		{
			p->Stu.class[0] = class_number+'0';
			p->Stu.class[1] = '\0';
		}
		system("cls");
        //��ʾ�û�����Ҫ¼��ѧ����רҵ
        printf("||������������Ҫ¼��ѧ����רҵ(����0�˳�)����\n||");
        scanf("%s",p->Stu.majority);
        take_in_line_break();
        //�������"0"�˳�
	    if(char_return_by_zero(p->Stu.majority))return;
        //����ѧ�����븳Ϊ��ʼ����
	    p->Stu.password = ORIGINAL_PASSWROD;
	    //����ѧ���ɼ��Ϳ���״̬��ʼ��Ϊ0
	    p->Stu.grade = 0;
	    p->Stu.examination_status = 0;
	    //��ʾ�û��Ƿ���Ҫ����
 	    save_id_studentinfo();
	    tea_save_stu(2);
		printf("||����¼��ɹ�\n||�����㻹��Ҫ¼����?(��Ҫ������y,�����ַ��򷵻ز˵�)����\n");
	    printf("||===========================================================||\n||");
 	    //����û�ֻ����س��������ѭ��ֱ��������س���Ϊֹ
 	    scanf("%c",&ch);
        while(ch == '\n')
        {
        	printf("||");
		    scanf("%c",&ch);
		    continue;
	    }
	}while(ch == 'y');
	take_in_line_break();
	system("cls");
}

//����ַ���Ϊ"0"�򷵻�1,���򷵻�0,�����ж��Ƿ�Ϊ0,��������˳���ǰ����
int char_return_by_zero(char flag[])
{
	//����ַ���Ϊ"0"�������䷵��1
	if(strcmp(flag,"0") == 0)
    {
		printf("||�˳��ɹ�\n||");
        system("pause");
        system("cls");
        return 1;
	}
	//���򷵻�0
	return 0;
}

//ѧ������ʦ�鿴ȫ��ѧ���ɼ�
void print_studentinfo(void)
{
	system("cls");
	
	stu *p = stu_list;//����ָ��stu���͵�ָ��pָ��ѧ����Ϣ�����ͷ
	int count = 0,i = 0;//i���ڽ�������ѧ���������Ϣ���浽һ��������,count����ͳ����������ĵ�ѧ������
	
	for(p = stu_list;p;p=p->next,count++);//��countͳ��ѧ������
	
	Student ranking[count];//����ṹ���������ڴ���ѧ�������Ϣ
	
	do
	{
		//�鿴�ɼ��Ĳ˵�
		system("cls");
		//��ö�����ͽ�id,grade,go_back�ֱ�Ϊ1��2��3
	    enum Choice{id = 1,grade,custom,go_back}choice;
	
	    for(p = stu_list,i=0;p && i<count;i++,p = p->next)
		    ranking[i] = p->Stu;
		printf("||==============================||\n");
		printf("||��������Ҫ��ѧ���ɼ�������ʽ||\n");
 		printf("||==============================||\n");
 		printf("||1.ѧ������\t\t\t||\n");
 		printf("||2.�ɼ�����\t\t\t||\n");
 		printf("||3.�Զ��������˳������\t||\n");
 		printf("||4.���ز˵�\t\t\t||\n");
 		printf("||==============================||\n||");
  		if(scanf("%d",&choice) != 1)//���choice�����������������if���
		{
			//��ʾ�û�����ԭ��
			printf("||Ҫ����������\n");
			input_again();//��ʾ�û���������
			continue;//����ѭ��
		}
        take_in_line_break();
        
	    switch(choice)
	    {
	        case id://ѧ������
                id_rank(&ranking[0],count);
                break;
	        case grade://�ɼ�����
		        grade_rank(&ranking[0],count);
		        break;
			case custom://�Զ�������β���
				Custom_statistics(&ranking[0],count);
				break;
	  	    case go_back://���ز˵�
			    system("cls");
			    break;
	        default ://��������
			    printf("!���������!\n");
		        break;
        }
        if(choice == go_back)break;
    }while(1);
	system("cls");
}

//�Զ�������β���
void Custom_statistics(Student *ranking,int count)
{
	//upper_limit��������,lower_limit��������
	float upper_limit = 0,lower_limit = 0;
	//j����ѭ�����ѧ���ɼ�,i��������
	int j = 0,gap = count,i = 0;
	
	do
	{
    	do
    	{
	        system("cls");
	        printf("||��������ҲҪͳ�Ƶķ�����(����С��0�����˳�)\n");
	        printf("||����:");
	        if(scanf("%f",&lower_limit) != 1)
	        {
		    	take_in_line_break();
		    	//��ʾ�û�����ԭ��
		    	printf("||Ҫ����������\n||");
		    	system("pause");
		    	system("cls");
		     	continue;//����ѭ��
	        }
	        take_in_line_break();
	    	break;
    	}while(1);
        if(lower_limit < 0)break;
        
    	do
    	{
	        system("cls");
	        printf("||��������ҲҪͳ�Ƶķ�����(����С��0�����˳��˳�)\n");
	        printf("||����:%.0f\n",lower_limit);
	        printf("||����:");
	        if(scanf("%f",&upper_limit) != 1)
	        {
	        	take_in_line_break();
		    	//��ʾ�û�����ԭ��
		    	printf("||Ҫ����������\n");
		    	input_again();//��ʾ�û���������
		    	continue;//����ѭ��
	        }
	        take_in_line_break();
	    	break;
	    }while(1);
	    if(upper_limit < 0)break;
	    
	    if(upper_limit < lower_limit)
		{
			printf("||���������С������,�����������������\n||");
			system("pause");
		    continue;
		}
	    break;
	}while(1);
	if(upper_limit < 0 || lower_limit < 0)return;
	
	printf("||����ɹ�\n||");
	system("pause");
	system("cls");

	while (gap>1)
	{
		//ÿ�ζ�gap�۰����
		gap = gap / 2;
		//��������
		for (i = 0; i < count - gap; ++i)
		{
			int end = i;
			Student tem = ranking[end + gap];
			while (end >= 0)
			{
				if (tem.grade > ranking[end].grade)
				{
					ranking[end + gap] = ranking[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			ranking[end + gap] = tem;
		}
	}
	printf("||======================================================================||\n");
	printf("||����%.1f~~%.1f�ֶε�ѧ������:\t\t\t\t\t\t||\n",lower_limit,upper_limit);
	printf("||ѧ��============����============�༶============רҵ============����==||\n");
	for(j = 0;j < count;j++)
		if(ranking[j].grade >= lower_limit && ranking[j].grade <= upper_limit)
            printf("||%d\t\t%s\t\t%s\t\t%s\t\t  %.1f\t||\n",ranking[j].id,ranking[j].name,ranking[j].class,ranking[j].majority,ranking[j].grade);
	printf("||======================================================================||\n||");
	system("pause");
	system("cls");
}

//ѧ������
//id_rank�Ǹ��޷���ֵ�ĺ���,�β�ranking��Stuent���͵�ָ��,ָ��һ������������׵�ַ,�ø������ѧ������
//count���������ͱ�������ͳ��������ѧ��������
void id_rank(Student *ranking,int count)
{
	system("cls");
		
	//��ö�����ͽ�idorder,reverse_order,go_back�ֱ�Ϊ1��2��3
	enum Choice{order = 1,reverse_order,go_back}choice;
	do
	{
     	//��ʾ�û�������Ϣ
    	printf("||==============================||\n");
	    printf("||��Ҫѧ��˳����������������||\n");
    	printf("||==============================||\n");
	    printf("||1.ѧ��˳������\t\t||\n");
	    printf("||2.ѧ����������\t\t||\n");
	    printf("||3.����������\t\t||\n");
	    printf("||==============================||\n||");
  	    if(scanf("%d",&choice) != 1)//���choice�����������������if���
	    {
		    //��ʾ�û�����ԭ��
		    printf("||Ҫ����������\n");
		    input_again();//��ʾ�û���������
		    continue;//����ѭ��
	    }
	
        take_in_line_break();
        system("cls");
	    switch(choice)
    	{
	        case order:
	        	//���˳����������id_order_rank����,��������Ԫ�ص�ַ��ѧ��������Ϊʵ�δ�������
                id_order_rank(&ranking[0],count);
                break;
	        case reverse_order:
	        	//���������������id_reverse_order_rank����,��������Ԫ�ص�ַ��ѧ��������Ϊʵ�δ�������
		        id_reverse_order_rank(&ranking[0],count);
	    	    break;
	     	case go_back:
	  	    	//����
		    	system("cls");
		    	return;
	        default ://��������
		    	printf("||�������\n||");
		    	system("pause");
		    	system("cls");
		        break;
        }
        if(choice == go_back)break;
	}while(1);
}

//ϣ�������Ƚ��������н���Ԥ����ʹ�������нӽ�����Ȼ���ٶԸ����н���һ�β�������
//˳��ѧ������
//id_order_rank�ǲ�������ֵ�ĺ���,rankingΪStudent���͵�ָ��,��ָ��ѧ����Ϣ����,count���������͵ı�������ͳ��ѧ������
void id_order_rank(Student *ranking,int count)
{
    //gap������������Ŀ��,i����ѭ��
	int gap = count,i = 0;
	
	while (gap>1)
	{
		//ÿ�ζ�gap�۰����
		gap = gap / 2;
		//��������
		for (i = 0; i < count - gap; ++i)
		{
			int end = i;
			Student tem = ranking[end + gap];
			
			while (end >= 0)
			{
				if (tem.id < ranking[end].id)
				{
					ranking[end + gap] = ranking[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			ranking[end + gap] = tem;
		}
	}
	printf("||ѧ��============����============�༶============רҵ============����==||\n");
	for(i = 0;i < count; i++)
		printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.1f\t||\n",ranking[i].id,ranking[i].name,ranking[i].class,ranking[i].majority,ranking[i].grade);
	print_wholescore_and_avgscore();
	printf("||����%dλѧ��\n",count);
	system("pause");
	system("cls");
}

//����ѧ������
void id_reverse_order_rank(Student *ranking,int count)
{
	int gap = count,i;
	
	while (gap>1)
	{
		//ÿ�ζ�gap�۰����
		gap = gap / 2;
		//��������
		for (i = 0; i < count - gap; ++i)
		{
			int end = i;
			Student tem = ranking[end + gap];
			while (end >= 0)
			{
				if (tem.id > ranking[end].id)
				{
					ranking[end + gap] = ranking[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			ranking[end + gap] = tem;
		}
	}
	printf("||ѧ��============����============�༶============רҵ============����==||\n");
	for(i = 0;i < count; i++)
		printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.1f\t||\n",ranking[i].id,ranking[i].name,ranking[i].class,ranking[i].majority,ranking[i].grade);
	print_wholescore_and_avgscore();
	printf("||����%dλѧ��\n",count);
	system("pause");
	system("cls");
}

//�ɼ�����
void grade_rank(Student *ranking,int count)
{
	system("cls");
	
	enum Choice{order = 1,reverse_order,go_back}choice;
	do
	{
	    printf("||==============================||\n");
	    printf("||��Ҫ�ɼ�˳����������������? ||\n");
	    printf("||==============================||\n");
	    printf("||1.�ɼ�˳������\t\t||\n");
	    printf("||2.�ɼ���������\t\t||\n");
	    printf("||3.����������\t\t||\n");
	    printf("||==============================||\n||");
 		if(scanf("%d",&choice) != 1)//���choice�����������������if���
		{
			//��ʾ�û�����ԭ��
			printf("||Ҫ����������\n");
			input_again();//��ʾ�û���������
			continue;//����ѭ��
		}
		break;
	}while(1);
    take_in_line_break();
    system("cls");
	switch(choice)
	{
	    case order://���ɼ�˳�����
            grade_order_rank(&ranking[0],count);
            break;
	    case reverse_order://���ɼ��������
		    grade_reverse_order_rank(&ranking[0],count);
		    break;
	  	case go_back://����������
			system("cls");
			return;
	    default ://��������
			printf("!���������!\n");
		    break;
    }
}

//˳�򰴳ɼ�����
void grade_order_rank(Student *ranking,int count)
{
	int gap = count,i;
	
	while (gap>1)
	{
		//ÿ�ζ�gap�۰����
		gap = gap / 2;
		//��������
		for (i = 0; i < count - gap; ++i)
		{
			int end = i;
			Student tem = ranking[end + gap];
			while (end >= 0)
			{
				if (tem.grade > ranking[end].grade)
				{
					ranking[end + gap] = ranking[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			ranking[end + gap] = tem;
		}
	}
	printf("||ѧ��============����============�༶============רҵ============����==||\n");
	for(i = 0;i < count; i++)
		printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.1f\t||\n",
		ranking[i].id,ranking[i].name,ranking[i].class,ranking[i].majority,ranking[i].grade);
	print_wholescore_and_avgscore();
	printf("||����%dλѧ��\n",count);
	system("pause");
	system("cls");
}

//���򰴳ɼ�����
void grade_reverse_order_rank(Student *ranking,int count)
{
	int gap = count,i;
	
	while (gap>1)
	{
		//ÿ�ζ�gap�۰����
		gap = gap / 2;
		//��������
		for (i = 0; i < count - gap; ++i)
		{
			int end = i;
			Student tem = ranking[end + gap];
			while (end >= 0)
			{
				if (tem.grade < ranking[end].grade)
				{
					ranking[end + gap] = ranking[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			ranking[end + gap] = tem;
		}
	}
	printf("||ѧ��============����============�༶============רҵ============����==||\n");
	for(i = 0;i < count; i++)
        printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.1f\t||\n",ranking[i].id,ranking[i].name,ranking[i].class,ranking[i].majority,ranking[i].grade);
    print_wholescore_and_avgscore();
	printf("||����%dλѧ��\n",count);
	system("pause");
	system("cls");
}

//��ʦ�鿴ȫ���ֺܷ�ƽ����
void print_wholescore_and_avgscore(void)
{
	//����һ��stu���͵�ָ��pָ��stu_list(��ǰѧ����Ϣ��ͷ�ڵ�)
	stu *p = stu_list;
	int count = 0;//count������ѭ��������ͳ��ѧ������
	float avg = 0,wholesccore = 0;//avg����ȫ��ƽ����,wholesccore����ȫ���ܷ�

    //��forѭ������༶�ܷ��Լ�ѧ������
	for(count = 0,wholesccore = 0;p;p = p->next,count++)
		wholesccore += p->Stu.grade;
	if(count)
	    avg = wholesccore/count;
	else avg = 0;
	    //��ʾ�û��༶�÷���Ϣ
	    printf("||�����༶�ܷ�:%.1f����\t\t\t\t\t\t\t||\n||�����༶ƽ����:%.2f����\t\t\t\t\t\t||\n",wholesccore,avg);
	    printf("||======================================================================||\n");
}

//��ʦ�鿴����ѧ����Ϣ
void seek_studentinfo(void)
{
	
	do
	{
	    system("cls");
	    enum Choice{id = 1,name,go_back}choice;
	    //��ʾ�û��˵�
	    printf("||======================||\n");
		printf("||������Ҫ����ѧ������Ϣ||\n");
		printf("||======================||\n");
		printf("||1.ͨ��ѧ�Ų���\t||\n");
		printf("||2.ͨ����������\t||\n");
		printf("||3.���ز˵�\t\t||\n");
	    printf("||======================||\n||");
  	    if(scanf("%d",&choice) != 1)//���choice�����������������if���
	    {
		    //��ʾ�û�����ԭ��
		    printf("||Ҫ����������\n");
		    input_again();//��ʾ�û���������
		    continue;//����ѭ��
	    }
        take_in_line_break();
        
	    switch(choice)
	    {
	        case id://ѧ�Ų���
                seek_by_id();
                break;
	        case name://��������
		        seek_by_name();
		        break;
	  	    case go_back://���ز˵�
				system("cls");
				return;
	        default ://��������
				printf("!���������!\n");
		        break;
     	}
     	if(choice == go_back)break;
     }while(1);
	system("cls");
}

//ͨ��ѧ�Ų���ѧ��
void seek_by_id(void)
{
	system("cls");
	int stu_id = 0;//�������ͱ���,��Ҫ�û���ֵ���ñ���
	stu *p = stu_list;//����stu���͵�ָ��ָ��stu_list(ѧ����Ϣ����ı�ͷ)
	
	do
	{
	    printf("||=====================================||\n");
	    printf("||��������Ҫ���ҵ�ѧ��ѧ��(����0�˳�)\n||");
  		if(scanf("%d",&stu_id) != 1)//���stu_id�����������������if���
		{
			//��ʾ�û�����ԭ��
			printf("||Ҫ����������\n");
			input_again();//��ʾ�û���������
			continue;//����ѭ��
		}
		break;
	}while(1);
	//�������Ϊ0���˳�ѧ����¼����
	if(return_by_zero(stu_id))return;
	if(stu_list == NULL)
	{
        printf("||�����ڸ�ѧ��\n||");
        system("pause");
        system("cls");
        return;
	}
	
    take_in_line_break();
	system("cls");
	for(p = stu_list;p;p = p->next)
	{
		//�����������ѧ����ѧ�ź��û������ѧ��ƥ������������(˵���ҵ���ѧ��)
		if(p->Stu.id == stu_id)
			{
				//��ʾ��ѧ������Ϣ
				printf("||ѧ��============����============�༶============רҵ============����============����==||\n");
				printf("||%d\t\t%s\t\t%s\t\t%s\t\t%d\t\t%.2f\t||\n||",p->Stu.id,p->Stu.name,p->Stu.class,
				p->Stu.majority,p->Stu.password,p->Stu.grade);
				system("pause");
	            break;
			}
        //�����������ĩβ��ƥ�䲻��
		if(p->Stu.id != stu_id && p->next == NULL)
		{
		    printf("||!��δ���ҵ���ѧ����!\n||");
		    system("pause");
		    system("cls");
		}
	}
}

//ͨ����������ѧ��
void seek_by_name(void)
{
	system("cls");
	char stu_name[10];
	stu *p=stu_list;
	
	printf("||=========================================||\n");
	printf("||��������Ҫ���ҵ�ѧ������(ֻ����һ��0�˳�)||\n||");
	scanf("%s",stu_name);
    take_in_line_break();
    //�������"0"�˳�
    if(char_return_by_zero(stu_name))return;
	if(stu_list == NULL)
	{
        printf("||�����ڸ�ѧ��\n||");
        system("pause");
        system("cls");
        return;
	}
	
	system("cls");
	for(;p;p=p->next)
	{
		if(strcmp(p->Stu.name,stu_name) == 0)
			{
				printf("||ѧ��===========����===========�༶=============רҵ===========����=============����===||\n");
				printf("||%d\t\t%s\t\t%s\t\t%s\t\t%d\t\t%.2f\t||\n||",p->Stu.id,p->Stu.name,p->Stu.class,
				p->Stu.majority,p->Stu.password,p->Stu.grade);
				system("pause");
	            break;
			}
		if(p->next == NULL && strcmp(p->Stu.name,stu_name) != 0)
		{
		    printf("||!��δ���ҵ���ѧ����!\n||");
		    system("pause");
		    system("cls");
		}
	}
}

//��ʦ�޸�ѧ����Ϣ
void modify_studentinfo(void)
{
	enum Choice{id = 1,name,go_back}choice;
	
	do
	{
	    system("cls");
		//��ʾ�û�����
		printf("||==============================||\n");
	    printf("||��������Ҫ�޸ĵ�ѧ����Ϣ      ||\n");
	    printf("||==============================||\n");
	    printf("||1.ͨ��ѧ���޸�\t\t||\n");
	    printf("||2.ͨ�������޸�\t\t||\n");
	    printf("||3.���ز˵�\t\t\t||\n");
	    printf("||==============================||\n||");
  	    if(scanf("%d",&choice) != 1)//���choice�����������������if���
	    {
		    //��ʾ�û�����ԭ��
		    printf("||Ҫ����������\n");
		    input_again();//��ʾ�û���������
		    continue;//����ѭ��
	    }
        take_in_line_break();
        
	    switch(choice)
	    {
	        case id://ѧ�Ų���
                modify_by_id();
                break;
	        case name://��������
		        modify_by_name();
		        break;
	  	    case go_back://���ز˵�
				system("cls");
				break;
	        default ://��������
				printf("||!���������!\n||");
				system("pause");
		        break;
     	}
        tea_save_stu(4);
        save_id_studentinfo();
        if(choice == go_back)break;
    }while(1);
	system("cls");
}

//ͨ��ѧ���޸�ѧ����Ϣ
void modify_by_id(void)
{
	system("cls");
	//����һ�����ͱ���stu_id,id_flag�ж������޸ĵ�ѧ���Ƿ����ظ�
	//stu_flag�ж��Ƿ����ҵ�ѧ��,modify_id����Ҫ�޸ĵ�ѧ��,class_number����༶��
	int stu_id = 0,id_flag = 0,stu_flag = 0,modify_id = 0,class_number = 0;
    //����һ��stu���͵�ָ��ָ��ѧ����Ϣ�����ͷ�ڵ�stu_list,���ڱ�������
	stu *p = stu_list;
	char modify_mojority[MAJORITY];

    do
	{
		//��ʾ�û�������Ϣ
	    printf("||===================================||\n");
	    printf("||��������Ҫ�޸ĵ�ѧ��ѧ��(����0�˳�)||\n||");
  	    if(scanf("%d",&stu_id) != 1)//���stu_id�����������������if���
	    {
		    //��ʾ�û�����ԭ��
		    printf("||Ҫ����������\n");
		    input_again();//��ʾ�û���������
		    continue;//����ѭ��
	    }
	    break;
	}while(1);
    take_in_line_break();
    //�������Ϊ0���˳�ѧ����¼����
	if(return_by_zero(stu_id))return;
	
	if(stu_list == NULL)
	{
        printf("||�����ڸ�ѧ��\n||");
        system("pause");
        system("cls");
        return;
	}
	
	system("cls");
	stu_flag = 0;
	//��ѧ�����������Ѱ,Ѱ�Ҹ�ѧ��
	for(p = stu_list;p;p = p->next)
	{
		//����û������ѧ��ѧ�ź������ж�Ӧ��ѧ��ѧ��ƥ�������if���
		if(p->Stu.id == stu_id)
			{
				//��ʾ��ѧ������Ϣ
				printf("||ѧ��============����============�༶============רҵ============����=======||\n");
				printf("||%d\t\t%s\t\t%s\t\t %s\t\t  %.2f\t     ||\n",p->Stu.id,p->Stu.name,p->Stu.class,p->Stu.majority,p->Stu.grade);
				stu_flag = 1;
				break;
			}
        //��δ��ƥ�����Լ�������ĩβ�����if���
		if(p->Stu.id != stu_id && p->next == NULL)
            {
			    //��ʾδ���ҵ���ѧ��
		        printf("||!��δ���ҵ���ѧ����!\n||");
		        system("pause");
		        system("cls");
		    }
	}
	//���δ�ҵ�ѧ���򷵻�
	if(!stu_flag)return;
	
	printf("||===========================================================================||\n");
	printf("||���������������ѧ����Ϣ�����޸ġ���\t\t\t\t\t     ||\n||");
	system("pause");
	
	do
	{
	    system("cls");
	    id_flag = 0;
		//��ʾ�û�����Ҫ¼��ѧ����ѧ��
	    printf("||������������Ҫ�޸�ѧ����ѧ��(��Χ1000~9999)(����0�˳�)����\n");
	    printf("||�������������С�������������޸ġ���\n||");
	    if(scanf("%d",&modify_id) != 1)
	    {
		    take_in_line_break();
	        //��ʾ�û�����ԭ��
			printf("||!��Ҫ��������λ������!\n||");
			system("pause");
			system("cls");
	        continue;
	    }
	    take_in_line_break();
	    //����û�����0���˳�ѭ��
	    if(!modify_id)break;
	    //����û�����
	    else if(modify_id > 9999 ||modify_id <1000)
	    {
	     	//��ʾ�û�������λ����
	     	printf("||!��Ҫ��������λ������!\n||");
			system("pause");
			system("cls");
	        continue;
		}
		stu *find = stu_list;
  		//��������,�鿴ѧ���Ƿ����ظ�
        for(find = stu_list;find;find = find->next)
        {
            //���ѧ���ظ�����ʾ�û���������
        	if(find->Stu.id == modify_id && find->Stu.id != stu_id)
        	{
        	    id_flag = 1;
				printf("||�����ѧ�ź͵�ǰѧ�������е�ĳ��ѧ��ѧ����ͬ,����������\n||");
			    system("pause");
			    system("cls");
	        }
	        if(id_flag)break;
		}
		if(id_flag)continue;
		break;
	}while(1);
    //����0�˳�
    if(return_by_zero(modify_id))return;
    p->Stu.id = modify_id;
    
    system("cls");
    do
    {
        system("cls");
        //��ʾ�û�Ҫ¼��ѧ���İ༶
        printf("||������������Ҫ�޸�ѧ���İ༶(Ҫ�������14����ֻ����14����)\n||(ֻ������һ����λ��)(����0�˳�)����\n");
        printf("||�����������С����ȡ��������\n||");
        if(scanf("%d",&class_number) != 1)
        {
            take_in_line_break();
            printf("||Ҫ����������\n||");
            system("pause");
            system("cls");
            continue;
		}
		take_in_line_break();
		if(class_number > 99 ||class_number < 0)
		{
		    printf("||Ҫ������һ����λ��\n||");
		    system("pause");
		    system("cls");
		    continue;
		}
		break;
    }while(1);
	if(return_by_zero(class_number))return;
	if(class_number > 9 )
	{
		p->Stu.class[0] = class_number/10+'0';
		p->Stu.class[1] = class_number%10+'0';
		p->Stu.class[2] = '\0';
	}
	else
	{
		p->Stu.class[0] = class_number+'0';
		p->Stu.class[1] = '\0';
	}
	system("cls");
    //��ʾ�û�����ѧ��רҵ
	printf("||����������ѧ��רҵ����\n||");
	scanf("%s",modify_mojority);
    take_in_line_break();
    //����0�˳�
    if(char_return_by_zero(p->Stu.majority))
    {
		printf("||�˳��ɹ�\n");
		system("pause");
		system("cls");
        return;
	}
    strcpy(p->Stu.majority,modify_mojority);
    printf("||�޸ĳɹ�\n||");
    system("pause");
}

//ͨ�������޸�ѧ����Ϣ
void modify_by_name(void)
{
	system("cls");
	//����һ�����ͱ���stu_id,id_flag�ж������޸ĵ�ѧ���Ƿ����ظ�
	//stu_flag�ж��Ƿ����ҵ�ѧ��,modify_id����Ҫ�޸ĵ�ѧ��,class_number����༶��
	int id_flag = 0,stu_flag = 0,modify_id = 0,class_number = 0;
    //����һ��stu���͵�ָ��ָ��ѧ����Ϣ�����ͷ�ڵ�stu_list,���ڱ�������
	stu *p = stu_list;
	char modify_mojority[MAJORITY],stu_name[NAME_LEN];

	//��ʾ�û�������Ϣ
	printf("||===================================||\n");
	printf("||��������Ҫ�޸ĵ�ѧ������(����0�˳�)||\n||");
  	scanf("%s",stu_name);
    take_in_line_break();
    //�������"0"�˳�
    if(char_return_by_zero(stu_name))return;
    
	if(stu_list == NULL)
	{
        printf("||�����ڸ�ѧ��\n||");
        system("pause");
        system("cls");
        return;
	}
	
	system("cls");
	stu_flag = 0;
	//��ѧ�����������Ѱ,Ѱ�Ҹ�ѧ��
	for(p = stu_list;p;p = p->next)
	{
		//����û������ѧ��ѧ�ź������ж�Ӧ��ѧ��ѧ��ƥ�������if���
		if(strcmp(p->Stu.name,stu_name) == 0)
			{
				//��ʾ��ѧ������Ϣ
				printf("||ѧ��============����============�༶============רҵ============����=======||\n");
				printf("||%d\t\t%s\t\t%s\t\t %s\t\t  %.2f\t     ||\n",p->Stu.id,p->Stu.name,p->Stu.class,p->Stu.majority,p->Stu.grade);
				stu_flag = 1;
				break;
			}
        //��δ��ƥ�����Լ�������ĩβ�����if���
		if(strcmp(p->Stu.name,stu_name) != 0 && p->next == NULL)
            {
			    //��ʾδ���ҵ���ѧ��
		        printf("||!��δ���ҵ���ѧ����!\n||");
		        system("pause");
		        system("cls");
		    }
	}
	//���δ�ҵ�ѧ���򷵻�
	if(!stu_flag)return;

	printf("||===========================================================================||\n");
	printf("||���������������ѧ����Ϣ�����޸ġ���\t\t\t\t\t     ||\n||");
	system("pause");

	do
	{
	    system("cls");
	    id_flag = 0;
		//��ʾ�û�����Ҫ¼��ѧ����ѧ��
	    printf("||������������Ҫ�޸�ѧ����ѧ��(��Χ1000~9999)(����0�˳�)����\n");
	    printf("||�������������С�������������޸ġ���\n||");
	    if(scanf("%d",&modify_id) != 1)
	    {
		    take_in_line_break();
	        //��ʾ�û�����ԭ��
			printf("||!��Ҫ��������λ������!\n||");
			system("pause");
			system("cls");
	        continue;
	    }
	    take_in_line_break();
	    //����û�����0���˳�ѭ��
	    if(!modify_id)break;
	    //����û�����
	    else if(modify_id > 9999 ||modify_id <1000)
	    {
	     	//��ʾ�û�������λ����
	     	printf("||!��Ҫ��������λ������!\n||");
			system("pause");
			system("cls");
	        continue;
		}
		stu *find = stu_list;
  		//��������,�鿴ѧ���Ƿ����ظ�
        for(find = stu_list;find;find = find->next)
        {
            //���ѧ���ظ�����ʾ�û���������
        	if(find->Stu.id == modify_id && find->Stu.id != p->Stu.id)
        	{
        	    id_flag = 1;
				printf("||�����ѧ�ź͵�ǰѧ�������е�ĳ��ѧ��ѧ����ͬ,����������\n||");
			    system("pause");
			    system("cls");
	        }
	        if(id_flag)break;
		}
		if(id_flag)continue;
		break;
	}while(1);
    //����0�˳�
    if(return_by_zero(modify_id))return;
    p->Stu.id = modify_id;

    system("cls");
    do
    {
        system("cls");
        //��ʾ�û�Ҫ¼��ѧ���İ༶
        printf("||������������Ҫ�޸�ѧ���İ༶(Ҫ�������14����ֻ����14����)\n||(ֻ������һ����λ��)(����0�˳�)����\n");
        printf("||�����������С����ȡ��������\n||");
        if(scanf("%d",&class_number) != 1)
        {
            take_in_line_break();
            printf("||Ҫ����������\n||");
            system("pause");
            system("cls");
            continue;
		}
		take_in_line_break();
		if(class_number > 99 ||class_number < 0)
		{
		    printf("||Ҫ������һ����λ��\n||");
		    system("pause");
		    system("cls");
		    continue;
		}
		break;
    }while(1);
	if(return_by_zero(class_number))return;
	if(class_number > 9 )
	{
		p->Stu.class[0] = class_number/10+'0';
		p->Stu.class[1] = class_number%10+'0';
		p->Stu.class[2] = '\0';
	}
	else
	{
		p->Stu.class[0] = class_number+'0';
		p->Stu.class[1] = '\0';
	}
	system("cls");
    //��ʾ�û�����ѧ��רҵ
	printf("||����������ѧ��רҵ(����'0'�˳�)����\n||");
	scanf("%s",modify_mojority);
    take_in_line_break();
    //����0�˳�
    if(char_return_by_zero(p->Stu.majority))
	{
		printf("||�˳��ɹ�\n||");
		system("pause");
		system("cls");
        return;
    }
    strcpy(p->Stu.majority,modify_mojority);
    printf("||�޸ĳɹ�\n||");
    system("pause");
}

//��ʦɾ��ѧ�������Ϣ
void remove_student_id_info(void)
{
	enum Choice{id = 1,name,go_back}choice;
	
    do
	{
	    system("cls");
        //��ʾ�û�������Ϣ
        printf("||==============================||\n");
	    printf("||��������Ҫɾ����ѧ�������Ϣ  ||\n");
	    printf("||==============================||\n");
	    printf("||1.ͨ��ѧ��ɾ��\t\t||\n");
	    printf("||2.ͨ������ɾ��\t\t||\n");
	    printf("||3.���ز˵�\t\t\t||\n");
        printf("||==============================||\n||");
	   	if(scanf("%d",&choice) != 1)//���choice�����������������if���
	    {
		    //��ʾ�û�����ԭ��
		    printf("||Ҫ����������\n");
		    input_again();//��ʾ�û���������
		    continue;//����ѭ��
	    }
	    take_in_line_break();
	    switch(choice)
	    {
	        case id://ѧ��ɾ��
                remove_id_by_id();
                break;
	        case name://����ɾ��
		        remove_id_by_name();
		        break;
	  	    case go_back://���ز˵�
				system("cls");
				break;
	        default ://��������
				printf("||!���������!\n||");
				system("pause");
		        break;
     	}
	    //����ѧ����Ϣ
        tea_save_stu(5);
	    save_id_studentinfo();
     	if(choice == go_back)break;
	}while(1);
	system("cls");
}

//ͨ��ѧ��ɾ��ѧ�������Ϣ
void remove_id_by_id(void)
{
	system("cls");
	//�������ͱ���stu_id,���û���ֵ,��ƥ���ӦҪɾ����ѧ��,flag����ȷ���û��Ƿ�Ҫɾ��ѧ�������Ϣ
	int stu_id = 0;
	char flag;
	//����һ��stu���͵�ָ��ָ��ѧ������ı�ͷstu_list,���ڱ�������;������stu���͵�ָ�����p1����ɾ��ѧ�������Ϣ
	stu *p = stu_list,*p1 = NULL;
	
    do
    {
    	//��ʾ�û�������Ϣ
        printf("||===================================||\n");
	    printf("||��������Ҫɾ����ѧ��ѧ��(����0�˳�)||\n||");
	   	if(scanf("%d",&stu_id) != 1)//���stu_id�����������������if���
	    {
		    //��ʾ�û�����ԭ��
		    printf("||Ҫ����������\n");
		    input_again();//��ʾ�û���������
		    continue;//����ѭ��
	    }
	    break;
	}while(1);
    take_in_line_break();
	//����0�˳�
	if(return_by_zero(stu_id))return;
    
	if(stu_list == NULL)
	{
        printf("||�����ڸ�ѧ��\n||");
        system("pause");
        system("cls");
        return;
	}
    
	system("cls");
    //��pָ��ѧ����Ϣ����ı�ͷ,���б�������
	for(p = stu_list;p;p = p->next)
        //����û�����ѧ��ѧ�ź������ж�Ӧ��ѧ��ѧ��ƥ�������if���,�����flagΪһ,˵���Լ��ҵ���ѧ��,���˳�ѭ��
		if(p->Stu.id == stu_id)
		{
			flag = 1;
			break;
		}
    //���flag����Ϊ0��˵���Ҳ���ƥ��ѧ�������if�����ʾ�û�
	if(flag == 0)
	{
		printf("!���Ҳ�����ѧ����!\n");
		system("pause");
		system("cls");
    }
    //���flagΪ1˵���ҵ��������else���
	else
	{
		//��Ϊֻ֪����ѧ����ǰ����λ�û�����ɾ����Ϣ,Ҫ֪����ѧ��ǰ���ѧ����next����ɾ��
        //�����ٶ���ѭ��
	    for(p = stu_list;p;p = p->next)
	    {
	    	//������û������ѧ��ѧ�źͶ�Ӧ��ѧ��ѧ��ƥ����������
		    if(p->Stu.id == stu_id)
		    {
		    	do
		    	{
		    	    //��ʾ�û���ѧ����Ϣ
			        printf("||ѧ��============����============�༶============רҵ============����==||\n");
			        printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t||\n",p->Stu.id,p->Stu.name,p->Stu.class,p->Stu.majority,p->Stu.grade);
			        //��ʾ�û��Ƿ�ȷ��ɾ��
                    printf("||����ȷ��ɾ����(����y��ɾ��,���������ַ���ȡ��ɾ��)����\t\t||\n||");
					//����û�ֻ����س��������ѭ��ֱ��������س���Ϊֹ
 	                scanf("%c",&flag);
 	                getchar();
                    while(flag == '\n')
                    {
        	            printf("||");
		                scanf("%c",&flag);
		                continue;
	                }
	                break;
	            }while(1);
	            
                if(flag == 'y')
                {
                	//���жϸ�ѧ��λ��ѧ������ı�ͷ,���߱�β
                	//�����ѧ��λ�ڱ�ͷ�����if���
                    if(p == stu_list)
                    {
                    	//��ѧ������ı�ͷָ��ڶ����ڵ�Ȼ�����ͷ�p,��ʱpָ���ͷ,�ͷ�p�൱���ͷ��ʼ�ı�ͷ
                	    stu_list = stu_list->next;
                	    free(p);//�ͷű�ͷ�ڴ�
						p = NULL;//��������ָ��
				    }
                    //���λ�ڱ�β�����if���
				    else if(p->next == NULL)
                        {
					        free(p);
					        p = NULL;
					    }
                    //��ʾ�û�ɾ���ɹ�
				    printf("||����ɾ���ɹ�������\n||");
				    system("pause");
			    }
			    else
				{
				    printf("||ȡ��ɾ��\n||");
				    system("pause");
				}
			    break;
		    }
		    
		    //�����ѧ��λ�������м������if���
		    if(p->next->Stu.id == stu_id)
		    {
		    	do
		    	{
		    	    //��ʾ�û���ѧ����Ϣ
			        printf("||ѧ��============����============�༶============רҵ============����==||\n");
			        printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t||\n",p->next->Stu.id,p->next->Stu.name,
					p->next->Stu.class,p->next->Stu.majority,p->Stu.grade);
			        //��ʾ�û��Ƿ�ȷ��ɾ��
                    printf("||����ȷ��ɾ����(����y��ɾ��,���������ַ���ȡ��ɾ��)����\t\t||\n||");
					//����û�ֻ����س��������ѭ��ֱ��������س���Ϊֹ
 	                scanf("%c",&flag);
 	                getchar();
                    while(flag == '\n')
                    {
        	            printf("||");
		                scanf("%c",&flag);
		                continue;
	                }
                    break;
                }while(1);
                
                //ȷ��ɾ������y��������
                if(flag == 'y')
                {
                	//��p1ָ��Ҫɾ����ѧ��
            	    p1 = p->next;
            	    //��Ҫɾ����ѧ�����滻Ҫɾ����ѧ������һ��ѧ��
            	    p->next = p->next->next;
            	    //�ͷ�p1,p1ָ��Ҫɾ����ѧ��,�ͷ�p1�൱��ɾ����ѧ��
            	    free(p1);
					p1 = NULL;//��������ָ��
					//��ʾ�û�ɾ���ɹ�
			        printf("||����ɾ���ɹ�!����\n||");
			        system("pause");
			    }
			    else
			    {
				    printf("||ȡ��ɾ��\n||");
				    system("pause");
				}
			    break;
		    }
	    }
	}
}

//ͨ������ɾ��ѧ�������Ϣ
void remove_id_by_name(void)
{
	system("cls");
	//flag����ȷ��ѧ����Ϣ�Ƿ�Ҫɾ��
	int flag = 0;
	//stu_name���û�����,���������Ӧ��ѧ��ƥ��
	char stu_name[NAME_LEN];
	//����stu���͵�ָ�����pָ��ǰѧ������ı�ͷ,���ڱ�������;�ٶ���stu���͵�ָ���������ɾ��Ҫɾ����ѧ��
	stu *p = stu_list,*p1 = NULL;

	//��ʾ�û�������Ϣ
 	printf("||=====================================||\n");
	printf("||��������Ҫɾ����ѧ������(ֻ����0�˳�)||\n||");
	scanf("%s",stu_name);
    take_in_line_break();
    
	if(stu_list == NULL)
	{
        printf("||�����ڸ�ѧ��\n||");
        system("pause");
        system("cls");
        return;
	}
    
	//����0�˳�
	if(char_return_by_zero(stu_name))return;
	system("cls");
	
    //��pָ��ѧ����Ϣ����ı�ͷ,���б�������
	for(p = stu_list;p;p = p->next)
		//����û�����ѧ�������������ж�Ӧ��ѧ������ƥ�������if���,�����flagΪһ,˵���Լ��ҵ���ѧ��,���˳�ѭ��
		if(strcmp(p->Stu.name,stu_name) == 0)
		{
			flag = 1;
			break;
		}
    //���flag����Ϊ0��˵���Ҳ���ƥ��ѧ�������if�����ʾ�û�
	if(flag == 0)
	{
		printf("!���Ҳ�����ѧ����!\n");
		system("pause");
		system("cls");
    }
	else
	{
		//��Ϊֻ֪����ѧ����ǰ����λ�û�����ɾ����Ϣ,Ҫ֪����ѧ��ǰ���ѧ����next����ɾ��
        //�����ٶ���ѭ��
	    for(p = stu_list;p;p = p->next)
	    {
	    	//������û������ѧ�������Ͷ�Ӧ��ѧ������ƥ����������
		    if(strcmp(p->Stu.name,stu_name) == 0)
		    {
		    	do
		    	{
		    	    //��ʾ�û���ѧ������Ϣ
			        printf("||ѧ��============����============�༶============רҵ============����==||\n");
			        printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t||\n",p->Stu.id,p->Stu.name,p->Stu.class,p->Stu.majority,p->Stu.grade);
			        //��ʾ�û��Ƿ�Ҫɾ��
                    printf("||����ȷ��ɾ����(����y��ɾ��,���������ַ���ȡ��ɾ��)����\t\t||\n||");
					//����û�ֻ����س��������ѭ��ֱ��������س���Ϊֹ
 	                scanf("%c",&flag);
 	                getchar();
                    while(flag == '\n')
                    {
        	            printf("||");
		                scanf("%c",&flag);
		                continue;
	                }
					break;
                }while(1);
                
                //���ȷ��Ҫɾ�������if���
                if(flag == 'y')
                {
                	//���pָ��ѧ����Ϣ����ı�ͷ�����if���
                    if(p == stu_list)
                    {
                        //����ͷָ��ڶ���ѧ��
                	    stu_list = stu_list->next;
                	    //���ͷ�p,�ͷ�ǰpָ���ͷ�����ͷ�p�൱��ɾ����ͷ,�ҵڶ���ѧ����Ϊ�±�ͷ
                	    free(p);
                        p = NULL;//��������ָ��
				    }
				    //�����ѧ��Ϊ�����β��ֱ���ͷ�
				    else if(p->next == NULL)
				    {
					    free(p);
					    p = NULL;
					}
                    //��ʾ�û��ͷųɹ�
				    printf("||����ɾ���ɹ�������\n||");
				    system("pause");
			    }
			    else
			    {
				    printf("||ȡ��ɾ��\n||");
				    system("pause");
				}
			    break;
		    }
		    //���ѧ��λ��֮�������if���
		    if(strcmp(p->next->Stu.name,stu_name) == 0)
		    {
		    	do
		    	{
                    //��ʾ�û���ѧ����Ϣ
			        printf("||ѧ��============����============�༶============רҵ============����==||\n");
			        printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t||\n",p->next->Stu.id,p->next->Stu.name,p->next->Stu.class,p->next->Stu.majority,p->next->Stu.grade);
			        //��ʾ�û�ȷ���Ƿ�Ҫɾ����ѧ�������Ϣ
                    printf("||����ȷ��ɾ����(����y��ɾ��,���������ַ���ȡ��ɾ��)����\t\t||\n||");
                    //����û�ֻ����س��������ѭ��ֱ��������س���Ϊֹ
 	                scanf("%c",&flag);
                    while(flag == '\n')
                    {
        	            printf("||");
		                scanf("%c",&flag);
		                continue;
	                }
					break;
                }while(1);
                if(flag == 'y')
                {
                	//��p1ָ��Ҫɾ����ѧ��
            	    p1 = p->next;
            	    //��Ҫɾ����ѧ���滻ΪҪɾ����ѧ������һ��ѧ��
            	    p->next = p->next->next;
            	    //Ȼ�����ͷ�p1,��ʱ�ͷ�p1�൱��ɾ����ѧ��
            	    free(p1);
            	    p1 = NULL;//��������ָ��
                    //��ʾ�û�ɾ���ɹ�
			        printf("||����ɾ���ɹ�������\n||");
			        system("pause");
			    }
			    else 
			    {
				    printf("||ȡ��ɾ��\n||");
				    system("pause");
				}
			    break;
		    }
	    }
	}
}

//ɾ��ѧ��������Ϣ
void remove_student_exam_info(void)
{
	//��ȡѧ��������Ϣ
	read_stu_exam_list();
	enum Choice{id = 1,name,go_back}choice;
	
    do
	{
		//��ʾ�û�������Ϣ
	    system("cls");

        printf("||==============================||\n");
	    printf("||��������Ҫɾ����ѧ��������Ϣ  ||\n");
	    printf("||==============================||\n");
	    printf("||1.ͨ��ѧ��ɾ��\t\t||\n");
	    printf("||2.ͨ������ɾ��\t\t||\n");
	    printf("||3.���ز˵�\t\t\t||\n");
        printf("||==============================||\n||");
	   	if(scanf("%d",&choice) != 1)//���choice�����������������if���
	    {
	    	getchar();
		    //��ʾ�û�����ԭ��
		    printf("||Ҫ����������\n||");
		    system("pause");
		    system("cls");
		    continue;//����ѭ��
	    }
	    take_in_line_break();
	    switch(choice)
	    {
	        case id://ѧ��ɾ��ѧ��������Ϣ
                remove_exam_by_id();
                break;
	        case name://����ɾ��ѧ��������Ϣ
		        remove_exam_by_name();
		        break;
	  	    case go_back://���ز˵�
				system("cls");
				break;
	        default ://��������
				printf("||!���������!\n||");
		        break;
     	}
     	if(choice == go_back)break;
     }while(1);
     //��ȡѧ��������Ϣ֮��ɾ��ѧ��������Ϣ����
    delete_stu_exam_list();
    //������Ϣ��"studentinfo.txt"�ļ���
	save_id_studentinfo();
	system("cls");
}

//ͨ��ѧ��ɾ��ѧ��������Ϣ
void remove_exam_by_id(void)
{
	system("cls");
	//delete_stu_id����Ҫɾ����ѧ��ѧ��,flag�����ж��û������ѧ���Ƿ����ѧ��������Ϣ������
	//i����ѭ����ӡѧ������⿼�Դ�,gf_questions_count������¼���������
	int delete_stu_id,flag = 0,i = 0,gf_questions_count;
	//����һ��Student_timu_list���͵�ָ��pָ��ѧ��������Ϣ����ı�ͷstudent_timu_list
	//�ڶ���һ��ͬ��ΪStudent_timu_list���͵�ָ��p1��Ϊ��
	Student_timu_list *p = student_timu_list,*p1 = NULL;
	char ch;//ch�ж��û��Ƿ�ȷ��Ҫɾ����ѧ��

    //��ֻ���ķ�ʽ��"timu(clear)"���ı��ļ�,������һ���ļ�ָ��ָ����ļ�
	FILE *fpr = fopen("timu(clear).txt","r");
    if(fpr == NULL)
    {
    	printf("||ɾ��ʧ��\n||");
    	system("pause");
    	system("cls");
    	return;
	}
	//���ļ��ж�ȡ����������
	fscanf(fpr,"%*d,%*d,%d",&gf_questions_count);
	fclose(fpr);//�ر��ļ�

    do
    {
    	//��ʾ�û�����
        printf("||===================================||\n");
	    printf("||��������Ҫɾ����ѧ��ѧ��(����0�˳�)||\n||");
 		//����û������ѧ��ѧ�Ų�Ϊ���������if�����ʾ�û�����ԭ��
	    if(scanf("%d",&delete_stu_id) != 1)
	    {
	 		//��ʾ�û�����ԭ��
		    printf("||Ҫ����������\n");
		    system("pause");
			system("cls");
		    continue;//����ѭ��
		}
		break;
	}while(1);
    take_in_line_break();
    //����0�˳�
    if(return_by_zero(delete_stu_id))return;
    
	if(stu_list == NULL)
	{
        printf("||�����ڸ�ѧ��\n||");
        system("pause");
        system("cls");
        return;
	}
    
	system("cls");
	//��ѧ��������Ϣ������Ѱ�Ҹ�ѧ��
	for(p = student_timu_list;p;p = p->next)
		if(p->stu_timu.Stu.id == delete_stu_id)
		{
			flag = 1;//����ҵ���ѧ��,����flag��ֵΪ1
			break;//�ҵ�֮��ֹͣѰ��
		}
    //���flag == 0��˵���Ҳ�����ѧ��
	if(flag == 0)
	{
		//��ʾ�û��Ҳ�����ѧ��
		printf("||!���Ҳ�����ѧ����!\n||");
		system("pause");//��ͣ���û����
		system("cls");
    }
    //�������else���
	else
	{
		//����stu���͵�ָ��pt2ָ��ѧ����Ϣ�����ͷ
		stu *pt2 = stu_list;
		//Ѱ�ҵ���Ӧѧ��
		for(pt2 = stu_list;pt2;pt2 = pt2->next)
			if(pt2->Stu.id == p->stu_timu.Stu.id)//����ҵ������if��������ز���
			{
				//�ҵ�֮�����ѧ����Ϣ�����еĳɼ��Ϳ���״̬����Ҫɾ����ѧ������Ϣ
				p->stu_timu.Stu.examination_status = pt2->Stu.examination_status;
				p->stu_timu.Stu.grade = pt2->Stu.grade;
			    break;
			}
        //��ʾ�û���ǰѧ����Ϣ
		printf("||רҵ======�༶======ѧ��======����======�ɼ�======����״̬==ѧ���ж����=====ѧ��ѡ�����=====ѧ��������||\n");
 		printf("||%s    %s      %d       %s     %.2f  %d      \t%s     \t\t%s\t\t",p->stu_timu.Stu.majority,
		 p->stu_timu.Stu.class,p->stu_timu.Stu.id,p->stu_timu.Stu.name,p->stu_timu.Stu.grade,
		 p->stu_timu.Stu.examination_status,p->stu_timu.stu_tf_answer,p->stu_timu.stu_choice_answer);
		for(i = 0;i < gf_questions_count;i++)
		    printf("(%d).%s\t",i+1,p->stu_timu.stu_gf_answer[i]);
        //��ʾ�û��Ƿ�ɾ��
        printf("\n||����ȷ��ɾ����ѧ��������Ϣ��(����y��ɾ��,���������ַ���ȡ��ɾ��)����||\n||");
        while(1)//while����Ϊ��ֱ���û���һ���ַ������뻻�з�
        {
 	        scanf("%c",&ch);
            while(ch == '\n')
            {
        	    printf("||");
		        scanf("%c",&ch);
		        continue;
	        }
	        take_in_line_break();
	        break;
		}
		//�������y�����
        if(ch == 'y')
        {
        	//��ԭ�Ȼ�δ�޸ĵ�ѧ��������Ϣ��¼����Ϊ"stu1"���ı��ļ���
            save_stu1(p->stu_timu.Stu.id);
            //���¿�ʼ�޸�
            //���ɼ��Ϳ���״̬��Ϊ0
			p->stu_timu.Stu.grade = 0;
			p->stu_timu.Stu.examination_status = 0;
			p->stu_timu.stu_full_mark = 0;
			//�����д���Ϊ"no"
            strcpy(p->stu_timu.stu_tf_answer,"no");
            strcpy(p->stu_timu.stu_choice_answer,"no");
			for(i = 0;i < gf_questions_count;i++)
				strcpy(p->stu_timu.stu_gf_answer[i],"no");
			//��ѧ����Ϣ�ϵĳɼ��Ϳ���״̬Ҳ��Ϊ0
			pt2->Stu.examination_status = 0;
			pt2->Stu.grade = 0;
			//��ʾ�û�ɾ���ɹ�
			printf("||����ɾ���ɹ�!����\n||");
			system("pause");
			system("cls");
			save_id_studentinfo();
			tea_save_stu(3);//����ɾ�������Ϣ
		}
	}
}

//ͨ������ɾ��ѧ��������Ϣ
void remove_exam_by_name(void)
{
	system("cls");
	//flag�����ж��û������ѧ���Ƿ����ѧ��������Ϣ������
	//i����ѭ����ӡѧ������⿼�Դ�,gf_questions_count������¼���������
	int flag = 0,i = 0,gf_questions_count = 0;
	//delete_stu_name�������û�����Ҫɾ����ѧ������
	char delete_stu_name[NAME_LEN];
	//����һ��Student_timu_list���͵�ָ��pָ��ѧ��������Ϣ����ı�ͷstudent_timu_list
	//�ڶ���һ��ͬ��ΪStudent_timu_list���͵�ָ��p1��Ϊ��
	Student_timu_list *p = student_timu_list,*p1 = NULL;
	char ch;//ch�ж��û��Ƿ�ȷ��Ҫɾ����ѧ��

    //��ֻ���ķ�ʽ��"timu(clear)"���ı��ļ�,������һ���ļ�ָ��ָ����ļ�
	FILE *fpr = fopen("timu(clear).txt","r");
	if(fpr == NULL)
    {
    	printf("||ɾ��ʧ��\n||");
    	system("pause");
    	system("cls");
    	return;
    }
	//���ļ��ж�ȡ����������
	fscanf(fpr,"%*d,%*d,%d",&gf_questions_count);
	fclose(fpr);//�ر��ļ�

	//��ʾ�û�����
	printf("||===================================||\n");
	printf("||��������Ҫɾ����ѧ������(����0�˳�)||\n||");
	scanf("%s",delete_stu_name);
    take_in_line_break();
    //����"0"�˳�
    if(char_return_by_zero(delete_stu_name))return;
    
	if(stu_list == NULL)
	{
        printf("||�����ڸ�ѧ��\n||");
        system("pause");
        system("cls");
        return;
	}
    
	system("cls");
	//��ѧ��������Ϣ������Ѱ�Ҹ�ѧ��
	for(p = student_timu_list;p;p = p->next)
		if(strcmp(p->stu_timu.Stu.name,delete_stu_name) == 0)
			flag = 1;
    //˵���Ҳ�����ѧ��
	if(flag == 0)
	{
		//��ʾ�û��Ҳ���
		printf("||!���Ҳ�����ѧ����!\n||");
		system("pause");
		system("cls");
    }
    //�������else���
	else
	{
		//����stu���͵�ָ��pt2ָ��ѧ����Ϣ�����ͷ
		stu *pt2 = stu_list;
		//Ѱ�ҵ���Ӧѧ��
		for(pt2 = stu_list;pt2;pt2 = pt2->next)
			if(pt2->Stu.id == p->stu_timu.Stu.id)//����ҵ������if��������ز���
			{
				//�ҵ�֮�����ѧ����Ϣ�����еĳɼ��Ϳ���״̬����Ҫɾ����ѧ������Ϣ
				p->stu_timu.Stu.examination_status = pt2->Stu.examination_status;
				p->stu_timu.Stu.grade = pt2->Stu.grade;
			    break;
			}
        //��ʾ�û���ǰѧ����Ϣ
		printf("||רҵ======�༶======ѧ��======����======�ɼ�======����״̬==ѧ���ж����=====ѧ��ѡ�����=====ѧ��������||\n");
 		printf("||%s    %s      %d       %s     %.2f  %d      \t%s     \t\t%s\t\t",p->stu_timu.Stu.majority,p->stu_timu.Stu.class,p->stu_timu.Stu.id,p->stu_timu.Stu.name,p->stu_timu.Stu.grade,p->stu_timu.Stu.examination_status,p->stu_timu.stu_tf_answer,p->stu_timu.stu_choice_answer);
		for(i = 0;i < gf_questions_count;i++)
		    printf("(%d).%s\t",i+1,p->stu_timu.stu_gf_answer[i]);
        //��ʾ�û��Ƿ�Ҫɾ��
        printf("\n||����ȷ��ɾ����ѧ��������Ϣ��(����y��ɾ��,���������ַ���ȡ��ɾ��)����||\n||");
        while(1)//while����Ϊ��ֱ���û���һ���ַ������뻻�з�
        {
 	        scanf("%c",&ch);
            while(ch == '\n')
            {
        	    printf("||");
		        scanf("%c",&ch);
		        continue;
	        }
	        take_in_line_break();
	        break;
		}
		//�������y�����
        if(ch == 'y')
        {
        	//��ԭ�Ȼ�δ�޸ĵ�ѧ��������Ϣ��¼����Ϊ"stu1"���ı��ļ���
            save_stu1(p->stu_timu.Stu.id);
            //���¿�ʼ�޸�
            //���ɼ��Ϳ���״̬��Ϊ0
			p->stu_timu.Stu.grade = 0;
			p->stu_timu.Stu.examination_status = 0;
			p->stu_timu.stu_full_mark = 0;
			//�����д���Ϊ"no"
            strcpy(p->stu_timu.stu_tf_answer,"no");
            strcpy(p->stu_timu.stu_choice_answer,"no");
			for(i = 0;i < gf_questions_count;i++)
				strcpy(p->stu_timu.stu_gf_answer[i],"no");
			//��ѧ����Ϣ�ϵĳɼ��Ϳ���״̬Ҳ��Ϊ0
			pt2->Stu.examination_status = 0;
			pt2->Stu.grade = 0;
			//��ʾ�û�ɾ���ɹ�
			printf("||����ɾ���ɹ�!����\n||");
			system("pause");
			system("cls");
			tea_save_stu(3);//����ɾ�������Ϣ
		}
	}
}

//��ʼʱ��ȡ�ļ�stu.txt��ѧ����Ϣ������
void read_stu_exam_list(void)
{
	//��ֻ���ķ�ʽ����Ϊ"stu(clear)"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpr1ָ����ļ�
	FILE *fpr1 = fopen("stu(clear).txt","r");
	if(fpr1 == NULL)//��ʧ��ʱ
		return;
	//i����ʵʱ���������,j����һ��������ʵʱ����,gf_count�����ܵ��������Ŀ
	int i = 0,j = 0,gf_questions_count = 0,tf_questions_count = 0,Choice_questions_count = 0;
	//temp��ʱ����һ���ļ��е��ַ�,�жθ��ַ��Ƿ���Ч,��Ч�򸳸��������е�ĳ��Ԫ��
	char temp;
	
	//��ֻ���ķ�ʽ����Ϊ"timu(clear)"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpr2ָ����ļ�
	FILE *fpr2 = fopen("timu(clear).txt","r");
	//��ȡ����������
	if(fpr2 == NULL)
		return;
	fscanf(fpr2,"%d,%d,%d",&tf_questions_count,&Choice_questions_count,&gf_questions_count);
	fclose(fpr2);//�ر��ļ�

	if(tf_questions_count == 0 || Choice_questions_count == 0 || gf_questions_count == 0)return;

	else
	{
		//�������ĩβ���˳�
		if(fgetc(fpr1) == EOF)return;
		rewind(fpr1);//������һ��if����Ѿ�����һ���ַ���,������Ҫ��ָ�������Ƶ���ͷ
		
		while(1)//ָ���Ƶ��ļ�ĩβ����
		{
			//����һ��Student_timu_list���͵��ڴ�,����һ��Student_timu_list���͵�ָ��p1ָ����ڴ�
			Student_timu_list *p1 = (Student_timu_list *)malloc(sizeof(Student_timu_list));

            //���ļ��е�ѧ��������Ϣ���뵽ѧ��������Ϣ������
	        fscanf(fpr1,"%s %s %d %s %f %s %s ",p1->stu_timu.Stu.majority,p1->stu_timu.Stu.class,&p1->stu_timu.Stu.id,p1->stu_timu.Stu.name,&p1->stu_timu.stu_full_mark,p1->stu_timu.stu_tf_answer,p1->stu_timu.stu_choice_answer);
	        //��ȡѧ���������Ŀ
			for(i = 0;i < gf_questions_count;i++)
			{
				for(j = 0;;j++)
                {
				    //temp��ʱ�洢��ȡ�ļ����ַ�
				    temp = fgetc(fpr1);
				    if(temp == EOF)
				    {
					    //��ʾ�û�����ԭ��
					    system("cls");
					    break;
				    }
				    if(temp == '\n')break;
				    else if(temp == 35)break;
				    p1->stu_timu.stu_gf_answer[i][j] = temp;
				}
				//����Ч�ַ���ĩβ��Ϊ'\0'
			    p1->stu_timu.stu_gf_answer[i][j] = '\0';
			    //�������з�,�������ѧ����ѭ��,�ӵ��¸�ѧ����ѭ��
				if(temp == '\n')break;
				//���tempΪEOF(������ĩβ)�����ѭ��,�˳��ù���
				else if(temp == EOF)break;
			}
            //���tempΪEOF(������ĩβ)�����ѭ��,�˳��ù���
			if(temp == EOF) break;
			p1->next = NULL;//��ĩβ��Ϊ��
			//���ѧ����Ϣ����ı�ͷ��Ϊ�������if���
			if(student_timu_list)
			{
				//��β�巨����
                //����Ҫ����4
                //�����ǰ����Ϊ��1->5->0->2->NULL
                //����������Ϊ��1->5->0->2->4->NULL
				//����Student_timu_list���͵�ָ��pָ��ѧ��������Ϣ����ı�ͷ
				Student_timu_list *p = student_timu_list;
				//��pָ�������ĩβ
				for(;p->next;p = p->next);
				//�ٽ����µĲ��뵽ĩβ��
				p->next = p1;
			}
			//���ѧ����Ϣ����ı�ͷΪ��,�򽫸���Ϣ��Ϊ��ͷ
			else student_timu_list = p1;
		}
	}
	fclose(fpr1);//�ر��ļ�
	//���tempΪEOF(������ĩβ)�����ѭ��,�˳��ù���
	if(temp == EOF)return;
}

//������Ϣ��stu1.txt��,delete_stu_idΪҪɾ��ѧ����ѧ��,�����ҵ���Ӧѧ��
void save_stu1(int delete_stu_id)
{
	//��ֻ���ķ�ʽ����Ϊ"timu(clear)"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fprָ����ļ�
	FILE *fpr = fopen("timu(clear).txt","r");
	//����ĩβ׷�ӵķ�ʽ����Ϊ"stu1"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpwָ����ļ�
    FILE *fpw = fopen("stu1.txt","a+");
    //gf_questions_count�����������Ŀ,i����ѭ������������
    int gf_questions_count = 0,i = 0;
    
    //�������ָ��Ϊ��,��˵����ʧ��
    if(fpw == NULL || fpr == NULL)
	{
		printf("||!������ʧ�ܡ�!\n||");
		system("pause");
		return;
	}
	
    //��ȡ���������
    fscanf(fpr,"%*d,%*d,%d",&gf_questions_count);
    fclose(fpr);//�ر��ļ�
    
    //����һ��Student_timu_list���͵�ָ��pָ��ѧ��������Ϣ�����ͷ
    Student_timu_list *p = student_timu_list;
    //��������ֱ���ҵ���ѧ��,���ڸ���Ϣ�����ҵ���ѧ����ǰ���µõ���,���Բ������Ҳ�����ѧ�������
    for(p = student_timu_list;p;p = p->next)
        //����β���(�û�����)��ѧ�ź����������Ӧѧ����ѧ��ƥ�������if���
    	if(p->stu_timu.Stu.id == delete_stu_id)
        {
        	//����ѧ����Ϣ���뵽�ļ���
		    fprintf(fpw,"%s %s %d %s %f %d %s %s",p->stu_timu.Stu.majority,p->stu_timu.Stu.class,p->stu_timu.Stu.id,p->stu_timu.Stu.name,p->stu_timu.Stu.grade,p->stu_timu.Stu.examination_status,p->stu_timu.stu_tf_answer,p->stu_timu.stu_choice_answer);
		    //ѭ����ѧ����������ѭ�������ȥ
            for(i = 0;i < gf_questions_count;i++)
			    fprintf(fpw," %s",p->stu_timu.stu_gf_answer[i]);
		    fprintf(fpw,"\n");//���뻻�з��Ա���һ��ѧ����˳������
		    break;
		}
    //��ʾ�û���Ϣ����ɹ�
    printf("||����������Ϣ�ɹ�������\n");
    
    fclose(fpw);//�ر��ļ�
}

//��Ϣʹ�ý�����ѧ����Ϣ����ɾ��
void delete_stu_exam_list(void)
{
	//��ѧ����������Ϊ��ʱһֱѭ��
	while(student_timu_list)
	{
		//����һ��Student_timu_list���͵�ָ��pָ���ͷ
		Student_timu_list *p = student_timu_list;
		//����ͷָ���ͷ����һ���ڵ�,����Ϊ�µı�ͷ
		student_timu_list = student_timu_list->next;
		//��ʱpΪԭ���ı�ͷ,�ͷ�p�൱��ɾ��ԭ���ı�ͷ
		free(p);
	}
	//����ͷ��Ϊ��
	student_timu_list = NULL;
}

//��ʦ����ѧ����Ϣ��stu.txt��stu(clear).txt,flag˵��Ҫ�����ģʽ
void tea_save_stu(int flag)
{
	//flag == 3����ɾ�����޸�ĳ����һЩѧ��������Ϣ�󱣴�ȫ��ѧ��������Ϣ��"stu(clear)"��"stu"�ı��ļ���
	if(flag == 3)
	{
	    //��ֻд�ķ�ʽ����Ϊ"stu(clear)"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpw1ָ����ļ�
	    FILE *fpw1 = fopen("stu(clear).txt","w");
 	    //��ֻд�ķ�ʽ����Ϊ"stu"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpw2ָ����ļ�
	    FILE *fpw2 = fopen("stu.txt","w");
	    //i����ѭ������������,gf_questions_count�������������
	    int i = 0,gf_questions_count = 0;
	
	    //��ֻ���ķ�ʽ����Ϊ"timu(clear)"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpr1ָ����ļ�
	    FILE *fpr1 = fopen("timu(clear).txt","r");
	    if(fpr1 == NULL)return;
	    //��ȡ���������
	    fscanf(fpr1,"%*d,%*d,%d",&gf_questions_count);
	    fclose(fpr1);//�ر��ļ�
	
        //����һ��Student_timu_list���͵�ָ��p1ָ��ѧ����������ı�ͷ
	    Student_timu_list *p1 = student_timu_list;
	
        //��forѭ��������ѧ���Ŀ�����Ϣ�����뵽"stu(clear)"�ı��ļ���
	    for(p1 = student_timu_list;p1;p1 = p1->next)
	    {
		    fprintf(fpw1,"%s %s %d %s %f %s %s ",p1->stu_timu.Stu.majority,
			p1->stu_timu.Stu.class,p1->stu_timu.Stu.id,p1->stu_timu.Stu.name,
			p1->stu_timu.Stu.grade,p1->stu_timu.stu_tf_answer,p1->stu_timu.stu_choice_answer);
		    for(i = 0;i < gf_questions_count-1;i++)
			    fprintf(fpw1,"%s#",p1->stu_timu.stu_gf_answer[i]);
		    fprintf(fpw1,"%s",p1->stu_timu.stu_gf_answer[gf_questions_count-1]);
		    fprintf(fpw1,"\n");//���뻻�з�,������һ��ѧ����Ϣ¼��
	    }
	
	    fclose(fpw1);//�ر��ļ�
	
        //����Ӧ���ݴ�ӡ����
	    fprintf(fpw2,"רҵ******�༶*****ѧ��******����******�ɼ�******ѧ���ж����*****ѧ��ѡ�����*****ѧ��������\n");
         //��forѭ��������ѧ���Ŀ�����Ϣ�����뵽"stu"�ı��ļ���
	    for(p1 = student_timu_list;p1;p1 = p1->next)
	    {
	        fprintf(fpw2,"%s\t%s\t%d\t%s\t%f\t%s\t\t%s\t\t",p1->stu_timu.Stu.majority,p1->stu_timu.Stu.class,
			p1->stu_timu.Stu.id,p1->stu_timu.Stu.name,p1->stu_timu.Stu.grade,p1->stu_timu.stu_tf_answer,p1->stu_timu.stu_choice_answer);
	        for(i = 0;i < gf_questions_count;i++)
		        fprintf(fpw2,"(%d).%s\t",i+1,p1->stu_timu.stu_gf_answer[i]);
	        fprintf(fpw2,"\n");
	    }
	
	    fclose(fpw2);//�ر��ļ�
	}
	
	//flag == 2������¼���ѧ����Ϣ���浽"stu(clear)"��"stu"�ı��ļ���
	else if(flag == 2)
	{
	    //��ֻ���ķ�ʽ����Ϊ"studentinfo"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpr2ָ����ļ�
		FILE *fpr2 = fopen("studentinfo.txt","r");
 	    //��ֻ���ķ�ʽ����Ϊ"timu(clear)"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpr3ָ����ļ�
		FILE *fpr3 = fopen("timu(clear).txt","r");
 	    //����ĩβ׷�ӵķ�ʽ����Ϊ"stu(clear)"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpw3ָ����ļ�
		FILE *fpw3 = fopen("stu(clear).txt","a+");
 	    //����ĩβ׷�ӵķ�ʽ����Ϊ"stu"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpw4ָ����ļ�
		FILE *fpw4 = fopen("stu.txt","a+");
		
		//�������һ���õ���ָ��Ϊ������ʾ�û����˳�
		if(fpr2 == NULL || fpr3 == NULL || fpw3 == NULL || fpw4 == NULL)
		{
			printf("���ļ�ʧ��\n");
			system("pause");
			system("cls");
			return;
		}
		//gf_questions_count�������������,i����ѭ������ѧ��������
		int gf_questions_count = 0,i = 0;
		//����һ��stu���͵�ָ��p1ָ��ѧ��ѧϰ����ı�ͷ,������¼ȡ��ѧ����Ϣʹ��ͷ�巨�����
		//����p1��ָ�Ľڵ������¼��õ���ѧ����Ϣ,һ��*p1�������¼���ѧ����Ϣ,���ԶԴ˽�������Ŀ�𰸶���ʼ��Ϊno
		stu *p1 = stu_list;
		//����p2���͵ı������ڴ洢��¼���ѧ����Ϣ
 		Student_timu p2;
		
		//��ȡ���������
		fscanf(fpr3,"%*d,%*d,%d\n",&gf_questions_count);
		fclose(fpr3);//�ر��ļ�
		
		//��ѧ����Ϣ�ļ��ĵ�һ��(Ҳ�൱�ڱ�ͷ)���������ͷ��,����¼����ѧ����ϢΪͷ�巨,���Եõ�����ϢΪ��¼���ѧ����Ϣ
		fscanf(fpr2,"%d %s %s %s %d %f %d",&(p1->Stu.id),p1->Stu.name,p1->Stu.class,p1->Stu.majority,&(p1->Stu.password),&(p1->Stu.grade),&(p1->Stu.examination_status));
		fclose(fpr2);//�ر��ļ�

        //���ն�����ͷ��Ϣ��p1��ֵ��p2�е�Stu
		p2.Stu = p1->Stu;
        //��p2��ָ��������Ŀ�𰸶���ʼ��Ϊ"no"
		strcpy(p2.stu_tf_answer,"no");
		strcpy(p2.stu_choice_answer,"no");
		for(i = 0;i < gf_questions_count;i++)
			strcpy(p2.stu_gf_answer[i],"no");
			
		//����ĩβ׷�ӵķ�ʽ����Ϣ���뵽�ļ�ĩβ
        fprintf(fpw3,"%s %s %d %s %f %s %s ",p2.Stu.majority,p2.Stu.class,p2.Stu.id,p2.Stu.name,p2.Stu.grade,p2.stu_tf_answer,p2.stu_choice_answer);
		for(i = 0;i < gf_questions_count-1;i++)
			fprintf(fpw3,"%s#",p2.stu_gf_answer[i]);
		fprintf(fpw3,"%s",p2.stu_gf_answer[gf_questions_count-1]);
		fprintf(fpw3,"\n");//���뻻�з�������һλ��¼���ͬѧ����
		
		fclose(fpw3);//�ر��ļ�
		
		//����ĩβ׷�ӵķ�ʽ����Ϣ���뵽�ļ�ĩβ
 	    fprintf(fpw4,"%s\t%s\t%d\t%s\t%f\t%s\t\t%s\t\t",p2.Stu.majority,p2.Stu.class,p2.Stu.id,p2.Stu.name,p2.Stu.grade,p2.stu_tf_answer,p2.stu_choice_answer);
	    for(i = 0;i < gf_questions_count;i++)
		    fprintf(fpw4,"(%d).%s\t",i+1,p2.stu_gf_answer[i]);
	    fprintf(fpw4,"\n");//���뻻�з�������һλ��¼���ͬѧ����
	    
		fclose(fpw4);//�ر��ļ�
	}
	
	//flag == 1�����ʦ��������ʱ,������ͬѧ�ĳɼ�,����״̬,��Ŀ�𰸶���ʼ��,���浽"stu(clear)"��"stu"�ı��ļ���
	else if(flag == 1)
	{
        //�ȶ�ȡ"stu(clear)"�е���Ϣ��ѧ������������
		read_stu_exam_list();
		//i����ѭ���������𰸳�ʼ��,gf_questions_count���ڼ�¼�������Ŀ��
		int i = 0,gf_questions_count = 0;
		
        //��ֻ���ķ�ʽ����Ϊ"timu(clear)"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpr4ָ����ļ�
		FILE *fpr4 = fopen("timu(clear).txt","r");
		if(fpr4 == NULL)
		{
			printf("||��ȡ�ļ�ʧ��\n||");
			system("pause");
			system("cls");
			return;
        }
 	    //��ȡ���������
		fscanf(fpr4,"%*d,%*d,%d\n",&gf_questions_count);
		fclose(fpr4);//�ر��ļ�
		
		//����һ��Student_timu_list���͵�ָ��p1ָ��ѧ��������Ϣ�����ͷ
		Student_timu_list *p1 = student_timu_list;
		
		//������������ѧ���Ŀ�����Ϣ����ʼ��
		for(p1 = student_timu_list;p1;p1 = p1->next)
		{
			p1->stu_timu.Stu.grade = 0;
			p1->stu_timu.Stu.examination_status = 0;
			strcpy(p1->stu_timu.stu_tf_answer,"no");
			strcpy(p1->stu_timu.stu_choice_answer,"no");
			for(i = 0;i < gf_questions_count;i++)
				strcpy(p1->stu_timu.stu_gf_answer[i],"no");
		}
		//��ʼ������Ϣ������"stu"��"stu(clear)"���ı��ļ���
		tea_save_stu(3);
		//��Ϣʹ����֮����ɾ��ѧ��������Ϣ����
		delete_stu_exam_list();
	}
	
	//flag == 4��ʦ�޸Ĳ���ѧ����Ϣʱ,Ҳ��"stu"��"stu(clear)"�ļ�������Ϣ�޸�
	else if(flag == 4)
	{
		read_stu_exam_list();
		
		Student_timu_list *p1 = student_timu_list;
		stu *p2 = stu_list;
		
		for(p1 = student_timu_list;p1;p1 = p1->next)
			for(p2 = stu_list;p2;p2 = p2->next)
				if(p1->stu_timu.Stu.id == p2->Stu.id)
				{
					p1->stu_timu.Stu = p2->Stu;
					break;
				}
		tea_save_stu(3);
		
		delete_stu_exam_list();
	}
	
	//flag == 5��ʦɾ������ѧ����Ϣʱ,Ҳ��"stu"��"stu(clear)"�ļ�������Ϣɾ��
	else if(flag == 5)
	{
		read_stu_exam_list();

		if(student_timu_list == NULL)return;
		
		Student_timu_list *p1 = student_timu_list,*pt = p1->next;
		stu *p2 = stu_list;
		int find_flag = 0,head_flag = 0;
		for(p2 = stu_list;p2;p2 = p2->next)
			if(p2->Stu.id == student_timu_list->stu_timu.Stu.id)
			{
				head_flag = 1;
				break;
			}
		if(head_flag == 0)
		{
			student_timu_list = student_timu_list->next;
			free(p1);
			p1 = student_timu_list;
  		    tea_save_stu(3);
		    delete_stu_exam_list();
		    return;
		}
		
		for(p1 = student_timu_list;pt;p1 = p1->next,pt = pt->next)
		{
			find_flag = 0;
			for(p2 = stu_list;p2;p2 = p2->next)
				if(pt->stu_timu.Stu.id == p2->Stu.id)
				{
					find_flag = 1;
					break;
				}
			if(find_flag == 0)
			{
				if(pt->next == NULL)
				{
					p1->next = NULL;
					free(pt);
					pt = NULL;
				}
				else
				{
					p1->next = pt->next;
					free(pt);
					pt = p1->next;
				}
				break;
			}
		}
		tea_save_stu(3);
		delete_stu_exam_list();
	}
	
	else return;
}

//����ѧ�������Ϣ
void save_id_studentinfo(void)
{
	//��ֻд�ķ�ʽ����Ϊ"studentInfo"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpwָ����ļ�
	FILE *fpw = fopen("studentinfo.txt","w");
	//����һ��stu���͵�ָ��ָ��ѧ����Ϣ����ı�ͷ
	stu *p = stu_list;

	//forѭ����ѧ����Ϣ����
	for(;p;p=p->next)
	    fprintf(fpw,"%d %s %s %s %d %f %d\n",p->Stu.id,
		p->Stu.name,p->Stu.class,p->Stu.majority,p->Stu.password,
		p->Stu.grade,p->Stu.examination_status);
	fclose(fpw);//�ر��ļ�
	//��ʾ�û�������Ϣ�ɹ�
	printf("||����ѧ����Ϣ�ļ�����ɹ�!����\n||");
}

//�鿴�ѱ�ɾ����ѧ����Ϣ
void print_stu_deleted_exam_info(void)
{
	system("cls");
	//��ֻ���ķ�ʽ����Ϊ"stu1"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fprָ����ļ�
    FILE *fpr = fopen("stu1.txt","r");
    char ch;//ch������ȡ�ļ��е��ַ�
    
    //����õ���ָ��Ϊ������ʾ�û����˳�
    if(fpr == NULL)
	{
		printf("||���ļ�ʧ��\n||");
		system("pause");
		system("cls");
		return;
	}
	//��ʾ�û���ǰɾ����¼
	printf("||====================================================================================||\n");
	printf("||�������Ѿ�ɾ����ѧ��������Ϣ\t\t\t\t\t\t\t      ||\n");
	printf("||˳��Ϊרҵ,�༶,ѧ��,����,�ɼ�,����״̬,ѧ���ж����,ѧ��ѡ�����,ѧ��������||\n");
    while((ch = fgetc(fpr)) != EOF)//�������ı�ĩβʱ����ѭ��
		printf("%c",ch);

    fclose(fpr);//�ر��ļ�
    system("pause");//��ͣ���û����
    system("cls");
}

//��������
void tea_talking(void)
{
	system("cls");
	int choice = 0;//choice�������û����빦��
	//ǰ�����������Ҫ�𰸿����ļ���
	char teacher_t[TALKING_FILE_NAME] = "tea_and_tea_communication.txt";
	char student_t[TALKING_FILE_NAME] = "stu_and_tea_communication.txt";
	//�������ԭ��ֻ��������Ϊ��ʦ,��˽�"teacher"��Ϊ��ʦ����
	char teacher_name[NAME_LEN] = "teacher";
	
	while(1)
	{
		    system("cls");
	        printf("||==============================||\n");
	        printf("||1.ʦ������Ⱥ\t\t\t||\n");
	        printf("||2.�Լ�����(����¼)\t\t||\n");
	        printf("||3.�˳���������,���ز˵�\t||\n");
	        printf("||==============================||\n||");
	 	   	if(scanf("%d",&choice) != 1)//���choice�����������������if���
	        {
		        //��ʾ�û�����ԭ��
		        printf("||Ҫ����������\n");
		        input_again();//��ʾ�û���������
		        continue;//����ѭ��
	        }
        //����û�ѡ��1��2��������
	    if(choice == 1 ||choice == 2)
	    {
	    	//���ѡ��1�����ʦ������ȺȺ
	        if(choice == 1)
	        {
	        	//������Ϣ�ͷ�����Ϣ����,����student_t�����ļ���(��Ҫ�򿪵��ļ�)
                receive_message(student_t);
		        send_message(student_t,teacher_name);
	        }
	        //���ѡ��2����뱸��¼
	        if(choice == 2)
	        {
	        	//������Ϣ�ͷ�����Ϣ����,����teacher_t�����ļ���(��Ҫ�򿪵��ļ�)
		        receive_message(teacher_t);
		        send_message(teacher_t,teacher_name);
	        }
	    }
	    //����û����������ַ������else���(��1��2)
	    else
		{
			//���ѡ��3,����ʾ�û��˳��ɹ�
		    if(choice == 3)
		    {
			    printf("||�˳��ɹ�\n||");
			    system("pause");
			    system("cls");
			    return;
		    }
		    //���������ַ�����ʾ�û���������,��������
			else
		    {
			    printf("||�����������������\n||");
			    system("pause");
			    system("cls");
			    continue;//����ѭ��
		    }
		}
	}
	
	system("cls");
}

//������Ϣ����
//receive_message�ǲ�������ֵ�ĺ���,�β���һ���ַ����������ڴ��Ҫ�򿪵��ļ���
void receive_message(char filename[])
{
	system("cls");
	char ch;//ch���ڽ����ļ���Ϣ
    //��ֻ���ķ�ʽ����Ϊ"filename"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fprָ����ļ�
	FILE *fpr = fopen(filename,"r");
	
	//�����ǲ�ͬ�����ļ��Ŀ�ͷ
	if(strcmp(filename,"stu_and_tea_communication.txt") == 0)
	    printf("=================================ʦ������Ⱥ====================================================\n");
	if(strcmp(filename,"tea_and_tea_communication.txt") == 0)
		printf("=================================��ʦ����Ⱥ====================================================\n");
	if(strcmp(filename,"stu_and_stu_communication.txt") == 0)
		printf("=================================ѧ������Ⱥ====================================================\n");
    while((ch = fgetc(fpr)) != EOF)//�����ļ�ĩβ����ѭ��
		printf("%c",ch);//��һ���ַ����һ���ַ�
	printf("=================================֮ǰ�ļ�¼====================================================\n");
	
	fclose(fpr);//�ر��ļ�
}

//������Ϣ����
//send_message�ǲ�������ֵ�ĺ���,�β���һ���ַ����������ڴ��Ҫ�򿪵��ļ���
void send_message(char filename[],char username[])
{
	//����ĩβ׷�ӵķ�ʽ����Ϊ"filename"���ı��ļ�,������һ��ָ���ı��ļ����͵�ָ��fpwָ����ļ�
	FILE *fpw = fopen(filename,"a+");
    //sentence�����û�Ҫ����������
	char sentence[LINE_LEN];
	
	//��ʾ�û�����
	printf("||============================��������Ҫ���������=============================================\n");
	printf("||���������ĸ�'#'��������\n");//��ʾ�û������ĵ��ж�
	do
	{
   	    while(strcmp(gets(sentence),"\n") <= 0)
	        printf("||");
		//��ʾ�û�����Ч��
		printf("||%s(����Ԥ��)\n",sentence);
		if(strcmp(sentence,"####") == 0)break;//����û�����"####"���˳�ѭ��,�Ҳ����뵽�ļ���
		fprintf(fpw,"%s:%s\n",username,sentence);
	}while(1);
	printf("||=================================�������=====================================================\n");
	
	fclose(fpw);//�ر��ļ�
}

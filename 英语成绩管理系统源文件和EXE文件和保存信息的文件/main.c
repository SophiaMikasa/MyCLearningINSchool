#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TF_QUESTION 100//判断题题目的最长长度为100
#define OPTION 50//选择题选项的最长长度为50
#define CHOICE_QUESTION 100//选择题题目的最长长度为100
#define GF_QUESTION 100//填空题题目的最长长度为100
#define GF_ANSWER 30//填空题答案的最长长度为30
#define ANSWER_LEN 2//判断题和选择题答案最长长度为2
#define ALL_ANSWER_LEN 15//判断题和选择题分别的最长长度为15
#define NAME_LEN 10//学生名字的长度最长为10
#define CLASS_NAME_LEN 3//班级名字的长度最长为3
#define MAJORITY 10//专业名字的长度最长为10
#define ORIGINAL_PASSWROD 1111//学生初始密码为1111
#define LINE_LEN 64//一行的长度最长为64
#define TALKING_FILE_NAME 35//交流为文本名字的长度最长为30

//学生身份信息(含有名字,班级,专业,学号,密码)
typedef struct _Student{
	//name代表学生姓名(字符串数组),class代表学生所在班级(字符串数组),majority代表学生所选专业(字符串数组)
	char name[NAME_LEN],class[CLASS_NAME_LEN],majority[MAJORITY];
	//id代表学生的学号(整型),password代表学生的密码(整型)(学生初始密码为1111)
	int id,password;
	//grade代表学生的考试成绩(单精度浮点类型)
	float grade;
	//examination_status(整型)代表学生考试状态,如果值为1,则说明该考生已经考过试了,如果为0,则说明该考生还未考试(初始化为0)
	int examination_status;
}Student;//Student代表struct _Student

//学生身份信息的链表(含有学生信息,指向下一节点的指针)
typedef struct _list{
	//Stu代表一个学生
	Student Stu;
	//next指向下一个节点,说明指向下一个学生
	struct _list *next;
}stu;//stu代表struct _list

//判断题结构体(含有题目,答案,该题分数,指向下一节点的指针)
typedef struct _TF_questions{
	//tf_questions代表判断题题目,tf_answer代表判断题答案
	char tf_question[TF_QUESTION],tf_answer[ANSWER_LEN];
	//next指向下一节点,说明指向下一道判断题
	struct _TF_questions *next;
	//tf_score代表该判断题的分数(单精度浮点类型)
	float tf_score;
}TF_questions;//TF_question代表struct _TF_questions

//选择题的选项结构体(含有A、B、C、D四个选项的内容)
typedef struct _Options{
	//option_a代表选项A(后面的一次类推)
	char option_a[OPTION],option_b[OPTION],option_c[OPTION],option_d[OPTION];
}Option;//Option代表struct _Options

//选择题结构体(含有题目,选择的内容,答案,该题分数,指向下一节点的指针)
typedef struct _Choice_questions{
	//choice_question代表选择题题目,cq_answer代表选择题答案
	char choice_question[CHOICE_QUESTION],cq_answer[ANSWER_LEN];
	//cq_score代表该选择分数
	float cq_score;
	//option代表该题目的选项
	Option option;
	//next指向下一节点,说明指向下一道选择题
	struct _Choice_questions *next;
}Choice_questions;//Choice_questions代表struct _Choice_questions

//填空题结构体(含有题目,答案,该题分数,指向下一节点的指针)
typedef struct _GF_questions{
	//gf_question代表填空题题目,gf_answer代表填空题答案
	char gf_question[GF_QUESTION],gf_answer[GF_ANSWER];
	//gf_score代表填空题分数(单精度浮点型)
	float gf_score;
	//next指向下一节点,说明指向下一道填空题
	struct _GF_questions *next;
}GF_questions;//GF_questions代表struct _GF_questions

//总题目结构体(含有判断题结构体,选择题结构体,填空题结构体,总题的满分值)
typedef struct _Timu{
	//tf_questions代表指向TF_question类型的指针
	TF_questions *tf_questions;
	//choice_questions代表指向Choice_questions类型的指针
	Choice_questions *choice_questions;
	//gf_questions代表指向GF_questions类型的指针
	GF_questions *gf_questions;
	//full_mark代表整套题的分数(单精度浮点类型)
	float full_mark;
}Timu;//Timu代表struct _Timu

//输入到stu.txt所需要的内容,从stu(clear)读取所需要的结构体
typedef struct _Student_timu{
	//Stu里面含有学生信息
	Student Stu;
	//stu_tf_answer代表该学生的判断题的所有答案
	char stu_tf_answer[ALL_ANSWER_LEN];
	//stu_choice_answer代表该学生的选择题的所有答案
	char stu_choice_answer[ALL_ANSWER_LEN];
	//stu_gf_answer代表该学生的填空题的所有答案
	char stu_gf_answer[ALL_ANSWER_LEN][GF_ANSWER];
	//stu_full_mark代表该学生这套题的分数(初始分数为0)
	float stu_full_mark;
}Student_timu;//Student_timu代表struct _Student_timu

//该链表可含有整个文件的学生身份和考试信息(用于从文件stu.txt中读取内容到这个链表中)
typedef struct _Student_timu_List{
	//stu_timu含有一个学生的身份信息和考试信息
	Student_timu stu_timu;
	//next指向下一节点,说明指向下一个学生
	struct _Student_timu_List *next;
}Student_timu_list;//Student_timu_list代表struct _Student_timu_List

stu *stu_list = NULL;//将学生身份信息链表置为空(NULL)
Timu timu = {NULL,NULL,NULL,0};//定义题目变量
Student_timu_list *student_timu_list = NULL;//将学生考试信息链表置为空(NULL)

//开始时读入学生信息文件
int read_id_studentinfo_file(void);
//将学生信息导入
Student_timu *creat_student_timu(stu *mark);
//读入考试内容
int read_timu_file(int flag);
//删除读入的考试内容
void delete_timu(void);
//保存学生信息
void save_id_studentinfo(void);
//在用户输入错误之后提示用户并对其进行重新输入
void input_again(void);
//输入字符串时输入0结束
int char_return_by_zero(char flag[]);
//吸收回车符
void take_in_line_break(void);
//学生登录界面
void student_login_menu(void);
//学生菜单
void student_menu(stu **mark);
//学生开始考试
void start_exam(Student_timu *student_timu,stu **mark);
//打印题目
void print_timu(int flag);
//计算成绩
float calculate_score(Student_timu *student_timu,int gf_questions_count);
//学生保存学生成绩到stu.txt上
void stu_save_stu(Student_timu *student_timu);
//老师保存成绩到stu.txt上
void tea_save_stu(int flag);
//学生修改密码
void change_password(stu **mark);
//学生交流功能
void stu_talking(stu *mark);
//教师菜单
void teacher_menu(void);
//教师发布考试
void post_examination(void);
//发布考试菜单
int post_exam_menu(int *i11,int *i22,int *i33);
//保存题目内容
void save_timu(int i11,int i22,int i33);
//老师初始化同学成绩为零
void initialize_grade(void);
//教师录入学生信息
void input_studentinfo(void);
//教师打印全部学生成绩
void print_studentinfo(void);
//按分数段自定义统计学生
void Custom_statistics(Student *ranking,int count);
//教师按学生学号排序
void id_rank(Student *ranking,int count);
//学号顺序排序
void id_order_rank(Student *ranking,int count);
//学号逆序排序
void id_reverse_order_rank(Student *ranking,int count);
//教师按成绩排序
void grade_rank(Student *ranking,int count);
//成绩顺序排序
void grade_order_rank(Student *ranking,int count);
//成绩逆序排序
void grade_reverse_order_rank(Student *ranking,int count);
//教师统计全部总分和平均分
void print_wholescore_and_avgscore(void);
//教师查看部分学生成绩
void seek_studentinfo(void);
//教师用学生学号查看学生成绩
void seek_by_id(void);
//教师用学生成绩高低查看学生成绩
void seek_by_name(void);
//教师修改学生信息
void modify_studentinfo(void);
//教师通过学号修改
void modify_by_id(void);
//教师通过姓名修改
void modify_by_name(void);
//教师删除学生身份信息
void remove_student_id_info(void);
//通过学号删除学生身份信息
void remove_id_by_id(void);
//通过姓名删除学生身份信息
void remove_id_by_name(void);
//删除学生考试信息
void remove_student_exam_info(void);
//通过学号删除学生考试信息
void remove_exam_by_id(void);
//通过名字删除学生考试信息
void remove_exam_by_name(void);
//将stu.txt文件读入学生考试信息链表
void read_stu_exam_list(void);
//将学生考试信息链表删除
void delete_stu_exam_list(void);
//保存信息到stu1.txt文件中
void save_stu1(int delete_stu_id);
//查看已被删除的学生考试信息
void print_stu_deleted_exam_info(void);
//老师交流功能
void tea_talking(void);
//接收消息
void receive_message(char filename[]);
//发送消息
void send_message(char filename[],char username[]);

//主函数
int main(int argc, char *argv[])
{
	read_id_studentinfo_file();//开始时读取学生信息文件
	int choice;//用来选择功能
	
	while(1)
	{
		printf("||==============================================||\n");
		printf("||\t欢迎使用学生英语成绩教育平台V1.0\t||\n");
		printf("||==============================================||\n");
		printf("||\t\t请选择模式\t\t\t||\n");
		printf("||==============================================||\n");
		printf("||\t\t1.学生模式\t\t\t||\n");
		printf("||\t\t2.教师模式\t\t\t||\n");
		printf("||\t\t3.退出系统\t\t\t||\n");
		printf("||==============================================||\n||");

		if(scanf("%d",&choice) != 1)//如果choice不为整数类型则进入if语句
		{
			input_again();//提示用户重新输入
			continue;//重新循环
		}

		switch (choice)
		{
			case 1://学生模式
				student_login_menu();//进入学生登录界面
				break;
			case 2://教师模式
				system("cls");
                teacher_menu();//进入教师界面
				break;
			case 3://退出系统
				printf("||——成功退出!——\n");
                exit(0);//退出程序
			default://其他输入
				input_again();//提示用户重新输入
				break;
		}
	}//while(1)循环
	return 0;
}

//将名为"studentinfo.txt"的文件读取到链表中
int read_id_studentinfo_file(void)
{
	//打开名为"studentinfo"的文本文件,并返回的指针赋给fpr
	FILE *fpr = fopen("studentinfo.txt","r");

	if(fpr == NULL)//打开失败时
		return 0;
	else//打开文件成功
		while(1)
		{
			stu *p = (stu*)malloc(sizeof(stu));
			//将文件内学生信息输入到链表中
			fscanf(fpr,"%d %s %s %s %d %f %d",&(p->Stu.id),p->Stu.name,
			p->Stu.class,p->Stu.majority,&(p->Stu.password),
			&(p->Stu.grade),&(p->Stu.examination_status));
            //先将文件输入，如果链表得到的数据时空的，这时候就能判断以及读取到文件末尾，虽然还是不能阻止多一次输入
			if(feof(fpr)) break;//读到末尾结束循环
            p->next = NULL;
            if(stu_list)//如果开头不为空,则将头给到p的末尾,再将头更新为p
	        {
			//头插法
            //假设插入9
	        //插入前：5->4->3->1->NULL
	        //插入后：9->5->4->3->1->NULL
	    	    p->next=stu_list;
	    	    stu_list=p;
		    }
		    else stu_list=p;//如果开头为空,则直接将p赋给开头
		    //假设插入7
		    //插入前:NULL
		    //插入后:7->NULL
		}
		fclose(fpr);//关闭文件
}

//输入0退出
//return_by_zero是一个返回整数类型的数的函数
//参数为一个整型数
//函数作用原理:如果得到的参数不为0则返回0,如果得到的参数为0则返回1,并提示用户退出成功
//用于在学生登陆界面、修改密码等功能时,输入0退出功能
int return_by_zero(int flag)
{
	if(flag == 0)
	{
		printf("||退出成功!\n||");
		system("pause");
		system("cls");
		return 1;
	}
	return 0;
}

//提示用户重新输入
void input_again(void)
{
	printf("||!【输入错误请重新输入】!\n||");
	take_in_line_break();//吸收回车符
	system("pause");//暂停给用户浏览信息
	system("cls");
}

//吸收输入换行符
void take_in_line_break(void)
{
	while(getchar() != '\n');//直到字符不为换行符(回车符)
}

//学生登陆界面
void student_login_menu(void)
{
	system("cls");
	int self_id,self_password,flag = 0;//定义学生输入的学号和密码,用flag判断学号和密码是否对的上
	stu *mark = stu_list;//定义一个stu类型的指针mark,并将开头给到mark
	
	while(1)
	{
		printf("||=====================================================||\n");
	    printf("||请输入你的学号(1000~9999)(输入0退出学生登录界面,同下)||\n||");//提示用户输入学号
	    if(scanf("%d",&self_id) != 1)//如果输入不为数字则进入if语句
	    {
	    	printf("||请输入四位整数\n");
		    input_again();//提示用户重新输入
		    continue;//重新开始循环
		}
 		//如果输入为0则退出学生登录界面
		if(return_by_zero(self_id))break;
		if( self_id >9999 || self_id < 1000)
		{
	    	printf("||请输入四位整数\n");
			input_again();//提示用户重新输入
		    continue;//重新开始循环
		}
		
		take_in_line_break();
		printf("||=====================================================||\n");
	    printf("||  请输入你的密码(四位数)(初始密码为1111)(输入0退出)  ||\n");
		printf("||=====================================================||\n||");
	    if(scanf("%d",&self_password) != 1)//如果输入不为数字则进入if语句
	    {
		    input_again();//提示用户重新输入
		    continue;//重新开始循环
		}
		//如果输入为0则退出学生登录界面
		if(return_by_zero(self_password))return;
		
		take_in_line_break();
		printf("||=====================================================||\n");
	    for(mark = stu_list;mark;mark = mark->next)//遍历链表
		    if(mark->Stu.id == self_id && mark->Stu.password == self_password)
		    //注意不要遗漏mark = stu_list不然,用户第二次输入时mark仍会指向链表末尾,导致输入错误
			{//判断学生输入的密码和学号是否匹配(用文件"studentInfo.txt"来做参考)
			    flag = 1;//如果匹配的上则将1赋给flag
			    break;
            }
	    if(flag)//如果flag为1,则加入语句
	    {
			printf("||——登录成功,进入学生菜单!——\n||");//提示用户登陆成功
			system("pause");//暂停给用户浏览信息
			system("cls");
			student_menu(&mark);
            //进入学生菜单(并且将得到的当前学生信息的地址传给函数)
            //传入的地址可用来修改,比如修改学生密码
			break;
	    }
	    else//如果flag为0,则说明匹配不上
	    {
	    	//提示用户输入错误,并提示用户下一步操作
			printf("||!【账号或密码错误】!\n||");
			system("pause");//暂停给用户浏览信息
			system("cls");
	    }
	}
	system("cls");
}

//学生菜单
void student_menu(stu **mark)
{
	//creat_student_timu是返回Student_timu类型指针的函数
	//将当前学生的身份信息导入
	Student_timu student_timu = *creat_student_timu(*mark);
	int choice;//用于用户的选择
	
	while(1)
	{
		system("cls");
		printf("||=======================================================================================||\n");
		printf("||\t\t当前为学生模式\t\t\t\t\t\t\t\t ||\n");
		printf("||=======================================================================================||\n");
		printf("||学号\t\t姓名\t\t班级\t\t专业\t\t考试状态\t分数\t ||\n");
		printf("||=======================================================================================||\n");
		printf("||%d\t\t%s\t\t%s\t\t%s\t\t%d\t\t%.2f\t ||\n",(*mark)->Stu.id,(*mark)->Stu.name,(*mark)->Stu.class,
		(*mark)->Stu.majority,(*mark)->Stu.examination_status,(*mark)->Stu.grade);
		//通过得到的学生信息,将学生的信息打印出来(来确保用户是否登录到自己的账号)
		printf("||=======================================================================================||\n");
		printf("||\t\t请选择功能\t\t\t\t\t\t\t\t ||\n");//提示用户选择功能
		printf("||=======================================================================================||\n");
		printf("||\t\t1.开始考试\t\t\t\t\t\t\t\t ||\n");
		printf("||\t\t2.查看成绩\t\t\t\t\t\t\t\t ||\n");
		printf("||\t\t3.交流功能\t\t\t\t\t\t\t\t ||\n");
		printf("||\t\t4.修改密码\t\t\t\t\t\t\t\t ||\n");
		printf("||\t\t5.返回总菜单\t\t\t\t\t\t\t\t ||\n");
		printf("||=======================================================================================||\n||");

		if(scanf("%d",&choice) != 1)//如果choice不是整数类型则进入if语句
		{
			input_again();//提示用户程序输入
			continue;//重新循环
		}
		take_in_line_break();

		switch (choice)
		{
			case 1://学生开始考试
                //start_exam是不带返回值的函数,传入student_timu的地址,可以对student_timu的内容进行操作
                //如将学生考试状态改成1
				start_exam(&student_timu,mark);
				break;
			case 2://学生查看成绩
                //print_studentinfo是不带返回值的函数,也无形参
				print_studentinfo();
				break;
			case 3://学生交流功能
                //stu_talking是不带返回值的函数,形参*mark的作用是将学生的信息带进去
                //*mark内的名字用来标注发言人
				stu_talking(*mark);
				break;
			case 4://学生修改密码
                //将二级指针mark带进去来修改密码
				change_password(mark);
				break;
			case 5://返回总菜单
			    printf("||——成功返回——\n");
                return;
			default ://其他输入都为错误输入,这会提示用户重新输入
				input_again();
				break;
		}
	}
}

//将学生信息导入
Student_timu *creat_student_timu(stu *mark)
{
    Student_timu *p = (Student_timu *)malloc(sizeof(Student_timu));
	p->Stu = mark->Stu;//将mark中的结构体Stu信息带到p上然后返回p

	return (p);
	free(p);//释放p
	p = NULL;//避免悬空指针
}

//读取考试内容
//read_timu_file函数是一个返回整型类型的函数,函数会返回1和0,返回1则说明有题目,返回0则说明没题目或者打开文件失败
//flag用来判断使用函数的操作用户是学生用户还是教师用户,1是学生用户,2是教师用户
int read_timu_file(int flag)
{
	//以只读的方式打开名为"timu(clear)"的文本文件,并将返回的指针赋给fpr
	FILE *fpr = fopen("timu(clear).txt","r");
	//i1,i2,i3用来分别读取判断题,选择题,填空题的数目
	//i01,i02,i03用来循环打印题目,ch用来判断文件是否为空,i用来辅助文件读入,j辅助读入选择题选项
	int i = 0,j = 0,i1 = 0,i2 = 0,i3 = 0,i01 = 0,i02 = 0,i03 = 0,ch = 0;
	char temp;//temp用于临时储存文件的一个字符,判断是否得到的字符有异常或者是否为读取结束符

	if(fpr == NULL)//打开失败时
		return 0;
	else
	{
		ch = fgetc (fpr);//ch读取文件中的第一个字符
		fseek(fpr,0,SEEK_SET);//重新回到文件开头
		//分别给i1,i2,i3赋上判断题,选择题,填空题的题数
		fscanf(fpr,"%d,%d,%d\n",&i1,&i2,&i3);
		
		if(flag == 1)//如果flag为1,则进入if语句,flag为1表示该用户为学生用户
		{
			//如果读入文件的第一个字符为空,或则读入的题数都为0,则进入if语句
		    if(ch == EOF || (i1 == 0) && (i2 == 0) && (i3 == 0))
		    {
		    	system("cls");
			    printf("——老师暂未发布考试——\n");//提示用户老师暂未发布考试
		 	    return 0;
		    }
		}
		if(flag == 2)//如果flag不为2,则进入if语句,flag为2表示该用户为教师用户
			//如果读入文件的第一个字符为空,或则读入的题数都为0,则进入if语句
		    if(ch == EOF || (i1 == 0) && (i2 == 0) && (i3 == 0))
		    {
		    	system("cls");
			    printf("——暂未录入考试信息——\n");//提示用户老师暂未发布考试
			    system("pause");//暂停给用户浏览信息
			    system("cls");
		 	    return 0;
		    }
		//i01(表示当前打印出来的题目数)开始为0,当i01小于i1(总判断题数)时退出while循环
		while(i01 < i1)
		{
			//给p1分配TF_questions类型的指针
			TF_questions *p1 = (TF_questions *)malloc(sizeof(TF_questions));
			if(p1 == NULL)//如果分配失败则进入if语句
			{
				printf("||分配内存失败,不能打印判断题题目\n||");//提示用户分配内存失败
				break;//跳出当前while循环
			}
			
			//如果分配内存成功,则在文件中读去判断题信息(如题目、答案和分数)
			//读取判断题题目
			for(i = 0;;i++)
			{
                //temp暂时存储读取文件的字符
				temp = fgetc(fpr);
				if(temp == EOF)
				{
					//提示用户错误原因
					printf("读取错误\n");
					system("pause");//暂停给用户浏览信息
					system("cls");
					break;
				}
				if(temp == 35)break;
				p1->tf_question[i] = temp;
			}
			//将有效字符最末尾置为'\0'
			p1->tf_question[i] = '\0';
			
			//读取该判断题答案
			p1->tf_answer[0] = fgetc(fpr);
			p1->tf_answer[1] = '\0';
			//在读取判断题答案和分值之间的字符
			temp = fgetc(fpr);

            //读取该判断题分值以及换行符(读取换行符的作用是用于读取下一题)
	        fscanf(fpr,"%f\n",&(p1->tf_score));
			if(feof(fpr)) break;//如果读到文件末尾则结束当前循环
			p1->next = NULL;//给p1指针的next赋为NULL(避免野指针)
			if(timu.tf_questions)//如果链表timu.tf_questions的头节点不为空,则进入if语句
			{
			    //定义TF_questions类型的指针p指向timu.tf_questions的头节点
				TF_questions *p = timu.tf_questions;
                //for的作用:将指针p用for循环指向链表timu.tf_questions的末尾
                //假如链表现在的链表为3->2->9->1->NULL
				//开始for循环前p指向3，p->next指向2
				//for循环结束后p指向1,p->next指向NULL
				for(;p->next;p = p->next);
				p->next = p1;//将p1赋给p->next指向的NULL
			}
			//如果链表timu.tf_questions的头节点为空,则加入else语句
			//将p1赋给头节点
			else timu.tf_questions = p1;
			i01++;//i01加1,用于进行while语句判断是否打印下一道判断题
		}
		if(temp == EOF)return 0;
		
 		//i02(表示当前打印出来的题目数)开始为0,当i02小于i2(总判断题数)时退出while循环
		while(i02 < i2)
		{
			//给p2分配Choice_questions类型的指针
			Choice_questions *p2 = (Choice_questions *)malloc(sizeof(Choice_questions));
			if(p2 == NULL)//如果分配失败则进入if语句
			{
				printf("||分配内存失败,不能打印判断题题目\n||");//提示用户分配内存失败
				break;//跳出当前while循环
			}
            //如果分配内存成功,则在文件中读去选择题信息(如题目、选项a.b.c.d、答案和分数)
            //读取选择题题目
			for(i = 0;;i++)
			{
				//temp暂时储存在文件中读取的第一个字符
				temp = fgetc(fpr);
				if(temp == EOF)
				{
					//提示用户错误的原因
					printf("读取错误\n");
					system("pause");//暂停给用户浏览
					system("cls");
					break;
	}
				if(temp == 35)break;
				p2->choice_question[i] = temp;
			}
			//将有效字符最末尾置为'\0'
			p2->choice_question[i] = '\0';
			
			//定义一个二维数组来储存选择题的四个选项
			char Option_all[4][OPTION];
			
			//读取选择题各个选项
			//j代表ABCD选项
			for(j = 0;j < 4;j++)
			{
				//i代表选项中的各个字符
				for(i = 0;;i++)
				{
					//temp暂时储存读取文件的字符
					temp = fgetc(fpr);
					if(temp == EOF)
					{
						//提示用户错误的原因
						printf("读取错误\n");
					    system("pause");//暂停给用户浏览
					    system("cls");
					    break;
					}
					if(temp == 35)break;
					Option_all[j][i] = temp;
				}
				if(temp == EOF)break;
				//给选项的有效字符的末尾赋为'\0'
                Option_all[j][i] = '\0';
			}
			
			//读取该选择题的答案
			p2->cq_answer[0] = fgetc(fpr);
			p2->cq_answer[1] = '\0';
			//读取答案和分值之间的字符
			temp = fgetc(fpr);
			
			//分别将Option_all的各个元素复制给p2所指的各个ABCD选项
		    strcpy(p2->option.option_a,*Option_all);
		    strcpy(p2->option.option_b,*(Option_all+1));
		    strcpy(p2->option.option_c,*(Option_all+2));
		    strcpy(p2->option.option_d,*(Option_all+3));
			
			//读取该选择题分值以及换行符(读取换行符的作用是用于读取下一题)
			fscanf(fpr,"%f\n",&p2->cq_score);
			if(feof(fpr))break;//如果读到文件末尾则结束当前循环
			p2->next = NULL;//给p2指针的next赋为NULL(避免野指针)
			if(timu.choice_questions)//如果链表timu.choice_questions的头节点不为空,则进入if语句
			{
				//定义Choice_questions类型的指针p指向timu.choice_questions的头节点
				Choice_questions *p = timu.choice_questions;
				//for的作用:将指针p用for循环指向链表timu.choice_questions的末尾
                //假如链表现在的链表为2->4->11->3->NULL
				//开始for循环前p指向3，p->next指向4
				//for循环结束后p指向3,p->next指向NULL
				for(;p->next;p = p->next);
				p->next = p2;//将p2赋给p->next指向的NULL
			}
			//如果链表timu.choice_questions的头节点为空,则加入else语句
			//将p2赋给头节点
			else timu.choice_questions = p2;
			i02++;//i02加1,用于进行while语句判断是否打印下一道选择题
		}
 		if(temp == EOF)return 0;
		
		//i03(表示当前打印出来的题目数)开始为0,当i03小于i3(总判断题数)时退出while循环
		while(i03 < i3)
		{
			//给p3分配GF_questions类型的指针
			GF_questions *p3 = (GF_questions *)malloc(sizeof(GF_questions));
  			if(p3 == NULL)//如果分配失败则进入if语句
			{
				printf("||分配内存失败,不能打印判断题题目\n||");//提示用户分配内存失败
				break;//跳出当前while循环
			}
            //如果分配内存成功,则在文件中读去填空信息(如题目、答案和分数)
            //读取填空题题目
			for(i = 0;;i++)
			{
				//暂temp时储存文件中读取的字符
				temp = fgetc(fpr);
				if(temp == EOF)
				{
					//提示用户错误的原因
					printf("读取错误\n");
					system("pause");//暂停给用户浏览
					system("cls");
					break;
				}
				if(temp == 35)break;
				p3->gf_question[i] = temp;
			}
			//将有效字符最末尾置为'\0'
			p3->gf_question[i] = '\0';

			//读取填空题的标准答案
			for(i = 0;;i++)
			{
				temp = fgetc(fpr);
				if(temp == EOF)
				{
					//提示用户错误原因
					printf("读取失败\n");
					system("pause");//暂停给用户浏览
					system("cls");
					break;
				}
				if(temp == 35)break;
				p3->gf_answer[i] = temp;
			}
			//将有效字符最末尾置为'\0'
			p3->gf_answer[i] = '\0';
			
			//读取该填空题分值以及换行符(读取换行符的作用是用于读取下一题)
			fscanf(fpr,"%f\n",&p3->gf_score);
			if(feof(fpr))break;//如果读到文件末尾则结束当前循环
			p3->next = NULL;//给p3指针的next赋为NULL(避免野指针)
			if(timu.gf_questions)//如果链表timu.gf_questions的头节点不为空,则进入if语句
			{
				//定义GF_questions类型的指针p指向timu.gf_questions的头节点
				GF_questions *p = timu.gf_questions;
   				//for的作用:将指针p用for循环指向链表timu.gf_questions的末尾
                //假如链表现在的链表为32->1->10->34->NULL
				//开始for循环前p指向32，p->next指向1
				//for循环结束后p指向34,p->next指向NULL
				for(;p->next;p = p->next);
				p->next = p3;//将p3赋给p->next指向的NULL
			}
  			//如果链表timu.gf_questions的头节点为空,则加入else语句
			//将p3赋给头节点
			else timu.gf_questions = p3;
			i03++;//i03加1,用于进行while语句判断是否打印下一填空题
		}
 		if(temp == EOF)return 0;
		//将文件中该考试的满分分值读到timu.full_mark
		fscanf(fpr,"%f\n",&timu.full_mark);

		return 1;//返回1表示文件有题目
	}

	fclose(fpr);//关闭文件
}

//学生开始考试
//start_exam是不返回值的函数
//形参一个是Student_timu类型的指针用来保存学生用户的答题记录
//另一个是Stu类型的二重指针mark,用来修改考试状态和保存学生成绩
void start_exam(Student_timu *student_timu,stu **mark)
{
	TF_questions *p111 = NULL;//用来末尾总览判断题题目(同下)
	Choice_questions *p222 = NULL;
	GF_questions *p333 = NULL;
	//tf_questions_count,Choice_questions_count,gf_questions_count分别标记判断题,选择题和填空题的题数
	//i则用来循环核对学生判断和选择题答案和给学生输入填空题答案,choice用来选择要修改的题目
	int tf_questions_count = 0,Choice_questions_count = 0,gf_questions_count = 0,i = 0,count = 0,choice = 0;

	//read_timu_file函数作用是读取"timu(clear)"文本文件中的题目,用于后面print_timu打印题目
	//read_timu_file函数里面的形参为1代表,读取的用户为学生用户,read_timu_file函数返回的值如果为0则进入if语句
	if(!read_timu_file(1))
	{
		printf("||!【考试信息读取失败】!\n||");//提示用户信息读取失败
		system("pause");//暂停给用户浏览信息
		system("cls");
		return;//回到学生菜单
	}
	//以只读的方式打开名为"timu(clear)"的文本文件,并将返回的指针赋给fpr
	FILE *fpr = fopen("timu(clear).txt","r");
    //在文件中读取填空题的题目数
	fscanf(fpr,"%d,%d,%d",&tf_questions_count,&Choice_questions_count,&gf_questions_count);
	fclose(fpr);//关闭文件
	
	//examination_status代表该生的考试状态,如果等于1则进入语句
	if((*mark)->Stu.examination_status == 1)
	{
		//提示该用户已经考过试了,不能再考试了
		printf("！！！【——检测到你已经考试了,所以不可以再次考试了——】！！！\n");
		system("pause");//暂停给用户浏览
		system("cls");
		return;//返回学生菜单
	}
    (*mark)->Stu.examination_status = 1;//如果考试状态为0,则将其赋为1,然后开始下面的考试
    system("cls");
    print_timu(4);
    system("pause");
    system("cls");
    
	do
	{
		system("cls");
	    print_timu(1);//打印这套题的题目
	    printf("=============================\n");
	    printf("||请输入判断题答案(如YNNYNY)\n||");//提示用户输入判断题答案
	    //如果输入的答案为回车则进入while循环继续继续答案的输入知道输入的答案不为回车(同下)
	    while(strcmp(gets(student_timu->stu_tf_answer),"\n") <= 0)
	        printf("||");//||为了和最左边对齐(同下)
		count = 0;
        for(i = 0;i < tf_questions_count;i++)
        	if(student_timu->stu_tf_answer[i] != 'Y'&&student_timu->stu_tf_answer[i] != 'N')
				count++;
		if(count)
		{
		    printf("||你有%d道题不符合填写要求,需要重新填写\n||",count);
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
	    printf("||请输入选择题答案(如AACDBA)\n||");//提示用户输入选择题答案
	    while(strcmp(gets(student_timu->stu_choice_answer),"\n") <= 0)
	        printf("||");
	 	count = 0;
	    for(i = 0;i < Choice_questions_count;i++)
			if(student_timu->stu_choice_answer[i] != 'A' && student_timu->stu_choice_answer[i] != 'B' && student_timu->stu_choice_answer[i] != 'C' && student_timu->stu_choice_answer[i] != 'D')
				count++;
			//以下为过长的代码
			//_choice_answer[i] != 'B' && student_timu->stu_choice_answer[i
			//] != 'C' && student_timu->stu_choice_answer[i] != 'D')
   		if(count)
		{
		    printf("||你有%d道题不符合填写要求,需要重新填写\n||",count);
		    system("pause");
		    continue;
		}
		student_timu->stu_choice_answer[i] = '\0';
		break;
    }while(1);
    
    system("cls");
    print_timu(3);
	//初始化i=0,进入for循环,如果i小于填空题题目数则继续循环,否则结束循环
	for(i = 0;i < gf_questions_count;i++)
	{
		printf("=============================\n");
	    printf("||请输入第%d道填空题答案\n||",i+1);
 	    while(strcmp(gets(student_timu->stu_gf_answer[i]),"\n") <= 0)
	        printf("||");
	}
	printf("||===================================\n");
	//提示用户是否进行修改,如果要修改则输入y,如过不修改则输入其他字符
	printf("||答题完毕\n||");
	system("pause");
	system("cls");

	do//死循环,但是这是作用于如果choice输入错误用的,最后有个break用于结束循环
	{
		system("cls");
		printf("||==============================||\n");
		printf("||你需要修改吗?\t\t\t||\n");//提示用户选择功能
		printf("||==============================||\n");
		printf("||若要修改则输入你要修改的题型  ||\n");
		printf("||若不需要则输入4\t\t||\n");
		printf("||==============================||\n");
	    printf("||1.判断题\t\t\t||\n");
	    printf("||2.选择题\t\t\t||\n");
	    printf("||3.填空题\t\t\t||\n");
	    printf("||4.不做修改\t\t\t||\n");
	    printf("||==============================||\n||");
		
	    if(scanf("%d",&choice) != 1)//如果choice不为整数类型则进入if语句
	    {
		    input_again();//提示用户重新输入
		    continue;//重新循环
	    }
	    take_in_line_break();
	    system("cls");

		switch(choice)//选择功能
		{
		  	case 1:
			 	do
	            {
		            system("cls");
	                print_timu(1);//打印这套题的题目
	                printf("=============================\n");
	                printf("||请输入判断题答案(如YNNYNY)\n||");//提示用户输入判断题答案
	                //如果输入的答案为回车则进入while循环继续继续答案的输入知道输入的答案不为回车(同下)
	                while(strcmp(gets(student_timu->stu_tf_answer),"\n") <= 0)
	                    printf("||");//||为了和最左边对齐(同下)
		            count = 0;
                    for(i = 0;i < tf_questions_count;i++)
        	            if(student_timu->stu_tf_answer[i] != 'Y'&&student_timu->stu_tf_answer[i] != 'N')
				            count++;
		            if(count)
		            {
		                printf("||你有%d道题不符合填写要求,需要重新填写\n||",count);
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
	                printf("||请输入选择题答案(如AACDBA)\n||");//提示用户输入选择题答案
	                while(strcmp(gets(student_timu->stu_choice_answer),"\n") <= 0)
	                    printf("||");
	 	            count = 0;
	                for(i = 0;i < Choice_questions_count;i++)
			            if(student_timu->stu_choice_answer[i] != 'A' && student_timu->stu_choice_answer[i] != 'B' && student_timu->stu_choice_answer[i] != 'C' && student_timu->stu_choice_answer[i] != 'D')
				            count++;
   		            if(count)
		            {
		                printf("||你有%d道题不符合填写要求,需要重新填写\n||",count);
		                system("pause");
		                continue;
		            }
		            student_timu->stu_choice_answer[i] = '\0';
		            break;
                }while(1);
	            break;
	        case 3:
		 		printf("||==============================||\n||");
	        	printf("你要修改第几道填空题答案?\n||");//提示用户输入填空题答案
		  		if(scanf("%d",&i) != 1)//如果i不为整数类型则进入if语句
		        {
		            printf("||输入不能为非数字\n");//提示用户出错原因
			        input_again();//提示用户重新输入
			        continue;//重新循环
		        }
		        else
					if(i > gf_questions_count || i <= 0)
					{
						//如果输入的数字为整数但是不在题目数范围内也进入if语句
					    //提示用户出错原因
						printf("||输入的题数要求在有效题目数范围内(1~%d)\n",gf_questions_count);
	  			        input_again();//提示用户重新输入
			            continue;//重新循环
					}
	            take_in_line_break();
	            printf("||请输入第%d道填空题答案\n||",i);
 	            while(strcmp(gets(student_timu->stu_gf_answer[i-1]),"\n") <= 0)
	                printf("||");
	            break;
            case 4://如果输入4则退出循环返回学生菜单
            	system("cls");
				break;
			default://如果其他字符则进入input_again语句重新输入
			 	input_again();
				break;
		}
		printf("||修改成功\n||");
		system("pause");
		if(choice == 4)break;
	}while(1);
	
   	printf("||答题完毕\n");//用于提示用户答题完毕
    printf("||计算ing......\n");//用于提示用户正在计算成绩
    //将学生成绩赋值
    (*mark)->Stu.grade = calculate_score(student_timu,gf_questions_count);
    student_timu->Stu.examination_status = 1;
    student_timu->Stu.grade = (*mark)->Stu.grade;
	printf("||保存信息ing......\n");//提示用户正在保存信息
	stu_save_stu(student_timu);//保存学生的题目信息(将学生题目带到函数里面进行操作)
	save_id_studentinfo();//保存学生信息
	delete_timu();//删除题目链表中的题目
}

//打印题目
void print_timu(int flag)
{
	TF_questions *p111 = NULL;//指向TF_questions类型的指针p111定义用来末尾总览判断题题目(同下)
	Choice_questions *p222 = NULL;
	GF_questions *p333 = NULL;
	int i1 = 0,i2 = 0,i3 = 0,i = 0,count = 0;//count用来打印题号,i用来循环给学生输入填空题答案

    //以只读的方式打开名为"timu(clear)"的文本文件,并将返回的指针赋给fpr
	FILE *fpr = fopen("timu(clear).txt","r");
	if(fpr == NULL)
	{
		printf("||读取题目文件失败\n||");
		system("pause");
		system("cls");
		return;
	}
	//用i1,i2,i3分别读取判断题、选择题和填空题的题目数
	fscanf(fpr,"%d,%d,%d",&i1,&i2,&i3);
	fclose(fpr);//关闭文件
	
	if(flag == 4)
	{
	    printf("||=====================================\n");
	    printf("||题目总览:\n");//提示用户整套题目
	    //以下都是这一整套题
	    printf("||一、判断题\n");
	    //将将p111指向timu.tf_questions的头节点,当p111为空时结束for循环
	    for(p111 = timu.tf_questions,count = 0;p111;p111 = p111->next,count++)
	    //打印出来的效果比如:||1.This is a egg.
	    //                   ||分值:3.000000
	    //                   ||
	    //                   ||2.This is an egg.
	    //......................................................
		    printf("||%d.%s\n||分值:%f\n||\n",count+1,p111->tf_question,p111->tf_score);
	    printf("||二、选择题\n");
	    for(p222 = timu.choice_questions,count = 0;p222;p222 = p222->next,count++)
	    //打印出来的效果比如:||1.What color is this?
	    //                   ||选项:A:red.    B:blue.    C:yellow.    D:black.
	    //                   ||分值:3.000000
	    //                   ||
	    //                   ||2.What color does Gogo like?
	    //......................................................
            printf("||%d.%s\n||选项:A:%s.   B:%s.   C:%s.   D:%s.\n||分值:%f\n||\n",
			count+1,p222->choice_question,p222->option.option_a,p222->option.option_b,
			p222->option.option_c,p222->option.option_d,p222->cq_score);
	    printf("||三、填空题\n");
	    for(p333 = timu.gf_questions,count = 0;p333;p333 = p333->next,count++)
	    //打印出来的效果比如:||1.This is a ____.
	    //                   ||分值:3.000000
	    //                   ||
	    //                   ||2.I like ___.
	    //......................................................
		    printf("||%d.%s\n||分值:%f\n||\n",count+1,p333->gf_question,p333->gf_score);
	    //提示用户该卷的题目数和满分信息
	    printf("||目前题数:%d\t目前满分:%.2f\n",i1+i2+i3,timu.full_mark);
	    printf("||====================================\n||");
	}
	if(flag == 1)
	{
 	    printf("||一、判断题\n");
	    //将p111指向timu.tf_questions的头节点,当p111为空时结束for循环
	    for(p111 = timu.tf_questions,count = 0;p111;p111 = p111->next,count++)
		    printf("||%d.%s\n||分值:%f\n||\n",count+1,p111->tf_question,p111->tf_score);
	}
	if(flag == 2)
	{
 	    printf("||二、选择题\n");
	    for(p222 = timu.choice_questions,count = 0;p222;p222 = p222->next,count++)
            printf("||%d.%s\n||选项:A:%s.   B:%s.   C:%s.   D:%s.\n||分值:%f\n||\n",
			count+1,p222->choice_question,p222->option.option_a,p222->option.option_b,
			p222->option.option_c,p222->option.option_d,p222->cq_score);
	}
	if(flag == 3)
	{
 	    printf("||三、填空题\n");
	    for(p333 = timu.gf_questions,count = 0;p333;p333 = p333->next,count++)
		    printf("||%d.%s\n||分值:%f\n||\n",count+1,p333->gf_question,p333->gf_score);
	}
}

//计算成绩
//calculate_score是个返回一个单精度浮点型数的函数,该数为计算出来之后的学生成绩
//函数第一个形参指向Student_timu类型的指针student_timu,该指针指向当前学生的考试信息,用于函数内部答案的核对批改
//函数第二个形参时一个整型数gf_questions_count,循环核对填空题的答案
float calculate_score(Student_timu *student_timu,int gf_questions_count)
{
	//i1,i2,i3用来对题目往后递归
	int i1,i2,i3;
	TF_questions *p1 = NULL;//定义指向TF_questions类型的指针变量p1,用于浏览判断题题目(同下)
	Choice_questions *p2 = NULL;
	GF_questions *p3 = NULL;

    //首先将学生的分赋值为零
    student_timu->stu_full_mark = 0;
    //判断题答案核对见下图,选择题和填空题同理
    //假设学生答案:YYNYNNY(注意此时答案是连在一起的,为一个数值)
	//标准答案为:YYYYNNN(注意该答案其实是一个链表相互连接的,即Y->Y->Y->Y->N->N->N->NULL)
    //开始i0 = 0，p1指向timu.tf_questions的首地址(即Y的地址)
	//判断student_timu->stu_tf_answer[i1]是否为'\0'(如果是则结束for循环,进入下一个语句;否则进入循环)
	//如果学生答案第i1个元素(即student_timu->stu_tf_answer[i1])等于p1所指的判断题答案的第一个元速,则进入if语句
	//如果进入if语句学生的分数会增加当前p1所指的节点的分数(即该题的分值),然后进入下一步
	//if语句结束后或者跳过if语句之后i1加1,p1指向当前节点所指向的下一个节点
	//然后再次进入for语句的判断条件
	for(p1 = timu.tf_questions,i1 = 0;student_timu->stu_tf_answer[i1] != '\0';i1++,p1 = p1->next)
        if(student_timu->stu_tf_answer[i1] == p1->tf_answer[0])
        	student_timu->stu_full_mark += p1->tf_score;
	for(p2 = timu.choice_questions,i2 = 0;student_timu->stu_choice_answer[i2];i2++,p2 = p2->next)
		if(student_timu->stu_choice_answer[i2] == p2->cq_answer[0])
			student_timu->stu_full_mark += p2->cq_score;
	for(p3 = timu.gf_questions,i3 = 0;i3 < gf_questions_count;i3++,p3 = p3->next)
		if(strcmp(student_timu->stu_gf_answer[i3],p3->gf_answer) == 0)
			student_timu->stu_full_mark += p3->gf_score;
	printf("||——计算完成!——\n");//提示用户计算完成
	
	return student_timu->stu_full_mark;//返回计算之后学生的分数
}

//保存学生答题信息
//stu_save_stu是一个不返回值的函数
//形参是一个指向Student_timu类型的指针student_timu
//用于将学生考试信息以在末尾追加的方式导入到名为"stu"和"stu(clear)"的文件
void stu_save_stu(Student_timu *student_timu)
{
	read_stu_exam_list();
	//以只写的方式分别打开到名为"stu"和"stu(clear)"的文件,并将返回的指针分别赋给fpw1和fpw2
	FILE *fpw1 = fopen("stu(clear).txt","w");
	FILE *fpw2 = fopen("stu.txt","w");
	//i用于循环将学生填空题答案输入,gf_questions_count用于标记填空题的题目数
	int i = 0,gf_questions_count = 0;
	Student_timu_list *p = student_timu_list;
	Student_timu_list *p1 = student_timu_list;

    //以只读的方式将名为"timu(clear)"的文件,并将返回的指针赋给fpr
	FILE *fpr = fopen("timu(clear).txt","r");
	if(fpr == NULL)
	{
		printf("||保存文件失败\n||");
		system("pause");
		system("cls");
		return;
	}
	//读取填空题题目数
	fscanf(fpr,"%*d,%*d,%d",&gf_questions_count);
	fclose(fpr);//关闭文件
	
	//首先打印到"stu"文本文件上(stu用于浏览)
	
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

	fprintf(fpw2,"专业******班级*****学号******姓名******成绩******学生判断题答案*****学生选择题答案*****学生填空题答案\n");
	for(p1 = student_timu_list;p1;p1 = p1->next)
	{
	    fprintf(fpw2,"%s\t%s\t%d\t%s\t%f\t%s\t\t%s\t\t",p1->stu_timu.Stu.majority,
		p1->stu_timu.Stu.class,p1->stu_timu.Stu.id,p1->stu_timu.Stu.name,
		p1->stu_timu.Stu.grade,p1->stu_timu.stu_tf_answer,p1->stu_timu.stu_choice_answer);
	    for(i = 0;i < gf_questions_count;i++)
		    fprintf(fpw2,"(%d).%s\t",i+1,p1->stu_timu.stu_gf_answer[i]);
	    fprintf(fpw2,"\n");
	}

	fclose(fpw2);//关闭"stu(clear)"文件
	delete_stu_exam_list();
}

//删除题目内容(用于删除全局变量timu)
//delete_timu是不返回值的函数,也无形参
void delete_timu(void)
{
	TF_questions *p1 = timu.tf_questions;
	Choice_questions *p2 = timu.choice_questions;
	GF_questions *p3 = timu.gf_questions;
	
	if(p1 == NULL || p2 == NULL || p3 == NULL)//如果p1、p2和p3得到的指针的为空进入语句
	{//进入ifp1、p2、p3其中有分配内存失败
		printf("||!【保存文件失败】!\n||");
		system("pause");//暂停给用户浏览
		return;//返回
	}
	
	//以判断题为例,下面的选择题和填空题也一样
	//如果p1的不为空,则进入if语句(说明链表头不为空)
	while(p1)
	{
		//将指针p1赋给p11
        TF_questions *p11 = p1;
        //然后将指针p1指向下一个节点的头
        p1 = p1->next;
        //然后将当前的头节点释放,此时原来第二个节点变为头(也就是第一个节点)
        free(p11);
        p11 = NULL;
	}
    //最后再把头节点置为空,这样就完成了将判断题链表的的内容全部删除了
    timu.tf_questions = NULL;

    //操作同判断题
	while(p2)
	{
        Choice_questions *p22 = p2;
        p2 = p2->next;
        free(p22);
        p22 = NULL;
	}
    timu.choice_questions = NULL;
		
    //操作同判断题
	while(p3)
	{
        GF_questions *p33 = p3;
        p3 = p3->next;
        free(p33);
        p33 = NULL;
	}
	timu.gf_questions = NULL;
	
	//最后将卷子满分置为0(来表示该卷没有题目)
	timu.full_mark = 0;
}

//学生修改密码
//change_password是一个不带返回值的函数,形参mark是一个二级指针,是用来传入地址带改变值的
void change_password(stu **mark)
{
	//new_password用于输入学生的新密码,re_new_password用于学生再次确定密码
	//flag则是用来判断第一次和第二次输入的密码是否一致,还有用于判断输入的密码是否满足要求
	int new_password,re_new_password,flag = 1;
	
	system("cls");
	printf("||======================================================================||\n");
	printf("||你当前的密码为%d\n",(*mark)->Stu.password);//提示用户当前的密码
	
	do
	{
		//如果flag为0则进入if语句
		if(flag == 0)
		{
			printf("||======================================================================||\n");
			//提示用户错误的内容,并要求重新输入第一次内容
			printf("||前后新密码不一致!!!请重新输入第一次新密码(仅限四位数)(输入0退出程序)  ||\n||");
		}
		//如果flag为1则进入if语句
		if(flag == 1)
		{
			printf("||======================================================================||\n");
			//提示用户输入自己想要改变的新密码
	        printf("||请输入你的新密码(仅限四位数)(输入0退出程序)\n||");
	    }
	    
 		if(scanf("%d",&new_password) != 1)//如果new_password不为整数类型则进入if语句
		{
			input_again();//提示用户重新输入
			continue;//重新循环
		}
		//此时if语句出来的new_password为整数类型
	    take_in_line_break();
	    system("cls");
	    
	    //调用return_by_zero函数来退出该功能
	    //作用原理:函数得到用户输入的数(即new_password)
		//如果用户为0则会提示用户退出成功并暂停且返回1,否则返回0
	    //如果返回值为1,则进入if语句;如果返回值为0,则跳过if语句
	    if(return_by_zero(new_password))return;
	    //如果第一次输入的密码符合要求和进入if语句,否则跳过if语句
	    if(new_password < 10000 && new_password > 999)
	    {
			do//该死循环用于循环输入第二次新密码,此时得到的第二次新密码为整数类型
			{
	    	    //提示用户第二次输入新密码
		        printf("||请再次输入你的新密码(输入0退出程序)\t\t\t\t\t||\n||");
		        if(scanf("%d",&re_new_password) != 1)//如果re_new_password不为整数类型则进入if语句
		        {
			        input_again();//提示用户重新输入
			        continue;//重新循环
		        }
	            take_in_line_break();
	            break;//退出死循环
	        }while(1);
	        
	        //调用return_by_zero函数来退出该功能
	        //作用原理:函数得到用户输入的数(即re_new_password)
			//如果用户为0则会提示用户退出成功并暂停且返回1,否则返回0
	        //如果返回值为1,则进入if语句;如果返回值为0,则跳过if语句
	        if(return_by_zero(re_new_password))return;
	        
            //如果第二次输入的新密码为四位数则进入语句
	        if(re_new_password < 10000 && re_new_password > 999)
	        {
	        	//判断第一次和第二次输入的新密码是否一致,如果不一致则进入if语句,否则跳过语句
			    if(new_password != re_new_password)
			    {
			    	//如果不一致则将flag置为0,接着继续循环
			    	flag = 0;
			    	continue;
			    }
			    //此时第一次和第二次输入的密码一致,退出循环,退出循环之后就将学生的密码置为新密码
		        break;
            }
            
            //如果第二次输入的新密码不为四位数则进入else语句
            else
			{
				//提示用户输入错误的原因
			    printf("||输入的新密码不符合要求(要求四位整数)\t\t\t\t\t||\n");
			    printf("||======================================================================||\n");
			    flag = 0;//将flag置为0
			}
	    }
	    
	    //如果第一次输入的新密码不为四位数则进入语句
	    else
		{
			//提示用户输入错误的原因
		    printf("||输入的新密码不符合要求(要求四位整数)\t\t\t\t\t||\n");
		    printf("||======================================================================||\n");
		}
	    system("pause");//暂停给用户浏览信息
	    system("cls");
	}while(1);
	//将新密码赋给当前操作学生的密码
	(*mark)->Stu.password = re_new_password;
	//提示用户输入成功
	printf("||——密码修改成功!——\n");
	printf("||======================================================================||\n");
	save_id_studentinfo();//保存学生信息
	system("pause");//暂停给用户浏览信息
	system("cls");
}

//学生交流功能
//stu_talking是一个不带返回值的函数,形参mark时用来确定发送信息的用户的姓名
void stu_talking(stu *mark)
{
	system("cls");
	int choice = 0;//用于选择功能
	//数组teacher_t用于给用户打开师生交流文件(即进入师生交流群)
	char teacher_t[TALKING_FILE_NAME] = "stu_and_tea_communication.txt";
	//数组student_t用于给用户打开学生交流文件(即进入学生交流群)
	char student_t[TALKING_FILE_NAME] = "stu_and_stu_communication.txt";

	do
	{
		//提示用户输入的学生交流界面菜单
		system("cls");
	    printf("||==============================||\n");
	    printf("||1.进入学生交流群\t\t||\n");
	    printf("||2.进入师生交流群\t\t||\n");
	    printf("||3.退出交流功能,返回菜单\t||\n");
	    printf("||==============================||\n||");
	    
 		if(scanf("%d",&choice) != 1)//如果choice不为整数类型则进入if语句
		{
			input_again();//提示用户重新输入
			continue;//重新循环
		}//if语句之后的choice为整数类型的数
		
		//如果用户选择1或2则进入if语句
	    if(choice == 1 ||choice == 2)
	    {
	    	//如果用户选择1则进入if语句(1代表和学生们交流)
	        if(choice == 1)
	        {
	        	//接受信息,并把用户要打开的文件名(此时用户要打开学生交流群的文件)
                receive_message(student_t);
                //接收消息,并把用户要打开的文件名和用户姓名(此时用户要打开学生交流群的文件)
		        send_message(student_t,mark->Stu.name);
	        }
	        //如果用户选择2则进入if语句(2代表和老师交流)
	        if(choice == 2)
	        {
	        	//接受信息,并把用户要打开的文件名(此时用户要打开师生交流群的文件)
		        receive_message(teacher_t);
		        //接收消息,并把用户要打开的文件名和用户姓名(此时用户要打开师生交流群的文件)
		        send_message(teacher_t,mark->Stu.name);
	        }
	    }
	    
	    //如果不选择1或2则进入else语句
	    else
		{
			//如果选择3则进入if语句(3代表退出功能)
		    if(choice == 3)
		    {
			    printf("||退出成功\n||");//提示用户退出成功
			    system("pause");//暂停给用户浏览信息
			    system("cls");
			    return;
		    }
		    
		    //如果输入了其他数字则进入else语句
			else
		    {
		    	//提示用户输入错误,并重新输入
			    printf("||输入错误请重新输入\n||");
			    system("pause");//暂停给用户浏览信息
			    system("cls");
			    continue;
		    }
		}
	}while(1);

	system("cls");
}

//教师菜单
void teacher_menu(void)
{
	int choice;//用于教师选择功能
	
	while(1)
	{
		//提示用户选择功能
		printf("||==============================================||\n");
		printf("||\t\t当前为教师模式\t\t\t||\n");//提示用户当前的信息
		printf("||==============================================||\n");
		printf("||\t\t请选择功能\t\t\t||\n");
		printf("||==============================================||\n");
		printf("||\t\t1.发布考试\t\t\t||\n");
		printf("||\t\t2.录入学生信息\t\t\t||\n");
		printf("||\t\t3.查看全部学生成绩\t\t||\n");
		printf("||\t\t4.查找个别学生信息\t\t||\n");
		printf("||\t\t5.修改学生信息\t\t\t||\n");
		printf("||\t\t6.删除学生身份信息\t\t||\n");
		printf("||\t\t7.删除学生考试信息\t\t||\n");
		printf("||\t\t8.查看删除的学生考试记录\t||\n");
		printf("||\t\t9.交流功能\t\t\t||\n");
		printf("||\t\t10.返回总菜单\t\t\t||\n");
		printf("||==============================================||\n||");

		//从键盘获得1,2,3,4,5,6,7,8,9
		if(scanf("%d",&choice) != 1)//如果choice不是整数类型则进入if语句
		{
			input_again();//提示用户程序输入
			continue;//重新循环
		}
		take_in_line_break();

		switch (choice)
		{
			case 1://发布考试
				post_examination();
            	break;
			case 2://录入学生信息
				input_studentinfo();
				break;
			case 3://查看全部学生成绩
				print_studentinfo();
				break;
			case 4://查看个别学生信息
				seek_studentinfo();
				break;
			case 5://修改学生信息
				modify_studentinfo();
				break;
            case 6://删除学生身份信息
				remove_student_id_info();
            	break;
            case 7://删除学生考试信息
				remove_student_exam_info();
            	break;
		    case 8://查看已被删除的学生信息
				print_stu_deleted_exam_info();
            	break;
		    case 9://老师交流功能
				tea_talking();
            	break;
			case 10://返回总菜单
			    printf("||成功返回\n||");
	            system("pause");//暂停给用户浏览信息
	            system("cls");
                return;
			default ://其他输入
				input_again();
				break;
		}
	}
}

//发布考试
void post_examination(void)
{
	//ch用来确定用户是否要录入
	char ch;
	//i0用来循环,i1标记当时需要设置的判断题题数,i11标记总判断题题数(其他变量同理)
	int i0,i1 = 0,i11 = 0,i2 = 0,i22 = 0,i3 = 0,i33 = 0,count = 0;
	//Timu_flag用于判断用户是否还继续录入题目,TF_flag用于判断判断题答案是否为Y或N
	//Option_flag用于判断录入的选择题答案是否为ABCD其中之一
	int Timu_flag = 0,TF_flag = 0,Option_flag = 0;

	//调用post_exam_menu函数,将函数返回的值赋给flag
	Timu_flag = post_exam_menu(&i11,&i22,&i33);
	//如果返回的值为0,进入if语句,说明用户选择退出
	if(Timu_flag == 0)return;

	do
	{
		//提示用户每个题型要设置多少道题
		system("cls");

		do
		{
            printf("||你要设置多少道判断题?(输入小于的数则退出功能)||\n||");
            if(scanf("%d",&i1) != 1)//如果i1不是整数类型则进入if语句
		    {
			    input_again();//提示用户程序输入
			    continue;//重新循环
		    }
			break;
		}while(1);
        take_in_line_break();
        if(i1 < 0)break;
        
       system("cls");

		do
		{
            printf("||你要设置多少道选择题?(输入小于的数则退出功能)||\n||");
            if(scanf("%d",&i2) != 1)//如果i2不是整数类型则进入if语句
		    {
			    input_again();//提示用户程序输入
			    continue;//重新循环
		    }
		    break;
		}while(1);
        take_in_line_break();
        if(i2 < 0)break;
        
        system("cls");

		do
		{
            printf("||你要设置多少道填空题题?(输入小于的数则退出功能)||\n||");
            if(scanf("%d",&i3) != 1)//如果i3不是整数类型则进入if语句
		    {
			    input_again();//提示用户程序输入
			    continue;//重新循环
		    }
		    break;
		}while(1);
        take_in_line_break();
        if(i3 < 0)break;
        if(i1 == 0 && i2 == 0 && i3 == 0)break;

        system("cls");

		//该循环用于给教师录入判断题
	    for(i0 = 0;i0 < i1;i0++,i11++)
	    {
	    	//分配一个TF_questions大小的内存,得到的指针赋给p11,另外定义一个指向TF_questions类型的指针p
		    TF_questions *p11 = (TF_questions *)malloc(sizeof(TF_questions)),*p = NULL;
		    
		    if(p11 == NULL)//如果p11得到的指针为空,则进入if语句,且则说明分配内存失败,并退出录入判断题
		    {
		    	//提示用户分配失败的原因
		    	printf("||!【分配内存失败】!\n||");
		    	printf("pause");//暂停给用户浏览信息
		    	system("cls");
		    	break;
			}
			
		    //将p11的next置为NULL
            p11->next = NULL;
            //首先timu.tf_questions代表判断题的链表,此时代表链表表头,如果不为空则进入if语句
	        if(timu.tf_questions)
	        {
	        	//尾插法
	        	//定义一个指向TF_questions类型的指针tf_tail,并将tf_tail指向判断题链表的头节点
	        	TF_questions *tf_tail = timu.tf_questions;
                //进行循环直到tf_tail为最后一个节点
	        	for(;tf_tail->next;tf_tail = tf_tail->next);
	        	//此时的tf_tail的next为空,将其赋为p11
	    	    tf_tail->next = p11;
		    }
		    else//如果timu.tf_questions链表头为空则进入else语句
                //将p11赋给链表头节点
			    timu.tf_questions = p11;
            //提示用户输入该判断题题目
		    printf("||——请输入第%d道判断题题目——\n||",i11+1);
  	        while(strcmp(gets(p11->tf_question),"\n") <= 0)
	            printf("||");
            //提示用户输入该判断题题答案
		    printf("||——请输入第%d道判断题的答案(Y or N)——\n||",i11+1);
		    do
		    {
		    	//将判断题答案输入标志置为0(0表示还未有答案或则得到的答案不符合录入标准)
		    	TF_flag = 0;
		        scanf("%s",p11->tf_answer);
		        //如果录入的答案为Y或N则让标志置为1
		        if(p11->tf_answer[0] == 'Y')TF_flag = 1;
		        if(p11->tf_answer[0] == 'N')TF_flag = 1;
		        //如果标志为0则进入if语句且说明得到的录入答案错误
		        if(TF_flag == 0)
		        {
		        	//提示录入答案错误的原因,并提示用户重新输入
		  		    printf("||选项答案只能是大写Y或N\n");
		        	printf("||请重新输入判断题答案\n||");
					continue;
				}
                //录入答案正确则退出循环
				break;
		    }while(1);
            take_in_line_break();

            do
            {
            	//提示用户输入该判断题题分值
		        printf("||——请输入第%d道判断题题目的分值——\n||",i11+1);
		        if(scanf("%f",&p11->tf_score) != 1)
		        {
			        input_again();//提示用户程序输入
			        continue;//重新循环
			    }
			    //如果输入的分值小于0
			    if(p11->tf_score <= 0)
			    {
			    	printf("||输入的分值需要大于0,请重新输入\n");
		            continue;
				}
				//录入的分值正确则退出循环
			    break;
			}while(1);
            take_in_line_break();
            //将当前满分增加该判断题题分值得到新的当前满分
		    timu.full_mark += p11->tf_score;
		    system("cls");
		    //提示用户判断题题目信息(打印出来)
	 		printf("||======================================||\n");
		    printf("||目前共有%d道判断题:\n",i11+1);
		    for(p = timu.tf_questions; p ;p = p->next)
		        printf("||题目:%s    答案:%s    分值:%.2f\n||\n",p->tf_question,p->tf_answer,p->tf_score);
	    	printf("||目前满分值为：%0.2f\n",timu.full_mark);
	 		printf("||======================================||\n||");
	    	p11 = p11->next;
	    	free(p11);//p11用完之后释放内存
	    	system("pause");//暂停给用户浏览
	    	system("cls");
        }
        
        //该循环用于给教师录入选择题
	    for(i0 = 0;i0 < i2;i0++,i22++)
	    {
            //分配一个Choice_questions大小的内存,得到的指针赋给p22,另外定义一个指向Choice_questions类型的指针p
		    Choice_questions *p22 = (Choice_questions *)malloc(sizeof(Choice_questions)),*p = NULL;
		    
  		    if(p22 == NULL)//如果p22得到的指针为空,则进入if语句,且则说明分配内存失败,并退出录入选择题
		    {
		    	//提示用户分配失败的原因
		    	printf("||!【分配内存失败】!\n||");
		    	printf("pause");//暂停给用户浏览信息
		    	system("cls");
		    	break;
			}
			
		    //将p22的next置为空
            p22->next = NULL;
            //首先timu.choice_questions代表判断题的链表,此时代表链表表头,如果不为空则进入if语句
	        if(timu.choice_questions)
	        {
	        	//定义一个指向Choice_questions类型的指针cq_tail,并将cq_tail指向选择题链表的头节点
	        	Choice_questions *cq_tail = timu.choice_questions;
	        	//进行循环直到cq_tail为最后一个节点
	    	    for(;cq_tail->next;cq_tail = cq_tail->next);
	    	    //此时的cq_tail的next为空,将其赋为p22
	    	    cq_tail->next = p22;
		    }
		    else//如果timu.choice_questions链表头为空则进入else语句
				//将p22赋给链表头节点
			    timu.choice_questions = p22;
			    
            //提示用户输入该选择题题目
		    printf("||——请输入第%d道选择题题目——\n||",i22+1);
  		    while(strcmp(gets(p22->choice_question),"\n") <= 0)
	            printf("||");
		    //提示用户输入该选择题的各个选项
		    printf("||————请输入A选项————\n||");
  	        while(strcmp(gets(p22->option.option_a),"\n") <= 0)
	            printf("||");
		    printf("||————请输入B选项————\n||");
  	        while(strcmp(gets(p22->option.option_b),"\n") <= 0)
	            printf("||");
		    printf("||————请输入C选项————\n||");
  	        while(strcmp(gets(p22->option.option_c),"\n") <= 0)
	            printf("||");
		    printf("||————请输入D选项————\n||");
  	        while(strcmp(gets(p22->option.option_d),"\n") <= 0)
	            printf("||");
            //提示用户输入该选择题答案
            printf("||——请输入第%d道选择题的答案(A、B、C、D)——\n||",i22+1);
            
            //do-while循环用于辅助Option_flag变量检测得到的答案是否是ABCD其中之一
            do
            {
            	//先将选择题选项答案判断标志置为0
            	Option_flag = 0;
		        scanf("%s",p22->cq_answer);
		        //判断录入的选择题答案,如果符合标准则将Option_flag置为1
		        if(p22->cq_answer[0] == 'A')Option_flag = 1;
		        else if(p22->cq_answer[0] == 'B')Option_flag = 1;
		        else if(p22->cq_answer[0] == 'C')Option_flag = 1;
		        else if(p22->cq_answer[0] == 'D')Option_flag = 1;
		        //如果得到的录入选择题答案不符合要求则进入语句
		        if(Option_flag == 0)
		        {
		        	//提示用户该选择题错误的原因,并要求重新输入
		        	printf("||选项答案只能是大写ABCD其中之一\n");
		        	printf("||请重新输入选项答案\n||");
					continue;
				}
				//此时得到的录入的选择题答案符合标准退出循环
				break;
		    }while(1);
		    
            take_in_line_break();
            
            //do-while循环用于检测得到的选择题分值的类型是否正确(即出来后的分值为浮点型)
            do
            {
                //提示用户输入该选择题题分值
		        printf("||——请输入第%d道选择题的分值——\n||",i22+1);
		        if(scanf("%f",&p22->cq_score) != 1)
		        {
		        	input_again();
					continue;
			    }
			    if(p22->cq_score <= 0)
			    {
			    	printf("||输入的分值应该大于0\n");
			    	continue;
				}
			    break;
			}while(1);
            take_in_line_break();
            
            //将该选择题的分值加入到当前满分分值变成最新的满分分值
		    timu.full_mark += p22->cq_score;
		    
		    system("cls");
		    //提示用户目前的选择题信息
    	 	printf("||=====================================||\n");
		    printf("||目前共有%d道选择题:\n",i22+1);
            //将timu.choice_questions链表的表头赋给p,p利用for循环将选择题打印出来
		    for(p = timu.choice_questions; p ;p = p->next)
		        printf("||题目：%s\n||选项：A:%s   B:%s   C:%s   D:%s\n||答案：%s    分值：%f\n||\n",
				p->choice_question,p->option.option_a,p->option.option_b,p->option.option_c,
				p->option.option_d,p->cq_answer,p->cq_score);
	    	printf("||目前满分值为：%f\n",timu.full_mark);
    	 	printf("||=====================================||\n||");
	    	p22 = p22->next;
	    	free(p22);//将p22的内存释放
	    	system("pause");//暂停给用户浏览
	    	system("cls");
        }
        
        //用于给教师录入填空题
        for(i0 = 0;i0 < i3;i0++,i33++)
	    {
	        //分配一个GF_questions大小的内存,得到的指针赋给p33,另外定义一个指向GF_questions类型的指针p
		    GF_questions *p33 = (GF_questions *)malloc(sizeof(GF_questions)),*p;
		    
  		    if(p33 == NULL)//如果p33得到的指针为空,则进入if语句,且则说明分配内存失败,并退出录入填空题
		    {
		    	//提示用户分配失败的原因
		    	printf("||!【分配内存失败】!\n||");
		    	printf("pause");//暂停给用户浏览信息
		    	system("cls");
		    	break;
			}
			
			//将p33的next
            p33->next = NULL;
            //首先timu.gf_questions代表填空题的链表,此时代表链表表头,如果不为空则进入if语句
	        if(timu.gf_questions)
	        {
	        	//定义一个指向GF_questions类型的指针gf_tail,并将gf_tail指向填空题链表的头节点
	        	GF_questions *gf_tail = timu.gf_questions;
	        	//进行循环直到gf_tail为最后一个节点
	    	    for(;gf_tail->next;gf_tail = gf_tail->next);
	    	    //此时的gf_tail的next为空,将其赋为p33
	    	    gf_tail->next = p33;
		    }
		    else//如果timu.gf_questions链表头为空则进入else语句
				//将p33赋给链表头节点
			    timu.gf_questions = p33;
			//提示用户输入该填空题题目
		    printf("||——请输入第%d道填空题题目——\n||",i33+1);
    	    while(strcmp(gets(p33->gf_question),"\n") <= 0)
	            printf("||");
		    printf("||——请输入第%d道填空题的答案——\n||",i33+1);
		    while(strcmp(gets(p33->gf_answer),"\n") <= 0)
	            printf("||");
		    
		    do
            {
            	//提示用户输入该填空题题分值
		        printf("||——请输入第%d道填空题的分值——\n||",i33+1);
		        if(scanf("%f",&p33->gf_score) != 1)
		        {
			        input_again();//提示用户程序输入
			        continue;//重新循环
			    }
			    if(p33->gf_score <= 0)
			    {
			    	printf("||输入的分值应该大于0\n");
					continue;
				}
			    //录入的分值正确则退出循环
			    break;
			}while(1);
            take_in_line_break();
            
            //将当前满分增加该题分值得到新的当前满分
		    timu.full_mark += p33->gf_score;
		    
		    system("cls");
		    //提示用户当前的填空题信息(打印题目)
		    printf("||=========================||\n");
		    printf("||目前共有%d道填空题:\n",i33+1);
		    for(p = timu.gf_questions; p ;p = p->next)
		        printf("||题目：%s\n||答案：%s\n||分值：%f\n||\n",p->gf_question,
				p->gf_answer,p->gf_score);
	    	printf("||目前满分值为：%.2f\n",timu.full_mark);
	    	printf("||=========================||\n||");
	    	p33 = p33->next;
	    	free(p33);//释放p33的内存
	    	system("pause");
	    	system("cls");
        }
        
        //将题目保存
	    save_timu(i11,i22,i33);
	    system("cls");
	    //打印题目给用户浏览录入后的题目
	    print_timu(4);
	    //提示用户是否还需要录入
	    printf("===============================================================\n");
	    printf("||——你还要继续录入题目吗?(需要则输入y,其余字符则返回菜单)——\n||");
	    ch = getchar();
 	    //如果用户只输入回车符则进入循环直到不输入回车符为止
        while(ch == '\n')
        {
        	printf("||");
		    scanf("%c",&ch);
		    continue;
	    }
    }while(ch == 'y');
	if(i1 < 0 || i2 < 0 || i3 < 0)
	{
		printf("||退出成功\n||");
		system("pause");
		system("cls");
	    return;
	}
	if(i1 == 0 && i2 == 0 && i3 == 0)
	{
		printf("||由于输入的题数都是0,所以返回\n||");
		system("pause");
		system("cls");
		return;
	}
    //录入玩题目之后则初始化所有学生的分数和考试状态
    initialize_grade();
    //保存学生信息
    save_id_studentinfo();
    //保存录入之后的题目到文件中
    save_timu(i11,i22,i33);
    //将当前题目链表中的题目删除
    delete_timu();
	tea_save_stu(1);
	system("cls");
}

//老师将学生成绩和考试状态初始化成绩为0
void initialize_grade(void)
{
	//定义一个指向stu类型的指针p,并将p指向当前学生链表的表头
	stu *p = stu_list;
	
	//用for语句浏览链表
	for(;p;p = p->next)
	{
		//将所有学生的成绩和考试状态都赋为0
		p->Stu.grade = 0;
		p->Stu.examination_status = 0;
	}
	//提示用户初始化成功
	printf("||——初始化成绩成功!——\n");
}

//发布考试的菜单
//post_exam_menu是返回一个整数类型的函数
//形参分别为判断题,选择题,填空题的题目数(如果要重新录入则都置为0)的整型指针
//返回的函数值用来判断用户是否录入考试题目
//如果返回1则说明要继续录入或者重新录入题目;否则退出发布考试功能,返回教师菜单
int post_exam_menu(int *i11,int *i22,int *i33)
{
	//choice用于选择功能
	char choice;
	
	//2代表教师身份,read_timu_file函数代表读取题目内容
	//如果函数返回值不为0则进入if语句(此时返回值为1,说明有考试题目),否则跳过if语句
	if(read_timu_file(2))
	{
		system("cls");
		
		//以只读的方式打开名为"timu(clear)"的文件
		FILE *fpr = fopen("timu(clear).txt","r");
		//分别将判断题、选择题和填空题的题目数赋给i11,i22,i33
	    fscanf(fpr,"%d,%d,%d",i11,i22,i33);
	    fclose(fpr);//关闭文件
	    
	    print_timu(4);//打印题目
	    system("pause");//暂停给用户浏览信息
	    system("cls");
	    
		do
		{
			system("cls");
			//提示用户选择功能
	        printf("||======================================||\n");
		    printf("||当前已经录入题目接下来你可以有以下操作||\n");
		    printf("||======================================||\n");
		    printf("||1.继续录入\t\t\t\t||\n");
		    printf("||2.重新录入\t\t\t\t||\n");
		    printf("||3.退出该功能返回菜单\t\t\t||\n");
		    printf("||======================================||\n||");
		    
		    //用户输入选项
			scanf("%c",&choice);
            take_in_line_break();
            
		    //如果用户只输入回车符则进入循环直到不输入回车符为止
            while(choice == '\n')
            {
		        printf("||");
		        scanf("%c",&choice);
		        continue;
	        }
	        
	        //如果输入的功能不为1、2、3则进入if语句
	        if(choice != '1' && choice != '2' && choice != '3')
	        {
	        	//提示用户输入错误
			    printf("||——————————\n");
			    printf("||输入错误,请重新输入||\n");
			    printf("||——————————\n||");
			    system("pause");
			}
		//如果用户输入不为1、2、3则进入循环
        }while(choice != '1' && choice != '2' && choice != '3');

		switch (choice)
		{
			case '1':
				//提示用户开始录入
				printf("||——开始继续录入.....——\n||");
				system("pause");//暂停给用户浏览信息
				return 1;
			case '2':
				delete_timu();//删除题目(如果要重新录入就要将当前题目链表继续删除)
				*i11 = *i22 = *i33 = 0;//将题目数置为0
                //提示用户开始重新录入
				printf("||——开始重新录入.....——\n||");
				system("pause");//暂停给用户浏览信息
				return 1;
				break;
			case '3':
				printf("||——退出成功——\n||");
				system("pause");
				system("cls");
				delete_timu();
				return 0;
		}
	}
	else//如果read_timu_file(2)返回的值不为0则进入else语句
	{
		//提示用户还未录入题目
	    printf("||————————————————||\n");
		printf("||现在尚未有录入题目,可以进行录入 ||\n");
		printf("||————————————————||\n");
		system("pause");//暂停给用户浏览信息
		return 1;
	}
	
	system("cls");
}

//保存总题目
void save_timu(int i11,int i22,int i33)
{
	//打开文件名为"timu(clear)"和"timu"的文件,并将返回的指针分别赋给fpw1和fpw2
	FILE *fpw1 = fopen("timu(clear).txt","w");
	FILE *fpw2 = fopen("timu.txt","w");
	
	//定义指向TF_questions类型的指针p1,并将p1指向timu.tf_questions链表表头(p2、p3同下)
	TF_questions *p1 = timu.tf_questions;
	Choice_questions *p2 = timu.choice_questions;
	GF_questions *p3 = timu.gf_questions;
	int count;//count用来辅助将题目打印到文件中
	
	//如果fpw1和fpw2为空则进入if语句(说明打开文件失败)
	if( fpw1 == NULL || fpw2 ==NULL)
	{
		//提示用户错误原因,并退出
		printf("!【保存失败】!\n");
		system("pause");
		return;
	}
	
	//将题目的判断题、选择题和填空题分别打印到"timu(clear)"中格式为x,y,z(回车)
	fprintf(fpw1,"%d,%d,%d\n",i11,i22,i33);
	//循环将题目按以下格式输入到文件
	//例如判断题题目:This is an egg 答案:Y 分值2.000000
	//则输入到文件的格式为This is an egg.#Y#2.000000(其他判断题同上)
	for(p1 = timu.tf_questions; p1 ;p1 = p1->next)
	    fprintf(fpw1,"%s#%s#%f\n",p1->tf_question,p1->tf_answer,p1->tf_score);
    //循环将题目按以下格式输入到文件
	//例如判断题题目:What color does Gogo like?
	//          选项:A.red    B.blue    C.yellow    D.green    答案:A 分值2.000000
	//则输入到文件的格式为What color does Gogo like?#red#blue#yellow#green#A 2.000000(其他选择题同上)
	for(p2 = timu.choice_questions; p2 ;p2 = p2->next)
	    fprintf(fpw1,"%s#%s#%s#%s#%s#%s %f\n",p2->choice_question,p2->option.option_a,p2->option.option_b,p2->option.option_c,p2->option.option_d,p2->cq_answer,p2->cq_score);
	//循环将题目按以下格式输入到文件
	//例如判断题题目:I like ___. 答案:study 分值2.000000
	//则输入到文件的格式为I like ___.#study#2.000000(其他填空题同上)
	for(p3 = timu.gf_questions; p3 ;p3 = p3->next)
	    fprintf(fpw1,"%s#%s#%f\n",p3->gf_question,p3->gf_answer,p3->gf_score);
    //将该卷分数输入到文件
	fprintf(fpw1,"%f\n",timu.full_mark);
	fclose(fpw1);//关闭文件
	//打印到名为"timu"的文本文件上
	//以下为格式
//  题目总览:
//  一、判断题
//  1.This is an egg.
//  答案:Y    分值:2.000000
//
//  2.This is my dad.
//  答案:Y    分值:2.000000
//
//  二、选择题
//  1.What color does Gogo like?
//  选项:A:red   B:blue   C:yellow   D:green
//  答案:A2    分值:2.000000
//
//  2.This does Gogo doing in this pA
//  选项:A:reading   B:drawing   C:writing   D:runing
//  答案:Ao    分值:3.000000
//
//  三、填空题
//  2.Gogo don't like ___?
//  答案:sleeping    分值:2.000000
//
//  3.I like ___.
//  答案:study    分值:2.000000
//
//  目前满分值为：17.000000
//  共有8道题目
	fprintf(fpw2,"题目总览:\n");
	fprintf(fpw2,"一、判断题\n");
	//将p1指向timu.tf_questions头节点,利用循环输入到文件上
	for(p1 = timu.tf_questions,count = 0;p1;p1 = p1->next,count++)
		fprintf(fpw2,"%d.%s\n答案:%s    分值:%f\n\n",count+1,p1->tf_question,p1->tf_answer,p1->tf_score);
	fprintf(fpw2,"二、选择题\n");
	//将p2指向timu.choice_questions头节点,利用循环输入到文件上
	for(p2 = timu.choice_questions,count = 0;p2;p2 = p2->next,count++)
        fprintf(fpw2,"%d.%s\n选项:A:%s   B:%s   C:%s   D:%s\n答案:%s    分值:%f\n\n",count+1,
		p2->choice_question,p2->option.option_a,p2->option.option_b,p2->option.option_c,
		p2->option.option_d,p2->cq_answer,p2->cq_score);
	//将p3指向timu.gf_questions头节点,利用循环输入到文件上
	fprintf(fpw2,"三、填空题\n");
	for(p3 = timu.gf_questions,count = 0;p3;p3 = p3->next,count++)
		fprintf(fpw2,"%d.%s\n答案:%s    分值:%f\n\n",count+1,p3->gf_question,p3->gf_answer,p3->gf_score);
	//在文件输入满分和题目数
    fprintf(fpw2,"目前满分值为：%f\n共有%d道题目\n",timu.full_mark,i11+i22+i33);
	fclose(fpw2);//关闭文件
	//提示用户录入题目成功
	printf("||录入成功!");
	system("pause");//暂停给用户浏览信息
}

//教师录入学生信息
void input_studentinfo(void)
{
	system("cls");
    //ch用来判断用户是否还要录入,input_name原来给用户输入要录入的学生名字
	char ch,input_name[NAME_LEN];
	//input_id用来给用户输入要录入的学生学号,class_number用来记录班号,i用来记录班号位数
	int input_id = 0,class_number = 0,i = 0,id_flag = 0;
	stu *find = stu_list;//定义一个stu类型的指针指向学生信息链表中,用于查找录入的学生是否有重复
	
	do
	{
		do
		{
	        system("cls");
	        id_flag = 0;
		    //提示用户输入要录入学生的学号
	        printf("||——请输入你要录入学生的学号(范围1000~9999)(输入0退出)——\n");
	        printf("||——如果输入了小数则按整数部分录入——\n||");
	        if(scanf("%d",&input_id) != 1)
	        {
		        take_in_line_break();
	            //提示用户错误原因
			    printf("||!【要求输入四位整数】!\n||");
			    system("pause");
				system("cls");
	            continue;
	        }
	        take_in_line_break();
	        //如果用户输入0则退出循环
	        if(!input_id)break;
	        //如果用户输入
	        else if(input_id > 9999 ||input_id <1000)
	        {
	     	    //提示用户输入四位整数
	     	    printf("||!【要求输入四位整数】!\n||");
	     	    system("pause");
			    system("cls");
	            continue;
		    }
  		    //遍历链表,查看学号是否有重复
            for(find = stu_list;find;find = find->next)
            {
            	//如果学号重复则提示用户重新输入
        	    if(find->Stu.id == input_id)
        	    {
        	    	id_flag = 1;
				    printf("||输入的学号和当前学生链表中的某个学生学号相同,请重新输入\n||");
			        system("pause");
			        system("cls");
	            }
	            if(id_flag)break;
		    }
		    if(id_flag)continue;
		    break;
		}while(1);
        //输入0退出
        if(return_by_zero(input_id))return;
        system("cls");
        //提示用户输入要录入学生的姓名
	    printf("||——请输入你要录入学生的姓名(输入0退出)——\n||");
	    scanf("%s",input_name);
		take_in_line_break();
        //如果输入"0"退出
        if(char_return_by_zero(input_name))return;
	    stu *p = (stu *)malloc(sizeof(stu));
	    //如果内存分配失败则进入if语句
	    if(p == NULL)
	    {
	    	//提示用户错误原因
	    	printf("||分配内存失败\n");
	    	system("pause");//暂停给用户浏览
	    	system("cls");
	    	return;
		}
		//将p的next置为空
	    p->next = NULL;
	    p->Stu.id = input_id;
	    strcpy(p->Stu.name,input_name);
	    //如果学生信息链表表头不为空则进入if语句
	    if(stu_list)
	    {
	    	//用头插法插入
	    	//插入前head->node1->node2->node3->NULL
	    	//插入后head->p->node1->node2->node3->NULL
	    	//将p的next指向表头再将p学生信息结构体赋给表头,此时表头为新插入的结构体
	    	p->next = stu_list;
	    	stu_list = p;
		}
		//如果学生信息链表表头为空则进入else语句
		else
		    stu_list = p;
        do
        {
        	system("cls");
            //提示用户要录入学生的班级
            printf("||——请输入你要录入学生的班级(要输入如果14班则只输入14即可)\n||(只能输入一或两位数)(输入0退出)——\n");
            printf("||——如果输入小数则取整数部分\n||");
            if(scanf("%d",&class_number) != 1)
            {
            	take_in_line_break();
            	printf("||要求输入整数\n||");
            	system("pause");
            	system("cls");
            	continue;
		    }
		    take_in_line_break();
		    if(class_number > 99 ||class_number < 0)
		    {
		    	printf("||要求输入一或两位数\n||");
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
        //提示用户输入要录入学生的专业
        printf("||——请输入你要录入学生的专业(输入0退出)——\n||");
        scanf("%s",p->Stu.majority);
        take_in_line_break();
        //如果输入"0"退出
	    if(char_return_by_zero(p->Stu.majority))return;
        //将该学生密码赋为初始密码
	    p->Stu.password = ORIGINAL_PASSWROD;
	    //将该学生成绩和考试状态初始化为0
	    p->Stu.grade = 0;
	    p->Stu.examination_status = 0;
	    //提示用户是否还需要输入
 	    save_id_studentinfo();
	    tea_save_stu(2);
		printf("||——录入成功\n||——你还需要录入吗?(需要则输入y,其余字符则返回菜单)——\n");
	    printf("||===========================================================||\n||");
 	    //如果用户只输入回车符则进入循环直到不输入回车符为止
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

//如果字符串为"0"则返回1,否则返回0,用于判断是否为0,如果是则退出当前功能
int char_return_by_zero(char flag[])
{
	//如果字符串为"0"则进入语句返回1
	if(strcmp(flag,"0") == 0)
    {
		printf("||退出成功\n||");
        system("pause");
        system("cls");
        return 1;
	}
	//否则返回0
	return 0;
}

//学生或老师查看全部学生成绩
void print_studentinfo(void)
{
	system("cls");
	
	stu *p = stu_list;//定义指向stu类型的指针p指向学生信息链表表头
	int count = 0,i = 0;//i用于将至整个学生链表的信息储存到一个数组中,count用于统计整个链表的的学生个数
	
	for(p = stu_list;p;p=p->next,count++);//用count统计学生个数
	
	Student ranking[count];//定义结构体数组用于储存学生身份信息
	
	do
	{
		//查看成绩的菜单
		system("cls");
		//用枚举类型将id,grade,go_back分别赋为1、2、3
	    enum Choice{id = 1,grade,custom,go_back}choice;
	
	    for(p = stu_list,i=0;p && i<count;i++,p = p->next)
		    ranking[i] = p->Stu;
		printf("||==============================||\n");
		printf("||请输入你要的学生成绩的排序方式||\n");
 		printf("||==============================||\n");
 		printf("||1.学号排序\t\t\t||\n");
 		printf("||2.成绩排序\t\t\t||\n");
 		printf("||3.自定义分数段顺序排序\t||\n");
 		printf("||4.返回菜单\t\t\t||\n");
 		printf("||==============================||\n||");
  		if(scanf("%d",&choice) != 1)//如果choice不是整数类型则进入if语句
		{
			//提示用户错误原因
			printf("||要求输入整数\n");
			input_again();//提示用户重新输入
			continue;//重新循环
		}
        take_in_line_break();
        
	    switch(choice)
	    {
	        case id://学号排序
                id_rank(&ranking[0],count);
                break;
	        case grade://成绩排序
		        grade_rank(&ranking[0],count);
		        break;
			case custom://自定义分数段查找
				Custom_statistics(&ranking[0],count);
				break;
	  	    case go_back://返回菜单
			    system("cls");
			    break;
	        default ://其他输入
			    printf("!【输入错误】!\n");
		        break;
        }
        if(choice == go_back)break;
    }while(1);
	system("cls");
}

//自定义分数段查找
void Custom_statistics(Student *ranking,int count)
{
	//upper_limit代表上限,lower_limit代表下限
	float upper_limit = 0,lower_limit = 0;
	//j用于循环输出学生成绩,i用于排序
	int j = 0,gap = count,i = 0;
	
	do
	{
    	do
    	{
	        system("cls");
	        printf("||请输入你也要统计的分数段(输入小于0的数退出)\n");
	        printf("||下限:");
	        if(scanf("%f",&lower_limit) != 1)
	        {
		    	take_in_line_break();
		    	//提示用户错误原因
		    	printf("||要求输入数字\n||");
		    	system("pause");
		    	system("cls");
		     	continue;//重新循环
	        }
	        take_in_line_break();
	    	break;
    	}while(1);
        if(lower_limit < 0)break;
        
    	do
    	{
	        system("cls");
	        printf("||请输入你也要统计的分数段(输入小于0的数退出退出)\n");
	        printf("||下限:%.0f\n",lower_limit);
	        printf("||上限:");
	        if(scanf("%f",&upper_limit) != 1)
	        {
	        	take_in_line_break();
		    	//提示用户错误原因
		    	printf("||要求输入数字\n");
		    	input_again();//提示用户重新输入
		    	continue;//重新循环
	        }
	        take_in_line_break();
	    	break;
	    }while(1);
	    if(upper_limit < 0)break;
	    
	    if(upper_limit < lower_limit)
		{
			printf("||输入的上限小于下限,输入错误请重新输入\n||");
			system("pause");
		    continue;
		}
	    break;
	}while(1);
	if(upper_limit < 0 || lower_limit < 0)return;
	
	printf("||输入成功\n||");
	system("pause");
	system("cls");

	while (gap>1)
	{
		//每次对gap折半操作
		gap = gap / 2;
		//单趟排序
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
	printf("||处于%.1f~~%.1f分段的学生如下:\t\t\t\t\t\t||\n",lower_limit,upper_limit);
	printf("||学号============姓名============班级============专业============分数==||\n");
	for(j = 0;j < count;j++)
		if(ranking[j].grade >= lower_limit && ranking[j].grade <= upper_limit)
            printf("||%d\t\t%s\t\t%s\t\t%s\t\t  %.1f\t||\n",ranking[j].id,ranking[j].name,ranking[j].class,ranking[j].majority,ranking[j].grade);
	printf("||======================================================================||\n||");
	system("pause");
	system("cls");
}

//学号排序
//id_rank是个无返回值的函数,形参ranking是Stuent类型的指针,指向一个整个数组的首地址,用该数组对学生排序
//count是整数类型变量用于统计链表中学生的人数
void id_rank(Student *ranking,int count)
{
	system("cls");
		
	//用枚举类型将idorder,reverse_order,go_back分别赋为1、2、3
	enum Choice{order = 1,reverse_order,go_back}choice;
	do
	{
     	//提示用户输入信息
    	printf("||==============================||\n");
	    printf("||你要学号顺序排序还是逆序排序？||\n");
    	printf("||==============================||\n");
	    printf("||1.学号顺序排序\t\t||\n");
	    printf("||2.学号逆序排序\t\t||\n");
	    printf("||3.返回排序功能\t\t||\n");
	    printf("||==============================||\n||");
  	    if(scanf("%d",&choice) != 1)//如果choice不是整数类型则进入if语句
	    {
		    //提示用户错误原因
		    printf("||要求输入整数\n");
		    input_again();//提示用户重新输入
		    continue;//重新循环
	    }
	
        take_in_line_break();
        system("cls");
	    switch(choice)
    	{
	        case order:
	        	//如果顺序输出则调用id_order_rank函数,将数组首元素地址和学生个数作为实参带进函数
                id_order_rank(&ranking[0],count);
                break;
	        case reverse_order:
	        	//如果逆序输出则调用id_reverse_order_rank函数,将数组首元素地址和学生个数作为实参带进函数
		        id_reverse_order_rank(&ranking[0],count);
	    	    break;
	     	case go_back:
	  	    	//返回
		    	system("cls");
		    	return;
	        default ://其他输入
		    	printf("||输入错误\n||");
		    	system("pause");
		    	system("cls");
		        break;
        }
        if(choice == go_back)break;
	}while(1);
}

//希尔排序，先将待排序列进行预排序，使待排序列接近有序，然后再对该序列进行一次插入排序
//顺序按学号排序
//id_order_rank是不带返回值的函数,ranking为Student类型的指针,它指向学生信息数组,count是整数类型的变量用于统计学生个数
void id_order_rank(Student *ranking,int count)
{
    //gap用于描述数组的宽距,i用于循环
	int gap = count,i = 0;
	
	while (gap>1)
	{
		//每次对gap折半操作
		gap = gap / 2;
		//单趟排序
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
	printf("||学号============姓名============班级============专业============分数==||\n");
	for(i = 0;i < count; i++)
		printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.1f\t||\n",ranking[i].id,ranking[i].name,ranking[i].class,ranking[i].majority,ranking[i].grade);
	print_wholescore_and_avgscore();
	printf("||共有%d位学生\n",count);
	system("pause");
	system("cls");
}

//逆序按学号排序
void id_reverse_order_rank(Student *ranking,int count)
{
	int gap = count,i;
	
	while (gap>1)
	{
		//每次对gap折半操作
		gap = gap / 2;
		//单趟排序
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
	printf("||学号============姓名============班级============专业============分数==||\n");
	for(i = 0;i < count; i++)
		printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.1f\t||\n",ranking[i].id,ranking[i].name,ranking[i].class,ranking[i].majority,ranking[i].grade);
	print_wholescore_and_avgscore();
	printf("||共有%d位学生\n",count);
	system("pause");
	system("cls");
}

//成绩排序
void grade_rank(Student *ranking,int count)
{
	system("cls");
	
	enum Choice{order = 1,reverse_order,go_back}choice;
	do
	{
	    printf("||==============================||\n");
	    printf("||你要成绩顺序排序还是逆序排序? ||\n");
	    printf("||==============================||\n");
	    printf("||1.成绩顺序排序\t\t||\n");
	    printf("||2.成绩逆序排序\t\t||\n");
	    printf("||3.返回排序功能\t\t||\n");
	    printf("||==============================||\n||");
 		if(scanf("%d",&choice) != 1)//如果choice不是整数类型则进入if语句
		{
			//提示用户错误原因
			printf("||要求输入整数\n");
			input_again();//提示用户重新输入
			continue;//重新循环
		}
		break;
	}while(1);
    take_in_line_break();
    system("cls");
	switch(choice)
	{
	    case order://按成绩顺序输出
            grade_order_rank(&ranking[0],count);
            break;
	    case reverse_order://按成绩逆序输出
		    grade_reverse_order_rank(&ranking[0],count);
		    break;
	  	case go_back://返回排序功能
			system("cls");
			return;
	    default ://其他输入
			printf("!【输入错误】!\n");
		    break;
    }
}

//顺序按成绩排序
void grade_order_rank(Student *ranking,int count)
{
	int gap = count,i;
	
	while (gap>1)
	{
		//每次对gap折半操作
		gap = gap / 2;
		//单趟排序
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
	printf("||学号============姓名============班级============专业============分数==||\n");
	for(i = 0;i < count; i++)
		printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.1f\t||\n",
		ranking[i].id,ranking[i].name,ranking[i].class,ranking[i].majority,ranking[i].grade);
	print_wholescore_and_avgscore();
	printf("||共有%d位学生\n",count);
	system("pause");
	system("cls");
}

//逆序按成绩排序
void grade_reverse_order_rank(Student *ranking,int count)
{
	int gap = count,i;
	
	while (gap>1)
	{
		//每次对gap折半操作
		gap = gap / 2;
		//单趟排序
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
	printf("||学号============姓名============班级============专业============分数==||\n");
	for(i = 0;i < count; i++)
        printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.1f\t||\n",ranking[i].id,ranking[i].name,ranking[i].class,ranking[i].majority,ranking[i].grade);
    print_wholescore_and_avgscore();
	printf("||共有%d位学生\n",count);
	system("pause");
	system("cls");
}

//教师查看全部总分和平均分
void print_wholescore_and_avgscore(void)
{
	//定义一个stu类型的指针p指向stu_list(当前学生信息的头节点)
	stu *p = stu_list;
	int count = 0;//count既用于循环又用于统计学生人数
	float avg = 0,wholesccore = 0;//avg代表全班平均分,wholesccore代表全班总分

    //用for循环计算班级总分以及学生人数
	for(count = 0,wholesccore = 0;p;p = p->next,count++)
		wholesccore += p->Stu.grade;
	if(count)
	    avg = wholesccore/count;
	else avg = 0;
	    //提示用户班级得分信息
	    printf("||——班级总分:%.1f——\t\t\t\t\t\t\t||\n||——班级平均分:%.2f——\t\t\t\t\t\t||\n",wholesccore,avg);
	    printf("||======================================================================||\n");
}

//教师查看个别学生信息
void seek_studentinfo(void)
{
	
	do
	{
	    system("cls");
	    enum Choice{id = 1,name,go_back}choice;
	    //提示用户菜单
	    printf("||======================||\n");
		printf("||输入你要输入学生的信息||\n");
		printf("||======================||\n");
		printf("||1.通过学号查找\t||\n");
		printf("||2.通过姓名查找\t||\n");
		printf("||3.返回菜单\t\t||\n");
	    printf("||======================||\n||");
  	    if(scanf("%d",&choice) != 1)//如果choice不是整数类型则进入if语句
	    {
		    //提示用户错误原因
		    printf("||要求输入整数\n");
		    input_again();//提示用户重新输入
		    continue;//重新循环
	    }
        take_in_line_break();
        
	    switch(choice)
	    {
	        case id://学号查找
                seek_by_id();
                break;
	        case name://姓名查找
		        seek_by_name();
		        break;
	  	    case go_back://返回菜单
				system("cls");
				return;
	        default ://其他输入
				printf("!【输入错误】!\n");
		        break;
     	}
     	if(choice == go_back)break;
     }while(1);
	system("cls");
}

//通过学号查找学生
void seek_by_id(void)
{
	system("cls");
	int stu_id = 0;//定义整型变量,需要用户赋值给该变量
	stu *p = stu_list;//定义stu类型的指针指向stu_list(学生信息链表的表头)
	
	do
	{
	    printf("||=====================================||\n");
	    printf("||请输入你要查找的学生学号(输入0退出)\n||");
  		if(scanf("%d",&stu_id) != 1)//如果stu_id不是整数类型则进入if语句
		{
			//提示用户错误原因
			printf("||要求输入整数\n");
			input_again();//提示用户重新输入
			continue;//重新循环
		}
		break;
	}while(1);
	//如果输入为0则退出学生登录界面
	if(return_by_zero(stu_id))return;
	if(stu_list == NULL)
	{
        printf("||不存在该学生\n||");
        system("pause");
        system("cls");
        return;
	}
	
    take_in_line_break();
	system("cls");
	for(p = stu_list;p;p = p->next)
	{
		//如果链表中有学生的学号和用户输入的学号匹配上则进入语句(说明找到该学生)
		if(p->Stu.id == stu_id)
			{
				//显示该学生的信息
				printf("||学号============姓名============班级============专业============密码============分数==||\n");
				printf("||%d\t\t%s\t\t%s\t\t%s\t\t%d\t\t%.2f\t||\n||",p->Stu.id,p->Stu.name,p->Stu.class,
				p->Stu.majority,p->Stu.password,p->Stu.grade);
				system("pause");
	            break;
			}
        //如果读到链表末尾都匹配不到
		if(p->Stu.id != stu_id && p->next == NULL)
		{
		    printf("||!【未能找到该学生】!\n||");
		    system("pause");
		    system("cls");
		}
	}
}

//通过姓名查找学生
void seek_by_name(void)
{
	system("cls");
	char stu_name[10];
	stu *p=stu_list;
	
	printf("||=========================================||\n");
	printf("||请输入你要查找的学生姓名(只输入一个0退出)||\n||");
	scanf("%s",stu_name);
    take_in_line_break();
    //如果输入"0"退出
    if(char_return_by_zero(stu_name))return;
	if(stu_list == NULL)
	{
        printf("||不存在该学生\n||");
        system("pause");
        system("cls");
        return;
	}
	
	system("cls");
	for(;p;p=p->next)
	{
		if(strcmp(p->Stu.name,stu_name) == 0)
			{
				printf("||学号===========姓名===========班级=============专业===========密码=============分数===||\n");
				printf("||%d\t\t%s\t\t%s\t\t%s\t\t%d\t\t%.2f\t||\n||",p->Stu.id,p->Stu.name,p->Stu.class,
				p->Stu.majority,p->Stu.password,p->Stu.grade);
				system("pause");
	            break;
			}
		if(p->next == NULL && strcmp(p->Stu.name,stu_name) != 0)
		{
		    printf("||!【未能找到该学生】!\n||");
		    system("pause");
		    system("cls");
		}
	}
}

//教师修改学生信息
void modify_studentinfo(void)
{
	enum Choice{id = 1,name,go_back}choice;
	
	do
	{
	    system("cls");
		//提示用户输入
		printf("||==============================||\n");
	    printf("||请输入你要修改的学生信息      ||\n");
	    printf("||==============================||\n");
	    printf("||1.通过学号修改\t\t||\n");
	    printf("||2.通过姓名修改\t\t||\n");
	    printf("||3.返回菜单\t\t\t||\n");
	    printf("||==============================||\n||");
  	    if(scanf("%d",&choice) != 1)//如果choice不是整数类型则进入if语句
	    {
		    //提示用户错误原因
		    printf("||要求输入整数\n");
		    input_again();//提示用户重新输入
		    continue;//重新循环
	    }
        take_in_line_break();
        
	    switch(choice)
	    {
	        case id://学号查找
                modify_by_id();
                break;
	        case name://姓名查找
		        modify_by_name();
		        break;
	  	    case go_back://返回菜单
				system("cls");
				break;
	        default ://其他输入
				printf("||!【输入错误】!\n||");
				system("pause");
		        break;
     	}
        tea_save_stu(4);
        save_id_studentinfo();
        if(choice == go_back)break;
    }while(1);
	system("cls");
}

//通过学号修改学生信息
void modify_by_id(void)
{
	system("cls");
	//定义一个整型变量stu_id,id_flag判断重新修改的学号是否有重复
	//stu_flag判断是否能找到学生,modify_id代表要修改的学生,class_number代表班级号
	int stu_id = 0,id_flag = 0,stu_flag = 0,modify_id = 0,class_number = 0;
    //定义一个stu类型的指针指向学生信息链表的头节点stu_list,用于遍历链表
	stu *p = stu_list;
	char modify_mojority[MAJORITY];

    do
	{
		//提示用户输入信息
	    printf("||===================================||\n");
	    printf("||请输入你要修改的学生学号(输入0退出)||\n||");
  	    if(scanf("%d",&stu_id) != 1)//如果stu_id不是整数类型则进入if语句
	    {
		    //提示用户错误原因
		    printf("||要求输入整数\n");
		    input_again();//提示用户重新输入
		    continue;//重新循环
	    }
	    break;
	}while(1);
    take_in_line_break();
    //如果输入为0则退出学生登录界面
	if(return_by_zero(stu_id))return;
	
	if(stu_list == NULL)
	{
        printf("||不存在该学生\n||");
        system("pause");
        system("cls");
        return;
	}
	
	system("cls");
	stu_flag = 0;
	//对学生链表进行搜寻,寻找该学生
	for(p = stu_list;p;p = p->next)
	{
		//如果用户输入的学生学号和链表中对应的学生学号匹配则进入if语句
		if(p->Stu.id == stu_id)
			{
				//提示该学生的信息
				printf("||学号============姓名============班级============专业============分数=======||\n");
				printf("||%d\t\t%s\t\t%s\t\t %s\t\t  %.2f\t     ||\n",p->Stu.id,p->Stu.name,p->Stu.class,p->Stu.majority,p->Stu.grade);
				stu_flag = 1;
				break;
			}
        //若未能匹配且以及到链表末尾则进入if语句
		if(p->Stu.id != stu_id && p->next == NULL)
            {
			    //提示未能找到该学生
		        printf("||!【未能找到该学生】!\n||");
		        system("pause");
		        system("cls");
		    }
	}
	//如果未找到学生则返回
	if(!stu_flag)return;
	
	printf("||===========================================================================||\n");
	printf("||——请重新输入该学生信息以作修改——\t\t\t\t\t     ||\n||");
	system("pause");
	
	do
	{
	    system("cls");
	    id_flag = 0;
		//提示用户输入要录入学生的学号
	    printf("||——请输入你要修改学生的学号(范围1000~9999)(输入0退出)——\n");
	    printf("||——如果输入了小数则按整数部分修改——\n||");
	    if(scanf("%d",&modify_id) != 1)
	    {
		    take_in_line_break();
	        //提示用户错误原因
			printf("||!【要求输入四位整数】!\n||");
			system("pause");
			system("cls");
	        continue;
	    }
	    take_in_line_break();
	    //如果用户输入0则退出循环
	    if(!modify_id)break;
	    //如果用户输入
	    else if(modify_id > 9999 ||modify_id <1000)
	    {
	     	//提示用户输入四位整数
	     	printf("||!【要求输入四位整数】!\n||");
			system("pause");
			system("cls");
	        continue;
		}
		stu *find = stu_list;
  		//遍历链表,查看学号是否有重复
        for(find = stu_list;find;find = find->next)
        {
            //如果学号重复则提示用户重新输入
        	if(find->Stu.id == modify_id && find->Stu.id != stu_id)
        	{
        	    id_flag = 1;
				printf("||输入的学号和当前学生链表中的某个学生学号相同,请重新输入\n||");
			    system("pause");
			    system("cls");
	        }
	        if(id_flag)break;
		}
		if(id_flag)continue;
		break;
	}while(1);
    //输入0退出
    if(return_by_zero(modify_id))return;
    p->Stu.id = modify_id;
    
    system("cls");
    do
    {
        system("cls");
        //提示用户要录入学生的班级
        printf("||——请输入你要修改学生的班级(要输入如果14班则只输入14即可)\n||(只能输入一或两位数)(输入0退出)——\n");
        printf("||——如果输入小数则取整数部分\n||");
        if(scanf("%d",&class_number) != 1)
        {
            take_in_line_break();
            printf("||要求输入整数\n||");
            system("pause");
            system("cls");
            continue;
		}
		take_in_line_break();
		if(class_number > 99 ||class_number < 0)
		{
		    printf("||要求输入一或两位数\n||");
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
    //提示用户输入学生专业
	printf("||——请输入学生专业——\n||");
	scanf("%s",modify_mojority);
    take_in_line_break();
    //输入0退出
    if(char_return_by_zero(p->Stu.majority))
    {
		printf("||退出成功\n");
		system("pause");
		system("cls");
        return;
	}
    strcpy(p->Stu.majority,modify_mojority);
    printf("||修改成功\n||");
    system("pause");
}

//通过姓名修改学生信息
void modify_by_name(void)
{
	system("cls");
	//定义一个整型变量stu_id,id_flag判断重新修改的学号是否有重复
	//stu_flag判断是否能找到学生,modify_id代表要修改的学生,class_number代表班级号
	int id_flag = 0,stu_flag = 0,modify_id = 0,class_number = 0;
    //定义一个stu类型的指针指向学生信息链表的头节点stu_list,用于遍历链表
	stu *p = stu_list;
	char modify_mojority[MAJORITY],stu_name[NAME_LEN];

	//提示用户输入信息
	printf("||===================================||\n");
	printf("||请输入你要修改的学生姓名(输入0退出)||\n||");
  	scanf("%s",stu_name);
    take_in_line_break();
    //如果输入"0"退出
    if(char_return_by_zero(stu_name))return;
    
	if(stu_list == NULL)
	{
        printf("||不存在该学生\n||");
        system("pause");
        system("cls");
        return;
	}
	
	system("cls");
	stu_flag = 0;
	//对学生链表进行搜寻,寻找该学生
	for(p = stu_list;p;p = p->next)
	{
		//如果用户输入的学生学号和链表中对应的学生学号匹配则进入if语句
		if(strcmp(p->Stu.name,stu_name) == 0)
			{
				//提示该学生的信息
				printf("||学号============姓名============班级============专业============分数=======||\n");
				printf("||%d\t\t%s\t\t%s\t\t %s\t\t  %.2f\t     ||\n",p->Stu.id,p->Stu.name,p->Stu.class,p->Stu.majority,p->Stu.grade);
				stu_flag = 1;
				break;
			}
        //若未能匹配且以及到链表末尾则进入if语句
		if(strcmp(p->Stu.name,stu_name) != 0 && p->next == NULL)
            {
			    //提示未能找到该学生
		        printf("||!【未能找到该学生】!\n||");
		        system("pause");
		        system("cls");
		    }
	}
	//如果未找到学生则返回
	if(!stu_flag)return;

	printf("||===========================================================================||\n");
	printf("||——请重新输入该学生信息以作修改——\t\t\t\t\t     ||\n||");
	system("pause");

	do
	{
	    system("cls");
	    id_flag = 0;
		//提示用户输入要录入学生的学号
	    printf("||——请输入你要修改学生的学号(范围1000~9999)(输入0退出)——\n");
	    printf("||——如果输入了小数则按整数部分修改——\n||");
	    if(scanf("%d",&modify_id) != 1)
	    {
		    take_in_line_break();
	        //提示用户错误原因
			printf("||!【要求输入四位整数】!\n||");
			system("pause");
			system("cls");
	        continue;
	    }
	    take_in_line_break();
	    //如果用户输入0则退出循环
	    if(!modify_id)break;
	    //如果用户输入
	    else if(modify_id > 9999 ||modify_id <1000)
	    {
	     	//提示用户输入四位整数
	     	printf("||!【要求输入四位整数】!\n||");
			system("pause");
			system("cls");
	        continue;
		}
		stu *find = stu_list;
  		//遍历链表,查看学号是否有重复
        for(find = stu_list;find;find = find->next)
        {
            //如果学号重复则提示用户重新输入
        	if(find->Stu.id == modify_id && find->Stu.id != p->Stu.id)
        	{
        	    id_flag = 1;
				printf("||输入的学号和当前学生链表中的某个学生学号相同,请重新输入\n||");
			    system("pause");
			    system("cls");
	        }
	        if(id_flag)break;
		}
		if(id_flag)continue;
		break;
	}while(1);
    //输入0退出
    if(return_by_zero(modify_id))return;
    p->Stu.id = modify_id;

    system("cls");
    do
    {
        system("cls");
        //提示用户要录入学生的班级
        printf("||——请输入你要修改学生的班级(要输入如果14班则只输入14即可)\n||(只能输入一或两位数)(输入0退出)——\n");
        printf("||——如果输入小数则取整数部分\n||");
        if(scanf("%d",&class_number) != 1)
        {
            take_in_line_break();
            printf("||要求输入整数\n||");
            system("pause");
            system("cls");
            continue;
		}
		take_in_line_break();
		if(class_number > 99 ||class_number < 0)
		{
		    printf("||要求输入一或两位数\n||");
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
    //提示用户输入学生专业
	printf("||——请输入学生专业(输入'0'退出)——\n||");
	scanf("%s",modify_mojority);
    take_in_line_break();
    //输入0退出
    if(char_return_by_zero(p->Stu.majority))
	{
		printf("||退出成功\n||");
		system("pause");
		system("cls");
        return;
    }
    strcpy(p->Stu.majority,modify_mojority);
    printf("||修改成功\n||");
    system("pause");
}

//教师删除学生身份信息
void remove_student_id_info(void)
{
	enum Choice{id = 1,name,go_back}choice;
	
    do
	{
	    system("cls");
        //提示用户输入信息
        printf("||==============================||\n");
	    printf("||请输入你要删除的学生身份信息  ||\n");
	    printf("||==============================||\n");
	    printf("||1.通过学号删除\t\t||\n");
	    printf("||2.通过姓名删除\t\t||\n");
	    printf("||3.返回菜单\t\t\t||\n");
        printf("||==============================||\n||");
	   	if(scanf("%d",&choice) != 1)//如果choice不是整数类型则进入if语句
	    {
		    //提示用户错误原因
		    printf("||要求输入整数\n");
		    input_again();//提示用户重新输入
		    continue;//重新循环
	    }
	    take_in_line_break();
	    switch(choice)
	    {
	        case id://学号删除
                remove_id_by_id();
                break;
	        case name://姓名删除
		        remove_id_by_name();
		        break;
	  	    case go_back://返回菜单
				system("cls");
				break;
	        default ://其他输入
				printf("||!【输入错误】!\n||");
				system("pause");
		        break;
     	}
	    //保存学生信息
        tea_save_stu(5);
	    save_id_studentinfo();
     	if(choice == go_back)break;
	}while(1);
	system("cls");
}

//通过学号删除学生身份信息
void remove_id_by_id(void)
{
	system("cls");
	//定义整型变量stu_id,由用户赋值,来匹配对应要删除的学生,flag用于确定用户是否要删除学生身份信息
	int stu_id = 0;
	char flag;
	//定义一个stu类型的指针指向学生链表的表头stu_list,用于遍历链表;定义了stu类型的指针变量p1用于删除学生身份信息
	stu *p = stu_list,*p1 = NULL;
	
    do
    {
    	//提示用户输入信息
        printf("||===================================||\n");
	    printf("||请输入你要删除的学生学号(输入0退出)||\n||");
	   	if(scanf("%d",&stu_id) != 1)//如果stu_id不是整数类型则进入if语句
	    {
		    //提示用户错误原因
		    printf("||要求输入整数\n");
		    input_again();//提示用户重新输入
		    continue;//重新循环
	    }
	    break;
	}while(1);
    take_in_line_break();
	//输入0退出
	if(return_by_zero(stu_id))return;
    
	if(stu_list == NULL)
	{
        printf("||不存在该学生\n||");
        system("pause");
        system("cls");
        return;
	}
    
	system("cls");
    //将p指向学生信息链表的表头,进行遍历链表
	for(p = stu_list;p;p = p->next)
        //如果用户输入学生学号和链表中对应的学生学号匹配则进入if语句,并标记flag为一,说明以及找到该学生,并退出循环
		if(p->Stu.id == stu_id)
		{
			flag = 1;
			break;
		}
    //如果flag还是为0则说明找不到匹配学生则进入if语句提示用户
	if(flag == 0)
	{
		printf("!【找不到该学生】!\n");
		system("pause");
		system("cls");
    }
    //如果flag为1说明找到了则进入else语句
	else
	{
		//因为只知道该学生当前所在位置还不能删除信息,要知道该学生前面的学生的next才能删除
        //所以再对其循环
	    for(p = stu_list;p;p = p->next)
	    {
	    	//如果该用户输入的学生学号和对应的学生学号匹配则进入语句
		    if(p->Stu.id == stu_id)
		    {
		    	do
		    	{
		    	    //提示用户该学生信息
			        printf("||学号============姓名============班级============专业============分数==||\n");
			        printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t||\n",p->Stu.id,p->Stu.name,p->Stu.class,p->Stu.majority,p->Stu.grade);
			        //提示用户是否确定删除
                    printf("||——确定删除吗？(输入y则删除,输入其他字符则取消删除)——\t\t||\n||");
					//如果用户只输入回车符则进入循环直到不输入回车符为止
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
                	//再判断该学生位于学生链表的表头,或者表尾
                	//如果该学生位于表头则进入if语句
                    if(p == stu_list)
                    {
                    	//将学生链表的表头指向第二个节点然后再释放p,此时p指向表头,释放p相当于释放最开始的表头
                	    stu_list = stu_list->next;
                	    free(p);//释放表头内存
						p = NULL;//避免悬空指针
				    }
                    //如果位于表尾则进入if语句
				    else if(p->next == NULL)
                        {
					        free(p);
					        p = NULL;
					    }
                    //提示用户删除成功
				    printf("||——删除成功！——\n||");
				    system("pause");
			    }
			    else
				{
				    printf("||取消删除\n||");
				    system("pause");
				}
			    break;
		    }
		    
		    //如果该学生位于链表中间则进入if语句
		    if(p->next->Stu.id == stu_id)
		    {
		    	do
		    	{
		    	    //提示用户该学生信息
			        printf("||学号============姓名============班级============专业============分数==||\n");
			        printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t||\n",p->next->Stu.id,p->next->Stu.name,
					p->next->Stu.class,p->next->Stu.majority,p->Stu.grade);
			        //提示用户是否确定删除
                    printf("||——确定删除吗？(输入y则删除,输入其他字符则取消删除)——\t\t||\n||");
					//如果用户只输入回车符则进入循环直到不输入回车符为止
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
                
                //确认删除输入y则进入语句
                if(flag == 'y')
                {
                	//将p1指向要删除的学生
            	    p1 = p->next;
            	    //将要删除的学生被替换要删除的学生的下一个学生
            	    p->next = p->next->next;
            	    //释放p1,p1指向要删除的学生,释放p1相当于删除了学生
            	    free(p1);
					p1 = NULL;//避免悬空指针
					//提示用户删除成功
			        printf("||——删除成功!——\n||");
			        system("pause");
			    }
			    else
			    {
				    printf("||取消删除\n||");
				    system("pause");
				}
			    break;
		    }
	    }
	}
}

//通过名字删除学生身份信息
void remove_id_by_name(void)
{
	system("cls");
	//flag用来确定学生信息是否要删除
	int flag = 0;
	//stu_name由用户输入,和链表相对应的学生匹配
	char stu_name[NAME_LEN];
	//定义stu类型的指针变量p指向当前学生链表的表头,用于遍历链表;再定义stu类型的指针变量用来删除要删除的学生
	stu *p = stu_list,*p1 = NULL;

	//提示用户输入信息
 	printf("||=====================================||\n");
	printf("||请输入你要删除的学生姓名(只输入0退出)||\n||");
	scanf("%s",stu_name);
    take_in_line_break();
    
	if(stu_list == NULL)
	{
        printf("||不存在该学生\n||");
        system("pause");
        system("cls");
        return;
	}
    
	//输入0退出
	if(char_return_by_zero(stu_name))return;
	system("cls");
	
    //将p指向学生信息链表的表头,进行遍历链表
	for(p = stu_list;p;p = p->next)
		//如果用户输入学生姓名和链表中对应的学生姓名匹配则进入if语句,并标记flag为一,说明以及找到该学生,并退出循环
		if(strcmp(p->Stu.name,stu_name) == 0)
		{
			flag = 1;
			break;
		}
    //如果flag还是为0则说明找不到匹配学生则进入if语句提示用户
	if(flag == 0)
	{
		printf("!【找不到该学生】!\n");
		system("pause");
		system("cls");
    }
	else
	{
		//因为只知道该学生当前所在位置还不能删除信息,要知道该学生前面的学生的next才能删除
        //所以再对其循环
	    for(p = stu_list;p;p = p->next)
	    {
	    	//如果该用户输入的学生姓名和对应的学生姓名匹配则进入语句
		    if(strcmp(p->Stu.name,stu_name) == 0)
		    {
		    	do
		    	{
		    	    //提示用户该学生的信息
			        printf("||学号============姓名============班级============专业============分数==||\n");
			        printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t||\n",p->Stu.id,p->Stu.name,p->Stu.class,p->Stu.majority,p->Stu.grade);
			        //提示用户是否要删除
                    printf("||——确定删除吗？(输入y则删除,输入其他字符则取消删除)——\t\t||\n||");
					//如果用户只输入回车符则进入循环直到不输入回车符为止
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
                
                //如果确定要删除则进入if语句
                if(flag == 'y')
                {
                	//如果p指向学生信息链表的表头则进入if语句
                    if(p == stu_list)
                    {
                        //将表头指向第二个学生
                	    stu_list = stu_list->next;
                	    //再释放p,释放前p指向表头所以释放p相当于删除表头,且第二个学生成为新表头
                	    free(p);
                        p = NULL;//避免悬空指针
				    }
				    //如果该学生为链表表尾则直接释放
				    else if(p->next == NULL)
				    {
					    free(p);
					    p = NULL;
					}
                    //提示用户释放成功
				    printf("||——删除成功！——\n||");
				    system("pause");
			    }
			    else
			    {
				    printf("||取消删除\n||");
				    system("pause");
				}
			    break;
		    }
		    //如果学生位于之间则进入if语句
		    if(strcmp(p->next->Stu.name,stu_name) == 0)
		    {
		    	do
		    	{
                    //提示用户该学生信息
			        printf("||学号============姓名============班级============专业============分数==||\n");
			        printf("||%d\t\t%s\t\t%s\t\t%s\t\t%.2f\t||\n",p->next->Stu.id,p->next->Stu.name,p->next->Stu.class,p->next->Stu.majority,p->next->Stu.grade);
			        //提示用户确定是否要删除该学生身份信息
                    printf("||——确定删除吗？(输入y则删除,输入其他字符则取消删除)——\t\t||\n||");
                    //如果用户只输入回车符则进入循环直到不输入回车符为止
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
                	//将p1指向要删除的学生
            	    p1 = p->next;
            	    //将要删除的学生替换为要删除的学生的下一个学生
            	    p->next = p->next->next;
            	    //然后再释放p1,此时释放p1相当于删除该学生
            	    free(p1);
            	    p1 = NULL;//避免悬空指针
                    //提示用户删除成功
			        printf("||——删除成功】——\n||");
			        system("pause");
			    }
			    else 
			    {
				    printf("||取消删除\n||");
				    system("pause");
				}
			    break;
		    }
	    }
	}
}

//删除学生考试信息
void remove_student_exam_info(void)
{
	//读取学生考试信息
	read_stu_exam_list();
	enum Choice{id = 1,name,go_back}choice;
	
    do
	{
		//提示用户输入信息
	    system("cls");

        printf("||==============================||\n");
	    printf("||请输入你要删除的学生考试信息  ||\n");
	    printf("||==============================||\n");
	    printf("||1.通过学号删除\t\t||\n");
	    printf("||2.通过姓名删除\t\t||\n");
	    printf("||3.返回菜单\t\t\t||\n");
        printf("||==============================||\n||");
	   	if(scanf("%d",&choice) != 1)//如果choice不是整数类型则进入if语句
	    {
	    	getchar();
		    //提示用户错误原因
		    printf("||要求输入整数\n||");
		    system("pause");
		    system("cls");
		    continue;//重新循环
	    }
	    take_in_line_break();
	    switch(choice)
	    {
	        case id://学号删除学生考试信息
                remove_exam_by_id();
                break;
	        case name://姓名删除学生考试信息
		        remove_exam_by_name();
		        break;
	  	    case go_back://返回菜单
				system("cls");
				break;
	        default ://其他输入
				printf("||!【输入错误】!\n||");
		        break;
     	}
     	if(choice == go_back)break;
     }while(1);
     //读取学生考试信息之后删除学生考试信息链表
    delete_stu_exam_list();
    //保存信息到"studentinfo.txt"文件中
	save_id_studentinfo();
	system("cls");
}

//通过学号删除学生考试信息
void remove_exam_by_id(void)
{
	system("cls");
	//delete_stu_id代表要删除的学生学号,flag用来判断用户输入的学号是否存在学生考试信息链表中
	//i用来循环打印学生填空题考试答案,gf_questions_count用来记录填空题题数
	int delete_stu_id,flag = 0,i = 0,gf_questions_count;
	//定义一个Student_timu_list类型的指针p指向学生考试信息链表的表头student_timu_list
	//在定义一个同样为Student_timu_list类型的指针p1置为空
	Student_timu_list *p = student_timu_list,*p1 = NULL;
	char ch;//ch判断用户是否确定要删除该学生

    //以只读的方式打开"timu(clear)"的文本文件,并定义一个文件指针指向该文件
	FILE *fpr = fopen("timu(clear).txt","r");
    if(fpr == NULL)
    {
    	printf("||删除失败\n||");
    	system("pause");
    	system("cls");
    	return;
	}
	//在文件中读取填空题的题数
	fscanf(fpr,"%*d,%*d,%d",&gf_questions_count);
	fclose(fpr);//关闭文件

    do
    {
    	//提示用户输入
        printf("||===================================||\n");
	    printf("||请输入你要删除的学生学号(输入0退出)||\n||");
 		//如果用户输入的学生学号不为数字则进入if语句提示用户错误原因
	    if(scanf("%d",&delete_stu_id) != 1)
	    {
	 		//提示用户错误原因
		    printf("||要求输入整数\n");
		    system("pause");
			system("cls");
		    continue;//重新循环
		}
		break;
	}while(1);
    take_in_line_break();
    //输入0退出
    if(return_by_zero(delete_stu_id))return;
    
	if(stu_list == NULL)
	{
        printf("||不存在该学生\n||");
        system("pause");
        system("cls");
        return;
	}
    
	system("cls");
	//在学生考试信息链表中寻找该学生
	for(p = student_timu_list;p;p = p->next)
		if(p->stu_timu.Stu.id == delete_stu_id)
		{
			flag = 1;//如果找到该学生,则让flag赋值为1
			break;//找到之后停止寻找
		}
    //如果flag == 0则说明找不到该学生
	if(flag == 0)
	{
		//提示用户找不到该学生
		printf("||!【找不到该学生】!\n||");
		system("pause");//暂停给用户浏览
		system("cls");
    }
    //否则进入else语句
	else
	{
		//定义stu类型的指针pt2指向学生信息链表表头
		stu *pt2 = stu_list;
		//寻找到相应学生
		for(pt2 = stu_list;pt2;pt2 = pt2->next)
			if(pt2->Stu.id == p->stu_timu.Stu.id)//如果找到则进入if语句进行相关操作
			{
				//找到之后则把学生信息链表中的成绩和考试状态赋给要删除的学生的信息
				p->stu_timu.Stu.examination_status = pt2->Stu.examination_status;
				p->stu_timu.Stu.grade = pt2->Stu.grade;
			    break;
			}
        //提示用户当前学生信息
		printf("||专业======班级======学号======姓名======成绩======考试状态==学生判断题答案=====学生选择题答案=====学生填空题答案||\n");
 		printf("||%s    %s      %d       %s     %.2f  %d      \t%s     \t\t%s\t\t",p->stu_timu.Stu.majority,
		 p->stu_timu.Stu.class,p->stu_timu.Stu.id,p->stu_timu.Stu.name,p->stu_timu.Stu.grade,
		 p->stu_timu.Stu.examination_status,p->stu_timu.stu_tf_answer,p->stu_timu.stu_choice_answer);
		for(i = 0;i < gf_questions_count;i++)
		    printf("(%d).%s\t",i+1,p->stu_timu.stu_gf_answer[i]);
        //提示用户是否删除
        printf("\n||——确定删除该学生考试信息吗？(输入y则删除,输入其他字符则取消删除)——||\n||");
        while(1)//while作用为：直到用户第一个字符不输入换行符
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
		//如果输入y则进入
        if(ch == 'y')
        {
        	//将原先还未修改的学生考试信息记录到名为"stu1"的文本文件上
            save_stu1(p->stu_timu.Stu.id);
            //以下开始修改
            //将成绩和考试状态置为0
			p->stu_timu.Stu.grade = 0;
			p->stu_timu.Stu.examination_status = 0;
			p->stu_timu.stu_full_mark = 0;
			//将所有答案置为"no"
            strcpy(p->stu_timu.stu_tf_answer,"no");
            strcpy(p->stu_timu.stu_choice_answer,"no");
			for(i = 0;i < gf_questions_count;i++)
				strcpy(p->stu_timu.stu_gf_answer[i],"no");
			//将学生信息上的成绩和考试状态也置为0
			pt2->Stu.examination_status = 0;
			pt2->Stu.grade = 0;
			//提示用户删除成功
			printf("||——删除成功!——\n||");
			system("pause");
			system("cls");
			save_id_studentinfo();
			tea_save_stu(3);//保存删除后的信息
		}
	}
}

//通过姓名删除学生考试信息
void remove_exam_by_name(void)
{
	system("cls");
	//flag用来判断用户输入的学号是否存在学生考试信息链表中
	//i用来循环打印学生填空题考试答案,gf_questions_count用来记录填空题题数
	int flag = 0,i = 0,gf_questions_count = 0;
	//delete_stu_name用来给用户输入要删除的学生姓名
	char delete_stu_name[NAME_LEN];
	//定义一个Student_timu_list类型的指针p指向学生考试信息链表的表头student_timu_list
	//在定义一个同样为Student_timu_list类型的指针p1置为空
	Student_timu_list *p = student_timu_list,*p1 = NULL;
	char ch;//ch判断用户是否确定要删除该学生

    //以只读的方式打开"timu(clear)"的文本文件,并定义一个文件指针指向该文件
	FILE *fpr = fopen("timu(clear).txt","r");
	if(fpr == NULL)
    {
    	printf("||删除失败\n||");
    	system("pause");
    	system("cls");
    	return;
    }
	//在文件中读取填空题的题数
	fscanf(fpr,"%*d,%*d,%d",&gf_questions_count);
	fclose(fpr);//关闭文件

	//提示用户输入
	printf("||===================================||\n");
	printf("||请输入你要删除的学生姓名(输入0退出)||\n||");
	scanf("%s",delete_stu_name);
    take_in_line_break();
    //输入"0"退出
    if(char_return_by_zero(delete_stu_name))return;
    
	if(stu_list == NULL)
	{
        printf("||不存在该学生\n||");
        system("pause");
        system("cls");
        return;
	}
    
	system("cls");
	//在学生考试信息链表中寻找该学生
	for(p = student_timu_list;p;p = p->next)
		if(strcmp(p->stu_timu.Stu.name,delete_stu_name) == 0)
			flag = 1;
    //说明找不到该学生
	if(flag == 0)
	{
		//提示用户找不到
		printf("||!【找不到该学生】!\n||");
		system("pause");
		system("cls");
    }
    //否则进入else语句
	else
	{
		//定义stu类型的指针pt2指向学生信息链表表头
		stu *pt2 = stu_list;
		//寻找到相应学生
		for(pt2 = stu_list;pt2;pt2 = pt2->next)
			if(pt2->Stu.id == p->stu_timu.Stu.id)//如果找到则进入if语句进行相关操作
			{
				//找到之后则把学生信息链表中的成绩和考试状态赋给要删除的学生的信息
				p->stu_timu.Stu.examination_status = pt2->Stu.examination_status;
				p->stu_timu.Stu.grade = pt2->Stu.grade;
			    break;
			}
        //提示用户当前学生信息
		printf("||专业======班级======学号======姓名======成绩======考试状态==学生判断题答案=====学生选择题答案=====学生填空题答案||\n");
 		printf("||%s    %s      %d       %s     %.2f  %d      \t%s     \t\t%s\t\t",p->stu_timu.Stu.majority,p->stu_timu.Stu.class,p->stu_timu.Stu.id,p->stu_timu.Stu.name,p->stu_timu.Stu.grade,p->stu_timu.Stu.examination_status,p->stu_timu.stu_tf_answer,p->stu_timu.stu_choice_answer);
		for(i = 0;i < gf_questions_count;i++)
		    printf("(%d).%s\t",i+1,p->stu_timu.stu_gf_answer[i]);
        //提示用户是否要删除
        printf("\n||——确定删除该学生考试信息吗？(输入y则删除,输入其他字符则取消删除)——||\n||");
        while(1)//while作用为：直到用户第一个字符不输入换行符
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
		//如果输入y则进入
        if(ch == 'y')
        {
        	//将原先还未修改的学生考试信息记录到名为"stu1"的文本文件上
            save_stu1(p->stu_timu.Stu.id);
            //以下开始修改
            //将成绩和考试状态置为0
			p->stu_timu.Stu.grade = 0;
			p->stu_timu.Stu.examination_status = 0;
			p->stu_timu.stu_full_mark = 0;
			//将所有答案置为"no"
            strcpy(p->stu_timu.stu_tf_answer,"no");
            strcpy(p->stu_timu.stu_choice_answer,"no");
			for(i = 0;i < gf_questions_count;i++)
				strcpy(p->stu_timu.stu_gf_answer[i],"no");
			//将学生信息上的成绩和考试状态也置为0
			pt2->Stu.examination_status = 0;
			pt2->Stu.grade = 0;
			//提示用户删除成功
			printf("||——删除成功!——\n||");
			system("pause");
			system("cls");
			tea_save_stu(3);//保存删除后的信息
		}
	}
}

//开始时读取文件stu.txt到学生信息链表上
void read_stu_exam_list(void)
{
	//以只读的方式打开名为"stu(clear)"的文本文件,并定义一个指向文本文件类型的指针fpr1指向该文件
	FILE *fpr1 = fopen("stu(clear).txt","r");
	if(fpr1 == NULL)//打开失败时
		return;
	//i代表实时填空题题数,j代表一道填空题的实时字数,gf_count代表总的填空题数目
	int i = 0,j = 0,gf_questions_count = 0,tf_questions_count = 0,Choice_questions_count = 0;
	//temp暂时储存一个文件中的字符,判段该字符是否有效,有效则赋给填空题答案中的某个元素
	char temp;
	
	//以只读的方式打开名为"timu(clear)"的文本文件,并定义一个指向文本文件类型的指针fpr2指向该文件
	FILE *fpr2 = fopen("timu(clear).txt","r");
	//读取填空题的题数
	if(fpr2 == NULL)
		return;
	fscanf(fpr2,"%d,%d,%d",&tf_questions_count,&Choice_questions_count,&gf_questions_count);
	fclose(fpr2);//关闭文件

	if(tf_questions_count == 0 || Choice_questions_count == 0 || gf_questions_count == 0)return;

	else
	{
		//如果读到末尾则退出
		if(fgetc(fpr1) == EOF)return;
		rewind(fpr1);//由于上一行if语句已经读入一个字符了,所以需要将指针重新移到开头
		
		while(1)//指针移到文件末尾结束
		{
			//开辟一个Student_timu_list类型的内存,定义一个Student_timu_list类型的指针p1指向该内存
			Student_timu_list *p1 = (Student_timu_list *)malloc(sizeof(Student_timu_list));

            //将文件中的学生考试信息读入到学生考试信息链表中
	        fscanf(fpr1,"%s %s %d %s %f %s %s ",p1->stu_timu.Stu.majority,p1->stu_timu.Stu.class,&p1->stu_timu.Stu.id,p1->stu_timu.Stu.name,&p1->stu_timu.stu_full_mark,p1->stu_timu.stu_tf_answer,p1->stu_timu.stu_choice_answer);
	        //读取学生填空题题目
			for(i = 0;i < gf_questions_count;i++)
			{
				for(j = 0;;j++)
                {
				    //temp暂时存储读取文件的字符
				    temp = fgetc(fpr1);
				    if(temp == EOF)
				    {
					    //提示用户错误原因
					    system("cls");
					    break;
				    }
				    if(temp == '\n')break;
				    else if(temp == 35)break;
				    p1->stu_timu.stu_gf_answer[i][j] = temp;
				}
				//将有效字符最末尾置为'\0'
			    p1->stu_timu.stu_gf_answer[i][j] = '\0';
			    //读到换行符,则结束该学生的循环,接到下个学生的循环
				if(temp == '\n')break;
				//如果temp为EOF(即读到末尾)则结束循环,退出该功能
				else if(temp == EOF)break;
			}
            //如果temp为EOF(即读到末尾)则结束循环,退出该功能
			if(temp == EOF) break;
			p1->next = NULL;//将末尾置为空
			//如果学生信息链表的表头不为空则进入if语句
			if(student_timu_list)
			{
				//用尾插法插入
                //假设要插入4
                //则插入前链表为：1->5->0->2->NULL
                //则插入后链表为：1->5->0->2->4->NULL
				//定义Student_timu_list类型的指针p指向学生考试信息链表的表头
				Student_timu_list *p = student_timu_list;
				//将p指到链表的末尾
				for(;p->next;p = p->next);
				//再将最新的插入到末尾中
				p->next = p1;
			}
			//如果学生信息链表的表头为空,则将该信息作为表头
			else student_timu_list = p1;
		}
	}
	fclose(fpr1);//关闭文件
	//如果temp为EOF(即读到末尾)则结束循环,退出该功能
	if(temp == EOF)return;
}

//保存信息到stu1.txt中,delete_stu_id为要删除学生的学号,用于找到相应学生
void save_stu1(int delete_stu_id)
{
	//以只读的方式打开名为"timu(clear)"的文本文件,并定义一个指向文本文件类型的指针fpr指向该文件
	FILE *fpr = fopen("timu(clear).txt","r");
	//以在末尾追加的方式打开名为"stu1"的文本文件,并定义一个指向文本文件类型的指针fpw指向该文件
    FILE *fpw = fopen("stu1.txt","a+");
    //gf_questions_count代表填空题数目,i用于循环输入填空题答案
    int gf_questions_count = 0,i = 0;
    
    //如果返回指针为空,则说明打开失败
    if(fpw == NULL || fpr == NULL)
	{
		printf("||!【保存失败】!\n||");
		system("pause");
		return;
	}
	
    //读取填空题题数
    fscanf(fpr,"%*d,%*d,%d",&gf_questions_count);
    fclose(fpr);//关闭文件
    
    //定义一个Student_timu_list类型的指针p指向学生考试信息链表表头
    Student_timu_list *p = student_timu_list;
    //遍历链表直到找到该学生,由于该信息是在找到该学生的前提下得到的,所以不存在找不到该学生的情况
    for(p = student_timu_list;p;p = p->next)
        //如果形参中(用户输入)的学号和链表中相对应学生的学号匹配则进入if语句
    	if(p->stu_timu.Stu.id == delete_stu_id)
        {
        	//将该学生信息输入到文件中
		    fprintf(fpw,"%s %s %d %s %f %d %s %s",p->stu_timu.Stu.majority,p->stu_timu.Stu.class,p->stu_timu.Stu.id,p->stu_timu.Stu.name,p->stu_timu.Stu.grade,p->stu_timu.Stu.examination_status,p->stu_timu.stu_tf_answer,p->stu_timu.stu_choice_answer);
		    //循环将学生填空题答案用循环输入进去
            for(i = 0;i < gf_questions_count;i++)
			    fprintf(fpw," %s",p->stu_timu.stu_gf_answer[i]);
		    fprintf(fpw,"\n");//输入换行符以便下一个学生能顺利输入
		    break;
		}
    //提示用户信息保存成功
    printf("||——保存信息成功！——\n");
    
    fclose(fpw);//关闭文件
}

//信息使用结束后将学生信息链表删除
void delete_stu_exam_list(void)
{
	//到学生考试链表不为空时一直循环
	while(student_timu_list)
	{
		//定义一个Student_timu_list类型的指针p指向表头
		Student_timu_list *p = student_timu_list;
		//将表头指向表头的下一个节点,来作为新的表头
		student_timu_list = student_timu_list->next;
		//此时p为原来的表头,释放p相当于删除原来的表头
		free(p);
	}
	//将表头置为空
	student_timu_list = NULL;
}

//老师保存学生信息到stu.txt和stu(clear).txt,flag说明要保存的模式
void tea_save_stu(int flag)
{
	//flag == 3代表删除或修改某个或一些学生考试信息后保存全部学生考试信息到"stu(clear)"和"stu"文本文件中
	if(flag == 3)
	{
	    //以只写的方式打开名为"stu(clear)"的文本文件,并定义一个指向文本文件类型的指针fpw1指向该文件
	    FILE *fpw1 = fopen("stu(clear).txt","w");
 	    //以只写的方式打开名为"stu"的文本文件,并定义一个指向文本文件类型的指针fpw2指向该文件
	    FILE *fpw2 = fopen("stu.txt","w");
	    //i用来循环输入填空题答案,gf_questions_count代表填空题题数
	    int i = 0,gf_questions_count = 0;
	
	    //以只读的方式打开名为"timu(clear)"的文本文件,并定义一个指向文本文件类型的指针fpr1指向该文件
	    FILE *fpr1 = fopen("timu(clear).txt","r");
	    if(fpr1 == NULL)return;
	    //读取填空题题数
	    fscanf(fpr1,"%*d,%*d,%d",&gf_questions_count);
	    fclose(fpr1);//关闭文件
	
        //定义一个Student_timu_list类型的指针p1指向学生考试链表的表头
	    Student_timu_list *p1 = student_timu_list;
	
        //用for循环将所有学生的考试信息都输入到"stu(clear)"文本文件中
	    for(p1 = student_timu_list;p1;p1 = p1->next)
	    {
		    fprintf(fpw1,"%s %s %d %s %f %s %s ",p1->stu_timu.Stu.majority,
			p1->stu_timu.Stu.class,p1->stu_timu.Stu.id,p1->stu_timu.Stu.name,
			p1->stu_timu.Stu.grade,p1->stu_timu.stu_tf_answer,p1->stu_timu.stu_choice_answer);
		    for(i = 0;i < gf_questions_count-1;i++)
			    fprintf(fpw1,"%s#",p1->stu_timu.stu_gf_answer[i]);
		    fprintf(fpw1,"%s",p1->stu_timu.stu_gf_answer[gf_questions_count-1]);
		    fprintf(fpw1,"\n");//输入换行符,方便下一个学生信息录入
	    }
	
	    fclose(fpw1);//关闭文件
	
        //将相应内容打印出来
	    fprintf(fpw2,"专业******班级*****学号******姓名******成绩******学生判断题答案*****学生选择题答案*****学生填空题答案\n");
         //用for循环将所有学生的考试信息都输入到"stu"文本文件中
	    for(p1 = student_timu_list;p1;p1 = p1->next)
	    {
	        fprintf(fpw2,"%s\t%s\t%d\t%s\t%f\t%s\t\t%s\t\t",p1->stu_timu.Stu.majority,p1->stu_timu.Stu.class,
			p1->stu_timu.Stu.id,p1->stu_timu.Stu.name,p1->stu_timu.Stu.grade,p1->stu_timu.stu_tf_answer,p1->stu_timu.stu_choice_answer);
	        for(i = 0;i < gf_questions_count;i++)
		        fprintf(fpw2,"(%d).%s\t",i+1,p1->stu_timu.stu_gf_answer[i]);
	        fprintf(fpw2,"\n");
	    }
	
	    fclose(fpw2);//关闭文件
	}
	
	//flag == 2代表将新录入的学生信息保存到"stu(clear)"和"stu"文本文件中
	else if(flag == 2)
	{
	    //以只读的方式打开名为"studentinfo"的文本文件,并定义一个指向文本文件类型的指针fpr2指向该文件
		FILE *fpr2 = fopen("studentinfo.txt","r");
 	    //以只读的方式打开名为"timu(clear)"的文本文件,并定义一个指向文本文件类型的指针fpr3指向该文件
		FILE *fpr3 = fopen("timu(clear).txt","r");
 	    //以在末尾追加的方式打开名为"stu(clear)"的文本文件,并定义一个指向文本文件类型的指针fpw3指向该文件
		FILE *fpw3 = fopen("stu(clear).txt","a+");
 	    //以在末尾追加的方式打开名为"stu"的文本文件,并定义一个指向文本文件类型的指针fpw4指向该文件
		FILE *fpw4 = fopen("stu.txt","a+");
		
		//如果其中一个得到的指针为空则提示用户并退出
		if(fpr2 == NULL || fpr3 == NULL || fpw3 == NULL || fpw4 == NULL)
		{
			printf("打开文件失败\n");
			system("pause");
			system("cls");
			return;
		}
		//gf_questions_count代表填空题题数,i用于循环输入学生填空题答案
		int gf_questions_count = 0,i = 0;
		//定义一个stu类型的指针p1指向学生学习链表的表头,由于新录取的学生信息使用头插法插入的
		//所以p1所指的节点就是新录入得到的学生信息,一次*p1则道标新录入的学生信息,可以对此将他的题目答案都初始化为no
		stu *p1 = stu_list;
		//定义p2类型的变量用于存储新录入的学生信息
 		Student_timu p2;
		
		//读取填空题题数
		fscanf(fpr3,"%*d,%*d,%d\n",&gf_questions_count);
		fclose(fpr3);//关闭文件
		
		//将学生信息文件的第一个(也相当于表头)几点读到表头中,由于录入新学生信息为头插法,所以得到的信息为新录入的学生信息
		fscanf(fpr2,"%d %s %s %s %d %f %d",&(p1->Stu.id),p1->Stu.name,p1->Stu.class,p1->Stu.majority,&(p1->Stu.password),&(p1->Stu.grade),&(p1->Stu.examination_status));
		fclose(fpr2);//关闭文件

        //将刚读到表头信息的p1赋值给p2中的Stu
		p2.Stu = p1->Stu;
        //将p2所指的所有题目答案都初始化为"no"
		strcpy(p2.stu_tf_answer,"no");
		strcpy(p2.stu_choice_answer,"no");
		for(i = 0;i < gf_questions_count;i++)
			strcpy(p2.stu_gf_answer[i],"no");
			
		//以在末尾追加的方式将信息输入到文件末尾
        fprintf(fpw3,"%s %s %d %s %f %s %s ",p2.Stu.majority,p2.Stu.class,p2.Stu.id,p2.Stu.name,p2.Stu.grade,p2.stu_tf_answer,p2.stu_choice_answer);
		for(i = 0;i < gf_questions_count-1;i++)
			fprintf(fpw3,"%s#",p2.stu_gf_answer[i]);
		fprintf(fpw3,"%s",p2.stu_gf_answer[gf_questions_count-1]);
		fprintf(fpw3,"\n");//输入换行符方便下一位新录入的同学输入
		
		fclose(fpw3);//关闭文件
		
		//以在末尾追加的方式将信息输入到文件末尾
 	    fprintf(fpw4,"%s\t%s\t%d\t%s\t%f\t%s\t\t%s\t\t",p2.Stu.majority,p2.Stu.class,p2.Stu.id,p2.Stu.name,p2.Stu.grade,p2.stu_tf_answer,p2.stu_choice_answer);
	    for(i = 0;i < gf_questions_count;i++)
		    fprintf(fpw4,"(%d).%s\t",i+1,p2.stu_gf_answer[i]);
	    fprintf(fpw4,"\n");//输入换行符方便下一位新录入的同学输入
	    
		fclose(fpw4);//关闭文件
	}
	
	//flag == 1代表教师发布考试时,将所有同学的成绩,考试状态,题目答案都初始化,保存到"stu(clear)"和"stu"文本文件中
	else if(flag == 1)
	{
        //先读取"stu(clear)"中的信息到学生考试链表中
		read_stu_exam_list();
		//i用于循环将填空题答案初始化,gf_questions_count用于记录填空题题目数
		int i = 0,gf_questions_count = 0;
		
        //以只读的方式打开名为"timu(clear)"的文本文件,并定义一个指向文本文件类型的指针fpr4指向该文件
		FILE *fpr4 = fopen("timu(clear).txt","r");
		if(fpr4 == NULL)
		{
			printf("||读取文件失败\n||");
			system("pause");
			system("cls");
			return;
        }
 	    //读取填空题题数
		fscanf(fpr4,"%*d,%*d,%d\n",&gf_questions_count);
		fclose(fpr4);//关闭文件
		
		//定义一个Student_timu_list类型的指针p1指向学生考试信息链表表头
		Student_timu_list *p1 = student_timu_list;
		
		//将链表中所有学生的考试信息都初始化
		for(p1 = student_timu_list;p1;p1 = p1->next)
		{
			p1->stu_timu.Stu.grade = 0;
			p1->stu_timu.Stu.examination_status = 0;
			strcpy(p1->stu_timu.stu_tf_answer,"no");
			strcpy(p1->stu_timu.stu_choice_answer,"no");
			for(i = 0;i < gf_questions_count;i++)
				strcpy(p1->stu_timu.stu_gf_answer[i],"no");
		}
		//初始化后将信息保存在"stu"和"stu(clear)"的文本文件中
		tea_save_stu(3);
		//信息使用完之后则删除学生考试信息链表
		delete_stu_exam_list();
	}
	
	//flag == 4教师修改部分学生信息时,也将"stu"和"stu(clear)"文件部分信息修改
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
	
	//flag == 5教师删除部分学生信息时,也将"stu"和"stu(clear)"文件部分信息删除
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

//保存学生身份信息
void save_id_studentinfo(void)
{
	//以只写的方式打开名为"studentInfo"的文本文件,并定义一个指向文本文件类型的指针fpw指向该文件
	FILE *fpw = fopen("studentinfo.txt","w");
	//定义一个stu类型的指针指向学生信息链表的表头
	stu *p = stu_list;

	//for循环将学生信息输入
	for(;p;p=p->next)
	    fprintf(fpw,"%d %s %s %s %d %f %d\n",p->Stu.id,
		p->Stu.name,p->Stu.class,p->Stu.majority,p->Stu.password,
		p->Stu.grade,p->Stu.examination_status);
	fclose(fpw);//关闭文件
	//提示用户保存信息成功
	printf("||——学生信息文件保存成功!——\n||");
}

//查看已被删除的学生信息
void print_stu_deleted_exam_info(void)
{
	system("cls");
	//以只读的方式打开名为"stu1"的文本文件,并定义一个指向文本文件类型的指针fpr指向该文件
    FILE *fpr = fopen("stu1.txt","r");
    char ch;//ch用来读取文件中的字符
    
    //如果得到的指针为空则提示用户并退出
    if(fpr == NULL)
	{
		printf("||打开文件失败\n||");
		system("pause");
		system("cls");
		return;
	}
	//提示用户当前删除记录
	printf("||====================================================================================||\n");
	printf("||以下是已经删除的学生考试信息\t\t\t\t\t\t\t      ||\n");
	printf("||顺序为专业,班级,学号,姓名,成绩,考试状态,学生判断题答案,学生选择题答案,学生填空题答案||\n");
    while((ch = fgetc(fpr)) != EOF)//当读到文本末尾时结束循环
		printf("%c",ch);

    fclose(fpr);//关闭文件
    system("pause");//暂停给用户浏览
    system("cls");
}

//交流功能
void tea_talking(void)
{
	system("cls");
	int choice = 0;//choice用来给用户输入功能
	//前两个数组代表要答案开的文件名
	char teacher_t[TALKING_FILE_NAME] = "tea_and_tea_communication.txt";
	char student_t[TALKING_FILE_NAME] = "stu_and_tea_communication.txt";
	//由于设计原因只设置了以为教师,因此将"teacher"作为老师名字
	char teacher_name[NAME_LEN] = "teacher";
	
	while(1)
	{
		    system("cls");
	        printf("||==============================||\n");
	        printf("||1.师生交流群\t\t\t||\n");
	        printf("||2.自己交流(备忘录)\t\t||\n");
	        printf("||3.退出交流功能,返回菜单\t||\n");
	        printf("||==============================||\n||");
	 	   	if(scanf("%d",&choice) != 1)//如果choice不是整数类型则进入if语句
	        {
		        //提示用户错误原因
		        printf("||要求输入整数\n");
		        input_again();//提示用户重新输入
		        continue;//重新循环
	        }
        //如果用户选择1或2则进入语句
	    if(choice == 1 ||choice == 2)
	    {
	    	//如果选择1则进入师生交流群群
	        if(choice == 1)
	        {
	        	//接受信息和发送消息函数,其中student_t代表文件名(即要打开的文件)
                receive_message(student_t);
		        send_message(student_t,teacher_name);
	        }
	        //如果选择2则进入备忘录
	        if(choice == 2)
	        {
	        	//接受信息和发送消息函数,其中teacher_t代表文件名(即要打开的文件)
		        receive_message(teacher_t);
		        send_message(teacher_t,teacher_name);
	        }
	    }
	    //如果用户输入其他字符则进入else语句(非1非2)
	    else
		{
			//如果选择3,则提示用户退出成功
		    if(choice == 3)
		    {
			    printf("||退出成功\n||");
			    system("pause");
			    system("cls");
			    return;
		    }
		    //输入其他字符则提示用户输入有误,重新输入
			else
		    {
			    printf("||输入错误请重新输入\n||");
			    system("pause");
			    system("cls");
			    continue;//重新循环
		    }
		}
	}
	
	system("cls");
}

//接受消息功能
//receive_message是不带返回值的函数,形参是一个字符串数组用于存放要打开的文件名
void receive_message(char filename[])
{
	system("cls");
	char ch;//ch用于接受文件信息
    //以只读的方式打开名为"filename"的文本文件,并定义一个指向文本文件类型的指针fpr指向该文件
	FILE *fpr = fopen(filename,"r");
	
	//以下是不同交流文件的开头
	if(strcmp(filename,"stu_and_tea_communication.txt") == 0)
	    printf("=================================师生交流群====================================================\n");
	if(strcmp(filename,"tea_and_tea_communication.txt") == 0)
		printf("=================================教师交流群====================================================\n");
	if(strcmp(filename,"stu_and_stu_communication.txt") == 0)
		printf("=================================学生交流群====================================================\n");
    while((ch = fgetc(fpr)) != EOF)//读到文件末尾结束循环
		printf("%c",ch);//读一个字符输出一个字符
	printf("=================================之前的记录====================================================\n");
	
	fclose(fpr);//关闭文件
}

//发送消息功能
//send_message是不带返回值的函数,形参是一个字符串数组用于存放要打开的文件名
void send_message(char filename[],char username[])
{
	//以在末尾追加的方式打开名为"filename"的文本文件,并定义一个指向文本文件类型的指针fpw指向该文件
	FILE *fpw = fopen(filename,"a+");
    //sentence代表用户要交流的内容
	char sentence[LINE_LEN];
	
	//提示用户输入
	printf("||============================以下是你要输入的内容=============================================\n");
	printf("||——输入四个'#'结束——\n");//提示用户结束的的判断
	do
	{
   	    while(strcmp(gets(sentence),"\n") <= 0)
	        printf("||");
		//提示用户输入效果
		printf("||%s(输入预览)\n",sentence);
		if(strcmp(sentence,"####") == 0)break;//如果用户输入"####"则退出循环,且不输入到文件中
		fprintf(fpw,"%s:%s\n",username,sentence);
	}while(1);
	printf("||=================================交流完毕=====================================================\n");
	
	fclose(fpw);//关闭文件
}

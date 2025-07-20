
#include <pthread.h>  // 包含线程相关的函数
#include <stdio.h>    // 打印函数
#include <unistd.h>   // sleep 用的
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

// int main()
// {
// 	printf("Let's sleep for 100000ms\n");
// 	usleep(1000000);
// 	printf("Done waiting\n");
// }

// int main()
// {
// 	struct timeval cur_time;
// 	gettimeofday(&cur_time,NULL);
// 	printf("Seconds: %ld\nMicro seconds: %d\n", cur_time.tv_sec, cur_time.tv_usec);

// 	return 0;
// }

// void *print_wish(void *arg)
// {
// 	printf("I wish %s", (char *)arg);
// 	return NULL;

// }

// int main()
// {
// 	pthread_t line1;
// 	pthread_t line2;

// 	char *wish1 = "我能开家拉面馆。\n";
// 	char *wish2 = "我代码越来越好。\n";

// 	pthread_create(&line1, NULL,print_wish, (void*)wish1);
// 	pthread_create(&line2, NULL,print_wish, (void*)wish2);

// 	pthread_join(line1, NULL);
// 	pthread_join(line2, NULL);

// }

// void *print_greeting(void * arg)
// {
// 	printf("Hello from thread %d !\n", *(int*)arg);
// 	return NULL;
// }

// int main()
// {
// 	int ids[3] = {1,2,3};
// 	int i;

// 	i = 0;
// 	while(i < 3)
// 	{
// 		pthread_t threads[3];

// 		pthread_create(&threads[i], NULL, print_greeting, (void *)&ids[i]);
// 		pthread_join(threads[i], NULL);
// 		i++;
// 	}
// }

// typedef struct s_info //定义了一个结构体变量里面包含编号和名字
// {
// 	int number;
// 	char *name;
// }	t_info;

// void *print_info(void* arg) //需要传入一个结构体
// {

// 	t_info *info = (t_info *)arg;
// 	printf("Hello, I'm thread %d and my name is %s !\n", info->number, info->name);
// 	return NULL;
// }

// int main()
// {
// 	pthread_t line1;
// 	pthread_t line2;

// 	t_info info1;
// 	t_info info2;

// 	info1.number = 1;
// 	info1.name = "leia";
// 	info2.number = 2;
// 	info2.name = "zhong";

// 	pthread_create(&line1, NULL, print_info,(void*)&info1);//print_info 的参数应该是一个结构体
// 	pthread_create(&line2, NULL, print_info,(void*)&info2);

// 	pthread_join(line1, NULL);
// 	pthread_join(line2, NULL);

// 	return 0;
// }

// typedef struct s_task
// {
// 	int int1;
// 	int int2;
// 	int number;
// }t_task;

// void *calculator(void * arg)
// {
// 	t_task *task = (t_task*)arg;

// 	printf("Thread %d: %d + %d = %d \n", task->number, task->int1, task->int2, task->int1 + task->int2 );
// 	return NULL;
// }

// int main()
// {
// 	pthread_t line1, line2, line3;
// 	t_task task1 = {21, 32, 1};
// 	t_task task2 = {8,23,2};
// 	t_task task3 = {21,3,3};

// 	pthread_create(&line1, NULL, calculator, (void*)&task1);
// 	pthread_create(&line2, NULL, calculator, (void*)&task2);
// 	pthread_create(&line3, NULL, calculator, (void*)&task3);

// 	pthread_join(line1, NULL);
//  	pthread_join(line2, NULL);
// 	pthread_join(line3, NULL);

// }

// typedef struct s_chef{
// 	int id;
// 	pthread_mutex_t *stove_mutex;
// }t_chef;

// void *chef_routine(void *arg)
// {
// 	t_chef *chef = (t_chef*)arg;

// 	int i = 0;
// 	while (i < 3)
// 	{
// 		printf("chef %d is waiting for using the stove...\n", chef->id);
// 		pthread_mutex_lock(chef->stove_mutex);
// 		printf("chef %d is cooking...\n", chef->id);
// 		sleep(1);
// 		printf("Chef %d finishs cooking...\n", chef->id);
// 		pthread_mutex_unlock(chef->stove_mutex);
// 		i++;
// 	}
// 	return NULL;
// }

// int main()
// {
// 	pthread_t thread[3];
// 	t_chef chefs[3];   // 三个主厨结构体
// 	int i = 0;
// 	pthread_mutex_t stove_mutex;
// 	pthread_mutex_init(&stove_mutex, NULL);

// 	while (i < 3)
// 	{
// 		chefs[i].id = i + 1;
// 		chefs[i].stove_mutex = &stove_mutex;
// 		pthread_create(&thread[i], NULL, chef_routine,(void*)(&chefs[i]));
// 		i++;
// 	}
// 	i = 0;
// 	while(i < 3)
// 		pthread_join(thread[i++], NULL);
// 	pthread_mutex_destroy(&stove_mutex);
// }

// typedef struct s_chef
// {
// 	int id;
// 	pthread_mutex_t *stove;
// }t_chef;

// void *chef_routine(void *arg)
// {
// 	t_chef *chefs = (t_chef*)arg;
// 	int i = 0;

// 	while (i < 3) //跑三遍。这里的0，1，2表示每个线程跑三遍
// 	{
// 		int stove_index = rand() % 2;
// 		if (pthread_mutex_trylock(&chefs->stove[stove_index]) == 0) //闲置，可以使用
// 		{

// 			printf("👨‍🍳 Chef %d is tring stove %d... success!\n", chefs->id, stove_index);
// 			printf("🔥 Chef %d is cooking on stove %d\n", chefs ->id,stove_index);
// 			sleep(1);
// 			pthread_mutex_unlock(&chefs->stove[stove_index]);
// 		}
// 		else
// 		{
// 			printf("👨‍🍳 Chef %d trying stove %d... busy, waiting\n", chefs->id,stove_index);
// 			sleep(1);
// 		}
// 		i++;
// 	}
// 	return NULL;

// }
// int main()
// {
// 	srand(time(NULL));
// 	t_chef chefs[3];  //创建三个厨师结构体，每个里面包括了厨师的id和灶台指针（这样就不需要在这个阶段确定是几号灶台）
// 	pthread_t thread[3]; //声明三个线程，每个线程代表一个厨师
// 	pthread_mutex_t stove[2]; //声明两个mutex类型的炉子
// 	pthread_mutex_init(&stove[0], NULL);
// 	pthread_mutex_init(&stove[1], NULL);

// 	int i = 0;// 三个线程都要跑一遍0，1，2 代表了三个线程
// 	while (i < 3)
// 	{
// 		chefs[i].id = i + 1;
// 		chefs[i].stove = stove;
// 		pthread_create(&thread[i], NULL, chef_routine,(void*)(&chefs[i])); // 创建了第0，1，2个线程，并立刻进入线程函数
// 		i++;
// 	}
// 	i = 0;
// 	while(i < 3)
// 		pthread_join(thread[i++], NULL);
// 	pthread_mutex_destroy(&stove[0]);
// 	pthread_mutex_destroy(&stove[1]);

// }



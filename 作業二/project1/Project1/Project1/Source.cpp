#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
using namespace std;

#define x 0
#define y 1
int map[2][20];
int alledge;
double distance[20][20];
int convexmap[2][20];
int convexcount;
int edgenode[20];
int vectornum;

void readfile()
{
	FILE *fp=fopen("vector3.txt","r");
	int num;
	for (int i = 0; i < vectornum; i++)
	{
		fscanf(fp, "%d %d", &map[0][i],&map[1][i]);
	}
}

double CountDistane(int x1, int y1, int x2, int y2)
{
	double distance = sqrt((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
	return distance;
}

void FinMinDis()
{
	double min = 200;
	int mina, minb;
	for (int i = 0; i < vectornum; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (i == j)
			{
				distance[i][j] = -1;
			}
			else
			{
				distance[i][j] = CountDistane(map[0][i], map[0][j], map[1][i], map[1][j]);
			}
			
		}
	}
	for (int i = 0; i < vectornum; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (distance[i][j] < min&&distance[i][j]>0)
			{
				min = distance[i][j];
				mina = i;
				minb = j;
			}
		}
	}
	printf("1. x=%d,y=%d and x=%d y=%d is cloest \n",map[x][mina],map[y][mina],map[x][minb],map[y][minb]);
}

void FindArea()
{
	for (int i = 0; i < vectornum; i++)
	{
		edgenode[i] = 0;
	}
	double a = 0;
    double b = 0;
	double c = 0;
	int positive;
	int negative;
	for (int i = 0; i < vectornum; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (i != j)
			{		
				//make polenomial
				positive = 0;
				negative = 0;
				//斜率為0
				double deltax = (double)(map[x][i] - map[x][j]);
				if (deltax == 0)
				{
					for (int k = 0; k < 10; k++)
					{
						if (k == i || k == j)
						{
							continue;
						}
						else
						{
							c = (double)map[x][i]-(double)map[x][k];   //x=k c=x-k

							if (c > 0)
							{
								positive++;
							}
							else
							{
								negative++;
							}
						}
					}
				}
				else
				{
					a = (double)(map[y][i] - map[y][j]) / deltax;
					b = map[y][i] - map[x][i] * a;
					for (int k = 0; k < vectornum; k++)
					{
						if (k == i || k == j)
						{

							continue;
						}
						else
						{
							c = a * (double)map[x][k] + b - (double)map[y][k];

							if (c > 0)
							{
								positive++;
							}
							else
							{
								negative++;
							}
						}
					}
				}
				
				if (positive == 0 || negative == 0)
				{
					edgenode[i] = 1;
					edgenode[j] = 1;
				}
			}
		}
	}
	for (int i = 0; i < vectornum; i++)
	{
		if (edgenode[i] == 1)
		{
			convexmap[x][convexcount] = map[x][i];
			convexmap[y][convexcount] = map[y][i];
			convexcount++;
		}
	}
	int total=0;
	for (int i = 0; i < convexcount; i++)
	{
		total = total - convexmap[x][i] * convexmap[y][i + 1]+ convexmap[y][i] * convexmap[x][i + 1];
		
	}
	total=total - convexmap[x][convexcount-1] * convexmap[y][0] + convexmap[y][convexcount-1] * convexmap[x][0];
	total = (abs(total)) / 2;
	printf("2.the area is: %d\n", total);
}

//for brute force

double CountRoute(int *num)
{
	double totaldistance=0;
	for (int i = 1; i < vectornum; i++)
	{
		totaldistance = totaldistance + CountDistane(map[x][num[i]], map[y][num[i]], map[x][num[i]+1], map[y][num[i]]+1);
	}
	return totaldistance;
}
double min = 100000;
void perm(int* num, int i) {
	int j, k, tmp;
	
	if (i < vectornum) {
		for (j = i; j <= vectornum; j++) {
			tmp = num[j];
			for (k = j; k > i; k--)
			{
				num[k] = num[k - 1];
			}
			num[i] = tmp;
			perm(num, i + 1);
			for (k = i; k < j; k++)
			{
				num[k] = num[k + 1];
			}		
			num[j] = tmp;
		}
	}
	else {
		if (CountRoute(num) < min)
		{
			min = CountRoute(num);
		}
	}
}

void brute()
{
	int num[20], i;

	for (i = 1; i <= vectornum; i++)
	{
		num[i] = i-1;
	}
	perm(num, 1);
	printf("3.(a) the shortest rute is %f \n",min);
}
//convex find shortest

double myabs(double num)
{
	if (num >= 0)
	{
		return num;
	}
	else
	{
		num = num * (-1);
		return num;
	}
}

class Convexedge
{
public:
	int pointax;
	int pointay;
	int pointbx;
	int pointby;
	int closenode[10][2];
	int closenodecount;
};
void ConvexHull()
{
	Convexedge edge[20];
	double distance, min;
	double a, b, c;
	int minedge;
	//存入class
	for (int i = 0; i < convexcount-1; i++)
	{
		edge[i].pointax=convexmap[x][i];
		edge[i].pointay = convexmap[y][i];
		edge[i].pointbx = convexmap[x][i+1];
		edge[i].pointby = convexmap[y][i+1];
		edge[i].closenodecount = 0;
	}
	edge[convexcount - 1].pointax = convexmap[x][convexcount - 1];
	edge[convexcount - 1].pointay = convexmap[y][convexcount - 1];
	edge[convexcount - 1].pointbx = convexmap[x][0];
	edge[convexcount - 1].pointby = convexmap[y][0];
	edge[convexcount - 1].closenodecount = 0;
	//不再線上的node找最近的node
	for (int i = 0; i < vectornum; i++)
	{
		if (edgenode[i] == 1)
		{
			continue;
		}
		else
		{
			min = 100000;
			minedge = 10;
			for (int j = 0; j < convexcount; j++)
			{
				if (edge[j].pointax == edge[j].pointbx)
				{
					a = 1;
					b = 0;
					c = edge[j].pointax;
					distance = myabs((a * map[x][i] + b * map[y][i] + c)) / sqrt((double)(a * a + b * b));
					if (distance < min)
					{
						min = distance;
						minedge = j;
					}
				}
				else
				{
					
					a = (double)(edge[j].pointay - edge[j].pointby) / (double)(edge[j].pointax - edge[j].pointbx);
					c = edge[j].pointay - edge[j].pointax * a;
					b = -1;
					distance = myabs((a * map[x][i] + b * map[y][i] + c)) / sqrt((double)(a * a + b * b));
					if (distance < min)
					{
						min = distance;
						minedge = j;
					}
				}
			}
			edge[minedge].closenode[edge[minedge].closenodecount][0] = i;
			edge[minedge].closenode[edge[minedge].closenodecount][1] = min;
			edge[minedge].closenodecount++;
		}
	}
	//排序所有點中的距離
	int temp1,temp2;
	for (int k = 0; k < convexcount; k++)
	{
		for (int i = 0; i < edge[k].closenodecount; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (edge[k].closenode[i][1] > edge[k].closenode[j][1])
				{
					temp1 = edge[k].closenode[i][1];
					edge[k].closenode[i][1] = edge[k].closenode[j][1];
					edge[k].closenode[j][1] = temp1;
					temp2= edge[k].closenode[i][0];
					edge[k].closenode[i][0] = edge[k].closenode[j][0];
					edge[k].closenode[j][0] = temp2;
				}
			}
		}
		
	}
	//開始走
	int insidecount=0,lastx,lasty,nowx,nowy;
	double totaldistance=0;
	lastx = edge[0].pointax;
	lasty = edge[0].pointay;
	for (int i = 0; i < convexcount; i++)
	{
		insidecount = 0;
		if (insidecount==0&&edge[i].closenodecount==0)
		{
			nowx = edge[i].pointax;
			nowy = edge[i].pointay;
			printf("(%d, %d) ", edge[i].pointax, edge[i].pointay);
			totaldistance = CountDistane(lastx, lasty, nowx, nowy) + totaldistance;
			lastx = nowx;
			lasty = nowy;
		}
		else
		{
			nowx = edge[i].pointax;
			nowy = edge[i].pointay;
			printf("(%d, %d), ", edge[i].pointax, edge[i].pointay);
			totaldistance = CountDistane(lastx, lasty, nowx, nowy) + totaldistance;
			lastx = nowx;
			lasty = nowy;
			insidecount++;
			while (insidecount <= edge[i].closenodecount)
			{
				nowx = map[x][edge[i].closenode[insidecount - 1][0]];
				nowy = map[y][edge[i].closenode[insidecount - 1][0]];
				totaldistance = CountDistane(lastx, lasty, nowx, nowy) + totaldistance;
				printf("(%d, %d), ", nowx, nowy);
				lastx = nowx;
				lastx = nowy;
				insidecount++;
			}
			
		}
	}
	printf("\n 3.(b) total distance %f \n", totaldistance);
}

//Hungarian method
int people[2][20];
int noderange[20][20];
int makeamount[2][20];


int checkuse[20][20];
int copy[20][20];
int finaljob[20];


bool checknode()
{
	//set strat
	for (int i = 0; i < vectornum; i++)
	{
		for (int j = 0; j < vectornum; j++)
		{
			copy[i][j] = noderange[i][j];
			checkuse[i][j] = noderange[i][j];
		}
	}
	//判斷1人1工作
	int count = 0;

	int zerocheck;
	int zerocount;
	//圈出所有的線 #這裡應該出問題了

	for (int k = vectornum; k > 0; k--)
	{
		for (int i = 0; i < vectornum; i++)
		{
			zerocount = 0;
			zerocheck = false;
			for (int j = 0; j < vectornum; j++)
			{
				if (copy[i][j] == 0)
				{
					zerocheck = true;
				}
			}
			if (zerocheck)
			{
				for (int j = 0; j < vectornum; j++)
				{

					if (copy[i][j] == 0 || copy[i][j] == -1)
					{
						zerocount++;
					}
				}
			}
			if (zerocount == k)
			{

				for (int j = 0; j < vectornum; j++)
				{
					if (checkuse[i][j] == -1)
					{
						checkuse[i][j] = -2;
					}
					else
					{
						checkuse[i][j] = -1;
					}
					if (copy[i][j] == 0)
					{
						copy[i][j] = -1;
					}
				}
			}
		}

		for (int i = 0; i < vectornum; i++)
		{
			zerocount = 0;
			zerocheck = false;
			for (int j = 0; j < vectornum; j++)
			{
				if (copy[j][i] == 0)
				{
					zerocheck = true;
				}
			}
			if (zerocheck)
			{
				for (int j = 0; j < vectornum; j++)
				{

					if (copy[j][i] == 0 || copy[j][i] == -1)
					{
						zerocount++;
					}
				}
			}
			if (zerocount == k)
			{
				for (int j = 0; j < vectornum; j++)
				{
					if (copy[j][i] == 0)
					{
						copy[j][i] = -1;
					}
					if (checkuse[j][i] == -1)
					{
						checkuse[j][i] = -2;
					}
					else
					{
						checkuse[j][i] = -1;
					}
				}
			}
		}
	}


	int check;
	int job;

	//判斷是否1人1工作

	int temp = 0;
	while (temp < vectornum)
	{
		temp++;

		for (int i = 0; i < vectornum; i++)
		{
			count = 0;
			for (int j = 0; j < vectornum; j++)
			{
				if (copy[i][j] == -1)
				{
					count++;
					job = j;
				}
			}
			if (count == 1)
			{

				finaljob[i] = job;
				copy[i][job] = -2;
				for (int m = 0; m < vectornum; m++)
				{
					for (int n = 0; n < vectornum; n++)
					{
						if (copy[m][n] == -1 && n == job && copy[m][n] != -2)
						{
							copy[m][n] = -3;
						}
					}
				}
			}
		}
	}

	count = 0;
	for (int m = 0; m < vectornum; m++)
	{
		for (int n = 0; n < vectornum; n++)
		{
			if (copy[m][n] == -2)
			{
				count++;
			}
		}
	}
	if (count < vectornum)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Hungarianmethod()
{
	for (int i = 0; i < vectornum; i++)
	{
		people[x][i] = i;
		people[y][i] = i;
	}
	
	//產生權重
	for (int i = 0; i < vectornum; i++)
	{
		for (int j=0;j<vectornum;j++)
		{
			noderange[i][j] = (int)CountDistane(people[x][i], people[y][i], map[x][j], map[y][j]);
		}
	}

	//遇到相同權重製造不同權重
	int temp1,temp2;
	for (int i = 0; i < vectornum; i++)
	{
		for (int j = 0; j < vectornum; j++)
		{
			makeamount[0][j] = j;
			makeamount[1][j] = noderange[i][j];
		}
		for (int m = 0; m < vectornum; m++)
		{
			for (int n = 0; n < m; n++)
			{
				if (makeamount[1][n] > makeamount[1][m])
				{
					temp1 = makeamount[0][n];
					temp2 = makeamount[1][n];
					makeamount[0][n]= makeamount[0][m];
					makeamount[1][n] = makeamount[1][m];
					makeamount[0][m]=temp1;
					makeamount[1][m]=temp2;
				}
			}
		}
		for (int j = 0; j < vectornum; j++)
		{
			noderange[i][makeamount[0][j]] = ((j + 1)*(i+2))+i*i ;
		}
	}
	
	
	//真正的城市部分
	int mincol[20];
	int minrow[20];
	int addcol[20];
	int finalcount = 0;
	for (int i = 0; i < vectornum; i++)
	{
		mincol[i] = 1000;
		minrow[i] = 1000;
		addcol[i] = 0;
	}

	//找出col最小
	for (int i = 0; i < vectornum; i++)
	{
		for (int j = 0; j < vectornum; j++)
		{
			if (noderange[i][j] < mincol[i])
			{
				mincol[i] = noderange[i][j];
			}
		}
	}

	for (int i = 0; i < vectornum; i++)
	{
		for (int j = 0; j < vectornum; j++)
		{
			noderange[i][j] = noderange[i][j] - mincol[i];
		}
	}

	//找出row最小
	for (int i = 0; i < vectornum; i++)
	{
		for (int j = 0; j < vectornum; j++)
		{
			if (noderange[j][i] < minrow[i])
			{
				minrow[i] = noderange[j][i];
			}
		}
	}

	for (int i = 0; i < vectornum; i++)
	{
		for (int j = 0; j < vectornum; j++)
		{
			noderange[j][i] = noderange[j][i] - minrow[i];
		}
	}

	int count = 0;
	int min = 1000;

	while (checknode())
	{

		min = 1000;
		count++;
		for (int i = 0; i < vectornum; i++)
		{
			for (int j = 0; j < vectornum; j++)
			{
				if (checkuse[i][j] < min && checkuse[i][j] != -1 && checkuse[i][j] != -2)
				{
					min = checkuse[i][j];
				}
			}
		}
		for (int i = 0; i < vectornum; i++)
		{
			for (int j = 0; j < vectornum; j++)
			{
				if (checkuse[i][j] == -2)
				{
					noderange[i][j] = noderange[i][j] + min;
				}
				else if (checkuse[i][j] == -1)
				{
					continue;
				}
				else
				{
					noderange[i][j] = noderange[i][j] - min;
				}
			}
		}

	}

	int temp = 0;
	int job;
	while (temp < vectornum)
	{
		temp++;

		for (int i = 0; i < vectornum; i++)
		{
			count = 0;
			for (int j = 0; j < vectornum; j++)
			{
				if (noderange[i][j] == 0)
				{
					count++;
					job = j;
				}
			}
			if (count == 1)
			{

				finaljob[i] = job;
				noderange[i][job] = -2;
				for (int m = 0; m < vectornum; m++)
				{
					for (int n = 0; n < vectornum; n++)
					{
						if (noderange[m][n] == 0 && n == job && noderange[m][n] != -2)
						{
							noderange[m][n] = -1;
						}
					}
				}
			}
		}
	}
	for (int j = 0; j < vectornum; j++)
	{
		printf("pople %d goto %d \n", j + 1, finaljob[j] + 1);
	}
	printf("\n");

}


int main()
{
	_LARGE_INTEGER Timestart, Timeend, Pintime;
	QueryPerformanceFrequency(&Pintime);
	printf("please enter vector number");
	scanf("%d", &vectornum);
	readfile();
	alledge = vectornum * (vectornum - 1) / 2;
	FinMinDis();
	FindArea();
	QueryPerformanceCounter(&Timestart);
	brute();
	QueryPerformanceCounter(&Timeend);
	double time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
	printf("time: %f ms\n",time);
	QueryPerformanceCounter(&Timestart);
	ConvexHull();
	QueryPerformanceCounter(&Timeend);
	time = ((double)Timeend.QuadPart - (double)Timestart.QuadPart) / ((double)Pintime.QuadPart / 1000);
	printf("time: %f ms\n", time);
	printf("4.\n");
	Hungarianmethod();
	return 0;
}
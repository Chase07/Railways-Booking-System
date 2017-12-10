#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<limits.h>

typedef struct Palce_Node PN ;
typedef struct Edge_Node EN ;
typedef struct Priority_Queue PQ ;
typedef struct Stack_Node SN ;

struct Palce_Node
{
	int ID ;
	int Num_e ;
	int Dist ;
	char *Name ;
	EN *All_e ;
	PN *Path ;
	PN *Next ;
} ;
struct Edge_Node
{
	PN *adja_p ;
	int weight ;
	EN *Next ;
} ;
struct Priority_Queue 
{
	int Capacity ;
	int Cur_Size ;
	PN **Elem ;
} ;
struct Stack_Node
{
	PN *Elem ;
	SN *Next ;
} ;

PN* Init_Graph() ;
void Update_Graph( PN *Adja_List ) ;
PN* Find_Vertex( int ap, PN *current ) ;
int Find_Path( int Start, PN *Adja_List ) ;
int Display_Path( int End, PN *Adja_List ) ;
void Output_Name( char *p ) ;
void Push( PN *elem, SN **Top ) ;
PN* Pop( SN **Top ) ;
int Cal_All_Edges( PN *Adja_List ) ;
PQ* Init_PQ( int HeapSize, int Sentinel ) ;
PN* Delete_Min( PQ *MinHeap ) ;
void Insert_PQ( PN *current, PQ *MinHeap ) ;
int IsFull( PQ *MinHeap ) ;
int IsEmpty( PQ *MinHeap ) ;
char* Apply_Char_Space() ;
void Overflow() ;
void OpenFailed() ;
void Main_Menu() ;
void Display_Main_Menu() ;
void Admin_Mode() ;
void Add_Place() ;
int Write_in_vfile( char *a ) ;
int Write_in_efile( int num_e ) ;
int Modify_Place( int ID, int ap, int new_ap, int new_weight ) ;
void Modify_Information() ;
void Init_blank( char *a ) ;
char* Get_Password() ;
int Check_Password() ;
void Display_Admin_Menu() ;
void Admin_Menu() ;
void Search_Path() ;

char password[ 17 ] ;//存密码数组

int main( void )
{
	Main_Menu() ;
	return 0 ;
}
void Display_Main_Menu()
{	
	printf( "~~~~~~~欢迎来到南昌工程学院~~~~~~~" ) ;
	putchar( 10 ) ;
	printf( "1.景点介绍\n" ) ;
	printf( "2.路线查询\n" ) ;
	printf( "3.管理者模式\n" ) ;
	printf( "4.退出系统\n" ) ;
	putchar( 10 ) ;
}
void Display_Place()
{
	printf( "           <~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>\n" );
	printf( "           |         NIT ( 南昌工程学院 )           |\n" );
	printf( "           |         ^0^   主要景点   ^0^           |\n" );
	printf( "           |                                        |\n" );
	printf( "           |    1.学校大门          2.教学北大楼    |\n" );
	printf( "           |    3.教学南大楼        4.教育技术楼    |\n" );
	printf( "           |    5.电子信息楼        6.逸夫楼        |\n" );
	printf( "           |    7.机械电气楼        8.图书馆        |\n" );
	printf( "           |    9.学术交流中心      10.一食堂       |\n" );
	printf( "           |    11.体育馆           12.田径场       |\n" );
	printf( "           |    13.三食堂           14.大学生创业园 |\n" );
	printf( "           |    15.校医院           16.教师公寓     |\n" );
	printf( "           |    17.学生公寓         18.学生活动中心 |\n" );
	printf( "           |    19.行政楼           20.升旗台       |\n" );
	printf( "           |                                        |\n" );
	printf( "           <________________________________________>\n" );
}
void Main_Menu()
{
	int i = 0 ;

	for( ; ; )
	{
		Display_Main_Menu() ;
		printf( "请继续键入数字选择您所需的功能^_^:" ) ;
		scanf( "%d", &i ) ;
		system( "cls" ) ;
		switch( i )
		{
			case 1:
			{
				/*景点简介*/
				Display_Place() ;
				continue ;
			}
			case 2:
			{
				/*路线查询*/
				Display_Place() ;
				Search_Path() ;
				system( "cls" ) ;
				continue ;
			}
			case 3:
			{
				/*管理者模式*/
				Admin_Mode() ;
				continue ;
			}
			case 4:
			{
				printf( "蟹蟹您的使用啦,下次再撩哦^0^!\n" ) ;
				exit( 0 ) ;//退出系统
			}
			default:
			{
				printf( "哪有这样的功能啊!阿拉伯数字都看不清楚，您这是要换眼镜的节奏吗Q.Q\n" ) ;	
				continue ;
			}
		}
	}
}
void Admin_Mode()
{
	int i ;//i用来标志是否通过密码验证
	printf( "想进本菇凉的闺房可是有条件的哦*.*\n" ) ;
	i = Check_Password() ;//验证密码
	for( ; i != 1 ;  )
	{
		printf( "\n你不是我主人!别想进来+o+\n" ) ;
		i = Check_Password() ;
	}
	putchar( 10 ) ;
	system( "cls" ) ;
	Admin_Menu() ;
}
void Display_Admin_Menu()
{
	printf( "*******本菇凉||-_-||现在处于管(受)理(虐)模式*******\n" ) ;
	printf( "1.增加景点\n" ) ;
	//printf( "2.修改信息\n" ) ;
	printf( "2.滚回主界面\n" ) ;
	printf( "3.退出系统\n" ) ;
	printf( "`=`继续吧!让暴风雨来得更猛烈些吧!\n" ) ;
	putchar( 10 ) ;
}
void Admin_Menu()
{
	int i ;
	
	for( ; ; )
	{
		Display_Admin_Menu() ;
		
		scanf( "%d", &i ) ;
		system( "cls" ) ;
		switch ( i )
		{
			case 1:
			{
				/* 增加景点 */
				Add_Place() ;
				system( "cls" ) ;
				continue ;
			}
			/*case 2:
			{
				// 修改景点信息
				Modify_Information() ;
				continue ;
			}*/
			case 2:
			{
				/* 返回主界面 */
				Main_Menu() ;
				continue ;
			}
			case 3:
			{
				printf( "走走走!最好别再来啦!我自己一个人玩得欢着呢~\n" ) ;
				exit( 0 ) ;
			}
			default :
			{
				printf( "O*O你这是想干嘛!?要增加功能自己到后台慢慢撸去!\n" ) ;
				continue ;
			}
		}
	}
}
/*void Modify_Information()
{
	int ID, ap, weight ;
	int flag ;

	printf( "你要改哪个景点啊?\n" ) ;
	scanf( "%d", &ID ) ;
	printf( "那要改的相邻景点和改之后的距离是多少?\n" ) ;
	scanf( "%d %d", &ap, &weight ) ;
	flag = Modify_Place( ID, ap, ap, weight ) ;
	if( flag )
	{
		printf( "小意思!O啦!`0`\n" ) ;
	}
}*/
void Add_Place()
{
	int flag = 0, num_e ;//第一个变量标志写入信息过程中的状态
	char name[ 50 ] ;
	
	getchar() ;
	printf( "老大,你要加啥景点啊!?\n告诉我:" ) ;
	gets( name ) ;
	flag = Write_in_vfile( name ) ;//将景点名写入顶点文件
	if( flag )
	{
		printf( "这景点有几条边咧?\nTell me!Plz:" ) ;
		scanf( "%d", &num_e ) ;
		flag = Write_in_efile( num_e ) ;//将景点的边信息写入边文件
		if( flag )
		{
			printf( "OK啦~ 搞定!\n" ) ;
			getch() ;
		}
		else
		{
			printf( "写入边信息失败#.#\n" ) ;
		}
	}
	else
	{
		printf( "写入景点名失败#.#\n" ) ;
	}
}
int Write_in_efile( int num_e )
{
	char *c ;
	FILE *fp ;
	int ap, weight ;
	int i, n ;//n 读入具有边的顶点总数

	c = Apply_Char_Space() ;
	if( fp = fopen( "NIT景点边文件.txt", "r+" ) )
	{
		fscanf( fp, "%d", &n ) ;
		fseek( fp, 0L, SEEK_SET ) ;
		fprintf( fp, "%d", ++n ) ;//n自加后成为新的景点的ID
		fclose( fp ) ;//关闭文件
		fp =fopen( "NIT景点边文件.txt", "r+" ) ;
		for( i = 1 ; i <= n ; ++i )
		{
			fgets( c, LONG_MAX, fp ) ;
		}
		fputc( 10, fp ) ;//写入一个回车符
		fprintf( fp, "%d %d  ", n, num_e ) ;//后面多写入2个空格
		for( i = 1 ; i <= num_e ; ++i )
		{
			printf( "输入它的一个相邻景点和距离，空格分开哦~\n" ) ;
			scanf( "%d %d", &ap, &weight ) ;
			fprintf( fp, "%d %d ", ap, weight ) ;
			if( !( Modify_Place( ap, 0, n, weight ) ) )//**修改对应的边信息**
			{
				printf( "修改对应的边信息失败\n" ) ;
				return 0 ;
			}
		}
		free( c ) ;
		fclose( fp ) ;//关闭文件
		
		return 1 ;
	}
	OpenFailed() ;
	return 0 ;
}
void Init_blank( char *a )
{
	int i ;
	for( i = 0 ; i <= 9 ; ++i )
	{
		a[ i ] = 32 ;
		if( i == 9 )
		{
			a[ i ] = '\0' ;
		}
	}
}
int Modify_Place( int ID, int ap, int new_ap, int new_weight )
{
	int i ;
	int num_e, temp_ap, temp_weight ;
	long save_pos ;//用来保存内部文件指针所指的位置到文件头的距离 
	char *c, blank[ 10 ]  ;
	FILE *fp1 ;
	FILE *temp_fp ;

	c = Apply_Char_Space() ;
	Init_blank( blank ) ;
	if( ap != 0 )
	{
		fp1 = fopen( "NIT景点边文件.txt", "r+" ) ;
		if( !fp1 )
		{
			OpenFailed() ;
		}
		for( i = 1 ; i <= ID ; ++i )
		{
			fgets( c, LONG_MAX, fp1 ) ;
		}

		fscanf( fp1, "%d %d", &ID, &num_e ) ;
		fseek( fp1, 1L, SEEK_CUR ) ;
		for( i = 1 ; i <= num_e ; ++i )
		{
			save_pos = ftell( fp1 ) ;//在读取之前先记录下前一组数据的起始位置
			fscanf( fp1, " %d %d", &temp_ap, &temp_weight ) ;
			if( temp_ap == ap )
			{
				//说明已经找到要修改的相邻景点
				break ;
			}
		}
		if( i <= num_e )
		{
			fseek( fp1, save_pos, SEEK_SET ) ;
			fgets( c, LONG_MAX, fp1 ) ;
			temp_fp = fopen( "临时文件.txt", "w+" ) ;
			if( !temp_fp )
			{
				OpenFailed() ;
			}
			fputs( c, temp_fp ) ;
			fseek( temp_fp, 0L, SEEK_SET ) ;
			fscanf( temp_fp, "%d %d", &temp_ap, &temp_weight ) ;//把第一组(旧的)数据读走
			fgets( c, LONG_MAX, temp_fp ) ;
			
			fseek( fp1, save_pos, SEEK_SET ) ;//确实回到了正确的位置
			fputs( blank, fp1 ) ;//将后面的字符置为空白
			fseek( fp1, save_pos, SEEK_SET ) ;
			fprintf( fp1, " %d %d", new_ap, new_weight ) ;					
			fputs( c, fp1 ) ;

			free( c ) ;
			fseek( fp1, 0L, SEEK_SET ) ;
			fseek( temp_fp, 0L, SEEK_SET ) ;
			fclose( fp1 ) ;
			fclose( temp_fp ) ;
			return 1 ;
		}
		else
		{
			printf( "没有这个相邻的景点哟-0-\n" ) ;
			return 0 ;
		}
	}
	else
	{
		fp1 = fopen( "NIT景点边文件.txt", "r+") ;
		if( !fp1 )
		{
			OpenFailed() ;
		}
		for( i = 1 ; i <= ID ; ++i )
		{
			fgets( c, LONG_MAX, fp1 ) ;
		}
		
		fscanf( fp1, "%d", &ID ) ;//此时ID用来占读取的位置,无实际用途
		save_pos = ftell( fp1 ) ;//***记录当前fp1内部文件指针的位置***
		fgets( c, LONG_MAX, fp1 ) ;//将ID后面的全部数据读走
		
		temp_fp = fopen( "临时文件.txt", "w+" ) ;//打开一个临时文件并清空
		if( !temp_fp )
		{
			OpenFailed() ;
		}
		fputs( c, temp_fp ) ;//将ID后面的全部数据放入临时文件中
		fseek( temp_fp, 0L, SEEK_SET ) ;//使文件指针重新指向文件头
		fscanf( temp_fp, "%d", &num_e ) ;//在临时文件读取改顶点的边数
		fgets( c, LONG_MAX, temp_fp ) ;//再将除顶点边数外的数据读走
		
		fseek( fp1, save_pos, SEEK_SET ) ;
		fprintf( fp1, " %d", 1 + num_e ) ;
		save_pos = ftell( fp1 ) ;//***记录当前fp1内部文件指针的位置***
		fputs( c, fp1 ) ;
		fseek( fp1, save_pos, SEEK_SET ) ;
		for( i = 1 ; i <=num_e ; ++i )
		{
			fscanf( fp1, "%d %d", &temp_ap, &temp_weight ) ;
		}
		fseek( fp1, 0L, SEEK_CUR ) ;
		fprintf( fp1, " %d %d", new_ap, new_weight ) ;
		free( c ) ;
		/* 分别找到两个文件的开始位置，并释放 */
		fseek( fp1, 0L, SEEK_SET ) ;
		fseek( temp_fp, 0L, SEEK_SET ) ;
		fclose( fp1 ) ;
		fclose( temp_fp ) ;
		return 1 ;
	}
}
int Write_in_vfile( char *a )
{
	FILE *fp ;
	int i ;//用i更改顶点文件中的顶点总数

	if( fp = fopen( "NIT景点文件.txt", "r+" ) )
	{
		fscanf( fp, "%d", &i ) ;
		fseek( fp, -( ftell( fp ) ) , SEEK_CUR ) ;//返回文件头部
		fprintf( fp, "%d", ++i ) ;//i自加后成为新的景点的ID
		fclose( fp ) ;//关闭文件
		if( fp = fopen( "NIT景点文件.txt", "a+" ) )
		{
			fprintf( fp, "%d   ", i ) ;
			fputs( a, fp ) ;//写入景点名字
			fputc( 10, fp ) ;//写入一个回车
			fclose( fp ) ;//关闭文件
			return 1 ;
		}
	}
	OpenFailed() ;
	return 0 ;
}
char* Get_Password()
{
	int counter = 0 ;//用来记录输入了几位密码
	char ch, *p ;

	p = password ;//右值为全局变量
	for( ch = getch() ; ch != 13 && counter <= 16 ; ch = getch() )//输入的字符不为回车且未达到最大的密码位数循环继续
	{
		if( ch == 8 && counter != 0 )//输入的字符为退格且至少输入了1位密码
		{
			printf( "\b " ) ;
			printf( "\b" ) ;
			--counter ;
			--p ;
		}
		else if( ch >= 33 && ch <= 126 )
		{
			printf( "*" ) ;
			++counter ;
			*p = ch ;
			++p ;
		}
		else
		{
			counter = 0 ;
			p = password ;
			printf( "\n字符不合法耶~.~，重新输入\n" ) ;
		}
	}
	password[ counter ] = 0 ;//末尾加入一个串结束符
	return password ;
}
int Check_Password()
{
	int i ;
	long num ;//用来读取密码文件中的密码为数
	char *p1, *p2, *temp ;//分别用来读取用户输入的密码和密码文件中的密码,temp用来释放p2申请的空间
	FILE *fp ;
	
	printf( "请输入密码:" ) ;
	p1 = Get_Password() ;
	temp = p2 = Apply_Char_Space() ;
	if( fp = fopen( "管理员密码文件.txt", "r") )
	{
		fscanf( fp, "%d", &num ) ;
		fseek( fp, 2L, SEEK_CUR ) ;
		fgets( p2, num + 1 , fp ) ;
		fclose( fp ) ;//关闭文件
		for( i = 1 ; i <= num ; ++p1, ++p2, ++i )
		{
			if( *p1 != *p2 )
			{
				free( temp ) ;
				return 0 ;
			}
		}
		if( *p1 == '\0' )
		{
			free( temp ) ;
			return 1 ;
		}
		else
		{
			free( temp ) ;
			return 0 ;
		}
	}
	printf( "错误发生在检查密码函数处,无法打开文件\n" ) ;//面向维护人员
	exit( 1 ) ;
}
void Search_Path()
{
	PN *Adja_List ;
	int i, Start, End ;// i用来标志是否存在用户输入的位置

	Adja_List = Init_Graph() ;
	Update_Graph( Adja_List ) ;
	for( i = 0 ; i != 1 ; )
	{
		printf( "请输入你要查询路线的起点:" ) ;
		scanf( "%d", &Start ) ;
		i = Find_Path( Start ,Adja_List ) ;
	}
	for( i = 0 ; i != 1 ; )
	{
		printf( "请输入你要查询路线的终点:" ) ;
		scanf( "%d", &End ) ;
		i = Display_Path( End, Adja_List ) ;
	}
}
int Display_Path( int End, PN *Adja_List )
{
	SN *Top ;
	PN *current, *temp ;
	
	Top = NULL ;
	current = Find_Vertex( End, Adja_List ) ;
	if( current )
	{
		printf( "喏,本大人给您指路啦,还不赶紧打赏一下￥o￥:\n" ) ;
		for( ; current != NULL ; current = current->Path )
		{
			Push( current, &Top ) ;
		}
		for( ; Top != NULL ; )
		{
			temp = Pop( &Top ) ;
			Output_Name( temp->Name ) ;
			if( Top != NULL )
			{
				printf( "->" ) ;
			}
		}
		putchar( 10 ) ;
		getchar() ;
		printf( "                       请按任意键返回主菜单^_^\n" ) ;
		getch() ;
		return 1 ;
	}
	else
	{
		printf( "抱歉了,找不到这样的终点耶@-@\n" ) ;
		return 0 ;
	}
}
void Output_Name( char *p )
{
	for( ; *p != '\n' ; ++p )
	{
		printf( "%c", *p ) ;
	}
}
void Push( PN *elem, SN **Top )
{
	SN *p ;

	p = ( SN* )malloc( sizeof( SN ) ) ;
	if( p )
	{
		p->Elem = elem ;
		p->Next = *Top ;
		*Top = p ; 
	}
	else
	{
		Overflow() ;
	}
}
PN* Pop( SN **Top )
{
	PN *p ;
	SN *temp ;

	if( *Top != NULL )
	{
		p = ( *Top )->Elem ;
		temp = *Top ;
		*Top = ( *Top )->Next ;
		free( temp ) ;
		return p ;
	}
	else
	{
		printf( "Error: Stack is empty!\n" ) ;
		return NULL ;
	}
} 
int Find_Path( int Start, PN *Adja_List )
{
	int Edges ;
	PQ *MinHeap ;
	PN *current ;
	EN *temp ;

	Edges = Cal_All_Edges( Adja_List ) ;//计算总边数
	MinHeap = Init_PQ( Edges, 0 ) ;//创建一个和边数相同大小的最小堆
	current = Find_Vertex( Start, Adja_List ) ;//找到起始结点
	if( current )
	{
		current->Dist = 0 ;
		Insert_PQ( current, MinHeap ) ;
		for( ; !IsEmpty( MinHeap ) ; )
		{
			current = Delete_Min( MinHeap ) ;
			for( temp = current->All_e ; temp != NULL ; temp = temp->Next )
			{
				if( current->Dist + temp->weight < temp->adja_p->Dist )//若两者相等，不将当前结点加入路径，可以保证最短路径的转折点最少
				{
					temp->adja_p->Dist = current->Dist + temp->weight ;//更新边结点到达起点的Dist值
					temp->adja_p->Path = current ;//将当前结点加入边结点到达起点的路径中
					Insert_PQ( temp->adja_p, MinHeap ) ;
				}
			}
		}
		return 1 ;
	}
	else
	{
		printf( "很抱歉，臣妾找不到这样的起点T^T,可不可以换一个\n" ) ;
		return 0 ;
	}
	
}
PN* Delete_Min( PQ *MinHeap )
{
	int i, Child ;
	PN *Min, *Last ;
	
	if( !IsEmpty( MinHeap ) )//首先判断堆空不空
	{
		Min = MinHeap->Elem[ 1 ] ;
		Last = MinHeap->Elem[ ( MinHeap->Cur_Size )-- ] ;
		for( i = 1 ; 2 * i <= MinHeap->Cur_Size ; i = Child )
		{
			Child = 2 * i ;
			if( Child != MinHeap->Cur_Size && MinHeap->Elem[ Child ]->Dist > MinHeap->Elem[ 1 + Child ]->Dist )//通过Dist比较大小
			{
				++Child ; 
			}
			if( Last->Dist > MinHeap->Elem[ Child ]->Dist )
			{
				MinHeap->Elem[ i ] = MinHeap->Elem[ Child ] ;
			}
			else
			{
				break ;
			}
		}
		MinHeap->Elem[ i ] = Last ;
		return Min ;
	}
	printf( "Error: Heap is Empty!\n" ) ;
	return NULL ;
} 
void Insert_PQ( PN *current, PQ *MinHeap ) 
{
	int i ;

	if( !IsFull( MinHeap ) )
	{
		for( i = ++( MinHeap->Cur_Size ) ; current->Dist < MinHeap->Elem[ i / 2 ]->Dist ; i /= 2 )
		{
			MinHeap->Elem[ i ] = MinHeap->Elem[ i / 2 ] ;
		}
		MinHeap->Elem[ i ] = current ;
	}
	else
	{
		printf( "Error: Heap is Full!\n" ) ;
	}
}
int IsEmpty( PQ *MinHeap )
{
	if( MinHeap->Cur_Size == 0 )
	{
		return 1 ;
	}
	return 0 ;
}
int IsFull( PQ *MinHeap ) 
{
	if( MinHeap->Cur_Size == MinHeap->Capacity )
	{
		return 1 ;
	}
	return 0 ;
}
PQ* Init_PQ( int HeapSize, int Sentinel )
{
	PQ *MinHeap ;

	MinHeap = ( PQ* )malloc( sizeof( PQ ) ) ;
	if( MinHeap )
	{
		MinHeap->Elem = ( PN** )malloc( ( 1 + HeapSize ) * sizeof( PN* ) ) ;
		if( MinHeap->Elem )
		{
			MinHeap->Capacity = HeapSize ;
			MinHeap->Cur_Size = 0 ;
			MinHeap->Elem[ 0 ] = ( PN* )malloc( sizeof( PN ) ) ;
			if( MinHeap->Elem[ 0 ] )
			{
				MinHeap->Elem[ 0 ]->Dist = Sentinel ;
				return MinHeap ;
			}
		}
	}
	Overflow() ;
	return NULL ;
}
int Cal_All_Edges( PN *Adja_List )
{
	int Num_Edges = 0 ; 
	PN *current ;

	for( current = Adja_List ; current ; current = current->Next )
	{
		Num_Edges += current->Num_e ;
	}
	return Num_Edges ;
}
void Update_Graph( PN *Adja_List )
{
	int i, j, n ;
	int v, e, ap ;//分别表示顶点，边的个数，邻接点
	char *c ;
	PN *current ;
	EN *p ;
	FILE *fp ;

	if( fp = fopen( "NIT景点边文件.txt", "r" ) )
	{
		fscanf( fp, "%d", &n ) ;
		c = Apply_Char_Space() ;
		fgets( c, 50, fp ) ;//将第一行读取完
		/* 读取完即刻释放 */free( c ) ;
	}
	else
	{
		OpenFailed() ;//打开文件失败
	}
	for( i = 1 ; i <= n ; ++i )
	{
		fscanf( fp, "%d %d ", &v, &e ) ;
		current = Find_Vertex( v, Adja_List ) ;//找到所要更新的顶点
		current->Num_e = e;//记录边的总数 
		for( j = 1 ; j <= e ; ++j )
		{
			p = ( EN* )malloc( sizeof( EN ) ) ;
			if( p )
			{
				fscanf( fp, " %d %d", &ap, &p->weight ) ;
				p->adja_p = Find_Vertex( ap, Adja_List ) ;
				p->Next = current->All_e ;
				current->All_e = p ;
			}
			else
			{
				Overflow() ;
			}
		}
	}
	fclose( fp ) ;//关闭文件
}
PN* Find_Vertex( int v, PN *current )
{
	for( current ; current && current->ID != v ; current = current->Next ) ;
	if( current )
	{
		return current ;
	}
	//printf( "Error: No such vertex!\n" ) ;//正式运行程序时将这句注释掉
	return NULL ;
}
PN* Init_Graph()
{
	int i, Size ;
	char *c ;
	PN *p, *temp, *Adja_List ;
	FILE *fp ;
	
	c = Apply_Char_Space() ; 
	if( fp = fopen( "NIT景点文件.txt", "r" ) )
	{
		fscanf( fp, "%d", &Size ) ;//读取导游图的地点总数
	}
	else
	{
		OpenFailed() ;//打开文件失败
	}
	fgets( c, LONG_MAX, fp ) ;//用200个字节来保证将文件第一行读取完
	/* 读取完即刻释放 */free( c ) ;
	for( i = 1 ; i <= Size ; ++i )
	{
		p = ( PN* )malloc( sizeof( PN ) ) ;
		if( p )
		{
			p->Name = Apply_Char_Space() ;//给景点名字申请空间
			fscanf( fp, "%d", &p->ID ) ;
			fseek( fp, 3L, SEEK_CUR ) ;
			fgets( p->Name, 100, fp ) ;
			p->Num_e = 0 ;
			p->Dist = INT_MAX ;
			p->Path = NULL ;
			p->All_e = NULL ;
			p->Next = NULL ;
			if( i == 1 )
			{
				Adja_List = temp = p ;
			}
			else
			{
				temp->Next = p ;
				temp = p ;
			}
		}
		else
		{
			Overflow() ;
		}
	}
	fclose( fp ) ;//关闭文件(在此处执行该语句出错)
	return Adja_List ;
}
char* Apply_Char_Space()
{
	char *p ;
	p = ( char* )malloc( 1000 * sizeof( char ) ) ;
	if( p )
	{
		return p ;
	}
	Overflow() ;
	return NULL ;
}
void OpenFailed()
{
	printf( "Error: File can't opened!\n" ) ;
	exit( 0 ) ;
}
void Overflow()
{
	printf( "Error: Out of space!\n" ) ;
	exit( 0 ) ;
}
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

char password[ 17 ] ;//����������

int main( void )
{
	Main_Menu() ;
	return 0 ;
}
void Display_Main_Menu()
{	
	printf( "~~~~~~~��ӭ�����ϲ�����ѧԺ~~~~~~~" ) ;
	putchar( 10 ) ;
	printf( "1.�������\n" ) ;
	printf( "2.·�߲�ѯ\n" ) ;
	printf( "3.������ģʽ\n" ) ;
	printf( "4.�˳�ϵͳ\n" ) ;
	putchar( 10 ) ;
}
void Display_Place()
{
	printf( "           <~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>\n" );
	printf( "           |         NIT ( �ϲ�����ѧԺ )           |\n" );
	printf( "           |         ^0^   ��Ҫ����   ^0^           |\n" );
	printf( "           |                                        |\n" );
	printf( "           |    1.ѧУ����          2.��ѧ����¥    |\n" );
	printf( "           |    3.��ѧ�ϴ�¥        4.��������¥    |\n" );
	printf( "           |    5.������Ϣ¥        6.�ݷ�¥        |\n" );
	printf( "           |    7.��е����¥        8.ͼ���        |\n" );
	printf( "           |    9.ѧ����������      10.һʳ��       |\n" );
	printf( "           |    11.������           12.�ﾶ��       |\n" );
	printf( "           |    13.��ʳ��           14.��ѧ����ҵ԰ |\n" );
	printf( "           |    15.УҽԺ           16.��ʦ��Ԣ     |\n" );
	printf( "           |    17.ѧ����Ԣ         18.ѧ������� |\n" );
	printf( "           |    19.����¥           20.����̨       |\n" );
	printf( "           |                                        |\n" );
	printf( "           <________________________________________>\n" );
}
void Main_Menu()
{
	int i = 0 ;

	for( ; ; )
	{
		Display_Main_Menu() ;
		printf( "�������������ѡ��������Ĺ���^_^:" ) ;
		scanf( "%d", &i ) ;
		system( "cls" ) ;
		switch( i )
		{
			case 1:
			{
				/*������*/
				Display_Place() ;
				continue ;
			}
			case 2:
			{
				/*·�߲�ѯ*/
				Display_Place() ;
				Search_Path() ;
				system( "cls" ) ;
				continue ;
			}
			case 3:
			{
				/*������ģʽ*/
				Admin_Mode() ;
				continue ;
			}
			case 4:
			{
				printf( "зз����ʹ����,�´�����Ŷ^0^!\n" ) ;
				exit( 0 ) ;//�˳�ϵͳ
			}
			default:
			{
				printf( "���������Ĺ��ܰ�!���������ֶ����������������Ҫ���۾��Ľ�����Q.Q\n" ) ;	
				continue ;
			}
		}
	}
}
void Admin_Mode()
{
	int i ;//i������־�Ƿ�ͨ��������֤
	printf( "����������Ĺ뷿������������Ŷ*.*\n" ) ;
	i = Check_Password() ;//��֤����
	for( ; i != 1 ;  )
	{
		printf( "\n�㲻��������!�������+o+\n" ) ;
		i = Check_Password() ;
	}
	putchar( 10 ) ;
	system( "cls" ) ;
	Admin_Menu() ;
}
void Display_Admin_Menu()
{
	printf( "*******������||-_-||���ڴ��ڹ�(��)��(Ű)ģʽ*******\n" ) ;
	printf( "1.���Ӿ���\n" ) ;
	//printf( "2.�޸���Ϣ\n" ) ;
	printf( "2.����������\n" ) ;
	printf( "3.�˳�ϵͳ\n" ) ;
	printf( "`=`������!�ñ��������ø�����Щ��!\n" ) ;
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
				/* ���Ӿ��� */
				Add_Place() ;
				system( "cls" ) ;
				continue ;
			}
			/*case 2:
			{
				// �޸ľ�����Ϣ
				Modify_Information() ;
				continue ;
			}*/
			case 2:
			{
				/* ���������� */
				Main_Menu() ;
				continue ;
			}
			case 3:
			{
				printf( "������!��ñ�������!���Լ�һ������û�����~\n" ) ;
				exit( 0 ) ;
			}
			default :
			{
				printf( "O*O�����������!?Ҫ���ӹ����Լ�����̨����ߣȥ!\n" ) ;
				continue ;
			}
		}
	}
}
/*void Modify_Information()
{
	int ID, ap, weight ;
	int flag ;

	printf( "��Ҫ���ĸ����㰡?\n" ) ;
	scanf( "%d", &ID ) ;
	printf( "��Ҫ�ĵ����ھ���͸�֮��ľ����Ƕ���?\n" ) ;
	scanf( "%d %d", &ap, &weight ) ;
	flag = Modify_Place( ID, ap, ap, weight ) ;
	if( flag )
	{
		printf( "С��˼!O��!`0`\n" ) ;
	}
}*/
void Add_Place()
{
	int flag = 0, num_e ;//��һ��������־д����Ϣ�����е�״̬
	char name[ 50 ] ;
	
	getchar() ;
	printf( "�ϴ�,��Ҫ��ɶ���㰡!?\n������:" ) ;
	gets( name ) ;
	flag = Write_in_vfile( name ) ;//��������д�붥���ļ�
	if( flag )
	{
		printf( "�⾰���м�������?\nTell me!Plz:" ) ;
		scanf( "%d", &num_e ) ;
		flag = Write_in_efile( num_e ) ;//������ı���Ϣд����ļ�
		if( flag )
		{
			printf( "OK��~ �㶨!\n" ) ;
			getch() ;
		}
		else
		{
			printf( "д�����Ϣʧ��#.#\n" ) ;
		}
	}
	else
	{
		printf( "д�뾰����ʧ��#.#\n" ) ;
	}
}
int Write_in_efile( int num_e )
{
	char *c ;
	FILE *fp ;
	int ap, weight ;
	int i, n ;//n ������бߵĶ�������

	c = Apply_Char_Space() ;
	if( fp = fopen( "NIT������ļ�.txt", "r+" ) )
	{
		fscanf( fp, "%d", &n ) ;
		fseek( fp, 0L, SEEK_SET ) ;
		fprintf( fp, "%d", ++n ) ;//n�ԼӺ��Ϊ�µľ����ID
		fclose( fp ) ;//�ر��ļ�
		fp =fopen( "NIT������ļ�.txt", "r+" ) ;
		for( i = 1 ; i <= n ; ++i )
		{
			fgets( c, LONG_MAX, fp ) ;
		}
		fputc( 10, fp ) ;//д��һ���س���
		fprintf( fp, "%d %d  ", n, num_e ) ;//�����д��2���ո�
		for( i = 1 ; i <= num_e ; ++i )
		{
			printf( "��������һ�����ھ���;��룬�ո�ֿ�Ŷ~\n" ) ;
			scanf( "%d %d", &ap, &weight ) ;
			fprintf( fp, "%d %d ", ap, weight ) ;
			if( !( Modify_Place( ap, 0, n, weight ) ) )//**�޸Ķ�Ӧ�ı���Ϣ**
			{
				printf( "�޸Ķ�Ӧ�ı���Ϣʧ��\n" ) ;
				return 0 ;
			}
		}
		free( c ) ;
		fclose( fp ) ;//�ر��ļ�
		
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
	long save_pos ;//���������ڲ��ļ�ָ����ָ��λ�õ��ļ�ͷ�ľ��� 
	char *c, blank[ 10 ]  ;
	FILE *fp1 ;
	FILE *temp_fp ;

	c = Apply_Char_Space() ;
	Init_blank( blank ) ;
	if( ap != 0 )
	{
		fp1 = fopen( "NIT������ļ�.txt", "r+" ) ;
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
			save_pos = ftell( fp1 ) ;//�ڶ�ȡ֮ǰ�ȼ�¼��ǰһ�����ݵ���ʼλ��
			fscanf( fp1, " %d %d", &temp_ap, &temp_weight ) ;
			if( temp_ap == ap )
			{
				//˵���Ѿ��ҵ�Ҫ�޸ĵ����ھ���
				break ;
			}
		}
		if( i <= num_e )
		{
			fseek( fp1, save_pos, SEEK_SET ) ;
			fgets( c, LONG_MAX, fp1 ) ;
			temp_fp = fopen( "��ʱ�ļ�.txt", "w+" ) ;
			if( !temp_fp )
			{
				OpenFailed() ;
			}
			fputs( c, temp_fp ) ;
			fseek( temp_fp, 0L, SEEK_SET ) ;
			fscanf( temp_fp, "%d %d", &temp_ap, &temp_weight ) ;//�ѵ�һ��(�ɵ�)���ݶ���
			fgets( c, LONG_MAX, temp_fp ) ;
			
			fseek( fp1, save_pos, SEEK_SET ) ;//ȷʵ�ص�����ȷ��λ��
			fputs( blank, fp1 ) ;//��������ַ���Ϊ�հ�
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
			printf( "û��������ڵľ���Ӵ-0-\n" ) ;
			return 0 ;
		}
	}
	else
	{
		fp1 = fopen( "NIT������ļ�.txt", "r+") ;
		if( !fp1 )
		{
			OpenFailed() ;
		}
		for( i = 1 ; i <= ID ; ++i )
		{
			fgets( c, LONG_MAX, fp1 ) ;
		}
		
		fscanf( fp1, "%d", &ID ) ;//��ʱID����ռ��ȡ��λ��,��ʵ����;
		save_pos = ftell( fp1 ) ;//***��¼��ǰfp1�ڲ��ļ�ָ���λ��***
		fgets( c, LONG_MAX, fp1 ) ;//��ID�����ȫ�����ݶ���
		
		temp_fp = fopen( "��ʱ�ļ�.txt", "w+" ) ;//��һ����ʱ�ļ������
		if( !temp_fp )
		{
			OpenFailed() ;
		}
		fputs( c, temp_fp ) ;//��ID�����ȫ�����ݷ�����ʱ�ļ���
		fseek( temp_fp, 0L, SEEK_SET ) ;//ʹ�ļ�ָ������ָ���ļ�ͷ
		fscanf( temp_fp, "%d", &num_e ) ;//����ʱ�ļ���ȡ�Ķ���ı���
		fgets( c, LONG_MAX, temp_fp ) ;//�ٽ����������������ݶ���
		
		fseek( fp1, save_pos, SEEK_SET ) ;
		fprintf( fp1, " %d", 1 + num_e ) ;
		save_pos = ftell( fp1 ) ;//***��¼��ǰfp1�ڲ��ļ�ָ���λ��***
		fputs( c, fp1 ) ;
		fseek( fp1, save_pos, SEEK_SET ) ;
		for( i = 1 ; i <=num_e ; ++i )
		{
			fscanf( fp1, "%d %d", &temp_ap, &temp_weight ) ;
		}
		fseek( fp1, 0L, SEEK_CUR ) ;
		fprintf( fp1, " %d %d", new_ap, new_weight ) ;
		free( c ) ;
		/* �ֱ��ҵ������ļ��Ŀ�ʼλ�ã����ͷ� */
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
	int i ;//��i���Ķ����ļ��еĶ�������

	if( fp = fopen( "NIT�����ļ�.txt", "r+" ) )
	{
		fscanf( fp, "%d", &i ) ;
		fseek( fp, -( ftell( fp ) ) , SEEK_CUR ) ;//�����ļ�ͷ��
		fprintf( fp, "%d", ++i ) ;//i�ԼӺ��Ϊ�µľ����ID
		fclose( fp ) ;//�ر��ļ�
		if( fp = fopen( "NIT�����ļ�.txt", "a+" ) )
		{
			fprintf( fp, "%d   ", i ) ;
			fputs( a, fp ) ;//д�뾰������
			fputc( 10, fp ) ;//д��һ���س�
			fclose( fp ) ;//�ر��ļ�
			return 1 ;
		}
	}
	OpenFailed() ;
	return 0 ;
}
char* Get_Password()
{
	int counter = 0 ;//������¼�����˼�λ����
	char ch, *p ;

	p = password ;//��ֵΪȫ�ֱ���
	for( ch = getch() ; ch != 13 && counter <= 16 ; ch = getch() )//������ַ���Ϊ�س���δ�ﵽ��������λ��ѭ������
	{
		if( ch == 8 && counter != 0 )//������ַ�Ϊ�˸�������������1λ����
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
			printf( "\n�ַ����Ϸ�Ү~.~����������\n" ) ;
		}
	}
	password[ counter ] = 0 ;//ĩβ����һ����������
	return password ;
}
int Check_Password()
{
	int i ;
	long num ;//������ȡ�����ļ��е�����Ϊ��
	char *p1, *p2, *temp ;//�ֱ�������ȡ�û����������������ļ��е�����,temp�����ͷ�p2����Ŀռ�
	FILE *fp ;
	
	printf( "����������:" ) ;
	p1 = Get_Password() ;
	temp = p2 = Apply_Char_Space() ;
	if( fp = fopen( "����Ա�����ļ�.txt", "r") )
	{
		fscanf( fp, "%d", &num ) ;
		fseek( fp, 2L, SEEK_CUR ) ;
		fgets( p2, num + 1 , fp ) ;
		fclose( fp ) ;//�ر��ļ�
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
	printf( "�������ڼ�����뺯����,�޷����ļ�\n" ) ;//����ά����Ա
	exit( 1 ) ;
}
void Search_Path()
{
	PN *Adja_List ;
	int i, Start, End ;// i������־�Ƿ�����û������λ��

	Adja_List = Init_Graph() ;
	Update_Graph( Adja_List ) ;
	for( i = 0 ; i != 1 ; )
	{
		printf( "��������Ҫ��ѯ·�ߵ����:" ) ;
		scanf( "%d", &Start ) ;
		i = Find_Path( Start ,Adja_List ) ;
	}
	for( i = 0 ; i != 1 ; )
	{
		printf( "��������Ҫ��ѯ·�ߵ��յ�:" ) ;
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
		printf( "��,�����˸���ָ·��,�����Ͻ�����һ�£�o��:\n" ) ;
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
		printf( "                       �밴������������˵�^_^\n" ) ;
		getch() ;
		return 1 ;
	}
	else
	{
		printf( "��Ǹ��,�Ҳ����������յ�Ү@-@\n" ) ;
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

	Edges = Cal_All_Edges( Adja_List ) ;//�����ܱ���
	MinHeap = Init_PQ( Edges, 0 ) ;//����һ���ͱ�����ͬ��С����С��
	current = Find_Vertex( Start, Adja_List ) ;//�ҵ���ʼ���
	if( current )
	{
		current->Dist = 0 ;
		Insert_PQ( current, MinHeap ) ;
		for( ; !IsEmpty( MinHeap ) ; )
		{
			current = Delete_Min( MinHeap ) ;
			for( temp = current->All_e ; temp != NULL ; temp = temp->Next )
			{
				if( current->Dist + temp->weight < temp->adja_p->Dist )//��������ȣ�������ǰ������·�������Ա�֤���·����ת�۵�����
				{
					temp->adja_p->Dist = current->Dist + temp->weight ;//���±߽�㵽������Distֵ
					temp->adja_p->Path = current ;//����ǰ������߽�㵽������·����
					Insert_PQ( temp->adja_p, MinHeap ) ;
				}
			}
		}
		return 1 ;
	}
	else
	{
		printf( "�ܱ�Ǹ������Ҳ������������T^T,�ɲ����Ի�һ��\n" ) ;
		return 0 ;
	}
	
}
PN* Delete_Min( PQ *MinHeap )
{
	int i, Child ;
	PN *Min, *Last ;
	
	if( !IsEmpty( MinHeap ) )//�����ж϶ѿղ���
	{
		Min = MinHeap->Elem[ 1 ] ;
		Last = MinHeap->Elem[ ( MinHeap->Cur_Size )-- ] ;
		for( i = 1 ; 2 * i <= MinHeap->Cur_Size ; i = Child )
		{
			Child = 2 * i ;
			if( Child != MinHeap->Cur_Size && MinHeap->Elem[ Child ]->Dist > MinHeap->Elem[ 1 + Child ]->Dist )//ͨ��Dist�Ƚϴ�С
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
	int v, e, ap ;//�ֱ��ʾ���㣬�ߵĸ������ڽӵ�
	char *c ;
	PN *current ;
	EN *p ;
	FILE *fp ;

	if( fp = fopen( "NIT������ļ�.txt", "r" ) )
	{
		fscanf( fp, "%d", &n ) ;
		c = Apply_Char_Space() ;
		fgets( c, 50, fp ) ;//����һ�ж�ȡ��
		/* ��ȡ�꼴���ͷ� */free( c ) ;
	}
	else
	{
		OpenFailed() ;//���ļ�ʧ��
	}
	for( i = 1 ; i <= n ; ++i )
	{
		fscanf( fp, "%d %d ", &v, &e ) ;
		current = Find_Vertex( v, Adja_List ) ;//�ҵ���Ҫ���µĶ���
		current->Num_e = e;//��¼�ߵ����� 
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
	fclose( fp ) ;//�ر��ļ�
}
PN* Find_Vertex( int v, PN *current )
{
	for( current ; current && current->ID != v ; current = current->Next ) ;
	if( current )
	{
		return current ;
	}
	//printf( "Error: No such vertex!\n" ) ;//��ʽ���г���ʱ�����ע�͵�
	return NULL ;
}
PN* Init_Graph()
{
	int i, Size ;
	char *c ;
	PN *p, *temp, *Adja_List ;
	FILE *fp ;
	
	c = Apply_Char_Space() ; 
	if( fp = fopen( "NIT�����ļ�.txt", "r" ) )
	{
		fscanf( fp, "%d", &Size ) ;//��ȡ����ͼ�ĵص�����
	}
	else
	{
		OpenFailed() ;//���ļ�ʧ��
	}
	fgets( c, LONG_MAX, fp ) ;//��200���ֽ�����֤���ļ���һ�ж�ȡ��
	/* ��ȡ�꼴���ͷ� */free( c ) ;
	for( i = 1 ; i <= Size ; ++i )
	{
		p = ( PN* )malloc( sizeof( PN ) ) ;
		if( p )
		{
			p->Name = Apply_Char_Space() ;//��������������ռ�
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
	fclose( fp ) ;//�ر��ļ�(�ڴ˴�ִ�и�������)
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
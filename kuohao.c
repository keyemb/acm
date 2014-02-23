#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define	TRUE		1
#define	FALSE	0

char *strdupp( char *string, char const ch )
{
	char *new_string = NULL;

	new_string = (char *)malloc( strlen( string ) + 2 );

	if( new_string != NULL )
		strcpy( new_string, string );

	new_string[ strlen( string ) ] = ch;
	new_string[ strlen( string ) + 1 ] = '\0';

	free( string );

	return new_string;
}

int jishu( char const *str, char const ch )
{
	int len = 0;
	while( ( str = strchr( str, ch ) ) != NULL )
	{
		str++;
		len++;
	}
	return len;
}

int peidui( char const *str )
{
	if( *str == ']' || *str == ')' )
		return	FALSE;
		
	if( ( strlen( str ) % 2 ) == 1 )
		return	FALSE;
		
	if( jishu( str, '[' ) != jishu( str, ']' ) )
		return	FALSE;
	else if( jishu( str, '(' ) != jishu( str, ')' ) )
		return	FALSE;
	else
		return	TRUE;
}

int digui( char const *str )
{
	int i = 0, j;
	int k1, k2;
	char *strcp = NULL, ch;

	strcp = (char *)malloc( ( strlen( str ) + 1 ) * sizeof(char) );
	
	while( str[i] != '\0' )
	{
		k1 = k2 = j = 0;
		if( str[i] == '(' )
		{
			while( !( ( ch = str[ i+j+1 ] ) == ')' &&  ( k1 == k2 ) ) )
			{	
				strcp[j] = ch;
				if( ch == '(' )
					k1++;
				else if( ch == ')' )
					k2++;	
				j++;			 
			}
		}
		else if( str[i] == '[' )
		{
			while( !( ( ch = str[ i+j+1 ] ) == ']' &&  ( k1 == k2 ) ) )
			{
				strcp[j] = ch;
				if( ch == '[' )
					k1++;
				else if(ch == ']' )
					k2++;	
				j++;			 
			}
		}
		i++;
		if( j == 0 )
			continue;
		strcp[j] = '\0';
		if( peidui( strcp ) )
			continue;
		else
		{
			free( strcp );
			return	FALSE;
		}
	}
	free( strcp );
	return TRUE;
}

int main( void )
{
	int N, i;
	char c, *S[100] = {NULL};
	
	scanf( "%d", &N );
	getchar();
	if( N <= 0 || N > 100 )
		return	EXIT_FAILURE;
	
	for( i = 0; i < N; i++ ){
		while( ( c = getchar() ) != '\n')
		{
			if( S[i] == NULL )
			{
				S[i] = (char *)malloc( 2 * sizeof(char) );
				S[i][0] = c;
				S[i][1] = '\0';
			}
			else
			{
				S[i] = strdupp( S[i], c );
			}
		}
	}
	for( i = 0; i < N; i++ ){
		if( peidui( S[i] ) && digui( S[i] ) )
			puts("Yes");
		else
			puts("No");
		free( S[i] );
	}
	return	EXIT_SUCCESS;
}

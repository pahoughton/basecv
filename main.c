/*********************************************************************
 *
 * File:        main.c
 * Project:	basecv
 * Desc:
 *
 *  
 *
 * Notes:
 *
 * Author:	Paul A. Houghton - (paul.houghton@wcom.com)
 * Created:	05/07/99 04:45
 *
 * Revision History: (See end of file for Revision Log)
 *
 *  Last Mod By:    $Author$
 *  Last Mod:	    $Date$
 *  Version:	    $Revision$
 *
 *********************************************************************/

#include "basecv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char * Digits = "0123456789abcdefghijklmnopqrstuvwxyz";
static const int _CharToNum[] =
{
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23, 24,
  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  -1,  -1,  -1,  -1, -1,
  -1,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23, 24,
  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,
};

static const char * White = " \t\r\n\f";

const int	MaxBase = MAX_BASE;

/*
 * Options
 */

int		Debug = 0;

#define CharToInt( c_ )	(_CharToNum[ (int)c_ ])

#define CharIsBaseDigit( c_, b_ )					      \
    (CharToInt( c_ ) > 0 && CharToInt( c_ ) < b_ )

unsigned long
ToULong( const char * inNumber, const char * inBase )
{
  const char *  conv;
  const char *  end;
  size_t	base;
  unsigned long	value;
  
  conv    = inNumber;
  end	  = conv + strlen( conv );
  value   = 0;

  if( (base = atoi(inBase)) <= 0 || base > MaxBase )
    {
      fprintf( stderr, "invalid input base '%s'\n", inBase );
      exit( 1 );
    }
  
  /* skip past white space */
  for( ; conv < end && strchr( White, *conv ); ++ conv );

  /* ignore trailing white space */
  for( ; end > conv && strchr( White, *(end - 1) ); -- end );
  
  if( conv >= end )
    {
	fprintf( stderr, "no digits in '%s'\n", inNumber );
	exit( 1 );
    }
  
  for( ; conv < end; ++ conv )
    {
      if( CharIsBaseDigit( *conv, base ) )
	{
	  value *= base;
	  value += CharToInt( *conv );
	}
      else
	{
	  fprintf( stderr, "invalid input character '%c' in '%s'\n",
		   *conv,
		   inNumber );
	  exit( 1 );
	}
    }
  
  if( Debug ) fprintf( stderr, "Value: %lu\n", value );
  
  return( value );
}

const char *
ToString( unsigned long value, const char * outBase, int pretty )
{
  static char outNumber[ 512 ];
  
  unsigned long num;
  size_t	base;
  char *	end;
  size_t	size;
  size_t	digitCount;
    
  num		= value;
  size		= sizeof( outNumber ) - 1;
  end		= outNumber + size - 1;
  *(end + 1)	= 0;
  digitCount	= 1;
    
  if( (base = atoi(outBase)) <= 0 || base > MaxBase )
    {
      fprintf( stderr, "invalid input base '%s'\n", outBase );
      exit( 1 );
    }
  
  for( ; num != 0 && size; -- end, -- size, ++ digitCount, num /= base )
    {
      *end = Digits[ (num % base) ];
      if( pretty && size > 1 && num > base )
	{
	  switch( base )
	    {
	    case 10:
	      if( (digitCount % 3) == 0 )
		{
		  -- end;
		  *end = ',';
		}
	      break;

	    case 8:
	      if( (digitCount % 3 ) == 0 )
		{
		  -- end;
		  *end = ' ';
		}
	      break;
		
	    case 2:
	    case 16:
	    default:
	      if( ( digitCount % 4 ) == 0 )
		{
		  -- end;
		  *end = ' ';
		}
	      break;
	    }
	}
    }
  return( end + 1 );
}

int
main( int argc, char * argv[] )
{
  char		    inBase[ 4 ];
  char		    outBase[ 4 ];
  char		    inNumber[ 512 ];
  unsigned long	    value;
  const char *	    outNumber;
  
  struct BasecvParam	param;

  param.inBase  = 0;
  param.outBase = 0;
  param.number  = 0;
  param.raw	= 0;
  
  if( ! process_options( &argc, &argv, &param ) )
    exit( 1 );

  if( ! param.inBase )
    {
      fputs( "input base: ", stdout );
      if( ! fgets( inBase, sizeof( inBase ), stdin ) )
	exit( 1 );
      if ( inBase[0] == '\n' )
	exit( 0 );
      param.inBase = inBase;
    }

  if( ! param.outBase )
    {
      fputs( "output base: ", stdout );
      if( ! fgets( outBase, sizeof( outBase ), stdin ) )
	exit( 1 );
      param.outBase = outBase;
    }

  if( ! param.number )
    {
      fputs( "number: ", stdout );
      if( ! fgets( inNumber, sizeof( inNumber ), stdin ) )
	exit( 1 );
      param.number = inNumber;
    }

  for( ;; )
    {
      value = ToULong( param.number, param.inBase );
      
      outNumber = ToString( value, param.outBase, param.raw ? 0 : 1 );
      
      puts( outNumber );

      if( param.number != inNumber )
	break;

      fputs( "input base: ", stdout );
      if( ! fgets( inBase, sizeof( inBase ), stdin ) )
	break;
      if ( inBase[0] == '\n' )
	exit( 0 );
      param.inBase = inBase;
      
      fputs( "output base: ", stdout );

      if( ! fgets( outBase, sizeof( outBase ), stdin ) )
	exit( 1 );
      param.outBase = outBase;
      
      fputs( "number: ", stdout );

      if( ! fgets( inNumber, sizeof( inNumber ), stdin ) )
	exit( 1 );
    }
      

  return( 0 );

}

/*
 *
 * Revision Log:
 *
 * $Log$
 * Revision 1.1  1999/05/07 15:58:46  houghton
 * Initial Version.
 *
 *
 */

/*********************************************************************
 *
 * File:        options.c
 * Project:	basecv
 * Desc:
 *
 *  
 *
 * Notes:
 *
 * Author:	Paul A. Houghton - (paul.houghton@wcom.com)
 * Created:	05/07/99 06:06
 *
 * Revision History: (See end of file for Revision Log)
 *
 *  Last Mod By:    $Author$
 *  Last Mod:	    $Date$
 *  Version:	    $Revision$
 *
 *********************************************************************/

const char * _basecv_options_version =
"$Id$";

#include "basecv.h"

#include <getopt.h>
#include <stdio.h>
#include <ctype.h>

#if STDC_HEADERS 
#include <string.h>
#endif

struct option BasecvOptions[] =
{
  { "help",		no_argument,	    0, 'H' },
  { "version",		no_argument,	    0, 'V' },
  { "input-base",	required_argument,  0, 'i' },
  { "output-base",	required_argument,  0, 'o' },
  { "number",		required_argument,  0, 'n' },
  { "raw",		no_argument,	    0, 'r' },
  { 0, 0, 0, 0 }
};

struct Help
{
  int		argId;
  const char *	desc;
  const char *  argdesc;
};

/*
 * Must be sorted
 */
struct Help BasecvHelp[] =
{
  { 'H', "show this help.", "" },
  { 'V', "show the version", "" },
  { 'i', "input base (2-" MAX_BASE_STRING ").", "number" },
  { 'n', "number to convert (0-MAX_ULONG)", "number" },
  { 'o', "output base (2-" MAX_BASE_STRING ").", "number" },
  { 'r', "output the 'raw' number (no commas or spaces)." "" },
  { 0, 0, 0 }
};

static void
show_version( void )
{
  printf( "%s version %s, convert a number from one base to another.\n",
	  PACKAGE, VERSION );
}

static void
usage( void )
{
  size_t    arg;
  size_t    help;
  size_t    arglen;
  char *    fmtString;

  show_version();

  printf( "Usage: %s [options]\n"
	  "\n"
	  "Options:\n",
	  PACKAGE );
  
  for( arg = 0; BasecvOptions[ arg ].name; ++ arg )
    {
      for( help = 0; BasecvHelp[ help ].argId; ++ help )
	{
	  if( BasecvHelp[ help ].argId == BasecvOptions[ arg ].val )
	    break;
	}
      
      if( BasecvOptions[ arg ].has_arg )
	{
	  arglen = ( strlen( BasecvHelp[help].argdesc) +
		     strlen(BasecvOptions[arg].name) );
	  
	  if( BasecvOptions[arg].has_arg == required_argument )
	    fmtString = "  %c%c%c --%s=%s%*s  %s%s\n";
	  else
	    fmtString = "  %c%c%c --%s=[%s]%*s%s%s\n";
	  
	  printf( fmtString,
		  ( isalpha( BasecvOptions[arg].val ) ? '-' : ' ' ),
		  ( isalpha( BasecvOptions[arg].val ) ?
		    BasecvOptions[arg].val : ' ' ),
		  ( isalpha( BasecvOptions[arg].val ) ? ',' : ' ' ),
		  BasecvOptions[arg].name,
		  BasecvHelp[help].argdesc,
		  ( arglen <= 9 ? 9 - arglen : 1 ),
		  " ",
		  ( arglen <= 9 ?
		    " " : "\n                      " ),
		  BasecvHelp[help].desc );
	}
      else
	{
	  printf( "  %c%c%c --%-12s %s%s\n",
		  ( isalpha( BasecvOptions[arg].val ) ? '-' : ' ' ),
		  ( isalpha( BasecvOptions[arg].val ) ?
		    BasecvOptions[arg].val : ' ' ),
		  ( isalpha( BasecvOptions[arg].val ) ? ',' : ' ' ),
		  BasecvOptions[arg].name,
		  ( strlen( BasecvOptions[arg].name ) <= 12 ?
		    " " : "\n                      " ),
		  BasecvHelp[help].desc );
	}
    }
}

int
process_options( int * argc, char *** argv, struct BasecvParam * param )
{
  int	opt;

  int	show_help = 0;
  int	show_ver = 0;
  
  while( (opt = getopt_long( *argc, *argv,
			     "i:o:n:rVH",
			     BasecvOptions,
			     (int *)0)) != EOF )
    {
      switch( opt )
	{
	default:
	  fprintf( stderr," invalid argument '%c' (%d)\n", opt, opt );
	case 'H':
	  show_help = 1;
	  break;
	  
	case 'V':
	  show_ver = 1;
	  break;

	case 'i':
	  (*param).inBase = strdup( optarg );
	  break;

	case 'o':
	  (*param).outBase = strdup( optarg );
	  break;

	case 'n':
	  (*param).number = strdup( optarg );
	  break;

	case 'r':
	  (*param).raw = 1;
	  break;
	}
    }
  if( show_help )
    {
      usage();
      return( 0 );
    }
  else
    {
      if( show_ver )
	{
	  show_version();
	  return( 0 );
	}
    }
  return( 1 );
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

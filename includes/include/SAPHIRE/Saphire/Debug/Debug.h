/*
 * Debug.h
 *
 *  Created on: 03-01-2013
 *      Author: rast
 */

#ifndef DEBUG_H_
#define DEBUG_H_

	#define CALLERPOS 3

	#ifndef WINDOWS
		#define RESET		0
		#define BRIGHT 		1
		#define DIM			2
		#define UNDERLINE 	3
		#define BLINK		4
		#define REVERSE		7
		#define HIDDEN		8

		#define BLACK 		0
		#define RED			1
		#define GREEN		2
		#define YELLOW		3
		#define BLUE		4
		#define MAGENTA		5
		#define CYAN		6
		#define	WHITE		7

		#define BBLACK 		0
		#define BRED			1
		#define BGREEN		2
		#define BYELLOW		3
		#define BBLUE		4
		#define BMAGENTA		5
		#define BCYAN		6
		#define BWHITE		7

	#else

		#define RESET		0
		#define BRIGHT 		1
		#define DIM			2
		#define UNDERLINE 	3
		#define BLINK		4
		#define REVERSE		7
		#define HIDDEN		8

		#define BLACK 		0
		#define RED			FOREGROUND_RED
		#define GREEN		FOREGROUND_GREEN
		#define YELLOW		FOREGROUND_BLUE
		#define BLUE			FOREGROUND_BLUE
		#define MAGENTA	FOREGROUND_BLUE
		#define CYAN			FOREGROUND_BLUE
		#define	WHITE		FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN

		#define BBLACK 		0
		#define BRED			BACKGROUND_RED
		#define BGREEN		BACKGROUND_GREEN
		#define BYELLOW		BACKGROUND_BLUE | BACKGROUND_RED
		#define BBLUE		BACKGROUND_BLUE
		#define BMAGENTA		BACKGROUND_BLUE
		#define BCYAN		BACKGROUND_BLUE
		#define BWHITE		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED

	#endif

		#ifdef ANDROID

			#define color(attr,fg,bg)
			#define DEBUG_PRINT(where,format, ...)  __android_log_print( ANDROID_LOG_INFO , where,format,  __VA_ARGS__ );
			#define DEBUG_ERROR(where,format, ...)  __android_log_print( ANDROID_LOG_INFO , where,format,  __VA_ARGS__ );
			#define DEBUG_WARNING(where,format, ...)  __android_log_print( ANDROID_LOG_INFO , where,format,  __VA_ARGS__ );
			#define DEBUG_INFO(where,format, ...)  __android_log_print( ANDROID_LOG_INFO , where,format,  __VA_ARGS__ );
		#else

		# ifdef LINUX

			#define color(attr,fg,bg) printf ("%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
			#define DEBUG_PRINT(where,format, args... ) color( RESET ,GREEN,BBLACK); printf ("[%s]", where); color( RESET ,WHITE,BBLACK); printf(format,  args  );  printf ("\n");  fflush( stdout );
			#define DEBUG_ERROR(where,format, args... ) color( RESET ,RED,BBLACK); printf ("[%s]", where); color( BRIGHT ,RED,BBLACK); printf(format,  args  );  printf ("\n");  fflush( stdout );
			#define DEBUG_WARNING(where,format, args... ) color( RESET ,GREEN,BBLACK); printf ("[%s]", where); color( RESET ,WHITE,BBLACK); printf(format,  args  );  printf ("\n");  fflush( stdout );
			#define DEBUG_INFO(where,format, args... ) color( BRIGHT ,GREEN,BBLACK); printf ("[%s]", where); color( BRIGHT ,WHITE,BCYAN); printf(format,  args  );  printf ("\n");  fflush( stdout );
		#endif

		#ifdef WINDOWS

			#define color(attr,fg,bg)   SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), fg | bg);
			#define DEBUG_PRINT(where,format, args... ) color( RESET ,GREEN,BBLACK); printf ("[%s]", where); color( RESET ,WHITE,BBLACK); printf(format,  args  );  printf ("\n");  fflush( stdout );
			#define DEBUG_ERROR(where,format, args... ) color( RESET ,RED,BBLACK); printf ("[%s]", where); color( BRIGHT ,RED,BBLACK); printf(format,  args  );  printf ("\n");  fflush( stdout );
			#define DEBUG_WARNING(where,format, args... ) color( RESET ,GREEN,BBLACK); printf ("[%s]", where); color( RESET ,WHITE,BBLACK); printf(format,  args  );  printf ("\n");  fflush( stdout );
			#define DEBUG_INFO(where,format, args... ) color( BRIGHT ,GREEN,BBLACK); printf ("[%s]", where); color( BRIGHT ,WHITE,BCYAN); printf(format,  args  );  printf ("\n");  fflush( stdout );
		#endif
	#endif

#endif /* DEBUG_H_ */


